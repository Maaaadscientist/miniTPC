//////////////////////////////////////////
// nEXODetectorConstruction.hh //
// Construction of the external components to the nEXO TPC //
//////////////////////////////////////////

#ifndef miniTPCDetectorConstruction_h
#define miniTPCDetectorConstruction_h 1

#include <map>
#include <algorithm>

#include "G4SystemOfUnits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Cons.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4VUserDetectorConstruction.hh"

class miniTPCDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  miniTPCDetectorConstruction();
  virtual ~miniTPCDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();


  

private:
  void BuildOtherParts(G4LogicalVolume* logicWorld);
  void SetOpticalSurfaces();

  bool fCheckOverlaps;
  G4double fTPCVesselRef;
  G4double fFieldRingRef;
  G4double fAnodeRef;
  G4double fCathodeRef;
  G4double fBulgeRef;
  G4double fTeflonRef;
  G4double fSTeflonRef;
  G4double fSTPCVesselRef;

  G4double fSTPCRadius;
  G4double fSTPCVesselSideThickness;
  G4double fSTPCHalfheight;

  // Parameters for field rings
  G4int nFieldRings;//Ring number of miniTPC
  G4double fTopRingZPosition;
  G4double fieldRingSweptR;
  G4double fFieldRingLength;
  G4double fFieldRingThick;
  G4double fWWDistance;

  // Parameters for Anode/Cathode
  G4double fAnodeRadius;
  G4double fAnodeThickness;
  G4double fAnodeZPosition;
  G4double fCathodeRadius;
  G4double fCathodeThickness;
  G4double fCathodeZPosition;

  // Parameters for Simple SiPM
  G4int fNSiPMPadAlongZ;
  G4int fNSiPMPadAlongPhi; 
  G4double dGapAlongZ;
  G4double fTopSiPMZPosition;
  G4double fSiPMPadThickness; 
  G4double fSiPMPadHeight;
  G4double fSiPMStandoffFromTPC;
  
  G4double fSiPMActiveLayerThickness;
  G4double fSiPMActiveLayerDepth;
  G4double fActiveSiPMPadHeight;
  
  G4double fSiPMBaseLayerThickness;
  G4double fSiPMPadBaseHeight;
  
  G4int fRingArrangeID;
  G4int fSiPMOption;
};
#endif
