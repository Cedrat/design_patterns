#include <string>
#include <list>
#include <iostream>

class Component
{
    protected :
        Component *_parent;

    public :
        virtual ~Component(){};
        void setParent(Component *parent)
        {
            _parent = parent;
        }
        Component *getParent() const
        {
            return (_parent);
        }
        virtual void add(Component *component) {}
        virtual void remove(Component *component) {}
        virtual bool isComposite() const
        {
            return (false);
        }
        virtual std::string operation() const = 0;
};

class Leaf : public Component
{
    std::string operation() const
    {
        return ("Leaf");
    }
};

class Branch : public Component
{

    protected :
        std::list<Component *> _children;

    public :
        void add(Component *component)
        {
            _children.push_back(component);
            component->setParent(this);
        }
        void remove(Component *component)
        {
            _children.remove(component);
            component->setParent(nullptr);
        }
        bool isComposite() const
        {
            return (true);
        }
        std::string operation() const
        {
            std::string result;
            for (Component* component : _children)
            {
                if (component == _children.back())
                {
                    result += component->operation();
                }
                else
                {
                    result += component->operation() + "+";
                }
            }
            return ("Branch(" + result + ")");
        }
};

int main()
{
    Component *leaf1 = new Leaf;
    Component *leaf2 = new Leaf;
    Component *leaf3 = new Leaf;
    Component *leaf4 = new Leaf;

    Component *branch1 = new Branch;
    Component *branch2 = new Branch;
    Component *branch3 = new Branch;
    Component *branch4 = new Branch;

    branch1->add(branch2);
    branch2->add(branch3);
    branch1->add(branch4);

    branch3->add(leaf1);
    branch3->add(leaf2);
    branch3->add(leaf3);
    branch1->add(leaf4);

    std::cout << branch1->operation() << std::endl;
    std::cout << branch3->operation() << std::endl;

    delete leaf1 ;
    delete leaf2 ;
    delete leaf3 ;
    delete leaf4 ;

    delete branch1 ;
    delete branch2 ;
    delete branch3 ;
    delete branch4 ;
}