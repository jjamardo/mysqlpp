# mysqlpp
Small C++ wrapper for the mysql C Linux library.
			
## Use

```c++
std::string query = "SELECT name, lastname FROM employees;";

MySql db;

db.connect("192.168.0.10", 3306, "user", "password", "dbname");

std::list<std::vector<std::string> > result = db.perform(query);

std::list<std::vector<std::string> >::const_iterator it = result.begin();

for (; it != result.end(); ++it)
{
	std::vector<std::string> row = *it;
	std::string name = row[0];
	std::string lastname = row[1];
};
```

## Compilation

Include the "mysql.hpp" file and link with:

-lmysqlclient
