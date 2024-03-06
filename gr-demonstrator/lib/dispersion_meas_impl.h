/* -*- c++ -*- */
/*
 * Copyright 2024 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_DISPERSION_MEAS_IMPL_H
#define INCLUDED_DEMONSTRATOR_DISPERSION_MEAS_IMPL_H

#include <demonstrator/dispersion_meas.h>
#include <gnuradio/digital/constellation.h>
#include <cmath> // Include the cmath library for pow

namespace gr {
namespace demonstrator {

class dispersion_meas_impl : public dispersion_meas
{
private:
    digital::constellation_sptr d_constellation;
    int d_length;
    int d_length_init;
    void dispersion(gr_complex sample);
    int d_counter;
    float d_acum;
    bool d_run;

public:
    dispersion_meas_impl(digital::constellation_sptr constellation,
                         float length,
                         float length_init);
    ~dispersion_meas_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_DISPERSION_MEAS_IMPL_H */
