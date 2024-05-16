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
#include "MyOpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4VUserDetectorConstruction.hh"
#include "miniTPCDetectorMessenger.hh"

class miniTPCDetectorConstruction : public G4VUserDetectorConstruction
{
public:
  miniTPCDetectorConstruction();
  virtual ~miniTPCDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();

  void SetCheckoverlaps (bool key){fCheckOverlaps = key;};
  void SetTPCVesselRef (G4double ref){fTPCVesselRef = ref;};
  void SetFieldRingRef (G4double ref){fFieldRingRef = ref;};
  void SetAnodeRef (G4double ref){fAnodeRef = ref;};
  void SetCathodeRef (G4double ref){fCathodeRef = ref;};
  void SetTeflonRef (G4double ref){fTeflonRef = ref;};
  void SetSTeflonRef (G4double ref){fSTeflonRef = ref;};
  void SetBulgeRef (G4double ref){fBulgeRef = ref;};
  void SetSTPCVesselRef (G4double ref){fSTPCVesselRef = ref;};

  
  void SetSiPMOption(G4int opt ){fSiPMOption = opt;};
  void SetRingArrangeID(G4int opt ){fRingArrangeID = opt;};
  
  void SetSTPCRadius (G4double r){fSTPCRadius = r;};
  void SetSTPCVesselSideThickness (G4double t){fSTPCVesselSideThickness = t;};
  void SetSTPCHalfheight (G4double h){fSTPCHalfheight = h;};
  
  void SetnFieldRings (G4int n){nFieldRings = n;};
  void SetTopRingZPosition (G4double z){fTopRingZPosition = z;};
  void SetfieldRingSweptR (G4double r){fieldRingSweptR = r;};
  void SetFieldRingLength (G4double l){fFieldRingLength = l;};
  void SetFieldRingThick (G4double t){fFieldRingThick = t;};
  void SetWWDistance (G4double d){fWWDistance = d;};
  
  void SetAnodeRadius (G4double r){fAnodeRadius = r;};
  void SetAnodeThickness (G4double t){fAnodeThickness = t;};
  void SetAnodeZPosition (G4double z){fAnodeZPosition = z;};

  void SetCathodeRadius (G4double r){fCathodeRadius = r;};
  void SetCathodeThickness (G4double t){fCathodeThickness = t;};
  void SetCathodeZPosition (G4double z){fCathodeZPosition = z;};

  void SetNSiPMPadAlongZ (G4int n){fNSiPMPadAlongZ = n;};
  void SetNSiPMPadAlongPhi (G4int n){fNSiPMPadAlongPhi = n;};
  void SetdGapAlongZ (G4double d){dGapAlongZ = d;};
  void SetTopSiPMZPosition (G4double z){fTopSiPMZPosition = z;};
  void SetSiPMPadThickness (G4double t){fSiPMPadThickness = t;};
  void SetSiPMPadHeight (G4double h){fSiPMPadHeight = h;};
  void SetSiPMStandoffFromTPC (G4double d){fSiPMStandoffFromTPC = d;};
  void SetSiPMActiveLayerThickness (G4double t){fSiPMActiveLayerThickness = t;};
  void SetSiPMActiveLayerDepth (G4double d){fSiPMActiveLayerDepth = d;};
  void SetActiveSiPMPadHeight (G4double h){fActiveSiPMPadHeight = h;};
  void SetSiPMBaseLayerThickness (G4double t){fSiPMBaseLayerThickness = t;};
  void SetSiPMPadBaseHeight (G4double h){fSiPMPadBaseHeight = h;};
  void SetWavelengthRef (G4int w){fWavelengthRef = w;};



private:
  void BuildOtherParts(G4LogicalVolume* logicWorld);
  void SetOpticalSurfaces();

  bool fCheckOverlaps;
  
  G4double fTopHatR;
  G4double fTopHatHalfHeight;
  G4double fTopHatThickness;
  G4double fTopHatBrimThickness;

  
  G4double fGapCuInner;
  G4double fGapInnerOuter;
  G4double fInnerVesselR;
  G4double fInnerVesselThickness;
  G4double fInnerVesselHalfHeight;
  G4double fInnerVesselBottomThickness;
  G4double fInnerVesselTopThickness;
  G4double fInnerVesselZPosition;
  G4double fInnerVesselStandOfSTPC;
  
  G4double fOuterVesselR;
  G4double fOuterVesselThickness;
  G4double fOuterVesselHalfHeight;
  G4double fInnerStandOfOuter;
  G4double fOuterVesselBottomThickness;
  G4double fOuterVesselTopThickness;
  G4double fOuterVesselZPosition;
  
  G4double fTeflonVesselR;
  G4double fTeflonVesselThickness;
  G4double fTeflonVesselHalfHeight;
  G4double fTeflonVesselBottomThickness;
  G4double fTeflonVesselZPosition;
  
  G4double fTopConstructThickness;
  
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
  G4double fSTPCBottomThickness;

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
  G4double fSiPMStandoffFromRing;
  
  G4double fSiPMActiveLayerThickness;
  G4double fSiPMActiveLayerDepth;
  G4double fActiveSiPMPadHeight;
  
  G4double fSiPMBaseLayerThickness;
  G4double fSiPMPadBaseHeight;
  G4double fSiPMStaveHeight; 
  G4double fSiPMStaveWidth;
  G4double fSiPMStaveThickness;
  G4double fSiPMStaveZPosition;

  G4int fRingArrangeID;
  G4int fSiPMOption;
 
  G4double OR_Max;
  G4double PhiOR;
  G4double OR;
  G4double IR;
  G4double PhiIR;
  G4double SiPMIR;
  G4double SiPMStaveDPhi;
  G4int fNSiPMStaveAlongPhi;
  G4double dGapAlongPhi;
  G4double fSiPMGapSiPM;
  G4double fSliceAngle;
  G4double fAnodeStandoffFromSiPM;

  G4double fSiPMWindowThickness;
  G4double fWindowGapSiPM;
  miniTPCDetectorMessenger* fDetectorMessenger;

  G4int fWavelengthRef;
};
#endif

