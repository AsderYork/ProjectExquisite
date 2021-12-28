#include "Dataserver.h"
#include <iostream>
#include <algorithm>

Dataserver::Dataserver(std::string connectonString) : m_session(connectonString) {}

mysqlx::abi2::r0::Table Dataserver::enshureTableExists(std::string tableName, std::string tableScript) {
        auto table = m_session.getSchema("db").getTable(tableName);
        if (!table.existsInDatabase()) {
            m_session.sql(tableScript).execute();
            std::cout << "Table " << tableName << "didn't exist before. Creating" << std::endl;
            table = m_session.getSchema("db").getTable(tableName);
        }
	    return table;
    }

void Dataserver::addUserRecord(std::string username, std::string servername, std::string usermessage) {

        auto query = m_session.sql("INSERT INTO userrecords(username, servername, usermessage) VALUES(?, ?, ?)");
        query.bind(username, servername, usermessage);
        query.execute();

    }

std::vector<Userrecord> Dataserver::getRecords(std::string ommitUser) {

        auto query = m_session.sql("select id, username, servername, usermessage, date_created from userrecords where username != ?");
		query.bind(ommitUser);
		auto queryResult = query.execute();
		auto recordCount = queryResult.count();

        std::vector<Userrecord> result;
        std::transform(queryResult.begin(), queryResult.end(), std::back_inserter(result), [](auto& row) { return Userrecord(row); });
        return result;

    }

