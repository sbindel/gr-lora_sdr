/* -*- c++ -*- */
/*
 * Copyright 2022 seb.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LORA_SDR_ADD_CRC_H
#define INCLUDED_LORA_SDR_ADD_CRC_H

#include <gnuradio/block.h>
#include <lora_sdr/api.h>

namespace gr {
namespace lora_sdr {

/*!
 * \brief <+description of block+>
 * \ingroup lora_sdr
 *
 */
class LORA_SDR_API add_crc : virtual public gr::block
{
public:
    typedef std::shared_ptr<add_crc> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of lora_sdr::add_crc.
     *
     * To avoid accidental use of raw pointers, lora_sdr::add_crc's
     * constructor is in a private implementation
     * class. lora_sdr::add_crc::make is the public interface for
     * creating new instances.
     */
    static sptr make(bool has_crc);
};

} // namespace lora_sdr
} // namespace gr

#endif /* INCLUDED_LORA_SDR_ADD_CRC_H */
