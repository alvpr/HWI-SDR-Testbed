/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "sequence_detector_bb_impl.h"
#include <gnuradio/io_signature.h>
#include <array>
//#include <gnuradio/pmt/pmt.h>



namespace gr {
namespace demonstrator {

// Define the known sequence
const std::array<unsigned char, 32> gr::demonstrator::sequence_detector_bb_impl::KNOWN_SEQUENCE = {
    2, 2, 3, 0, 3, 1, 3, 1, 2, 2, 1, 0, 3, 2, 0, 2,
    3, 3, 0, 2, 2, 0, 3, 0, 0, 2, 0, 0, 3, 3, 3, 0
};


sequence_detector_bb::sptr sequence_detector_bb::make()
{
    return gnuradio::make_block_sptr<sequence_detector_bb_impl>();
}


/*
 * The private constructor
 */
sequence_detector_bb_impl::sequence_detector_bb_impl() 
    : gr::sync_block("sequence_detector_bb",
                     gr::io_signature::make(1, 1, sizeof(unsigned char)),
                     gr::io_signature::make(1, 1, sizeof(unsigned char))),
      d_sequence_index(0), d_copy_mode(false), d_bytes_remaining(0), d_bytes_to_copy(412)
{
    d_check_history.resize(KNOWN_SEQUENCE.size(), 0);
}

/*
 * Our virtual destructor.
 */
sequence_detector_bb_impl::~sequence_detector_bb_impl() {}

int sequence_detector_bb_impl::work(int noutput_items,
                                    gr_vector_const_void_star& input_items,
                                    gr_vector_void_star& output_items)
{
    const unsigned char *in = (const unsigned char *) input_items[0];
    unsigned char *out = (unsigned char *) output_items[0];


    for (int i = 0; i < noutput_items; ++i) {
        // Update the check history with the current byte for sequence detection only if we are not putting bytes at the output
        d_check_history.push_back(in[i]);
        if (d_check_history.size() > KNOWN_SEQUENCE.size()) {
            d_check_history.erase(d_check_history.begin()); // Keep the history buffer's size constant
            // Check if the current history matches the known sequence
        if (d_check_history.size() == KNOWN_SEQUENCE.size()) {
            if (std::equal(d_check_history.begin(), d_check_history.end(), KNOWN_SEQUENCE.begin())) {
                // Sequence found, add a tag to the next item
                add_item_tag(0, nitems_written(0) + i + 1, pmt::string_to_symbol("nb"), pmt::from_long(400));
                d_sequence_index = 0;
                d_check_history.clear(); // Clear history after a successful match
                d_copy_mode = true; // Start copying bytes
                d_bytes_remaining = 412;
            }
        }
        }
        out[i] = in[i];
    }

    return noutput_items;
}

} /* namespace demonstrator */
} /* namespace gr */
