#ifndef _cPersistSQLite_HG_
#define _cPersistSQLite_HG_

#include <string>

class cPersistSQLite_Imp;	// Forward declare

class cPersistSQLite 
{
public:
	cPersistSQLite();
	~cPersistSQLite();

	// Note: We don't do this in the ctor in case something goes wrong
	bool OpenDB(std::string name);   
	bool CloseDB(std::string name);
	bool Execute(std::string dbName, std::string SQLText);



	cPersistSQLite_Imp* m_pInst;
};



#endif
