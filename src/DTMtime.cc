/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007/01/22 18:24:45 $
 *  $Revision: 1.11 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// This Class' Header --
//----------------------
#include "CondFormats/DTObjects/interface/DTMtime.h"
#include "CondFormats/DTObjects/interface/DTDataBuffer.h"

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
DTMtime::DTMtime():
  dataVersion( " " ),
  nsPerCount( 25.0 / 32.0 ) {
}


DTMtime::DTMtime( const std::string& version ):
  dataVersion( version ),
  nsPerCount( 25.0 / 32.0 ) {
}


DTMtimeId::DTMtimeId() :
    wheelId( 0 ),
  stationId( 0 ),
   sectorId( 0 ),
       slId( 0 ),
    layerId( 0 ),
     cellId( 0 ) {
}


DTMtimeData::DTMtimeData() :
  mTime( 0.0 ),
  mTrms( 0.0 ) {
}


//--------------
// Destructor --
//--------------
DTMtime::~DTMtime() {
  DTDataBuffer<int,DTMtimeData*>::dropBuffer( mapName() );
}


DTMtimeId::~DTMtimeId() {
}


DTMtimeData::~DTMtimeData() {
}


//--------------
// Operations --
//--------------
int DTMtime::get( int   wheelId,
                  int stationId,
                  int  sectorId,
                  int      slId,
                  float&  mTime,
                  float&  mTrms,
                  DTTimeUnits::type unit ) const {
  return get( wheelId, stationId, sectorId,
                 slId,         0,        0,
                mTime, mTrms, unit );

}


int DTMtime::get( int   wheelId,
                  int stationId,
                  int  sectorId,
                  int      slId,
                  int   layerId,
                  int    cellId,
                  float&  mTime,
                  float&  mTrms,
                  DTTimeUnits::type unit ) const {

  mTime =
  mTrms = 0.0;

  std::string mName = mapName();
  DTBufferTree<int,DTMtimeData*>* dBuf =
  DTDataBuffer<int,DTMtimeData*>::findBuffer( mName );
  if ( dBuf == 0 ) {
    cacheMap();
    dBuf =
    DTDataBuffer<int,DTMtimeData*>::findBuffer( mName );
  }
  std::vector<int> chanKey;
  chanKey.push_back(   wheelId );
  chanKey.push_back( stationId );
  chanKey.push_back(  sectorId );
  chanKey.push_back(      slId );
  chanKey.push_back(   layerId );
  chanKey.push_back(    cellId );
  DTMtimeData* data;
  int searchStatus = dBuf->find( chanKey.begin(), chanKey.end(), data );
  if ( !searchStatus ) {
    mTime = data->mTime;
    mTrms = data->mTrms;
    if ( unit == DTTimeUnits::ns ) {
      mTime *= nsPerCount;
      mTrms *= nsPerCount;
    }
  }

  return searchStatus;

}


int DTMtime::get( const DTSuperLayerId& id,
                  float&  mTime,
                  float&  mTrms,
                  DTTimeUnits::type unit ) const {
  return get( id.wheel(),
              id.station(),
              id.sector(),
              id.superLayer(), 0, 0,
              mTime, mTrms, unit );
}


int DTMtime::get( const DetId& id,
                  float&  mTime,
                  float&  mTrms,
                  DTTimeUnits::type unit ) const {
  DTWireId wireId( id.rawId() );
  return get( wireId.wheel(),
              wireId.station(),
              wireId.sector(),
              wireId.superLayer(),
              wireId.layer(),
              wireId.wire(),
              mTime, mTrms, unit );
}


float DTMtime::unit() const {
  return nsPerCount;
}


const
std::string& DTMtime::version() const {
  return dataVersion;
}


std::string& DTMtime::version() {
  return dataVersion;
}


void DTMtime::clear() {
  dataList.clear();
  return;
}


int DTMtime::set( int   wheelId,
                  int stationId,
                  int  sectorId,
                  int      slId,
                  float   mTime,
                  float   mTrms,
                  DTTimeUnits::type unit ) {
  return set( wheelId, stationId, sectorId,
                 slId,         0,        0,
                mTime, mTrms, unit );
}


int DTMtime::set( int   wheelId,
                  int stationId,
                  int  sectorId,
                  int      slId,
                  int   layerId,
                  int    cellId,
                  float   mTime,
                  float   mTrms,
                  DTTimeUnits::type unit ) {

  if ( unit == DTTimeUnits::ns ) {
    mTime /= nsPerCount;
    mTrms /= nsPerCount;
  }

  std::string mName = mapName();
  DTBufferTree<int,DTMtimeData*>* dBuf =
  DTDataBuffer<int,DTMtimeData*>::findBuffer( mName );
  if ( dBuf == 0 ) {
    cacheMap();
    dBuf =
    DTDataBuffer<int,DTMtimeData*>::findBuffer( mName );
  }
  std::vector<int> chanKey;
  chanKey.push_back(   wheelId );
  chanKey.push_back( stationId );
  chanKey.push_back(  sectorId );
  chanKey.push_back(      slId );
  chanKey.push_back(   layerId );
  chanKey.push_back(    cellId );
  DTMtimeData* dptr;
  int searchStatus = dBuf->find( chanKey.begin(), chanKey.end(), dptr );

  if ( !searchStatus ) {
    DTMtimeData& data = *dptr;
    data.mTime = mTime;
    data.mTrms = mTrms;
    return -1;
  }
  else {
    DTMtimeId key;
    key.  wheelId =   wheelId;
    key.stationId = stationId;
    key. sectorId =  sectorId;
    key.     slId =      slId;
    key.  layerId =   layerId;
    key.   cellId =    cellId;
    DTMtimeData data;
    data.mTime = mTime;
    data.mTrms = mTrms;
    dataList.push_back( std::pair<DTMtimeId,DTMtimeData>( key, data ) );
    DTMtimeData* dptr = &( dataList.back().second );
    dBuf->insert( chanKey.begin(), chanKey.end(), dptr  );
    return 0;
  }

  return 99;

}


int DTMtime::set( const DTSuperLayerId& id,
                  float   mTime,
                  float   mTrms,
                  DTTimeUnits::type unit ) {
  return set( id.wheel(),
              id.station(),
              id.sector(),
              id.superLayer(), 0, 0,
              mTime, mTrms, unit );
}


int DTMtime::set( const DetId& id,
                  float   mTime,
                  float   mTrms,
                  DTTimeUnits::type unit ) {
  DTWireId wireId( id.rawId() );
  return set( wireId.wheel(),
              wireId.station(),
              wireId.sector(),
              wireId.superLayer(),
              wireId.layer(),
              wireId.wire(),
              mTime, mTrms, unit );
}


void DTMtime::setUnit( float unit ) {
  nsPerCount = unit;
}


DTMtime::const_iterator DTMtime::begin() const {
  return dataList.begin();
}


DTMtime::const_iterator DTMtime::end() const {
  return dataList.end();
}


std::string DTMtime::mapName() const {
  std::string name = dataVersion + "_map_Mtime";
  char nptr[100];
  sprintf( nptr, "%x", reinterpret_cast<unsigned int>( this ) );
  name += nptr;
  return name;
}


void DTMtime::cacheMap() const {

  std::string mName = mapName();
  DTBufferTree<int,DTMtimeData*>* dBuf =
  DTDataBuffer<int,DTMtimeData*>::openBuffer( mName );

  const_iterator iter = dataList.begin();
  const_iterator iend = dataList.end();
  int    wheelId;
  int  stationId;
  int   sectorId;
  int       slId;
  int    layerId;
  int     cellId;
  while ( iter != iend ) {

    const std::pair<DTMtimeId, DTMtimeData>& link = *iter++;
    const DTMtimeId& chan = link.first;
      wheelId = chan.  wheelId;
    stationId = chan.stationId;
     sectorId = chan. sectorId;
         slId = chan.     slId;
      layerId = chan.  layerId;
       cellId = chan.   cellId;

    const DTMtimeData* dptr = &( link.second );

    std::vector<int> chanKey;
    chanKey.push_back(   wheelId );
    chanKey.push_back( stationId );
    chanKey.push_back(  sectorId );
    chanKey.push_back(      slId );
    chanKey.push_back(   layerId );
    chanKey.push_back(    cellId );
    dBuf->insert( chanKey.begin(), chanKey.end(),
                  const_cast<DTMtimeData*>( dptr ) );

  }

  return;

}

