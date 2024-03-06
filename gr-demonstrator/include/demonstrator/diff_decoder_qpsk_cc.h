/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_DIFF_DECODER_QPSK_CC_H
#define INCLUDED_DEMONSTRATOR_DIFF_DECODER_QPSK_CC_H

#include <gnuradio/sync_block.h>
#include <demonstrator/api.h>

namespace gr {
namespace demonstrator {

/*!
 * \brief <+description of block+>
 * \ingroup demonstrator
 *
 */
class DEMONSTRATOR_API diff_decoder_qpsk_cc : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<diff_decoder_qpsk_cc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of demonstrator::diff_decoder_qpsk_cc.
     *
     * To avoid accidental use of raw pointers, demonstrator::diff_decoder_qpsk_cc's
     * constructor is in a private implementation
     * class. demonstrator::diff_decoder_qpsk_cc::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_DIFF_DECODER_QPSK_CC_H */
