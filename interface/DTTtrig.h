#ifndef DTTtrig_H
#define DTTtrig_H
/** \class DTTtrig
 *
 *  Description:
 *       Class to hold drift tubes TTrigs
 *             ( SL by SL time offsets )
 *
 *  $Date: 2008/09/29 13:10:34 $
 *  $Revision: 1.7 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "CondFormats/DTObjects/interface/DTTimeUnits.h"
#include "DataFormats/MuonDetId/interface/DTWireId.h"
#include "DataFormats/MuonDetId/interface/DTSuperLayerId.h"

//---------------
// C++ Headers --
//---------------
#include <string>
#include <vector>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTTtrigId   {

 public:

  DTTtrigId();
  ~DTTtrigId();

  int   wheelId;
  int stationId;
  int  sectorId;
  int      slId;
  int   layerId;
  int    cellId;

};


class DTTtrigData {

 public:

  DTTtrigData();
  ~DTTtrigData();

  float tTrig;
  float tTrms;
  float kFact;

};


class DTTtrig {

 public:

  /** Constructor
   */
  DTTtrig();
  DTTtrig( const std::string& version );

  /** Destructor
   */
  ~DTTtrig();

  /** Operations
   */
  /// get content
  int get( int   wheelId,
           int stationId,
           int  sectorId,
           int      slId,
           float&  tTrig,
           float&  tTrms,
           float&  kFact,
           DTTimeUnits::type unit ) const;
  int get( int   wheelId,
           int stationId,
           int  sectorId,
           int      slId,
           int   layerId,
           int    cellId,
           float&  tTrig,
           float&  tTrms,
           float&  kFact,
           DTTimeUnits::type unit ) const;
  int get( const DTSuperLayerId& id,
           float&  tTrig,
           float&  tTrms,
           float&  kFact,
           DTTimeUnits::type unit ) const;
  int get( const DetId& id,
           float&  tTrig,
           float&  tTrms,
           float&  kFact,
           DTTimeUnits::type unit ) const;
  float unit() const;

  /// access version
  const
  std::string& version() const;
  std::string& version();

  /// reset content
  void clear();

  int set( int   wheelId,
           int stationId,
           int  sectorId,
           int      slId,
           float   tTrig,
           float   tTrms,
           float   kFact,
           DTTimeUnits::type unit );
  int set( int   wheelId,
           int stationId,
           int  sectorId,
           int      slId,
           int   layerId,
           int    cellId,
           float   tTrig,
           float   tTrms,
           float   kFact,
           DTTimeUnits::type unit );
  int set( const DTSuperLayerId& id,
           float   tTrig,
           float   tTrms,
           float   kFact,
           DTTimeUnits::type unit );
  int set( const DetId& id,
           float   tTrig,
           float   tTrms,
           float   kFact,
           DTTimeUnits::type unit );
  void setUnit( float unit );

  /// Access methods to data
  typedef std::vector< std::pair<DTTtrigId,
                                 DTTtrigData> >::const_iterator
                                                 const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

 private:

  std::string dataVersion;
  float nsPerCount;

  std::vector< std::pair<DTTtrigId,DTTtrigData> > dataList;

  /// read and store full content
  void cacheMap() const;
  std::string mapName() const;

};


#endif // DTTtrig_H

