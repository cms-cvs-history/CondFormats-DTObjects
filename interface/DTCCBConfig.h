#ifndef DTCCBConfig_H
#define DTCCBConfig_H
/** \class DTCCBConfig
 *
 *  Description:
 *       Class to hold configuration identifier for chambers
 *
 *  $Date: 2007-01-09 12:33:52 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "DataFormats/MuonDetId/interface/DTChamberId.h"
//#include "CondFormats/DTObjects/interface/DTConfigHandler.h"

//---------------
// C++ Headers --
//---------------
#include <string>
#include <vector>
#include <map>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTCCBId {

 public:

  DTCCBId();
  ~DTCCBId();

  int   wheelId;
  int stationId;
  int  sectorId;

};


class DTCCBCompare {
 public:
  bool operator()( const DTCCBId& idl,
                   const DTCCBId& idr ) const;
};


class DTCCBConfig {

 public:

  /** Constructor
   */
  DTCCBConfig();
  DTCCBConfig( const std::string& version );

  /** Destructor
   */
  virtual ~DTCCBConfig();

  /** Operations
   */
  /// get content
  int fullKey() const;
  int stamp() const;
  int configKey( int   wheelId,
                 int stationId,
                 int  sectorId,
                 std::vector<int>& confKey ) const;
  int configKey( const DTChamberId& id,
                 std::vector<int>& confKey ) const;

//  DTConfigHandler* getHandler() const;

  /// access version
  const
  std::string& version() const;
  std::string& version();

  /// reset content
  void clear();

  void setFullKey( int key );
  void setStamp( int s );

  int setConfigKey( int   wheelId,
                    int stationId,
                    int  sectorId,
                    const std::vector<int>& confKey );
  int setConfigKey( const DTChamberId& id,
                    const std::vector<int>& confKey );

  /// Access methods to data
  typedef std::map<DTCCBId,std::vector<int>,DTCCBCompare>::const_iterator const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

 private:

  int timeStamp;
  std::string dataVersion;
  int fullConfigKey;
  std::map<DTCCBId,std::vector<int>,DTCCBCompare> ccbData;

};


#endif // DTCCBConfig_H

