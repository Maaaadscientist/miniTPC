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
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "nEXOAnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "nEXOHisto.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOAnalysisManager* nEXOAnalysisManager::fManager = 0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOAnalysisManager* nEXOAnalysisManager::getInstance()
{
  if(!fManager) {
    fManager = new nEXOAnalysisManager();
  }
  return fManager;
}
void nEXOAnalysisManager::dispose()
{
  delete fManager;
  fManager = 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOAnalysisManager::nEXOAnalysisManager()
{
  verbose = 0;
  nEvt1   = -1;
  nEvt2   = -1;
  targetThresE = 10*keV;
  detectorThresE = 10*keV;
  pulseWidth = 0.1*microsecond;
  histo   = new nEXOHisto();
  bookHisto();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOAnalysisManager::~nEXOAnalysisManager()
{
#ifdef G4ANALYSIS_USE 
#define HISTDELETE
#endif
#ifdef G4ANALYSIS_USE_ROOT
#define HISTDELETE
#endif
#ifdef HISTDELETE
  delete histo;
#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOAnalysisManager::bookHisto()
{
  histEMax = 5.0*MeV;
  histEMin = .0*MeV;
  histNBin = 100;

  histo->add1D("1",
    "Energy deposit (MeV) in the detector",histNBin,histEMin,histEMax,MeV);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOAnalysisManager::BeginOfRun()
{
  histo->book();
  G4cout << "nEXOAnalysisManager: Histograms are booked and the run has been started" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOAnalysisManager::EndOfRun()
{
  histo->save();  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOAnalysisManager::BeginOfEvent()
{
  Edepo.clear();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOAnalysisManager::EndOfEvent()
{
  if (Edepo.size()) {
    std::sort(Edepo.begin(),Edepo.end());
    G4double TarE = Edepo[0].GetEnergy();
    G4double Time = Edepo[0].GetTime();
    G4double TarW = Edepo[0].GetEnergy()*Edepo[0].GetWeight();
    G4double DetE = 0.;
    G4double DetW = 0.;
    G4double ComW = 0.;
    
  if (TarE< 0.) {
      DetE = -TarE;
      DetW = -TarW;
      TarE = 0.;
      TarW = 0.;
    }
//    G4cout << "** NEW EVENT **" << G4endl; 
    for (size_t i = 1; i < Edepo.size(); i++) {
 /*      G4cout << "!!!!! in End of Event, parid =  " << Edepo[i].GetParentid()  << G4endl;
       G4cout << "and trackid =  " << Edepo[i].GetTrackid() << G4endl;
       G4cout << "and energy =  " << Edepo[i].GetEnergy() << G4endl;
       G4cout << "and gamid =  " << Edepo[i].GetGamid() << G4endl;
       G4cout << "  " << G4endl;
*/
      if ( Edepo[i].GetGamid() == Edepo[i-1].GetGamid()) {
	if ( Edepo[i].GetEnergy() > 0. ) {
	      TarE += Edepo[i].GetEnergy();
 //             G4cout << "TarE +=  " << TarE << G4endl;
	      TarW += Edepo[i].GetEnergy()*Edepo[i].GetWeight();
         } else {
	  DetE -= Edepo[i].GetEnergy();
	  DetW -= Edepo[i].GetEnergy()*Edepo[i].GetWeight();
          }
       } else {
	// tallying
	if (TarE || DetE) ComW = (TarW+DetW)/(TarE+DetE);
	if (TarE) TarW /= TarE;
	if (DetE) DetW /= DetE;
	//
	if (TarE) histo->fillHisto(0,TarE,TarW); // target histogram
//	if (DetE) histo->fillHisto(0,DetE,DetW); // Detector histogram
	//
	//reset
	TarE = Edepo[i].GetEnergy();
//        G4cout << "TarE not += " << TarE << G4endl;
	Time = Edepo[i].GetTime();
	TarW = Edepo[i].GetEnergy()*Edepo[i].GetWeight();
	DetE = 0.;
	DetW = 0.;

	if (TarE < 0) {
	  DetE = -TarE;
	  DetW = -TarW;
	  TarE = 0.;
	  TarW = 0.;
	}
      }
    }
    //tally the last hit
    if (TarE || DetE) ComW = (TarW+DetW)/(TarE+DetE);
    if (TarE) TarW /= TarE;
    if (DetE) DetW /= DetE;
    //
    if (TarE) histo->fillHisto(0,TarE,TarW); // target histogram
//    if (DetE) histo->fillHisto(0,DetE,DetW); // Detector histogram

    // now add zero energy to separat events
    AddEnergy(0.,0.,0.,0,0);
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void nEXOAnalysisManager::AddEnergy(G4double edep, G4double weight, G4double time, G4int parentid, G4int trackid)
{
  if(1 < verbose) {
    G4cout << "nEXOAnalysisManager::AddEnergy: e(keV)= " << edep/keV 
	   << " weight = " << weight << " time (s) = " <<  time/second
           << G4endl;
  }

  histo->addRow(2);
  // 
 
       G4int gamid = 0; 
       G4int j = Edepo.size();
//       G4cout << "j = " << j << G4endl;
   
       if (parentid == trackid ) {
          gamid = parentid;
       } else if (j > 0) {
                 if (parentid == Edepo[j-1].GetParentid()) {
                    gamid = Edepo[j-1].GetGamid();
                 } 
                 else if (parentid == Edepo[j-1].GetTrackid() || parentid == Edepo[j-1].GetGamid()) {
                    gamid = Edepo[j-1].GetGamid();
                 }   
       } 
/*      
       G4cout << "## gamid =  " << gamid << G4endl;
       G4cout << "## parentid = " << parentid << G4endl;
       G4cout << "## trackid = " << trackid << G4endl;
       G4cout << "  " << G4endl;
*/
  nEXOEnergyDeposition A(edep,time,weight,parentid,trackid,gamid);
  Edepo.push_back(A);
/*
    for (size_t i = 1; i < Edepo.size(); i++) {
       G4cout << "*****in AddEnergy, parid =  " << Edepo[i].GetParentid()  << G4endl;
       G4cout << "and trackid =  " << Edepo[i].GetTrackid() << G4endl;
       G4cout << "and energy =  " << Edepo[i].GetEnergy() << G4endl;
       G4cout << "  " << G4endl;
   }*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOAnalysisManager::AddParticle()
{
  histo->addRow(0);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOAnalysisManager::AddIsotope()
{
  histo->addRow(1);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

