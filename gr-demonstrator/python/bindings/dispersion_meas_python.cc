/*
 * Copyright 2024 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(dispersion_meas.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(9876a9b6683029e55da3165f6cac47af)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <demonstrator/dispersion_meas.h>
// pydoc.h is automatically generated in the build directory
#include <dispersion_meas_pydoc.h>

void bind_dispersion_meas(py::module& m)
{

    using dispersion_meas    = ::gr::demonstrator::dispersion_meas;


    py::class_<dispersion_meas, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<dispersion_meas>>(m, "dispersion_meas", D(dispersion_meas))

        .def(py::init(&dispersion_meas::make),
           py::arg("constellation"),
           py::arg("length"),
           py::arg("length_init"),
           D(dispersion_meas,make)
        )
        



        ;




}








