/* -*- c++ -*- */
/*
 * Copyright 2024 gr-demonstrator author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_DEMONSTRATOR_TAG_SINK_H
#define INCLUDED_DEMONSTRATOR_TAG_SINK_H

#include <gnuradio/sync_block.h>
#include <demonstrator/api.h>

namespace gr {
namespace demonstrator {

/*!
 * \brief <+description of block+>
 * \ingroup demonstrator
 *
 */
class DEMONSTRATOR_API tag_sink : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<tag_sink> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of demonstrator::tag_sink.
     *
     * To avoid accidental use of raw pointers, demonstrator::tag_sink's
     * constructor is in a private implementation
     * class. demonstrator::tag_sink::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& filename, const std::string& tag_key);
};

} // namespace demonstrator
} // namespace gr

#endif /* INCLUDED_DEMONSTRATOR_TAG_SINK_H */
