#include "G4RunManager.hh"
#include "G4UImanager.hh"
#ifdef G4UI_USE_GAG
#include "G4UIGAG.hh"
#endif
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif 

#include "nEXODetectorConstruction.hh"

//#include "nEXOPhysicsList.hh"
#include "EXOPhysicsList.hh"

#include "nEXOEventAction.hh"
#include "nEXORunAction.hh"
#include "nEXOSteppingAction.hh"
#include "nEXOPrimaryGeneratorAction.hh"


#include "Randomize.hh"

//#include "nEXOParallelDetectorConstruction.hh"

#include "G4GeometrySampler.hh"
#include "G4IStore.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv)
{
  //random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
  G4long seed = (G4int)argv[1];
//time(0);
  CLHEP::HepRandom::setTheSeed(seed);
  CLHEP::HepRandom::showEngineStatus();
  G4cout << "Seed = " << CLHEP::HepRandom::getTheSeed() << G4endl;

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // set mandatory initialization classes

  nEXODetectorConstruction* Detector = new nEXODetectorConstruction;
  runManager->SetUserInitialization(Detector);

  //****************Define Parallel World and Register****************//
  //   G4String parallelName("ParallelWorld");
  //   nEXOParallelDetectorConstruction *pdet = new nEXOParallelDetectorConstruction(parallelName);
  //   Detector->RegisterParallelWorld(pdet);
  


  //****************Physics
  //    nEXOPhysicsList* physlist = new nEXOPhysicsList;
  //****************Add for Parallel World****************//

  runManager->SetUserInitialization(new EXOPhysicsList);

  // Set Mandatory User Action Classes
  G4VUserPrimaryGeneratorAction* gen_action = new nEXOPrimaryGeneratorAction();
  runManager->SetUserAction(gen_action);

  nEXORunAction* run_action = new nEXORunAction;
      runManager->SetUserAction(run_action); 

  nEXOEventAction* event_action = new nEXOEventAction(run_action);
  runManager->SetUserAction(event_action);

  G4UserSteppingAction* stepping_action = new nEXOSteppingAction(run_action, event_action);
  runManager->SetUserAction(stepping_action); 

  //****************Initialize Run Manager****************//
  runManager->Initialize();

    
  G4UIsession* session = 0;

  if (argc==1)  // Define UI session for interactive mode.
    {
#ifdef G4UI_USE_XM
      session = new G4UIXm(argc, argv);
#else
#ifdef G4UI_USE_TCSH
      session = new G4UIterminal(new G4UItcsh);
#else
      session = new G4UIterminal();
#endif
#endif
    }

#ifdef G4VIS_USE
  // visualization manager
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // Initialize G4 kernel
  // do this at run time so the geometry/physics can be changed

  //get the pointer to the User Interface manager
  G4UImanager* UI = G4UImanager::GetUIpointer();
  if (session)  // Define UI session for interactive mode
    {
      session->SessionStart();
      delete session;
    }
  else     // Batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UI->ApplyCommand(command+fileName);
    }

  //job termination
#ifdef G4VIS_USE
  delete visManager;
#endif


  delete runManager;

  return 0;
}
