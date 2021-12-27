#include <iostream>
#include <vector>
#include <string>
#include "ClientUser/ClientUser.h"
#include "ppconsul/agent.h"



#include <mysqlx/xdevapi.h>


using ppconsul::Consul;
using namespace ppconsul::agent;
using namespace ::mysqlx;


ClientUser createUserFromConsoleInput() {
    ClientUser currentUser;
    std::cout << "Pleese enter username:" << std::endl;
    std::string recievedUsername;
    std::cin >> recievedUsername;
    currentUser.setUsername(recievedUsername);
    return currentUser;
}


Table enshureTableExists(Session& sess, std::string tableName, std::string tableScript) {
	auto table = sess.getSchema("db").getTable(tableName);
	if (!table.existsInDatabase()) {
		sess.sql(tableScript).execute();
		std::cout << "Table " << tableName << "didn't exist before. Creating" << std::endl;
		table = sess.getSchema("db").getTable(tableName);
	}
	return table;
}

void addUserRecord(Session& sess, std::string username, std::string servername, std::string usermessage) {

	auto query = sess.sql("INSERT INTO userrecords(username, servername, usermessage) VALUES(?, ?, ?)");
	query.bind(username, servername, usermessage);
	query.execute();

}

void loginToDBAndRetrieveRecords(std::string username, std::string servername, std::string usermessage) {
	try {
		Session sess("mysqlx://user:ultrapass@127.0.0.1:33060/db?ssl-mode=disabled");

		auto table = enshureTableExists(sess, "userrecords", "create table userrecords (id int NOT NULL AUTO_INCREMENT, username TEXT, usermessage TEXT, servername TEXT, date_created TIMESTAMP DEFAULT CURRENT_TIMESTAMP, primary key (id))");
		
		addUserRecord(sess, username, servername, usermessage);

		auto query = sess.sql("select id, username, servername, usermessage, date_created from userrecords where username != ?");
		query.bind(username);
		auto queryResult = query.execute();
		auto recordCount = queryResult.count();

		for (auto queryResult : queryResult)
		{
			auto colCount = queryResult.colCount();
			auto id = (int)queryResult.get(0);
			auto newUsername = (std::string)queryResult.get(1);
			auto newUervername = (std::string)queryResult.get(2);
			auto newUsermessage = (std::string)queryResult.get(3);
		}

	}
	catch (const std::exception & exc)
	{
		std::cout << "Can't execute db part: "<< exc.what() << std::endl;
	}
}


int main(int, char**) {

	loginToDBAndRetrieveRecords("user3", "server1", "message3");

    


    auto user = ClientUser("aabbccrerasd"); //createUserFromConsoleInput();
    std::cout << user.getUsername() << std::endl;

   /* Consul consul;
    Agent agent(consul);


    // Register a service with TTL
    agent.registerService(
        kw::name = "Client",
        kw::port = 9876,
        kw::id = "Client",
        kw::check = TtlCheck{std::chrono::seconds(60)}
    );

    auto getAllServices = agent.services();

    std::string cmd;
    while(cmd.compare("q") != 0) {
        std::cin >> cmd;
        std::cout << cmd;
        agent.servicePass("Client");
    }*/

    
    // Report service is OK


}
