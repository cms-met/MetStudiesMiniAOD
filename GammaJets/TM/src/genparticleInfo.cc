#include "GammaJets/TM/interface/genparticleInfo.h"

genparticleInfo::genparticleInfo(std::string name, TTree* tree, bool debug, const pset& iConfig):baseTree(name,tree,debug){
  if(debug) std::cout<<"in genparticle constructor"<<std::endl;
  genParticleLabel_               = iConfig.getUntrackedParameter<edm::InputTag> ("genParticleLabel_");
  Gen_Photon_4Momentum            = new TClonesArray("TLorentzVector");

  if(debug) std::cout<<"in genparticle constructor: calling SetBrances()"<<std::endl;
  SetBranches();
}

genparticleInfo::~genparticleInfo(){
  delete tree_;
  delete Gen_Photon_4Momentum            ;
}

void genparticleInfo::Fill(const edm::Event& iEvent){
  Clear();
  if(debug_)    std::cout<<"getting genparticle info"<<std::endl;
  
  edm::Handle<reco::GenParticleCollection> genParticles;
  iEvent.getByLabel(genParticleLabel_, genParticles);
  if(not iEvent.getByLabel(genParticleLabel_, genParticles )){
    std::cout<<"FATAL EXCEPTION: "<<"Following Not Found: "<<genParticleLabel_<<std::endl;
    exit(0);
  }

  reco::GenParticleCollection genColl(*(genParticles.product()));
  std::sort(genColl.begin(),genColl.end(),PtGreater());
  for (reco::GenParticleCollection::const_iterator genparticle = genParticles->begin(); genparticle != genParticles->end(); genparticle++){
      if (genparticle->pdgId() == 22 && genparticle->status() == 1){ 
	  new( (*Gen_Photon_4Momentum)[Gen_Photon_n]) TLorentzVector((float)genparticle->px(),
								     (float)genparticle->py(),
								     (float)genparticle->pz(),
								     (float)genparticle->energy());
	  Gen_Photon_isPrompt.push_back(genparticle->isPromptFinalState());
	  Gen_Photon_n++;
	}
    }
 
  if(debug_) cout<<"got genparticle info"<<endl;  
}


void genparticleInfo::SetBranches(){
  if(debug_)    std::cout<<"setting branches: calling AddBranch of baseTree"<<std::endl;
  AddBranch(&Gen_Photon_n                    ,"Gen_Photon_n");
  AddBranch(&Gen_Photon_isPrompt             ,"Gen_Photon_isPrompt");
  AddBranch(&Gen_Photon_4Momentum            ,"Gen_Photon_4Momentum");
 
  if(debug_)    std::cout<<"set branches"<<std::endl;
}

void genparticleInfo::Clear(){
  if(debug_)std::cout<<"clearing Photon info"<<std::endl;

  Gen_Photon_n = 0;
  Gen_Photon_isPrompt.clear();
  Gen_Photon_4Momentum->Clear();            

  if(debug_) std::cout<<"cleared"<<std::endl;
}

