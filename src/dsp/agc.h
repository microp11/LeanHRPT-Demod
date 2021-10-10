/*
 * LeanHRPT Demod
 * Copyright (C) 2021 Xerbo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DSP_AGC_H
#define DSP_AGC_H

#include <complex>

// Automatic Gain Control, normalizes the magnitude of a signal
class AGC {
    public:
        AGC(float rate = 0.001f, float reference = 1.0f, float gain = 1.0f, float max_gain = 65536.0f)
            : d_rate(rate),
              d_reference(reference),
              d_gain(gain),
              d_max_gain(max_gain) { }

        size_t work(const std::complex<float> *in, std::complex<float> *out, size_t n) {
            for (size_t i = 0; i < n; i++) {
                out[i] = in[i] * d_gain;

                float abs = std::sqrt(out[i].real()*out[i].real() + out[i].imag()*out[i].imag());
                d_gain += d_rate * (d_reference - abs);
                d_gain = std::min(d_gain, d_max_gain);
            }

            return n;
        }
    private:
        const float d_rate;
        const float d_reference;
        float d_gain;
        const float d_max_gain;
};

#endif
