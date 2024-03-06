/* -*- c++ -*- */
/*
 * Copyright 2024 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_CONSTELLATION_JOINT_DECODER_H
#define INCLUDED_DEMONSTRATOR_CONSTELLATION_JOINT_DECODER_H

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
class DEMONSTRATOR_API constellation_joint_decoder : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<constellation_joint_decoder> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of
     * demonstrator::constellation_joint_decoder.
     *
     * To avoid accidental use of raw pointers,
     * demonstrator::constellation_joint_decoder's constructor is in a private
     * implementation class. demonstrator::constellation_joint_decoder::make is the public
     * interface for creating new instances.
     */
    static sptr make(digital::constellation_sptr constj,
                     digital::constellation_sptr const1,
                     digital::constellation_sptr const2,
                     int n_user);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_CONSTELLATION_JOINT_DECODER_H */
