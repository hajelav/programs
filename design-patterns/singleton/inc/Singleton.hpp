#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>

using namespace std;
class Singleton
{
public:
    // Delete copy constructor and assignment operator
    Singleton(const Singleton &) = delete;
    /** Delete assignment operator */
    Singleton &operator=(const Singleton &) = delete;

    static unique_ptr<Singleton> instance;
    Singleton() {}

    static Singleton &getInstance()
    {
        if (!instance)
        {
            instance = make_unique<Singleton>();
        }
        return *instance;
    }
};

unique_ptr<Singleton> Singleton::instance = nullptr;

#endif // SINGLETON_HPP
