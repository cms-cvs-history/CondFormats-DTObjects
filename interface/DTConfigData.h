#ifndef DTConfigData_H
#define DTConfigData_H
/** \class DTConfigData
 *
 *  Description: 
 *
 *
 *  $Date: 2007-01-12 11:11:03 $
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


//---------------
// C++ Headers --
//---------------
#include <string>
#include <vector>


//              ---------------------
//              -- Class Interface --
//              ---------------------

class DTConfigData {

 public:

  /** Constructor
   */
  DTConfigData();
  DTConfigData( const DTConfigData& obj );

  /** Destructor
   */
  virtual ~DTConfigData();

  /** Operations
   */
  /// 
  void setId( int id );
  void add( const std::string& data );
  void add( int id );

  typedef std::vector<std::string>::const_iterator data_iterator;
  typedef std::vector<        int>::const_iterator link_iterator;
  data_iterator dataBegin() const;
  data_iterator dataEnd() const;
  link_iterator linkBegin() const;
  link_iterator linkEnd() const;

 private:

  int cfgId;
  std::vector<std::string> dataList; 
  std::vector<int>         linkList; 

};


#endif // DTConfigData_H






