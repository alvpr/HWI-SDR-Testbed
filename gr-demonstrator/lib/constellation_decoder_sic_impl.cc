/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "constellation_decoder_sic_impl.h"
#include <gnuradio/io_signature.h>
#include <gnuradio/digital/constellation.h>
#include <iostream> // Include this at the top of your file


namespace gr {
namespace demonstrator {


constellation_decoder_sic::sptr
constellation_decoder_sic::make(digital::constellation_sptr constellation, int n_user, const std::vector<float>& power_allocation_factors)
{
    return gnuradio::make_block_sptr<constellation_decoder_sic_impl>(constellation, n_user, power_allocation_factors);
}


/*
 * The private constructor
 */
constellation_decoder_sic_impl::constellation_decoder_sic_impl(
    digital::constellation_sptr constellation, int n_user, const std::vector<float>& power_allocation_factors)
    : gr::sync_block("constellation_decoder_sic",
                     gr::io_signature::make(1 /* min inputs */, 1 /* max inputs */, sizeof(gr_complex)),
                     gr::io_signature::make(1 /* min outputs */, 1 /*max outputs */, sizeof(unsigned char))),
                     d_constellation(constellation), d_n_user(n_user), d_power_allocation_factors(power_allocation_factors)
{
}

/*
 * Our virtual destructor.
 */
constellation_decoder_sic_impl::~constellation_decoder_sic_impl() {}

int constellation_decoder_sic_impl::work(int noutput_items,
                                         gr_vector_const_void_star& input_items,
                                         gr_vector_void_star& output_items)
{
    gr_complex const* in = (const gr_complex*)input_items[0];
    unsigned char* out = (unsigned char*)output_items[0];
    int counter_sic; //Counter for times SIC must be perfomed
    gr_complex current_symbol;
    unsigned int closest_point_index;
    gr_complex ideal_symbol;

    for (int i = 0; i < noutput_items; i++) {
        current_symbol = in[i];
        for (int sic_iteration = 0; sic_iteration < d_n_user; sic_iteration++) {
            // Use decision_maker to get the index of the closest point in the constellation
            closest_point_index = d_constellation->decision_maker(&current_symbol);

            // Use map_to_points to get the actual constellation point
            d_constellation->map_to_points(closest_point_index, &ideal_symbol);

            // Subtract the ideal symbol from the current symbol for interference cancellation, taking into account the power 
            // allocation factor
            current_symbol -= ideal_symbol * d_power_allocation_factors[sic_iteration];
        }

        // After all SIC iterations, decide on the final symbol
        unsigned int final_decision = d_constellation->decision_maker(&current_symbol);

        // Output the decision as a byte
        out[i] = static_cast<unsigned char>(final_decision);
    }

    return noutput_items;
}

} /* namespace demonstrator */
} /* namespace gr */
