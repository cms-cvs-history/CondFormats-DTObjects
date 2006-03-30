#ifndef DTDataBuffer_H
#define DTDataBuffer_H
/** \class DTDataBuffer
 *
 *  Description:
 *       Class to hold drift tubes T0s
 *
 *  $Date: 2006/02/28 17:28:55 $
 *  $Revision: 1.3 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//----------------------
// Base Class Headers --
//----------------------


//------------------------------------
// Collaborating Class Declarations --
//------------------------------------
#include "CondFormats/DTObjects/interface/DTBufferTree.h"

//---------------
// C++ Headers --
//---------------
#include <string>
#include <map>

//              ---------------------
//              -- Class Interface --
//              ---------------------

template <class Key, class Content>
class DTDataBuffer {

 public:

  /** Constructor
   */
  DTDataBuffer();

  /** Destructor
   */
  ~DTDataBuffer();

  /** Operations
   */
  /// access internal buffer
  static DTBufferTree<Key,Content>* openBuffer( std::string& name );
  static DTBufferTree<Key,Content>* findBuffer( std::string& name );
  static void                       dropBuffer( std::string& name );

 private:

  static std::map<std::string,DTBufferTree<Key,Content>*> bufferMap;

};

#include "DTDataBuffer.icc"

#endif // DTDataBuffer_H

