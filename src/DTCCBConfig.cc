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
#include "CondFormats/DTObjects/interface/DTCCBConfig.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondFormats/DTObjects/interface/DTConfigHandler.h"
#include "CondFormats/DTObjects/interface/DTDataBuffer.h"

//---------------
// C++ Headers --
//---------------
#include <iostream>
#include <vector>

//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTCCBConfig::DTCCBConfig():
  dataVersion( " " ) {
}


DTCCBConfig::DTCCBConfig( const std::string& version ):
  dataVersion( version ) {
}


DTCCBId::DTCCBId() :
    wheelId( 0 ),
  stationId( 0 ),
   sectorId( 0 ) {
}


//--------------
// Destructor --
//--------------
DTCCBConfig::~DTCCBConfig() {
//  std::cout << "DTCCBConfig::~DTCCBConfig begin" << std::endl;
  DTConfigHandler::autoPurge();
/*
  std::string mapRefList( "config_obj_ref" );
  DTBufferTree<int,DTConfigHandler*>* refListBuf =
  DTDataBuffer<int,DTConfigHandler*>::findBuffer( mapRefList );
  if ( refListBuf != 0 ) {
    std::vector<int> configKey;
    configKey.push_back( 1 );
    DTConfigHandler* configList = 0;
    DTBufferTree<int,DTConfigHandler*>::setDefault( 0 );
    refListBuf->find( configKey.begin(), configKey.end(), configList );
    if ( configList != 0 ) configList->purge();
  }
*/
/*
  std::string mapRefList( "config_obj_ref" );
  std::cout << "DTCCBConfig::~DTCCBConfig - 1" << std::endl;
  DTBufferTree<int,DTConfigHandler*>* refListBuf =
  DTDataBuffer<int,DTConfigHandler*>::findBuffer( mapRefList );
  std::cout << "DTCCBConfig::~DTCCBConfig - 2" << std::endl;
  std::vector<int> configKey;
  std::cout << "DTCCBConfig::~DTCCBConfig - 3" << std::endl;
  configKey.push_back( 1 );
  std::cout << "DTCCBConfig::~DTCCBConfig - 4" << std::endl;
  DTConfigHandler* configList = 0;
  std::cout << "DTCCBConfig::~DTCCBConfig - 5" << std::endl;
  if ( configList != 0 ) {
    DTBufferTree<int,DTConfigHandler*>::setDefault( 0 );
    refListBuf->find( configKey.begin(), configKey.end(), configList );
    std::cout << "DTCCBConfig::~DTCCBConfig - 6" << std::endl;
    delete configList;
    std::cout << "DTCCBConfig::~DTCCBConfig - 7" << std::endl;
    DTDataBuffer<int,DTConfigHandler*>::dropBuffer( mapRefList );
  }
*/
//  std::cout << "DTCCBConfig::~DTCCBConfig end" << std::endl;
}


DTCCBId::~DTCCBId() {
}


//--------------
// Operations --
//--------------
bool DTCCBCompare::operator()( const DTCCBId& idl,
                               const DTCCBId& idr ) const {
  if ( idl.  wheelId < idr.  wheelId ) return true;
  if ( idl.  wheelId > idr.  wheelId ) return false;
  if ( idl.stationId < idr.stationId ) return true;
  if ( idl.stationId > idr.stationId ) return false;
  if ( idl. sectorId < idr. sectorId ) return true;
  if ( idl. sectorId > idr. sectorId ) return false;
  return false;
}


int DTCCBConfig::fullKey() const {
  return fullConfigKey;
}


int DTCCBConfig::stamp() const {
  return timeStamp;
}


int DTCCBConfig::configKey( int   wheelId,
                            int stationId,
                            int  sectorId,
                            std::vector<int>& confKey ) const {

//  confKey = 0;
  confKey.clear();

  DTCCBId key;
  key.  wheelId =   wheelId;
  key.stationId = stationId;
  key. sectorId =  sectorId;
  std::map<DTCCBId,std::vector<int>,DTCCBCompare>::const_iterator iter =
                                                     ccbData.find( key );

  if ( iter != ccbData.end() ) {
    confKey = iter->second;
    return 0;
  }
  return 1;

}


int DTCCBConfig::configKey( const DTChamberId& id,
                            std::vector<int>& confKey ) const {
  return configKey( id.wheel(),
                 id.station(),
                 id.sector(),
                 confKey );
}


const
std::string& DTCCBConfig::version() const {
  return dataVersion;
}


std::string& DTCCBConfig::version() {
  return dataVersion;
}


void DTCCBConfig::clear() {
  ccbData.clear();
  return;
}


void DTCCBConfig::setFullKey( int key ) {
  fullConfigKey = key;
}


void DTCCBConfig::setStamp( int s ) {
  timeStamp = s;
}


int DTCCBConfig::setConfigKey( int   wheelId,
                               int stationId,
                               int  sectorId,
                               const std::vector<int>& confKey ) {

  DTCCBId key;
  key.  wheelId =   wheelId;
  key.stationId = stationId;
  key. sectorId =  sectorId;

  std::map<DTCCBId,std::vector<int>,DTCCBCompare>::iterator
       iter = ccbData.find( key );
  if ( iter != ccbData.end() ) iter->second = confKey;
  else                         ccbData.insert( 
                               std::pair<const DTCCBId,std::vector<int> >( 
                                    key, confKey ) );

  return 0;

}


int DTCCBConfig::setConfigKey( const DTChamberId& id,
                               const std::vector<int>& confKey ) {
  return setConfigKey( id.wheel(),
                       id.station(),
                       id.sector(),
                       confKey );
}


DTCCBConfig::const_iterator DTCCBConfig::begin() const {
  return ccbData.begin();
}


DTCCBConfig::const_iterator DTCCBConfig::end() const {
  return ccbData.end();
}


