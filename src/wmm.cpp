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
#endif

#include "units.h"  // NOLINT
#include "wmm.h"  // NOLINT
#include "XYZgeomag.h"  // NOLINT

namespace bfs {

WmmData wrldmagm(const float alt, const float lat, const float lon,
                 const float decyear, const WmmModel model,
                 const AngPosUnit ang) {
  WmmData ret;
  geomag::Vector pos = geomag::geodetic2ecef(
                          convang(lat, ang, AngPosUnit::DEG),
                          convang(lon, ang, AngPosUnit::DEG), alt);
  geomag::Vector mag_field;
  switch (model) {
    case WMM2015_V2: {
      mag_field = geomag::GeoMag(decyear, pos, geomag::WMM2015v2);
      break;
    }
    case WMM2015: {
      mag_field = geomag::GeoMag(decyear, pos, geomag::WMM2015);
      break;
    }
    default: {
      mag_field = geomag::GeoMag(decyear, pos, geomag::WMM2020);
      break;
    }
  }
  geomag::Elements out = geomag::magField2Elements(mag_field,
                            convang(lat, ang, AngPosUnit::DEG),
                            convang(lon, ang, AngPosUnit::DEG));
  ret.mag_field_nt[0] = out.north;
  ret.mag_field_nt[1] = out.east;
  ret.mag_field_nt[2] = out.down;
  ret.horz_intensity_nt = out.horizontal;
  ret.total_intensity_nt = out.total;
  ret.inclination_deg = out.inclination;
  ret.declination_deg = out.declination;
  return ret;
}

WmmData wrldmagm(const float alt, const float lat, const float lon,
                 const float decyear, const AngPosUnit ang) {
  return wrldmagm(alt, lat, lon, decyear, WMM2020, ang);
}

}  // namespace bfs
