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

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef nEXORunAction_h
#define nEXORunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <TObject.h>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"

class TTree;
class TFile;
class TChain;

class nEXORunActionMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

class G4Run;

class nEXORunAction : public G4UserRunAction
{
  public:
    nEXORunAction();
   ~nEXORunAction();

  public:
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);

  TTree* GetTree() {return rootTree; };
  TFile* GetTFile() {return rootFile; };
  
  void SetOutputFileName(G4String val) {ROOTFileName = val;}
  
  //  void FillTree(G4int eventNum, G4int numDeposits, G4double totalEventEnergy, G4double energyDeposit[100], G4int trackNum[100], G4double xpos[100], G4double ypos[100], G4double zpos[100]);

  void FillTree(G4int eventNum, G4int numDeposits, G4double totalEventEnergy, G4double energyDeposit[200], G4int trackNum[200], G4double xpos[200], G4double ypos[200], G4double zpos[200]);
  
  G4double GetXposElement(G4int n){return Xpos[n];}
  void SetXposElement(G4int n, G4double xpos){Xpos[n] = xpos;}
  G4double GetYposElement(G4int n){return Ypos[n];}
  void SetYposElement(G4int n, G4double ypos){Ypos[n] = ypos;}
  G4double GetZposElement(G4int n){return Zpos[n];}
  void SetZposElement(G4int n, G4double zpos){Zpos[n] = zpos;}
  
  private:
  TFile *rootFile; // ROOT File
  TTree *rootTree; // ROOT tree
  TFile *InputFile;  // ROOT File to read Primary Events from
  TChain *InputChain;


  G4int EventNumber;
  G4double TotalEventEnergy;
  G4int NumDeposits;
  G4double * EnergyDepositPoint;
  G4int * TrackNumberPoint;
  G4double * XposPoint;
  G4double * YposPoint;
  G4double * ZposPoint;
  G4double EnergyDeposit[200];
  G4int TrackNumber[200];
  G4double Xpos[200];
  G4double Ypos[200];
  G4double Zpos[200];
  G4String VolumeName;
  G4double StepLength;


  G4double ReadTotalEnergy;
  G4double ReadXpos;
  G4double ReadYpos;
  G4double ReadZpos;
  G4double ReadXmomentum;
  G4double ReadYmomentum;
  G4double ReadZmomentum;
  
  G4String ROOTFileName;
  G4String ReadFileName;

  nEXORunActionMessenger* messenger;

};

#endif

