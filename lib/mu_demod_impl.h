/* -*- c++ -*- */
/*
 * Copyright 2022 gr-lora_sdr author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LORA_SDR_MU_DEMOD_IMPL_H
#define INCLUDED_LORA_SDR_MU_DEMOD_IMPL_H

#include <lora_sdr/mu_demod.h>

namespace gr {
namespace lora_sdr {

class mu_demod_impl : public mu_demod
{
private:
    // Nothing to declare in this block.

public:
    mu_demod_impl();
    ~mu_demod_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace lora_sdr
} // namespace gr

#endif /* INCLUDED_LORA_SDR_MU_DEMOD_IMPL_H */
