/*! \file demo_1d_meas.cpp
    \brief Simple plot of uncertainty of 1D data.
    \details An example to demonstrate simple 1D plot using two vectors,
     including showing values with uncertainty information as
     'plus minus' and degrees of freedom estimates.
    \author Paul A. Bristow
    \date Mar 2009
*/

// Copyright Paul A Bristow 2012

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

#ifdef _MSC_VER
// point_shape::round is legal in C++11, but gives warning
// (collides with name of function round in rounding.hpp.
#  pragma warning (disable : 4482) // nonstandard extension used: enum.
#endif


//[demo_1d_meas_1

/*`First we need a few includes to use Boost.Plot:
*/
#include <boost/quan/unc.hpp>
// Now #include <boost/quan/unc_init.hpp>
 // using boost::quan::unc; // Holds value and uncertainty information.
#include <boost/quan/meas.hpp> // Holds time and order information added to unc.

#include <boost/svg_plot/detail/functors.hpp>
//  using boost::svg::detail::unc_1d_convert;
#include <boost/svg_plot/svg_1d_plot.hpp>
  using namespace boost::svg;

#include <boost/svg_plot/show_1d_settings.hpp>
 void boost::svg::show_1d_plot_settings(svg_1d_plot&);

#include <iostream>
  using std::cout;
  using std::endl;
#include <vector>
  using std::vector;
#include <iterator>
  using std::ostream_iterator;
#include <algorithm>
  using std::copy;
//] [/demo_1d_meas_1]

int main()
{
  try
  {
//[demo_1d_meas_2

/*`STL vector is used as the container for our two data series,
and values are inserted using push_back.  Since this is a 1-D plot
the order of data values is not important.
*/
  setUncDefaults(std::cout);
  typedef unc<false> uncun; // Uncertain Uncorrelated (the normal case).

  vector<double> D_data; // Sample vector of doubles.
  D_data.push_back(3.95);
  D_data.push_back(6.1);

  vector<uncun> A_times;
  A_times.push_back(unc<false>(3.1, 0.02F, 8));
  A_times.push_back(uncun(4.2, 0.01F, 14, 0U));

  short unsigned int t = UNC_KNOWN | UNC_EXPLICIT| DEG_FREE_EXACT | DEG_FREE_KNOWN;

  vector<unc<false> > B_times;
  B_times.push_back(uncun(2.1, 0.001F, 29, t)); // Value, uncertainty, degrees of freedom and type known.
  // (But use of type is not yet implemented.)
  B_times.push_back(unc<>(5.1, 0.025F, 20, 0U)); // Value, uncertainty, and degrees of freedom known - the usual case.
  B_times.push_back(uncun(7.2, 0.0025F, 0, 0U)); // Value and uncertainty known, but not degrees of freedom.
  B_times.push_back(uncun(3.4, 0.03F, 0, 0U)); // Value and uncertainty known, but not degrees of freedom.
  B_times.push_back(uncun(6.9, 0.0F, 0, 0U)); // Only value known - no information available about uncertainty.

  vector<unc<false> > C_times;
  C_times.push_back(uncun(2.6, 0.1F, 5, 0U));
  C_times.push_back(uncun(5.4, 0.2F, 11, 0U));

  /*`Echo the values input: */
  copy(A_times.begin(), A_times.end(), ostream_iterator<uncun>(std::cout, " "));
  cout << endl;
  copy(B_times.begin(), B_times.end(), ostream_iterator<uncun>(std::cout, " "));
  cout << endl;
 /*`The constructor initializes a new 1D plot, called `my_plot`,
 and also sets all the very many defaults for axes, width, colors, etc.
*/
  using namespace boost::gregorian;
  using namespace boost::posix_time;
  boost::gregorian::date d(2012, Feb, 21);
  boost::posix_time::time_duration td(12,59,56);
  ptime atime = ptime(d, td);
  Meas one23(uncun(1.23, 0.02F), "one23", atime, 5); // Construct from everything.
  //cout << one23 << endl; // one23 1.23 #5, 2012-Feb-21 12:59:56
  ptime time1 = ptime(date(2012, Mar, 13), time_duration(13,01,0));
  ptime time2= ptime(date(2012, Mar, 14), time_duration(9,12,0));
  //std::stringstream ss("2004-Jan-1 05:21:33.20"); // Warning so avoid :-(
  //ss >> t2;

  Meas m1 (uncun(3.3, 0.1F, 5, 0U), "first", time1, 1);
  Meas m2 (uncun(4.5, 0.2F, 3, DEG_FREE_KNOWN), "2nd", time2, 2);

  cout << m1 << endl;
  cout << m2 << endl;

  vector<Meas> M_times;
  M_times.push_back(m1);
  M_times.push_back(m2);
  copy(M_times.begin(), M_times.end(), ostream_iterator<Meas>(std::cout, "\n"));
  cout << endl;

  cout << M_times[0] << endl;
  cout << M_times[1] << endl;

  svg_1d_plot my_plot;
/*`A few (member) functions that are set should be fairly self-explanatory:

* title provides a title at the top for the whole plot,
* `legend_on(true)` will mean that titles of data series and markers will display in the legend box.
* `x_range(-1, 11)` sets the axis limits from -1 to +11 (instead of the default -10 to +10).
* `background_border_color(blue)` sets just one of the very many other options.
*/
  my_plot.autoscale_check_limits(false); // default is true.
  my_plot.autoscale_plusminus(3); // default is 3.

  my_plot
    .x_size(600)
    .y_size(400)
    .plot_window_on(true)
    .background_border_color(blue)
    .plot_border_color(yellow)
    .plot_border_width(1)
    .x_axis_vertical(0.75)
    //.x_ticks_on_window_or_axis(0) // now the default.
    .legend_on(false)
    .title("A, B and C Times")
    .x_range(0, 10)
    .x_label("times (sec)")
    .x_values_on(true)
    .x_values_precision(2)
    .x_values_rotation(slopeup)
    .x_plusminus_color(blue)
    .x_plusminus_on(true)
    .x_df_on(true)
    .x_df_color(green)
    .x_id_on(true)
    .x_id_color(red)
    .x_datetime_on(true)
    .x_datetime_color(magenta)
    .x_order_on(true)
    .x_order_color(brown)
    .x_autoscale(B_times) // Note that this might not be right scaling for A_times and/or C_times.
    ;

/*`
Then we add our data series,
and add optional data series titles
(very helpful if we want them to show on the legend).

The A_times mark data points with a red border circle with a green fill,
The B_times use a blue vertical line,
while C_times use an ellipse whose width (x radius) is from the uncertainty,
1st standard deviation shows as ellipse in magenta, and 2nd as yellow.
All the data points are also labelled with their value,
and uncertainty and degrees of freedom if known.
*/
  my_plot.plot(D_data, "D");

  my_plot.plot(A_times, "A").shape(circlet).size(10).stroke_color(red).fill_color(green);
  my_plot.plot(B_times, "B").shape(vertical_line).stroke_color(blue);
  my_plot.plot(C_times, "C").shape(unc_ellipse).fill_color(lightyellow).stroke_color(magenta);

  my_plot.plot(M_times, "M").shape(circlet).size(10).stroke_color(purple).fill_color(orange);

/*`
Finally, we can write the SVG to a file of our choice.
*/

  std::string svg_file =  (my_plot.legend_on() == true) ?
    "./demo_1d_meas_legend.svg" : "./demo_1d_meas.svg";

  my_plot.write(svg_file);

  cout <<"Plot written to file " << svg_file << endl;
 // show_1d_plot_settings(my_plot);

//] [/demo_1d_meas_2]

  }
  catch(const std::exception& e)
  {
    std::cout << "\n""Message from thrown exception was:\n   " << e.what() << std::endl;
  }

  return 0;
} // int main()

/*

boost-no-inspect
to avoid  inspect warning about +/- being non-ASCII   "demo_1d_meas.cpp": Non-ASCII: 3.1�0.02 (8)  4.2�0.01 (14)
(May be relaxed in C++11?)

Output:
//[demo_1d_meas_output
demo_1d_meas.cpp
Linking...
Embedding manifest...
Autorun j:\Cpp\SVG\debug\demo_1d_meas.exe
3.1�0.02 (8)  4.2�0.01 (14)
2.1�0.001 (30)  7.8�0.0025 (21)  3.4�0.03 6.9
Build Time 0:03
//] [/demo_1d_meas_output]
*/

/*
Data for another 1D example, also use Boost.Math?

The data is taken from J. C. Banford el al, Analyst (1983) 107, 195
and compares the concentration of thiol of the lysate of the blood of two groups
of volunteers as control and a second suffering from rhematoid arthritis.

  map<pair<unc, unc> > control;
  control.push_back(unc(1.921, 0.076F, 7));
  map<pair<unc, unc> > rheumatoid;
  control.push_back(unc(3.456, 0.44F, 6));


*/


