#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillGenpart(edm::Handle<reco::GenParticleCollection> &gens){
  
  value_gen_n = 0;
  for (auto it = gens->begin(); it != gens->end(); it++) {
    const auto status = it->status();
    const auto pdgId = std::abs(it->pdgId());
    if (status == 1 && pdgId == 13) { // muon
      interestingGenParticles.emplace_back(*it);
    }
    if (status == 1 && pdgId == 11) { // electron
      interestingGenParticles.emplace_back(*it);
    }
    /*
      if (status == 1 && pdgId == 22) { // photon
      interestingGenParticles.emplace_back(*it);
      }
    */
    if (status == 2 && pdgId == 15) { // tau
      interestingGenParticles.emplace_back(*it);
    }
  }
  
  // Match muons with gen particles and jets
  for (auto p = selectedMuons.begin(); p != selectedMuons.end(); p++) {
    // Gen particle matching
    auto p4 = p->p4();
    auto idx = findBestVisibleMatch(interestingGenParticles, p4);
    if (idx != -1) {
      auto g = interestingGenParticles.begin() + idx;
      value_gen_pt[value_gen_n] = g->pt();
      value_gen_eta[value_gen_n] = g->eta();
      value_gen_phi[value_gen_n] = g->phi();
      value_gen_mass[value_gen_n] = g->mass();
      value_gen_pdgid[value_gen_n] = g->pdgId();
      value_gen_status[value_gen_n] = g->status();
      value_mu_genpartidx[p - selectedMuons.begin()] = value_gen_n;
      value_gen_n++;
    }
    
    // Jet matching
    value_mu_jetidx[p - selectedMuons.begin()] = findBestMatch(selectedJets, p4);
  }
  
  // Match electrons with gen particles and jets
  for (auto p = selectedElectrons.begin(); p != selectedElectrons.end(); p++) {
    // Gen particle matching
    auto p4 = p->p4();
    auto idx = findBestVisibleMatch(interestingGenParticles, p4);
    if (idx != -1) {
      auto g = interestingGenParticles.begin() + idx;
      value_gen_pt[value_gen_n] = g->pt();
      value_gen_eta[value_gen_n] = g->eta();
      value_gen_phi[value_gen_n] = g->phi();
      value_gen_mass[value_gen_n] = g->mass();
      value_gen_pdgid[value_gen_n] = g->pdgId();
      value_gen_status[value_gen_n] = g->status();
      value_el_genpartidx[p - selectedElectrons.begin()] = value_gen_n;
      value_gen_n++;
    }
    
    // Jet matching
    value_el_jetidx[p - selectedElectrons.begin()] = findBestMatch(selectedJets, p4);
  }
  
  /*
  // Match photons with gen particles and jets
  for (auto p = selectedPhotons.begin(); p != selectedPhotons.end(); p++) {
  // Gen particle matching
  auto p4 = p->p4();
  auto idx = findBestVisibleMatch(interestingGenParticles, p4);
  if (idx != -1) {
  auto g = interestingGenParticles.begin() + idx;
  value_gen_pt[value_gen_n] = g->pt();
  value_gen_eta[value_gen_n] = g->eta();
  value_gen_phi[value_gen_n] = g->phi();
  value_gen_mass[value_gen_n] = g->mass();
  value_gen_pdgid[value_gen_n] = g->pdgId();
  value_gen_status[value_gen_n] = g->status();
  value_ph_genpartidx[p - selectedPhotons.begin()] = value_gen_n;
  value_gen_n++;
  }
  
  // Jet matching
  value_ph_jetidx[p - selectedPhotons.begin()] = findBestMatch(selectedJets, p4);
  }
  */
  
  // Match taus with gen particles and jets
  for (auto p = selectedTaus.begin(); p != selectedTaus.end(); p++) {
    // Gen particle matching
    auto p4 = p->p4();
    auto idx = findBestVisibleMatch(interestingGenParticles, p4); // TODO: Subtract the invisible parts only once.
    if (idx != -1) {
      auto g = interestingGenParticles.begin() + idx;
      value_gen_pt[value_gen_n] = g->pt();
      value_gen_eta[value_gen_n] = g->eta();
      value_gen_phi[value_gen_n] = g->phi();
      value_gen_mass[value_gen_n] = g->mass();
      value_gen_pdgid[value_gen_n] = g->pdgId();
      value_gen_status[value_gen_n] = g->status();
      value_tau_genpartidx[p - selectedTaus.begin()] = value_gen_n;
      value_gen_n++;
    }
    
    // Jet matching
    value_tau_jetidx[p - selectedTaus.begin()] = findBestMatch(selectedJets, p4);
  }
  
}
