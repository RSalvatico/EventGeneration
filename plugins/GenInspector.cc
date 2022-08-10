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
 
#include "GenInspector.h"

using namespace std;
 
// constructors and destructor
GenInspector::GenInspector(const edm::ParameterSet& iConfig)
{
  genParticlesToken_ = consumes<std::vector<reco::GenParticle> >(edm::InputTag("genParticles"));

  //create_trees();
}

GenInspector::~GenInspector()
{
}

// ------------ method called for each event  ------------
void GenInspector::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<std::vector<reco::GenParticle>  > genParticles;
  iEvent.getByToken(genParticlesToken_, genParticles);

  // int genN2_ID    = -999;
  // float genN2_pT  = -999.;
  // float genN2_eta = -999.;
  // float genN2_phi = -999.;
  // float genN2_E   = -999.;

  // int genC1_ID    = -999;
  // float genC1_pT  = -999.;
  // float genC1_eta = -999.;
  // float genC1_phi = -999.;
  // float genC1_E   = -999.;

  // int genN1_ID    = -999;
  // float genN1_pT  = -999.;
  // float genN1_eta = -999.;
  // float genN1_phi = -999.;
  // float genN1_E   = -999.;

  // genN2_ID_tree  = 0;
  // genN2_pT_tree  = 0.;
  // genN2_eta_tree = 0.;
  // genN2_phi_tree = 0.;
  // genN2_E_tree   = 0.;

  // genC1_ID_tree  = 0;
  // genC1_pT_tree  = 0.;
  // genC1_eta_tree = 0.;
  // genC1_phi_tree = 0.;
  // genC1_E_tree   = 0.;

  // genN1_ID_tree  = 0;
  // genN1_pT_tree  = 0.;
  // genN1_eta_tree = 0.;
  // genN1_phi_tree = 0.;
  // genN1_E_tree   = 0.;


  for(auto gen = genParticles->begin(); gen != genParticles->end(); ++gen){


    if(fabs(gen->pdgId()) == 1000023 && gen->numberOfDaughters() == 2){
      cout << "#### N2 ####" << endl;

      for(int i = 0; i < 2; i++){
	cout << "PDGID: " << gen->daughter(i)->pdgId() << "\n";
      }
      cout << "#################" << endl;
    }

    if(fabs(gen->pdgId()) == 1000024 && gen->numberOfDaughters() == 2){

      if (gen->mother()->pdgId() == 1000023){
	cout << "#### N2 -> C1: " << gen->pdgId() << " ####" << endl;

	for(int i = 0; i < 2; i++){
	  cout << "PDGID: " << gen->daughter(i)->pdgId() << "\n";
	}
	cout << "#################\n";
      }
      else{
	cout << "#### C1: " << gen->pdgId() << " ####" << endl;
	for(int i = 0; i < 2; i++){
	  cout << "PDGID: " << gen->daughter(i)->pdgId() << "\n";
	}
	cout << "#################\n";
      }
    }  
  }
}
void GenInspector::beginJob()
{
}

void GenInspector::endJob() 
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenInspector);
