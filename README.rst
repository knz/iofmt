=========
 io::fmt
=========

small, fast, printf-like formatting for C++ streams
---------------------------------------------------

In a nutshell, **io::fmt**:

- provides a `printf`__-like syntax to control **formatting** on C++'s
  I/O **streams** (std::iostream, std::stringstream, etc.);
- provides a **shorter syntax** than the standard C++ manipulators (std::fixed, std::setprecision, etc.).
- **runs faster** than `boost::format`__ (but does not enforce typing).

.. __: http://www.cplusplus.com/reference/cstdio/printf/
.. __: http://www.boost.org/doc/libs/1_54_0/libs/format/

How to use
==========

1. copy ``iofmt.h`` in your project,
2. include ``iofmt.h`` in your C++ code,
3. use ``io::fmt("...")`` on your C++ streams.

For example::

  #include "iofmt.h"
  #include <iostream>

  using namespace std;
  int main() {
     int v;
     cout << "Enter an octal value: " << flush;
     cin  >> io::fmt("o") >> v;
     cout << "In hex: " << io::fmt("#x") << v << endl;
     return 0;
  }

will print "0x7b" before terminating.

This example shows:

- ``io::fmt("o")`` which is like ``std::oct``;
- ``io::fmt("#x")`` which is like but shorter than ``std::hex << std::showbase``;
- that ``io::fmt`` works for both input and output streams.

Format strings
==============

The argument to **io::fmt** is a C string containing zero or more of the following
sequences in any order:

========== ====================== ================================ =================
Sequence   ``printf`` equivalent  Description                      C++ equivalent
========== ====================== ================================ =================
``s``      ``s``                  String                           (default)
``d``      ``d``                  Decimal integer                  ``std::dec`` (default)
``o``      ``o``                  Octal integer                    ``std::oct``
``x``      ``x``                  Hexadecimal integer              ``std::hex``
``X``      ``X``                  Hexadecimal integer, uppercase   ``std::hex << std::uppercase``
``p``      ``p``                  Pointer (same as ``#x``)         ``std::hex << std::showbase``
``f``      ``f``                  Fixed float                      ``std::fixed``
``F``      ``F``                  Fixed float, uppercase           ``std::fixed << std::uppercase``
``e``      ``e``                  Scientific float                 ``std::scientific``
``E``      ``E``                  Scientific float, uppercase      ``std::scientific << std::uppercase``
``g``      ``g``                  Automatic (floats)               (default)
``G``      ``G``                  Automatic (floats), uppercase    ``std::uppercase``
``a``      ``a``                  Hexadecimal float [1]_ [2]_      ``std::hexfloat``
``A``      ``A``                  Hexadecimal float [1]_ [2]_, uc  ``std::hexfloat << std::uppercase``
``b``      (no equivalent)        Print true/false as strings [1]_ ``std::boolalpha``
``#``      ``#``                  Alternate format                 ``std::showpoint`` (floats) / ``std::showbase`` (ints)
``+``      ``+``                  Show sign even if positive       ``std::showpos``
``.`` *N*  ``.`` *N*              Set float precision to *N*       ``std::setprecision(N)``
``-``      ``-``                  Align left, pad right            ``std::left``
``L``      ``-``                  Align left, pad right            ``std::left``
``R``      (default)              Align right, pad left            ``std::right``
``I``      (no equivalent)        Align left and right, pad middle ``std::internal``
``=`` *C*  0  (only *C* = '0')    Use *C* as padding character     ``std::setfill(C)``
*N*        *N*                    Set format width to *N* chars    ``std::setw(N)``
``&``      (no equivalent)        Flush after each I/O operation   ``std::unitbuf``
``>``      (no equivalent)        Skip whitespace on input         ``std::skipws``
``!``      (no equivalent)        Invert meaning of next ``&/>``   ``std::nounitbuf`` or ``std::noskipws``
========== ====================== ================================ =================

.. [1] Hexadecimal floats (``aA``) and booleans as strings (``b``)
       are a new feature from `C++11`_. These format characters are only effective
       when compiling in C++11 mode (e.g. ``-std=c++11`` or ``-std=gnu++11``).

.. [2] Hexadecimal floats are not yet supported in libstdc++ and
       libc++ as of G++ 4.8 and Clang++ 3.3, although they are
       mandated by the ISO C++ standard. Although **io::fmt**
       recognizes the syntax the desired effect will not be obtained
       unless the underlying C++ library also supports the
       feature. Complain to your C++ library provider if needed.

.. _C++11: https://en.wikipedia.org/wiki/C++11

Each use of ``io::fmt`` first resets all formatting flags on the I/O
stream. This means that any unspecified parameter other than ``&`` and
``>`` revert to their C++ defaults: decimal, automatic width, fill
using spaces, float precision 6, automatic float format, show sign
only if negative, no prefix.

In particular,

 ::

     s << io::fmt("");

is equivalent to::

     s << std::setw(0)
       << std::dec
       << std::setfill(' ')
       << std::setprecision(6)
       << std::noshowpos
       << std::noshowbase;
     s.setf(std::ios_base::fmtflags(), std::ios_base::floatfield);

For ``&`` and ``>`` there is no default setting: each use of
``io::fmt`` will keep the previous configuration. This is why a syntax
is also provided to disable these flags when needed: ``!&``
(``std::noflush``) and ``!>`` (``std::noskipws``).

Performance
===========

Using the enclosed ``bench.cc`` on a Core 2 Duo @ 2.4GHz and
optimization level ``-O3``, the following was measured:

========================= ==================== ====================== ==================
C++ toolchain             Formatter            Performance (fmt/sec)  Slowdown
========================= ==================== ====================== ==================
g++ 4.8 / libstdc++       none                 13796503               N/A
g++ 4.8 / libstdc++       io::fmt              12920048               7%  (1.07x slower)
g++ 4.8 / libstdc++       boost w/ pre-parse   603934                 95% (22x slower)
g++ 4.8 / libstdc++       boost w/o pre-parse  523598                 96% (26x slower)

clang++ 3.3 / libc++      none                 9001542                N/A
clang++ 3.3 / libc++      io::fmt              7752862                7%  (1.16x slower)
clang++ 3.3 / libc++      boost w/ pre-parse   531301                 95% (17x slower)
clang++ 3.3 / libc++      boost w/o pre-parse  401781                 96% (22x slower)
========================= ==================== ====================== ==================

In short, in this test program **io::fmt** incurs less than 10%
overhead compared to no formatting; whereas boost::format incurs at
least 95% overhead. YMMV.
