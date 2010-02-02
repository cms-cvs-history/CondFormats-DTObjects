#ifndef DTAbstractSessionFactory_H
#define DTAbstractSessionFactory_H
/** \class DTAbstractSessionFactory
 *
 *  Description: 
 *    abstract interface for DB session factory
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
class DTDBAbstractSession;
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


//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTAbstractSessionFactory {

 public:

  /** Constructor
   */
  DTAbstractSessionFactory();

  /** Destructor
   */
  virtual ~DTAbstractSessionFactory();

  /** Operations
   */
  /// get instance pointer
  static DTAbstractSessionFactory* getInstance();

  /// create DB session pointer
  virtual DTDBAbstractSession* createSession( const std::string& dbFile,
                                              const std::string& dbCatalog,
                                              const std::string& auth_path,
                                              bool siteLocalConfig = false );

 protected:

  static DTAbstractSessionFactory* instance;

 private:


};


#endif // DTAbstractSessionFactory_H

