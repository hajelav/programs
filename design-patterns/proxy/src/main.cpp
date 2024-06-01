/*
The Proxy Design Pattern is a structural pattern where a surrogate or placeholder object controls 
access to another object. This pattern is useful when you want to add an additional layer of control 
to manage access to an object. Below is an example of the Proxy Design
 Pattern using a virtual proxy for loading images lazily.
*/

#include "AbstractSubjectImage.hpp"
#include "RealSubjectImage.hpp"
#include "ProxyImage.hpp"

#include <memory>
#include <iostream>

int main(int argc, char const *argv[])
{
    //creating a real image object
    shared_ptr<AbstractSubjectImage>realImage = make_shared<RealSubjectImage>("Sample.jpg");
    realImage->display();

    //creating a proxy image object
    shared_ptr<AbstractSubjectImage> proxyImage = make_shared<ProxyImage>("Sample2.jpg");
    proxyImage->display();

    return 0;
}
