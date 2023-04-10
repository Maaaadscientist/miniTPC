#include "nEXORunAction.hh"
#include "nEXOAnalysisManager.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXORunAction::nEXORunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXORunAction::~nEXORunAction()
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXORunAction::BeginOfRunAction(const G4Run* aRun)
{
  // Creation of the analysis manager
  nEXOAnalysisManager* analysis = nEXOAnalysisManager::getInstance();
  analysis->BeginOfRun();
 
  G4int RunN = aRun->GetRunID();
  if ( RunN % 1000 == 0 ) 
    G4cout << "### Run : " << RunN << G4endl;

#ifdef G4VIS_USE
  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer(); 
      UI->ApplyCommand("/vis/clear/view");
      UI->ApplyCommand("/vis/draw/current");
    } 
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXORunAction::EndOfRunAction(const G4Run* )
{
  // Get the analysis manager
  nEXOAnalysisManager* analysis = nEXOAnalysisManager::getInstance();
  analysis->EndOfRun();
 
#ifdef G4VIS_USE
  if (G4VVisManager::GetConcreteInstance())
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/show/view");
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....




