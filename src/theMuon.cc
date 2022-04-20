#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillMuon(const edm::Event &iEvent, ){
  // Muons
  //Handle<MuonCollection> muons;
  //iEvent.getByLabel(InputTag("muons"), muons);

  value_mu_n = 0;
  const float mu_min_pt = 3;
  std::vector<Muon> selectedMuons;
  for (auto it = muons->begin(); it != muons->end(); it++) {
    if (it->pt() > mu_min_pt) {
      selectedMuons.emplace_back(*it);
      value_mu_pt[value_mu_n] = it->pt();
      value_mu_eta[value_mu_n] = it->eta();
      value_mu_phi[value_mu_n] = it->phi();
      value_mu_charge[value_mu_n] = it->charge();
      value_mu_mass[value_mu_n] = it->mass();
      if (it->isPFMuon() && it->isPFIsolationValid()) {
        auto iso03 = it->pfIsolationR03();
        value_mu_pfreliso03all[value_mu_n] =
	  (iso03.sumChargedHadronPt + iso03.sumNeutralHadronEt + iso03.sumPhotonEt)/it->pt();
        auto iso04 = it->pfIsolationR04();
        value_mu_pfreliso04all[value_mu_n] =
	  (iso04.sumChargedHadronPt + iso04.sumNeutralHadronEt + iso04.sumPhotonEt)/it->pt();
      } else {
        value_mu_pfreliso03all[value_mu_n] = -999;
        value_mu_pfreliso04all[value_mu_n] = -999;
      }
      value_mu_tightid[value_mu_n] = muon::isTightMuon(*it, *vertices->begin());
      value_mu_softid[value_mu_n] = muon::isSoftMuon(*it, *vertices->begin());
      auto trk = it->globalTrack();
      if (trk.isNonnull()) {
        value_mu_dxy[value_mu_n] = trk->dxy(pv);
        value_mu_dz[value_mu_n] = trk->dz(pv);
        value_mu_dxyErr[value_mu_n] = trk->d0Error();
        value_mu_dzErr[value_mu_n] = trk->dzError();
      } else {
        value_mu_dxy[value_mu_n] = -999;
        value_mu_dxyErr[value_mu_n] = -999;
        value_mu_dz[value_mu_n] = -999;
        value_mu_dzErr[value_mu_n] = -999;
      }
      value_mu_genpartidx[value_mu_n] = -1;
      value_mu_jetidx[value_mu_n] = -1;
      value_mu_n++;
    }
  }
  
}
