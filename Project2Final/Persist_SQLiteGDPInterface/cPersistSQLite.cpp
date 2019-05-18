#include "cPersistSQLite.h"

#include "cPersistSQLite_Imp.h"


cPersistSQLite::cPersistSQLite()
{
#ifdef DEBUG
	std::cout << "A cPersistSQLite() is created." << std::endl;
#endif
	return;
}

cPersistSQLite::~cPersistSQLite()
{


	return;
}

bool cPersistSQLite::OpenDB(std::string name)
{
	return this->m_pInst->OpenDB(name);
}


bool cPersistSQLite::CloseDB(std::string name)
{
	return this->m_pInst->CloseDB(name);
}

bool cPersistSQLite::Execute(std::string dbName, std::string SQLText)
{
	return this->m_pInst->Execute( dbName, SQLText );
}
