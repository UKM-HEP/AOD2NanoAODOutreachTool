#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillTriggerObj(edm::Handle<trigger::TriggerEvent> &trigEvent){

  using namespace trigger;
  
  value_trigobj_ele_n = 0;
  value_trigobj_isou_runa_n = 0;
  value_trigobj_isou_runb_n = 0;
  value_trigobj_jpsiu_runa_n = 0;
  value_trigobj_jpsiu_runb_n = 0;

  if (trigEvent.isValid()) {
    edm::InputTag trigEventTag("hltTriggerSummaryAOD","","HLT");

    // https://cms-opendata-workshop.github.io/workshop2022-lesson-trigger/aio/index.html
    // https://cms-opendata-workshop.github.io/workshop2021-lesson-basicobjects/05-trigger/index.html

    const size_type nF(trigEvent->sizeFilters());
    const TriggerObjectCollection& TOC(trigEvent->getObjects());
    
    // HLT_Ele27_WP80_v10
    size_type e_filterIndex = trigEvent->filterIndex( edm::InputTag( "hltEle27WP80TrackIsoFilter" , "" , trigEventTag.process() ) );
    if( e_filterIndex < nF ){
      const Keys& trigKeys = trigEvent->filterKeys(e_filterIndex);
      
      //now loop of the trigger objects passing filter
      for( trigger::Keys::const_iterator keyIt=trigKeys.begin() ; keyIt!=trigKeys.end() ; ++keyIt ){
	const TriggerObject trigobj = TOC[*keyIt];

	value_trigobj_ele_id[value_trigobj_ele_n] = trigobj.id();
	value_trigobj_ele_pt[value_trigobj_ele_n] = trigobj.pt();
	value_trigobj_ele_eta[value_trigobj_ele_n] = trigobj.eta();
	value_trigobj_ele_phi[value_trigobj_ele_n] = trigobj.phi();
	value_trigobj_ele_mass[value_trigobj_ele_n] = trigobj.mass();
	
	value_trigobj_ele_n++;
      }
    } // e_filterIndex

    // Run2012B_SingleMu : HLT_IsoMu30_eta2p1_v13 : hltL3crIsoL1sMu16Eta2p1L1f0L2f16QL3f30QL3crIsoRhoFiltered0p15
    // Run2012A_SingleMu : HLT_IsoMu30_eta2p1_v11 : hltL3crIsoL1sMu16Eta2p1L1f0L2f16QL3f30QL3crIsoFiltered10
    size_type isou_filterIndex_RunA = trigEvent->filterIndex( edm::InputTag( "hltL3crIsoL1sMu16Eta2p1L1f0L2f16QL3f30QL3crIsoFiltered10" , "" , trigEventTag.process() ) );
    size_type isou_filterIndex_RunB = trigEvent->filterIndex( edm::InputTag( "hltL3crIsoL1sMu16Eta2p1L1f0L2f16QL3f30QL3crIsoRhoFiltered0p15" , "" , trigEventTag.process() ) );
    if( isou_filterIndex_RunA < nF ){
      const Keys& trigKeys = trigEvent->filterKeys(isou_filterIndex_RunA);

      //now loop of the trigger objects passing filter
      for( trigger::Keys::const_iterator keyIt=trigKeys.begin() ; keyIt!=trigKeys.end() ; ++keyIt ){
        const TriggerObject trigobj = TOC[*keyIt];
	
        value_trigobj_isou_runa_id[value_trigobj_isou_runa_n] = trigobj.id();
        value_trigobj_isou_runa_pt[value_trigobj_isou_runa_n] = trigobj.pt();
        value_trigobj_isou_runa_eta[value_trigobj_isou_runa_n] = trigobj.eta();
        value_trigobj_isou_runa_phi[value_trigobj_isou_runa_n] = trigobj.phi();
        value_trigobj_isou_runa_mass[value_trigobj_isou_runa_n] = trigobj.mass();
	
        value_trigobj_isou_runa_n++;
      }
    } // isou_filterIndex_RunA

    if( isou_filterIndex_RunB < nF ){
      const Keys& trigKeys = trigEvent->filterKeys(isou_filterIndex_RunB);

      //now loop of the trigger objects passing filter                                                                                                                                                                                                                                                                       
      for( trigger::Keys::const_iterator keyIt=trigKeys.begin() ; keyIt!=trigKeys.end() ; ++keyIt ){
        const TriggerObject trigobj = TOC[*keyIt];

        value_trigobj_isou_runb_id[value_trigobj_isou_runb_n] = trigobj.id();
        value_trigobj_isou_runb_pt[value_trigobj_isou_runb_n] = trigobj.pt();
        value_trigobj_isou_runb_eta[value_trigobj_isou_runb_n] = trigobj.eta();
        value_trigobj_isou_runb_phi[value_trigobj_isou_runb_n] = trigobj.phi();
        value_trigobj_isou_runb_mass[value_trigobj_isou_runb_n] = trigobj.mass();

        value_trigobj_isou_runb_n++;
      }
    } // isou_filterIndex_RunB
    

    // Run2011A_Muonia : HLT_DoubleMu3_Jpsi_v2    : hltDoubleMu3JpsiL3Filtered
    // HLT_DoubleMu3_LowMass_v1 : hltDiMuonL3PreFiltered3LowMass 	
    // Run2011B_Muonia : HLT_Dimuon0_Jpsi_Muon_v7 : hltVertexmumuFilterJpsiMuon
    // HLT_DoubleMu3_v10 : hltDiMuonL3PreFiltered3
    size_type jpsiu_filterIndex_RunA = trigEvent->filterIndex( edm::InputTag( "hltDiMuonL3PreFiltered3LowMass" , "" , trigEventTag.process() ) );
    size_type jpsiu_filterIndex_RunB = trigEvent->filterIndex( edm::InputTag( "hltVertexmumuFilterJpsiMuon" , "" , trigEventTag.process() ) );
    if( jpsiu_filterIndex_RunA < nF ){
      const Keys& trigKeys = trigEvent->filterKeys(jpsiu_filterIndex_RunA);

      //now loop of the trigger objects passing filter
      for( trigger::Keys::const_iterator keyIt=trigKeys.begin() ; keyIt!=trigKeys.end() ; ++keyIt ){
        const TriggerObject trigobj = TOC[*keyIt];

        value_trigobj_jpsiu_runa_id[value_trigobj_jpsiu_runa_n] = trigobj.id();
        value_trigobj_jpsiu_runa_pt[value_trigobj_jpsiu_runa_n] = trigobj.pt();
        value_trigobj_jpsiu_runa_eta[value_trigobj_jpsiu_runa_n] = trigobj.eta();
        value_trigobj_jpsiu_runa_phi[value_trigobj_jpsiu_runa_n] = trigobj.phi();
        value_trigobj_jpsiu_runa_mass[value_trigobj_jpsiu_runa_n] = trigobj.mass();

        value_trigobj_jpsiu_runa_n++;
      }
    } // isou_filterIndex_RunA

    if( jpsiu_filterIndex_RunB < nF ){
      const Keys& trigKeys = trigEvent->filterKeys(jpsiu_filterIndex_RunB);

      //now loop of the trigger objects passing filter
      for( trigger::Keys::const_iterator keyIt=trigKeys.begin() ; keyIt!=trigKeys.end() ; ++keyIt ){
        const TriggerObject trigobj = TOC[*keyIt];

        value_trigobj_jpsiu_runb_id[value_trigobj_jpsiu_runb_n] = trigobj.id();
        value_trigobj_jpsiu_runb_pt[value_trigobj_jpsiu_runb_n] = trigobj.pt();
        value_trigobj_jpsiu_runb_eta[value_trigobj_jpsiu_runb_n] = trigobj.eta();
        value_trigobj_jpsiu_runb_phi[value_trigobj_jpsiu_runb_n] = trigobj.phi();
        value_trigobj_jpsiu_runb_mass[value_trigobj_jpsiu_runb_n] = trigobj.mass();
	
        value_trigobj_jpsiu_runb_n++;
      }
    } // isou_filterIndex_RunB      
    
  }
  else {
    std::cout<< "Handle invalid! Check InputTag provided." << std::endl;
  }
  
}
