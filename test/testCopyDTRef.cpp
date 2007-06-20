#include "CondFormats/DTObjects/interface/DTConfigList.h"
#include "CondFormats/DTObjects/interface/DTConfigHandler.h"
//#include "CondTools/DT/interface/DTDBWriter.h"
#include "CondTools/DT/interface/DTDBSession.h"

#include <string>
#include <map>
#include <iostream>
#include <fstream>

int main( int argc, char* argv[] ){

  std::string contactS( argv[1] );
  std::string catalogS( argv[2] );
//  DTDBSession* session1 = new DTDBSession( contactS, catalogS, cond::XML );
  DTDBSession* session1 = new DTDBSession( contactS, catalogS,
               "/afs/cern.ch/cms/DB/conddb" );
  std::string contactD( argv[3] );
  std::string catalogD( argv[4] );
//  DTDBSession* session2 = new DTDBSession( contactD, catalogD, cond::XML );
  DTDBSession* session2 = new DTDBSession( contactD, catalogD,
               "/afs/cern.ch/cms/DB/conddb" );
//  DTDBSession* session1 = new DTDBSession( "sqlite_file:test.db",
//                                           "file:testcatalog.xml" );
//  DTDBSession* session2 = new DTDBSession( "sqlite_file:test2.db",
//                                           "file:testcatalog.xml" );
  session1->connect( false );
  session2->connect( false );

  const DTConfigList* rs;
  rs = 0;

  std::string mytok=argv[5];
  std::cout << mytok << std::endl;
  DTConfigHandler ri( session1, mytok );
  rs = ri.getContainer();
  std::cout << rs << std::endl;
  std::cout << "1" << std::endl;
  std::string tokclo;
  tokclo = ri.clone( session2, "DTConfigList", "DTConfigData" );
//  tokclo = ri.clone( session2, "Refs", "Refsr" );
  std::cout << "copied: " << tokclo      << std::endl;

  session1->disconnect();
  session2->disconnect();
  delete session1;
  delete session2;
  return 0;

}
