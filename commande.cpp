#include <string>
#include <iostream>
#include <ctime>

class Command
{
    public :
        virtual ~Command(){};
        virtual void exec() = 0;
};

class Bet : public Command
{
    private :
        int _amount;

    public :
        Bet(int amount) : _amount(amount)
        {

        }
        ~Bet(){};

        void exec()
        {
            if (_amount <= 0)
            {
                std::cout << "Not any money for play" << std::endl;
            }
            else
            {
                std::srand(std::time(0));
                int amount_win = std::rand() % 3 - 1;
                std::cout << "you bet one : " <<std::endl;
                std::cout << "you win : " << amount_win << std::endl;
                std::cout << "you have now : " << _amount + amount_win << std::endl;
                _amount += amount_win;
            }
        }
};

class PurchaseProduct : public Command
{
    private :
        std::string _product_name;
        int _price;
        int _amount;

    public :
        PurchaseProduct(std::string product_name, int price, int amount) :
                     _product_name(product_name), _price(price),_amount(amount)
        {

        }
        ~PurchaseProduct(){};

        void exec()
        {
            if ((_amount - _price) < 0)
            {
                std::cout << "Not any money for buy " << _product_name << std::endl;
            }
            else
            {
                _amount -= _price;
                std::cout << "You buy " << _product_name << " for " << _amount << " , you still have " << _amount << std::endl; 
            }
        }
};


void human_life(Command *command)
{
    command->exec();
    command->exec();
    command->exec();
}

int main()
{
    Command *human_1 = new Bet(2);
    Command *human_2 = new PurchaseProduct("Pasta", 3, 7);

    human_life(human_1);
    human_life(human_2);

    delete human_1;
    delete human_2;
} 