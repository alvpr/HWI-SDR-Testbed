/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <pybind11/pybind11.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

namespace py = pybind11;

// Headers for binding functions
/**************************************/
// The following comment block is used for
// gr_modtool to insert function prototypes
// Please do not delete
/**************************************/
// BINDING_FUNCTION_PROTOTYPES(
    void bind_constellation_decoder_sic(py::module& m);
    void bind_sequence_detector_bb(py::module& m);
    void bind_header_detector_bb(py::module& m);
    void bind_crc32_check(py::module& m);
    void bind_diff_encoder_qpsk_cc(py::module& m);
    void bind_diff_decoder_qpsk_cc(py::module& m);
    void bind_dispersion_meas(py::module& m);
    void bind_tag_sink(py::module& m);
    void bind_constellation_joint_decoder(py::module& m);
// ) END BINDING_FUNCTION_PROTOTYPES


// We need this hack because import_array() returns NULL
// for newer Python versions.
// This function is also necessary because it ensures access to the C API
// and removes a warning.
void* init_numpy()
{
    import_array();
    return NULL;
}

PYBIND11_MODULE(demonstrator_python, m)
{
    // Initialize the numpy C API
    // (otherwise we will see segmentation faults)
    init_numpy();

    // Allow access to base block methods
    py::module::import("gnuradio.gr");

    /**************************************/
    // The following comment block is used for
    // gr_modtool to insert binding function calls
    // Please do not delete
    /**************************************/
    // BINDING_FUNCTION_CALLS(
    bind_constellation_decoder_sic(m);
    bind_sequence_detector_bb(m);
    bind_header_detector_bb(m);
    bind_crc32_check(m);
    bind_diff_encoder_qpsk_cc(m);
    bind_diff_decoder_qpsk_cc(m);
    bind_dispersion_meas(m);
    bind_tag_sink(m);
    bind_constellation_joint_decoder(m);
    // ) END BINDING_FUNCTION_CALLS
}