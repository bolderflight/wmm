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

#include "wmm.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) {}
  bfs::WmmData data = bfs::wrldmagm(2062, 35.691544, -105.944183, 2022.5);
  Serial.println(data.mag_field_nt[0]);
  Serial.println(data.mag_field_nt[1]);
  Serial.println(data.mag_field_nt[2]);
  Serial.println(data.horz_intensity_nt);
  Serial.println(data.declination_deg);
  Serial.println(data.inclination_deg);
  Serial.println(data.total_intensity_nt);
}

void loop() {}
