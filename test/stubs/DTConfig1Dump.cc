
/*----------------------------------------------------------------------

Toy EDAnalyzer for testing purposes only.

----------------------------------------------------------------------*/

#include <stdexcept>
#include <iostream>
#include <map>
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/MakerMacros.h"


#include "CondFormats/DTObjects/test/stubs/DTConfig1Dump.h"
#include "CondFormats/DTObjects/interface/DTCCBConfig.h"
#include "CondFormats/DataRecord/interface/DTCCBConfigRcd.h"

namespace edmtest {

  DTConfig1Dump::DTConfig1Dump(edm::ParameterSet const& p) {
// parameters to setup 
    connect   = p.getParameter< std::string >("connect");
    auth_path = p.getParameter< std::string >("authenticationPath");
    token     = p.getParameter< std::string >("token");
    local     = p.getParameter< bool        >("siteLocalConfig");
    if ( local ) catalog = "";
    else         catalog = p.getParameter< std::string >("catalog");

// create DB session
    session = new DTDB1Session( connect, catalog, auth_path, local );
//    session = new DTDB1Session( connect, catalog, cond::XML, local );
    session->connect( false );

// create an interface to handle configurations list
    DTConfig1Handler::maxBrickNumber  = 100;
    DTConfig1Handler::maxStringNumber = 10000;
    DTConfig1Handler::maxByteNumber   = 1000000;
    rs = 0;
    ri = DTConfig1Handler::create( session, token );
//    ri = new DTConfig1Handler( session, token );
    rs = ri->getContainer();
  }

  DTConfig1Dump::DTConfig1Dump(int i) {
  }

  DTConfig1Dump::~DTConfig1Dump() {
    DTConfig1Handler::remove( session );
    session->disconnect();
    delete session;
  }

  void DTConfig1Dump::analyze( const edm::Event& e,
                              const edm::EventSetup& context ) {
    using namespace edm::eventsetup;
    // Context is not used.
    std::cout <<" I AM IN RUN NUMBER "<<e.id().run() <<std::endl;
    std::cout <<" ---EVENT NUMBER "<<e.id().event() <<std::endl;

// get configuration for current run
    edm::ESHandle<DTCCBConfig> conf;
    context.get<DTCCBConfigRcd>().get(conf);
    std::cout << conf->version() << std::endl;
    std::cout << std::distance( conf->begin(), conf->end() )
              << " data in the container" << std::endl;

// loop over chambers
    DTCCBConfig::ccb_config_map configKeys( conf->configKeyMap() );
    DTCCBConfig::ccb_config_iterator iter = configKeys.begin();
    DTCCBConfig::ccb_config_iterator iend = configKeys.end();
//    DTCCBConfig::const_iterator iter = conf->begin();
//    DTCCBConfig::const_iterator iend = conf->end();
    while ( iter != iend ) {
// get chamber id
      const DTCCBId& ccbId = iter->first;
      std::cout << ccbId.wheelId   << " "
                << ccbId.stationId << " "
                << ccbId.sectorId  << " -> ";
      std::cout << std::endl;
// get brick identifiers list
      const std::vector<int>& ccbConf = iter->second;
      std::vector<int>::const_iterator cfgIter = ccbConf.begin();
      std::vector<int>::const_iterator cfgIend = ccbConf.end();

// loop over configuration bricks
      while ( cfgIter != cfgIend ) {
// get brick identifier
        int id = *cfgIter++;
        std::cout << " " << id;
        std::cout << std::endl;
// create strings list
        std::vector<const std::string*> list;
        ri->getData( id, list );
// loop over strings
        std::vector<const std::string*>::const_iterator s_iter = list.begin();
        std::vector<const std::string*>::const_iterator s_iend = list.end();
        while ( s_iter != s_iend ) std::cout << "        ----> "
                                             << **s_iter++ << std::endl;
      }
      std::cout << std::endl;
      ++iter;
    }
/*
*/
  }
  DEFINE_FWK_MODULE(DTConfig1Dump);
}
