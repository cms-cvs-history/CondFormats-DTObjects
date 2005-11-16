#include "CondCore/DBCommon/interface/DBWriter.h"
#include "CondFormats/DTObjects/interface/DTReadOutMapping.h"
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
  cond::IOV* mapiov=new cond::IOV;
  std::string mapiovToken=w.write<cond::IOV>(mapiov,"IOV");
  DTReadOutMapping* ro_map = new DTReadOutMapping("cmssw_map","cmssw_cell");
    int
    status = ro_map->insertReadOutGeometryLink( 1,2,3,0,29,2,3,4,1,3,42 );
    std::cout << "insert status: " << status << std::endl;
    status = ro_map->insertReadOutGeometryLink( 1,2,3,0,28,2,3,4,1,3,41 );
    std::cout << "insert status: " << status << std::endl;
    status = ro_map->insertReadOutGeometryLink( 1,2,3,0,27,2,3,4,1,3,40 );
    std::cout << "insert status: " << status << std::endl;
    status = ro_map->insertReadOutGeometryLink( 1,2,3,0,26,2,3,4,1,3,39 );
    std::cout << "insert status: " << status << std::endl;
  std::string mappingtok=w.write<DTReadOutMapping>(ro_map,"DTReadOutMapping");
  std::cout<<"endoftime "<<edm::IOVSyncValue::endOfTime().eventID().run()<<std::endl;
  std::cout << mappingtok << std::endl;
  mapiov->iov.insert(std::make_pair(10, mappingtok));
//  mapiov->iov.insert(std::make_pair(edm::IOVSyncValue::endOfTime().eventID().run(), mappingtok));
  
  w.commitTransaction();
  //register the iovToken to the metadata service
  cond::MetaData metadata_svc(contact);
  // metadata_svc.addMapping("DTMapping_v1", mapiovToken);  
  metadata_svc.addMapping("dtfall_test", mapiovToken);  
}
