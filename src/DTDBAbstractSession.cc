/*
 *  See header file for a description of this class.
 *
 *  TEMPORARY TOOL TO HANDLE CONFIGURATIONS
 *  TO BE REMOVED IN FUTURE RELEASES
 *
 *
 *  $Date: 2010/01/15 09:30:00 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondFormats/DTObjects/interface/DTDBAbstractSession.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondFormats/DTObjects/interface/DTAbstractSessionFactory.h"

//---------------
// C++ Headers --
//---------------
#include <iostream>

//-------------------
// Initializations --
//-------------------
//DTDBAbstractSession* DTDBAbstractSession::instance = 0;

//----------------
// Constructors --
//----------------
DTDBAbstractSession::DTDBAbstractSession() {
  std::cout << "DTDBAbstractSession::DTDBAbstractSession" << std::endl;
}


DTDBAbstractSession::DTDBAbstractSession( const std::string& dbFile,
                                          const std::string& dbCatalog,
                                          const std::string& auth_path,
                                          bool siteLocalConfig ) {
  std::cout << "DTDBAbstractSession::DTDBAbstractSession(...)" << std::endl;
  std::cout << "DTAbstractSessionFactory instance: "
            << DTAbstractSessionFactory::getInstance() << std::endl;
  instance =
  DTAbstractSessionFactory::getInstance()->createSession( dbFile, dbCatalog,
                                                          auth_path,
                                                          siteLocalConfig );
}

//--------------
// Destructor --
//--------------
DTDBAbstractSession::~DTDBAbstractSession() {
}

//--------------
// Operations --
//--------------
/// get storage manager
cond::PoolTransaction* DTDBAbstractSession::poolDB() const {
  if ( instance != 0 ) return instance->poolDB();
  return 0;
}


/// start transaction
void DTDBAbstractSession::connect( bool readOnly ) {
  if ( instance != 0 ) instance->connect( readOnly );
  return;
}


/// end   transaction
void DTDBAbstractSession::disconnect() {
  if ( instance != 0 ) instance->disconnect();
  return;
}
