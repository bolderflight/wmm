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
#include "core/core.h"
#endif

#include "julian.h"

namespace bfs {

double julian(const int16_t yyyy, const int8_t mm, const int8_t dd,
              const int8_t h, const int8_t m, const int8_t s) {
  int64_t jdn = (1461 * (yyyy + 4800 + (mm - 14) / 12)) / 4 +
                (367 * (mm - 2 - 12 * ((mm - 14) / 12))) / 12 -
                (3 * ((yyyy + 4900 + (mm - 14) / 12) / 100)) / 4 + dd - 32075;
  double jd = static_cast<double>(jdn) + (h - 12.0) / 24.0 + m / 1440.0 +
              s / 86400.0;
  return jd;
}

int64_t julian(const int16_t yyyy, const int8_t mm, const int8_t dd) {
  return static_cast<int64_t>(julian(yyyy, mm, dd, 12, 0, 0));
}

double decyear(const int16_t yyyy, const int8_t mm, const int8_t dd,
               const int8_t h, const int8_t m, const int8_t s) {
  double jd = julian(yyyy, mm, dd, h, m, s);
  double epoch = julian(yyyy, 1, 1, 0, 0, 0);
  return static_cast<double>(yyyy) + (jd - epoch) / 365.0;
}

double decyear(const int16_t yyyy, const int8_t mm, const int8_t dd) {
  return decyear(yyyy, mm, dd, 0, 0, 0);
}

}  // namespace bfs
