#include <string>
#include <iostream>
#include <thread> //code c++11, adaptable to cpp 98 using C functions.

class Singleton
{
    private :
        static Singleton    *_pinstance;
        static std::mutex   _mutex;
        std::string         _value;
        Singleton(const std::string value) : _value(value) {}
        ~Singleton();

        Singleton(Singleton &rhs) {}; // Singleton should not be cloneable
        void operator=(const Singleton & rhs) {}; // Singleton should not be assignable.

    public :
        static Singleton *GetInstance(const std::string & value)
        {
            std::lock_guard<std::mutex> lock(_mutex); //block during the time of using the functions.
            if (_pinstance == nullptr)
            {
                _pinstance = new Singleton(value);
            }
            return (_pinstance);
        }

        std::string const & getValue() const
        {
            return (_value);
        }
};

Singleton *Singleton::_pinstance = nullptr;
std::mutex Singleton::_mutex;

void first()
{

    Singleton *singleton = singleton->GetInstance("I'm the first NANANANANNA");
    std::cout << singleton->getValue() << std::endl;
}

void second()
{

    Singleton *singleton = singleton->GetInstance("No, it's me the first lalalala");
    std::cout << singleton->getValue() << std::endl;
}


int main()
{
    std::cout << "only one first can exist,\n" << 
     "if two peoples says different things, it's a lie and singleton does'nt work" << std::endl;

     std::thread t1(first);
     std::thread t2(second);
    t1.join();
    t2.join();
}