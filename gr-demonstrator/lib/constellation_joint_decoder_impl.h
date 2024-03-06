/* -*- c++ -*- */
/*
 * Copyright 2024 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_CONSTELLATION_JOINT_DECODER_IMPL_H
#define INCLUDED_DEMONSTRATOR_CONSTELLATION_JOINT_DECODER_IMPL_H

#include <demonstrator/constellation_joint_decoder.h>
#include <gnuradio/digital/constellation.h>

namespace gr {
namespace demonstrator {

class constellation_joint_decoder_impl : public constellation_joint_decoder
{
private:
    digital::constellation_sptr d_constj;
    digital::constellation_sptr d_const1;
    digital::constellation_sptr d_const2;
    int d_n_user;

public:
    constellation_joint_decoder_impl(digital::constellation_sptr constj,
                                     digital::constellation_sptr const1,
                                     digital::constellation_sptr const2,
                                     int n_user);
    ~constellation_joint_decoder_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_CONSTELLATION_JOINT_DECODER_IMPL_H */
