/* -*- c++ -*- */
/*
 * Copyright 2022 gr-lora_sdr author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "crc_verif_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace lora_sdr {

#pragma message("set the following appropriately and remove this warning")
using input_type = uint8_t;
#pragma message("set the following appropriately and remove this warning")
using output_type = uint8_t;
crc_verif::sptr crc_verif::make() { return gnuradio::make_block_sptr<crc_verif_impl>(); }


/*
 * The private constructor
 */
crc_verif_impl::crc_verif_impl()
    : gr::block("crc_verif",
                gr::io_signature::make(
                    1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                gr::io_signature::make(
                    1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
}

/*
 * Our virtual destructor.
 */
crc_verif_impl::~crc_verif_impl() {}

void crc_verif_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
#pragma message( \
    "implement a forecast that fills in how many items on each input you need to produce noutput_items and remove this warning")
    /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
}

int crc_verif_impl::general_work(int noutput_items,
                                 gr_vector_int& ninput_items,
                                 gr_vector_const_void_star& input_items,
                                 gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

#pragma message("Implement the signal processing in your block and remove this warning")
    // Do <+signal processing+>
    // Tell runtime system how many input items we consumed on
    // each input stream.
    consume_each(noutput_items);

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace lora_sdr */
} /* namespace gr */
