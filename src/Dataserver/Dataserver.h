#include <string>
#include <mysqlx/xdevapi.h>

struct Userrecord {
    int id;
    std::string newUsername;
    std::string newUervername;
    std::string newUsermessage;
    Userrecord(mysqlx::abi2::r0::Row result) {
        id = (int)result.get(0);
        newUsername = (std::string)result.get(1);
        newUervername = (std::string)result.get(2);
        newUsermessage = (std::string)result.get(3);
    }

};

class Dataserver
{
private:
    mysqlx::abi2::r0::Session m_session;

    mysqlx::abi2::r0::Table enshureTableExists(std::string tableName, std::string tableScript);
    

public:

    Dataserver(std::string connectonString);

    void addUserRecord(std::string username, std::string servername, std::string usermessage);
    std::vector<Userrecord> getRecords(std::string ommitUser);

};



