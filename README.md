[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

![Bolder Flight Systems Logo](img/logo-words_75.png) &nbsp; &nbsp; ![Arduino Logo](img/arduino_logo_75.png)

# WMM
This implements the World Magnetic Model providing the magnetic field vector, horizontal intensity, declination, inclination, and total intensity as outputs. This library is compatible with Arduino ARM and CMake build systems.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

# Installation

## Arduino
Use the Arduino Library Manager to install this library or clone to your Arduino/libraries folder. Additionally, the [Bolder Flight Systems Units library](https://github.com/bolderflight/units) must be installed. This library is added as:

```C++
#include "wmm.h"
```

An example Arduino executable is located at *examples/arduino/wmm_ex/wmm_ex.ino*. Teensy 3.x, 4.x, and LC devices are used for testing under Arduino and this library should be compatible with other ARM devices. This library is *not* expected to work on AVR devices.

## CMake
CMake is used to build this library, which is exported as a library target called *wmm*. The header is added as:

```C++
#include "wmm.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library and an example executable called *wmm_ex*. The example executable source file is located at *examples/cmake/wmm_ex.cc*.

# Namespace
This library is within the namespace *bfs*.

# Structs and Enums

**WmmData** This struct is used to access the WMM outputs. The struct fields are:

   * float mag_field_nt[3]: The magnetic field vector in the north, east, and down direction respectively. Units nT.
   * float horz_intensity_nt: The horizontal intensity, returned as a scalar in nT.
   * float declination_deg: Declination, returned as a scalar, in degrees (+ve east).
   * float inclination_deg: Inclination, returned as a scalar, in degrees (+ve down).
   * float total_intensity_nt: The total intensity, returned as a scalar in nT.

**WmmModel** This enum is used to optionally specify the model used. The options are:
   * WMM2020: WMM2020 (epoch 2020–2025).
   * WMM2015_V2: WMM2015v2 (epoch 2015–2020).
   * WMM2015: WMM2015 (epoch 2015–2020). This version is not recommended. Use WMM2015V2 instead.

# Functions
   
**WmmData wrldmagm(const float alt, const float lat, const float lon, const float decyear, const WmmModel model, const AngPosUnit ang = AngPosUnit::DEG)** Given the altitude above the WGS84 ellipsoid, the latitude, longitude, decimal year, and model, returns the WMM data in the *WmmData* structure format. Optionally, can specify the units for the latitude and longitude, the default is degrees.

```C++
bfs::WmmData data = bfs::wrldmagm(2062, 35.691544, -105.944183, 2022.5, bfs::WMM2015_V2);
std::cout << data.mag_field_nt[0] << std::endl;
std::cout << data.mag_field_nt[1] << std::endl;
std::cout << data.mag_field_nt[2] << std::endl;
std::cout << data.horz_intensity_nt << std::endl;
std::cout << data.declination_deg << std::endl;
std::cout << data.inclination_deg << std::endl;
std::cout << data.total_intensity_nt << std::endl;
```

**WmmData wrldmagm(const float alt, const float lat, const float lon, const float decyear, const WmmModel model, const AngPosUnit ang = AngPosUnit::DEG)** Given the altitude above the WGS84 ellipsoid, the latitude, longitude, and decimal year, returns the WMM data in the *WmmData* structure format. Optionally, can specify the units for the latitude and longitude, the default is degrees. The WMM2020 model is used.

```C++
bfs::WmmData data = bfs::wrldmagm(2062, 35.691544, -105.944183, 2022.5);
std::cout << data.mag_field_nt[0] << std::endl;
std::cout << data.mag_field_nt[1] << std::endl;
std::cout << data.mag_field_nt[2] << std::endl;
std::cout << data.horz_intensity_nt << std::endl;
std::cout << data.declination_deg << std::endl;
std::cout << data.inclination_deg << std::endl;
std::cout << data.total_intensity_nt << std::endl;
```

