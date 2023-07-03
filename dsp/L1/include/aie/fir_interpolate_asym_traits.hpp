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
#ifndef _DSPLIB_FIR_INTERPOLATE_ASYM_TRAITS_HPP_
#define _DSPLIB_FIR_INTERPOLATE_ASYM_TRAITS_HPP_

#ifndef INLINE_DECL
#define INLINE_DECL inline __attribute__((always_inline))
#endif
#ifndef NOINLINE_DECL
#define NOINLINE_DECL inline __attribute__((noinline))
#endif

namespace xf {
namespace dsp {
namespace aie {
namespace fir {
namespace interpolate_asym {
/*
Asymmetrical Interpolation FIR traits.
This file contains sets of overloaded, templatized and specialized templatized functions which
encapsulate properties of the intrinsics used by the main kernal class. Specifically,
this file does not contain any vector types or intrinsics since it is required for construction
and therefore must be suitable for the aie compiler graph-level compilation.
*/

static constexpr unsigned int kBuffSize128Byte = 128; // 1024-bit buffer size in Bytes
static constexpr unsigned int kBuffSize64Byte = 64;   // 512-bit buffer size in Bytes
static constexpr unsigned int kBuffSize32Byte = 32;   // 256-bit buffer size in Bytes

// maximum tap lengths.
template <typename TT_DATA, typename TT_COEFF>
unsigned int fnMaxTapssIntAsym() {
    return 8192 / sizeof(TT_COEFF);
}; //

// The following is a set of type-specialized functions which return the number of accumulator registers
// available in the processor. Since these may be 384 or 768 bit registers the number could vary by type.
template <typename TT_DATA, typename TT_COEFF>
unsigned int fnAccRegsIntAsym() {
    return 4;
}; //

// function to return the number of lanes for a type combo
template <typename TT_DATA, typename TT_COEFF>
INLINE_DECL constexpr unsigned int fnNumLanesIntAsym() {
    return fnNumLanes<TT_DATA, TT_COEFF>();
};

// function to return the columns of lanes for a type combo
template <typename TT_DATA, typename TT_COEFF>
INLINE_DECL constexpr unsigned int fnNumColsIntAsym() {
    return fnNumCols<TT_DATA, TT_COEFF>();
};
template <>
INLINE_DECL constexpr unsigned int fnNumColsIntAsym<int16, int32>() {
    return 1;
}; // only single columns can be used due to MAC operating on 256-bit coeff buffer.

// Function to return the lowest common multiple of two numbers
// A full implementation of this would entail prime factor decomposition, but here
// The maximum integer size is 16, so a simpler brute force method will do.
template <typename TT_DATA, typename TT_COEFF, unsigned int TP_FACTOR>
INLINE_DECL constexpr unsigned int fnLCMIntAsym() {
    return ((fnNumLanesIntAsym<TT_DATA, TT_COEFF>() == 2)
                ? ((TP_FACTOR % 2 == 0) ? TP_FACTOR : (TP_FACTOR * 2))
                : (fnNumLanesIntAsym<TT_DATA, TT_COEFF>() == 4)
                      ? ((TP_FACTOR % 4 == 0) ? TP_FACTOR : ((TP_FACTOR % 2 == 0) ? (TP_FACTOR * 2) : (TP_FACTOR * 4)))
                      : (fnNumLanesIntAsym<TT_DATA, TT_COEFF>() == 8)
                            ? ((TP_FACTOR % 8 == 0)
                                   ? TP_FACTOR
                                   : ((TP_FACTOR % 4 == 0) ? (TP_FACTOR * 2)
                                                           : ((TP_FACTOR % 2 == 0) ? (TP_FACTOR * 4) : TP_FACTOR * 8)))
                            : 0);
};

// function to return the number of samples in an output vector for a type combo
template <typename TT_DATA, typename TT_COEFF>
INLINE_DECL constexpr unsigned int fnVOutSizeIntAsym() {
    return fnNumLanesIntAsym<TT_DATA, TT_COEFF>();
};
}
}
}
}
} // namespaces
#endif // _DSPLIB_FIR_INTERPOLATE_ASYM_TRAITS_HPP_
