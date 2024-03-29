#ifndef REAL_SUBJECT_IMAGE_H
#define REAL_SUBJECT_IMAGE_H

#include "AbstractSubjectImage.hpp"
#include <iostream>

using namespace std;

class RealSubjectImage : public AbstractSubjectImage
{
private:
    string fileName;
public:
    void display() override {
        cout << "Diplaying real image:" << fileName << endl;
    }
    void loadFromDisk() {
        cout << "Loading real image from disk:" << fileName << endl;
    }

    RealSubjectImage(string fName) : fileName(fName) {
        loadFromDisk();
    }
    ~RealSubjectImage() {}
};

#endif // !REAL_SUBJECT_IMAGE_H