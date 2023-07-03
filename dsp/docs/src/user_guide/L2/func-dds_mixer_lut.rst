..
   Copyright (C) 2019-2022, Xilinx, Inc.
   Copyright (C) 2022-2023, Advanced Micro Devices, Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.


.. _DDS_MIXER_LUT:

======================
DDS / Mixer using LUTs
======================
~~~~~~~~~~~
Entry Point
~~~~~~~~~~~

The graph entry point is the following:

.. code-block::

    xf::dsp::aie::mixer::dds_mixer::dds_mixer_lut_graph

~~~~~~~~~~~~~~~
Supported Types
~~~~~~~~~~~~~~~

On AIE devices, the dds_mixer_lut supports cint16, cint32 and cfloat as ``TT_DATA`` type that specifies the type of input and output data. Input is only required when ``TP_MIXER_MODE`` is
set to 1 (simple mixer) or 2 (dual conjugate mixer).
The AIE-ML devices does not support cfloat data type, so the dds_mixer_lut also does not support this data type. Only cint16 and cint32 are supported.

~~~~~~~~~~~~~~~~~~~
Template Parameters
~~~~~~~~~~~~~~~~~~~

To see details on the template parameters for the DDS/Mixer, see :ref:`API_REFERENCE`.

~~~~~~~~~~~~~~~~
Access functions
~~~~~~~~~~~~~~~~

To see details on the access functions for the DDS/Mixer, see :ref:`API_REFERENCE`.

~~~~~
Ports
~~~~~

To see details on the ports for the DDS/Mixer, see :ref:`API_REFERENCE`.
Please note that on AIE-ML devices, outputs of the streaming and windowed modes are not bitwise identical due to some implementation choices made for higher performance.

~~~~~~~~~~~~
Design Notes
~~~~~~~~~~~~

Scaling
-------

When configured as a DDS (TP_MIXER_MODE=0) the output of the DDS is intended to be the components of a unit vector. For ``TT_DATA = cfloat``, this means that the outputs will be in the range -1.0 to +1.0. For ``TT_DATA = cint16`` and ``TT_DATA = cint32`` the output is scaled by 2 to the power 15 and 31 respectively such that the binary point follows the most significant bit of the output. Therefore, if the DDS output is used to multiply/mix, you must account for this bit shift.

SFDR
----

Spurious Free Dynamic Range is a parameter used to characterize signal generators. It measures the ratio between the amplitude of the fundamental frequency of the signal generator to the amplitude of the strongest spur. The dds_mixer_lut generates slightly different designs based on the SFDR requested by the user. The different implementations offer tradeoffs between the SFDR of the waveform generated and the throughput. Three different implementations are available, for SFDR less than 60dB, less than 120dB and for less than 180dB. Note that with the cint16 data type the maximum SFDR is 120dB.

Super Sample Rate Operation
---------------------------
See :ref:`DDS_SSR`.

Please note that in this implementation of the DDS, the output data for various values of ``TP_SSR`` are not bitwise identical. The SFDR values may also be slightly different for different values of ``TP_SSR``.

~~~~~~~~~~~~~~~~~~~~
Implementation Notes
~~~~~~~~~~~~~~~~~~~~
In a conventional DDS (sometimes known as an Numerically Controlled Oscillator), a phase increment value is added to a phase accumulator on each cycle. The value of the phase accumulator is effectively the phase part of a unit vector in polar form. This unit vector is then converted to cartesian form by lookup of sin and cos values from a table of precomputed values. These cartesian values are then output.

It should be noted that, in the dds_mixer_lut the sin/cos values are not scaled to the full range of the bit-width to avoid saturation effects that arise due to 2s complement representation of numbers. The maximum positive value representable by an n-bit 2s complement number is 1 less than the magnitude of the largest negative value. So, the sin/cos values are scaled by the magnitude of the maximum positive value only. So, for cint16 type, +1 scales to +32767 and -1 scales to -32767. Also, following the run-time multiplication of the looked-up cartesian value for a cycle by the precomputed vector, scaling down and rounding will lead to other small reductions in the maximum magnitude of the waveform produced.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Code Example including constraints
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The following code example shows how the DDS/Mixer graph class may be used within a user super-graph to use an instance configured as a mixer.

.. literalinclude:: ../../../../L2/examples/docs_examples/test_dds_lut.hpp
    :language: cpp
    :lines: 15-



.. |image1| image:: ./media/image1.png
.. |image2| image:: ./media/image2.png
.. |image3| image:: ./media/image4.png
.. |image4| image:: ./media/image2.png
.. |image6| image:: ./media/image2.png
.. |image7| image:: ./media/image5.png
.. |image8| image:: ./media/image6.png
.. |image9| image:: ./media/image7.png
.. |image10| image:: ./media/image2.png
.. |image11| image:: ./media/image2.png
.. |image12| image:: ./media/image2.png
.. |image13| image:: ./media/image2.png
.. |trade|  unicode:: U+02122 .. TRADEMARK SIGN
   :ltrim:
.. |reg|    unicode:: U+000AE .. REGISTERED TRADEMARK SIGN
   :ltrim:



