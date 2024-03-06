/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_CRC32_CHECK_IMPL_H
#define INCLUDED_DEMONSTRATOR_CRC32_CHECK_IMPL_H

#include <demonstrator/crc32_check.h>
#include <boost/crc.hpp>

namespace gr {
namespace demonstrator {

class crc32_check_impl : public crc32_check
{
private:
    boost::crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true> d_crc_impl;

    pmt::pmt_t d_in_port;
    pmt::pmt_t d_out_port;

    void check(pmt::pmt_t msg);

    int d_npass;
    int d_ntotal;
    int d_npackets;
    int d_nuser;
    int d_nsym;

public:
    crc32_check_impl(int n_packets, int n_sym, int n_user);
    ~crc32_check_impl();


    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_CRC32_CHECK_IMPL_H */
