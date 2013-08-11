#include "iofmt.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <stdint.h>

const char ttab[] = "oxXdbBfFeEgGaA";
const char* xtab[] = { "", "#" };
const char* atab[] = { "", "R", "L", "-", "I" };
const char* wtab[] = { "", "0", "10" };
const char* stab[] = { "", "==" };
const char* ntab[] = { "", ".0", ".4" };
const char* ptab[] = { "", "+" };

#define SZ(tab) sizeof(tab) / sizeof(tab[0])

void test(size_t t, size_t x, size_t a, size_t w, size_t s, size_t n, size_t p)
{
    if (n > 0 && t < 6)
        // precision is meaningless for non-floats
        return;
    if (s > 0 && a < 2)
        // padding char is meaningless without padding
        return;
    if (p > 0 && t < 3)
        // force sign is meaningless for o/x
        return;

    std::string sfmt;
    sfmt = sfmt + xtab[x] + atab[a] + wtab[w] + stab[s] + ntab[n] + ptab[p] + ttab[t];
    const char* cfmt = sfmt.c_str();

    std::cout << io::fmt("")
              << std::setw(10) << sfmt << ' ';
    if (t < 4)
        std::cout << ':'
                  << io::fmt(cfmt) << (int16_t) 123
                  << ':'
                  << io::fmt(cfmt) << (int16_t)-123
                  << ':';
    else if (t < 6)
        std::cout << ':'
                  << io::fmt(cfmt) << true
                  << ':'
                  << io::fmt(cfmt) << false
                  << ':';
    else
        std::cout << ':'
                  << io::fmt(cfmt) << 12.3
                  << ':'
                  << io::fmt(cfmt) << -12.3
                  << ':';
    std::cout << std::endl;
}

int main()
{
    size_t t, a, p, w, s, x, n;
    for (t = 0; t < SZ(ttab) - 1; ++t)
        for (x = 0; x < SZ(xtab); ++x)
            for (a = 0; a < SZ(atab); ++a)
                for (w = 0; w < SZ(wtab); ++w)
                    for (s = 0; s < SZ(stab); ++s)
                        for (n = 0; n < SZ(ntab); ++n)
                            for (p = 0; p < SZ(ptab); ++p)
                                test(t, x, a, w, s, n, p);
    return 0;
}
