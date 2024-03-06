/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_HEADER_DETECTOR_BB_H
#define INCLUDED_DEMONSTRATOR_HEADER_DETECTOR_BB_H

#include <gnuradio/block.h>
#include <demonstrator/api.h>

namespace gr {
namespace demonstrator {

/*!
 * \brief <+description of block+>
 * \ingroup demonstrator
 *
 */
class DEMONSTRATOR_API header_detector_bb : virtual public gr::block
{
public:
    typedef std::shared_ptr<header_detector_bb> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of demonstrator::header_detector_bb.
     *
     * To avoid accidental use of raw pointers, demonstrator::header_detector_bb's
     * constructor is in a private implementation
     * class. demonstrator::header_detector_bb::make is the public interface for
     * creating new instances.
     */
    static sptr make(int n_payload_bytes);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_HEADER_DETECTOR_BB_H */
