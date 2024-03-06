/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_DIFF_DECODER_QPSK_CC_IMPL_H
#define INCLUDED_DEMONSTRATOR_DIFF_DECODER_QPSK_CC_IMPL_H

#include <demonstrator/diff_decoder_qpsk_cc.h>

namespace gr {
namespace demonstrator {

class diff_decoder_qpsk_cc_impl : public diff_decoder_qpsk_cc
{
private:
    const float d_modulus;
    unsigned int phase_pos(gr_complex symbol);
    gr_complex phase_pos2symbol(unsigned int pahse_pos);

public:
    diff_decoder_qpsk_cc_impl();
    ~diff_decoder_qpsk_cc_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_DIFF_DECODER_QPSK_CC_IMPL_H */
