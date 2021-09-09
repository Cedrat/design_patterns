#include <string>
#include <iostream>

class IVerifData
{
    public : 
        virtual IVerifData *setNext(IVerifData *verif) = 0;
        virtual std::string verifData(std::string request) = 0;
};

class AVerifData : public IVerifData
{
    private :
        IVerifData *_next_verif;

    public :
        AVerifData() : _next_verif(NULL){}

        IVerifData *setNext(IVerifData *verif_data)
        {
            this->_next_verif = verif_data;
            return (verif_data);
        }
        std::string verifData(std::string data)
        {
            if (this->_next_verif)
            {
                return (this->_next_verif->verifData(data));
            }
        return "Nice PassWord";
        }
};

class VerifSize : public AVerifData
{
    public :
        std::string verifData(std::string request)
        {
            if (request.size() < 6)
                return ("Too short\n");
            else
                return (AVerifData::verifData(request));
        }
};

class VerifJumpLine : public AVerifData
{
    public :
        std::string verifData(std::string data)
        {
            if (data.find("\n") != std::string::npos)
            {
                return ("Jump line in password\n");
            }
            else
            {
                return (AVerifData::verifData(data));
            }
        }
};


int main ()
{
    VerifSize *size = new VerifSize;
    VerifJumpLine *jump_line = new VerifJumpLine;

    size->setNext(jump_line);

    std::cout << size->verifData("12\n21") << std::endl;
    std::cout << size->verifData("12") << std::endl;
    std::cout << size->verifData("1234434234\n32323") << std::endl;
    std::cout << size->verifData("j32enfurf") << std::endl;

    delete jump_line;
    delete size;
}