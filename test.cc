#include "iofmt.h"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdint.h>

bool haserr = false;
std::ostringstream out;

template<typename T>
void test(const char *fmt, const T& val, const char* ref)
{
    std::ostringstream os;
    os << io::fmt(fmt) << val;
    if (os.str() != ref)
    {
        std::cerr << "error: fmt(\"" << fmt << "\") << " << std::boolalpha << val
                  << ": expected >>>" << ref
                  << "<<<, got >>>" << os.str()
                  << "<<<"
                  << std::endl;
        haserr = true;
    }
    else
    {
        out << "fmt(\"" << fmt << "\") << " << std::boolalpha << val
            << " -> >>>" << os.str() << "<<<" << std::endl;
    }
}

int main()
{
    // Integers, positive, decimal
    test("d",     123, "123");
    test("6d",    123, "   123");
    test("6Rd",   123, "   123");
    test("6Id",   123, "   123");
    test("6Ld",   123, "123   ");
    test("6=0d",  123, "000123");
    test("6R=0d", 123, "000123");
    test("6I=0d", 123, "000123");
    test("6L=0d", 123, "123000");
    test("6=xd",  123, "xxx123");
    test("6R=xd", 123, "xxx123");
    test("6I=xd", 123, "xxx123");
    test("6L=xd", 123, "123xxx");

    // Integers, positive, decimal, with sign
    test("+d",     123, "+123");
    test("6+d",    123, "  +123");
    test("6+Rd",   123, "  +123");
    test("6+Id",   123, "+  123");
    test("6+Ld",   123, "+123  ");
    test("6+=0d",  123, "00+123");
    test("6+R=0d", 123, "00+123");
    test("6+I=0d", 123, "+00123");
    test("6+L=0d", 123, "+12300");
    test("6+=xd",  123, "xx+123");
    test("6+R=xd", 123, "xx+123");
    test("6+I=xd", 123, "+xx123");
    test("6+L=xd", 123, "+123xx");

    // Integers, negative, decimal
    test("d",    -123, "-123");
    test("6d",   -123, "  -123");
    test("6Rd",  -123, "  -123");
    test("6Id",  -123, "-  123");
    test("6Ld",  -123, "-123  ");
    test("6=0d", -123, "00-123");
    test("6R=0d",-123, "00-123");
    test("6I=0d",-123, "-00123");
    test("6L=0d",-123, "-12300");
    test("6=xd", -123, "xx-123");
    test("6R=xd",-123, "xx-123");
    test("6I=xd",-123, "-xx123");
    test("6L=xd",-123, "-123xx");

    // Integers, positive, octal
    test("o",     123, "173");
    test("6o",    123, "   173");
    test("6Ro",   123, "   173");
    test("6Io",   123, "   173");
    test("6Lo",   123, "173   ");
    test("6=0o",  123, "000173");
    test("6R=0o", 123, "000173");
    test("6I=0o", 123, "000173");
    test("6L=0o", 123, "173000");
    test("6=xo",  123, "xxx173");
    test("6R=xo", 123, "xxx173");
    test("6I=xo", 123, "xxx173");
    test("6L=xo", 123, "173xxx");

    // Integers, negative, octal
    test("o",    (int16_t)-123, "177605");
    test("8o",   (int16_t)-123, "  177605");
    test("8Ro",  (int16_t)-123, "  177605");
    test("8Io",  (int16_t)-123, "  177605");
    test("8Lo",  (int16_t)-123, "177605  ");
    test("8=0o", (int16_t)-123, "00177605");
    test("8R=0o",(int16_t)-123, "00177605");
    test("8I=0o",(int16_t)-123, "00177605");
    test("8L=0o",(int16_t)-123, "17760500");
    test("8=xo", (int16_t)-123, "xx177605");
    test("8R=xo",(int16_t)-123, "xx177605");
    test("8I=xo",(int16_t)-123, "xx177605");
    test("8L=xo",(int16_t)-123, "177605xx");

    // Integers, positive, octal, alternate (prefix)
    test("#o",     123, "0173");
    test("#6o",    123, "  0173");
    test("#6Ro",   123, "  0173");
    test("#6Io",   123, "  0173");
    test("#6Lo",   123, "0173  ");
    test("#6=0o",  123, "000173");
    test("#6R=0o", 123, "000173");
    test("#6I=0o", 123, "000173");
    test("#6L=0o", 123, "017300");
    test("#6=xo",  123, "xx0173");
    test("#6R=xo", 123, "xx0173");
    test("#6I=xo", 123, "xx0173");
    test("#6L=xo", 123, "0173xx");

    // Integers, positive, hexadecimal
    test("x",     123, "7b");
    test("6x",    123, "    7b");
    test("6Rx",   123, "    7b");
    test("6Ix",   123, "    7b");
    test("6Lx",   123, "7b    ");
    test("6=0x",  123, "00007b");
    test("6R=0x", 123, "00007b");
    test("6I=0x", 123, "00007b");
    test("6L=0x", 123, "7b0000");
    test("6=xx",  123, "xxxx7b");
    test("6R=xx", 123, "xxxx7b");
    test("6I=xx", 123, "xxxx7b");
    test("6L=xx", 123, "7bxxxx");

    // Integers, negative, hexadecimal
    test("x",    (int16_t)-123, "ff85");
    test("8x",   (int16_t)-123, "    ff85");
    test("8Rx",  (int16_t)-123, "    ff85");
    test("8Ix",  (int16_t)-123, "    ff85");
    test("8Lx",  (int16_t)-123, "ff85    ");
    test("8=0x", (int16_t)-123, "0000ff85");
    test("8R=0x",(int16_t)-123, "0000ff85");
    test("8I=0x",(int16_t)-123, "0000ff85");
    test("8L=0x",(int16_t)-123, "ff850000");
    test("8=xx", (int16_t)-123, "xxxxff85");
    test("8R=xx",(int16_t)-123, "xxxxff85");
    test("8I=xx",(int16_t)-123, "xxxxff85");
    test("8L=xx",(int16_t)-123, "ff85xxxx");

    // Integers, positive, hexadecimal, alternate (prefix)
    test("#x",     123, "0x7b");
    test("p",      123, "0x7b");
    test("#6x",    123, "  0x7b");
    test("#6Rx",   123, "  0x7b");
    test("#6Ix",   123, "0x  7b");
    test("#6Lx",   123, "0x7b  ");
    test("#6=0x",  123, "000x7b");
    test("#6R=0x", 123, "000x7b");
    test("#6I=0x", 123, "0x007b");
    test("#6L=0x", 123, "0x7b00");
    test("#6=xx",  123, "xx0x7b");
    test("#6R=xx", 123, "xx0x7b");
    test("#6I=xx", 123, "0xxx7b");
    test("#6L=xx", 123, "0x7bxx");

    // Integers, negative, hexadecimal, capitals
    test("X",    (int16_t)-123, "FF85");
    test("8X",   (int16_t)-123, "    FF85");
    test("8RX",  (int16_t)-123, "    FF85");
    test("8IX",  (int16_t)-123, "    FF85");
    test("8LX",  (int16_t)-123, "FF85    ");
    test("8=0X", (int16_t)-123, "0000FF85");
    test("8R=0X",(int16_t)-123, "0000FF85");
    test("8I=0X",(int16_t)-123, "0000FF85");
    test("8L=0X",(int16_t)-123, "FF850000");
    test("8=xX", (int16_t)-123, "xxxxFF85");
    test("8R=xX",(int16_t)-123, "xxxxFF85");
    test("8I=xX",(int16_t)-123, "xxxxFF85");
    test("8L=xX",(int16_t)-123, "FF85xxxx");

    // Integers, positive, hexadecimal, alternate (prefix), capitals
    test("#X",     123, "0X7B");
    test("#6X",    123, "  0X7B");
    test("#6RX",   123, "  0X7B");
    test("#6IX",   123, "0X  7B");
    test("#6LX",   123, "0X7B  ");
    test("#6=0X",  123, "000X7B");
    test("#6R=0X", 123, "000X7B");
    test("#6I=0X", 123, "0X007B");
    test("#6L=0X", 123, "0X7B00");
    test("#6=xX",  123, "xx0X7B");
    test("#6R=xX", 123, "xx0X7B");
    test("#6I=xX", 123, "0Xxx7B");
    test("#6L=xX", 123, "0X7Bxx");

    // Floats, fixed
    test("f", 12.3, "12.300000");
    test("+f", 12.3, "+12.300000");
    test("12+f",  12.3, "  +12.300000");
    test("12R+f", 12.3, "  +12.300000");
    test("12I+f", 12.3, "+  12.300000");
    test("12L+f", 12.3, "+12.300000  ");
    test(".2f",  12.3, "12.30");
    test(".2+f", 12.3, "+12.30");
    test("12.2+f",  12.3, "      +12.30");
    test("12.2R+f", 12.3, "      +12.30");
    test("12.2I+f", 12.3, "+      12.30");
    test("12.2L+f", 12.3, "+12.30      ");

    // Floats, scientific
    test("e", 12.3, "1.230000e+01");
    test("+e", 12.3, "+1.230000e+01");
    test("15+e",  12.3, "  +1.230000e+01");
    test("15R+e", 12.3, "  +1.230000e+01");
    test("15I+e", 12.3, "+  1.230000e+01");
    test("15L+e", 12.3, "+1.230000e+01  ");
    test(".2e",  12.3, "1.23e+01");
    test(".2+e", 12.3, "+1.23e+01");
    test("12.2+e",  12.3, "   +1.23e+01");
    test("12.2R+e", 12.3, "   +1.23e+01");
    test("12.2I+e", 12.3, "+   1.23e+01");
    test("12.2L+e", 12.3, "+1.23e+01   ");

    // Floats, scientific, capitals
    test("E", 12.3, "1.230000E+01");
    test("+E", 12.3, "+1.230000E+01");
    test("15+E",  12.3, "  +1.230000E+01");
    test("15R+E", 12.3, "  +1.230000E+01");
    test("15I+E", 12.3, "+  1.230000E+01");
    test("15L+E", 12.3, "+1.230000E+01  ");
    test(".2E",  12.3, "1.23E+01");
    test(".2+E", 12.3, "+1.23E+01");
    test("12.2+E",  12.3, "   +1.23E+01");
    test("12.2R+E", 12.3, "   +1.23E+01");
    test("12.2I+E", 12.3, "+   1.23E+01");
    test("12.2L+E", 12.3, "+1.23E+01   ");


    // Bools
    test("b", true, "true");
    test("b", false, "false");
    test("10b", true, "      true");
    test("10Rb", true, "      true");
    test("10Ib", true, "      true");
    test("10Lb", true, "true      ");

    // Strings
    test("s",    "hello", "hello");
    test("10s",  "hello", "     hello");
    test("10Rs", "hello", "     hello");
    test("10Is", "hello", "     hello");
    test("10Ls", "hello", "hello     ");
    test("==10s",  "hello", "=====hello");
    test("==10Rs", "hello", "=====hello");
    test("==10Is", "hello", "=====hello");
    test("==10Ls", "hello", "hello=====");

    if (haserr)
        return 1;

    // Floats, hex
    std::cerr << "Warning: LLVM's libc++ & GNU's libstdc++ don't support hexfloat" << std::endl;
    test("a",  12.5, "0x1.9p+3");
    test("+a", 12.5, "+0x1.9p+3");
    test("12+a",  12.5, "   +0x1.9p+3");
    test("12+Ra", 12.5, "   +0x1.9p+3");
    test("12+Ia", 12.5, "+0x   1.9p+3");
    test("12+La", 12.5, "+0x1.9p+3   ");

    std::cout << out.str();
    return 0;
}
