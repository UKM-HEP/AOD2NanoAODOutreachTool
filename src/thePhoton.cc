#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillTau(const edm::Event &iEvent){

  // Photons
  //Handle<PhotonCollection> photons;
  //iEvent.getByLabel(InputTag("photons"), photons);

  value_ph_n = 0;
  const float ph_min_pt = 5;
  std::vector<Photon> selectedPhotons;
  for (auto it = photons->begin(); it != photons->end(); it++) {
    if (it->pt() > ph_min_pt) {
      selectedPhotons.emplace_back(*it);
      value_ph_pt[value_ph_n] = it->pt();
      value_ph_eta[value_ph_n] = it->eta();
      value_ph_phi[value_ph_n] = it->phi();
      value_ph_charge[value_ph_n] = it->charge();
      value_ph_mass[value_ph_n] = it->mass();
      value_ph_pfreliso03all[value_ph_n] = it->ecalRecHitSumEtConeDR03() / it->pt();
      value_ph_jetidx[value_ph_n] = -1;
      value_ph_genpartidx[value_ph_n] = -1;
      value_ph_n++;
    }
  }
  
}
