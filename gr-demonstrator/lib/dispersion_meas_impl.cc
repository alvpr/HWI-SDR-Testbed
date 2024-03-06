/* -*- c++ -*- */
/*
 * Copyright 2024 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dispersion_meas_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/digital/constellation.h>
#include <cmath> // Include the cmath library for pow

namespace gr {
namespace demonstrator {

dispersion_meas::sptr dispersion_meas::make(digital::constellation_sptr constellation,
                                            float length,
                                            float length_init)
{
    return gnuradio::make_block_sptr<dispersion_meas_impl>(
        constellation, length, length_init);
}


/*
 * The private constructor
 */
dispersion_meas_impl::dispersion_meas_impl(digital::constellation_sptr constellation,
                                           float length,
                                           float length_init)
    : gr::sync_block("dispersion_meas",
                    gr::io_signature::make(
                         1, 1, sizeof(gr_complex)),
                         gr::io_signature::make(0, 0, 0)),
                        d_constellation(constellation), 
                        d_length(int(length)), 
                        d_length_init(int(length_init)),
                        d_counter(0),
                        d_acum(0),
                        d_run(false)
{
}

/*
 * Our virtual destructor.
 */
dispersion_meas_impl::~dispersion_meas_impl() {}

void dispersion_meas_impl::dispersion(gr_complex sample){
    d_counter++;

    if (!d_run){
        if (d_counter >= d_length_init){
            d_counter = 0;
            d_run = true;
        }
        return;
    }

    gr_complex  received_symbol = sample;
    gr_complex decided_symbol;
    unsigned int closest_point_index;
    float dispersion;
    // Use decision_maker to get the index of the closest point in the constellation
    closest_point_index = d_constellation->decision_maker(&received_symbol);
    // Use map_to_points to get the actual constellation point
    d_constellation->map_to_points(closest_point_index, &decided_symbol);
    // Subtract the ideal symbol from the current symbol for interference cancellation, taking into account the power 
    // allocation factor
    dispersion = pow(received_symbol.real() - decided_symbol.real(), 2) + pow(received_symbol.imag() - decided_symbol.imag(), 2);
    d_acum += dispersion;

    if (d_counter >= d_length){
        d_counter = 0;
        dispersion = d_acum/d_length;
        d_acum = 0;
        std::cout << "Dispersion: " << dispersion << " (" << -10 * log10(dispersion) << ")\n";
    }
}

int dispersion_meas_impl::work(int noutput_items,
                               gr_vector_const_void_star& input_items,
                               gr_vector_void_star& output_items)
{
    const gr_complex* in = (const gr_complex*)input_items[0];

    for (int i; i < noutput_items; i++){
        dispersion(in[i]);
    }

    return noutput_items;
}

} /* namespace demonstrator */
} /* namespace gr */
