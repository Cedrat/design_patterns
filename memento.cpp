#include <string>
#include <ctime>
#include <iostream>
#include <vector>

class Memento
{
    public :
        virtual std::string getName() const = 0;
        virtual std::string date() const = 0;
        virtual std::string state() const = 0;
};

class ConcreteMemento : public Memento
{
    private :
        std::string _state;
        std::string _date;

    public :
        ConcreteMemento(std::string state) :  _state(state)
        {
            this->_state = state;
            std::time_t now = std::time(0);
            this->_date = ctime(&now);
        }
        std::string getName() const
        {
            return this->_date + " / (" + this->_state.substr(0, 9) + "...)";
        }
        std::string state() const
        {
            return _state;
        }
        std::string date() const
        {
            return _date;
        }
};

class Originator
{
    private :
        std::string _state;

    public :
        Originator(std::string state) : _state(state)
        {
            std::cout << "My initial state is " << _state << std::endl;
        }
        std::string generateRandomString(int length = 10)
        {
            const char alphanum[] =
                        "0123456789"
                        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                        "abcdefghijklmnopqrstuvwxyz";
            
            std::string random_string;
            for (int i = 0; i < length; i++)
            {
                random_string += alphanum[std::rand() % 63];
            }
            return (random_string);
        }
        void doSomething()
        {
            std::cout << "Originator: I'm doing something important.\n";
            this->_state = this->generateRandomString(30);
            std::cout << "Originator: and my state has changed to: " << this->_state << std::endl;
        }

        Memento *save()
        {
            return (new ConcreteMemento(this->_state));
        }

        void restore(Memento *memento)
        {
            this->_state = memento->state();
            std::cout << "Originator: My state has changed to: " << this->_state << std::endl;
        }
};

class CareTaker
{
    private :
        std::vector<Memento *>_mementos;
        Originator *_originator;
    
    public :
        CareTaker(Originator *originator) : _originator(originator)
        {
            this->_originator = originator;
        }
        void backUp()
        {
            std::cout << "Backup for originator !" << std::endl;
            _mementos.push_back(_originator->save());
        }
        void undo()
        {
            if (_mementos.empty())
            {
                std::cout << "No save available" << std::endl;
                return;
            }
            Memento *memento = _mementos.back();
            _mementos.pop_back();
            std::cout << "Caretaker : Restoring state to " << memento->getName() << std::endl;
            try
            {
                _originator->restore(memento);
            }
            catch(...)
            {
        		std::cout << "Problem with this save, go to the previous" << std::endl;
                undo();
            }
            
        }
        void ShowHistory() const 
        {
            std::cout << "Caretaker: Here's the list of mementos:\n";
            for (Memento *memento : this->_mementos) 
            {
                std::cout << memento->getName() << "\n";
            }
        }
};


void ClientCode() 
{
    Originator *originator = new Originator("Original state");
    CareTaker *caretaker = new CareTaker(originator);
    caretaker->backUp();
    originator->doSomething();
    caretaker->backUp();
    originator->doSomething();
    caretaker->backUp();
    originator->doSomething();
    std::cout << "\n";
    caretaker->ShowHistory();
    std::cout << "\nClient: Now, let's rollback!\n\n";
    caretaker->undo();
    std::cout << "\nClient: Once more!\n\n";
    caretaker->undo();

    delete originator;
    delete caretaker;
}

int main() 
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    ClientCode();
    return 0;
}