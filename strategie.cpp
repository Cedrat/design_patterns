#include <string>
#include <iostream>

class IStrategy
{
    public : 
        virtual ~IStrategy(){};
        virtual void exec(std::string str) = 0;
};

class ReadString
{
    private :
        IStrategy *_strategy;

    public :
        ReadString(IStrategy *strategy = nullptr) : _strategy(strategy)
        {

        }
        ~ReadString()
        {
            if (_strategy != nullptr)
                delete _strategy;
        }
        void setStrategy(IStrategy *strategy)
        {
            if (_strategy != nullptr)
                delete _strategy;
            _strategy = strategy;
        }

        void read(std::string str)
        {
            _strategy->exec(str);
        }
};

class Strat1 : public IStrategy
{
    public : 
        void exec(std::string str)
        {
            std::cout << "We are doing the first strategy ! " << std::endl;
            std::cout << str << std::endl;
        }
        
};

class Strat2 : public IStrategy
{
    public :
        void exec(std::string str)
        {
            std::cout << "We are doing the second strategy ! " << std::endl;
            std::string::reverse_iterator rit_begin = str.rbegin(); 
            while (rit_begin != str.rend())
            {
                std::cout << *rit_begin;
                rit_begin++;
            }
            std::cout << std::endl;
        }
};

int main()
{
    ReadString reader(new Strat2);

    reader.read("now step live...");
    reader.setStrategy(new Strat1);
    reader.read("now step live...");
}