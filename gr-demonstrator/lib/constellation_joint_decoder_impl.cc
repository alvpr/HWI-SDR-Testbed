/* -*- c++ -*- */
/*
 * Copyright 2024 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "constellation_joint_decoder_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/digital/constellation.h>
#include <iostream> // Include this at the top of your file

namespace gr {
namespace demonstrator {



constellation_joint_decoder::sptr
constellation_joint_decoder::make(digital::constellation_sptr constj,
                                  digital::constellation_sptr const1,
                                  digital::constellation_sptr const2,
                                  int n_user)
{
    return gnuradio::make_block_sptr<constellation_joint_decoder_impl>(constj, const1, const2, n_user);
}


/*
 * The private constructor
 */
constellation_joint_decoder_impl::constellation_joint_decoder_impl(
    digital::constellation_sptr constj,
    digital::constellation_sptr const1,
    digital::constellation_sptr const2,
    int n_user)
    : gr::sync_block("constellation_joint_decoder",
                     gr::io_signature::make(1 /* min inputs */, 1 /* max inputs */, sizeof(gr_complex)),
                     gr::io_signature::make(1 /* min outputs */, 1 /*max outputs */, sizeof(unsigned char))),
                     d_constj(constj), d_const1(const1), d_const2(const2), d_n_user(n_user)
{
}

/*
 * Our virtual destructor.
 */
constellation_joint_decoder_impl::~constellation_joint_decoder_impl() {}

int constellation_joint_decoder_impl::work(int noutput_items,
                                           gr_vector_const_void_star& input_items,
                                           gr_vector_void_star& output_items)
{
    gr_complex const* in = (const gr_complex*)input_items[0];
    unsigned char* out = (unsigned char*)output_items[0];
    gr_complex current_symbol;
    unsigned int closest_point_index;
    unsigned int final_decision;

    for (int i = 0; i < noutput_items; i++) {
        current_symbol = in[i];
        closest_point_index = d_constj->decision_maker(&current_symbol);
        if(d_n_user == 1){
            final_decision = closest_point_index / 4; // The 4 number should be adjusted
        }
        else{
            final_decision = closest_point_index % 4; // The 4 number should be adjusted
        }
        // Output the decision as a byte
        out[i] = static_cast<unsigned char>(final_decision);
    }
    return noutput_items;
}

} /* namespace demonstrator */
} /* namespace gr */
