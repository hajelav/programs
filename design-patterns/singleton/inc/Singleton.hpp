#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <memory>

using namespace std;
class Singleton
{
private:
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;

    static unique_ptr<Singleton> instance;
    Singleton() {}

public:
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
