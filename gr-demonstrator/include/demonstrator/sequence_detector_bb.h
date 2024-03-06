/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_SEQUENCE_DETECTOR_BB_H
#define INCLUDED_DEMONSTRATOR_SEQUENCE_DETECTOR_BB_H

#include <gnuradio/sync_block.h>
#include <demonstrator/api.h>
//#include <gnuradio/pmt/pmt.h>

namespace gr {
namespace demonstrator {

/*!
 * \brief <+description of block+>
 * \ingroup demonstrator
 *
 */
class DEMONSTRATOR_API sequence_detector_bb : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<sequence_detector_bb> sptr;

    static sptr make();
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_SEQUENCE_DETECTOR_BB_H */
