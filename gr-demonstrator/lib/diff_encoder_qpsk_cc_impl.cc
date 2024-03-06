/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "diff_encoder_qpsk_cc_impl.h"
#include <gnuradio/io_signature.h>
#include <cmath> // Include the cmath library for sqrt

namespace gr {
namespace demonstrator {


diff_encoder_qpsk_cc::sptr diff_encoder_qpsk_cc::make()
{
    return gnuradio::make_block_sptr<diff_encoder_qpsk_cc_impl>();
}


/*
 * The private constructor
 */
diff_encoder_qpsk_cc_impl::diff_encoder_qpsk_cc_impl()
    : gr::sync_block("diff_encoder_qpsk_cc",
                     gr::io_signature::make(1, 1, sizeof(gr_complex)),
                     gr::io_signature::make(1, 1, sizeof(gr_complex))),
                     d_last_out(0),
                     d_modulus(sqrt(2)/2)
{
}

/*
 * Our virtual destructor.
 */
diff_encoder_qpsk_cc_impl::~diff_encoder_qpsk_cc_impl() {}

unsigned int diff_encoder_qpsk_cc_impl::phase_pos(gr_complex symbol){
    if (symbol.real() > 0 && symbol.imag() > 0) return 0;
    if (symbol.real() < 0 && symbol.imag() > 0) return 1;
    if (symbol.real() < 0 && symbol.imag() < 0) return 2;
    if (symbol.real() > 0 && symbol.imag() < 0) return 3;
    return 0;
}

gr_complex diff_encoder_qpsk_cc_impl::phase_pos2symbol(unsigned int phase_pos){
    float mod = d_modulus;
    switch (phase_pos)
    {
    case 0:
        return gr_complex(mod, mod);
        break;
    case 1:
        return gr_complex(-mod, mod);
        break;
    case 2:
        return gr_complex(-mod, -mod);
        break;
    case 3:
        return gr_complex(mod, -mod);
        break; 
    default:
        return gr_complex(mod, mod);
        break;
    }
}

int diff_encoder_qpsk_cc_impl::work(int noutput_items,
                                    gr_vector_const_void_star& input_items,
                                    gr_vector_void_star& output_items)
{
    const gr_complex* in = (const gr_complex*)input_items[0];
    gr_complex* out = (gr_complex*)output_items[0];
    unsigned int phase_position;
    unsigned int last_out = d_last_out;
    unsigned int phase_out;


    for (int i = 0; i < noutput_items; i++) {
            phase_out = (phase_pos(in[i]) + last_out) % 4;
            out[i] = phase_pos2symbol(phase_out);
            last_out = phase_out;
}
    d_last_out = last_out;
    return noutput_items;
} /* namespace demonstrator */
} /* namespace gr */
}
