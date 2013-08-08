#include <cstdio>

#include <gr_top_block.h>
#include <gr_core_api.h>
#include <gr_sync_block.h>
#include <gr_io_signature.h>
#include <gr_add_ff.h>

#include <analog/sig_source_f.h>
#include <analog/noise_source_f.h>

#include <eq/eq_lms_ff.h>

////////////////////////////////////////////////////////////////////////////////

class eq_lms_dump_sink;
typedef boost::shared_ptr<eq_lms_dump_sink> eq_lms_dump_sink_sptr;

class GR_CORE_API eq_lms_dump_sink : public gr_sync_block
{
private:
  eq_lms_dump_sink():
    gr_sync_block("eq_lms_dump_sink",
		  gr_make_io_signature(1, 2, sizeof(float)),
		  gr_make_io_signature(0, 0, 0))
  {
    /* NOP */
  }

  int work(int noutput_items, gr_vector_const_void_star &input_items,
	   gr_vector_void_star &output_items)
  {
    const float *y = (const float *) input_items[0];
    // const float *e = (const float *) input_items[1];

    std::vector<gr_tag_t> tags;
    get_tags_in_range(tags, 0, nitems_read(0), nitems_read(0) + noutput_items);

    for (int i = 0; i < noutput_items; i++) {
      std::string key = pmt::pmt_symbol_to_string(tags[i].key);
      if (key == gr::eq::FILTER_TAPS_TAG_NAME) {
        std::vector<float> filter_taps = pmt::pmt_f32vector_elements(tags[i].value);

        // fprintf(stderr, "%s, %c, %d, [ %f, %f, %f, %f ]\n", key.c_str(), pmt::pmt_is_f32vector(tags[i].value) ? 'T' : 'F', filter_taps.size(), filter_taps[0], filter_taps[1], filter_taps[2], filter_taps[3]);

        fprintf(stdout, "%f, %f, %f, %f, %f\n", y[i], filter_taps[0], filter_taps[1], filter_taps[2], filter_taps[3]);
      }
    }

    return noutput_items;
  }

  friend eq_lms_dump_sink_sptr make_eq_lms_dump_sink();
};

eq_lms_dump_sink_sptr make_eq_lms_dump_sink()
{
  return gnuradio::get_initial_sptr(new eq_lms_dump_sink());
}

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  double samp_rate = 1000;
  double freq = 10;

  unsigned int M = 4;
  float mu = 0.02;

  gr_top_block_sptr tb = gr_make_top_block("eq_lms_dump");

  gr::analog::sig_source_f::sptr sig_source = gr::analog::sig_source_f::make(samp_rate, gr::analog::GR_SIN_WAVE, freq, 1, 0);
  gr::analog::noise_source_f::sptr noise_source = gr::analog::noise_source_f::make(gr::analog::GR_GAUSSIAN, 0.1, 0);

  gr_add_ff_sptr add = gr_make_add_ff(1);

  gr::eq::eq_lms_ff::sptr lms_eq = gr::eq::eq_lms_ff::make(M, mu, true);
  eq_lms_dump_sink_sptr dump_sink = make_eq_lms_dump_sink();

  tb->connect(sig_source, 0, add, 0);
  tb->connect(noise_source, 0, add, 1);

  tb->connect(add, 0, lms_eq, 0);
  tb->connect(sig_source, 0, lms_eq, 1);

  tb->connect(lms_eq, 0, dump_sink, 0);
  tb->connect(lms_eq, 1, dump_sink, 1);

  // Tell GNU Radio runtime to start flowgraph threads; the foreground thread
  // will block until either flowgraph exits (this example doesn't) or the
  // application receives SIGINT (e.g., user hits CTRL-C).
  tb->run();

  return 0;
}
