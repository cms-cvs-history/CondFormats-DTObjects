#ifndef DTDBAbstractSession_H
#define DTDBAbstractSession_H
/** \class DTDBAbstractSession
 *
 *  Description: 
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

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
namespace edm {
  class Event;
  class EventSetup;
  class ParameterSet;
}
namespace cond{
  class PoolTransaction;
  class Connection;
  class DBSession;
}
#include <string>
#include <map>

//---------------
// C++ Headers --
//---------------
#include <string>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTDBAbstractSession {

 public:

  /** Constructor
   */
  DTDBAbstractSession();
  DTDBAbstractSession( const std::string& dbFile,
                       const std::string& dbCatalog,
                       const std::string& auth_path,
                       bool siteLocalConfig = false );

  /** Destructor
   */
  virtual ~DTDBAbstractSession();

  /** Operations
   */
  /// get storage manager
  virtual cond::PoolTransaction* poolDB() const;

  /// start transaction
  virtual void connect( bool readOnly );
  /// end   transaction
  virtual void disconnect();

 protected:

  DTDBAbstractSession* instance;

 private:

};


#endif // DTDBAbstractSession_H

