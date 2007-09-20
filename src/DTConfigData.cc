/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007-01-12 11:11:03 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondFormats/DTObjects/interface/DTConfigData.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------


//---------------
// C++ Headers --
//---------------
#include <iostream>


//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTConfigData::DTConfigData() {
}


DTConfigData::DTConfigData( const DTConfigData& obj ) {
//  std::cout << "create DTConfigData: " << this << std::endl;
  cfgId = obj.cfgId;
  data_iterator d_iter = obj.dataList.begin();
  data_iterator d_iend = obj.dataList.end();
  while ( d_iter != d_iend ) dataList.push_back( *d_iter++ );
  link_iterator l_iter = obj.linkList.begin();
  link_iterator l_iend = obj.linkList.end();
  while ( l_iter != l_iend ) linkList.push_back( *l_iter++ );
}


//--------------
// Destructor --
//--------------
DTConfigData::~DTConfigData() {
//  std::cout << "delete DTConfigData " << this << std::endl;
}

//--------------
// Operations --
//--------------
void DTConfigData::setId( int id ) {
  cfgId = id;
}


void DTConfigData::add( const std::string& data ) {
  dataList.push_back( data );
}


void DTConfigData::add( int id ) {
  linkList.push_back( id );
}


DTConfigData::data_iterator DTConfigData::dataBegin() const {
  return dataList.begin();
}


DTConfigData::data_iterator DTConfigData::dataEnd() const {
  return dataList.end();
}


DTConfigData::link_iterator DTConfigData::linkBegin() const {
  return linkList.begin();
}


DTConfigData::link_iterator DTConfigData::linkEnd() const {
  return linkList.end();
}





