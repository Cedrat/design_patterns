#include <string> 
#include <iostream>

class DittoInt;
class DittoStr;

class IVisitor
{
    public :
        virtual void visitDittoInt(const DittoInt *ditto) const = 0;
        virtual void visitDittoStr(const DittoStr *ditto) const = 0;
};

class IDitto
{
    public :
        virtual ~IDitto(){};
        virtual void accept(IVisitor*) const = 0;
 };

 class DittoInt : public IDitto
 {
    public :
        int ditto_int;
        DittoInt(int integer) : ditto_int(integer) {}
        void accept(IVisitor *visitor) const
        {
            visitor->visitDittoInt(this);
        }
 };

class DittoStr : public IDitto
 {
    public :
        std::string ditto_str;
        DittoStr(std::string str) : ditto_str(str) {}
        void accept(IVisitor *visitor) const
        {
            visitor->visitDittoStr(this);
        }
 };

 class PrintLast : public IVisitor
 {
    public :
        void visitDittoInt(const DittoInt *ditto) const
        {
            std::cout << "this visitor give the last character.. : " << ditto->ditto_int%10 << std::endl;
        }
         void visitDittoStr(const DittoStr *ditto) const
        {
            std::cout << "this visitor give the last character.. : " << ditto->ditto_str[ditto->ditto_str.size() - 1] << std::endl;
        }
 };


int main()
{
    IVisitor *last_part = new PrintLast;
    IDitto *str = new DittoStr("POKEMON");
    IDitto *integer = new DittoInt(42);
    
    str->accept(last_part);
    integer->accept(last_part);

    delete last_part;
	delete str;
	delete integer;
}



