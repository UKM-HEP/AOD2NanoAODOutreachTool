#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillElectron(edm::Handle<reco::GsfElectronCollection> &electrons, edm::Handle<reco::VertexCollection> &vertices){

  value_el_n = 0;
  const float el_min_pt = 5;
  //std::vector<reco::GsfElectron> selectedElectrons;
  for (auto it = electrons->begin(); it != electrons->end(); it++) {
    if (it->pt() > el_min_pt) {
      selectedElectrons.emplace_back(*it);
      value_el_pt[value_el_n] = it->pt();
      value_el_eta[value_el_n] = it->eta();
      value_el_phi[value_el_n] = it->phi();
      value_el_charge[value_el_n] = it->charge();
      value_el_mass[value_el_n] = it->mass();
      value_el_cutbasedid[value_el_n] = it->passingCutBasedPreselection();
      value_el_pfid[value_el_n] = it->passingPflowPreselection();
      // https://twiki.cern.ch/twiki/bin/view/CMSPublic/EgammaPublicData#Electron_Identification_Base_AN2
      value_el_dEtaIn[value_el_n] = it->deltaEtaSuperClusterTrackAtVtx();
      value_el_dPhiIn[value_el_n] = it->deltaPhiSuperClusterTrackAtVtx();
      value_el_sigmaIEtaIEta[value_el_n] = it->sigmaIetaIeta();
      value_el_HoE[value_el_n] = it->hadronicOverEm();
      value_el_fbrem[value_el_n] = it->fbrem();
      value_el_EoP_In[value_el_n] = it->eSuperClusterOverP();
      value_el_IoEIoP_In[value_el_n] = abs( ( 1. / it->ecalEnergy() ) - ( it->eSuperClusterOverP() / it->ecalEnergy() ) );
      
      if (it->passingPflowPreselection()) {
        auto iso03 = it->pfIsolationVariables();
        value_el_pfreliso03all[value_el_n] =
	  (iso03.chargedHadronIso + iso03.neutralHadronIso + iso03.photonIso)/it->pt();
      } else {
        value_el_pfreliso03all[value_el_n] = -999;
      }
      auto trk = it->gsfTrack();
      math::XYZPoint pv(vertices->begin()->position());

      // impact parameter
      value_el_dxy[value_el_n] = trk->dxy(pv);
      value_el_dz[value_el_n] = trk->dz(pv);
      value_el_dxyErr[value_el_n] = trk->d0Error();
      value_el_dzErr[value_el_n] = trk->dzError();
      value_el_Nmisshits[value_el_n] = trk->trackerExpectedHitsInner().numberOfHits();
      value_el_jetidx[value_el_n] = -1;
      value_el_genpartidx[value_el_n] = -1;
      value_el_n++;
    }
  }
  
}


// https://twiki.cern.ch/twiki/bin/viewauth/CMS/VbtfEleID2011#Electron_VBTF_Selection_for_2011
// https://twiki.cern.ch/twiki/bin/view/CMS/SimpleCutBasedEleID
// https://twiki.cern.ch/twiki/bin/view/CMS/EgammaWorkingPointsv3
// https://twiki.cern.ch/twiki/bin/view/CMSPublic/EgammaPublicData
