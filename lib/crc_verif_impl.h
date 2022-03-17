/* -*- c++ -*- */
/*
 * Copyright 2022 gr-lora_sdr author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_LORA_SDR_CRC_VERIF_IMPL_H
#define INCLUDED_LORA_SDR_CRC_VERIF_IMPL_H

#include <lora_sdr/crc_verif.h>

namespace gr {
namespace lora_sdr {

class crc_verif_impl : public crc_verif
{
private:
	/**
	 * @brief Payload length in bytes
	 */ 
	uint8_t m_payload_len;

	/**
	 * @brief Indicate if a payload CRC is present
	 */
	bool m_has_crc;

	/**
	 * @brief The CRC computed from the payload
	 */
	uint16_t m_crc;

	/**
	 * @brief payload data
	 */
	std::vector<uint8_t> m_payload;

	/**
	 * \brief  Calculate the CRC 16 using poly=0x1021 and Init=0x0000
	 *
	 * \param unsigned int : the crc 
	 * \param unsigned char : the data byte
	 * \param unsigned int : the crc related to the data byte
	 */
	unsigned int crc16(unsigned int crcValue, unsigned char newByte);

public:
	crc_verif_impl();
    ~crc_verif_impl();

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace lora_sdr
} // namespace gr

#endif /* INCLUDED_LORA_SDR_CRC_VERIF_IMPL_H */
