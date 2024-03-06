/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_CONSTELLATION_DECODER_SIC_H
#define INCLUDED_DEMONSTRATOR_CONSTELLATION_DECODER_SIC_H

#include <gnuradio/sync_block.h>
#include <demonstrator/api.h>
#include <gnuradio/digital/constellation.h>


namespace gr {
namespace demonstrator {

/*!
 * \brief <+description of block+>
 * \ingroup demonstrator
 *
 */
class DEMONSTRATOR_API constellation_decoder_sic : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<constellation_decoder_sic> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of
     * demonstrator::constellation_decoder_sic.
     *
     * To avoid accidental use of raw pointers, demonstrator::constellation_decoder_sic's
     * constructor is in a private implementation
     * class. demonstrator::constellation_decoder_sic::make is the public interface for
     * creating new instances.
     */
    static sptr make(digital::constellation_sptr constellation, int n_user, const std::vector<float>& power_allocation_factors);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_CONSTELLATION_DECODER_SIC_H */
