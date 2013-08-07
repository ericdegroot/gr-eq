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
      : gr_block("eq_lms_ff",
                 gr_make_io_signature(2, 2, sizeof(float)),
                 gr_make_io_signature(1, 1, sizeof(float))),
        d_filter_size(filter_size), d_step_factor(step_factor), d_filter_taps(filter_size, 0)
    {
    }

    /*
     * Our virtual destructor.
     */
    eq_lms_ff_impl::~eq_lms_ff_impl()
    {
    }

    void
    eq_lms_ff_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    eq_lms_ff_impl::general_work (int noutput_items,
                                  gr_vector_int &ninput_items,
                                  gr_vector_const_void_star &input_items,
                                  gr_vector_void_star &output_items)
    {
      const float *x = (const float *) input_items[0];
      const float *dn = (const float *) input_items[1];
      float *y = (float *) output_items[0];
      
      // Do <+signal processing+>

      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each(noutput_items);
      
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace eq */
} /* namespace gr */

