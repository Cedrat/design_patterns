#include <string>
#include <iostream>
#include <vector>


class Product1
{
    public :
        std::vector<std::string> _parts;
        void ListParts() const
        {
            std::cout << "Product Parts:" << std::endl;
            for (size_t i = 0; i < _parts.size(); i++)
            {
                if (_parts[i] == _parts.back())
                {
                    std::cout << _parts[i];
                }
                else
                {
                    std::cout << _parts[i] << ", ";
                }
                
            }
            std::cout << std::endl;
        }
};

class Builder
{
    public :
        virtual ~Builder() {};
        virtual void ProducePartA() const = 0;
        virtual void ProducePartB() const = 0;
        virtual void ProducePartC() const = 0;
};

class ConcreteBuilder1 : public Builder
{
    private:
        Product1 *product;
    
    public:
        ConcreteBuilder1(){
            this->reset();
        }

        ~ConcreteBuilder1(){
            delete product;
        }

        void reset(){
            this->product = new Product1;
        }

        void ProducePartA() const{
            this->product->_parts.push_back("A good bread !");
        }

        void ProducePartB() const{
            this->product->_parts.push_back("Add littles tomatoes !");
        }

        void ProducePartC() const{
            this->product->_parts.push_back("One steak and two eggs");
        }

        Product1 * getProduct(){
            Product1 * result = this->product;
            this->reset();
            return result;
        }
};

class Director
{
    private :
        Builder *builder;

    public :
        void set_builder(Builder *builder)
        {
            this->builder = builder;
        }
        void just_bread(){
            this->builder->ProducePartA();
        }
        void sandwich_veget(){
            this->builder->ProducePartA();
            this->builder->ProducePartB();
        }
        void the_full(){
            this->builder->ProducePartA();
            this->builder->ProducePartB();
            this->builder->ProducePartC();
        }
};


int main()
{
    Director *director = new Director;
    ConcreteBuilder1* builder = new ConcreteBuilder1();

    director->set_builder(builder);

    director->just_bread();

    Product1 * product = builder->getProduct();
    
    product->ListParts();
    director->the_full();
    delete product;
    
    product = builder->getProduct();
    product->ListParts();
    delete product;

    //The manufacturer can make the desired configuration himself.
    builder->ProducePartA();
    builder->ProducePartC();
    product = builder->getProduct();
    product->ListParts();
    delete product;
}