#ifndef _cPersistSQLite_Imp_HG_
#define _cPersistSQLite_Imp_HG_


#include "sqlite3.h"

#include <iostream>
#include <string>
#include <map>

class cPersistSQLite_Imp
{
public:
	cPersistSQLite_Imp();
	~cPersistSQLite_Imp();

	bool OpenDB(std::string name);   
	bool CloseDB(std::string name);
	bool Execute(std::string dbName, std::string SQLText);

//	std::map<std::string /*DB Name*/, sqlite3*> m_map_pDBsByName;
	std::map<std::string /*DB Name*/, void*> m_map_pDBsByName;
	// Returns NULL if it didn't find it
	sqlite3* m_getDBByName(std::string);

	std::string translateSQLiteErrorCode(int errorCode);

	// This is what's called from SQLite...
	static int callback(void *NotUsed, int argc, char **argv, char **azColName);
};

#endif