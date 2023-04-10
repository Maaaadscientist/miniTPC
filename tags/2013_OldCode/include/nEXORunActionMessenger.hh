#ifndef nEXORunActionMessenger_h
#define nEXORunActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class nEXORunAction;
class G4UIdirectory;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nEXORunActionMessenger: public G4UImessenger
{
public:
  nEXORunActionMessenger(nEXORunAction *);
  ~nEXORunActionMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  nEXORunAction*          runAction;
  
  G4UIdirectory*         rootfileDir;
  G4UIcmdWithAString*    fileCmd;

};








#endif
