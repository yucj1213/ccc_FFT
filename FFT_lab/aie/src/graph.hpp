// Copyright (C) 2023 Advanced Micro Devices, Inc
//
// SPDX-License-Identifier: MIT

#pragma once

#include "adf.h"
#include "fft.hpp"




class DSPLibGraph: public graph {
    private:
        FFT1d_graph fft;
    public:
        adf::input_plio s_in[4];
        adf::output_plio s_out[6];
        DSPLibGraph() {
 
            // FFT connections
            s_in[1] = input_plio::create("DataInFFT0", adf::plio_128_bits, "data/DataInFFT0.txt");
            s_out[1] = output_plio::create("DataOutFFT0", adf::plio_128_bits, "DataOutFFT0.txt");
            adf::connect<stream> (s_in[1].out[0],  fft.in);
            adf::connect<stream> (fft.out, s_out[1].in[0]);
            
             }
};
