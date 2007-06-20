/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007-01-09 12:33:52 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondFormats/DTObjects/interface/DTConfigList.h"

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


//----------------
// Constructors --
//----------------
DTConfigList::DTConfigList():
  dataVersion( " " ) {
}


DTConfigList::DTConfigList( const std::string& version ):
  dataVersion( version ) {
}


DTConfigToken::DTConfigToken() :
  id( 0 ),
  ref( " " ) {
//  std::cout << "create DTConfigToken " << this << " ---> "
//            << id << " " << ref << std::endl;
}

//--------------
// Destructor --
//--------------
DTConfigList::~DTConfigList() {
}


DTConfigToken::~DTConfigToken() {
//  std::cout << "delete DTConfigToken " << this << std::endl;
}


//--------------
// Operations --
//--------------
int DTConfigList::get( int id, DTConfigToken& token ) const {

//  std::cout << "look in map" << std:: endl;
  const_iterator iter = refMap.find( id );
//  std::cout << "map read..." << std:: endl;

  if ( iter != refMap.end() ) {
//    std::cout << "token found in map" << std:: endl;
    token = iter->second;
    return 0;
  }
  else {
//    std::cout << "dummy token" << std:: endl;
    token.ref = std::string( "" );
    return -1;
  }

}


const
std::string& DTConfigList::version() const {
  return dataVersion;
}


std::string& DTConfigList::version() {
  return dataVersion;
}


void DTConfigList::clear() {
  refMap.clear();
  return;
}


int DTConfigList::set( int id, const DTConfigToken& token ) {

  std::map<int,DTConfigToken>::iterator iter = refMap.find( id );
  if ( iter != refMap.end() ) {
    iter->second = token;
    return -1;
  }
  else {
    refMap.insert( std::pair< int,DTConfigToken >( id, token ) );
    return 0;
  }

  return 0;

}


DTConfigList::const_iterator DTConfigList::begin() const {
  return refMap.begin();
}


DTConfigList::const_iterator DTConfigList::end() const {
  return refMap.end();
}


