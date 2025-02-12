//////////////////////////////////////////
// nEXOAnalysis.hh //
// Analysis manager to save event info  //
// This class is designed as a singleton//
//////////////////////////////////////////

#ifndef nEXOAnalysis_h
#define nEXOAnalysis_h 1

#include "globals.hh"

#include "G4Run.hh"
#include "G4Event.hh"
#include "G4Step.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SteppingManager.hh"
#include "G4OpticalPhoton.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4RunManager.hh"
#include "G4Cons.hh"
#include "G4Tubs.hh"

#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"

#include "TROOT.h"
#include "TObject.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TTree.h"
#include "TBranch.h"
#include "TChain.h"
#include "TTimeStamp.h"
#include "TVector3.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoCone.h"
#include "TGeoTube.h"
#include "TParameter.h"

#include "Geant4GM/volumes/Factory.h"
#include "RootGM/volumes/Factory.h"
#include "TGeoManager.h"
#include "G4RegionStore.hh"

#include "nEXOG4ThermalElectron.hh"
#include <vector>

class nEXOAnalysis
{
public:
  static nEXOAnalysis* GetInstance(){
    if(nEXOAnalysis::fInstance == NULL) nEXOAnalysis::fInstance = new nEXOAnalysis();
    return nEXOAnalysis::fInstance;
  }
  
  virtual ~nEXOAnalysis();
  
  void SetROOTFileName(G4String& name){fRootFileName = name;}
  void SetROOTTreeName(G4String& name){fRootTreeName = name;}   
  void SetPropagateOP(G4int flag) { fPropagateOP = flag; }
  void SetPropagateTE(G4int flag) { fPropagateTE = flag; }
  void SetSaveOP(G4int flag) { fSaveOP = flag; }
  void SetSaveTE(G4int flag) { fSaveTE = flag; }

  void SetSaveOnlyEventsWithDeposits(G4bool saveOnly){ fSaveOnlyEventsWithDeposits = saveOnly; }
  
  G4int GetPropagateOP() { return fPropagateOP; }
  G4int GetPropagateTE() { return fPropagateTE; }
  G4int GetSaveOP() { return fSaveOP; }
  G4int GetSaveTE() { return fSaveTE; }

  //void WriteGeometry(G4VPhysicalVolume* world);
  void WriteGeometry();
  void SetGeometry(G4VPhysicalVolume* world) { fWorld = world; }
  G4VPhysicalVolume* GetGeometry() { return fWorld; }

  void PrepareNewRun(const G4Run* g4Run);
  void EndOfRun(const G4Run* g4Run);

  void PrepareNewEvent(const G4Event* g4Event);
  void EndOfEvent(const G4Event* g4Event);

  void PreUserTrackingAction(const G4Track* g4Track);
  void PostUserTrackingAction(const G4Track* g4Track);
  
  void SteppingAction(const G4Step* g4Step);

  void GetTE(int i, G4double& E, G4double& X, G4double& Y, G4double& Z);
  void AddThermalElectron(G4ThreeVector pos);
  void AddInitNOP() { fInitNOP++;}

private:
  nEXOAnalysis();
  static nEXOAnalysis* fInstance;

  void ResetTreeVariables();
  void SetTreeBranches();
  
  G4String fRootFileName;
  G4String fRootTreeName;
  TFile* fRootFile; 
  TTree* fRootTree;

private:

  G4int fEventNumber;
  G4double fGenX;
  G4double fGenY;
  G4double fGenZ;
  G4double fTotalEventEnergy;
  G4int fNumDeposits;
  std::vector<G4double> fLengthDeposit;
  std::vector<G4double> fEnergyDeposit;
  std::vector<G4double> fPreEnergyDeposit;
  std::vector<G4double> fPostEnergyDeposit;
  std::vector<G4int> fTrackNumber;
  std::vector<G4double> fXpos;
  std::vector<G4double> fYpos;
  std::vector<G4double> fZpos;
  std::vector<G4double> fTglob;
  std::vector<G4double> fTloc;
  
  G4int fNOP;
  G4int fInitNOP;
  G4int fInitCherenkovOP;
  std::vector<G4double> fOPEnergy;
  std::vector<G4int> fSiPMID;
  std::vector<G4double> fOPTime;
  std::vector<G4int> fOPType;
  std::vector<G4int> fOPStopVolume;
  std::vector<G4double> fOPX;
  std::vector<G4double> fOPY;
  std::vector<G4double> fOPZ;
  G4int fNTE;
  std::vector<G4double> fTEEnergy;
  std::vector<G4double> fTEX;
  std::vector<G4double> fTEY;
  std::vector<G4double> fTEZ;

  G4OpBoundaryProcess* fBoundary;
  G4VPhysicalVolume* fWorld;

  G4int fPropagateOP;
  G4int fPropagateTE;
  G4int fSaveOP;
  G4int fSaveTE;

  G4bool fSaveOnlyEventsWithDeposits;
  
};

class nEXOAnalysisMessenger : public G4UImessenger
{
public:
  nEXOAnalysisMessenger(nEXOAnalysis* analysis);
  virtual ~nEXOAnalysisMessenger();

  virtual void SetNewValue(G4UIcommand* cmd, G4String val);

private:
  nEXOAnalysis* fAnalysis;
  G4UIdirectory* fDirectory;

  G4UIcmdWithAString* fRootFileNameCmd;
  G4UIcmdWithAString* fRootTreeNameCmd;

  G4UIcmdWithAnInteger* fPrintVolumesCmd;
  
  G4UIcmdWithoutParameter* fPrintVolNames;
  G4UIcmdWithAString* fPrintVolTranslationCmd;

  G4UIcmdWithAnInteger* fPropagateOpCmd;
  G4UIcmdWithAnInteger* fPropagateTeCmd;
  G4UIcmdWithAnInteger* fSaveOpCmd;
  G4UIcmdWithAnInteger* fSaveTeCmd;
  G4UIcmdWithABool* fSaveOnlyEventsWithDepositsCmd;
};

#endif
