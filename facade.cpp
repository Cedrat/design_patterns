#include <iostream>
#include <string>

class SubSystem1
{
    public :
        std::string Operation1() const
        {
            return ("Subsystem 1: Ready !\n");
        }
        std::string OperationN() const
        {
                return ("Subsystem 1: Neutralize !\n");
        }
};

class SubSystem2
{
        private : 
            std::string _weapon;
    public :
        SubSystem2() : _weapon("filet") {};
        SubSystem2(std::string weapon) : _weapon(weapon) {};
        std::string Operation1() const
        {
            return ("Subsystem 2: Prepare the " + _weapon + " !\n");
        }
        std::string OperationK() const
        {
            return ("Subsystem 2: Launch the " + _weapon + " !\n");
        }
};

class InterfaceForCapture
{
    protected :
        SubSystem1 *_subsystem1;
        SubSystem2 *_subsystem2;

    public :
        InterfaceForCapture(SubSystem1 *subsystem1 = nullptr, SubSystem2 *subsystem2 = nullptr) 
        {
            if (subsystem1 == nullptr)
                _subsystem1 = new SubSystem1;
            else
            {
                _subsystem1 = subsystem1;
            }
            if (subsystem2 == nullptr)
                _subsystem2 = new SubSystem2;
             else
            {
                _subsystem2 = subsystem2;
            }

        }
        ~InterfaceForCapture()
        {
            delete _subsystem1;
            delete _subsystem2;
        }

        std::string Operation() const
        {
            std::string list_operations;
            list_operations += _subsystem1->Operation1();
            list_operations += _subsystem2->Operation1();
            list_operations += _subsystem1->OperationN();
            list_operations += _subsystem2->OperationK();
            return (list_operations);
        }
};

int main()
{
    {
        InterfaceForCapture *capture = new InterfaceForCapture();
        
        std::cout << capture->Operation() << std::endl;
        
        delete capture;
    }
    {
        SubSystem1 *subsystem1 = new SubSystem1;
        SubSystem2 *subsystem2 = new SubSystem2("bed");
        InterfaceForCapture *capture = new InterfaceForCapture(subsystem1, subsystem2);
        
        std::cout << capture->Operation() << std::endl;

        delete capture;
    }


}