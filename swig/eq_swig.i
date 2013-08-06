/* -*- c++ -*- */

#define EQ_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "eq_swig_doc.i"

%{
#include "eq/eq_lms_ff.h"
%}


%include "eq/eq_lms_ff.h"
GR_SWIG_BLOCK_MAGIC2(eq, eq_lms_ff);
