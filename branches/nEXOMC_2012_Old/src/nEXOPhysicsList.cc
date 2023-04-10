
#include "nEXOPhysicsList.hh"
#include "nEXOPhysicsListMessenger.hh"

#include "nEXOPhysListParticles.hh"
#include "G4EmStandardPhysics.hh"
#include "nEXOPhysListEmLowEnergy.hh"
#include "nEXOPhysListHadron.hh"
#include "G4RegionStore.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleTable.hh"

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4UnitsTable.hh"
#include "G4LossTableManager.hh"

#include "HadronPhysicsQGSP_BERT.hh"
#include "HadronPhysicsQGSP_BIC.hh"
#include "HadronPhysicsQGSP_BERT_HP.hh"
#include "HadronPhysicsQGSP_BIC_HP.hh"

#include "G4EmExtraPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4QStoppingPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4DecayPhysics.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nEXOPhysicsList::nEXOPhysicsList() : G4VModularPhysicsList()
{
  paraWorldName.clear();

  G4LossTableManager::Instance();
  defaultCutValue = 1.*mm;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;

//  DetectorCuts = 1;
//  TargetCuts   = 1;

  pMessenger = new nEXOPhysicsListMessenger(this);

  SetVerboseLevel(1);

  //default physics
  particleList = new G4DecayPhysics();

  //default physics
  raddecayList = new G4RadioactiveDecayPhysics();

  // EM physics
  emPhysicsList = new G4EmStandardPhysics();
  
  // Had physics 
  hadPhysicsList = 0;
  nhadcomp = 0;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nEXOPhysicsList::~nEXOPhysicsList()
{
  delete pMessenger;
  delete raddecayList;
  delete emPhysicsList;
  if (hadPhysicsList) delete hadPhysicsList;
  if (nhadcomp > 0) {
    for(G4int i=0; i<nhadcomp; i++) {
      delete hadronPhys[i];
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOPhysicsList::ConstructParticle()
{
  particleList->ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOPhysicsList::ConstructProcess()
{
  AddTransportation();
  // em
  emPhysicsList->ConstructProcess();
  // decays
  particleList->ConstructProcess();
  raddecayList->ConstructProcess();
  // had
  if (nhadcomp > 0) {
    for(G4int i=0; i<nhadcomp; i++) {
      (hadronPhys[i])->ConstructProcess();
    }
  }
  if (hadPhysicsList) hadPhysicsList->ConstructProcess();
  G4cout << "### nEXOPhysicsList::ConstructProcess is done" << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOPhysicsList::SelectPhysicsList(const G4String& name)
{
  if (verboseLevel>1) {
    G4cout << "nEXOPhysicsList::SelectPhysicsList: <" << name << ">" << G4endl;
  }
  // default  Had physics
  if (name == "Hadron" && !hadPhysicsList) {
    hadPhysicsList = new nEXOPhysListHadron("hadron");
  } else if (name == "QGSP_BERT") {
    AddExtraBuilders(false);
    hadPhysicsList = new HadronPhysicsQGSP_BERT("std-hadron");
  } else if (name == "QGSP_BIC" && !hadPhysicsList) {
    AddExtraBuilders(false);
    hadPhysicsList = new HadronPhysicsQGSP_BIC("std-hadron");
  } else if (name == "QGSP_BERT_HP"  && !hadPhysicsList) {
    AddExtraBuilders(true);
    hadPhysicsList = new HadronPhysicsQGSP_BERT_HP("std-hadron");
  } else if (name == "QGSP_BIC_HP"  && !hadPhysicsList) {
    AddExtraBuilders(true);
    hadPhysicsList = new HadronPhysicsQGSP_BIC_HP("std-hadron");
  } else if (name == "LowEnergy_EM") {
      delete emPhysicsList;
      emPhysicsList = new nEXOPhysListEmLowEnergy("lowe-em");
  } else if (name == "Standard_EM") {
      delete emPhysicsList;
      emPhysicsList = new G4EmStandardPhysics();
  } else {
      G4cout << "nEXOPhysicsList WARNING wrong or unknown <" 
	     << name << "> Physics " << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOPhysicsList::AddExtraBuilders(G4bool flagHP)
{
  nhadcomp = 5;
  hadronPhys.push_back( new G4EmExtraPhysics("extra EM"));
  hadronPhys.push_back( new G4QStoppingPhysics("stopping",verboseLevel));
  hadronPhys.push_back( new G4IonBinaryCascadePhysics("ionBIC"));
  hadronPhys.push_back( new G4NeutronTrackingCut("Neutron tracking cut"));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOPhysicsList::SetCuts()
{
  SetCutValue(cutForGamma, "gamma");
  SetCutValue(cutForElectron, "e-");
  SetCutValue(cutForPositron, "e+");
  G4cout << "world cuts are set" << G4endl;
/*
  if( !TargetCuts ) SetTargetCut(cutForElectron);
  G4Region* region = (G4RegionStore::GetInstance())->GetRegion("Target");
  region->SetProductionCuts(TargetCuts);
  G4cout << "Target cuts are set" << G4endl;

  if( !DetectorCuts ) SetDetectorCut(cutForElectron);
  region = (G4RegionStore::GetInstance())->GetRegion("Detector");
  region->SetProductionCuts(DetectorCuts);
  G4cout << "Detector cuts are set" << G4endl;
*/
  if (verboseLevel>0) DumpCutValuesTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOPhysicsList::SetCutForGamma(G4double cut)
{
  cutForGamma = cut;
  SetParticleCuts(cutForGamma, G4Gamma::Gamma());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOPhysicsList::SetCutForElectron(G4double cut)
{
  cutForElectron = cut;
  SetParticleCuts(cutForElectron, G4Electron::Electron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOPhysicsList::SetCutForPositron(G4double cut)
{
  cutForPositron = cut;
  SetParticleCuts(cutForPositron, G4Positron::Positron());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
void nEXOPhysicsList::SetTargetCut(G4double cut)
{
  if( !TargetCuts ) TargetCuts = new G4ProductionCuts();

  TargetCuts->SetProductionCut(cut, idxG4GammaCut);
  TargetCuts->SetProductionCut(cut, idxG4ElectronCut);
  TargetCuts->SetProductionCut(cut, idxG4PositronCut);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOPhysicsList::SetDetectorCut(G4double cut)
{
  if( !DetectorCuts ) DetectorCuts = new G4ProductionCuts();

  DetectorCuts->SetProductionCut(cut, idxG4GammaCut);
  DetectorCuts->SetProductionCut(cut, idxG4ElectronCut);
  DetectorCuts->SetProductionCut(cut, idxG4PositronCut);
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
