//ROOT includes
#include <TH1F.h>
#include <TFile.h>
#include <TLorentzVector.h>
#include <TTree.h>
#include "Math/VectorUtil.h"
#include <stdlib.h>
#include <algorithm> 

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/MET.h"
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
  genMETToken_       = consumes<std::vector<reco::GenMET> >(edm::InputTag("genMetTrue"));
  create_trees();
}

GenInspector::~GenInspector()
{
}

// ------------ method called for each event  ------------
void GenInspector::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<std::vector<reco::GenParticle>  > genParticles;
  iEvent.getByToken(genParticlesToken_, genParticles);

  edm::Handle<std::vector<reco::GenMET> > genMETs;
  iEvent.getByToken(genMETToken_, genMETs);
  
  initialState_tree = -999;;
  int initialState = -999;
  int nSlep = 0;
  int nSnu  = 0;
  double genMET = -999;
  genMET_tree = -999;
  lepID_tree.clear();
  lepMother_tree.clear();
  lepPt_tree.clear();
  isLepFromSparticle_tree = false;
  bool isLepFromSparticle = false;
  maxLepPtOne_tree   = -999;
  maxLepPtTwo_tree   = -999;
  maxLepPtThree_tree = -999;
  nLepEvent_tree = 0;
  bool trSingleMu24 = false;
  bool trSingleEle30 = false;
  bool trDoubleEle23 = false;
  bool trDoubleEle12 = false;
  bool trDoubleMu12 = false;
  bool trDoubleMu23 = false;
  trMu24_tree = false;
  trEle30_tree = false;
  trEle23Ele12_tree = false;
  trMu12Ele23_tree = false;
  trMu23Ele12_tree = false;
  
  
  for(auto gen = genParticles->begin(); gen != genParticles->end(); ++gen){
    
    if(fabs(gen->pdgId()) == 1000011 && int(gen->numberOfDaughters()) == 2){//Selectron
      nSlep++;
      //std::cout << "daughters Selectron: " << gen->daughter(0)->pdgId() << " " << gen->daughter(1)->pdgId() << std::endl;
    }

    if(fabs(gen->pdgId()) == 1000013 && int(gen->numberOfDaughters()) == 2){//Smuon
      nSlep++;
      //std::cout << "daughter Smuon: " << gen->daughter(0)->pdgId() << " " << gen->daughter(1)->pdgId() << std::endl;
    }
    
    if(fabs(gen->pdgId()) == 1000012 && int(gen->numberOfDaughters()) == 2){//Electron sneutrino
      nSnu++;
      //std::cout << "daughter SneuEl: " << gen->daughter(0)->pdgId() << " " << gen->daughter(1)->pdgId() << std::endl;
    }

    if(fabs(gen->pdgId()) == 1000014 && int(gen->numberOfDaughters()) == 2){//Muon sneutrino
      nSnu++;
      //std::cout << "daughter SneuMu: " << gen->daughter(0)->pdgId() << " " << gen->daughter(1)->pdgId() << std::endl;
    }    
  }

  if(nSlep==2 && nSnu==0) initialState = 1; //SlepSlep
  if(nSlep==1 && nSnu==1) initialState = 2; //SlepSnu
  if(nSlep==0 && nSnu==2) initialState = 3; //SnuSnu

  initialState_tree = initialState;

  //Leptons
  for(auto gen = genParticles->begin(); gen != genParticles->end(); ++gen){

    if( (abs(gen->pdgId()) == 11 && fabs(gen->eta()) > 2.5) || (abs(gen->pdgId()) == 13 && fabs(gen->eta()) > 2.4) ) continue;

    if( (abs(gen->pdgId()) == 11  || abs(gen->pdgId()) == 13) && (abs(gen->mother()->pdgId()) == 1000011 || abs(gen->mother()->pdgId()) == 1000012 || abs(gen->mother()->pdgId()) == 1000013 || abs(gen->mother()->pdgId()) == 1000014 || abs(gen->mother()->pdgId()) == 23 || abs(gen->mother()->pdgId()) == 24) ){

      nLepEvent_tree++;
      lepID_tree.emplace_back(int(gen->pdgId()));
      lepPt_tree.emplace_back(double(gen->pt()));
      lepMother_tree.emplace_back(int(gen->mother()->pdgId()));

      if( !(abs(gen->mother()->pdgId()) == 23 || abs(gen->mother()->pdgId()) == 24) ) isLepFromSparticle = true;
    }
    isLepFromSparticle_tree = isLepFromSparticle;      
  }

  std::sort (lepPt_tree.begin(), lepPt_tree.end(), greaterThan);
  maxLepPtOne_tree   = nLepEvent_tree > 0 ? lepPt_tree.at(0) : 0;
  maxLepPtTwo_tree   = nLepEvent_tree > 1 ? lepPt_tree.at(1) : 0;
  maxLepPtThree_tree = nLepEvent_tree > 2 ? lepPt_tree.at(2) : 0;


  for(auto gen = genParticles->begin(); gen != genParticles->end(); ++gen){

    if( (abs(gen->pdgId()) == 11 && fabs(gen->eta()) > 2.5) || (abs(gen->pdgId()) == 13 && fabs(gen->eta()) > 2.4) ) continue;

    if( (abs(gen->pdgId()) == 11  || abs(gen->pdgId()) == 13) && (abs(gen->mother()->pdgId()) == 1000011 || abs(gen->mother()->pdgId()) == 1000012 || abs(gen->mother()->pdgId()) == 1000013 || abs(gen->mother()->pdgId()) == 1000014 || abs(gen->mother()->pdgId()) == 23 || abs(gen->mother()->pdgId()) == 24) ){

      if(abs(gen->pdgId()) == 13 && gen->pt() > 25 ){
	trSingleMu24 = true;
	break;
      }
      if(abs(gen->pdgId()) == 11 && gen->pt() > 31 ){
	trSingleEle30 = true;
        break;
      }      
      if(abs(gen->pdgId()) == 13 && gen->pt() > 24 ){
	trDoubleMu23 = true;
      }
      if(abs(gen->pdgId()) == 13 && gen->pt() > 13 ){
	trDoubleMu12 = true;
      }
      if(abs(gen->pdgId()) == 11 && gen->pt() > 24 ){
        trDoubleEle23 = true;
      }
      if(abs(gen->pdgId()) == 11 && gen->pt() > 13 ){
        trDoubleEle12 = true;
      }

    }
  }

  trMu24_tree  = trSingleMu24;
  trEle30_tree = trSingleEle30;
  trEle23Ele12_tree = (trDoubleEle23 && trDoubleEle12) ? true : false;
  trMu12Ele23_tree = (trDoubleMu12 && trDoubleEle23) ? true : false;
  trMu23Ele12_tree = (trDoubleMu23 && trDoubleEle12) ? true : false;
  
  //MET
  for(auto met = genMETs->begin(); met != genMETs->end(); ++ met){
    genMET = met->pt();
  }
  genMET_tree = genMET;

  
  mytree->Fill();
}

void GenInspector::create_trees()
{
  mytree = fs->make<TTree>("mytree", "Tree containing gen info");

  mytree->Branch("initialState",&initialState_tree);
  mytree->Branch("lepID",&lepID_tree);
  mytree->Branch("lepMother",&lepMother_tree);
  mytree->Branch("lepPt",&lepPt_tree);
  mytree->Branch("genMET",&genMET_tree);
  mytree->Branch("isLepFromSparticle",&isLepFromSparticle_tree);
  mytree->Branch("nLepEvent",&nLepEvent_tree);
  mytree->Branch("maxLepPtOne",&maxLepPtOne_tree);
  mytree->Branch("maxLepPtTwo",&maxLepPtTwo_tree);
  mytree->Branch("maxLepPtThree",&maxLepPtThree_tree);
  mytree->Branch("trMu24",&trMu24_tree);
  mytree->Branch("trEle30",&trEle30_tree);
  mytree->Branch("trEle23Ele12",&trEle23Ele12_tree);
  mytree->Branch("trMu12Ele23",&trMu12Ele23_tree);
  mytree->Branch("trMu23Ele12",&trMu23Ele12_tree);
}

void GenInspector::beginJob()
{
}

void GenInspector::endJob() 
{
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenInspector);
