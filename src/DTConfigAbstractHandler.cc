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
#include "CondFormats/DTObjects/interface/DTConfigAbstractHandler.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------

#include "CondCore/DBCommon/interface/TypedRef.h"

#include "CondFormats/DTObjects/interface/DTDBAbstractSession.h"

//---------------
// C++ Headers --
//---------------
#include <iostream>

//-------------------
// Initializations --
//-------------------
DTConfigAbstractHandler* DTConfigAbstractHandler::instance = 0;
int DTConfigAbstractHandler::maxBrickNumber  = 50;
int DTConfigAbstractHandler::maxStringNumber = 1000;
int DTConfigAbstractHandler::maxByteNumber   = 1000000;

//----------------
// Constructors --
//----------------
DTConfigAbstractHandler::DTConfigAbstractHandler() {
  std::cout << "DTConfigAbstractHandler::DTConfigAbstractHandler" << std::endl;
}


DTConfigAbstractHandler::~DTConfigAbstractHandler() {
}


//--------------
// Operations --
//--------------
/// create static object
DTConfigAbstractHandler* DTConfigAbstractHandler::create(
                         DTDBAbstractSession* session,
                         const std::string& token ) {

  std::cout << "DTConfigAbstractHandler::create " << instance << std::endl;
  if ( instance != 0 ) return instance->build( session, token );
  return 0;

}


void DTConfigAbstractHandler::remove( const DTDBAbstractSession* session ) {
  std::cout << "DTConfigAbstractHandler::remove( session ) "
            << instance << std::endl;
  if ( instance != 0 ) instance->destroy( session );
  return;
}


void DTConfigAbstractHandler::remove( const DTConfigAbstractHandler* handler ) {
  std::cout << "DTConfigAbstractHandler::remove( handler ) "
            << instance << std::endl;
  if ( instance != 0 ) instance->destroy( handler );
  return;
}


/// get content
const DTConfigList* DTConfigAbstractHandler::getContainer() {
  return 0;
}


int DTConfigAbstractHandler::get( int cfgId, DTConfigData*& obj ) {
  return 999;
}


void DTConfigAbstractHandler::getData( int cfgId,
                               std::vector<const std::string*>& list ) {
  return;
}


int DTConfigAbstractHandler::set( int cfgId, const std::string& token ) {
  return 0;
}


DTConfigAbstractHandler::const_iterator DTConfigAbstractHandler::begin() const {
  return refMap.begin();
}


DTConfigAbstractHandler::const_iterator DTConfigAbstractHandler::end() const {
  return refMap.end();
}


void DTConfigAbstractHandler::purge() {
  return;
}


DTConfigAbstractHandler* DTConfigAbstractHandler::build(
                         DTDBAbstractSession* session,
                         const std::string& token ) {
  std::cout << "DTConfigAbstractHandler::build " << this << std::endl;
  return 0;
}


void DTConfigAbstractHandler::destroy(
                              const DTDBAbstractSession* session ) {
  std::cout << "DTConfigAbstractHandler::destroy( session ) "
            << this << std::endl;
  return ;
}


void DTConfigAbstractHandler::destroy(
                              const DTConfigAbstractHandler* handler ) {
  std::cout << "DTConfigAbstractHandler::destroy( handler ) "
            << this << std::endl;
  return ;
}


std::string DTConfigAbstractHandler::clone( DTDBAbstractSession* newSession,
                                    const std::string& newToken,
                                    const std::string& objContainer,
                                    const std::string& refContainer ) {

  return std::string( "" );
}


