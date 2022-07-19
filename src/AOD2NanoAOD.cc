#include "AOD2NanoAOD.h"

AOD2NanoAOD::AOD2NanoAOD(const edm::ParameterSet& iConfig):
  isData(iConfig.getParameter<bool>("isData"))
{
  
  tree = fs->make<TTree>("Events", "Events");

  // Event information
  tree->Branch("run", &value_run);
  tree->Branch("luminosityBlock", &value_lumi_block);
  tree->Branch("event", &value_event);
  
  // Trigger
  for(size_t i = 0; i < interestingTriggers.size(); i++) {
    tree->Branch(interestingTriggers[i].c_str(), value_trig + i, (interestingTriggers[i] + "/O").c_str());
  }

  // Xsec
  tree->Branch("Xsec", &value_Xsec);
  
  // Vertices
  tree->Branch("PV_npvs", &value_ve_n, "PV_npvs/I");
  tree->Branch("PV_x", &value_ve_x, "PV_x/F");
  tree->Branch("PV_y", &value_ve_y, "PV_y/F");
  tree->Branch("PV_z", &value_ve_z, "PV_z/F");

  // Muons
  tree->Branch("nMuon", &value_mu_n, "nMuon/i");
  tree->Branch("Muon_pt", value_mu_pt, "Muon_pt[nMuon]/F");
  tree->Branch("Muon_eta", value_mu_eta, "Muon_eta[nMuon]/F");
  tree->Branch("Muon_phi", value_mu_phi, "Muon_phi[nMuon]/F");
  tree->Branch("Muon_mass", value_mu_mass, "Muon_mass[nMuon]/F");
  tree->Branch("Muon_charge", value_mu_charge, "Muon_charge[nMuon]/I");
  tree->Branch("Muon_pfRelIso03_all", value_mu_pfreliso03all, "Muon_pfRelIso03_all[nMuon]/F");
  tree->Branch("Muon_pfRelIso04_all", value_mu_pfreliso04all, "Muon_pfRelIso04_all[nMuon]/F");
  tree->Branch("Muon_tightId", value_mu_tightid, "Muon_tightId[nMuon]/O");
  tree->Branch("Muon_softId", value_mu_softid, "Muon_softId[nMuon]/O");
  tree->Branch("Muon_dxy", value_mu_dxy, "Muon_dxy[nMuon]/F");
  tree->Branch("Muon_dxyErr", value_mu_dxyErr, "Muon_dxyErr[nMuon]/F");
  tree->Branch("Muon_dz", value_mu_dz, "Muon_dz[nMuon]/F");
  tree->Branch("Muon_dzErr", value_mu_dzErr, "Muon_dzErr[nMuon]/F");
  tree->Branch("Muon_jetIdx", value_mu_jetidx, "Muon_jetIdx[nMuon]/I");
  tree->Branch("Muon_genPartIdx", value_mu_genpartidx, "Muon_genPartIdx[nMuon]/I");

  // Electrons
  tree->Branch("nElectron", &value_el_n, "nElectron/i");
  tree->Branch("Electron_pt", value_el_pt, "Electron_pt[nElectron]/F");
  tree->Branch("Electron_eta", value_el_eta, "Electron_eta[nElectron]/F");
  tree->Branch("Electron_phi", value_el_phi, "Electron_phi[nElectron]/F");
  tree->Branch("Electron_mass", value_el_mass, "Electron_mass[nElectron]/F");
  tree->Branch("Electron_charge", value_el_charge, "Electron_charge[nElectron]/I");
  tree->Branch("Electron_pfRelIso03_all", value_el_pfreliso03all, "Electron_pfRelIso03_all[nElectron]/F");
  tree->Branch("Electron_dxy", value_el_dxy, "Electron_dxy[nElectron]/F");
  tree->Branch("Electron_dxyErr", value_el_dxyErr, "Electron_dxyErr[nElectron]/F");
  tree->Branch("Electron_dz", value_el_dz, "Electron_dz[nElectron]/F");
  tree->Branch("Electron_dzErr", value_el_dzErr, "Electron_dzErr[nElectron]/F");
  tree->Branch("Electron_cutBasedId", value_el_cutbasedid, "Electron_cutBasedId[nElectron]/O");
  tree->Branch("Electron_pfId", value_el_pfid, "Electron_pfId[nElectron]/O");
  tree->Branch("Electron_jetIdx", value_el_jetidx, "Electron_jetIdx[nElectron]/I");
  tree->Branch("Electron_genPartIdx", value_el_genpartidx, "Electron_genPartIdx[nElectron]/I");
  tree->Branch("Electron_dEtaIn", value_el_dEtaIn, "Electron_dEtaIn[nElectron]/F");
  tree->Branch("Electron_dPhiIn", value_el_dPhiIn, "Electron_dPhiIn[nElectron]/F");
  tree->Branch("Electron_sigmaIEtaIEta", value_el_sigmaIEtaIEta, "Electron_sigmaIEtaIEta[nElectron]/F");
  tree->Branch("Electron_HoE", value_el_HoE, "Electron_HoE[nElectron]/F");
  tree->Branch("Electron_fbrem", value_el_fbrem, "Electron_fbrem[nElectron]/F");
  tree->Branch("Electron_EoP_In", value_el_EoP_In, "Electron_EoP_In[nElectron]/F");
  tree->Branch("Electron_IoEIoP_In", value_el_IoEIoP_In, "Electron_IoEIoP_In[nElectron]/F");
  tree->Branch("Electron_Nmisshits", value_el_Nmisshits, "Electron_Nmisshits[nElectron]/F");
  
  // Taus
  tree->Branch("nTau", &value_tau_n, "nTau/i");
  tree->Branch("Tau_pt", value_tau_pt, "Tau_pt[nTau]/F");
  tree->Branch("Tau_eta", value_tau_eta, "Tau_eta[nTau]/F");
  tree->Branch("Tau_phi", value_tau_phi, "Tau_phi[nTau]/F");
  tree->Branch("Tau_mass", value_tau_mass, "Tau_mass[nTau]/F");
  tree->Branch("Tau_charge", value_tau_charge, "Tau_charge[nTau]/I");
  tree->Branch("Tau_decayMode", value_tau_decaymode, "Tau_decayMode[nTau]/I");
  tree->Branch("Tau_relIso_all", value_tau_reliso_all, "Tau_relIso_all[nTau]/F");
  tree->Branch("Tau_jetIdx", value_tau_jetidx, "Tau_jetIdx[nTau]/I");
  tree->Branch("Tau_genPartIdx", value_tau_genpartidx, "Tau_genPartIdx[nTau]/I");
  tree->Branch("Tau_idDecayMode", value_tau_iddecaymode, "Tau_idDecayMode[nTau]/O");
  tree->Branch("Tau_idIsoRaw", value_tau_idisoraw, "Tau_idIsoRaw[nTau]/F");
  tree->Branch("Tau_idIsoVLoose", value_tau_idisovloose, "Tau_idIsoVLoose[nTau]/O");
  tree->Branch("Tau_idIsoLoose", value_tau_idisoloose, "Tau_idIsoLoose[nTau]/O");
  tree->Branch("Tau_idIsoMedium", value_tau_idisomedium, "Tau_idIsoMedium[nTau]/O");
  tree->Branch("Tau_idIsoTight", value_tau_idisotight, "Tau_idIsoTight[nTau]/O");
  tree->Branch("Tau_idAntiEleLoose", value_tau_idantieleloose, "Tau_idAntiEleLoose[nTau]/O");
  tree->Branch("Tau_idAntiEleMedium", value_tau_idantielemedium, "Tau_idAntiEleMedium[nTau]/O");
  tree->Branch("Tau_idAntiEleTight", value_tau_idantieletight, "Tau_idAntiEleTight[nTau]/O");
  tree->Branch("Tau_idAntiMuLoose", value_tau_idantimuloose, "Tau_idAntiMuLoose[nTau]/O");
  tree->Branch("Tau_idAntiMuMedium", value_tau_idantimumedium, "Tau_idAntiMuMedium[nTau]/O");
  tree->Branch("Tau_idAntiMuTight", value_tau_idantimutight, "Tau_idAntiMuTight[nTau]/O");
  
  // Photons
  tree->Branch("nPhoton", &value_ph_n, "nPhoton/i");
  tree->Branch("Photon_pt", value_ph_pt, "Photon_pt[nPhoton]/F");
  tree->Branch("Photon_eta", value_ph_eta, "Photon_eta[nPhoton]/F");
  tree->Branch("Photon_phi", value_ph_phi, "Photon_phi[nPhoton]/F");
  tree->Branch("Photon_mass", value_ph_mass, "Photon_mass[nPhoton]/F");
  tree->Branch("Photon_charge", value_ph_charge, "Photon_charge[nPhoton]/I");
  tree->Branch("Photon_pfRelIso03_all", value_ph_pfreliso03all, "Photon_pfRelIso03_all[nPhoton]/F");
  tree->Branch("Photon_jetIdx", value_ph_jetidx, "Photon_jetIdx[nPhoton]/I");
  tree->Branch("Photon_genPartIdx", value_ph_genpartidx, "Photon_genPartIdx[nPhoton]/I");

  // MET
  tree->Branch("MET_pt", &value_met_pt, "MET_pt/F");
  tree->Branch("MET_phi", &value_met_phi, "MET_phi/F");
  tree->Branch("MET_sumet", &value_met_sumet, "MET_sumet/F");
  tree->Branch("MET_significance", &value_met_significance, "MET_significance/F");
  tree->Branch("MET_CovXX", &value_met_covxx, "MET_CovXX/F");
  tree->Branch("MET_CovXY", &value_met_covxy, "MET_CovXY/F");
  tree->Branch("MET_CovYY", &value_met_covyy, "MET_CovYY/F");

  // Jets
  tree->Branch("nJet", &value_jet_n, "nJet/i");
  tree->Branch("Jet_pt", value_jet_pt, "Jet_pt[nJet]/F");
  tree->Branch("Jet_eta", value_jet_eta, "Jet_eta[nJet]/F");
  tree->Branch("Jet_phi", value_jet_phi, "Jet_phi[nJet]/F");
  tree->Branch("Jet_mass", value_jet_mass, "Jet_mass[nJet]/F");
  tree->Branch("Jet_puId", value_jet_puid, "Jet_puId[nJet]/O");
  tree->Branch("Jet_btag", value_jet_btag, "Jet_btag[nJet]/F");

  // Generator particles
  if (!isData) {
    tree->Branch("nGenPart", &value_gen_n, "nGenPart/i");
    tree->Branch("GenPart_pt", value_gen_pt, "GenPart_pt[nGenPart]/F");
    tree->Branch("GenPart_eta", value_gen_eta, "GenPart_eta[nGenPart]/F");
    tree->Branch("GenPart_phi", value_gen_phi, "GenPart_phi[nGenPart]/F");
    tree->Branch("GenPart_mass", value_gen_mass, "GenPart_mass[nGenPart]/F");
    tree->Branch("GenPart_pdgId", value_gen_pdgid, "GenPart_pdgId[nGenPart]/I");
    tree->Branch("GenPart_status", value_gen_status, "GenPart_status[nGenPart]/I");
  }
}

AOD2NanoAOD::~AOD2NanoAOD() {}

void AOD2NanoAOD::analyze(const edm::Event &iEvent,
                          const edm::EventSetup &iSetup) {

  using namespace edm;
  using namespace reco;
  using namespace std;

  // persist elements initialization
  selectedMuons.clear();
  selectedElectrons.clear();
  selectedTaus.clear();
  selectedPhotons.clear();
  selectedJets.clear();
  interestingGenParticles.clear();

  // Event information
  value_run = iEvent.run();
  value_lumi_block = iEvent.luminosityBlock();
  value_event = iEvent.id().event();

  // Trigger results
  Handle<TriggerResults> trigger;
  iEvent.getByLabel(InputTag("TriggerResults", "", "HLT"), trigger);
  fillTrigger(trigger);

  // Vertex
  Handle<VertexCollection> vertices;
  iEvent.getByLabel(InputTag("offlinePrimaryVertices"), vertices);
  fillVertex(vertices);

  // Muons
  Handle<MuonCollection> muons;
  iEvent.getByLabel(InputTag("muons"), muons);
  fillMuon(muons,vertices);

  // Electrons
  Handle<GsfElectronCollection> electrons;
  iEvent.getByLabel(InputTag("gsfElectrons"), electrons);
  fillElectron(electrons,vertices);

  // Taus
  fillTau(iEvent);

  // Photons
  Handle<PhotonCollection> photons;
  iEvent.getByLabel(InputTag("photons"), photons);
  fillPhoton(photons);

  // MET
  Handle<PFMETCollection> met;
  iEvent.getByLabel(InputTag("pfMet"), met);
  fillMET(met);

  // Jets
  Handle<CaloJetCollection> jets;
  iEvent.getByLabel(InputTag("ak5CaloJets"), jets);
  Handle<JetTagCollection> btags;
  iEvent.getByLabel(InputTag("combinedSecondaryVertexBJetTags"), btags);
  fillJet(jets,btags);

  // Generator particles
  if (!isData){
    
    // Genpart
    Handle<GenParticleCollection> gens;
    iEvent.getByLabel(InputTag("genParticles"), gens);
    fillGenpart(gens);

  }

  tree->Fill();

}

void AOD2NanoAOD::beginJob() {}

void AOD2NanoAOD::endJob() {}
 
void AOD2NanoAOD::endRun(const edm::Run &run, const edm::EventSetup &)
{

  // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideDataFormatGeneratorInterface#Using_other_products_AODSIM
  edm::Handle<GenRunInfoProduct> genRunInfo;
  run.getByLabel( "generator", genRunInfo );
  value_Xsec = !isData ? genRunInfo->crossSection() : 1. ;
 
  tree->Fill();
}


//void AOD2NanoAOD::endRun(edm::Run const&, edm::EventSetup const&)
//{
  // https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideDataFormatGeneratorInterface#Using_other_products_AODSIM
  //GenRunInfoProduct_generator__SIM. → GenRunInfoProduct_generator__SIM.obj → InternalXSec → value_.
  //if (!isData){
  //  edm::Handle<GenRunInfoProduct> genRunInfo;
  //  iRun.getByLabel( "generator", genRunInfo );
  //  value_Xsec = genRunInfo.InternalXsec();
  //}
  //else{
  //  value_Xsec = 1.;
  //}
//}


DEFINE_FWK_MODULE(AOD2NanoAOD);
