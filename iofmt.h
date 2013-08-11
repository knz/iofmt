// io::fmt -- printf-like formatting for streams -*- C++ -*-
//
// Copyright (c) 2013 Raphael 'kena' Poss
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#ifndef _IO_FMT_H
#define _IO_FMT_H

#include <ios>
#include <cstdlib>

namespace io {

    struct _Setfmt { const char* _M_fmt; };

    inline _Setfmt fmt(const char* __s)
    { _Setfmt __sf = { __s }; return __sf; }

    template<typename Stream>
        inline Stream& setfmt(Stream& __s, const char * __fmt)
    {
        __s.unsetf(
#if __cplusplus >= 201103L
            std::ios_base::boolalpha |
#endif
            std::ios_base::showpos |
            std::ios_base::showbase |
            std::ios_base::showpoint |
            std::ios_base::uppercase);
        __s.setf(std::ios_base::dec, std::ios_base::basefield);
        __s.setf(std::ios_base::fmtflags(),
                 std::ios_base::adjustfield | std::ios_base::floatfield);
        __s.precision(6);
        __s.width(0);
        __s.fill(' ');

        bool __alt = false, __inv = false;
        for (size_t i = 0; __fmt[i] != '\0'; ++i) {
            switch(__fmt[i]) {
            case '#': __alt = true; continue;
            case '!': __inv = true; continue;
            case '+': __s.setf(std::ios_base::showpos); continue;
            case 'L': case '-': __s.setf(std::ios_base::left); continue;
            case 'R': __s.setf(std::ios_base::right); continue;
            case 'I': __s.setf(std::ios_base::internal); continue;
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            {
                char *__end;
                unsigned long __w = ::strtoul(&__fmt[i], &__end, 10);
                i += __end - &__fmt[i] - 1;
                __s.width(__w);
            }
            continue;
            case '.':
                if (__fmt[i + 1] != '\0') {
                    char *__end;
                    ++i;
                    unsigned long __p = ::strtoul(&__fmt[i], &__end, 10);
                    i += __end - &__fmt[i] - 1;
                    __s.precision(__p);
                }
                continue;
            case '=':
                if (__fmt[i + 1] != '\0')
                    __s.fill(__fmt[++i]);
                continue;
            }

            if (__alt) switch(__fmt[i]) {
                case 'd': case 'p': case 'x': case 'X': case 'o': case 'O':
                    __s.setf(std::ios_base::showbase); break;
                case 'f': case 'F': case 'e': case 'E': case 'g': case 'G': case 'a': case 'A':
                    __s.setf(std::ios_base::showpoint); break;
                }
            switch(__fmt[i]) {
            case 'X': case 'F': case 'E': case 'G': case 'A':
                __s.setf(std::ios_base::uppercase); break;
            }
            switch(__fmt[i]) {
            case '&':
                if (__inv)
                    __s.unsetf(std::ios_base::unitbuf);
                else
                    __s.setf(std::ios_base::unitbuf);
                break;
            case '>':
                if (__inv)
                    __s.unsetf(std::ios_base::skipws);
                else
                    __s.setf(std::ios_base::skipws);
                break;
            case 'd': __s.setf(std::ios_base::dec, std::ios_base::basefield); break;
            case 'p': case 'x': case 'X': __s.setf(std::ios_base::hex, std::ios_base::basefield); break;
            case 'o': __s.setf(std::ios_base::oct, std::ios_base::basefield); break;
            case 'e': case 'E': __s.setf(std::ios_base::scientific, std::ios_base::floatfield); break;
            case 'f': case 'F': __s.setf(std::ios_base::fixed, std::ios_base::floatfield); break;
#if __cplusplus >= 201103L
            case 'b': __s.setf(std::ios_base::boolalpha); break;
#endif
            case 'a': case 'A': __s.setf(std::ios_base::scientific | std::ios_base::fixed); break;
                // no special case for g/G
            }
        }
        return __s;
    }

    template<typename Stream>
        Stream& operator<<(Stream& __os, const _Setfmt& __sf)
    {
        return setfmt(__os, __sf._M_fmt);
    }

    template<typename Stream>
        Stream& operator>>(Stream& __is, const _Setfmt& __sf)
    {
        return setfmt(__is, __sf._M_fmt);
    }
}

#endif
