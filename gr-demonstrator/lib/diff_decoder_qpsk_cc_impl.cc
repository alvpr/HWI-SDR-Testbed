/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "diff_decoder_qpsk_cc_impl.h"
#include <gnuradio/io_signature.h>
#include <cmath> // Include the cmath library for sqrt

namespace gr {
namespace demonstrator {


diff_decoder_qpsk_cc::sptr diff_decoder_qpsk_cc::make()
{
    return gnuradio::make_block_sptr<diff_decoder_qpsk_cc_impl>();
}


/*
 * The private constructor
 */
diff_decoder_qpsk_cc_impl::diff_decoder_qpsk_cc_impl()
    : gr::sync_block("diff_decoder_qpsk_cc",
                     gr::io_signature::make(1, 1, sizeof(gr_complex)),
                     gr::io_signature::make(1, 1, sizeof(gr_complex))),
                     d_modulus(sqrt(2)/2)
{
}

/*
 * Our virtual destructor.
 */
diff_decoder_qpsk_cc_impl::~diff_decoder_qpsk_cc_impl() {}

unsigned int diff_decoder_qpsk_cc_impl::phase_pos(gr_complex symbol){
    if (symbol.real() > 0 && symbol.imag() > 0) return 0;
    if (symbol.real() < 0 && symbol.imag() > 0) return 1;
    if (symbol.real() < 0 && symbol.imag() < 0) return 2;
    if (symbol.real() > 0 && symbol.imag() < 0) return 3;
    return 0;
}

gr_complex diff_decoder_qpsk_cc_impl::phase_pos2symbol(unsigned int phase_pos){
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


int diff_decoder_qpsk_cc_impl::work(int noutput_items,
                                    gr_vector_const_void_star& input_items,
                                    gr_vector_void_star& output_items)
{
    const gr_complex* in = (const gr_complex*)input_items[0];
    gr_complex* out = (gr_complex*)output_items[0];
    in += 1; // ensure that in[-1] is valid

    for (int i = 0; i < noutput_items; i++) {
            out[i] = phase_pos2symbol((phase_pos(in[i]) - phase_pos(in[i - 1])) % 4);
        }

    return noutput_items;
}

} /* namespace demonstrator */
} /* namespace gr */
