/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

// #include <cstdio>

#include <gr_io_signature.h>
#include "eq_lms_ff_impl.h"

namespace gr {
  namespace eq {

    eq_lms_ff::sptr
    eq_lms_ff::make(unsigned int filter_size, float step_factor, bool filter_taps_tagging)
    {
      return gnuradio::get_initial_sptr
        (new eq_lms_ff_impl(filter_size, step_factor, filter_taps_tagging));
    }

    /*
     * The private constructor
     */
    eq_lms_ff_impl::eq_lms_ff_impl(unsigned int filter_size, float step_factor, bool filter_taps_tagging)
      : gr_sync_block("eq_lms_ff",
                      gr_make_io_signature(2, 2, sizeof(float)),
                      gr_make_io_signature(1, 2, sizeof(float))),
        d_filter_size(filter_size), d_step_factor(step_factor), d_filter_taps(filter_size, 0),
        d_filter_taps_tagging(filter_taps_tagging)
    {
      set_history(filter_size);
    }

    /*
     * Our virtual destructor.
     */
    eq_lms_ff_impl::~eq_lms_ff_impl()
    {
    }

    int
    eq_lms_ff_impl::work(int noutput_items,
                         gr_vector_const_void_star &input_items,
                         gr_vector_void_star &output_items)
    {
      const float *x = (const float *) input_items[0];
      const float *dn = (const float *) input_items[1];
      float *y = (float *) output_items[0];
      float *e;

      // Check if 2nd optional output is connected
      if (output_items.size() > 1)
        e = (float *) output_items[1];
      else
        e = new float[noutput_items];

      for (int i = 0; i < noutput_items; i++) {
        y[i] = 0;
        for (int j = 0; j < d_filter_size; j++) {
          y[i] += d_filter_taps[j] * x[d_filter_size - (j + 1) + i];
        }

        e[i] = dn[i + (d_filter_size - 1)] - y[i];

        for (int j = 0; j < d_filter_size; j++) {
          d_filter_taps[j] += 2 * d_step_factor * e[i] * x[d_filter_size - (j + 1) + i];
        }

        if (d_filter_taps_tagging) {
          add_item_tag(0, nitems_written(0) + i, pmt::pmt_string_to_symbol(FILTER_TAPS_TAG_NAME),
                       pmt::pmt_init_f32vector(d_filter_size, d_filter_taps));
        }
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace eq */
} /* namespace gr */

