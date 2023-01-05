#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillElectron(edm::Handle<reco::GsfElectronCollection> &electrons, edm::Handle<reco::VertexCollection> &vertices, edm::Handle<reco::ConversionCollection> &conversions,
			       edm::Handle<reco::BeamSpot> &bsHandle, edm::Handle<double> &rhoHandle ){

  value_el_n = 0;
  const float el_min_pt = 5;
  //std::vector<reco::GsfElectron> selectedElectrons;
  for (auto it = electrons->begin(); it != electrons->end(); it++) {
    if (it->pt() > el_min_pt) {

      auto trk = it->gsfTrack();
      math::XYZPoint pv(vertices->begin()->position());
      const reco::BeamSpot &beamspot = *bsHandle.product();
      //float missing_hits = trk->trackerExpectedHitsInner().numberOfHits()-trk->hitPattern().numberOfHits();
      int missing_hits = it->gsfTrack()->trackerExpectedHitsInner().numberOfHits()-it->gsfTrack()->hitPattern().numberOfHits();
      bool passelectronveto = !ConversionTools::hasMatchedConversion(*it, conversions, beamspot.position());

      selectedElectrons.emplace_back(*it);
      value_el_pt[value_el_n] = it->pt();
      value_el_eta[value_el_n] = it->eta();
      value_el_phi[value_el_n] = it->phi();
      value_el_charge[value_el_n] = it->charge();
      value_el_mass[value_el_n] = it->mass();
      //value_el_cutbasedid[value_el_n] = it->passingCutBasedPreselection();
      value_el_pfid[value_el_n] = it->passingPflowPreselection();
      value_el_dEtaIn[value_el_n] = it->deltaEtaSuperClusterTrackAtVtx();
      value_el_dPhiIn[value_el_n] = it->deltaPhiSuperClusterTrackAtVtx();
      value_el_sigmaIEtaIEta[value_el_n] = it->sigmaIetaIeta();
      value_el_HoE[value_el_n] = it->hadronicOverEm();
      value_el_fbrem[value_el_n] = it->fbrem();
      value_el_EoP_In[value_el_n] = it->eSuperClusterOverP();
      value_el_IoEIoP_In[value_el_n] = abs( ( 1. / it->ecalEnergy() ) - ( it->eSuperClusterOverP() / it->ecalEnergy() ) );
      
      float el_pfIso = 999;
      if (it->passingPflowPreselection()) {
	double rho = 0;
	if(rhoHandle.isValid()) rho = *(rhoHandle.product());
	double Aeff = effectiveArea0p3cone(it->eta());
        auto iso03 = it->pfIsolationVariables();
        //value_el_pfreliso03all[value_el_n] = (iso03.chargedHadronIso + iso03.neutralHadronIso + iso03.photonIso)/it->pt();
	el_pfIso = (iso03.chargedHadronIso + std::max(0.0,iso03.neutralHadronIso + iso03.photonIso - rho*Aeff))/it->pt();
	//value_el_pfreliso03all[value_el_n] = el_pfIso;
      }
      /*
      else {
	value_el_pfreliso03all[value_el_n] = el_pfIso;
      }
      */
      value_el_pfreliso03all[value_el_n] = el_pfIso;
      
      // ID
      // https://twiki.cern.ch/twiki/bin/view/CMSPublic/EgammaPublicData#Electron_ID_Working_Points
      bool isVeto = false, isLoose = false, isMedium = false, isTight = false;
      if ( abs(it->eta()) <= 1.479 ) {

	if ( abs(it->deltaEtaSuperClusterTrackAtVtx())<.007 && abs(it->deltaPhiSuperClusterTrackAtVtx())<.8 &&
             it->sigmaIetaIeta()<.01 && it->hadronicOverEm()<.15 &&
             abs(trk->dxy(pv))<.04 && abs(trk->dz(pv))<.2 && el_pfIso<.15){

	  isVeto = true;

	  if ( abs(it->deltaEtaSuperClusterTrackAtVtx())<.007 && abs(it->deltaPhiSuperClusterTrackAtVtx())<.15 && 
	       it->sigmaIetaIeta()<.01 && it->hadronicOverEm()<.12 && 
	       abs(trk->dxy(pv))<.02 && abs(trk->dz(pv))<.2 && 
	       missing_hits<=1 && passelectronveto==true &&
	       abs(1/it->ecalEnergy()-1/(it->ecalEnergy()/it->eSuperClusterOverP()))<.05 && 
	       el_pfIso<.15){
	    
	    isLoose = true;
	    
	    if ( abs(it->deltaEtaSuperClusterTrackAtVtx())<.004 && abs(it->deltaPhiSuperClusterTrackAtVtx())<.06 && abs(trk->dz(pv))<.1 ){
	      isMedium = true;
	      
	      if (abs(it->deltaPhiSuperClusterTrackAtVtx())<.03 && missing_hits<=0 && el_pfIso<.10 ){
		isTight = true;
	      }
	    }
	  }
	}
      }
      else if ( abs(it->eta()) > 1.479 && abs(it->eta()) < 2.5 ) {

	if ( abs(it->deltaEtaSuperClusterTrackAtVtx())<.01 && abs(it->deltaPhiSuperClusterTrackAtVtx())<.7 &&
             it->sigmaIetaIeta()<.03 && abs(trk->dxy(pv))<.04 && abs(trk->dz(pv))<.2 && el_pfIso<.15 ) {
	  
	  isVeto = true;
	  
	  if ( abs(it->deltaEtaSuperClusterTrackAtVtx())<.009 && abs(it->deltaPhiSuperClusterTrackAtVtx())<.1 && 
	       it->sigmaIetaIeta()<.03 && it->hadronicOverEm()<.1 && 
	       abs(trk->dxy(pv))<.02 && abs(trk->dz(pv))<.2 && 
	       missing_hits<=1 && el_pfIso<.15 && passelectronveto==true &&
	       abs(1/it->ecalEnergy()-1/(it->ecalEnergy()/it->eSuperClusterOverP()))<.05) {
	    
	    isLoose = true;
	    
	    if ( abs(it->deltaEtaSuperClusterTrackAtVtx())<.007 && abs(it->deltaPhiSuperClusterTrackAtVtx())<.03 && abs(trk->dz(pv))<.1 ){
	      isMedium = true;
	      
	      if ( abs(it->deltaEtaSuperClusterTrackAtVtx())<.005 && abs(it->deltaPhiSuperClusterTrackAtVtx())<.02 && missing_hits<=0 && el_pfIso<.10 ){
		isTight = true;
	      }
	    }
	  }
	}
      } // ID end
      
      // 0:fail, 1:veto, 2:loose, 3:medium, 4:tight
      value_el_cutBasedId[value_el_n] = int(isVeto) + int(isLoose) + int(isMedium) + int(isTight);
      
      // impact parameter
      value_el_dxy[value_el_n] = trk->dxy(pv);
      value_el_dz[value_el_n] = trk->dz(pv);
      value_el_dxyErr[value_el_n] = trk->d0Error();
      value_el_dzErr[value_el_n] = trk->dzError();
      //value_el_Nmisshits[value_el_n] = trk->trackerExpectedHitsInner().numberOfHits();
      value_el_Nmisshits[value_el_n] = missing_hits;
      value_el_vetoConv[value_el_n] = passelectronveto;
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
