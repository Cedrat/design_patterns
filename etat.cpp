#include <iostream>
#include <string>

class Human;

class State
{
    protected :
        Human *_human;
    
    public :
        virtual ~State(){};

        void setHuman(Human *human)
        {
            this->_human = human;
        }

        virtual void dream() = 0;
        virtual void read() = 0;
        virtual std::string describeState() = 0;

};

class Human
{
    private :
        State *_state;

    public :
        Human(State *state) : _state(nullptr)
        {
            transitionTo(state);
        }
        ~Human()
        {
            delete _state;
        };
        void transitionTo(State *state)
        {
            std::cout << "Transition to " << state->describeState() << std::endl;
            if (_state != nullptr)
            {
                delete _state;
            }
            _state = state;
            _state->setHuman(this);
        }
        void dream()
        {
            _state->dream();
        }
        void read()
        {
            _state->read();
        }
};

class DreamState : public State
{
    public :
        void read()
        {
            std::cout << "You can't  read, you are sleeping." << std::endl;
        }
        std::string describeState()
        {
            return "You are sleeping !";
        }

        void dream();
};

class AwakeState : public State
{
    public :
        void dream()
        {
            std::cout << "You can't dream, you are awake ! " << std::endl;
        }
        void read()
        {
            std::cout << "You read a lot, see magnificent adventures ! You are tired and going to sleep !" << std::endl;
            _human->transitionTo(new DreamState);
        }
        std::string describeState()
        {
            return "You are awake !";
        }
};

void DreamState::dream()
{
    std::cout << "you dreamed about beautifull pigs ! and.. a wolf.. ! You get out of your sleep" << std::endl;
    _human->transitionTo(new AwakeState);
}

int main()
{
    Human *human = new Human(new DreamState);

    human->read();
    human->dream();
    human->dream();
    human->read();

    delete human;
}