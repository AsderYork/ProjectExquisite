#include <string>

class ClientUser
{
private:
    std::string m_username;
public:
    ClientUser(std::string username);
    ClientUser();

    void setUsername(std::string username);
    std::string getUsername();

};



