#include "ClientUser.h"

ClientUser::ClientUser(std::string username) : m_username(username)
{}

ClientUser::ClientUser() : m_username()
{}

void ClientUser::setUsername(std::string username) {
    m_username = username;
}

std::string ClientUser::getUsername() {
    return m_username;
}
