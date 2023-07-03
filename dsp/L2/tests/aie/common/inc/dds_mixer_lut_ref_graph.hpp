/*
 * Copyright (C) 2019-2022, Xilinx, Inc.
 * Copyright (C) 2022-2023, Advanced Micro Devices, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef _DSPLIB_dds_mixer_lut_ref_graph_HPP_
#define _DSPLIB_dds_mixer_lut_ref_graph_HPP_

/*
This file holds the definition of the dds_mixer
Reference model graph.
*/

#include <adf.h>
#include <vector>
#include "dds_mixer_ref.hpp"
#include "fir_ref_utils.hpp"

namespace xf {
namespace dsp {
namespace aie {
namespace mixer {
namespace dds_mixer {
using namespace adf;
struct no_port {};
class empty {};
template <typename TT_DATA,
          unsigned int TP_MIXER_MODE,
          unsigned int TP_SFDR = 90,
          unsigned int TP_API = 0,
          unsigned int TP_INPUT_WINDOW_VSIZE = 256,
          unsigned int TP_SSR = 1 // ignored
          >

class dds_mixer_lut_ref_graph : public graph {
   private:
    template <class dir>
    using port_array = std::array<port<dir>, 1>;

    using input_port1 =
        typename std::conditional_t<(TP_MIXER_MODE == 1 || TP_MIXER_MODE == 2), port_array<input>, no_port>;
    using input_port2 = typename std::conditional_t<TP_MIXER_MODE == 2, port_array<input>, no_port>;

   public:
    input_port1 in1;
    input_port2 in2;
    port_array<output> out;

    // DDS Kernel
    kernel m_ddsKernel;

    // Constructor
    dds_mixer_lut_ref_graph(uint32_t phaseInc, uint32_t initialPhaseOffset = 0) {
        printf("========================\n");
        printf("== DDS_MIXER_REF Graph  \n");
        printf("========================\n");

        // Create DDS_MIXER_REF kernel
        // IO_API is ignored because it's basically just a implementation detail
        static constexpr unsigned int tp_num_luts = TP_SFDR <= 60 ? 1 : TP_SFDR <= 120 ? 2 : 3;
        m_ddsKernel = kernel::create_object<
            dds_mixer_ref<TT_DATA, TP_INPUT_WINDOW_VSIZE, TP_MIXER_MODE, USE_LUT_SINCOS, tp_num_luts> >(
            phaseInc, initialPhaseOffset);

        // Make connections
        // Size of window in Bytes.
        if
            constexpr(TP_MIXER_MODE == 1 || TP_MIXER_MODE == 2) {
                connect<>(in1[0], m_ddsKernel.in[0]);
                dimensions(m_ddsKernel.in[0]) = {TP_INPUT_WINDOW_VSIZE};
            }
        if
            constexpr(TP_MIXER_MODE == 2) {
                connect<>(in2[0], m_ddsKernel.in[1]);
                dimensions(m_ddsKernel.in[1]) = {TP_INPUT_WINDOW_VSIZE};
            }
        connect<>(m_ddsKernel.out[0], out[0]);
        dimensions(m_ddsKernel.out[0]) = {TP_INPUT_WINDOW_VSIZE};
        // Specify mapping constraints
        runtime<ratio>(m_ddsKernel) = 0.4;

        // Source files
        source(m_ddsKernel) = "dds_mixer_ref.cpp";
    };
};
}
}
}
}
}
#endif // _DSPLIB_dds_mixer_lut_ref_graph_HPP_
