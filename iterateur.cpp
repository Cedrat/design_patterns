#include <vector>
#include <string>
#include <iostream>

template<typename T>
class IIterator
{
    public :
        typedef typename std::vector<T>::iterator iter_type;
        virtual ~IIterator(){};
        virtual iter_type begin() = 0;
        virtual iter_type end() = 0;
        virtual void next() = 0;
        virtual void previous() = 0;
        virtual T currentValue() = 0;
        virtual iter_type currentIt() = 0;
    private :
        iter_type it;
};

template<typename T>
class Iterator : public IIterator<T>
{
    public :
        typedef typename std::vector<T>::iterator iter_type;
        Iterator(std::vector<T> &p_data) :_p_data(p_data)
        {
            it = _p_data.begin();
        }
        iter_type begin()
        {
            return _p_data.begin();
        }
        iter_type end()
        {
            return _p_data.end();
        }
        void next()
        {
            it++;
        }
        void previous()
        {
            it--;
        }
        iter_type currentIt()
        {
            return (it);
        }
        T currentValue()
        {
            return (*it);
        }
    private : 
        std::vector<T> _p_data;
        iter_type it;
};

template<typename T>
class ReverseIterator : public IIterator<T>
{
    public :
        typedef typename std::vector<T>::iterator iter_type;
        ReverseIterator(std::vector<T> &p_data) :_p_data(p_data)
        {
            it = _p_data.end();
            it--;
        }
        iter_type begin()
        {
            return _p_data.end();
        }
        iter_type end()
        {
            return (_p_data.begin() - 1);
        }
        void next()
        {
            it--;
        }
        void previous()
        {
            it++;
        }
        iter_type currentIt()
        {
            return (it);
        }
        T currentValue()
        {
            return (*it);
        }
    private : 
        std::vector<T> _p_data;
        iter_type it;
};

template<typename T>
 void loop_between_data(IIterator<T> &it)
 {
    while (it.end() != it.currentIt())
    {
        std::cout << it.currentValue() << std::endl;
        it.next();
    }
 }

int main()
{
    std::vector<int> array;
    for (int i = 0; i < 10; i++)
    {
        array.push_back(i);
    }
    IIterator<int> *it_1 = new Iterator<int>(array);
    IIterator<int> *it_2 = new ReverseIterator<int>(array);
    std::cout << "Classical order : " << std::endl;
    loop_between_data(*it_1);
    std::cout << "Reverse order : " << std::endl;
    loop_between_data(*it_2);

    delete it_1;
    delete it_2;
}
