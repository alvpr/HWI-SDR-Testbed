/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_CRC32_CHECK_H
#define INCLUDED_DEMONSTRATOR_CRC32_CHECK_H

#include <gnuradio/block.h>
#include <demonstrator/api.h>

namespace gr {
namespace demonstrator {

/*!
 * \brief <+description of block+>
 * \ingroup demonstrator
 *
 */
class DEMONSTRATOR_API crc32_check : virtual public gr::block
{
public:
    typedef std::shared_ptr<crc32_check> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of demonstrator::crc32_check.
     *
     * To avoid accidental use of raw pointers, demonstrator::crc32_check's
     * constructor is in a private implementation
     * class. demonstrator::crc32_check::make is the public interface for
     * creating new instances.
     */
    static sptr make(int n_packets, int n_sym, int n_user);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_CRC32_CHECK_H */
