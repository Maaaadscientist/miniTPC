#include "G4ios.hh"

#include "nEXOSteppingAction.hh"
#include "nEXOEventAction.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4SteppingManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOSteppingAction::nEXOSteppingAction(nEXORunAction * run, nEXOEventAction * event)
{
  runAction = run;
  eventAction = event;  

 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOSteppingAction::~nEXOSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOSteppingAction::UserSteppingAction(const G4Step* fStep) 
{
  
  const G4Event * event = eventAction->GetEvent();
  G4int event_id = event->GetEventID();

  /*  
  G4cout << "I am a: " << fStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl;
  G4cout << "My event number is: "  << eventAction->GetEvent()->GetEventID() << G4endl;
  G4cout << "My Track ID is: " << fStep->GetTrack()->GetTrackID() << G4endl;
  G4cout << "My energy is: " << fStep->GetTrack()->GetTotalEnergy() << G4endl;
  G4cout << "My parent id is: " << fStep->GetTrack()->GetParentID() << G4endl;
  G4cout << "***********************" << G4endl;
  */


  G4StepPoint * PreStepPoint = fStep->GetPreStepPoint();
  const G4VPhysicalVolume * PreStepVolume = PreStepPoint->GetPhysicalVolume();
  const G4String PreVolName = PreStepVolume->GetName();

  G4StepPoint * PostStepPoint = fStep->GetPostStepPoint();   
  const G4VPhysicalVolume * PostStepVolume = PostStepPoint->GetPhysicalVolume();
  const G4String PostVolName = PostStepVolume->GetName();

  // Kill of particles that reach the InnerCryostat
  if(PostVolName == "HDPETank")
    {
      fStep->GetTrack()->SetTrackStatus(fStopAndKill);      
    }

  // Get Total Energy Deposit
  G4double Edep = fStep->GetTotalEnergyDeposit();
  if(Edep > 0 && PostVolName == "ActiveLXe"){
  eventAction->SetIsEnergyDeposit(1);
  eventAction->SetElementEnergyDeposit(eventAction->GetNumDeposits(),Edep);
  eventAction->AddToTotalEventEnergy(Edep);
  /*  
  G4cout << "Summed Energy Deposit = " << eventAction->GetTotalEventEnergy() << G4endl;
  G4cout << "NumDeposits = " << eventAction->GetNumDeposits() << G4endl;
    G4cout << "PreVolName = " << PreVolName << G4endl;
    G4cout << "PostVolName = " << PostVolName << G4endl;
  */
  
  //  if (Edep > 0 && PostVolName == "LXe" && fStep->GetTrack()->GetDefinition()->GetParticleName() == "gamma")
  //  {
      //      G4cout << "*\n*\n*\n*\n*\n*\n Flux Detected *\n*\n*\n*\n*\n*\n"<< G4endl;

    G4double StepLength = fStep->GetStepLength();
  G4double PreStepTotalEnergy = PreStepPoint->GetTotalEnergy();
  
  G4double PostStepTotalEnergy = PostStepPoint->GetTotalEnergy();    
  
  G4Track * StepTrack = fStep->GetTrack();
  G4double LocalTime = StepTrack->GetLocalTime();
  G4double GlobalTime = StepTrack->GetGlobalTime();
  G4int ParentID = StepTrack->GetParentID();
  G4int TrackID = StepTrack->GetTrackID();
  eventAction->SetElementTrackNumber(eventAction->GetNumDeposits(),TrackID);


  //  G4double EnergyDiff = PreStepTotalEnergy - PostStepTotalEnergy;

  
  G4ThreeVector Position = StepTrack->GetPosition();
  double Xpos = Position.getX();
  eventAction->SetElementXpos(eventAction->GetNumDeposits(),Xpos);
  double Ypos = Position.getY();
  eventAction->SetElementYpos(eventAction->GetNumDeposits(),Ypos);
  double Zpos = Position.getZ();
  eventAction->SetElementZpos(eventAction->GetNumDeposits(),Zpos);
  
  /*
  G4cout << "I am a " << fStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl;
  G4cout << "EventID = " << event_id << G4endl;
  G4cout << "TrackID = " << TrackID << G4endl;
  G4cout << "Parent Track ID = " << ParentID << G4endl;
  G4cout << "Energy = " << PostStepTotalEnergy << G4endl;
  G4cout << "EnergyDeposit = " << Edep << G4endl;
  G4cout << "Step Length = " << StepLength << G4endl;
  G4cout << "Global Time = " << GlobalTime << G4endl;
  G4cout << "Local Time = " << LocalTime << G4endl;

  G4cout << "*********************************************" << G4endl;
  */

  eventAction->AddToNumDeposits();
  }



  //     runAction->FillTree(event_id, TrackID,PostStepTotalEnergy, Xpos, Ypos, Zpos, XM, YM, ZM);  

  //    }
  /*  
  G4Track* fTrack = fStep->GetTrack();
  G4String particleName = fTrack->GetDefinition()->GetParticleName();
  G4String material = fTrack->GetMaterial()->GetName();
  G4int trackid = fTrack->GetTrackID();
  G4int parentid;
  */


// debug


/*
  G4cout << "*****I am here:  " << fTrack->GetVolume()->GetName() << "(" << material << ")" << " ******" << G4endl;
  G4cout << "I am a:  " << particleName << G4endl;
  G4cout << "This is the total energy:   " << fTrack->GetTotalEnergy() << G4endl;

  G4cout << "Event ID = " << event_id << G4endl;
  G4cout << "Track ID:   " << trackid << G4endl;
  G4cout << "Parent Track ID:  " << fTrack->GetParentID() << G4endl;
  G4cout << "Energy deposited:  " << fStep->GetTotalEnergyDeposit() << G4endl;
*/

/*
  G4int StepNo = fTrack->GetCurrentStepNumber();
  if(StepNo >= 10000) fTrack->SetTrackStatus(fStopAndKill);
*/
//  G4cout << "Current step no:  " << StepNo << G4endl;
//  G4cout << " " << G4endl;

//#ifndef COLLECT
//#define COLLECT
//#endif
/*
  parentid = fTrack->GetParentID();
  if (particleName == "gamma") {
     if (StepNo != 1) {
        if (fTrack->GetVolume()->GetName() == "ActiveXe") {
           if (fStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() != "ActiveXe") {
              parentid = fTrack->GetTrackID();
           }  
         }
     }
     }  */


//   G4cout << "parentid =  " << parentid << G4endl; 
//#ifdef COLLECT

/*
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
	  nEXOAnalysisManager::getInstance()->AddEnergy(edep,0., weight,time,parentid,trackid);
	   //           G4cout << "Total Energy Deposited in Active LXe:   " << edep << G4endl;
        }
	// Count gammas in Inner Water Shield
	if(fTrack->GetVolume()->GetName() == "OuterWater"){
	  nEXOAnalysisManager::getInstance()->AddEnergy(0.,edep,weight,time,parentid,trackid);
	}
    }
//#endif 
*/

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....


