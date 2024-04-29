//---------- class declaration----------

class GenInspector : public edm::EDAnalyzer {

 public:
  explicit GenInspector(const edm::ParameterSet&);
  ~GenInspector();

 private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() override;
  static bool greaterThan (double i, double j) { return (i>j); }

  edm::Service<TFileService> fs;

  void create_trees();

  // ---------- member data ----------- //

  TTree *mytree;
  std::vector<int> lepID_tree;
  std::vector<int> lepMother_tree;
  std::vector<double> lepPt_tree;
  int initialState_tree;
  bool isLepFromSparticle_tree;
  double genMET_tree;
  int nLepEvent_tree;
  double maxLepPtOne_tree;
  double maxLepPtTwo_tree;
  double maxLepPtThree_tree;
  bool trMu24_tree;
  bool trEle30_tree;
  bool trEle23Ele12_tree;
  bool trMu12Ele23_tree;
  bool trMu23Ele12_tree;
  
  edm::EDGetTokenT<std::vector<reco::GenParticle> > genParticlesToken_;
  edm::EDGetTokenT<std::vector<reco::GenMET> > genMETToken_; 
  //edm::EDGetTokenT<GenEventInfoProduct> GenInfoToken_;
};
