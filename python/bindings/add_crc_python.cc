/*
 * Copyright 2022 Free Software Foundation, Inc.
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
/* BINDTOOL_HEADER_FILE(add_crc.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(eb6adf44d2a8dcd81b8e3489fdf25d0e)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <lora_sdr/add_crc.h>
// pydoc.h is automatically generated in the build directory
#include <add_crc_pydoc.h>

void bind_add_crc(py::module& m)
{

    using add_crc    = ::gr::lora_sdr::add_crc;


    py::class_<add_crc, gr::block, gr::basic_block,
        std::shared_ptr<add_crc>>(m, "add_crc", D(add_crc))

        .def(py::init(&add_crc::make),
           py::arg("has_crc"),
           D(add_crc,make)
        )
        



        ;




}








