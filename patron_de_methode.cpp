#include <string>
#include <iostream>

/*
The recipes used for the pizzas were well distorted.
Once again.. sorry.
*/

class Pizza 
{
    public :
        virtual ~Pizza() {};
        void recipe() const
        {
            pizzaCrust();
            pizzaBase();
            mainIngredient();
            facultativeIngredient();
            cook();
        }
    protected: 
        virtual void pizzaBase() const = 0;
        virtual void mainIngredient() const = 0;

        void pizzaCrust() const
        {
            std::cout << "We have only one crust, go take it !" << std::endl;
        }

        void facultativeIngredient() const {};

        void cook() const
        {
            std::cout << "Let's cook the pizza !" << std::endl;
        }
};

class PizzaCannibal : public Pizza
{
    protected :
        void pizzaBase() const
        {
            std::cout << "Add sour cream base !" << std::endl;
        }
        void mainIngredient() const
        {
            std::cout << "Add one steak or two." << std::endl;
        }

        void facultativeIngredient() const
        {
            std::cout << "Add chorizo !" << std::endl;
        }
};

class PizzaVeget : public Pizza
{
    protected:
        void pizzaBase() const
        {
            std::cout << "Add tomato base !" << std::endl;
        }
        void mainIngredient() const
        {
            std::cout << "Add Artichoke, yumm yumm." << std::endl;
        }
};

int main()
{
    Pizza *veget = new PizzaVeget;
    Pizza *meat = new PizzaCannibal;

    std::cout << "First seeing the veget recipe : " << std::endl;
    veget->recipe();
    std::cout << "lets go to see cannibal recipe : " << std::endl;
    meat->recipe();

    delete veget;
    delete meat;
}

