/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_CONSTELLATION_DECODER_SIC_IMPL_H
#define INCLUDED_DEMONSTRATOR_CONSTELLATION_DECODER_SIC_IMPL_H

#include <demonstrator/constellation_decoder_sic.h>
#include <gnuradio/digital/constellation.h>


namespace gr {
namespace demonstrator {

class constellation_decoder_sic_impl : public constellation_decoder_sic
{
private:
    digital::constellation_sptr d_constellation;
    int d_n_user;
    const std::vector<float> d_power_allocation_factors;


public:
    constellation_decoder_sic_impl(digital::constellation_sptr constellation, int n_user, const std::vector<float>& power_allocation_factors);
    ~constellation_decoder_sic_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_CONSTELLATION_DECODER_SIC_IMPL_H */
