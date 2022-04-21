#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillJet(edm::Handle<reco::CaloJetCollection> &jets, edm::Handle<reco::JetTagCollection> &btags){

  // Jets
  // Jet ID recommendations:
  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/JetID#Recommendations_for_8_TeV_data_a
  // B-tag recommendations:
  // https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation53XReReco

  const float jet_min_pt = 15;
  value_jet_n = 0;
  //std::vector<CaloJet> selectedJets;
  for (auto it = jets->begin(); it != jets->end(); it++) {
    if (it->pt() > jet_min_pt) {
      selectedJets.emplace_back(*it);
      value_jet_pt[value_jet_n] = it->pt();
      value_jet_eta[value_jet_n] = it->eta();
      value_jet_phi[value_jet_n] = it->phi();
      value_jet_mass[value_jet_n] = it->mass();
      value_jet_puid[value_jet_n] = it->emEnergyFraction() > 0.01 && it->n90() > 1;
      value_jet_btag[value_jet_n] = btags->operator[](it - jets->begin()).second;
      value_jet_n++;
    }
  }

}
