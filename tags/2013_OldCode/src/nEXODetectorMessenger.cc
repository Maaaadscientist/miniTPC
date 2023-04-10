
// ******************************************************************
// * nEXODetectorMessenger                                           *
// ******************************************************************

#include "nEXODetectorMessenger.hh"

#include "nEXODetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nEXODetectorMessenger::nEXODetectorMessenger(nEXODetectorConstruction* myDet)
:myDetector(myDet)
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

nEXODetectorMessenger::~nEXODetectorMessenger()
{
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXODetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
