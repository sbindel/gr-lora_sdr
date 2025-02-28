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
/* BINDTOOL_HEADER_FILE(gray_enc.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(ba65851bfecff27219a935f2ed4bb1bc)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <lora_sdr/gray_enc.h>
// pydoc.h is automatically generated in the build directory
#include <gray_enc_pydoc.h>

void bind_gray_enc(py::module& m)
{

    using gray_enc    = ::gr::lora_sdr::gray_enc;


    py::class_<gray_enc, gr::sync_block, gr::block, gr::basic_block,
        std::shared_ptr<gray_enc>>(m, "gray_enc", D(gray_enc))

        .def(py::init(&gray_enc::make),
           D(gray_enc,make)
        )
        



        ;




}








