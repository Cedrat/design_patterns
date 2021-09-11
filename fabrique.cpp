#include <string>
#include <iostream>

class IArmy
{
    public :
    virtual ~IArmy(){}
    virtual std::string moving() const = 0;
};

class EarthArmy : public IArmy
{
    std::string moving() const
    {
        return ("EarthArmy use tanks for moving !!");
    }
};

class WaterArmy : public IArmy
{
    std::string moving() const
    {
        return ("WaterArmy use submarines for moving !!");
    }
};

class AGenerator
{
    public :
        virtual ~AGenerator(){};
        virtual IArmy *ArmyGenerator(std::string) const = 0;
};

class ConcreteCreator : public AGenerator
{
    IArmy* ArmyGenerator(std::string army) const
    {
        if (army == "earth")
            return (new EarthArmy);
        else if (army == "water")
            return (new WaterArmy);
        throw("No army created");
    }
};

int main()
{
    AGenerator *generator = new ConcreteCreator;
    IArmy * army1 = generator->ArmyGenerator("earth");
    IArmy * army2 = generator->ArmyGenerator("water");


    std::cout << army1->moving() << std::endl;
    std::cout << army2->moving() << std::endl;

    delete generator;
    delete army1;
    delete army2;
}
