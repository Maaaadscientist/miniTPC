// CHANGE HISTORY
// --------------
#include "G4ios.hh"
//#include "nEXOEventActionMessenger.hh"
#include "nEXOEventAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"

extern G4bool drawEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOEventAction::nEXOEventAction(nEXORunAction * run)
  : drawFlag("all")
{
  runAction = run;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOEventAction::~nEXOEventAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOEventAction::BeginOfEventAction(const G4Event* evt)
{
  SetIsEnergyDeposit(0);

  Event = evt;
  TotalEventEnergy = 0;
  NumDeposits = 0;
  
  for (G4int i = 0; i < 200; i++)
    {
      SetElementEnergyDeposit(i,0);
      SetElementTrackNumber(i,0);
      SetElementXpos(i,0);
      SetElementYpos(i,0);
      SetElementZpos(i,0);
    }
    
  /*  for (G4int i = 0; i < 1000; i++)
    {
      G4cout << "BeforeArrayXpos[" << i << "] = " << GetArrayXpos()[i] << G4endl;
    }
  */
}

//....oooOO0OOooo........ooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOEventAction::EndOfEventAction(const G4Event* evt)
{
  if (GetIsEnergyDeposit()){
    runAction->FillTree(evt->GetEventID(), GetNumDeposits(), GetTotalEventEnergy(), GetArrayEnergyDeposit(), GetArrayTrackNumber(), GetArrayXpos(), GetArrayYpos(), GetArrayZpos());
  }
  //  G4cout << "*\n*\n*\n*\nTotal Energy Deposited for event " << Event->GetEventID() << " = " << GetTotalEventEnergy() << " NumDeposits = " << GetNumDeposits() <<"\n*\n*\n*\n" << G4endl;

  /*  for (G4int i = 0; i < 100; i++)
    {
      G4cout << "AfterArrayXpos[" << i << "] = " << GetArrayXpos()[i] << G4endl;
      }*/


  // visualisation
#ifdef G4VIS_USE
  G4int event_id       = evt->GetEventID();
  if (event_id < 100 && G4VVisManager::GetConcreteInstance()) {
    G4TrajectoryContainer * trajectoryContainer = evt->GetTrajectoryContainer();
    G4int n_trajectories = 0;
    if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();
    for (G4int i=0; i<n_trajectories; i++) {
      G4Trajectory* trj = (G4Trajectory *)
        ((*(evt->GetTrajectoryContainer()))[i]);
      if (drawFlag == "all") {
        trj->DrawTrajectory(0);
      } else if (drawFlag == "charged" && trj->GetCharge() != 0.) {
        trj->DrawTrajectory(0);
      }
    }
  }
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

































