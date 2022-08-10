//ROOT includes
#include <TH1F.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include "Math/VectorUtil.h"
#include <stdlib.h>

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Common/interface/TriggerNames.h" 
 
#include "InspectGenparticles.h"
 
// constructors and destructor
InspectGenparticles::InspectGenparticles(const edm::ParameterSet& iConfig)
{
  genParticlesToken_ = consumes<std::vector<reco::GenParticle> >(edm::InputTag("genParticles"));

  create_trees();
}

InspectGenparticles::~InspectGenparticles()
{
}

// ------------ method called for each event  ------------
void InspectGenparticles::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<std::vector<reco::GenParticle>  > genParticles;
  iEvent.getByToken(genParticlesToken_, genParticles);

  int genZ_ID     = -999;
  int ZDau1_ID    = -999;
  int ZDau2_ID    = -999;
  float genZ_pT   = -999;
  float genZ_eta  = -999;
  float genZ_phi  = -999;
  float ZDau1_pT  = -999;
  float ZDau1_eta = -999;
  float ZDau1_phi = -999;
  float ZDau2_pT  = -999;
  float ZDau2_eta = -999;
  float ZDau2_phi = -999;

  genZ_ID_tree     = -999;
  ZDau1_ID_tree    = -999;
  ZDau2_ID_tree    = -999;
  genZ_pT_tree   = -999;
  genZ_eta_tree  = -999;
  genZ_phi_tree  = -999;
  ZDau1_pT_tree  = -999;
  ZDau1_eta_tree = -999;
  ZDau1_phi_tree = -999;
  ZDau2_pT_tree  = -999;
  ZDau2_eta_tree = -999;
  ZDau2_phi_tree = -999;


  for(auto gen = genParticles->begin(); gen != genParticles->end(); ++gen){

    if(abs(gen->pdgId()) == 23 && abs(gen->mother()->pdgId()) == 1000023  && gen->numberOfDaughters() == 2){

      genZ_ID  = gen->pdgId();
      genZ_pT  = gen->pt();
      genZ_eta = gen->eta();
      genZ_phi = gen->phi();
      
      ZDau1_ID  = gen->daughter(0)->pdgId();
      ZDau1_pT  = gen->daughter(0)->pt();
      ZDau1_eta = gen->daughter(0)->eta();
      ZDau1_phi = gen->daughter(0)->phi();
      
      ZDau2_ID  = gen->daughter(1)->pdgId();
      ZDau2_pT  = gen->daughter(1)->pt();
      ZDau2_eta = gen->daughter(1)->eta();
      ZDau2_phi = gen->daughter(1)->phi();

    }
  }

  genZ_ID_tree  = genZ_ID;
  genZ_pT_tree  = genZ_pT;
  genZ_eta_tree = genZ_eta;
  genZ_phi_tree = genZ_phi;

  ZDau1_ID_tree  = ZDau1_ID;
  ZDau1_pT_tree  = ZDau1_pT;
  ZDau1_eta_tree = ZDau1_eta;
  ZDau1_phi_tree = ZDau1_phi;

  ZDau2_ID_tree  = ZDau2_ID;
  ZDau2_pT_tree  = ZDau2_pT;
  ZDau2_eta_tree = ZDau2_eta;
  ZDau2_phi_tree = ZDau2_phi;
      
  mytree->Fill();
}

//*************************************************************//
//                                                             //
//---------------------- Create the tree ----------------------//
//                                                             //
//*************************************************************//

void InspectGenparticles::create_trees()
{
  mytree = fs->make<TTree>("mytree", "Tree containing gen info");

  mytree->Branch("genZ_ID",&genZ_ID_tree);
  mytree->Branch("genZ_pT",&genZ_pT_tree);
  mytree->Branch("genZ_eta",&genZ_eta_tree);
  mytree->Branch("genZ_phi",&genZ_phi_tree);
  
  mytree->Branch("ZDau1_ID",&ZDau1_ID_tree);
  mytree->Branch("ZDau1_pT",&ZDau1_pT_tree);
  mytree->Branch("ZDau1_eta",&ZDau1_eta_tree);
  mytree->Branch("ZDau1_phi",&ZDau1_phi_tree);

  mytree->Branch("ZDau2_ID",&ZDau2_ID_tree);
  mytree->Branch("ZDau2_pT",&ZDau2_pT_tree);
  mytree->Branch("ZDau2_eta",&ZDau2_eta_tree);
  mytree->Branch("ZDau2_phi",&ZDau2_phi_tree);
    
}

void InspectGenparticles::beginJob()
{
}

void InspectGenparticles::endJob() 
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(InspectGenparticles);
