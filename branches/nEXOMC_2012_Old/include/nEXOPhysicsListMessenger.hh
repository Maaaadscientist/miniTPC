
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef nEXOPhysicsListMessenger_h
#define nEXOPhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class nEXOPhysicsList;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nEXOPhysicsListMessenger: public G4UImessenger
{
public:
  
  nEXOPhysicsListMessenger(nEXOPhysicsList* );
  ~nEXOPhysicsListMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  
  nEXOPhysicsList* pPhysicsList;

  G4UIdirectory*             physDir;  
  G4UIcmdWithADoubleAndUnit* gammaCutCmd;
  G4UIcmdWithADoubleAndUnit* electCutCmd;
  G4UIcmdWithADoubleAndUnit* protoCutCmd;    
  G4UIcmdWithADoubleAndUnit* allCutCmd;    
//  G4UIcmdWithADoubleAndUnit* mCutCmd;
//  G4UIcmdWithADoubleAndUnit* eCutCmd;
  G4UIcmdWithAString*        pListCmd;
    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

