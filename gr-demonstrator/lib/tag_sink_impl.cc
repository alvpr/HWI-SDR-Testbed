/* -*- c++ -*- */
/*
 * Copyright 2024 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "tag_sink_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace demonstrator {

tag_sink::sptr tag_sink::make(const std::string& filename, const std::string& tag_key)
{
    return gnuradio::make_block_sptr<tag_sink_impl>(filename, tag_key);
}


/*
 * The private constructor
 */
tag_sink_impl::tag_sink_impl(const std::string& filename, const std::string& tag_key)
    : gr::sync_block("tag_sink",
                     gr::io_signature::make(
                         1 ,1, sizeof(gr_complex)),
                     gr::io_signature::make(0, 0, 0)),
    d_tag_key(tag_key),
    d_filename(filename),
    d_file(d_filename, std::ios::binary | std::ios::out) // Open the file for writing, in append mode
{
    if (!d_file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
      }
}


tag_sink_impl::~tag_sink_impl() {}

int tag_sink_impl::work(int noutput_items,
                        gr_vector_const_void_star& input_items,
                        gr_vector_void_star& output_items)
{
    const gr_complex *in = (const gr_complex *) input_items[0]; // Cast input stream to complex numbers
    // Define the range to search for tags
    uint64_t start = nitems_read(0); // Start of the range
    uint64_t end = start + noutput_items; // End of the range

    // Vector to hold the tags found in the range
    std::vector<tag_t> tags;

    // Retrieve all tags in the given range with the specified key
    get_tags_in_range(tags, 0, start, end, pmt::string_to_symbol(d_tag_key));

    // Iterate through each found tag
    for (const tag_t &tag : tags) {
        // Extract the value from the tag
        pmt::pmt_t value = tag.value;
        d_channel_state = pmt::c32vector_elements(tag.value);
        // Write the contents of d_channel_state to the file
        for (const auto& complex_value : d_channel_state) {
            d_file.write(reinterpret_cast<const char*>(&complex_value), sizeof(gr_complex));
        }
    }

    // Tell runtime system how many input items we consumed on each input stream.
    consume_each(noutput_items);

    // Return number of output items produced, which is 0 for a sink
    return 0;
}

} /* namespace demonstrator */
} /* namespace gr */
