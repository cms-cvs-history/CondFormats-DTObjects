#include "CondFormats/DTObjects/interface/DTConfigList.h"
#include "CondFormats/DTObjects/interface/DTConfigHandler.h"
#include "CondTools/DT/interface/DTDBSession.h"
//#include "CondTools/DT/interface/DTDBWriter.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>

int main( int argc, char* argv[] ){

  std::string contact( argv[1] );
  std::string catalog( argv[2] );
  DTDBSession* session = new DTDBSession( contact, catalog, "" );
//  DTDBSession* session = new DTDBSession( contact, catalog, cond::Env );
//  DTDBSession* session = new DTDBSession( "test.db" ,"file:testcatalog.xml" );
  session->connect( false );
  const DTConfigList* rs;
  rs = 0;

  std::string mytok=argv[3];
  std::cout << "create session" << std::endl;
  DTConfigHandler ri( session, mytok );
  std::cout << "get container" << std::endl;
  rs = ri.getContainer();
  std::cout << rs->version() << std::endl;
  std::cout << std::distance( rs->begin(), rs->end() )
            << " refs in the object " << rs << std::endl;
  DTConfigList::const_iterator iter = rs->begin();
  DTConfigList::const_iterator iend = rs->end();
  while ( iter != iend ) {
    int id = iter->first;
    std::cout << id << " -> "
              << iter->second.ref << std::endl;
    std::cout << "========> " << std::endl;
    DTConfigData* obj;
    ri.get( id, obj );
    std::cout << id << "--->" << std::endl;
    DTConfigData::data_iterator d_iter = obj->dataBegin();
    DTConfigData::data_iterator d_iend = obj->dataEnd();
    while ( d_iter != d_iend ) std::cout << "    " << *d_iter++
                                         << std:: endl;
    DTConfigData::link_iterator l_iter = obj->linkBegin();
    DTConfigData::link_iterator l_iend = obj->linkEnd();
    while ( l_iter != l_iend ) std::cout << "     + " << *l_iter++
                                         << std:: endl;
    std::vector<const std::string*> list;
    ri.getData( id, list );
    std::vector<const std::string*>::const_iterator s_iter = list.begin();
    std::vector<const std::string*>::const_iterator s_iend = list.end();
    while ( s_iter != s_iend ) std::cout << "        ----> "
                                         << **s_iter++ << std::endl;
    iter++;
  }
  session->disconnect();
  delete session;
  return 0;

}
