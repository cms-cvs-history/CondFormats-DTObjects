#ifndef DTConfigAbstractHandler_H
#define DTConfigAbstractHandler_H
/** \class DTConfigAbstractHandler
 *
 *  Description:
 *       Class to hold configuration identifier for chambers
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
#include "CondFormats/DTObjects/interface/DTConfigList.h"
#include "CondFormats/DTObjects/interface/DTConfigData.h"
namespace cond{
  template <typename T> class TypedRef;
}
class DTDBAbstractSession;

//---------------
// C++ Headers --
//---------------
#include <string>
#include <map>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTConfigAbstractHandler {

 public:

  /** Constructor
   */
  DTConfigAbstractHandler();

  /** Destructor
   */
  virtual ~DTConfigAbstractHandler();

  /** Operations
   */
  /// create static object
  static DTConfigAbstractHandler* create( DTDBAbstractSession* session,
                                          const std::string& token );
  static void remove( const DTDBAbstractSession* session );
  static void remove( const DTConfigAbstractHandler* handler );

  /// get content
  virtual const DTConfigList* getContainer();
  virtual int get( int cfgId, DTConfigData*& obj );

  virtual void getData( int cfgId, std::vector<const std::string*>& list );

  virtual int set( int cfgId, const std::string& token );
  /// Access methods to data
  typedef std::map< int, cond::TypedRef<DTConfigData>* >::const_iterator
                                                          const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

  /// purge db copy
  virtual void purge();

  /// copy to other DB
  virtual std::string clone( DTDBAbstractSession* newSession,
                             const std::string& newToken,
                             const std::string& objContainer,
                             const std::string& refContainer );

  static int maxBrickNumber;
  static int maxStringNumber;
  static int maxByteNumber;

 protected:

  /** Destructor
   */
//  virtual ~DTConfigAbstractHandler();

  std::map<int,cond::TypedRef<DTConfigData>*> refMap;
  static DTConfigAbstractHandler* instance;

 private:

  virtual DTConfigAbstractHandler* build( DTDBAbstractSession* session,
                                          const std::string& token );
  virtual void destroy( const DTDBAbstractSession* session );
  virtual void destroy( const DTConfigAbstractHandler* handler );

};


#endif // DTConfigAbstractHandler_H

