#include <iostream>
#include <mysql.h>
#include <list>
#include <vector>

class MySql {
	public:
		~MySql()
		{
			mysql_close(mysql_connection);
			mysql_library_end();
		}

		bool connect(std::string ip, int port, std::string user, std::string pass, std::string dbname)
		{
			mysql_connection = mysql_init(NULL);

			my_bool reconnect = 1; /* Automatic reconnect */
			mysql_options(mysql_connection, MYSQL_OPT_RECONNECT, &reconnect);

			if (!mysql_real_connect(mysql_connection, (char*)ip.c_str(), (char*)user.c_str(),
				(char*)pass.c_str(), (char*)dbname.c_str(), port, NULL, 0))
			{
				std::cout << "mysql: connection error: " << mysql_error(mysql_connection) << std::endl;
				return false;
			}
			std::cout << "mysql: DB connected!" << std::endl;

			return true;
		}

		std::list<std::vector<std::string> > perform(std::string query)
		{
			MYSQL_ROW row;
			std::list<std::vector<std::string> > l;

			if (mysql_connection == NULL)
			{
				std::cout << "mysql: there is no active connection: " << query << std::endl;
				return l;
			}

			if (mysql_query(mysql_connection, (char*)query.c_str()))
			{
				std::cout << "mysql: query error: " << mysql_error(mysql_connection) << std::endl;
				return l;
			}

			MYSQL_RES *res;
			res = mysql_use_result(mysql_connection);
			if (res == NULL)
			{
				std::cout << "mysql: no response from database" << std::endl;
				mysql_free_result(res);
				return l;
			}

			int unsigned columns = mysql_num_fields(res);
			while ((row = mysql_fetch_row(res))){
				std::vector<std::string> s;
				for (unsigned int i = 0; i < columns; i++)
				{
					s.push_back(row[i]);
				}
				l.push_back(s);
			}

			mysql_free_result(res);

			return l;
		}

	private:
		MYSQL* mysql_connection;
};
