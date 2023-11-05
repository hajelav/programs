#include <iostream>

class Singleton {

    public:

    static Singleton* getInstance() {
        if(instance == nullptr) {
            instance = new Singleton();
        } else {
            return instance;
        }
        return instance;
    }

    private:
        //private constructor to prevent external instantiation
        Singleton() {}
        //private destructor to prevent external deletion
        ~Singleton() {}
        //private copy constructor and assignment operator to prevent copying
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;


        static Singleton* instance; 
};

Singleton* Singleton::instance = nullptr;

