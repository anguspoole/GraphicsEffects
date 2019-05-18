#include "cPersistSQLite_Imp.h"


cPersistSQLite_Imp::cPersistSQLite_Imp()
{
	return;
}

cPersistSQLite_Imp::~cPersistSQLite_Imp()
{
	return;
}

bool cPersistSQLite_Imp::OpenDB(std::string name)
{	
	// Already openned? 
	// (assume if it's in the map, it's open)
//	std::map<std::string /*DB Name*/, sqlite3*>::iterator itDB 
//		= this->m_map_pDBsByName.find(name);
	std::map<std::string /*DB Name*/, void*>::iterator itDB = this->m_map_pDBsByName.find(name);

	if ( itDB != this->m_map_pDBsByName.end() )
	{
		// Already openned.
		return true;
	}

	// Open it
	sqlite3* pDB = NULL;
	int result = sqlite3_open( name.c_str(), &pDB );
	if ( result != SQLITE_OK )
	{
		// Didn't work
		sqlite3_close(pDB);
		return false;
	}

	// Save the database into the map
	this->m_map_pDBsByName[name] = pDB;

	return true;
}

bool cPersistSQLite_Imp::CloseDB(std::string name)
{
//	std::map<std::string /*DB Name*/, sqlite3*>::iterator itDB = this->m_map_pDBsByName.find(name);
	std::map<std::string /*DB Name*/, void*>::iterator itDB = this->m_map_pDBsByName.find(name);

	if ( itDB == this->m_map_pDBsByName.end() )
	{
		// Doesn't exist
		return false;
	}

	sqlite3_close( (sqlite3*)itDB->second);

	this->m_map_pDBsByName.erase(name);
	return true;
}

// Returns NULL if it didn't find it
sqlite3* cPersistSQLite_Imp::m_getDBByName(std::string name)
{
//	std::map<std::string /*DB Name*/, sqlite3*>::iterator itDB = this->m_map_pDBsByName.find(name);
	std::map<std::string /*DB Name*/, void*>::iterator itDB = this->m_map_pDBsByName.find(name);

	if ( itDB == this->m_map_pDBsByName.end() )
	{
		// Doesn't exist
		return NULL;
	}
	return (sqlite3*)itDB->second;
}


std::string cPersistSQLite_Imp::translateSQLiteErrorCode(int errorCode)
{
	switch ( errorCode )
	{
	case SQLITE_OK:
		return "";
	};

	return "UNKNOWN";
}



//static 
int cPersistSQLite_Imp::callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

bool cPersistSQLite_Imp::Execute(std::string dbName, std::string SQLText)
{
	sqlite3* pTheDB = this->m_getDBByName(dbName);

	if ( pTheDB == NULL )
	{
		return false;
	}

	//TODO: Add interlock for callback

	// The DB is valid
	char *zErrMsg = 0;
	int retCode = sqlite3_exec( pTheDB, SQLText.c_str(), cPersistSQLite_Imp::callback, 0, &zErrMsg );

	if ( retCode != SQLITE_OK )
	{
		// Something went wrong...
		// TODO: add some kind of error tranlation here (like "getLastError")
		return false;
	}
	
	// Good to go
	return true;
}