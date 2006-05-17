#include "CondFormats/DTObjects/interface/DTRangeT0.h"

#include "CondCore/DBCommon/interface/DBWriter.h"
#include "CondCore/DBCommon/interface/DBSession.h"
#include "CondCore/DBCommon/interface/Exception.h"
#include "CondCore/DBCommon/interface/ServiceLoader.h"
#include "CondCore/DBCommon/interface/ConnectMode.h"
#include "CondCore/DBCommon/interface/MessageLevel.h"
#include "CondCore/IOVService/interface/IOV.h"
#include "CondCore/MetaDataService/interface/MetaData.h"
#include "FWCore/Framework/interface/IOVSyncValue.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>

int main(){

  cond::ServiceLoader* loader=new cond::ServiceLoader;
  ::putenv("CORAL_AUTH_USER=me");
  ::putenv("CORAL_AUTH_PASSWORD=mypass");
  loader->loadAuthenticationService( cond::Env );
  loader->loadMessageService( cond::Error );
  try{
    std::cout << "01 " << std::endl;
    cond::DBSession* session1 =
          new cond::DBSession( std::string( "sqlite_file:test.db" ) );
    std::cout << "02  " << std::endl;
    session1->setCatalog( "file:testcatalog.xml" );
    std::cout << "03 " << std::endl;
    session1->connect( cond::ReadWriteCreate );
    std::cout << "04 " << std::endl;
    cond::DBWriter pwriter( *session1, "RangeT0s" );
    std::cout << "05 " << std::endl;
    cond::DBWriter iovwriter( *session1, "IOV" );
    std::cout << "06 " << std::endl;
    session1->startUpdateTransaction();
    std::cout << "07 " << std::endl;
    cond::IOV* t0iov = new cond::IOV;
    std::cout << "08 " << std::endl;

    DTRangeT0* t0 = new DTRangeT0( "cmssw_t0" );

    int status = 0;
    std::ifstream ifile( "testT0.txt" );
    int whe;
    int sta;
    int sec;
    int qua;
    int t0min;
    int t0max;
    while ( ifile >> whe
                  >> sta
                  >> sec
                  >> qua
                  >> t0min
                  >> t0max ) {
      status = t0->setSLRangeT0( whe, sta, sec, qua,
                                 t0min, t0max );
      std::cout << whe << " "
                << sta << " "
                << sec << " "
                << qua << " "
                << t0min << " "
                << t0max << "  -> ";                
      std::cout << "insert status: " << status << std::endl;
    }

    std::string mytok=pwriter.markWrite<DTRangeT0>( t0 );
    t0iov->iov.insert( std::make_pair(
                edm::IOVSyncValue::endOfTime().eventID().run(), mytok ) );

    std::string t0iovToken = iovwriter.markWrite<cond::IOV>( t0iov );
    session1->commit();//commit all in one
    session1->disconnect();
    delete session1;
    cond::MetaData metadata_svc( "sqlite_file:test.db", *loader );
    metadata_svc.connect();
    metadata_svc.addMapping( "cmssw_T0", t0iovToken );
    metadata_svc.disconnect();
  } catch( const cond::Exception& er ) {
    std::cout << er.what() << std::endl;
    delete loader;
    exit(-1);
  } catch( ... ) {
    std::cout << "Funny error" << std::endl;
    delete loader;
    exit( -1 );
  }

  delete loader;
  return 0;

}
