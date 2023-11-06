/* Vendor classes defined in this folder*/
#ifndef LIGHTS_H
#define LIGHTS_H

#include <iostream>

using namespace std;
class Lights {

    public:
        void on() {
            cout << "lights have turned on" << endl;
        }

        void off() {
            cout << "Lights have turned off" << endl;
        }
};

#endif /* LIGHTS_H */
