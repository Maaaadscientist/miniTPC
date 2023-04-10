
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nEXOPhysicsList_h
#define nEXOPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"
#include <vector>

class G4VPhysicsConstructor;
class nEXOPhysicsListMessenger;
class G4ProductionCuts;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nEXOPhysicsList: public G4VModularPhysicsList
{
public:
  nEXOPhysicsList();
  virtual ~nEXOPhysicsList();

  void AddParallelWorldName(G4String& pname)
       {paraWorldName.push_back(pname);}

  void ConstructParticle();

  void SetCuts();
  void SetCutForGamma(G4double);
  void SetCutForElectron(G4double);
  void SetCutForPositron(G4double);

  void SelectPhysicsList(const G4String& name);
  void ConstructProcess();

  void SetTargetCut(G4double val);
  void SetDetectorCut(G4double val);

private:

  void AddExtraBuilders(G4bool flagHP);

  // hide assignment operator
  nEXOPhysicsList & operator=(const nEXOPhysicsList &right);
  nEXOPhysicsList(const nEXOPhysicsList&);

  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;

  G4VPhysicsConstructor*  emPhysicsList;
  G4VPhysicsConstructor*  raddecayList;
  G4VPhysicsConstructor*  particleList;
  G4VPhysicsConstructor*  hadPhysicsList;

  std::vector<G4VPhysicsConstructor*>  hadronPhys;
  G4int nhadcomp;  

  nEXOPhysicsListMessenger* pMessenger;
//  G4ProductionCuts* DetectorCuts;
//  G4ProductionCuts* TargetCuts;

  std::vector<G4String> paraWorldName;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

