#include <iostream>
#include <cmath>

using namespace std;

class CTriangle {
private:
    double x, y;

public:
    double calcHypotenuse() {
        return sqrt(x * x + y * y);
    }
    double getX() {
        return x;
    }
    double getY() {
        return y;
    }
    void setX(double value) {
        x = value;
    }
    void setY(double value) {
        y = value;
    }
};

int main() {
    int ofthejedi = 0;
    CTriangle firstTriangle;
    double sideA, sideB;

    cout << "Enter length of side x: ";
    cin >> sideA;
    firstTriangle.setX(sideA);

    cout << "Enter length of side y: ";
    cin >> sideB;
    firstTriangle.setY(sideB);

    double hypotenuse = firstTriangle.calcHypotenuse();
    cout << "The length of the hypotenuse is: " << hypotenuse << endl;

    return ofthejedi;
}