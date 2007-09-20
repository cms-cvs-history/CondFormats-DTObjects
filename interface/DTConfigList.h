#ifndef DTConfigList_H
#define DTConfigList_H
/** \class DTConfigList
 *
 *  Description:
 *       Class to hold configuration identifier for chambers
 *
 *  $Date: 2007/06/20 17:45:30 $
 *  $Revision: 1.1.2.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
//#include "CondFormats/DTObjects/interface/DTConfigData.h"

//---------------
// C++ Headers --
//---------------
#include <string>
#include <map>

//              ---------------------
//              -- Class Interface --
//              ---------------------
class DTConfigToken {

 public:

  DTConfigToken();
  ~DTConfigToken();

  int id;
  std::string ref;

};


class DTConfigList {

 public:

  /** Constructor
   */
  DTConfigList();
  DTConfigList( const std::string& version );

  /** Destructor
   */
  virtual ~DTConfigList();

  /** Operations
   */
  /// get content
  int get( int id,
           DTConfigToken& token ) const;

  /// access version
  const
  std::string& version() const;
  std::string& version();

  /// reset content
  void clear();

  int set( int id, const DTConfigToken& token );
  /// Access methods to data
  typedef std::map<int,DTConfigToken>::const_iterator const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

  /// copy to other DB
 private:

  DTConfigList( const DTConfigList& x );
  const DTConfigList& operator=( const DTConfigList& x );

  std::string dataVersion;
  std::map<int,DTConfigToken> refMap;

};


#endif // DTConfigList_H

