#include <string>
#include <iostream>
#include <vector>

class ISubscribber
{
    public :
        virtual ~ISubscribber(){};
        virtual void update(const std::string &message_from_subject) = 0;
};

class INewsletter
{
    public :
        virtual ~INewsletter(){};
        virtual void addNewSubscribber(ISubscribber *subscribber) = 0;
        virtual void removeSubscribber(ISubscribber *subscribber) = 0;
        virtual void notify() = 0;
};

class Newsletter : public INewsletter
{
    private :
        std::vector<ISubscribber *> _subscribbers;
        std::string                 _message;
    
    public :
        Newsletter()
        {
            std::cout << "Games Parade is out !! Go Subscribe !" << std::endl;
        }
        virtual ~Newsletter()
        {
            std::cout << "The Newsletter is ending, bye !" << std::endl;
        }
        void addNewSubscribber(ISubscribber *subscribber)
        {
            _subscribbers.push_back(subscribber);
        }
        void removeSubscribber(ISubscribber *subscribber)
        {
            std::vector<ISubscribber *>::iterator it_begin = _subscribbers.begin();
            std::vector<ISubscribber *>::iterator it_end = _subscribbers.end();

            while (it_begin != it_end)
            {
                if (*it_begin == subscribber)
                {
                    _subscribbers.erase(it_begin);
                    break;
                }
                it_begin++;
            }
        }
        void notify()
        {
            for (ISubscribber * sub: _subscribbers)
            {
                sub->update(_message);
            }
        }
        void createNews(std::string news)
        {
            _message = news;
            notify();
        }
};

class Subscribber : public ISubscribber
{
    private : 
        Newsletter      &_newsletter;
        std::string     _message;
        std::string     _subscribber_name;

    public : 
        Subscribber(Newsletter &newsletter, std::string subscribber_name) : _newsletter(newsletter), _subscribber_name(subscribber_name)
        {
            std::cout << "Hi, i'm "<< _subscribber_name << " and i follow this newsletter " << std::endl;
            _newsletter.addNewSubscribber(this);
        }
        void update(std::string const & message_from_subject)
        {
            _message = message_from_subject;
            exec();
        }
        void exec() const
        {
            std::cout << _subscribber_name << ", you receive news : " << _message << std::endl;
        }
        void unsubscribe()
        {
            std::cout << _subscribber_name << ": i unfollow the newsletter" << std::endl;
            _newsletter.removeSubscribber(this);
        }
};

int main()
{
    Newsletter *newsletter = new Newsletter;
    Subscribber *cedrat = new Subscribber(*newsletter, "Cedrat");
    Subscribber *guest = new Subscribber(*newsletter, "Guest 5330");
    Subscribber *azertite = new Subscribber(*newsletter, "Azertite");
    Subscribber *pierrot = new Subscribber(*newsletter, "ElPierrot");

    newsletter->createNews("Outers wilds is Released !");
    pierrot->unsubscribe();
    newsletter->createNews("Binding of Isaac is the game of the year !!");

    delete newsletter;
    delete cedrat;
    delete guest;
    delete azertite;
    delete pierrot;
}
