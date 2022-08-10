//---------- class declaration----------

class InspectGenparticles : public edm::EDAnalyzer {

public:
  explicit InspectGenparticles(const edm::ParameterSet&);
  ~InspectGenparticles();

private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() override;

  const edm::InputTag genParticles_;

  edm::Service<TFileService> fs;

  int genZ_ID_tree;
  int ZDau1_ID_tree;
  int ZDau2_ID_tree;
  float genZ_pT_tree;
  float genZ_eta_tree;
  float genZ_phi_tree;
  float ZDau1_pT_tree;
  float ZDau1_eta_tree;
  float ZDau1_phi_tree;
  float ZDau2_pT_tree;
  float ZDau2_eta_tree;
  float ZDau2_phi_tree;

  void create_trees();

  // ---------- member data ----------- //

  TTree *mytree;

  edm::EDGetTokenT<std::vector<reco::GenParticle> > genParticlesToken_; 
};
