/* -*- c++ -*- */
/*
 * Copyright 2022 gr-lora_sdr author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LORA_SDR_MU_DEMOD_H
#define INCLUDED_LORA_SDR_MU_DEMOD_H

#include <gnuradio/block.h>
#include <lora_sdr/api.h>

namespace gr {
namespace lora_sdr {

/*!
 * \brief <+description of block+>
 * \ingroup lora_sdr
 *
 */
class LORA_SDR_API mu_demod : virtual public gr::block
{
public:
    typedef std::shared_ptr<mu_demod> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of lora_sdr::mu_demod.
     *
     * To avoid accidental use of raw pointers, lora_sdr::mu_demod's
     * constructor is in a private implementation
     * class. lora_sdr::mu_demod::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace lora_sdr
} // namespace gr

#endif /* INCLUDED_LORA_SDR_MU_DEMOD_H */
