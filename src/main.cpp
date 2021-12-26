#include <iostream>
#include "ClientUser/ClientUser.h"
#include "ppconsul/agent.h"

using ppconsul::Consul;
using namespace ppconsul::agent;


ClientUser createUserFromConsoleInput() {
    ClientUser currentUser;
    std::cout << "Pleese enter username:" << std::endl;
    std::string recievedUsername;
    std::cin >> recievedUsername;
    currentUser.setUsername(recievedUsername);
    return currentUser;
}




int main(int, char**) {

    auto user = ClientUser("aabbccrerasd"); //createUserFromConsoleInput();
    std::cout << user.getUsername() << std::endl;

    Consul consul;
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
    }

    
    // Report service is OK


}
