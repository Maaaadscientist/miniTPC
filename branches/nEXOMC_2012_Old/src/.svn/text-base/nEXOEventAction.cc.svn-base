// CHANGE HISTORY
// --------------
#include "G4ios.hh"
#include "nEXOEventActionMessenger.hh"
#include "nEXOEventAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4UImanager.hh"
#include "G4UnitsTable.hh"
#include "nEXOAnalysisManager.hh"

extern G4bool drawEvent;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOEventAction::nEXOEventAction()
  : drawFlag("all")
{
  eventMessenger = new nEXOEventActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOEventAction::~nEXOEventAction()
{
  delete eventMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOEventAction::BeginOfEventAction(const G4Event* )
{
  nEXOAnalysisManager::getInstance()->BeginOfEvent();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOEventAction::EndOfEventAction(const G4Event* evt)
{
  //analysis
  nEXOAnalysisManager::getInstance()->EndOfEvent();
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

































