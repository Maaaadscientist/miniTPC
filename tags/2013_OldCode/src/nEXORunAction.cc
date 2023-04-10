#include "nEXORunAction.hh"
#include "nEXORunActionMessenger.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"

#include <TObject.h>
#include <TObjString.h>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXORunAction::nEXORunAction():
  rootFile(0),rootTree(0)
{
  ROOTFileName = "output";

  messenger = new nEXORunActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXORunAction::~nEXORunAction()
{
  delete messenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXORunAction::BeginOfRunAction(const G4Run* aRun)
{
  // Creation of the analysis manager
 
  G4int RunN = aRun->GetRunID();
  if ( RunN % 1000 == 0 ) 
    G4cout << "### Run : " << RunN << G4endl;

  G4String id = ROOTFileName + ".root";
  rootFile = new TFile(id, "RECREATE");

    rootTree = new TTree("tree", "Tree of Flux Info");

    EventNumber = 0;
    TotalEventEnergy = 0;
    NumDeposits = 0;
    
    for (G4int i = 0; i < 200; i++){EnergyDeposit[i] = 0;}
    for (G4int i = 0; i < 200; i++){TrackNumber[i] = 0;}
    for (G4int i = 0; i < 200; i++){Xpos[i] = 0;}
    for (G4int i = 0; i < 200; i++){Ypos[i] = 0;}
    for (G4int i = 0; i < 200; i++){Zpos[i] = 0;}
    
    rootTree->Branch("EventNumber", &EventNumber, "EventNumber/I");
    rootTree->Branch("TotalEventEnergy", &TotalEventEnergy, "TotalEventEnergy/D");
    rootTree->Branch("NumDeposits", &NumDeposits, "NumDeposits/I");
    rootTree->Branch("EnergyDeposit", &EnergyDeposit, "EnergyDeposit[200]/D");
    rootTree->Branch("TrackNumber", &TrackNumber, "TrackNumber[200]/I");
    rootTree->Branch("Xpos", &Xpos, "Xpos[200]/D");
    rootTree->Branch("Ypos", &Ypos, "Ypos[200]/D");
    rootTree->Branch("Zpos", &Zpos, "Zpos[200]/D"); 
    
#ifdef G4VIS_USE
  if (G4VVisManager::GetConcreteInstance())
    {
      G4UImanager* UI = G4UImanager::GetUIpointer(); 
      UI->ApplyCommand("/vis/clear/view");
      UI->ApplyCommand("/vis/draw/current");
    } 
#endif
}

void nEXORunAction::FillTree(G4int eventNum, G4int numDeposits, G4double totalEventEnergy, G4double * energyDeposit, G4int * trackNum, G4double * xpos, G4double * ypos, G4double * zpos){

  // Try setting the variables with a 

  EventNumber = eventNum;
  NumDeposits = numDeposits;
    if (NumDeposits > 200){
    G4cout << "NumDeposits = " << NumDeposits << G4endl;
    }
  TotalEventEnergy = totalEventEnergy;
  EnergyDepositPoint = energyDeposit;
  TrackNumberPoint = trackNum;

  XposPoint = xpos;
  YposPoint = ypos;
  ZposPoint = zpos;
  
  for (G4int i = 0; i < 200; i++)
    {
      EnergyDeposit[i] = EnergyDepositPoint[i];
      TrackNumber[i] = TrackNumberPoint[i];
      //G4cout << "XposPoint[" << i << "] = " << XposPoint[i] << G4endl;
      Xpos[i] = XposPoint[i];
      //      G4cout << "RunArrayXpos[" << i << "] = " << GetXposElement(i) << G4endl;
      Ypos[i] = YposPoint[i];
      Zpos[i] = ZposPoint[i];

      }

  /*  for (G4int i = 0; i < 1000; i++)
    {
      G4cout << "RunArrayXpos[" << i << "] = " << GetXposElement(i) << G4endl;

      }
      G4cout << "TotalRunArray = " << Xpos << G4endl;*/


  rootTree->Fill();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXORunAction::EndOfRunAction(const G4Run* )
{
  G4cout << "writing tree..." << G4endl;
  GetTree()->Write();
  G4cout << "Closing file..." << G4endl;
  GetTFile()->Close();
  G4cout << "done..." << G4endl;

 
#ifdef G4VIS_USE
  if (G4VVisManager::GetConcreteInstance())
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/show/view");
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....




