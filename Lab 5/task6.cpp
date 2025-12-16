#include <iostream>
#include <string>
using namespace std;

class CVehicle {
public:
    CVehicle(string vType, string vMake, string vModel, int vYear, float vMaxSpeed, int vPassengerCapacity, string vColor)
        : type(vType), make(vMake), model(vModel), year(vYear), maxSpeed(vMaxSpeed), passengerCapacity(vPassengerCapacity), color(vColor) {}

    void setType(string newType) {
        type = newType;
    }  
    string getType() {
        return type;
    }
    void setMake(string newMake) {
        make = newMake;
    }
    string getMake() {
        return make;
    }
    void setModel(string newModel) {
        model = newModel;
    }
    string getModel() {
        return model;
    }
    void setYear(int newYear) { 
        year = newYear;
    }
    int getYear() {
        return year;
    }
    void setMaxSpeed(float newMaxSpeed) {
        maxSpeed = newMaxSpeed;
    }
    int getMaxSpeed() {
        return maxSpeed;
    }
    void setPassengerCapacity(int newCapacity) {
        passengerCapacity = newCapacity;
    }  
    int getPassengerCapacity() {
        return passengerCapacity;
    }
    void setColor(string newColor) {
        color = newColor;
    }
    string getColor() {
        return color;
    }

    void setData(string vType, string vMake, string vModel, int vYear, float vMaxSpeed, int vPassengerCapacity, string vColor) {
        type = vType;
        make = vMake;
        model = vModel;
        year = vYear;
        maxSpeed = vMaxSpeed;
        passengerCapacity = vPassengerCapacity;
        color = vColor;
    }

    void displayInfo() {
        cout << "Vehicle Type: " << type << endl;
        cout << "Make: " << make << endl;
        cout << "Model: " << model << endl;
        cout << "Year: " << year << endl;
        cout << "Max Speed: " << maxSpeed << " km/h" << endl;
        cout << "Passenger Capacity: " << passengerCapacity << endl;
        cout << "Color: " << color << endl;
    }

private: 
    string type;
    string make;
    string model;
    int year;
    float maxSpeed;
    int passengerCapacity;
    string color;
};

void swapColors(CVehicle &v1, CVehicle &v2) {
    string tempColor = v1.getColor();
    v1.setColor(v2.getColor());
    v2.setColor(tempColor);
}

int main() {
    CVehicle car1("Car", "Land Rover", "Defender", 1999, 180.0, 5, "Green");
    CVehicle car2("Car", "Honda", "Civic", 2019, 200.0, 5, "Blue");

    cout << "Before swapping colors:" << endl;
    car1.displayInfo();
    cout << endl;
    car2.displayInfo();
    cout << endl;

    swapColors(car1, car2);

    cout << "After swapping colors:" << endl;
    car1.displayInfo();
    cout << endl;
    car2.displayInfo();
    cout << endl;

    return 0;
}