#!/usr/bin/env python
# 
# Copyright 2013 <+YOU OR YOUR COMPANY+>.
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
import eq_swig as eq

# ctest -VV -R qa_eq_lms_ff
class qa_eq_lms_ff (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    # n = 0:1:20;
    # s = sin(0.1 * %pi * n);
    # v = rand(n, "normal") * 0.1;
    # x = s + v;
    # plot(n, x, n, s, n, v);
    #
    # function[w,y,e,J]=aalms(x,dn,mu,M)
    #   N=length(x);
    #   y=zeros(1,N);
    #   w=zeros(1,M);
    #   for n=M:N
    #     x1=x(n:-1:n-M+1);
    #     y(n)=w*x1';
    #     e(n)=dn(n)-y(n);
    #     w=w+2*mu*e(n)*x1;
    #   end;
    #   J=e.^2;
    # endfunction
    #
    # M = 4
    # mu = 0.02
    # [w,y,e,J] = aalms(s,x,mu,M)
    def test_001_t (self):
        M = 4
        mu = 0.02
        s = [ 0.0, 0.3090170, 0.5877853, 0.8090170, 0.9510565, 1.0, 0.9510565, 0.8090170, 0.5877853,
              0.3090170, 1.225E-16, -0.3090170, -0.5877853, -0.8090170, -0.9510565, -1.0, -0.9510565,
              -0.8090170, -0.5877853, -0.3090170, -2.449E-16 ]
        x = [ 0.1869771, 0.3164567, 0.5817531, 0.7321207, 0.9280425, 0.9442921, 0.7227481, 0.7236329,
              0.4502919, 0.4182683, 0.1211515, -0.3072967, -0.6598651, -0.5849396, -0.8081715, -1.0660516,
              -0.9508943, -0.7868964, -0.4899220, -0.3765086, 0.0794150 ]
        y_expected = [ 0.0, 0.0, 0.0030070, 0.0198613, 0.0684855, 0.1548310, 0.2389200, 0.3069399, 0.3028421,
              0.2665137, 0.1899010, 0.0551109, -0.0944788, -0.2088661, -0.3248339, -0.4673856, -0.5688788,
              -0.6141125, -0.5422770, -0.4194642, -0.2149493 ]

        x_src = gr.vector_source_f(x, False)
        s_src = gr.vector_source_f(s, False)
        eq_lms = eq.eq_lms_ff(M, mu, False)
        dst = gr.vector_sink_f()

        self.tb.connect((x_src, 0), (eq_lms, 0))
        self.tb.connect((s_src, 0), (eq_lms, 1))
        self.tb.connect((eq_lms, 0), (dst, 0))

        self.tb.run ()

        y = dst.data()

        self.assertFloatTuplesAlmostEqual(y_expected, y, 6)


if __name__ == '__main__':
    gr_unittest.run(qa_eq_lms_ff, "qa_eq_lms_ff.xml")
