/*! \file demo_2d_autoscaling.cpp
    \brief Demonstration of autoscaling in 2D plots.
    \details  An example to demonstrate simplest 2d *default* settings.
     See also auto_2d_plot.cpp for a wider range of use.

    \date 20 Mar 2009
    \author Paul A. Bristow
*/
// Copyright Paul A Bristow 2009

// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

//[demo_2d_autoscaling_1

/*`As always, we need a few includes to use Boost.Plot
*/

#include <boost/svg_plot/svg_2d_plot.hpp>
  using namespace boost::svg;
  using boost::svg::svg_2d_plot;

#include <iostream>
  using std::cout;
  using std::endl;
  using std::dec;
  using std::hex;

#include <map>
  using std::map;

//] [demo_2d_autoscaling_1]

int main()
{

//[demo_2d_autoscaling_2
/*`Some fictional data is pushed into an STL container, here map:\n

  This example uses a single map to demonstrate autoscaling.
  We construct a map to hold our data series, and insert some fictional values (that also sorts the data).
  The index value in [] is the x value.
  */
  map<const double, double> my_data;
  my_data[1.1] = 3.2;
  my_data[7.3] = 9.1;
  my_data[2.12] = 2.4394;
  my_data[5.47] = 5.3861;

  try
  { // try'n'catch blocks are needed to ensure error messages from any exceptions are shown.
    svg_2d_plot my_2d_plot; // Construct a plot with all the default constructor values.
    my_2d_plot.title("Autoscaling 2d Values"); // Add a string title of the plot.

/*` With the defaults ranges would be -10 to +10 for both X and Y axes.  We could chose our own ranges
    `.x_range(0, 6) // Add a range for the X-axis.`
    `.y_range(0, 10) // Add a range for the Y-axis.`
  Or we can use autoscaling.

*/
   my_2d_plot.xy_autoscale(my_data); // Autoscale both x and Y axes.

   /*`This says use the entire STL container my_data to set both X and Y ranges.
(The data used to autoscale the range(s) does not have to be the same as the data being plotted.
For example, if we have analysed a product and know that an attribute like strength can only decline as the product ages,
it would make sense to use the reference 'as new' data to scale the plot for the 'aged' product samples).

The add the (one but could be more) data series, `my_data` and a description, and how the data points are to be marked,
here a circle with a diameter of 5 pixels, without a line joining the points (also the default).
*/
    my_2d_plot.plot(my_data, "2d Values").shape(circlet).size(6).line_on(false);

/*`To use all these settings, finally write the plot to file.
*/
    my_2d_plot.write("./demo_2d_autoscaling.svg");

//] [demo_2d_autoscaling_2]
  }
  catch(const std::exception& e)
  {
    std::cout <<
      "\n""Message from thrown exception was:\n   " << e.what() << std::endl;
  }
  return 0;
} // int main()

/*

//[demo_2d_autoscaling_output

Output:



*/

