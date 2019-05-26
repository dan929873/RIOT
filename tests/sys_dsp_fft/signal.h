/*
 * Copyright (C) 2019 Unwired Devices [info@unwds.com]
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */
/**
 * @ingroup     tests
 * @{
 *
 * @file        signal.h
 * @brief       Digitized periodic signal values for fixed point FFT testing
 *
 * @author      Alexander Ugorelov <alex_u@unwds.com>
 *
 * @}
 */

#ifndef SIGNAL_H
#define SIGNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dsp/dsp_type.h"

#define FREQ_SAMPLE         400
#define DATA_SIZE           1024
    
const q15_t signal[1024] = {
     0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768,
-29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0, -14876,
-26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,  32767,  29197,  19261,
  5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,  14876,  26510,  32365,
 31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197, -19261,  -5126,  10126,
 23170,  31164,  32365,  26510,  14876,      0, -14876, -26510, -32365, -31164, -23170,
-10126,   5126,  19261,  29197,  32767,  29197,  19261,   5126, -10126, -23170, -31164,
-32365, -26510, -14876,      0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126,
-19261, -29197, -32768, -29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,
 14876,      0, -14876, -26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,
 32767,  29197,  19261,   5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,
 14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197,
-19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0, -14876, -26510,
-32365, -31164, -23170, -10126,   5126,  19261,  29197,  32767,  29197,  19261,   5126,
-10126, -23170, -31164, -32365, -26510, -14876,      0,  14876,  26510,  32365,  31164,
 23170,  10126,  -5126, -19261, -29197, -32768, -29197, -19261,  -5126,  10126,  23170,
 31164,  32365,  26510,  14876,      0, -14876, -26510, -32365, -31164, -23170, -10126,
  5126,  19261,  29197,  32767,  29197,  19261,   5126, -10126, -23170, -31164, -32365,
-26510, -14876,      0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261,
-29197, -32768, -29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,
     0, -14876, -26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,  32767,
 29197,  19261,   5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,  14876,
 26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197, -19261,
 -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0, -14876, -26510, -32365,
-31164, -23170, -10126,   5126,  19261,  29197,  32767,  29197,  19261,   5126, -10126,
-23170, -31164, -32365, -26510, -14876,      0,  14876,  26510,  32365,  31164,  23170,
 10126,  -5126, -19261, -29197, -32768, -29197, -19261,  -5126,  10126,  23170,  31164,
 32365,  26510,  14876,      0, -14876, -26510, -32365, -31164, -23170, -10126,   5126,
 19261,  29197,  32767,  29197,  19261,   5126, -10126, -23170, -31164, -32365, -26510,
-14876,      0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197,
-32768, -29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0,
-14876, -26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,  32767,  29197,
 19261,   5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,  14876,  26510,
 32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197, -19261,  -5126,
 10126,  23170,  31164,  32365,  26510,  14876,      0, -14876, -26510, -32365, -31164,
-23170, -10126,   5126,  19261,  29197,  32767,  29197,  19261,   5126, -10126, -23170,
-31164, -32365, -26510, -14876,      0,  14876,  26510,  32365,  31164,  23170,  10126,
 -5126, -19261, -29197, -32768, -29197, -19261, -5126,   10126,  23170,  31164,  32365,
 26510,  14876,      0, -14876, -26510, -32365, -31164, -23170, -10126,   5126,  19261,
 29197,  32767,  29197,  19261,   5126, -10126, -23170, -31164, -32365, -26510, -14876,
     0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768,
-29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0, -14876,
-26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,  32767,  29197,  19261,
  5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,  14876,  26510,  32365,
 31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197, -19261,  -5126,  10126,
 23170,  31164,  32365,  26510,  14876,      0, -14876, -26510, -32365, -31164, -23170,
-10126,   5126,  19261,  29197,  32767,  29197,  19261,   5126, -10126, -23170, -31164,
-32365, -26510, -14876,      0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126,
-19261, -29197, -32768, -29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,
 14876,      0, -14876, -26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,
 32767,  29197,  19261,   5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,
 14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197,
-19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0, -14876, -26510,
-32365, -31164, -23170, -10126,   5126,  19261,  29197,  32767,  29197,  19261,   5126,
-10126, -23170, -31164, -32365, -26510, -14876,      0,  14876,  26510,  32365,  31164,
 23170,  10126,  -5126, -19261, -29197, -32768, -29197, -19261,  -5126,  10126,  23170,
 31164,  32365,  26510,  14876,      0, -14876, -26510, -32365, -31164, -23170, -10126,
  5126,  19261,  29197,  32767,  29197,  19261,   5126, -10126, -23170, -31164, -32365,
-26510, -14876,      0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261,
-29197, -32768, -29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,
     0, -14876, -26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,  32767,
 29197,  19261,   5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,  14876,
 26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197, -19261,
 -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0, -14876, -26510, -32365,
-31164, -23170, -10126,   5126,  19261,  29197,  32767,  29197,  19261,   5126, -10126,
-23170, -31164, -32365, -26510, -14876,      0,  14876,  26510,  32365,  31164,  23170,
 10126,  -5126, -19261, -29197, -32768, -29197, -19261,  -5126,  10126,  23170,  31164,
 32365,  26510,  14876,      0, -14876, -26510, -32365, -31164, -23170, -10126,   5126,
 19261,  29197,  32767,  29197,  19261,   5126, -10126, -23170, -31164, -32365, -26510,
-14876,      0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197,
-32768, -29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0,
-14876, -26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,  32767,  29197,
 19261,   5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,  14876,  26510,
 32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197, -19261,  -5126,
 10126,  23170,  31164,  32365,  26510,  14876,      0, -14876, -26510, -32365, -31164,
-23170, -10126,   5126,  19261,  29197,  32767,  29197,  19261,   5126, -10126, -23170,
-31164, -32365, -26510, -14876,      0,  14876,  26510,  32365,  31164,  23170,  10126,
 -5126, -19261, -29197, -32768, -29197, -19261,  -5126,  10126,  23170,  31164,  32365,
 26510,  14876,      0, -14876, -26510, -32365, -31164, -23170, -10126,   5126,  19261,
 29197,  32767,  29197,  19261,   5126, -10126, -23170, -31164, -32365, -26510, -14876,
     0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768,
-29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0, -14876,
-26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,  32767,  29197,  19261,
  5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,  14876,  26510,  32365,
 31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197, -19261,  -5126,  10126,
 23170,  31164,  32365,  26510,  14876,      0, -14876, -26510, -32365, -31164, -23170,
-10126,   5126,  19261,  29197,  32767,  29197,  19261,   5126, -10126, -23170, -31164,
-32365, -26510, -14876,      0,  14876,  26510,  32365,  31164,  23170,  10126,  -5126,
-19261, -29197, -32768, -29197, -19261,  -5126,  10126,  23170,  31164,  32365,  26510,
 14876,      0, -14876, -26510, -32365, -31164, -23170, -10126,   5126,  19261,  29197,
 32767,  29197,  19261,   5126, -10126, -23170, -31164, -32365, -26510, -14876,      0,
 14876,  26510,  32365,  31164,  23170,  10126,  -5126, -19261, -29197, -32768, -29197,
-19261,  -5126,  10126,  23170,  31164,  32365,  26510,  14876,      0, -14876, -26510,
-32365,
};

#ifdef __cplusplus
}
#endif

#endif /* SIGNAL_H */

