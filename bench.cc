#include "iofmt.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <boost/format.hpp>
#include <unistd.h>

using namespace std;

volatile bool done = false;
void handler(int n)
{
    done = true;
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        cerr << "usage: " << argv[0] << " <seconds> [boost | boostc | iofmt | plain]" << endl;
        return 1;
    }

    int seconds = atoi(argv[1]);
    signal(SIGALRM, &handler);
    alarm(seconds);

    ostringstream os;
    int i;

    if (!strcmp(argv[2], "boost"))
    {
        for (i = 0; !done; ++i)
            os << boost::format("%1%") % 123;
    }
    else if (!strcmp(argv[2], "boostc"))
    {
        boost::format fmter("%1%");
        for (i = 0; !done; ++i)
            os << boost::format(fmter) % 123;
    }
    else if (!strcmp(argv[2], "iofmt"))
    {
        for (i = 0; !done; ++i)
            os << io::fmt("d") << 123;
    }
    else if (!strcmp(argv[2], "plain"))
    {
        for (i = 0; !done; ++i)
            os << 123;
    }
    else
    {
        cerr << "unrecognized argument: " << argv[2] << endl;
        return 1;
    }

    cout << i << " ints formatted (" << os.str().size() << " bytes) in " << seconds
         << "s = " << fixed << setprecision(1) << (float)i/(float)seconds << " io/s" << endl;

    return 0;
}
