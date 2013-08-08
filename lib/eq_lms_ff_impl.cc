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
    eq_lms_ff::make(unsigned int filter_size, float step_factor)
    {
      return gnuradio::get_initial_sptr
        (new eq_lms_ff_impl(filter_size, step_factor));
    }

    /*
     * The private constructor
     */
    eq_lms_ff_impl::eq_lms_ff_impl(unsigned int filter_size, float step_factor)
      : gr_sync_block("eq_lms_ff",
                      gr_make_io_signature(2, 2, sizeof(float)),
                      gr_make_io_signature(1, 2, sizeof(float))),
        d_filter_size(filter_size), d_step_factor(step_factor), d_filter_taps(filter_size, 0)
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
      //float *e = (float *) output_items[1];

      // fprintf(stderr, "work: noutput_items=%d, d_filter_size=%d, d_step_factor=%f\n", noutput_items, d_filter_size, d_step_factor);
      // fprintf(stderr, "x[0]=%f, x[d_filter_size-1]=%f, x[noutput_items-1]=%f, x[(d_filter_size-1)+noutput_items-1]=%f\n", x[0], x[d_filter_size-1], x[noutput_items - 1], x[(d_filter_size - 1) + noutput_items - 1]);

      for (int i = 0; i < noutput_items; i++) {
        /*
        for (int j = 0; j < d_filter_size; j++) {
          fprintf(stderr, "\t%f", d_filter_taps[j]);
        }
        fprintf(stderr, "\n");

        for (int j = 0; j < d_filter_size; j++) {
          fprintf(stderr, "\t%f", x[d_filter_size - (j + 1) + i]);
        }
        fprintf(stderr, "\n");
        */

        y[i] = 0;
        for (int j = 0; j < d_filter_size; j++) {
          // fprintf(stderr, "\ti=%d, j=%d, d_filter_taps[j]=%f, x[%d]=%f\n", i, j, d_filter_taps[j], d_filter_size-(j+1)+i, x[d_filter_size - (j + 1) + i]);
          y[i] += d_filter_taps[j] * x[d_filter_size - (j + 1) + i];
        }

        // e[i] = dn[i + (d_filter_size - 1)] - y[i];
        float e = dn[i + (d_filter_size - 1)] - y[i];
        // fprintf(stderr, "n=%d, dn(n)=%f, y(n)=%f, e(n)=%f\n", i, dn[i + (d_filter_size - 1)], y[i], e);

        for (int j = 0; j < d_filter_size; j++) {
          // fprintf(stderr, "\tj=%d, d_filter_taps[j]=%f\n", j, d_filter_taps[j]);
          d_filter_taps[j] += 2 * d_step_factor * e * x[d_filter_size - (j + 1) + i];
        }

        // fprintf(stdout, "WORK: %f, %f, %f, %f, %f, %f\n", y[i], d_filter_taps[0], d_filter_taps[1], d_filter_taps[2], d_filter_taps[3]);

        add_item_tag(0, nitems_written(0) + i, pmt::pmt_string_to_symbol("eq_lms_filter_taps"),
                     pmt::pmt_init_f32vector(d_filter_size, d_filter_taps));
      }

      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace eq */
} /* namespace gr */

