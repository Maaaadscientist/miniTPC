//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

//
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#ifndef nEXOEventAction_h
#define nEXOEventAction_h 1

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "globals.hh"
#include "nEXORunAction.hh"

class nEXOEventActionMessenger;
class nEXORunAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class nEXOEventAction : public G4UserEventAction
{
  public:
    nEXOEventAction(nEXORunAction* run);
   ~nEXOEventAction();

  public:
    void BeginOfEventAction(const G4Event* anEvent);
    void EndOfEventAction(const G4Event* anEvent);
    void AddToTotalEventEnergy(G4double Dep){TotalEventEnergy = TotalEventEnergy + Dep;}
  
  G4double GetTotalEventEnergy(){return TotalEventEnergy;}
  void AddToNumDeposits(){NumDeposits = NumDeposits + 1;}
  G4int GetNumDeposits(){return NumDeposits;}
  
   void SetElementEnergyDeposit(G4int n, G4double energyDep){EnergyDeposit[n] = energyDep;}
  void SetElementTrackNumber(G4int n, G4int trackNumber){TrackNumber[n] = trackNumber;}
  void SetElementXpos(G4int n, G4double xpos){Xpos[n] = xpos;}
  void SetElementYpos(G4int n, G4double ypos){Ypos[n] = ypos;}
  void SetElementZpos(G4int n, G4double zpos){Zpos[n] = zpos;}
 
  G4double * GetArrayEnergyDeposit(){return EnergyDeposit;}
  G4int * GetArrayTrackNumber(){return TrackNumber;}
  G4double * GetArrayXpos(){return Xpos;}
  G4double * GetArrayYpos(){return Ypos;}
  G4double * GetArrayZpos(){return Zpos;}

  G4int GetIsEnergyDeposit(){return IsEnergyDeposit;}
  void SetIsEnergyDeposit(G4int value){IsEnergyDeposit = value;}

  const G4Event * GetEvent() {return Event;}
    
    void SetDrawFlag(G4String val)  {drawFlag = val;};
    
  private:
    G4String drawFlag;                         // control the drawing of event
    nEXOEventActionMessenger*  eventMessenger;
  const G4Event * Event;
  G4double TotalEventEnergy;
  G4int NumDeposits; 
  G4double  EnergyDeposit[200];
  G4int  TrackNumber[200];
  G4double  Xpos[200];
  G4double  Ypos[200];
  G4double  Zpos[200];
  
  nEXORunAction * runAction;
  G4int IsEnergyDeposit;
}; 

#endif

    




