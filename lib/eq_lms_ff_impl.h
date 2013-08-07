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

#ifndef INCLUDED_EQ_EQ_LMS_FF_IMPL_H
#define INCLUDED_EQ_EQ_LMS_FF_IMPL_H

#include <eq/eq_lms_ff.h>

namespace gr {
  namespace eq {

    class eq_lms_ff_impl : public eq_lms_ff
    {
    private:
      unsigned int d_filter_size;
      float d_step_factor;
      std::vector<float> d_filter_taps;

    public:
      eq_lms_ff_impl(unsigned int filter_size, float step_factor);
      ~eq_lms_ff_impl();

      int work(int noutput_items,
               gr_vector_const_void_star &input_items,
               gr_vector_void_star &output_items);
    };

  } // namespace eq
} // namespace gr

#endif /* INCLUDED_EQ_EQ_LMS_FF_IMPL_H */

