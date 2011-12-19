//
/// \file server/sqlite/database.h
/// \brief Database module for sqlite
//

#ifndef SERVER_SQLITE_DATABASE_H
#define SERVER_SQLITE_DATABASE_H

#include <string>
#include <vector>

#include "sqlite3.h"

namespace SQLite
{
	class Database
	{
		public:
			//
			/// \brief Opens an sqlite database
			/// \param filename The filename to open
			//
			Database (std::string filename);

			//
			/// \brief Closes the database
			//
			virtual ~Database (void);

			//
			/// \brief Runs an SQL query on the database
			/// \param query_str The query to run
			/// \return false if an error occurred
			//
			bool query (std::string query_str);

			//
			/// \brief Get the number of rows in the last query
			//
			unsigned int getNumberOfRows (void);

			//
			/// \brief Get the query table from the last query
			//
			std::vector<std::vector<std::string> > getTable (void);

		protected:
			//
			/// \brief Our sqlite handler
			//
			sqlite3* db;

			//
			/// \brief The table from the last query
			//
			std::vector<std::vector<std::string> > query_table;
	};
}

#endif // SERVER_SQLITE_DATABASE_H

