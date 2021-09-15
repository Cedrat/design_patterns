#include <string>
#include <iostream>
#include <map>
class Prototype
{
    private :
        std::string _name;
        int         _field;

    public :
        Prototype(){}
        Prototype(std::string name) : _name(name){}
        virtual ~Prototype() {}
        
        virtual Prototype *clone() const = 0;
        virtual void setField(int field)
        {
            _field = field;
            std::cout << "Set field from " << _name << " with field: " << _field << std::endl;
        }
};

class ConcretePrototype1 : public Prototype
{
    private:
        int _field1;
    
    public :
        ConcretePrototype1(std::string name, int field) : Prototype(name) , _field1(field) {}

        Prototype *clone() const
        {
            return (new ConcretePrototype1(*this));
        }
};

class ConcretePrototype2 : public Prototype
{
    private:
        int _field2;
    
    public :
        ConcretePrototype2(std::string name, int field) : Prototype(name) , _field2(field) {}

        Prototype *clone() const
        {
            return (new ConcretePrototype2(*this)); 
        }
};

class PrototypeFactory
{
    private :
        std::map<int, Prototype *> _prototypes;

    public :
        PrototypeFactory() 
        {
            _prototypes[0] = new ConcretePrototype1("The beta prototype", 5);
            _prototypes[1] = new ConcretePrototype2("The real prototype", 10);
        }

        ~PrototypeFactory()
        {
            delete _prototypes[0];
            delete _prototypes[1];
        }

        Prototype * createPrototype(int i)
        {
            return (_prototypes[i]->clone());
        }
};

int main()
{
    PrototypeFactory *factory = new PrototypeFactory();

    Prototype *first = factory->createPrototype(0);
    Prototype *second = factory->createPrototype(1);
    Prototype *unknow = first->clone();

    std::cout << "Use the first :"  << std::endl;
    first->setField(10);
    std::cout << "Use the second :"  << std::endl;
    second->setField(20);

    std::cout << "Use the unknow :"  << std::endl;
    second->setField(20);

    delete first;
    delete second;
    delete unknow;
}