/* -*- c++ -*- */
/*
 * Copyright 2024 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_TAG_SINK_IMPL_H
#define INCLUDED_DEMONSTRATOR_TAG_SINK_IMPL_H

#include <demonstrator/tag_sink.h>

namespace gr {
namespace demonstrator {

class tag_sink_impl : public tag_sink
{
private:
    std::string d_tag_key;
    std::string d_filename;
    std::ofstream d_file;
    std::vector<gr_complex> d_channel_state;

public:
    tag_sink_impl(const std::string& filename, const std::string& tag_key);
    ~tag_sink_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_TAG_SINK_IMPL_H */
