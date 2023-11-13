#ifndef PROXY_IMAGE_H
#define CONCRETE_PROXY_IMAGE_H

#include "AbstractSubjectImage.hpp"
#include "RealSubjectImage.hpp"

#include <iostream>
#include <memory>

using namespace std;

class ProxyImage : public AbstractSubjectImage
{
private:
    string fileName;
    shared_ptr<RealSubjectImage> realImage;

public:
    ProxyImage(string fName) : fileName(fName) {
        cout << "Creating a proxy image object" << endl;
    }
    ~ProxyImage() {}

    void display() override {
        if(!realImage)
            //proxy is creating an object of real object and calling its display on behalf of client
            realImage = make_shared<RealSubjectImage>(fileName);
            realImage->display();
    }
};

#endif // !CONCRETE_PROXY_IMAGE_H