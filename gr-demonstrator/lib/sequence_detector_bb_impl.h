/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_SEQUENCE_DETECTOR_BB_IMPL_H
#define INCLUDED_DEMONSTRATOR_SEQUENCE_DETECTOR_BB_IMPL_H

#include <demonstrator/sequence_detector_bb.h>
//#include <gnuradio/pmt/pmt.h>


namespace gr {
namespace demonstrator {

class sequence_detector_bb_impl : public sequence_detector_bb
{
private:
    size_t d_sequence_index;
    std::vector<unsigned char> d_check_history;  // Stores the recent history of received bytes
    bool d_copy_mode; // Flag to indicate if we're in the mode of copying bytes
    int d_bytes_remaining; // Counter for the remaining bytes to copy
    int d_bytes_to_copy; //Total of bytes per packet

public:
    sequence_detector_bb_impl();
    ~sequence_detector_bb_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);

    // Define the known sequence as a static constant
    static const std::array<unsigned char, 32> KNOWN_SEQUENCE;
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_SEQUENCE_DETECTOR_BB_IMPL_H */
