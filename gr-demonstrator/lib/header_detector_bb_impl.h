/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_HEADER_DETECTOR_BB_IMPL_H
#define INCLUDED_DEMONSTRATOR_HEADER_DETECTOR_BB_IMPL_H

#include <demonstrator/header_detector_bb.h>

namespace gr {
namespace demonstrator {

class header_detector_bb_impl : public header_detector_bb
{
private:
    size_t d_sequence_index;
    std::vector<unsigned char> d_check_history;  // Stores the recent history of received bytes
    bool d_copy_mode; // Flag to indicate if we're in the mode of copying bytes
    int d_bytes_remaining; // Counter for the remaining bytes to copy
    int d_bytes_to_copy; //Total of bytes per packet
    int d_bytes_header; //Number of byte of the header
    int d_state;

public:
    header_detector_bb_impl(int n_payload_bytes);
    ~header_detector_bb_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);

    // Define the known sequence as a static constant
    static const std::array<unsigned char, 32> KNOWN_SEQUENCE;
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_HEADER_DETECTOR_BB_IMPL_H */
