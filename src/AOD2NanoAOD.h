#include <memory>

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/Common/interface/Ref.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "math.h"

#include "TFile.h"
#include "TTree.h"

#include "DataFormats/TrackReco/interface/HitPattern.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"

#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/PhotonFwd.h"

#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/PFMETFwd.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/BTauReco/interface/JetTag.h"

#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/TauReco/interface/PFTauDiscriminator.h"
#include "DataFormats/TauReco/interface/PFTauFwd.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/Common/interface/TriggerResultsByName.h"
#include "FWCore/ParameterSet/interface/Registry.h"

#include "helper.h"

const static std::vector<std::string> interestingTriggers = {
  "HLT_IsoMu24_eta2p1",
  "HLT_IsoMu24",
  "HLT_IsoMu17_eta2p1_LooseIsoPFTau20",
};

class AOD2NanoAOD : public edm::EDAnalyzer {
 public:
  explicit AOD2NanoAOD(const edm::ParameterSet&);
  ~AOD2NanoAOD();
  
 private:
  virtual void beginJob();
  virtual void analyze(const edm::Event &, const edm::EventSetup &);
  virtual void endJob();
  virtual void fillTrigger(edm::Handle<edm::TriggerResults> &);
  virtual void fillVertex(edm::Handle<reco::VertexCollection> &);
  virtual void fillMuon(edm::Handle<reco::MuonCollection> &, edm::Handle<reco::VertexCollection> &);
  virtual void fillElectron(edm::Handle<reco::GsfElectronCollection> &, edm::Handle<reco::VertexCollection> &);
  virtual void fillTau(const edm::Event &iEvent);
  virtual void fillPhoton(edm::Handle<reco::PhotonCollection> &);
  virtual void fillMET(edm::Handle<reco::PFMETCollection> &);
  virtual void fillJet(edm::Handle<reco::CaloJetCollection> &, edm::Handle<reco::JetTagCollection> &);
  virtual void fillGenpart(edm::Handle<reco::GenParticleCollection> &);

  bool providesGoodLumisection(const edm::Event &iEvent);
  bool isData;

  TTree *tree;

  // Event information
  Int_t value_run;
  UInt_t value_lumi_block;
  ULong64_t value_event;

  // Trigger
  const static int max_trig = 1000;
  bool value_trig[max_trig];

  // Vertices
  int value_ve_n;
  float value_ve_x;
  float value_ve_y;
  float value_ve_z;

  // Muons
  const static int max_mu = 1000;
  UInt_t value_mu_n;
  float value_mu_pt[max_mu];
  float value_mu_eta[max_mu];
  float value_mu_phi[max_mu];
  float value_mu_mass[max_mu];
  int value_mu_charge[max_mu];
  float value_mu_pfreliso03all[max_mu];
  float value_mu_pfreliso04all[max_mu];
  bool value_mu_tightid[max_mu];
  bool value_mu_softid[max_mu];
  float value_mu_dxy[max_mu];
  float value_mu_dxyErr[max_mu];
  float value_mu_dz[max_mu];
  float value_mu_dzErr[max_mu];
  int value_mu_genpartidx[max_mu];
  int value_mu_jetidx[max_mu];

  // Electrons
  const static int max_el = 1000;
  UInt_t value_el_n;
  float value_el_pt[max_el];
  float value_el_eta[max_el];
  float value_el_phi[max_el];
  float value_el_mass[max_el];
  int value_el_charge[max_el];
  float value_el_pfreliso03all[max_el];
  float value_el_dxy[max_el];
  float value_el_dxyErr[max_el];
  float value_el_dz[max_el];
  float value_el_dzErr[max_el];
  bool value_el_cutbasedid[max_el];
  bool value_el_pfid[max_el];
  int value_el_genpartidx[max_el];
  int value_el_jetidx[max_el];

  // Taus
  const static int max_tau = 1000;
  UInt_t value_tau_n;
  float value_tau_pt[max_tau];
  float value_tau_eta[max_tau];
  float value_tau_phi[max_tau];
  float value_tau_mass[max_tau];
  int value_tau_charge[max_tau];
  int value_tau_decaymode[max_tau];
  float value_tau_reliso_all[max_tau];
  int value_tau_genpartidx[max_tau];
  int value_tau_jetidx[max_tau];
  bool value_tau_iddecaymode[max_tau];
  float value_tau_idisoraw[max_tau];
  bool value_tau_idisovloose[max_tau];
  bool value_tau_idisoloose[max_tau];
  bool value_tau_idisomedium[max_tau];
  bool value_tau_idisotight[max_tau];
  bool value_tau_idantieleloose[max_tau];
  bool value_tau_idantielemedium[max_tau];
  bool value_tau_idantieletight[max_tau];
  bool value_tau_idantimuloose[max_tau];
  bool value_tau_idantimumedium[max_tau];
  bool value_tau_idantimutight[max_tau];

  // Photons
  const static int max_ph = 1000;
  UInt_t value_ph_n;
  float value_ph_pt[max_ph];
  float value_ph_eta[max_ph];
  float value_ph_phi[max_ph];
  float value_ph_mass[max_ph];
  int value_ph_charge[max_ph];
  float value_ph_pfreliso03all[max_ph];
  int value_ph_genpartidx[max_ph];
  int value_ph_jetidx[max_ph];

  // MET
  float value_met_pt;
  float value_met_phi;
  float value_met_sumet;
  float value_met_significance;
  float value_met_covxx;
  float value_met_covxy;
  float value_met_covyy;

  // Jets
  const static int max_jet = 1000;
  UInt_t value_jet_n;
  float value_jet_pt[max_jet];
  float value_jet_eta[max_jet];
  float value_jet_phi[max_jet];
  float value_jet_mass[max_jet];
  bool value_jet_puid[max_jet];
  float value_jet_btag[max_jet];

  // Generator particles
  const static int max_gen = 1000;
  UInt_t value_gen_n;
  float value_gen_pt[max_gen];
  float value_gen_eta[max_gen];
  float value_gen_phi[max_gen];
  float value_gen_mass[max_gen];
  int value_gen_pdgid[max_gen];
  int value_gen_status[max_gen];
  
  edm::Service<TFileService> fs;

  // persist elements
  std::vector<reco::Muon> selectedMuons;
  std::vector<reco::GsfElectron> selectedElectrons;
  std::vector<reco::PFTau> selectedTaus;
  std::vector<reco::Photon> selectedPhotons;
  std::vector<reco::CaloJet> selectedJets;
  std::vector<reco::GenParticle> interestingGenParticles;
};
