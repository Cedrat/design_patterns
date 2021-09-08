#include <string>
#include <iostream>

class Vehicule {
    public :
        virtual ~Vehicule()
        {}
        virtual std::string operation() const = 0;
};

class Bus : public Vehicule {
    public :
        std::string operation() const{
            return ("je transporte des gens\n");
        }
};

class Voyage : public Vehicule
{
    protected :
        Vehicule *_vehicule;
    
    public :
        Voyage(Vehicule *vehicule) : _vehicule(vehicule)
        {}

        std::string operation() const{
            return (_vehicule->operation());
        }
};

class Paris : public Voyage
{
    public :
        Paris(Vehicule *vehicule) : Voyage(vehicule)
        {}
    std::string operation() const
    {
        return (Voyage::operation() + "\n Jusqu'a Paris \n");
    }
};

class Tokyo : public Voyage
{
    public :
        Tokyo(Vehicule *vehicule) : Voyage(vehicule)
        {}
    std::string operation() const
    {
        return (Voyage::operation() + "\n Jusqu'a Tokyo \n");
    }
};

class Moscou : public Voyage
{
    public :
        Moscou(Vehicule *vehicule) : Voyage(vehicule)
        {}
    std::string operation() const
    {
        return (Voyage::operation() + "\n Jusqu'a Moscou \n");
    }
};





int main()
{
    {
        Vehicule *bus = new Bus;
        Vehicule *bus_pour_paris = new Paris(bus);
        Vehicule *bus_pour_tokyo_apres_paris = new Tokyo(bus_pour_paris);

        std::cout << bus_pour_tokyo_apres_paris->operation() << std::endl;
        
        delete bus;
        delete bus_pour_paris;
        delete bus_pour_tokyo_apres_paris;
    }
    {
        Vehicule *bus = new Bus;
        Vehicule *bus_pour_tokyo = new Tokyo(bus);
        Vehicule *bus_pour_paris_apres_tokyo = new Paris(bus_pour_tokyo);

        std::cout << bus_pour_paris_apres_tokyo->operation() << std::endl;

        delete bus;
        delete bus_pour_tokyo;
        delete bus_pour_paris_apres_tokyo;
    }
    {
        Vehicule *bus = new Bus;
        Vehicule *bus_pour_moscou = new Moscou(bus);
        Vehicule *bus_pour_moscou_apres_moscou = new Moscou(bus_pour_moscou);

        std::cout << bus_pour_moscou_apres_moscou->operation() << std::endl;

        delete bus;
        delete bus_pour_moscou;
        delete bus_pour_moscou_apres_moscou;
    }
}
