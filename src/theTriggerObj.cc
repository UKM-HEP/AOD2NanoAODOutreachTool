#include "AOD2NanoAOD.h"

void AOD2NanoAOD::fillTriggerObj(edm::Handle<trigger::TriggerEvent> &trigEvent){

  using namespace trigger;
  
  value_trigobj_ele_n = 0;
  value_trigobj_isou_n = 0;
  value_trigobj_jpsiu_n = 0;

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

    // Muon HLT_IsoMu30_eta2p1_v13
    size_type isou_filterIndex = trigEvent->filterIndex( edm::InputTag( "hltL3crIsoL1sMu16Eta2p1L1f0L2f16QL3f30QL3crIsoRhoFiltered0p15" , "" , trigEventTag.process() ) );
    if( isou_filterIndex < nF ){
      const Keys& trigKeys = trigEvent->filterKeys(isou_filterIndex);

      //now loop of the trigger objects passing filter
      for( trigger::Keys::const_iterator keyIt=trigKeys.begin() ; keyIt!=trigKeys.end() ; ++keyIt ){
        const TriggerObject trigobj = TOC[*keyIt];
	
        value_trigobj_isou_id[value_trigobj_isou_n] = trigobj.id();
        value_trigobj_isou_pt[value_trigobj_isou_n] = trigobj.pt();
        value_trigobj_isou_eta[value_trigobj_isou_n] = trigobj.eta();
        value_trigobj_isou_phi[value_trigobj_isou_n] = trigobj.phi();
        value_trigobj_isou_mass[value_trigobj_isou_n] = trigobj.mass();
	
        value_trigobj_isou_n++;
      }
    } // isou_filterIndex

    // HLT_Dimuon0_Jpsi_Muon_v7
    size_type jpsiu_filterIndex = trigEvent->filterIndex( edm::InputTag( "hltVertexmumuFilterJpsiMuon" , "" , trigEventTag.process() ) );
    //std::cout<<"jpsiu_filterIndex : "<<jpsiu_filterIndex<<std::endl;
    //std::cout<<"nF : "<<nF<<std::endl;
    if( jpsiu_filterIndex < nF ){
      const Keys& trigKeys = trigEvent->filterKeys(jpsiu_filterIndex);

      //now loop of the trigger objects passing filter
      for( trigger::Keys::const_iterator keyIt=trigKeys.begin() ; keyIt!=trigKeys.end() ; ++keyIt ){
        const TriggerObject trigobj = TOC[*keyIt];

        value_trigobj_jpsiu_id[value_trigobj_jpsiu_n] = trigobj.id();
        value_trigobj_jpsiu_pt[value_trigobj_jpsiu_n] = trigobj.pt();
        value_trigobj_jpsiu_eta[value_trigobj_jpsiu_n] = trigobj.eta();
        value_trigobj_jpsiu_phi[value_trigobj_jpsiu_n] = trigobj.phi();
        value_trigobj_jpsiu_mass[value_trigobj_jpsiu_n] = trigobj.mass();

        value_trigobj_jpsiu_n++;
      }
    } // isou_filterIndex
    
  }
  else {
    std::cout<< "Handle invalid! Check InputTag provided." << std::endl;
  }
  
}
