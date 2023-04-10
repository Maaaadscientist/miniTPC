#include "nEXOAnalysis.hh"
#include "G4SystemOfUnits.hh"
#include "TDirectory.h"

nEXOAnalysisMessenger::nEXOAnalysisMessenger(nEXOAnalysis* analysis)
{
  fAnalysis = analysis;
  
  fDirectory = new G4UIdirectory("/analysis/");
  fDirectory->SetGuidance("Control of the analysis output (mainly ROOT file options).");

  fRootFileNameCmd = new G4UIcmdWithAString("/analysis/setOutputROOTFileName",this);
  fRootFileNameCmd->SetGuidance("Set the name for output ROOT file.");
  fRootFileNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
  
  fRootTreeNameCmd = new G4UIcmdWithAString("/analysis/setOutputROOTTreeName",this);
  fRootTreeNameCmd->SetGuidance("Set the name for output ROOT tree [default = tree].");
  fRootTreeNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
/*
  fPrintVolNames = new G4UIcmdWithoutParameter("/analysis/printLogicVolumeNames",this);
  fPrintVolNames->SetGuidance("Print the logic volume names with a physical volume associated to nEXOSimplePhysVolManager");
  fPrintVolNames->AvailableForStates(G4State_Idle);

  fPrintVolumesCmd = new G4UIcmdWithAnInteger("/analysis/printVolumes",this);
  fPrintVolumesCmd->SetGuidance("Print volumes in current geometry");
  fPrintVolumesCmd->SetDefaultValue(0);
  fPrintVolumesCmd->AvailableForStates(G4State_Idle);

  fPrintVolTranslationCmd = new G4UIcmdWithAString("/analysis/printTotalTranslation",this);
  fPrintVolTranslationCmd->SetGuidance("Print translation of given volume (default = /nEXO/TPCInternals/LXe)");
  fPrintVolTranslationCmd->SetDefaultValue("/nEXO/TPCInternals/LXe");
  fPrintVolTranslationCmd->AvailableForStates(G4State_Idle);
*/
  fPropagateOpCmd = new G4UIcmdWithAnInteger("/analysis/setPropagateOP",this);
  fPropagateOpCmd->SetGuidance("Set whether to propagate optical photon");
  fPropagateOpCmd->SetDefaultValue(1);
  fPropagateOpCmd->AvailableForStates(G4State_Idle);

  fPropagateTeCmd = new G4UIcmdWithAnInteger("/analysis/setPropagateTE",this);
  fPropagateTeCmd->SetGuidance("Set whether to propagate thermal electron");
  fPropagateTeCmd->SetDefaultValue(0);
  fPropagateTeCmd->AvailableForStates(G4State_Idle);

  fSaveOpCmd = new G4UIcmdWithAnInteger("/analysis/setSaveOP",this);
  fSaveOpCmd->SetGuidance("Set whether to save optical photon");
  fSaveOpCmd->SetDefaultValue(1);
  fSaveOpCmd->AvailableForStates(G4State_Idle);

  fSaveTeCmd = new G4UIcmdWithAnInteger("/analysis/setSaveTE",this);
  fSaveTeCmd->SetGuidance("Set whether to save thermal electron");
  fSaveTeCmd->SetDefaultValue(1);
  fSaveTeCmd->AvailableForStates(G4State_Idle);

  fSaveOnlyEventsWithDepositsCmd = new G4UIcmdWithABool("/analysis/setSaveOnlyEventsWithDeposits", this);
  fSaveOnlyEventsWithDepositsCmd->SetGuidance("Toggle to only save events if they have energy deposits");
  fSaveOnlyEventsWithDepositsCmd->SetDefaultValue(true);
  fSaveOnlyEventsWithDepositsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

nEXOAnalysisMessenger::~nEXOAnalysisMessenger()
{
  delete fDirectory;
  delete fRootFileNameCmd;
  delete fRootTreeNameCmd;
//  delete fPrintVolNames;
//  delete fPrintVolumesCmd;
//  delete fPrintVolTranslationCmd;
  delete fPropagateTeCmd;
  delete fPropagateOpCmd;
  delete fSaveTeCmd;
  delete fSaveOpCmd;
  delete fSaveOnlyEventsWithDepositsCmd;

}

void nEXOAnalysisMessenger::SetNewValue(G4UIcommand* cmd, G4String val)
{
  if (cmd == fRootFileNameCmd) fAnalysis->SetROOTFileName(val);
  else if (cmd == fRootTreeNameCmd) fAnalysis->SetROOTTreeName(val);
  //else if (cmd == fPrintVolNames) nEXOSimplePhysVolManager::GetInstance()->PrintLogicVolumeNames();
  //else if (cmd == fPrintVolumesCmd) nEXOSimplePhysVolManager::GetInstance()->PrintVolumes(fPrintVolumesCmd->GetNewIntValue(val));
  //else if (cmd == fPrintVolTranslationCmd) nEXOSimplePhysVolManager::GetInstance()->PrintLogicVolumeTranslation(val);
  else if (cmd == fPropagateOpCmd) fAnalysis->SetPropagateOP(fPropagateOpCmd->GetNewIntValue(val));
  else if (cmd == fPropagateTeCmd) fAnalysis->SetPropagateTE(fPropagateTeCmd->GetNewIntValue(val));
  else if (cmd == fSaveOpCmd) fAnalysis->SetSaveOP(fSaveOpCmd->GetNewIntValue(val));
  else if (cmd == fSaveTeCmd) fAnalysis->SetSaveTE(fSaveTeCmd->GetNewIntValue(val));
  else if (cmd == fSaveOnlyEventsWithDepositsCmd) fAnalysis->SetSaveOnlyEventsWithDeposits(fSaveOnlyEventsWithDepositsCmd->GetNewBoolValue(val));
}

nEXOAnalysis* nEXOAnalysis::fInstance = 0;

nEXOAnalysis::nEXOAnalysis()
{
  fRootFile = NULL;
  fRootTree = NULL;
  fRootFileName = "output.root";
  fRootTreeName = "tree";

  ResetTreeVariables();
  fBoundary = NULL;
  fWorld = NULL;

  fPropagateOP = 1;
  fPropagateTE = 0;
  fSaveOP = 1;
  fSaveTE = 1;

  fSaveOnlyEventsWithDeposits = false; //false;
}

nEXOAnalysis::~nEXOAnalysis(){;}

void nEXOAnalysis::PrepareNewRun(const G4Run* g4Run)
{
  TTimeStamp start;
  G4cout << "Run " << g4Run->GetRunID() << " starts at:" << G4endl;
  start.Print();

  WriteGeometry();
  //G4String fileDir = fRootFileName+":/";
  //gDirectory->cd(fileDir.data());
  
  fRootFile = new TFile(fRootFileName, "update");

  fRootFile->cd();
  gDirectory->WriteObject(&start,Form("StartTime_Run%d",g4Run->GetRunID()));
  
  fRootTree = new TTree(fRootTreeName,"Tree of nEXO events");
  fRootTree->SetDirectory(fRootFile);
  
  ResetTreeVariables();
  
  SetTreeBranches();
}

void nEXOAnalysis::EndOfRun(const G4Run* g4Run)
{
  TTimeStamp end;
  G4cout << "Run " << g4Run->GetRunID() << " ends at:" << G4endl;
  end.Print();

  G4int nEvents = g4Run->GetNumberOfEvent();
  TParameter<G4int> nMCevents(Form("NumberOfEvents_Run%d",g4Run->GetRunID()),nEvents);
  
  //fRootFile = new TFile(fRootFileName, "update");
  TTimeStamp* start = (TTimeStamp*)fRootFile->Get(Form("StartTime_Run%d",g4Run->GetRunID()));
  if(start)
  {
    time_t diff = end.GetSec() - start->GetSec();
    G4cout << "Time to simulate " << nEvents << " events = " << diff << " seconds. Average = " << nEvents*1./diff << " events/seconds.\n";
  }
  else
    std::cout << "Not found: " << Form("StartTime_Run%d",g4Run->GetRunID()) << std::endl;

  fRootFile->cd();
  gDirectory->WriteObject(&end,Form("EndTime_Run%d",g4Run->GetRunID()));

  nMCevents.Write();
  
  G4cout << "Saving tree: " << fRootTreeName << " to output ROOT file: " << fRootFileName << G4endl;
  fRootTree->Write();
  
  fRootFile->Close();
}

void nEXOAnalysis::PrepareNewEvent(const G4Event* g4Event)
{
  ResetTreeVariables();  

  fEventNumber = g4Event->GetEventID();
  if(fEventNumber % 1000 == 0)
    G4cout << "Event id --> " << fEventNumber << G4endl;
}

void nEXOAnalysis::EndOfEvent(const G4Event* /*g4Event*/)
{
  //fEventNumber = g4Event->GetEventID();
  //if (fNumDeposits > 200) G4cout << "NumDeposits = " << fNumDeposits << G4endl;

  //if(!(fNTE<MAXTENUM)) G4cout << "fNTE>=MAXTENUM : " << fNTE<< G4endl;
  //if(!(fNOP<MAXOPNUM)) G4cout << "fNOP>=MAXOPNUM : " << fNOP<< G4endl;
  //if(!(fNumDeposits<MAXDEPNUM)) G4cout << "fNumDeposits>=MAXDEPNUM :" << fNumDeposits << G4endl;
  if(!fSaveOnlyEventsWithDeposits)
    fRootTree->Fill();
  else if(fNumDeposits > 0)
    fRootTree->Fill();
}

void nEXOAnalysis::PreUserTrackingAction(const G4Track* g4Track)
{
  if(g4Track->GetTrackID() == 1)
  {
    fGenX = (g4Track->GetVertexPosition()).getX()/mm;
    fGenY = (g4Track->GetVertexPosition()).getY()/mm;
    fGenZ = (g4Track->GetVertexPosition()).getZ()/mm;
  }

  //G4cout << g4Track->GetDefinition()->GetParticleName() << G4endl; //RT debug
}
void nEXOAnalysis::PostUserTrackingAction(const G4Track* /*g4Track*/){}

void nEXOAnalysis::SteppingAction(const G4Step* step)
{
  G4StepPoint* preStepPoint = step->GetPreStepPoint();
  G4StepPoint* postStepPoint = step->GetPostStepPoint();
  
  const G4VPhysicalVolume* postStepVolume = postStepPoint->GetPhysicalVolume();
  const G4VPhysicalVolume* preStepVolume = preStepPoint->GetPhysicalVolume();
  const G4String preVolName = preStepVolume->GetName();
  G4Track* stepTrack = step->GetTrack();

  if (postStepVolume)
  {
    G4String postVolName = postStepVolume->GetName();
    G4double edep = step->GetTotalEnergyDeposit();
    
    if (edep > 0 && postVolName == "/nEXO/TPCInternals/sTPCLXe")
    {
      fEnergyDeposit.push_back(edep);
      fTotalEventEnergy += edep;

      fLengthDeposit.push_back(step->GetStepLength());
      fPreEnergyDeposit.push_back(preStepPoint->GetTotalEnergy());
      fPostEnergyDeposit.push_back(postStepPoint->GetTotalEnergy());
      
      G4int trackID = stepTrack->GetTrackID();
      fTrackNumber.push_back(trackID);

      G4ThreeVector position = stepTrack->GetPosition();
      fXpos.push_back(position.getX());
      fYpos.push_back(position.getY());
      fZpos.push_back(position.getZ());

      fTglob.push_back(stepTrack->GetGlobalTime());
      fTloc.push_back(stepTrack->GetLocalTime());
      
      fNumDeposits++;
    }

    if(preVolName == "/nEXO/TPCInternals/sTPCLXe")
    {
      if(step->GetTrack()->GetDefinition() == nEXOG4ThermalElectron::ThermalElectron() && step->GetTrack()->GetCurrentStepNumber() == 1)
      {
        G4int nTE = fNTE;

        G4double energy = step->GetTrack()->GetKineticEnergy()/eV;
        G4double TEX = (preStepPoint->GetPosition()).getX()/mm;
        G4double TEY = (preStepPoint->GetPosition()).getY()/mm;
        G4double TEZ = (preStepPoint->GetPosition()).getZ()/mm;

        fTEEnergy.push_back(energy);
        fTEX.push_back(TEX);
        fTEY.push_back(TEY);
        fTEZ.push_back(TEZ);

        fNTE++;
        if(fPropagateTE==0) {
        // Stop and kill this thermal electron
          stepTrack->SetTrackStatus(fStopAndKill);
        }
      }
      if(step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() && step->GetTrack()->GetCurrentStepNumber() == 1)
      {
        fInitNOP++;
        
        if(step->GetTrack()->GetCreatorProcess() != 0) {
          if(step->GetTrack()->GetCreatorProcess()->GetProcessName().contains("Cere")){
              fInitCherenkovOP++;
          }
        }
        if(fPropagateOP==0) {
        // Stop and kill this thermal electron
          stepTrack->SetTrackStatus(fStopAndKill);
        }
      }
    }    
  }

  //find the volume that optical photon stopped
  if(step->GetTrack()->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition() && fPropagateOP == 1)
  {
    G4OpBoundaryProcessStatus boundaryStatus = Undefined;
    //find the boundary process only once
    if(!fBoundary || step->GetTrack()->GetCurrentStepNumber() == 1)
    {
      G4ProcessManager* pm = step->GetTrack()->GetDefinition()->GetProcessManager();
      G4int nprocesses = pm->GetProcessListLength();
      G4ProcessVector* pv = pm->GetProcessList();
      G4int i;
      for( i=0;i<nprocesses;i++){
        if((*pv)[i]->GetProcessName()=="OpBoundary"){
          fBoundary = (G4OpBoundaryProcess*)(*pv)[i];
          break;
        }
      }
    }
    
    if(fBoundary) boundaryStatus = fBoundary->GetStatus();
//std::cout << "volume: " << step->GetTrack()->GetNextVolume()->GetName() << ", process: " << step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() << std::endl;

    //if ((boundaryStatus==Absorption) || (step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="OpAbsorption"))
    if ((boundaryStatus==Absorption) || (step->GetTotalEnergyDeposit() > 0))
    {
      G4int volume = -1;
      if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/sTPCLXe")==0)
        volume = 1;
      else if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/SiPMPads")==0)
        volume = 2;
      else if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/ActiveSiPMPads")==0)
      {
        volume = 3;
        
        G4int nOP = fNOP; 
        G4int SiPMID = step->GetTrack()->GetNextTouchable()->GetReplicaNumber(1);
        G4double time = step->GetTrack()->GetGlobalTime()/ns;
        G4double energy = step->GetTrack()->GetKineticEnergy()/eV;
        //G4double OPX = (preStepPoint->GetPosition()).getX()/mm;
        //G4double OPY = (preStepPoint->GetPosition()).getY()/mm;
        //G4double OPZ = (preStepPoint->GetPosition()).getZ()/mm;
        G4double OPX = (step->GetTrack()->GetVertexPosition()).getX()/mm;
        G4double OPY = (step->GetTrack()->GetVertexPosition()).getY()/mm;
        G4double OPZ = (step->GetTrack()->GetVertexPosition()).getZ()/mm;

        G4int OPType=0;
        if(step->GetTrack()->GetCreatorProcess() != 0) {
          if(step->GetTrack()->GetCreatorProcess()->GetProcessName() =="S1") OPType=1;
          if(step->GetTrack()->GetCreatorProcess()->GetProcessName().contains("Cere")) OPType = 2;
        }

        fSiPMID.push_back(SiPMID);
        fOPTime.push_back(time);
        fOPEnergy.push_back(energy);
        fOPX.push_back(OPX);
        fOPY.push_back(OPY);
        fOPZ.push_back(OPZ);
        fOPType.push_back(OPType);

        fNOP++;
      }
      else if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/SiPMPadBase")==0)
        volume = 4;
      else if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/FieldRing")==0)
        volume = 5;
      else if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/Anode")==0)
        volume = 6;
      else if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/Cathode")==0 || strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/Bulge")==0)
        volume = 7;
      else if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCVessel")==0)
        volume = 8;
      else if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/TReflector")==0)
        volume = 9;
      else if (strcmp(step->GetTrack()->GetNextVolume()->GetName(),"/nEXO/TPCInternals/TPB")==0)
        volume = 10;
      else
        volume = -1;
//std::cout << "volume: " << volume << ", " << step->GetTrack()->GetNextVolume()->GetName() << std::endl;
      //fOPStopVolume[fInitNOP-1] = volume;
      fOPStopVolume.push_back(volume);
    }
  }
  
  
}


void nEXOAnalysis::GetTE(int i, G4double& E, G4double& X, G4double& Y, G4double& Z)
{
  E = fTEEnergy[i];
  X = fTEX[i];
  Y = fTEY[i];
  Z = fTEZ[i];
}

void nEXOAnalysis::AddThermalElectron(G4ThreeVector pos) {
  fTEX.push_back(pos[0]);
  fTEY.push_back(pos[1]);
  fTEZ.push_back(pos[2]);
  fNTE++;
}

void nEXOAnalysis::ResetTreeVariables(void)
{
  fEventNumber = 0;
  fTotalEventEnergy = 0;
  //fNumDeposits = 0;
  //fInitNOP = 0;
  //fNOP = 0;
  //fNTE = 0;
  fGenX = 0;
  fGenY = 0;
  fGenZ = 0;

  fSiPMID.clear();
  fOPTime.clear();
  fOPType.clear();
  fOPEnergy.clear();
  fOPX.clear();
  fOPY.clear();
  fOPZ.clear();
  fNOP = 0;

  fOPStopVolume.clear();
  fInitNOP = 0;
  fInitCherenkovOP=0;

  //for (G4int i = 0; i < MAXTENUM; i++)
  /* for (G4int i = 0; i < fNTE; i++)
  {
    fTEX[i] = 0; 
    fTEY[i] = 0;
    fTEZ[i] = 0;
    fTEEnergy[i] = 0; 
  } */
  fTEX.clear();
  fTEY.clear();
  fTEZ.clear();
  fTEEnergy.clear();
  fNTE = 0;

  //for (G4int i = 0; i< MAXDEPNUM; i++)
  /*for (G4int i = 0; i< fNumDeposits; i++)
  {
    fLengthDeposit[i] = 0; 
    fEnergyDeposit[i] = 0; 
    fPreEnergyDeposit[i] = 0; 
    fPostEnergyDeposit[i] = 0; 
    fTrackNumber[i] = 0; 
    fXpos[i] = 0; 
    fYpos[i] = 0; 
    fZpos[i] = 0;
    fTglob[i] = 0;
    fTloc[i] = 0;
  }*/
  fLengthDeposit.clear();
  fEnergyDeposit.clear();
  fPreEnergyDeposit.clear();
  fPostEnergyDeposit.clear();
  fTrackNumber.clear();
  fXpos.clear();
  fYpos.clear();
  fZpos.clear();
  fTglob.clear();
  fTloc.clear();

  fNumDeposits = 0;

}

void nEXOAnalysis::SetTreeBranches(void)
{
  fRootTree->Branch("EventNumber",&fEventNumber,"EventNumber/I");
  fRootTree->Branch("GenX",&fGenX,"GenX/D");
  fRootTree->Branch("GenY",&fGenY,"GenY/D");
  fRootTree->Branch("GenZ",&fGenZ,"GenZ/D");
  fRootTree->Branch("TotalEventEnergy",&fTotalEventEnergy,"TotalEventEnergy/D");
  fRootTree->Branch("NumDeposits",&fNumDeposits,"NumDeposits/I");
  fRootTree->Branch("LengthDeposit", &fLengthDeposit);
  fRootTree->Branch("EnergyDeposit", &fEnergyDeposit);
  fRootTree->Branch("PreEnergyDeposit", &fPreEnergyDeposit);
  fRootTree->Branch("PostEnergyDeposit", &fPostEnergyDeposit);
  fRootTree->Branch("TrackNumber", &fTrackNumber);
  fRootTree->Branch("Xpos", &fXpos);
  fRootTree->Branch("Ypos", &fYpos);
  fRootTree->Branch("Zpos", &fZpos);
  //fRootTree->Branch("Tglob", &fTglob);
  //fRootTree->Branch("Tloc", &fTloc);
  fRootTree->Branch("InitNumOP", &fInitNOP, "InitNumOP/I");
  fRootTree->Branch("OPStopVolume", &fOPStopVolume);
  fRootTree->Branch("NumOP", &fNOP, "NumOP/I");
  fRootTree->Branch("SiPMID", &fSiPMID);
  fRootTree->Branch("OPEnergy", &fOPEnergy);
  fRootTree->Branch("OPTime", &fOPTime);
  fRootTree->Branch("OPType", &fOPType);
  //fRootTree->Branch("OPX", &fOPX);
  //fRootTree->Branch("OPY", &fOPY);
  //fRootTree->Branch("OPZ", &fOPZ);
  fRootTree->Branch("NumTE", &fNTE, "NumTE/I");
  //fRootTree->Branch("TEEnergy", &fTEEnergy);
  //fRootTree->Branch("TEX", &fTEX);
  //fRootTree->Branch("TEY", &fTEY);
  //fRootTree->Branch("TEZ", &fTEZ);
}

//void nEXOAnalysis::WriteGeometry(G4VPhysicalVolume* world)
void nEXOAnalysis::WriteGeometry()
{
  // Export geometry in Root and save it in a file

  // Import Geant4 geometry to VGM
//  Geant4GM::Factory g4Factory;
//  g4Factory.Import(GetGeometry());
  // 
  // Export VGM geometry to Root
//  RootGM::Factory rtFactory;
//  g4Factory.Export(&rtFactory);
//  gGeoManager->CloseGeometry();
//  gGeoManager->SetName("nEXOGeometry");
//  gGeoManager->SetTitle("nEXO ROOT Geometry");
//  gGeoManager->Export(fRootFileName.data(),"nEXOGeometry");
}
