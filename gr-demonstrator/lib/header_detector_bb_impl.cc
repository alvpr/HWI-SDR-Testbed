/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "header_detector_bb_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace demonstrator {

// Define the known sequence
const std::array<unsigned char, 32> gr::demonstrator::header_detector_bb_impl::KNOWN_SEQUENCE = {
    2, 2, 3, 0, 3, 1, 3, 1, 2, 2, 1, 0, 3, 2, 0, 2,
    3, 3, 0, 2, 2, 0, 3, 0, 0, 2, 0, 0, 3, 3, 3, 0
};

enum packet_states_t {
    STATE_FIND_HEADER,       // Finding header
    STATE_COPY            // Copy Input to Output
};

header_detector_bb::sptr header_detector_bb::make(int n_payload_bytes)
{
    return gnuradio::make_block_sptr<header_detector_bb_impl>(n_payload_bytes);
}


/*
 * The private constructor
 */
header_detector_bb_impl::header_detector_bb_impl(int n_payload_bytes)
    : gr::block("header_detector_bb",
                gr::io_signature::make(1, 1, sizeof(unsigned char)),
                     gr::io_signature::make(1, 1, sizeof(unsigned char))),
      d_sequence_index(0), d_copy_mode(false), d_bytes_remaining(0), d_bytes_to_copy(n_payload_bytes), 
      d_bytes_header(KNOWN_SEQUENCE.size()), d_state(STATE_FIND_HEADER)
{
    d_check_history.resize(KNOWN_SEQUENCE.size(), 0);
}

/*
 * Our virtual destructor.
 */
header_detector_bb_impl::~header_detector_bb_impl() {}

void header_detector_bb_impl::forecast(int noutput_items,
                                       gr_vector_int& ninput_items_required)
{
    /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
}

int header_detector_bb_impl::general_work(int noutput_items,
                                          gr_vector_int& ninput_items,
                                          gr_vector_const_void_star& input_items,
                                          gr_vector_void_star& output_items)
{
    const unsigned char *in = (const unsigned char *) input_items[0];
    unsigned char *out = (unsigned char *) output_items[0];

    int items_copied = 0;
    int items_processed = 0;

/*
    switch (d_state) {
    case STATE_FIND_HEADER:
        // In an ideal world, this would never be called
        // parse_header_data_msg() is the only place that can kick us out
        // of this state.
        return 0;

    case STATE_COPY:
        out[items_copied++] = in[i];
            if (--d_bytes_remaining <= 0) {
                d_copy_mode = false; // Stop copying after 'n' bytes
            }
        break;
*/
    for (int i = 0; i < noutput_items; ++i) {
        // Update the check history with the current byte for sequence detection only if we are not putting bytes at the output
        if(!d_copy_mode){
            d_check_history.push_back(in[i]);
            if (d_check_history.size() > KNOWN_SEQUENCE.size()) {
            d_check_history.erase(d_check_history.begin()); // Keep the history buffer's size constant
            }
            if (d_check_history.size() == KNOWN_SEQUENCE.size()) {
                if (std::equal(d_check_history.begin(), d_check_history.end(), KNOWN_SEQUENCE.begin())) {
                // Sequence found, add a tag to the next item
                add_item_tag(0, nitems_written(0) + i + 1, pmt::string_to_symbol("nb"), pmt::from_long(400));
                d_sequence_index = 0;
                d_check_history.clear(); // Clear history after a successful match
                d_copy_mode = true; // Start copying bytes
                d_bytes_remaining = d_bytes_to_copy;
            }
            }
        }else{
            out[items_copied++] = in[i];
            if (--d_bytes_remaining <= 0) {
                d_copy_mode = false; // Stop copying after 'n' bytes
            }
            continue;
        }
        items_processed++;
    }

    // Tell the runtime system how many input items we consumed on each input stream.
    consume_each(items_processed);

    // Tell the runtime system how many output items we produced.
    return items_copied;
}

} /* namespace demonstrator */
} /* namespace gr */
