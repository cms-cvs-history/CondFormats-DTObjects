#ifndef DTConfigHandler_H
#define DTConfigHandler_H
/** \class DTConfigHandler
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
#include "CondFormats/DTObjects/interface/DTConfigList.h"
#include "CondFormats/DTObjects/interface/DTConfigData.h"
#include "CondCore/DBCommon/interface/Ref.h"
class DTDBSession;

//---------------
// C++ Headers --
//---------------
#include <string>
#include <map>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTConfigHandler {

 public:

  /** Constructor
   */
  DTConfigHandler( DTDBSession* session, const std::string& token );

  /** Destructor
   */
  virtual ~DTConfigHandler();

  /** Operations
   */
  /// create static object
  static DTConfigHandler* autoPtr( DTDBSession* session,
                                   const std::string& token );

  /// get content
  const DTConfigList* getContainer();
  int get( int cfgId, DTConfigData*& obj );

  void getData( int cfgId, std::vector<const std::string*>& list );

  /// Access methods to data
  typedef std::map<int,
                   cond::Ref<DTConfigData>*>::const_iterator const_iterator;
  const_iterator begin() const;
  const_iterator end() const;

  /// purge db copy
  void purge();
  static void autoPurge();

  /// copy to other DB
  std::string clone( DTDBSession* newSession,
                     const std::string& objContainer,
                     const std::string& refContainer );

 private:

  DTConfigHandler( const DTConfigHandler& x );
  const DTConfigHandler& operator=( const DTConfigHandler& x );

  static std::string compToken( const std::string& token, int id );
  static int         compToken( const std::string& token );

  DTDBSession* dbSession;
  std::string objToken;
  cond::Ref<DTConfigList>* refSet;
  std::map<int,cond::Ref<DTConfigData>*> refMap;

};


#endif // DTConfigHandler_H






