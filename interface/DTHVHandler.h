#ifndef DTHVHandler_H
#define DTHVHandler_H
/** \class DTHVHandler
 *
 *  Description:
 *       Class to analyze high voltage status
 *
 *  $Date: 2009/03/26 14:11:03 $
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
class DTHVStatus;
class DTChamberId;
class DTWireId;

//---------------
// C++ Headers --
//---------------
#include <string>
#include <vector>

//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTHVHandler {

 public:

  /** Constructor
   */
  DTHVHandler();
  DTHVHandler( const DTHVStatus* dbObject );

  /** Destructor
   */
  ~DTHVHandler();

  /** Operations
   */
  /// get content
  int get( const DTWireId& id,
           int&         flagA,
           int&         flagC,
           int&         flagS ) const;
  int offChannelsNumber() const; 
  int offChannelsNumber( const DTChamberId& id ) const; 
  /// access db object
  const DTHVStatus* getDBObject() const;

 private:

  const DTHVStatus* objectPtr;

};


#endif // DTHVHandler_H

