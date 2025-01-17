#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillTrigger(edm::Handle<edm::TriggerResults> &trigger){
  
  // Trigger results
  //edm::Handle<edm::TriggerResults> trigger;
  //iEvent.getByLabel(InputTag("TriggerResults", "", "HLT"), trigger);

  auto psetRegistry = edm::pset::Registry::instance();
  auto triggerParams = psetRegistry->getMapped(trigger->parameterSetID());
  edm::TriggerNames triggerNames(*triggerParams);
  edm::TriggerResultsByName triggerByName(&(*trigger), &triggerNames);
  for (size_t i = 0; i < interestingTriggers.size(); i++) {
    value_trig[i] = false;
  }
  const auto names = triggerByName.triggerNames();
  for (size_t i = 0; i < names.size(); i++) {
    const auto name = names[i];

    for (size_t j = 0; j < interestingTriggers.size(); j++) {
      const auto interest = interestingTriggers[j];

      if (name.find(interest) == 0) {
	const auto substr = name.substr(interest.length(), 2);
        if ( substr.compare("_v") == 0 ) {
          const auto status = triggerByName.state(name);
          if (status == 1) {
	    //std::cout<<"Firing trigger : "<< name <<std::endl;
            value_trig[j] = true;
            break;
          }
        }
      }
    }
  }
  //std::cout<<std::endl;
}
