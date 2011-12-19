//
/// \file server/sqlite/database.cpp
/// \brief Database module for sqlite
//

#include "database.h"

#include <iostream>

namespace SQLite
{
	Database::Database (std::string filename)
	{
		sqlite3_open (filename.c_str(), &db);
	}

	Database::~Database (void)
	{
		sqlite3_close (db);
	}

	bool Database::query (std::string query_str)
	{
		char* error_message = NULL;
		char** table = NULL;

		int num_of_rows = 0;
		int num_of_cols = 0;

		num_of_rows = 0; // New query
		int rc = sqlite3_get_table (db, query_str.c_str(), &table, &num_of_rows, &num_of_cols, &error_message);

		if (rc != SQLITE_OK)
		{
			if (error_message)
			{
				std::cout << std::string ("[sqlite] ERROR : ") + error_message << std::endl;
				sqlite3_free (error_message);
				return false;
			}
			else
			{
				// No error
			}
		}

		// create our table
		query_table.clear();

		for (int x=1; x <= num_of_rows; ++x) // Skip column names (row 0)
		{
			std::vector<std::string> cur_row;

			for (int y=0; y < num_of_cols; ++y)
			{
				cur_row.push_back (table[x*num_of_cols+y]);
			}

			query_table.push_back (cur_row);
		}

		sqlite3_free_table (table);

		// Done
		return true;
	}

	unsigned int Database::getNumberOfRows (void)
	{
		return query_table.size();
	}

	std::vector <std::vector <std::string> > Database::getTable (void)
	{
		return query_table;
	}

}

