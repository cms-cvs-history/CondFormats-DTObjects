/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007/01/22 18:24:45 $
 *  $Revision: 1.3 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// This Class' Header --
//----------------------
#include "CondFormats/DTObjects/interface/DTPerformance.h"
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
DTPerformance::DTPerformance():
  dataVersion( " " ) {
}


DTPerformance::DTPerformance( const std::string& version ):
  dataVersion( version ) {
}


DTPerformanceId::DTPerformanceId() :
    wheelId( 0 ),
  stationId( 0 ),
   sectorId( 0 ),
       slId( 0 ) {
}


DTPerformanceData::DTPerformanceData() :
  meanT0(         0.0 ),
  meanTtrig(      0.0 ),
  meanMtime(      0.0 ),
  meanNoise(      0.0 ),
  meanAfterPulse( 0.0 ),
  meanResolution( 0.0 ),
  meanEfficiency( 0.0 ) {
}


//--------------
// Destructor --
//--------------
DTPerformance::~DTPerformance() {
  DTDataBuffer<int,DTPerformanceData*>::dropBuffer( mapName() );
}


DTPerformanceData::~DTPerformanceData() {
}


DTPerformanceId::~DTPerformanceId() {
}


//--------------
// Operations --
//--------------
int DTPerformance::get( int   wheelId,
                        int stationId,
                        int  sectorId,
                        int      slId,
                        float& meanT0,
                        float& meanTtrig,
                        float& meanMtime,
                        float& meanNoise,
                        float& meanAfterPulse,
                        float& meanResolution,
                        float& meanEfficiency,
                        DTTimeUnits::type unit ) const {

  meanT0         =
  meanTtrig      =
  meanMtime      =
  meanNoise      =
  meanAfterPulse =
  meanResolution =
  meanEfficiency = 0.0;

  std::string mName = mapName();
  DTBufferTree<int,DTPerformanceData*>* dBuf =
  DTDataBuffer<int,DTPerformanceData*>::findBuffer( mName );
  if ( dBuf == 0 ) {
    cacheMap();
    dBuf =
    DTDataBuffer<int,DTPerformanceData*>::findBuffer( mName );
  }
  std::vector<int> chanKey;
  chanKey.push_back(   wheelId );
  chanKey.push_back( stationId );
  chanKey.push_back(  sectorId );
  chanKey.push_back(      slId );
  DTPerformanceData* data;
  int searchStatus = dBuf->find( chanKey.begin(), chanKey.end(), data );
  if ( !searchStatus ) {
    meanT0         = data->meanT0;
    meanTtrig      = data->meanTtrig;
    meanMtime      = data->meanMtime;
    meanNoise      = data->meanNoise;
    meanAfterPulse = data->meanAfterPulse;
    meanResolution = data->meanResolution;
    meanEfficiency = data->meanEfficiency;
    if ( unit == DTTimeUnits::ns ) {
      meanT0    *= nsPerCount;
      meanTtrig *= nsPerCount;
      meanMtime *= nsPerCount;
    }
  }

  return searchStatus;

}


int DTPerformance::get( const DTSuperLayerId& id,
                        float& meanT0,
                        float& meanTtrig,
                        float& meanMtime,
                        float& meanNoise,
                        float& meanAfterPulse,
                        float& meanResolution,
                        float& meanEfficiency,
                        DTTimeUnits::type unit ) const {
  return get( id.wheel(),
              id.station(),
              id.sector(),
              id.superLayer(),
              meanT0,
              meanTtrig,
              meanMtime,
              meanNoise,
              meanAfterPulse,
              meanResolution,
              meanEfficiency,
              unit );
}


float DTPerformance::unit() const {
  return nsPerCount;
}


const
std::string& DTPerformance::version() const {
  return dataVersion;
}


std::string& DTPerformance::version() {
  return dataVersion;
}


void DTPerformance::clear() {
  dataList.clear();
  return;
}


int DTPerformance::set( int   wheelId,
                        int stationId,
                        int  sectorId,
                        int      slId,
                        float meanT0,
                        float meanTtrig,
                        float meanMtime,
                        float meanNoise,
                        float meanAfterPulse,
                        float meanResolution,
                        float meanEfficiency,
                        DTTimeUnits::type unit ) {

  if ( unit == DTTimeUnits::ns ) {
    meanT0    /= nsPerCount;
    meanTtrig /= nsPerCount;
    meanMtime /= nsPerCount;
  }

  std::string mName = mapName();
  DTBufferTree<int,DTPerformanceData*>* dBuf =
  DTDataBuffer<int,DTPerformanceData*>::findBuffer( mName );
  if ( dBuf == 0 ) {
    cacheMap();
    dBuf =
    DTDataBuffer<int,DTPerformanceData*>::findBuffer( mName );
  }
  std::vector<int> chanKey;
  chanKey.push_back(   wheelId );
  chanKey.push_back( stationId );
  chanKey.push_back(  sectorId );
  chanKey.push_back(      slId );
  DTPerformanceData* dptr;
  int searchStatus = dBuf->find( chanKey.begin(), chanKey.end(), dptr );

  if ( !searchStatus ) {
    DTPerformanceData& data = *dptr;
    data.meanT0         = meanT0;
    data.meanTtrig      = meanTtrig;
    data.meanMtime      = meanMtime;
    data.meanNoise      = meanNoise;
    data.meanAfterPulse = meanAfterPulse;
    data.meanResolution = meanResolution;
    data.meanEfficiency = meanEfficiency;
    return -1;
  }
  else {
    DTPerformanceId key;
    key.  wheelId =   wheelId;
    key.stationId = stationId;
    key. sectorId =  sectorId;
    key.     slId =      slId;
    DTPerformanceData data;
    data.meanT0         = meanT0;
    data.meanTtrig      = meanTtrig;
    data.meanMtime      = meanMtime;
    data.meanNoise      = meanNoise;
    data.meanAfterPulse = meanAfterPulse;
    data.meanResolution = meanResolution;
    data.meanEfficiency = meanEfficiency;
    dataList.push_back( std::pair<DTPerformanceId,DTPerformanceData>(
                        key, data ) );
    DTPerformanceData* dptr = &( dataList.back().second );
    dBuf->insert( chanKey.begin(), chanKey.end(), dptr  );
    return 0;
  }

  return 99;

}


int DTPerformance::set( const DTSuperLayerId& id,
                        float meanT0,
                        float meanTtrig,
                        float meanMtime,
                        float meanNoise,
                        float meanAfterPulse,
                        float meanResolution,
                        float meanEfficiency,
                        DTTimeUnits::type unit ) {
  return set( id.wheel(),
              id.station(),
              id.sector(),
              id.superLayer(),
              meanT0,
              meanTtrig,
              meanMtime,
              meanNoise,
              meanAfterPulse,
              meanResolution,
              meanEfficiency,
              unit );
}


void DTPerformance::setUnit( float unit ) {
  nsPerCount = unit;
}


DTPerformance::const_iterator DTPerformance::begin() const {
  return dataList.begin();
}


DTPerformance::const_iterator DTPerformance::end() const {
  return dataList.end();
}


std::string DTPerformance::mapName() const {
  std::string name = dataVersion + "_map_Performance";
  char nptr[100];
  sprintf( nptr, "%x", reinterpret_cast<unsigned int>( this ) );
  name += nptr;
  return name;
}


void DTPerformance::cacheMap() const {

  std::string mName = mapName();
  DTBufferTree<int,DTPerformanceData*>* dBuf =
  DTDataBuffer<int,DTPerformanceData*>::openBuffer( mName );

  const_iterator iter = dataList.begin();
  const_iterator iend = dataList.end();
  int    wheelId;
  int  stationId;
  int   sectorId;
  int       slId;
  while ( iter != iend ) {

    const std::pair<DTPerformanceId, DTPerformanceData>& link = *iter++;
    const DTPerformanceId& chan = link.first;
      wheelId = chan.  wheelId;
    stationId = chan.stationId;
     sectorId = chan. sectorId;
         slId = chan.     slId;

    const DTPerformanceData* dptr = &( link.second );

    std::vector<int> chanKey;
    chanKey.push_back(   wheelId );
    chanKey.push_back( stationId );
    chanKey.push_back(  sectorId );
    chanKey.push_back(      slId );
    dBuf->insert( chanKey.begin(), chanKey.end(),
                  const_cast<DTPerformanceData*>( dptr ) );

  }

  return;

}

