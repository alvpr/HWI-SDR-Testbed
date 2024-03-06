/* -*- c++ -*- */
/*
 * Copyright 2023 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "crc32_check_impl.h"
#include <gnuradio/io_signature.h>
#include <cmath> // Include the cmath library for sqrt

namespace gr {
namespace demonstrator {


crc32_check::sptr crc32_check::make(int n_packets, int n_sym, int n_user)
{
    return gnuradio::make_block_sptr<crc32_check_impl>(n_packets, n_sym, n_user);
}


/*
 * The private constructor
 */
crc32_check_impl::crc32_check_impl(int n_packets, int n_sym, int n_user)
    : gr::block("crc32_check", io_signature::make(0, 0, 0), io_signature::make(0, 0, 0)),
    d_npass(0),
    d_ntotal(0),
    d_npackets(n_packets),
    d_nuser(n_user),
    d_nsym(n_sym)
{
    d_in_port = pmt::mp("in");
    d_out_port = pmt::mp("out");

    message_port_register_in(d_in_port);
    message_port_register_out(d_out_port);
    set_msg_handler(d_in_port, [this](pmt::pmt_t msg) { this->check(msg); });
}

/*
 * Our virtual destructor.
 */
crc32_check_impl::~crc32_check_impl() {}

void crc32_check_impl::check(pmt::pmt_t msg)
{
    // extract input pdu
    pmt::pmt_t meta(pmt::car(msg));
    pmt::pmt_t bytes(pmt::cdr(msg));

    unsigned int crc;
    size_t pkt_len(0);
    const uint8_t* bytes_in = pmt::u8vector_elements(bytes, pkt_len);

    d_crc_impl.reset();
    d_crc_impl.process_bytes(bytes_in, pkt_len - 4);
    crc = d_crc_impl();
    d_ntotal++;
    float ser = 0;
    float p_packet = 0;

    if (crc == *(unsigned int*)(bytes_in + pkt_len - 4)) { 
        d_npass++;
        pmt::pmt_t output = pmt::init_u8vector(pkt_len - 4, bytes_in);
        pmt::pmt_t msg_pair = pmt::cons(meta, output);
        message_port_pub(d_out_port, msg_pair);
    }

    if(d_ntotal >= d_npackets){
        p_packet =  static_cast<float> (d_npass) / d_ntotal;
        ser = log10(1 - pow(10, log10(p_packet) / d_nsym));
        std::cout << "Rate User " << d_nuser << ": " << d_npass << "/" << d_ntotal << " (" << ser  << ")" << "\n";
        d_npass = 0;
        d_ntotal = 0;
    }
    
}


int crc32_check_impl::general_work(int noutput_items,
                                   gr_vector_int& ninput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    return noutput_items;
}
} /* namespace demonstrator */
} /* namespace gr */
