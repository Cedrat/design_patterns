#include <string>
#include <iostream>


class IColor
{
    public :
        virtual ~IColor() {};
        virtual std::string description() const = 0;
};

class Red : public IColor
{
    public : 
        Red(){};
        ~Red(){};

        std::string description() const
        {
            return ("red");
        }
};

class Blue : public IColor
{
    public : 
        Blue(){};
        ~Blue(){};

        std::string description() const
        {
            return ("blue");
        }
};
class IShape 
{
    public:
        virtual ~IShape() {};
        virtual std::string description() const = 0;
};

class Square : public IShape
{
    private : 
        IColor &_color;
    public :
        Square(IColor &color) : _color(color) {};
        ~Square() {} ;

        std::string description() const
        {
            return ("it's a beautifull " + _color.description() + " square");
        }
};

class Circle : public IShape
{
    private : 
        IColor &_color;
    public :
        Circle(IColor &color) : _color(color) {};
        ~Circle() {} ;

        std::string description() const
        {
            return ("it's a beautifull " + _color.description() + " circle");
        }
};

int main()
{
    IColor * red =  new Red();
    IShape * square = new Square(*red);
    IShape * circle = new Circle(*red);
    IColor * blue = new Blue();
    IShape * square2 = new Square(*blue);

    std::cout << square->description() << std::endl;
    std::cout << square2->description() << std::endl;
    std::cout << circle->description() << std::endl;

    delete red;
    delete square;
    delete circle;
    delete blue;
    delete square2;
}