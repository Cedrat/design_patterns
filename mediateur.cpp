#include <string>
#include <iostream>
class BaseComponent;

class Mediator
{
    public :
        virtual void notify(BaseComponent *sender, std::string event) const = 0;
};

class BaseComponent
{
    protected :
        Mediator *_mediator;

    public :
        BaseComponent(Mediator *mediator = NULL) : _mediator(mediator)
        {

        }
        void set_mediator(Mediator *mediator)
        {
            this->_mediator = mediator;
        }
};

class Component1 : public BaseComponent
{
    public :
        void DoA()
        {
            std::cout << "Component1 do A: " << std::endl;
            this->_mediator->notify(this, "A");
        }
        void DoB()
        {
            std::cout << "Component1 do B:" << std::endl;
            this->_mediator->notify(this, "B");
        }
};

class Component2 : public BaseComponent
{
    public :
        void DoC()
        {
            std::cout << "Component2 do C: " << std::endl;
            this->_mediator->notify(this, "C");
        }
        void DoD()
        {
            std::cout << "Component2 do D:" << std::endl;
            this->_mediator->notify(this, "D");
        }
};

class ConcreteMediator : public Mediator
{
    private :
        Component1 *_component1;
        Component2 *_component2;

    public :
        ConcreteMediator(Component1 *c1, Component2 *c2) :
        _component1(c1), _component2(c2)
        {
            this->_component1->set_mediator(this);
            this->_component2->set_mediator(this);
        }

        void notify(BaseComponent *base_component, std::string event) const
        {
            if (event == "A")
            {
                this->_component2->DoC();
            }
            if (event == "C")
            {
                this->_component1->DoB();
                this->_component2->DoD();
            }
            if (event == "D")
            {
                this->_component1->DoB();
            }
        }
};

int main()
{
    Component1 *c1 = new Component1;
    Component2 *c2 = new Component2;
    ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
    std::cout << "c1 is going do to B" << std::endl;
    c1->DoB();
    std::cout << std::endl;
    std::cout << "c2 is going do to C" << std::endl;
    c2->DoC();
}

