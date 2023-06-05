/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2023 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#if defined(ARDUINO)
#include "Arduino.h"
#else
#include <cstddef>
#include <cinttypes>
#include <cmath>
#endif

#include <iostream>
#include <iomanip>
#include "units.h"
#include "wmm.h"

namespace bfs {

namespace {
static constexpr double A = 6378173;
static constexpr double f = 1.0 / 298.257223563;
static constexpr double e2 = f * (2.0 - f);
static constexpr double g[13][13] = {
  {},
  {-29404.5, -1450.7},
  {-2500.0, 2982.0, 1676.8},
  {1363.9, -2381.0, 1236.2, 525.7},
  {903.1, 809.4, 86.2, -309.4, 47.9},
  {-234.4, 363.1, 187.8, -140.7, -151.2, 13.7},
  {65.9, 65.6, 73.0, -121.5, -36.2, 13.5, -64.7},
  {80.6, -76.8, -8.3, 56.5, 15.8, 6.4, -7.2, 9.8},
  {23.6, 9.8, -17.5, -0.4, -21.1, 15.3, 13.7, -16.5, -0.3},
  {5.0, 8.2, 2.9, -1.4, -1.1, -13.3, 1.1, 8.9, -9.3, -11.9},
  {-1.9, -6.2, -0.1, 1.7, -0.9, 0.6, -0.9, 1.9, 1.4, -2.4, -3.9},
  {3.0, -1.4, -2.5, 2.4, -0.9, 0.3, -0.7, -0.1, 1.4, -0.6, 0.2, 3.1},
  {-2.0, -0.1, 0.5, 1.3, -1.2, 0.7, 0.3, 0.5, -0.2, -0.5, 0.1, -1.1, -0.3}
};
static constexpr double h[13][13] = {
  {},
  {0.0, 4652.9,},
  {0.0, -2991.6, -734.8},
  {0.0, -82.2, 241.8, -542.9},
  {0.0, 282.0, -158.4, 199.8, -350.1},
  {0.0, 47.7, 208.4, -121.3, 32.2, 99.1},
  {0.0, -19.1, 25.0, 52.7, -64.4, 9.0, 68.1},
  {0.0, -51.4, -16.8, 2.3, 23.5, -2.2, -27.2, -1.9},
  {0.0, 8.4, -15.3, 12.8, -11.8, 14.9, 3.6, -6.9, 2.8},
  {0.0, -23.3, 11.1, 9.8, -5.1, -6.2, 7.8, 0.4, -1.5, 9.7},
  {0.0, 3.4, -0.2, 3.5, 4.8, -8.6, -0.1, -4.2, -3.4, -0.1, -8.8},
  {0.0, -0.0, 2.6, -0.5, -0.4, 0.6, -0.2, -1.7, -1.6, -3.0, -2.0, -2.6},
  { 0.0, -1.2, 0.5, 1.3, -1.8, 0.1, 0.7, -0.1, 0.6, 0.2, -0.9, -0.0, 0.5}
};
static constexpr double gd[13][13] = {
  {},
  {6.7, 7.7},
  {-11.5, -7.1, -2.2},
  {2.8, -6.2, 3.4, -12.2},
  {-1.1, -1.6, -6.0, 5.4, -5.5},
  {-0.3, 0.6, -0.7, 0.1, 1.2, 1.0},
  {-0.6, -0.4, 0.5, 1.4, -1.4, -0.0, 0.8},
  {-0.1, -0.3, -0.1, 0.7, 0.2, -0.5, -0.8, 1.0},
  {-0.1, 0.1, -0.1, 0.5, -0.1, 0.4, 0.5, 0.0, 0.4},
  {-0.1, -0.2, -0.0, 0.4, -0.3, -0.0, 0.3, -0.0, -0.0, -0.4},
  {0.0, -0.0, -0.0, 0.2, -0.1, -0.2, -0.0, -0.1, -0.2, -0.1, -0.0},
  {-0.0, -0.1, -0.0, 0.0, -0.0, -0.1, 0.0, -0.0, -0.1, -0.1, -0.1, -0.1},
  {0.0, -0.0, -0.0, 0.0, -0.0, -0.0, 0.0, -0.0, 0.0, -0.0, -0.0, -0.0, -0.1}
};
static constexpr double hd[13][13] = {
  {},
  {0.0, -25.1},
  {0.0, -30.2, -23.9},
  {0.0, 5.7, -1.0, 1.1},
  {0.0, 0.2, 6.9, 3.7, -5.6},
  {0.0, 0.1, 2.5, -0.9, 3.0, 0.5},
  {0.0, 0.1, -1.8, -1.4, 0.9, 0.1, 1.0},
  {0.0, 0.5, 0.6, -0.7, -0.2, -1.2, 0.2, 0.3},
  {0.0, -0.3, 0.7, -0.2, 0.5, -0.3, -0.5, 0.4, 0.1},
  {0.0, -0.3, 0.2, -0.4, 0.4, 0.1, -0.0, -0.2, 0.5, 0.2},
  {0.0, -0.0, 0.1, -0.3, 0.1, -0.2, 0.1, -0.0, -0.1, 0.2, -0.0},
  {0.0, -0.0, 0.1, 0.0, 0.2, -0.0, 0.0, 0.1, -0.0, -0.1, 0.0, -0.0},
  {0.0, -0.0, 0.0, -0.1, 0.1, -0.0, 0.0, -0.0, 0.1, -0.0, -0.0, 0.0, -0.1}
};

}  // namespace 

WmmData wrldmagm(const float h, const double latitude, const double longitude,
                 const double decyear) {
  WmmData ret;
  double phi = bfs::deg2rad(latitude);
  double lamda = bfs::deg2rad(longitude);
  double Rc = A / std::sqrt(1.0 - e2 * std::sin(phi) * std::sin(phi));
  double p = (Rc + h) * std::cos(phi);
  double z = (Rc * (1.0 - e2) + h) * std::sin(phi);
  double r = std::sqrt(p * p + z * z); // XXX investigate more
  double pp = std::asin(z / r);
  double Xp, Yp, Zp, P, dP;

  for (std::size_t n = 1; n <=12; n++) {
    for (std::size_t m = 0; m <=n; m++) {
      P = 
      // dP = (n + 1) * std::tan(phi) * 
    }
   }


  // double r1 = 6378137;
  // double r2 = 6356752.3141;
  // double R = std::sqrt(((r1 * r1 * cos(phi)) * (r1 * r1 * cos(phi)) +
  //                      (r2 * r2 * sin(phi)) * (r2 * r2 * sin(phi))) / 
  //                     ((r1 * cos(phi)) * (r1 * cos(phi)) +
  //                      (r2 * sin(phi)) * (r2 * sin(phi))));

  // std::cout << std::setprecision(20) << R << std::endl;

  // double g, h;
  // double xp, yp, zp;
  // for (std::size_t n = 1; i <= 12; n++) {
  //   for (std::size_t m = 0; m <= n; m++) {
  //   }
  // }
  return ret;
}

}  // namespace bfs
