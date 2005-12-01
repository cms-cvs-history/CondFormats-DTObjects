#include "CondCore/DBCommon/interface/DBWriter.h"
#include "CondFormats/DTObjects/interface/DTTtrig.h"
#include "CondCore/IOVService/interface/IOV.h"
#include "CondCore/MetaDataService/interface/MetaData.h"
#include "FWCore/Framework/interface/IOVSyncValue.h"
#include "SealKernel/Service.h"
#include "POOLCore/POOLContext.h"
#include "SealKernel/Context.h"
#include <string>
#include <map>
#include <iostream>
int main(){
//  std::string contact("oracle://devdb");
   std::string contact("oracle://cms_val_lb.cern.ch/CMS_VAL_DT_POOL_OWNER");
 //std::string contact("oracle://cms_val_lb");
//  std::string contact("sqlite_file:ecalcalib.db");
  pool::POOLContext::loadComponent( "SEAL/Services/MessageService" );
  pool::POOLContext::setMessageVerbosityLevel( seal::Msg::Error );
//  const std::string userNameEnv = "POOL_AUTH_USER=cms_dt_writer";
  const std::string userNameEnv = "POOL_AUTH_USER=CMS_VAL_DT_POOL_OWNER";
  ::putenv( const_cast<char*>( userNameEnv.c_str() ) );
//  const std::string passwdEnv = "POOL_AUTH_PASSWORD=daqcms";
  const std::string passwdEnv = "POOL_AUTH_PASSWORD=val_dt_own_1031";
  ::putenv( const_cast<char*>( passwdEnv.c_str() ) );

  
  cond::DBWriter w(contact);
  w.startTransaction();
  cond::IOV* tTrigiov=new cond::IOV;
  std::string tTrigiovToken=w.write<cond::IOV>(tTrigiov,"IOV");
  DTTtrig* tTrig = new DTTtrig("cmssw_tTrig");
    int
    status = tTrig->setSLTtrig( 2,3,4,1,2523 );
    std::cout << "insert status: " << status << std::endl;
    status = tTrig->setSLTtrig( 2,3,4,2,2524 );
    std::cout << "insert status: " << status << std::endl;
    status = tTrig->setSLTtrig( 2,3,4,3,2525 );
    std::cout << "insert status: " << status << std::endl;
  std::string tTrigtok=w.write<DTTtrig>(tTrig,"DTTtrig");
  std::cout<<"endoftime "<<edm::IOVSyncValue::endOfTime().eventID().run()<<std::endl;
  std::cout << tTrigtok << std::endl;
  tTrigiov->iov.insert(std::make_pair(10, tTrigtok));
//  tTrigiov->iov.insert(std::make_pair(edm::IOVSyncValue::endOfTime().eventID().run(), tTrigtok));
  
  w.commitTransaction();
  //register the iovToken to the metadata service
  cond::MetaData metadata_svc(contact);
  // metadata_svc.addMapping("DTMapping_v1", mapiovToken);  
  metadata_svc.addMapping("tTrig_test", tTrigiovToken);  
}
