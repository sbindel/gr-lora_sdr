/* -*- c++ -*- */
/*
 * Copyright 2022 gr-lora_sdr author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LORA_SDR_CRC_VERIF_H
#define INCLUDED_LORA_SDR_CRC_VERIF_H

#include <gnuradio/block.h>
#include <lora_sdr/api.h>

namespace gr {
namespace lora_sdr {

/*!
 * \brief <+description of block+>
 * \ingroup lora_sdr
 *
 */
class LORA_SDR_API crc_verif : virtual public gr::block
{
public:
    typedef std::shared_ptr<crc_verif> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of lora_sdr::crc_verif.
     *
     * To avoid accidental use of raw pointers, lora_sdr::crc_verif's
     * constructor is in a private implementation
     * class. lora_sdr::crc_verif::make is the public interface for
     * creating new instances.
     */
    static sptr make(bool log = false);
};

} // namespace lora_sdr
} // namespace gr

#endif /* INCLUDED_LORA_SDR_CRC_VERIF_H */
