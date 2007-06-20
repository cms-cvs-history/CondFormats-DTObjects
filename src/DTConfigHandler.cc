/*
 *  See header file for a description of this class.
 *
 *  $Date: 2007-01-09 12:33:52 $
 *  $Revision: 1.1 $
 *  \author Paolo Ronchese INFN Padova
 *
 */

//-----------------------
// This Class' Header --
//-----------------------
#include "CondFormats/DTObjects/interface/DTConfigHandler.h"

//-------------------------------
// Collaborating Class Headers --
//-------------------------------
#include "CondTools/DT/interface/DTDBSession.h"
#include "CondFormats/DTObjects/interface/DTDataBuffer.h"

//---------------
// C++ Headers --
//---------------
//#include <iostream>

//-------------------
// Initializations --
//-------------------


//----------------
// Constructors --
//----------------
DTConfigHandler::DTConfigHandler( DTDBSession* session,
                                  const std::string& token ):
  dbSession( session ),
  objToken( token ),
  refSet( 0 ) {
}


//--------------
// Destructor --
//--------------
DTConfigHandler::~DTConfigHandler() {
  purge();
}


//--------------
// Operations --
//--------------
/// create static object
DTConfigHandler* DTConfigHandler::autoPtr( DTDBSession* session,
                                           const std::string& token ) {
//  std::cout << "DTConfigHandler::autoPtr 01" << std::endl;
  std::string mapRefList( "config_obj_ref" );
//  std::cout << "DTConfigHandler::autoPtr 02" << std::endl;
  DTBufferTree<int,DTConfigHandler*>* refListBuf =
  DTDataBuffer<int,DTConfigHandler*>::openBuffer( mapRefList );
//  std::cout << "DTConfigHandler::autoPtr 03" << std::endl;
//  std::cout << "DTConfigHandler::autoPtr 04" << std::endl;
  std::vector<int> configKey;
//  std::cout << "DTConfigHandler::autoPtr 05" << std::endl;
  configKey.push_back( 1 );
//  std::cout << "DTConfigHandler::autoPtr 06" << std::endl;
  DTConfigHandler* configList = 0;
//  std::cout << "DTConfigHandler::autoPtr 07" << std::endl;
  DTBufferTree<int,DTConfigHandler*>::setDefault( 0 );
//  std::cout << "DTConfigHandler::autoPtr 08" << std::endl;
  int error = refListBuf->find( configKey.begin(),
                                configKey.end(), configList );
//  std::cout << "DTConfigHandler::autoPtr 09" << std::endl;
  if ( error ) {
//    std::cout << "DTConfigHandler::autoPtr 10" << std::endl;
    configList = new DTConfigHandler( session, token );
//    std::cout << "DTConfigHandler::autoPtr 11" << std::endl;
    refListBuf->insert( configKey.begin(),
                        configKey.end(), configList );
//    std::cout << "DTConfigHandler::autoPtr 12" << std::endl;
  }
//  std::cout << "DTConfigHandler::autoPtr 13" << std::endl;
  return configList;
}

/// get content
const DTConfigList* DTConfigHandler::getContainer() {
  if ( refSet == 0 ) {
    refSet = new cond::Ref<DTConfigList>( *dbSession->poolDB(), objToken );
//    refSet->markUpdate();
  }
  return refSet->ptr();
}


int DTConfigHandler::get( int cfgId, DTConfigData*& obj ) {

  getContainer();
//  std::cout << "look for object..." << std::endl;
  const_iterator iter = refMap.find( cfgId );

  if ( iter != refMap.end() ) {
//    std::cout << "object found" << std:: endl;
    obj = iter->second->ptr();
    return 0;
  }
  else {
    DTConfigToken token;
//    std::cout << "look for token... " << refSet << std::endl;
    if ( refSet->ptr()->get( cfgId, token ) == 0 ) {
//      std::cout << "token found " << token.ref << std:: endl;
      try {
	std::string actualToken( token.ref );
        int actualId = token.id;
//        std::cout << "check token " << actualToken << std::endl;
        if ( ( actualToken == std::string( "dummyToken" ) ) &&
             ( actualId > 0 ) ) {
//          std::cout << "rebuild token..." << std::endl;
          refSet->ptr()->get( -999999999, token );
          actualToken = compToken( token.ref, actualId );
//          std::cout << "....>" << actualToken << std::endl;
        }
        cond::Ref<DTConfigData>* refObj =
              new cond::Ref<DTConfigData>( *dbSession->poolDB(),
                                           actualToken );
//                                           token.ref );
//        refObj->markUpdate();
        refMap.insert( std::pair<int,cond::Ref<DTConfigData>*>( cfgId,
                                                                refObj ) );
        obj = refObj->ptr();
//        std::cout << "object read" << std:: endl;
        return -1;
      } catch ( const pool::Exception& er ) {
        std::string error( "caught pool::Exception while reading " );
        std::cout << error + er.what() << std::endl;
        obj = 0;
        return 1;
      } catch ( const std::exception& er ) {
        std::string error ( "caught std::exception while reading " );
        std::cout << error + er.what() << std::endl;
        obj = 0;
        return 2;
      } catch ( ... ) {
        std::string error ( "caught unknown exception while reading " );
        std::cout << error << std::endl;
        obj = 0;
        return 99;
      }
    }
    else {
//      std::cout << "token not found" << std:: endl;
      obj = 0;
      return -2;
    }
  }
  return 999;

}


void DTConfigHandler::getData( int cfgId,
                               std::vector<const std::string*>& list ) {
  DTConfigData* obj = 0;
//  if ( get( cfgId, obj ) != 0 ) return; 
  get( cfgId, obj );
  if ( obj == 0 ) return; 
  DTConfigData::data_iterator d_iter = obj->dataBegin();
  DTConfigData::data_iterator d_iend = obj->dataEnd();
  while ( d_iter != d_iend ) list.push_back( &( *d_iter++ ) );
  DTConfigData::link_iterator l_iter = obj->linkBegin();
  DTConfigData::link_iterator l_iend = obj->linkEnd();
  while ( l_iter != l_iend ) getData( *l_iter++, list );
  return;
}


DTConfigHandler::const_iterator DTConfigHandler::begin() const {
  return refMap.begin();
}


DTConfigHandler::const_iterator DTConfigHandler::end() const {
  return refMap.end();
}

void DTConfigHandler::purge() {
//  std::cout << "DTConfigHandler::purge" << std::endl;
  const_iterator iter = refMap.begin();
  const_iterator iend = refMap.end();
  while ( iter != iend ) {
    delete iter->second;
    *iter++;
  }
  refMap.clear();
  delete refSet;
  refSet = 0;
  return;
}


void DTConfigHandler::autoPurge() {
  std::string mapRefList( "config_obj_ref" );
  DTBufferTree<int,DTConfigHandler*>* refListBuf =
  DTDataBuffer<int,DTConfigHandler*>::findBuffer( mapRefList );
  if ( refListBuf != 0 ) {
    std::vector<int> configKey;
    configKey.push_back( 1 );
    DTConfigHandler* configList = 0;
    DTBufferTree<int,DTConfigHandler*>::setDefault( 0 );
    refListBuf->find( configKey.begin(), configKey.end(), configList );
    if ( configList != 0 ) configList->purge();
  }
  return;
}


std::string DTConfigHandler::clone( DTDBSession* newSession,
                                    const std::string& objContainer,
                                    const std::string& refContainer ) {
//  std::cout << "DTConfigHandler::clone - begin" << std::endl;
  const DTConfigList* rs = getContainer();
  DTConfigList* rn = new DTConfigList( rs->version() );
  DTConfigList::const_iterator iter = rs->begin();
  DTConfigList::const_iterator iend = rs->end();
  while ( iter != iend ) {
//    cond::Ref<DTConfigData> sRef( *dbSession->poolDB(),
//                                  iter->second.ref );
    const DTConfigToken& token = iter->second;
    std::string actualToken( token.ref );
    int actualId = token.id;
//    if ( actualId > 35 ) break;
    if ( ( actualToken == std::string( "dummyToken" ) ) &&
         ( actualId > 0 ) ) {
      DTConfigToken chkToken;
      refSet->ptr()->get( -999999999, chkToken );
      actualToken = compToken( chkToken.ref, actualId );
    }
    cond::Ref<DTConfigData> sRef( *dbSession->poolDB(),
                                  actualToken );
//    sRef.markUpdate();
    DTConfigData* ptr = new DTConfigData( *( sRef.ptr() ) );
    cond::Ref<DTConfigData> dRef( *newSession->poolDB(), ptr );
    dRef.markWrite( refContainer );
    DTConfigToken objToken;
    std::string tokenRef( dRef.token() );
    objToken.ref = tokenRef;
    objToken.id = compToken( tokenRef );
    rn->set( iter->first, objToken );
    iter++;
  }
  cond::Ref<DTConfigList> setRef( *newSession->poolDB(), rn );
  setRef.markWrite( objContainer );
  std::string token = setRef.token();
//  std::cout << "DTConfigHandler::clone - end" << std::endl;
  return token;
}


std::string DTConfigHandler::compToken( const std::string& refToken, int id ) {
  std::string actualToken( "" );
  char* buf = new char[9];
  unsigned int iofb = 0;
  unsigned int iofe = 0;
  while ( true ) {
    iofb = refToken.find( "[", iofb );
    if ( iofb == std::string::npos ) break;
    iofe = refToken.find( "]", iofb );
    std::string sub( refToken.substr( iofb, 1 + iofe - iofb ) );
//    std::cout << sub << std::endl;
    iofb = sub.find( "=", 0 );
    std::string key( sub.substr( 1, iofb ) );
//    std::cout << key << std::endl;
    if ( key == std::string( "OID=" ) ) {
      iofb = 1 + sub.find( "-", 0 );
//      std::cout << iofb << " " << sub.length() << std::endl;
      std::string val( sub.substr( iofb, sub.length() - iofb - 1 ) );
//      std::cout << val <<std:: endl;
      actualToken += sub.substr( 0, iofb );
      sprintf( buf, "%8.8x", id );
//      std::cout << buf << std::endl;
      actualToken += buf;
      actualToken += "]";
    }
    else {
      actualToken += sub;
    }
    iofb = iofe;
  }
  delete[] buf;
  return actualToken;
}


int DTConfigHandler::compToken( const std::string& refToken ) {
  unsigned int iofb = 0;
  unsigned int iofe = 0;
  unsigned tokenId;
  while ( true ) {
    iofb = refToken.find( "[", iofb );
    if ( iofb == std::string::npos ) break;
    iofe = refToken.find( "]", iofb );
    std::string sub( refToken.substr( iofb, 1 + iofe - iofb ) );
    iofb = sub.find( "=", 0 );
    std::string key( sub.substr( 1, iofb ) );
    if ( key == std::string( "OID=" ) ) {
      iofb = 1 + sub.find( "-", 0 );
      std::string val( sub.substr( iofb, sub.length() - iofb - 1 ) );
      sscanf( val.c_str(), "%x", &tokenId );
//      std::cout << val << " ---> " << tokenId << std::endl;
      break;
    }
    iofb = iofe;
  }
  return tokenId;
}


