/* -*- c++ -*- */
/*
 * Copyright 2006,2009,2013 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <gnuradio/constants.h>
#include <stdlib.h>
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/filesystem/path.hpp>

namespace gr {

const std::string prefix()
{
    // Use "GR_PREFIX" environment variable when specified
    const char* prefix = getenv("GR_PREFIX");
    if (prefix != NULL)
        return prefix;

    boost::filesystem::path prefix_rel_lib = "../";
    boost::filesystem::path gr_runtime_lib_path = boost::dll::this_line_location();
    // Normalize before decomposing path so result is reliable
    boost::filesystem::path prefix_path =
        gr_runtime_lib_path.lexically_normal().parent_path() / prefix_rel_lib;
    return prefix_path.lexically_normal().string();
}

const std::string sysconfdir()
{
    boost::filesystem::path sysconfdir_rel_prefix = "etc";
    boost::filesystem::path prefix_path = prefix();
    boost::filesystem::path sysconfdir_path = prefix_path / sysconfdir_rel_prefix;

    return sysconfdir_path.lexically_normal().string();
}

const std::string prefsdir()
{
    boost::filesystem::path prefsdir_rel_prefix = "etc/gnuradio/conf.d";
    boost::filesystem::path prefix_path = prefix();
    boost::filesystem::path prefsdir_path = prefix_path / prefsdir_rel_prefix;

    return prefsdir_path.lexically_normal().string();
}

const std::string build_date() { return "Fri, 10 Nov 2023 17:23:55"; }

const std::string version() { return "3.9.0.0"; }

// Return individual parts of the version
const std::string major_version() { return "3"; }

const std::string api_version() { return "9"; }

const std::string minor_version() { return "0"; }

const std::string c_compiler() { return "cc (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0 \nCopyright (C) 2019 Free Software Foundation, Inc. \nThis is free software see the source for copying conditions.  There is NO \nwarranty not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."; }

const std::string cxx_compiler() { return "c++ (Ubuntu 9.4.0-1ubuntu1~20.04.2) 9.4.0 \nCopyright (C) 2019 Free Software Foundation, Inc. \nThis is free software see the source for copying conditions.  There is NO \nwarranty not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."; }

const std::string compiler_flags() { return "/usr/bin/cc:::-O3 -DNDEBUG  -fvisibility=hidden -Wsign-compare -Wall -Wno-uninitialized \n/usr/bin/c++:::-O3 -DNDEBUG  -fvisibility=hidden -Wsign-compare -Wall -Wno-uninitialized"; }

const std::string build_time_enabled_components() { return "testing-support;python-support;post-install;doxygen;gnuradio-runtime;gr-ctrlport"; }
} /* namespace gr */
