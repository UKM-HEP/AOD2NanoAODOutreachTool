#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillTau(const edm::Event &iEvent){

  // Taus
  // References for Tau collections and IDs:
  // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuidePFTauID#53X
  // https://twiki.cern.ch/twiki/bin/view/CMSPublic/NutShellRecipeFor5312AndNewer
  
  //Handle<PFTauCollection> taus;
  //iEvent.getByLabel(InputTag("hpsPFTauProducer"), taus);

  Handle<PFTauDiscriminator> tausLooseIso, tausVLooseIso, tausMediumIso, tausTightIso,
    tausDecayMode, tausLooseEleRej, tausMediumEleRej,
    tausTightEleRej, tausLooseMuonRej, tausMediumMuonRej,
    tausTightMuonRej, tausRawIso;

  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByDecayModeFinding"),
		    tausDecayMode);

  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByRawCombinedIsolationDBSumPtCorr"),
		    tausRawIso);
  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByVLooseCombinedIsolationDBSumPtCorr"),
		    tausVLooseIso);
  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByLooseCombinedIsolationDBSumPtCorr"),
		    tausLooseIso);
  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByMediumCombinedIsolationDBSumPtCorr"),
		    tausMediumIso);
  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByTightCombinedIsolationDBSumPtCorr"),
		    tausTightIso);

  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByLooseElectronRejection"),
		    tausLooseEleRej);
  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByMediumElectronRejection"),
		    tausMediumEleRej);
  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByTightElectronRejection"),
		    tausTightEleRej);

  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByLooseMuonRejection"),
		    tausLooseMuonRej);
  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByMediumMuonRejection"),
		    tausMediumMuonRej);
  iEvent.getByLabel(InputTag("hpsPFTauDiscriminationByTightMuonRejection"),
		    tausTightMuonRej);

  const float tau_min_pt = 15;
  value_tau_n = 0;
  std::vector<PFTau> selectedTaus;
  for (auto it = taus->begin(); it != taus->end(); it++) {
    if (it->pt() > tau_min_pt) {
      selectedTaus.emplace_back(*it);
      value_tau_pt[value_tau_n] = it->pt();
      value_tau_eta[value_tau_n] = it->eta();
      value_tau_phi[value_tau_n] = it->phi();
      value_tau_charge[value_tau_n] = it->charge();
      value_tau_mass[value_tau_n] = it->mass();
      value_tau_decaymode[value_tau_n] = it->decayMode();
      // Discriminators
      const auto idx = it - taus->begin();
      value_tau_iddecaymode[value_tau_n] = tausDecayMode->operator[](idx).second;
      value_tau_idisoraw[value_tau_n] = tausRawIso->operator[](idx).second;
      value_tau_idisovloose[value_tau_n] = tausVLooseIso->operator[](idx).second;
      value_tau_idisoloose[value_tau_n] = tausLooseIso->operator[](idx).second;
      value_tau_idisomedium[value_tau_n] = tausMediumIso->operator[](idx).second;
      value_tau_idisotight[value_tau_n] = tausTightIso->operator[](idx).second;
      value_tau_idantieleloose[value_tau_n] = tausLooseEleRej->operator[](idx).second;
      value_tau_idantielemedium[value_tau_n] = tausMediumEleRej->operator[](idx).second;
      value_tau_idantieletight[value_tau_n] = tausTightEleRej->operator[](idx).second;
      value_tau_idantimuloose[value_tau_n] = tausLooseMuonRej->operator[](idx).second;
      value_tau_idantimumedium[value_tau_n] = tausMediumMuonRej->operator[](idx).second;
      value_tau_idantimutight[value_tau_n] = tausTightMuonRej->operator[](idx).second;

      value_tau_reliso_all[value_tau_n] = (it->isolationPFChargedHadrCandsPtSum() + it->isolationPFGammaCandsEtSum()) / it->pt();
      value_tau_jetidx[value_tau_n] = -1;
      value_tau_genpartidx[value_tau_n] = -1;
      value_tau_n++;
    }
  } 
}
