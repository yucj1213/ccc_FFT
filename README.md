# CCFSys CCC 2023
This repository is used to store the code and files about the ccc .

## Tools Versions  

This version of the tutorial has been verified for the following environments. 

| Environment  | Vitis   |    XRT   | Shell | Notes |
|--------------|---------|----------|-------|-------|
| VCK5000      | 2022.2  | 2.14.384  | xilinx_vck5000_gen4x8_qdma_2_202220_1|  |  

## Problem FFT  
- Basic - 1024-Point FFT Single Kernel Programming
 The basic requirement is to complete a 1k-Point FFT design based on personal understanding using AIE API or AIE Intrinsic.
 
- Advanced - Explore very large point FFT (8k ~ 64k points) design on VCK5000

## Submission File Tree  
├── aie
│&nbsp;├── data
│   │   ├── inputa_float.txt
│   │   ├── ref_outputc_float.txt
│   ├── Makefile
│   └── src
│       ├── aie_kernels
│       ├── aie_kernels.h
│       ├── graph.cpp
│       ├── graph.h
│       └── system_settings.h
├── host
│   ├── host.cpp
│   ├── Makefile
│   └── matmult.py
├── hw_link
│   └── config.cfg
├── Makefile
└── pl
    ├── Makefile
    └── src
        ├── config.hpp
        ├── mm2s.cpp
        └── s2mm.cpp

## AIEEMU  



## MATLAB result  

## AIE hardware run  
准备一个txt文件 第一个数表示fft点的实部 空格 第二个点表示fft的虚部
## Result compare  

## Reference  
1. xup_aie_training-main/sources/dsplib_lab
2. xup_aie_training-main/sources/Vitis_Libraries
3. vck5000_mixed_kernel_integration-2022.2/vck5000_mixed_kernel_integration-master
4. Block-by-Block Configurable Fast Fourier Transform Implementation on AI Engine (XAPP1356)
5. 
