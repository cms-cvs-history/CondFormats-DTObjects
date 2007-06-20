#include "CondFormats/DTObjects/interface/DTConfigList.h"
#include "CondFormats/DTObjects/interface/DTConfigHandler.h"
#include "CondTools/DT/interface/DTDBSession.h"
//#include "CondTools/DT/interface/DTDBWriter.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>

int main( int arc, char* argv[] ){

  std::string contact( argv[1] );
  std::string catalog( argv[2] );
  DTDBSession* session = new DTDBSession( contact, catalog, "" );
//  DTDBSession* session = new DTDBSession( contact, catalog, cond::Env );
//  DTDBSession* session = new DTDBSession( "sqlite_file:test.db",
//                                          "file:testcatalog.xml",
//                                          cond::Env );
  std::cout << "01 " << std::endl;
  session->connect( false );
  std::cout << "02 " << std::endl;
  std::cout << "03 " << std::endl;
  std::cout << "04 " << std::endl;

  DTConfigList* rs = new DTConfigList( "list_ref" );

  int dummyId = -999999999;
  DTConfigData* obj = new DTConfigData();
  obj->setId( dummyId );
  cond::Ref<DTConfigData> objRef( *session->poolDB(), obj );
  objRef.markWrite( "DTConfigData" );
  DTConfigToken token;
  token.id  = 0;
  token.ref = objRef.token();
  rs->set( dummyId, token );

/*
  DTConfigList* rs;
  rs = 0;

  std::string mytok=argv[3];
  std::cout << "create session" << std::endl;
//  DTConfigHandler ri( session, mytok );
//  std::cout << "get container" << std::endl;
//  rs = ri.getContainer();
  cond::Ref<DTConfigList> refSet( *session->poolDB(), mytok );
  refSet.markUpdate();
  rs = refSet.ptr();
  std::cout << rs->version() << std::endl;
  std::cout << std::distance( rs->begin(), rs->end() )
            << " refs in the object " << rs << std::endl;
*/

/*
  int dummyId = 42;
//  int dummyId = -999999;
  DTConfigData* obj = new DTConfigData();
  obj->setId( dummyId );
  cond::Ref<DTConfigData> objRef( *session->poolDB(), obj );
  objRef.markWrite( "DTConfigData" );
  DTConfigToken token;
  token.id  = -999999999;
  token.ref = objRef.token();
  rs->set( dummyId, token );
*/
/*
  int dummyId = 42;
  DTConfigList::const_iterator iter = rs->begin();
  DTConfigList::const_iterator iend = rs->end();
  while ( iter != iend ) {
    if ( iter->first == dummyId ) {
      std::cout << iter->second.ref << std::endl;
//      cond::Ref<DTConfigData> objRef( *session->poolDB(), iter->second.ref );
      cond::Ref<DTConfigData> objRef( *session->poolDB(), "[DB=FE6848F6-A6D0-DB11-B86F-000E0C5CE282][CNT=DTConfigData][CLID=3858CAFE-30A2-DB11-9E86-000E0C5CE283][TECH=00000B01][OID=00000003-00000027]" );
      objRef.markDelete();
    }
    ++iter;
  }
*/

/*
  DTConfigData* obj1 = new DTConfigData();
  obj1->setId( 1 );
  obj1->add( "string11" );
  obj1->add( "string12" );
  obj1->add( "string13" );
  DTConfigData* obj2 = new DTConfigData();
  obj2->setId( 2 );
  obj2->add( "string21" );
  obj2->add( "string22" );
  obj2->add( "string23" );
  DTConfigData* obj3 = new DTConfigData();
  obj3->setId( 3 );
  obj3->add( "string31" );
  obj3->add( "string32" );
  obj3->add( "string33" );
  DTConfigData* obj4 = new DTConfigData();
  obj4->setId( 4 );
  obj4->add( "string41" );
  obj4->add( "string42" );
  obj4->add( "string43" );
  obj4->add( 1 );
  obj4->add( 2 );
  DTConfigData* obj5 = new DTConfigData();
  obj5->setId( 5 );
  obj5->add( "string51" );
  obj5->add( "string52" );
  obj5->add( "string53" );
  obj5->add( 3 );
  DTConfigData* obj6 = new DTConfigData();
  obj6->setId( 6 );
  obj6->add( "string61" );
  obj6->add( "string62" );
  obj6->add( "string63" );
  obj6->add( 1 );
  obj6->add( 5 );

  cond::Ref<DTConfigData> objRef1( *session->poolDB(), obj1 );
  cond::Ref<DTConfigData> objRef2( *session->poolDB(), obj2 );
  cond::Ref<DTConfigData> objRef3( *session->poolDB(), obj3 );
  cond::Ref<DTConfigData> objRef4( *session->poolDB(), obj4 );
  cond::Ref<DTConfigData> objRef5( *session->poolDB(), obj5 );
  cond::Ref<DTConfigData> objRef6( *session->poolDB(), obj6 );

  objRef1.markWrite( "Refsr" );
  objRef2.markWrite( "Refsr" );
  objRef3.markWrite( "Refsr" );
  objRef4.markWrite( "Refsr" );
  objRef5.markWrite( "Refsr" );
  objRef6.markWrite( "Refsr" );

  DTConfigToken token1;
  DTConfigToken token2;
  DTConfigToken token3;
  DTConfigToken token4;
  DTConfigToken token5;
  DTConfigToken token6;

  token1.id  = -999999999;
  token2.id  = -999999999;
  token3.id  = -999999999;
  token4.id  = -999999999;
  token5.id  = -999999999;
  token6.id  = -999999999;
  token1.ref = objRef1.token();
  token2.ref = objRef2.token();
  token3.ref = objRef3.token();
  token4.ref = objRef4.token();
  token5.ref = objRef5.token();
  token6.ref = objRef6.token();

  rs->set( 1, token1 );
  rs->set( 2, token2 );
  rs->set( 3, token3 );
  rs->set( 4, token4 );
  rs->set( 5, token5 );
  rs->set( 6, token6 );
*/

  cond::Ref<DTConfigList> setRef( *session->poolDB(), rs );
  setRef.markWrite( "DTConfigList" );
  std::string mytok = setRef.token();
/*
*/

  std::cout << "obj: " << mytok      << std::endl;

  std::cout << "91" << std::endl;
  session->disconnect();
  std::cout << "92" << std::endl;
  delete session;
  std::cout << "93" << std::endl;
  return 0;

}
