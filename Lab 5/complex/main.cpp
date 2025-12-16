#include <iostream>
#include "complex.h"

using namespace std;

int main() {
    Complex c1(4, 2);
    Complex c2(1, 3);

    Complex sum = c1 + c2;
    Complex diff = c1 - c2;
    Complex prod = c1 * c2;
    Complex quot = c1 / c2;

    cout << "Sum: " << sum.getReal() << " + " << sum.getImaginary() << "i\n";
    cout << "Difference: " << diff.getReal() << " + " << diff.getImaginary() << "i\n";
    cout << "Product: " << prod.getReal() << " + " << prod.getImaginary() << "i\n";
    cout << "Quotient: " << quot.getReal() << " + " << quot.getImaginary() << "i\n";

    return 0;
}
