#include "CondCore/DBCommon/interface/DBWriter.h"
#include "CondFormats/DTObjects/interface/DTT0.h"
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
  cond::IOV* t0iov=new cond::IOV;
  std::string t0iovToken=w.write<cond::IOV>(t0iov,"IOV");
  DTT0* t0 = new DTT0("cmssw_t0");
    int
    status = t0->setCellT0( 2,3,4,1,3,42,523,1.2 );
    std::cout << "insert status: " << status << std::endl;
    status = t0->setCellT0( 2,3,4,1,3,43,524,1.3 );
    std::cout << "insert status: " << status << std::endl;
    status = t0->setCellT0( 2,3,4,1,3,44,525,1.4 );
    std::cout << "insert status: " << status << std::endl;
  std::string t0tok=w.write<DTT0>(t0,"DTT0");
  std::cout<<"endoftime "<<edm::IOVSyncValue::endOfTime().eventID().run()<<std::endl;
  std::cout << t0tok << std::endl;
  t0iov->iov.insert(std::make_pair(10, t0tok));
//  t0iov->iov.insert(std::make_pair(edm::IOVSyncValue::endOfTime().eventID().run(), t0tok));
  
  w.commitTransaction();
  //register the iovToken to the metadata service
  cond::MetaData metadata_svc(contact);
  // metadata_svc.addMapping("DTMapping_v1", mapiovToken);  
  metadata_svc.addMapping("t0_test", t0iovToken);  
}
