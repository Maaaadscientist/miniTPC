#include "G4ios.hh"

#include "nEXOSteppingAction.hh"
#include "nEXOAnalysisManager.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SteppingManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOSteppingAction::nEXOSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOSteppingAction::~nEXOSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOSteppingAction::UserSteppingAction(const G4Step* fStep) 
{
  G4Track* fTrack = fStep->GetTrack();
  G4String particleName = fTrack->GetDefinition()->GetParticleName();
  G4String material = fTrack->GetMaterial()->GetName();
  G4int trackid = fTrack->GetTrackID();
  G4int parentid;
/*// debug
  G4cout << "*****I am here:  " << fTrack->GetVolume()->GetName() << "(" << material << ")" << " ******" << G4endl;
  G4cout << "I am a:  " << particleName << G4endl;
  G4cout << "This is the total energy:   " << fTrack->GetTotalEnergy() << G4endl;
  G4cout << "Track ID:   " << trackid << G4endl;
  G4cout << "Parent Track ID:  " << fTrack->GetParentID() << G4endl;
  G4cout << "Energy deposited:  " << fStep->GetTotalEnergyDeposit() << G4endl;
*/
  G4int StepNo = fTrack->GetCurrentStepNumber();
  if(StepNo >= 10000) fTrack->SetTrackStatus(fStopAndKill);

//  G4cout << "Current step no:  " << StepNo << G4endl;
//  G4cout << " " << G4endl;

//#ifndef COLLECT
//#define COLLECT
//#endif

  parentid = fTrack->GetParentID();
  if (particleName == "gamma") {
     if (StepNo != 1) {
        if (fTrack->GetVolume()->GetName() == "ActiveXe") {
           if (fStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() != "ActiveXe") {
              parentid = fTrack->GetTrackID();
           }  
         }
     }
   }  
//   G4cout << "parentid =  " << parentid << G4endl; 
//#ifdef COLLECT
  if (StepNo == 1) {
      // get the analysis manager
      nEXOAnalysisManager* analysis = nEXOAnalysisManager::getInstance();
    }
  // energy deposition
  if (fTrack->GetTrackID() != 1 ) {
	G4double time = fStep->GetPreStepPoint()->GetGlobalTime() ;
//	G4double time = fStep->GetPostStepPoint()->GetLocalTime() ;
//        G4cout << "Step time =  " << time/second << G4endl;
	G4double edep = fStep->GetTotalEnergyDeposit();
	G4ThreeVector position = fStep->GetPostStepPoint()->GetPosition();
        G4double weight = 1;
// Get energy deposition for everything that goes in the LXe
	if (material == "LiquidXe2") {
	   nEXOAnalysisManager::getInstance()->AddEnergy(edep,weight,time,parentid,trackid);
	   //           G4cout << "Total Energy Deposited in Active LXe:   " << edep << G4endl;
        }
    }
//#endif 
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


