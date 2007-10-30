/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007/01/22 18:24:45 $
 *  $Revision: 1.6 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// This Class' Header --
//----------------------
#include "CondFormats/DTObjects/interface/DTStatusFlag.h"
#include "CondFormats/DTObjects/interface/DTDataBuffer.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------


//---------------
// C++ Headers --
//---------------
#include <iostream>

//----------------
// Constructors --
//----------------
DTStatusFlag::DTStatusFlag():
  dataVersion( " " ) {
}


DTStatusFlag::DTStatusFlag( const std::string& version ):
  dataVersion( version ) {
}


DTStatusFlagId::DTStatusFlagId() :
    wheelId( 0 ),
  stationId( 0 ),
   sectorId( 0 ),
       slId( 0 ),
    layerId( 0 ),
     cellId( 0 ) {
}


DTStatusFlagData::DTStatusFlagData() :
  noiseFlag( false ),
     feMask( false ),
    tdcMask( false ),
   trigMask( false ),
   deadFlag( false ),
   nohvFlag( false ) {
}


//--------------
// Destructor --
//--------------
DTStatusFlag::~DTStatusFlag() {
  DTDataBuffer<int,DTStatusFlagData*>::dropBuffer( mapName() );
}


DTStatusFlagId::~DTStatusFlagId() {
}


DTStatusFlagData::~DTStatusFlagData() {
}


//--------------
// Operations --
//--------------
int DTStatusFlag::get( int   wheelId,
                       int stationId,
                       int  sectorId,
                       int      slId,
                       int   layerId,
                       int    cellId,
                       bool& noiseFlag,
                       bool&    feMask,
                       bool&   tdcMask,
                       bool&  trigMask,
                       bool&  deadFlag,
                       bool&  nohvFlag ) const {

  noiseFlag =
     feMask =
    tdcMask =
   deadFlag =
   nohvFlag = false;

  std::string mName = mapName();
  DTBufferTree<int,DTStatusFlagData*>* dBuf =
  DTDataBuffer<int,DTStatusFlagData*>::findBuffer( mName );
  if ( dBuf == 0 ) {
    cacheMap();
    dBuf =
    DTDataBuffer<int,DTStatusFlagData*>::findBuffer( mName );
  }
  std::vector<int> chanKey;
  chanKey.push_back(   wheelId );
  chanKey.push_back( stationId );
  chanKey.push_back(  sectorId );
  chanKey.push_back(      slId );
  chanKey.push_back(   layerId );
  chanKey.push_back(    cellId );
  DTStatusFlagData* data;
  int searchStatus = dBuf->find( chanKey.begin(), chanKey.end(),
                                          data );
  if ( !searchStatus ) {
    noiseFlag = data->noiseFlag;
       feMask = data->   feMask;
      tdcMask = data->  tdcMask;
     trigMask = data-> trigMask;
     deadFlag = data-> deadFlag;
     nohvFlag = data-> nohvFlag;
  }

  return searchStatus;

}


int DTStatusFlag::get( const DTWireId& id,
                       bool& noiseFlag,
                       bool&    feMask,
                       bool&   tdcMask,
                       bool&  trigMask,
                       bool&  deadFlag,
                       bool&  nohvFlag ) const {
  return get( id.wheel(),
              id.station(),
              id.sector(),
              id.superLayer(),
              id.layer(),
              id.wire(),
              noiseFlag,   feMask,  tdcMask,
               trigMask, deadFlag, nohvFlag );
}


const
std::string& DTStatusFlag::version() const {
  return dataVersion;
}


std::string& DTStatusFlag::version() {
  return dataVersion;
}


void DTStatusFlag::clear() {
  dataList.clear();
  return;
}


int DTStatusFlag::setCellStatus( int   wheelId,
                                 int stationId,
                                 int  sectorId,
                                 int      slId,
                                 int   layerId,
                                 int    cellId,
                                 bool noiseFlag,
                                 bool    feMask,
                                 bool   tdcMask,
                                 bool  trigMask,
                                 bool  deadFlag,
                                 bool  nohvFlag ) {

  std::string mName = mapName();
  DTBufferTree<int,DTStatusFlagData*>* dBuf =
  DTDataBuffer<int,DTStatusFlagData*>::findBuffer( mName );
  if ( dBuf == 0 ) {
    cacheMap();
    dBuf =
    DTDataBuffer<int,DTStatusFlagData*>::findBuffer( mName );
  }
  std::vector<int> chanKey;
  chanKey.push_back(   wheelId );
  chanKey.push_back( stationId );
  chanKey.push_back(  sectorId );
  chanKey.push_back(      slId );
  chanKey.push_back(   layerId );
  chanKey.push_back(    cellId );
  DTStatusFlagData* dptr;
  int searchStatus = dBuf->find( chanKey.begin(), chanKey.end(),
                                          dptr );

  if ( !searchStatus ) {
    DTStatusFlagData& data = *dptr;
    data.noiseFlag = noiseFlag;
    data.   feMask =    feMask;
    data.  tdcMask =   tdcMask;
    data. trigMask =  trigMask;
    data. deadFlag =  deadFlag;
    data. nohvFlag =  nohvFlag;
    return -1;
  }
  else {
    DTStatusFlagId key;
    key.  wheelId =   wheelId;
    key.stationId = stationId;
    key. sectorId =  sectorId;
    key.     slId =      slId;
    key.  layerId =   layerId;
    key.   cellId =    cellId;
    DTStatusFlagData data;
    data.noiseFlag = noiseFlag;
    data.   feMask =    feMask;
    data.  tdcMask =   tdcMask;
    data. trigMask =  trigMask;
    data. deadFlag =  deadFlag;
    data. nohvFlag =  nohvFlag;
    dataList.push_back( std::pair<const DTStatusFlagId,
                                        DTStatusFlagData>( key, data ) );
    DTStatusFlagData* dptr = &( dataList.back().second );
    dBuf->insert( chanKey.begin(), chanKey.end(), dptr  );
    return 0;
  }

  return 99;

}


int DTStatusFlag::setCellStatus( const DTWireId& id,
                                 bool noiseFlag,
                                 bool    feMask,
                                 bool   tdcMask,
                                 bool  trigMask,
                                 bool  deadFlag,
                                 bool  nohvFlag  ) {
  return setCellStatus( id.wheel(),
                        id.station(),
                        id.sector(),
                        id.superLayer(),
                        id.layer(),
                        id.wire(),
                        noiseFlag,   feMask,  tdcMask,
                         trigMask, deadFlag, nohvFlag );
}


int DTStatusFlag::setCellNoise( int   wheelId,
                                int stationId,
                                int  sectorId,
                                int      slId,
                                int   layerId,
                                int    cellId,
                                bool flag ) {

  bool noiseFlag;
  bool    feMask;
  bool   tdcMask;
  bool  trigMask;
  bool  deadFlag;
  bool  nohvFlag;
  int status = cellStatus(   wheelId,
                           stationId,
                            sectorId,
                                slId,
                             layerId,
                              cellId,
                           noiseFlag,
                              feMask,
                             tdcMask,
                            trigMask,
                            deadFlag,
                            nohvFlag );
  setCellStatus(   wheelId,
                 stationId,
                  sectorId,
                      slId,
                   layerId,
                    cellId,
                      flag,
                    feMask,
                   tdcMask,
                  trigMask,
                  deadFlag,
                  nohvFlag );
  return status;

}


int DTStatusFlag::setCellNoise( const DTWireId& id,
                                bool flag ) {
  return setCellNoise( id.wheel(),
                       id.station(),
                       id.sector(),
                       id.superLayer(),
                       id.layer(),
                       id.wire(),
                       flag );
}


int DTStatusFlag::setCellFEMask( int   wheelId,
                                 int stationId,
                                 int  sectorId,
                                 int      slId,
                                 int   layerId,
                                 int    cellId,
                                 bool mask ) {

  bool noiseFlag;
  bool    feMask;
  bool   tdcMask;
  bool  trigMask;
  bool  deadFlag;
  bool  nohvFlag;
  int status = cellStatus(   wheelId,
                           stationId,
                            sectorId,
                                slId,
                             layerId,
                              cellId,
                           noiseFlag,
                              feMask,
                             tdcMask,
                            trigMask,
                            deadFlag,
                            nohvFlag );
  setCellStatus(   wheelId,
                 stationId,
                  sectorId,
                      slId,
                   layerId,
                    cellId,
                 noiseFlag,
                      mask,
                   tdcMask,
                  trigMask,
                  deadFlag,
                  nohvFlag );
  return status;

}


int DTStatusFlag::setCellFEMask( const DTWireId& id,
                                 bool mask ) {
  return setCellFEMask( id.wheel(),
                        id.station(),
                        id.sector(),
                        id.superLayer(),
                        id.layer(),
                        id.wire(),
                        mask );
}


int DTStatusFlag::setCellTDCMask( int   wheelId,
                                  int stationId,
                                  int  sectorId,
                                  int      slId,
                                  int   layerId,
                                  int    cellId,
                                  bool mask ) {

  bool noiseFlag;
  bool    feMask;
  bool   tdcMask;
  bool  trigMask;
  bool  deadFlag;
  bool  nohvFlag;
  int status = cellStatus(   wheelId,
                           stationId,
                            sectorId,
                                slId,
                             layerId,
                              cellId,
                           noiseFlag,
                              feMask,
                             tdcMask,
                            trigMask,
                            deadFlag,
                            nohvFlag );
  setCellStatus(   wheelId,
                 stationId,
                  sectorId,
                      slId,
                   layerId,
                    cellId,
                 noiseFlag,
                    feMask,
                      mask,
                  trigMask,
                  deadFlag,
                  nohvFlag );
  return status;

}


int DTStatusFlag::setCellTDCMask( const DTWireId& id,
                                  bool mask ) {
  return setCellTDCMask( id.wheel(),
                         id.station(),
                         id.sector(),
                         id.superLayer(),
                         id.layer(),
                         id.wire(),
                         mask );
}


int DTStatusFlag::setCellTrigMask( int   wheelId,
                                   int stationId,
                                   int  sectorId,
                                   int      slId,
                                   int   layerId,
                                   int    cellId,
                                   bool mask ) {

  bool noiseFlag;
  bool    feMask;
  bool   tdcMask;
  bool  trigMask;
  bool  deadFlag;
  bool  nohvFlag;
  int status = cellStatus(   wheelId,
                           stationId,
                            sectorId,
                                slId,
                             layerId,
                              cellId,
                           noiseFlag,
                              feMask,
                             tdcMask,
                            trigMask,
                            deadFlag,
                            nohvFlag );
  setCellStatus(   wheelId,
                 stationId,
                  sectorId,
                      slId,
                   layerId,
                    cellId,
                 noiseFlag,
                    feMask,
                   tdcMask,
                      mask,
                  deadFlag,
                  nohvFlag );
  return status;

}


int DTStatusFlag::setCellTrigMask( const DTWireId& id,
                                   bool mask ) {
  return setCellTrigMask( id.wheel(),
                          id.station(),
                          id.sector(),
                          id.superLayer(),
                          id.layer(),
                          id.wire(),
                          mask );
}


int DTStatusFlag::setCellDead( int   wheelId,
                               int stationId,
                               int  sectorId,
                               int      slId,
                               int   layerId,
                               int    cellId,
                               bool flag ) {

  bool noiseFlag;
  bool    feMask;
  bool   tdcMask;
  bool  trigMask;
  bool  deadFlag;
  bool  nohvFlag;
  int status = cellStatus(   wheelId,
                           stationId,
                            sectorId,
                                slId,
                             layerId,
                              cellId,
                           noiseFlag,
                              feMask,
                             tdcMask,
                            trigMask,
                            deadFlag,
                            nohvFlag );
  setCellStatus(   wheelId,
                 stationId,
                  sectorId,
                      slId,
                   layerId,
                    cellId,
                 noiseFlag,
                    feMask,
                   tdcMask,
                  trigMask,
                      flag,
                  nohvFlag );
  return status;

}


int DTStatusFlag::setCellDead( const DTWireId& id,
                               bool flag ) {
  return setCellDead( id.wheel(),
                      id.station(),
                      id.sector(),
                      id.superLayer(),
                      id.layer(),
                      id.wire(),
                      flag );
}


int DTStatusFlag::setCellNoHV( int   wheelId,
                               int stationId,
                               int  sectorId,
                               int      slId,
                               int   layerId,
                               int    cellId,
                               bool flag ) {

  bool noiseFlag;
  bool    feMask;
  bool   tdcMask;
  bool  trigMask;
  bool  deadFlag;
  bool  nohvFlag;
  int status = cellStatus(   wheelId,
                           stationId,
                            sectorId,
                                slId,
                             layerId,
                              cellId,
                           noiseFlag,
                              feMask,
                             tdcMask,
                            trigMask,
                            deadFlag,
                            nohvFlag );
  setCellStatus(   wheelId,
                 stationId,
                  sectorId,
                      slId,
                   layerId,
                    cellId,
                 noiseFlag,
                    feMask,
                   tdcMask,
                  trigMask,
                  deadFlag,
                      flag );
  return status;

}


int DTStatusFlag::setCellNoHV( const DTWireId& id,
                               bool flag ) {
  return setCellNoHV( id.wheel(),
                      id.station(),
                      id.sector(),
                      id.superLayer(),
                      id.layer(),
                      id.wire(),
                      flag );
}


DTStatusFlag::const_iterator DTStatusFlag::begin() const {
  return dataList.begin();
}


DTStatusFlag::const_iterator DTStatusFlag::end() const {
  return dataList.end();
}


std::string DTStatusFlag::mapName() const {
  std::string name = dataVersion + "_map_StatusFlag";
  char nptr[100];
  sprintf( nptr, "%x", reinterpret_cast<unsigned int>( this ) );
  name += nptr;
  return name;
}


void DTStatusFlag::cacheMap() const {

  std::string mName = mapName();
  DTBufferTree<int,DTStatusFlagData*>* dBuf =
  DTDataBuffer<int,DTStatusFlagData*>::openBuffer( mName );

  const_iterator iter = dataList.begin();
  const_iterator iend = dataList.end();
  int    wheelId;
  int  stationId;
  int   sectorId;
  int       slId;
  int    layerId;
  int     cellId;
  while ( iter != iend ) {

    const std::pair<DTStatusFlagId, DTStatusFlagData>& link = *iter++;
    const DTStatusFlagId& chan = link.first;
      wheelId = chan.  wheelId;
    stationId = chan.stationId;
     sectorId = chan. sectorId;
         slId = chan.     slId;
      layerId = chan.  layerId;
       cellId = chan.   cellId;

    const DTStatusFlagData* dptr = &( link.second );

    std::vector<int> chanKey;
    chanKey.push_back(   wheelId );
    chanKey.push_back( stationId );
    chanKey.push_back(  sectorId );
    chanKey.push_back(      slId );
    chanKey.push_back(   layerId );
    chanKey.push_back(    cellId );
    dBuf->insert( chanKey.begin(), chanKey.end(),
                  const_cast<DTStatusFlagData*>( dptr ) );

  }

  return;

}

