#include <string>
#include <iostream>
#include <ctime>

class Target
{
    public :
                 Target(){};
        virtual ~Target(){};
        virtual std::string getTime() const
        {
            struct tm* time_struct;
            time_t actual_time = std::time(nullptr);
            time_struct = localtime(&actual_time);
            return (std::to_string(time_struct->tm_hour)+":"+std::to_string(time_struct->tm_min));
        }
};

class Adaptee
{
    public :
        std::string SpecificRequest() const
        {
            return (std::to_string(std::time(0)));

        }
};

class Adapter : public Target, public Adaptee
{
    public :
        Adapter(){}
        std::string getTime() const
        {
            std::string to_convert = SpecificRequest();

            int hour = atoi(to_convert.c_str()) / 3600 % (24);
            int min = atoi(to_convert.c_str()) / 60 % 60;


            return (std::to_string(hour) + ":" + std::to_string(min));

        }
};


int main()
{
    Target basic;
    std::cout << "Basic comportement : " << basic.getTime() << std::endl;

    Adaptee strange;
    std::cout << "Strange Behavior : " << strange.SpecificRequest() << std::endl;

    Adapter adapter;
    std::cout << "Behavior translated : " << adapter.getTime() << std::endl;
}