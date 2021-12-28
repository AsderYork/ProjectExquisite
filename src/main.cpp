#include <iostream>
#include <vector>
#include <string>
#include "ClientUser/ClientUser.h"
#include "Dataserver/Dataserver.h"
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

int main(int, char**) {

	try {
		Dataserver dataserver("mysqlx://user:ultrapass@127.0.0.1:33060/db?ssl-mode=disabled");
		dataserver.addUserRecord("user4", "server9", "random message");
		auto records = dataserver.getRecords("user3");
	}
	catch (const std::exception & exc)
	{
		std::cout << "Can't execute db part: "<< exc.what() << std::endl;
	}


    


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
