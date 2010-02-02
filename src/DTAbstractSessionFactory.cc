/*
 *  See header file for a description of this class.
 *
 *  $Date: 2010-01-14 22:58:02 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondFormats/DTObjects/interface/DTAbstractSessionFactory.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------


//---------------
// C++ Headers --
//---------------
#include <iostream>

//-------------------
// Initializations --
//-------------------
DTAbstractSessionFactory* DTAbstractSessionFactory::instance = 0;

//----------------
// Constructors --
//----------------
DTAbstractSessionFactory::DTAbstractSessionFactory() {
  std::cout << "DTAbstractSessionFactory::DTAbstractSessionFactory "
            << this << std::endl;
}

//--------------
// Destructor --
//--------------
DTAbstractSessionFactory::~DTAbstractSessionFactory() {
}

//--------------
// Operations --
//--------------
DTAbstractSessionFactory* DTAbstractSessionFactory::getInstance() {
  return instance;
}


DTDBAbstractSession* DTAbstractSessionFactory::createSession( 
                                               const std::string& dbFile,
                                               const std::string& dbCatalog,
                                               const std::string& auth_path,
                                               bool siteLocalConfig ) {
  return 0;
}

