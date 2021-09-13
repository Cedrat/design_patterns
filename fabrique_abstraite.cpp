#include <string>
#include <iostream>

class IToys
{
    public :
        virtual ~IToys(){};
        virtual std::string play() const = 0;
};

class CarToy : public IToys
{
    public :
        std::string play() const
        {
            return ("vroum vroummmm, let the dinosaur cross !!");
        }
};

class PhoneToy : public IToys
{
    public :
        std::string play() const
        {
            return ("Hello, hello, he didn't give priority to the dinosaur !! ");
        }
};

class IObjects
{
    public :
        virtual ~IObjects() {};
        virtual std::string use() const = 0;
};

class RealCar : public IObjects
{
    public:
        std::string use () const
        {
            return ("Honey, you have to take the kid to school !");
        }
};

class RealPhone : public IObjects
{
    public :
        std::string use() const
        {
            return ("Honeeyyyy, what de you want to eat tonight ?");
        }
};


class IGenerator
{
    public :
        virtual ~IGenerator() {};
        virtual IToys       *createToys() const = 0;
        virtual IObjects    *createObjects() const = 0;
};

class CarGenerator : public IGenerator
{
    public :
        IToys *createToys() const
        {
            return (new CarToy);
        }
        IObjects *createObjects() const
        {
            return (new RealCar);
        }
};

class PhoneGenerator : public IGenerator
{
    public :
        IToys *createToys() const
        {
            return (new PhoneToy);
        }
        IObjects *createObjects() const
        {
            return (new RealPhone);
        }
};

void try_generator(IGenerator *generator)
{
    IObjects * object = generator->createObjects();
    IToys * toy = generator->createToys();

    std::cout << "What does this factory product ?!\n"
    << object->use() << "\n" << toy->play() << "\n" << std::endl;
        
    delete object;
    delete toy;
}

int main()
{
    IGenerator *generator_1 = new CarGenerator;
    IGenerator *generator_2 = new PhoneGenerator;

    std::cout << "try the first generator!\n" << std::endl;
    try_generator(generator_1);

    std::cout << "try the second generator!\n" << std::endl;
    try_generator(generator_2);
   
    delete generator_1;
    delete generator_2;
}
