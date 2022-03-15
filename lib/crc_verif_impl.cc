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

	crc_verif::sptr crc_verif::make() { return gnuradio::make_block_sptr<crc_verif_impl>(); }

	crc_verif_impl::crc_verif_impl()
		: gr::block("crc_verif",
					gr::io_signature::make(1,1, sizeof(uint8_t)),
					gr::io_signature::make(1, 1, sizeof(uint8_t)))
	{
		set_tag_propagation_policy(TPP_DONT);
	}


	crc_verif_impl::~crc_verif_impl() {}

	void crc_verif_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
	{
		ninput_items_required[0] = 1;
	}

	unsigned int crc_verif_impl::crc16(const uint8_t* data, uint32_t len)
	{
		uint16_t crc = 0x0000;
		for (unsigned int i = 0; i < len; i++) {
			uint8_t newByte = data[i];
			for (unsigned char i = 0; i < 8; i++)
			{
				if (((crc & 0x8000) >> 8) ^ (newByte & 0x80))
				{
					crc = (crc << 1) ^ 0x1021;
				} else
				{
					crc = (crc << 1);
				}
				newByte <<= 1;
			}
		}
		return crc;
	}
	
	int crc_verif_impl::general_work(int noutput_items,
									 gr_vector_int& ninput_items,
									 gr_vector_const_void_star& input_items,
									 gr_vector_void_star& output_items)
	{
		const uint8_t *in = (const uint8_t *)input_items[0];
		uint8_t *out = (uint8_t *)output_items[0];
		int nitems_to_process = ninput_items[0];
		int return_item=0;

		// extract tag data 
		std::vector<tag_t> tags;
		get_tags_in_window(tags, 0, 0, noutput_items, pmt::string_to_symbol("frame_info"));
		if (tags.size())
		{
			if (tags[0].offset != nitems_read(0))
			{
				nitems_to_process = tags[0].offset - nitems_read(0);
			}
			else
			{
				if (tags.size() >= 2)
				{
					nitems_to_process = tags[1].offset - tags[0].offset;
				}
				pmt::pmt_t err = pmt::string_to_symbol("error");
				m_has_crc = pmt::to_long(pmt::dict_ref(tags[0].value, pmt::string_to_symbol("crc"), err));
				m_payload_len = pmt::to_long(pmt::dict_ref(tags[0].value, pmt::string_to_symbol("pay_len"), err));
				//tags[0].offset = nitems_written(0);
				//add_item_tag(0, tags[0]);
				//add_item_tag(0, nitems_written(0), pmt::string_to_symbol("data_info"), pmt::from_long(m_payload_len));

//std::cout<<"numboer of items to process"<<nitems_to_process<<std::endl;
				//std::cout<<"data +  :crc "<<tags[0].offset<<" - crc:"<<(int)m_has_crc<<" - pay_len: "<<(int)m_payload_len<<"\n";
			}
		}
		
		//std::cout<<ninput_items[0]<<std::endl;
		// extract data + crc
		if ((ninput_items[0] >= (int)m_payload_len + 2) && m_has_crc)
		{
			if (m_payload_len < 2)
			{
				std::cout << "CRC not supported for payload smaller than 2 bytes"<< std::endl;
			}
			else
			{
				// crc part
				m_crc = crc16(&in[0], m_payload_len - 2); // compute the CRC on the N-2 firsts data bytes
				m_crc = m_crc ^ in[m_payload_len - 1] ^ (in[m_payload_len - 2] << 8); //  // XOR the obtained CRC with the last 2 data bytes

				// payload part
				m_payload.clear();
				for (int i = 0; i < (int)m_payload_len; i++) {
					m_payload.push_back((char)in[i]);
					if (output_items.size())
						out[i] = in[i];
				}
				consume_each(m_payload_len+2);
				return_item = m_payload_len;
			}
		}
		// extract only data (without crc)
		else if ((ninput_items[0] >= (int)m_payload_len) && !m_has_crc)
		{
			m_payload.clear();
			for (int i = 0; i < m_payload_len; i++)
			{
				m_payload.push_back((char)in[i]);
				if (output_items.size())
					out[i] = in[i];
			}
			consume_each(m_payload_len);
			return_item = m_payload_len;
		}
		return return_item;
	}

} /* namespace lora_sdr */
} /* namespace gr */
