# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT demonstrator_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT demonstrator_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################
list(APPEND demonstrator_python_files
    constellation_decoder_sic_python.cc
    sequence_detector_bb_python.cc
    header_detector_bb_python.cc
    crc32_check_python.cc
    diff_encoder_qpsk_cc_python.cc
    diff_decoder_qpsk_cc_python.cc
    dispersion_meas_python.cc
    tag_sink_python.cc
    constellation_joint_decoder_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(demonstrator 
   ../..
   gr::demonstrator
   "${demonstrator_python_files}")

install(TARGETS demonstrator_python DESTINATION ${GR_PYTHON_DIR}/demonstrator COMPONENT pythonapi)
