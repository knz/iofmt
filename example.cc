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
