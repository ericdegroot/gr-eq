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


#ifndef INCLUDED_EQ_EQ_LMS_FF_H
#define INCLUDED_EQ_EQ_LMS_FF_H

#include <eq/api.h>
#include <gr_sync_block.h>

namespace gr {
  namespace eq {

    static const std::string FILTER_TAPS_TAG_NAME = "eq_lms_filter_taps";

    /*!
     * \brief <+description of block+>
     * \ingroup eq
     *
     */
    class EQ_API eq_lms_ff : virtual public gr_sync_block
    {
     public:
      typedef boost::shared_ptr<eq_lms_ff> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of eq::eq_lms_ff.
       *
       * To avoid accidental use of raw pointers, eq::eq_lms_ff's
       * constructor is in a private implementation
       * class. eq::eq_lms_ff::make is the public interface for
       * creating new instances.
       */
      static sptr make(unsigned int filter_size, float step_factor, bool filter_taps_tagging);
    };

  } // namespace eq
} // namespace gr

#endif /* INCLUDED_EQ_EQ_LMS_FF_H */

