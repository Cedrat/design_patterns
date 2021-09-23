#include <string>
#include <iostream>
#include <unordered_map>
#include <initializer_list>


class SharedState
{
    public :
        std::string _brand;
        std::string _model;
        std::string _color;

        SharedState(std::string brand, std::string model, std::string color) :
        _brand(brand), _model(model), _color(color)
        {
        }

        friend std::ostream &operator<<(std::ostream &os, const SharedState &ss)
        {
            return (os << "[ " << ss._brand << ", " << ss._model << ", " << ss._color << " ]");
        }
};

class UniqueState
{
    public :
        std::string _owner;
        std::string _plates;

        UniqueState(const  std::string & owner, std::string const & plates) : 
        _owner(owner), _plates(plates)
        {            
        }

        friend std::ostream &operator<<(std::ostream &os, const UniqueState &us)
        {
            return (os << "[ " << us._owner << ", " << us._plates << " ]");
        }
};

class FlyWeigth
{
    private :
        SharedState *_shared_state;
    
    public :
        FlyWeigth(const SharedState *shared_state) : _shared_state(new SharedState(*shared_state))
        {
        }
        FlyWeigth(const FlyWeigth &other) : _shared_state(new SharedState(*other._shared_state))
        {    
        }
        ~FlyWeigth()
        {
            delete _shared_state;
        }
        SharedState *shared_state() const
        {
            return (_shared_state);
        }
        void Operation(const UniqueState &unique_state) const
        {
            std::cout << "Shared state : " << *_shared_state << "\nUnique state : " << unique_state << std::endl;
        }
};

class FlyWeigthFactory
{
    private : 

        std::unordered_map<std::string, FlyWeigth> _flyweigths;

        std::string getKey(SharedState const &ss) const
        {
            return (ss._brand + "_" + ss._model + "_" + ss._color);
        }
    public :
        FlyWeigthFactory(std::initializer_list<SharedState> shared_states)
        {
            for (SharedState const &ss : shared_states)
            {
                this->_flyweigths.insert(std::make_pair<std::string, FlyWeigth>(this->getKey(ss), FlyWeigth(&ss)));
            }
        }
        FlyWeigth getFlyWeigth(SharedState const &share_state)
        {
            std::string key = this->getKey(share_state);
            if (_flyweigths.find(key) == _flyweigths.end())
            {
                std::cout << "Creating new object because no one of this type, existed below" << std::endl;
                this->_flyweigths.insert(std::make_pair(key, FlyWeigth(&share_state)));
            }
            else
            {
                std::cout << "Objet already created, return it" << std::endl;
            }
            return (_flyweigths.at(key)); 
        }
        void listFlyWeigths() const
        {
            for (std::pair<std::string, FlyWeigth> pair : _flyweigths)
            {
                std::cout << pair.first << std::endl; 
            }
        }
};

void add_car_to_database(FlyWeigthFactory &ff, std::string const & plates ,std::string const & owner,
                        std::string const &brand,std::string const &model,std::string const & color)
{
    std::cout << "\nAdding a car to database" << std::endl;
    const FlyWeigth & flyweigth = ff.getFlyWeigth({brand, model, color});
    flyweigth.Operation({owner, plates});
}

int main()
{
    FlyWeigthFactory *factory = new FlyWeigthFactory({{"Chevrolet", "Camaro2018", "pink"}, 
                                                        {"Mercedes Benz", "C300", "black"}, 
                                                        {"Mercedes Benz", "C500", "red"}, 
                                                        {"BMW", "M5", "red"}, 
                                                        {"BMW", "X6", "white"}});
    factory->listFlyWeigths();

    add_car_to_database(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "M5",
                            "red");

    add_car_to_database(*factory,
                            "CL234IR",
                            "James Doe",
                            "BMW",
                            "X1",
                            "red");
    factory->listFlyWeigths();
    delete factory;

    return 0;
}