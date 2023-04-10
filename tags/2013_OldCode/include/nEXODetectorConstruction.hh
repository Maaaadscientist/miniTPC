////////////////////////////////////////////////////////
// nEXODetectorConstruction3.hh
// Coarse nEXO Geometry header file
////////////////////////////////////////////////////////

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef nEXODetectorConstruction_h
#define nEXODetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "nEXODetectorMessenger.hh"
#include <vector>

class G4Box;
class G4Tubs;
class G4Sphere;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4PVParameterised;
class G4Material;
class G4UniformMagField;
class EXODetectorMessenger;
class G4Region;
class G4IStore;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nEXODetectorConstruction : public G4VUserDetectorConstruction
{
public:
  nEXODetectorConstruction();
 ~nEXODetectorConstruction();

public:

  G4VPhysicalVolume* Construct();

  void UpdateGeometry();

private:

  G4Material*        defaultMaterial;
  G4Material*        MineRock;
  G4Material*        Coating;
  G4Material*        Floor;
  G4Material*        Water1;
  G4Material*        Water2;
  G4Material*        WaterInner1;
  G4Material*        WaterInner2;
  G4Material*        OuterVessel;
  G4Material*        VacuumSpace;
  G4Material*        InnerVessel;
  G4Material*        HFEMaterial;
  G4Material*        TpcMaterial;
  G4Material*        Water;
  G4Material*        Hdpe;
  G4Material*        AIR;
  G4Material*        LEAD;
  G4Material*        LXe;
  G4Material*        ActiveLXe;
  G4Material*        Acrylic;
  G4Material*        Reflector;
  G4Material*        Insulator;
  G4Material*        SSteel;
  G4Material*        Cables;
  G4Material*        SiPMMaterial;

  G4double           WorldSizeXYZ;
  G4double           MineRockXYZ;

  G4double           SurroundRockR;
  G4double           SurroundRockh;
  G4double           AirDomeR;
  G4double           ShotcreteR;
  G4double           Shotcreteh;
  G4double           FloorR;
  G4double           Floorh;
  G4double           RockDomeR;
  G4double           SCDomeR;
  G4double           OuterWater1R;
  G4double           OuterWater1h;
  G4double           OuterWater2R;
  G4double           OuterWater2h;
  G4double           HDPETankR;
  G4double           HDPETankThick;
  G4double           HDPETankh;
  G4double           InnerWater1R;
  G4double           InnerWater1h;
  G4double           InnerWater2R;
  G4double           InnerWater2h;


  G4double           InnerCryoThick;
  //  G4double           InnerCryoIR;
  G4double           InnerCryoOR;
  G4double           InnerCryoH;
  G4double           OuterCryoThick;
  //  G4double           OuterCryoIR;
  G4double           OuterCryoOR;
  G4double           OuterCryoH;
  G4double           VacuumGapOR;
  G4double           VacuumGapH;
  G4double           VacuumGapThick;
  G4double           VesselThickness;
  G4double           LeadPlateR;
  G4double           LeadPlateH;
  G4double           AirCavityR;
  G4double           AirCavityH;
  G4double           HfeOR;
  G4double           HfeHeight;
  G4double           StSupportR;
  G4double           StSupportH;
  G4double           TpcThick;
  G4double           TpcLength;
  G4double           TpcOR;
  G4double           InactiveLXeR;
  G4double           InactiveLXeH;
  G4double           ActiveLXeR;
  G4double           ActiveLXeH;
  G4double           FieldRingIR;
  G4double           FieldRingOR;
  G4double           FieldRingWidth;
  //  G4double           FieldRingCenterDist;
  //  G4double           DistBetweenRings;
  G4double           FieldRingLipIR;
  G4double           FieldRingLipOR;
  G4double           FieldRingLipH;
  G4double           TReflectorIR;
  G4double           TReflectorOR;
  G4double           TReflectorH;
  G4double           APDPlatterR;
  G4double           APDPlatterThick;
  G4double           KCablesR;
  G4double           KCablesThick;
  G4double           TeflonInsulatorR;
  G4double           TeflonInsulatorThick;
  G4double           FieldSupportOR;
  G4double           FieldSupportIR;
  G4double           FieldSupportH;
  G4double           Cathode_Anode_distance;
  G4double           APD_Wire_Wire_Dist;
  G4double           SiPMR;
  G4double           SiPMThick;


  G4double           SurroundRockPlaceZ;
  G4double           ShotcretePlaceZ;
  G4double           FloorPlaceZ;
  G4double           OuterWaterPlace1Z;
  G4double           OuterWaterPlace2Z;
  G4double           HDPETankPlaceZ;
  G4double           InnerWater1PlaceZ;
  G4double           InnerWater2PlaceZ;
  G4double           StSupportPlaceZ;
  G4double           OuterCryoPlaceZ;
  //  G4double           SSupport2PlaceZ;
  G4double           APDPlatterPlaceZ;
  G4double           TeflonInsulatorPlaceZ;
  G4double           KCablesPlaceZ;
  G4double           SiPMPlaceZ;

  G4Box*             solidWorld;  //pointer to the solid World
  G4LogicalVolume*   logicWorld;  //pointer to the logical World
  G4VPhysicalVolume* physiWorld;  //pointer to the physical World
  
  G4Box*             solidMine;
  G4LogicalVolume*   logicMine;
  G4VPhysicalVolume* physiMine;


  G4Tubs*            solidSurroundRock;
  G4LogicalVolume*   logicSurroundRock;
  G4VPhysicalVolume* physiSurroundRock;
  
  G4Tubs*            solidShotcrete;
  G4LogicalVolume*   logicShotcrete;
  G4VPhysicalVolume* physiShotcrete;  

  G4Tubs*            solidFLOOR;
  G4LogicalVolume*   logicFLOOR;
  G4VPhysicalVolume* physiFLOOR;  

  G4Sphere*          solidRockDome;
  G4LogicalVolume*   logicRockDome;
  G4VPhysicalVolume* physiRockDome;

  G4Sphere*          solidShotDome;
  G4LogicalVolume*   logicShotDome;
  G4VPhysicalVolume* physiShotDome;

  G4Sphere*          solidAirDome;
  G4LogicalVolume*   logicAirDome;
  G4VPhysicalVolume* physiAirDome;

  G4Tubs*            solidOuterWater1;
  G4LogicalVolume*   logicOuterWater1;
  G4VPhysicalVolume* physiOuterWater1;

  G4Tubs*            solidOuterWater2;
  G4LogicalVolume*   logicOuterWater2;
  G4VPhysicalVolume* physiOuterWater2;

  G4Tubs*            solidHDPETank;
  G4LogicalVolume*   logicHDPETank;
  G4VPhysicalVolume* physiHDPETank;

  G4Tubs*            solidInnerWater1;
  G4LogicalVolume*   logicInnerWater1;
  G4VPhysicalVolume* physiInnerWater1; 

  G4Tubs*            solidInnerWater2;
  G4LogicalVolume*   logicInnerWater2;
  G4VPhysicalVolume* physiInnerWater2; 


  /*  G4Tubs*            solidStSupport2;
  G4LogicalVolume*   logicStSupport2;
  G4VPhysicalVolume* physiStSupport2[2];*/

  G4Tubs*            solidOuterCryo;
  G4LogicalVolume*   logicOuterCryo;
  G4VPhysicalVolume* physiOuterCryo;

  G4Tubs*            solidInnerCryo;
  G4LogicalVolume*   logicInnerCryo;
  G4VPhysicalVolume* physiInnerCryo;

  G4Tubs*            solidVacuumGap;
  G4LogicalVolume*   logicVacuumGap;
  G4VPhysicalVolume* physiVacuumGap;

  G4Tubs*            solidHFE;
  G4LogicalVolume*   logicHFE;
  G4VPhysicalVolume* physiHFE;

  G4Tubs*            solidTPC;
  G4LogicalVolume*   logicTPC;
  G4VPhysicalVolume* physiTPC;

  G4Tubs*            solidInactiveLXe;
  G4LogicalVolume*   logicInactiveLXe;
  G4VPhysicalVolume* physiInactiveLXe;


  G4Tubs*            solidFieldRing;
  G4LogicalVolume*   logicFieldRing;
  G4VPhysicalVolume* physiFieldRing[60];

  G4Tubs*            solidFieldRingLip;
  G4LogicalVolume*   logicFieldRingLip;
  G4VPhysicalVolume* physiFieldRingLip[120];

  G4Tubs*            solidTReflector;
  G4LogicalVolume*   logicTReflector;
  G4VPhysicalVolume* physiTReflector;

  G4Tubs*            solidAPDPlatter;
  G4LogicalVolume*   logicAPDPlatter;
  G4VPhysicalVolume* physiAPDPlatter[2];

  G4Tubs*            solidSiPMs;
  G4LogicalVolume*   logicSiPMs;
  G4VPhysicalVolume* physiSiPMs[2];

  G4Tubs*            solidKCables;
  G4LogicalVolume*   logicKCables;
  G4VPhysicalVolume* physiKCables[2];
  
  G4Tubs*            solidTeflonInsulator;
  G4LogicalVolume*   logicTeflonInsulator;
  G4VPhysicalVolume* physiTeflonInsulator[2];


  G4Tubs*            solidFieldSupport;
  G4LogicalVolume*   logicFieldSupport;
  G4VPhysicalVolume* physiFieldSupport;

  G4Tubs*            solidActiveLXe;
  G4LogicalVolume*   logicActiveLXe;
  G4VPhysicalVolume* physiActiveLXe;

  G4RotationMatrix  TpcRM ;
  G4RotationMatrix  AcrylicRM;

  nEXODetectorMessenger* detectorMessenger;  //pointer to the Messenger

  //    G4Region*         fCryostatRegion;
  //    G4Region*         fTPCRegion;
  
private:

  void DefineMaterials();
  G4VPhysicalVolume* ConstructDetector();


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
