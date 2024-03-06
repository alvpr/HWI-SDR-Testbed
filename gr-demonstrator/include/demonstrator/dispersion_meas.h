/* -*- c++ -*- */
/*
 * Copyright 2024 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_DISPERSION_MEAS_H
#define INCLUDED_DEMONSTRATOR_DISPERSION_MEAS_H

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
class DEMONSTRATOR_API dispersion_meas : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<dispersion_meas> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of demonstrator::dispersion_meas.
     *
     * To avoid accidental use of raw pointers, demonstrator::dispersion_meas's
     * constructor is in a private implementation
     * class. demonstrator::dispersion_meas::make is the public interface for
     * creating new instances.
     */
    static sptr
    make(digital::constellation_sptr constellation, float length, float length_init);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_DISPERSION_MEAS_H */
