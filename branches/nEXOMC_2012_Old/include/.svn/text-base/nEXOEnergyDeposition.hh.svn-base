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
#ifndef nEXOEnergyDeposition_h
#define nEXOEnergyDeposition_h 1

#include "globals.hh"

class nEXOEnergyDeposition
{
  public:   // with description

    nEXOEnergyDeposition();
    nEXOEnergyDeposition( const nEXOEnergyDeposition &right );
    nEXOEnergyDeposition( G4double, G4double, G4double, G4int, G4int, G4int );
    virtual ~nEXOEnergyDeposition();
         // Constructor and virtual destructor

    G4bool operator==(const nEXOEnergyDeposition &right) const ;
    G4bool operator< (const nEXOEnergyDeposition &right) const ;
    G4bool operator<=(const nEXOEnergyDeposition &right) const ;
  // Operators  

  G4double GetEnergy() {return Energy;};
  G4double GetTime() {return Time;};
  G4double GetWeight() {return Weight;};
  G4int GetParentid() {return Parentid;};
  G4int GetTrackid() {return Trackid;};
  G4int GetGamid() {return Gamid;};
  // Accessors

  private:

    G4double Energy;  
    G4double Time;    
    G4double Weight;
    G4int Parentid;
    G4int Trackid;
    G4int Gamid;
};
#endif



