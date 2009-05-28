
/*----------------------------------------------------------------------

Toy EDAnalyzer for testing purposes only.

----------------------------------------------------------------------*/

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CondFormats/DTObjects/interface/DTConfigList.h"
#include "CondFormats/DTObjects/interface/DTConfig1Handler.h"
#include "CondFormats/DTObjects/interface/DTDB1Session.h"

#include <string>

namespace edmtest {
  class DTConfig1Dump : public edm::EDAnalyzer
  {
  public:
    explicit  DTConfig1Dump(edm::ParameterSet const& p);
    explicit  DTConfig1Dump(int i) ;
    virtual ~ DTConfig1Dump();
    virtual void analyze(const edm::Event& e, const edm::EventSetup& c);
  private:
    std::string connect;
    std::string auth_path;
    std::string catalog;
    std::string token;
    bool local;
    DTDB1Session* session;
    const DTConfigList* rs;
    DTConfig1Handler* ri;
  };
}
