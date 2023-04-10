#include "nEXORunActionMessenger.hh"
#include "nEXORunAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

nEXORunActionMessenger::nEXORunActionMessenger(nEXORunAction* manager)
  :runAction(manager)
{
  rootfileDir = new G4UIdirectory("/rootfile/");
  rootfileDir->SetGuidance("Root file control");

  fileCmd = new G4UIcmdWithAString("/rootfile/fileName", this);
  fileCmd->SetGuidance("Set name for output root file");
  //  fileCmd->AvailableForStates(G4State_PreInt, G4State_Idle);  // do I need this?

}

nEXORunActionMessenger::~nEXORunActionMessenger()
{
  delete rootfileDir;
  delete fileCmd;
}

void nEXORunActionMessenger::SetNewValue(G4UIcommand* command, G4String newValues)
{
  if (command == fileCmd)
    runAction->SetOutputFileName(newValues);

}
