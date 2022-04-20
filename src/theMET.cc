#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillMET(const edm::Event &iEvent){

  // MET
  //Handle<PFMETCollection> met;
  //iEvent.getByLabel(InputTag("pfMet"), met);
  
  value_met_pt = met->begin()->pt();
  value_met_phi = met->begin()->phi();
  value_met_sumet = met->begin()->sumEt();
  value_met_significance = met->begin()->significance();
  auto cov = met->begin()->getSignificanceMatrix();
  value_met_covxx = cov[0][0];
  value_met_covxy = cov[0][1];
  value_met_covyy = cov[1][1];

}
