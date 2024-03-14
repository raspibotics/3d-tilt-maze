#include "mbed.h"
#include "Vector3.h"
#include <iostream>

// main() runs in its own thread in the OS
int main() {
    Vector3 v = {3,4,5};
    std::cout << "Vector before rotation: " << "\n";
    v.print();
    std::cout << "\n";

    Vector3 axis = {2,3,4};
    std::cout << "Vector after rotation around axis ";
    axis.print();
    std::cout << "\n";

    v.rotate(21.0, {5,4,3});
    v.print();

}

