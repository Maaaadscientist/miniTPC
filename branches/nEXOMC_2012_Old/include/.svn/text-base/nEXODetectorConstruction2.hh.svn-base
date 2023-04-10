////////////////////////////////////////////////////////
// nEXODetectorConstruction2.hh
// Coarse nEXO Geometry header file
////////////////////////////////////////////////////////

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef nEXODetectorConstruction2_h
#define nEXODetectorConstruction2_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "nEXODetectorMessenger2.hh"
#include <vector>

class G4Box;
class G4Tubs;
class G4Sphere;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4PVParameterised;
class G4Material;
class G4UniformMagField;
class EXODetectorMessenger2;
class G4Region;
class G4IStore;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class nEXODetectorConstruction2 : public G4VUserDetectorConstruction
{
public:
  nEXODetectorConstruction2();
 ~nEXODetectorConstruction2();

public:

  G4VPhysicalVolume* Construct();

  void UpdateGeometry();

private:

  G4Material*        defaultMaterial;
  G4Material*        OuterVessel;
  G4Material*        VacuumSpace;
  G4Material*        InnerVessel;
  G4Material*        HFEMaterial;
  G4Material*        TpcMaterial;
  G4Material*        MineRock;
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

  G4double           WorldSizeXYZ;
  G4double           MineRockXYZ;

  G4double           AirDomeR;
  G4double           OuterWaterR;
  G4double           OuterWaterThick;
  G4double           OuterWaterh;
  G4double           OuterWaterBottom;
  G4double           HDPETankR;
  G4double           HDPETankThick;
  G4double           HDPETankh;
  G4double           InnerWaterR;
  G4double           InnerWaterh;
  G4double           InnerWaterBottom;
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
  G4double           InactiveXeR;
  G4double           InactiveXeH;
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
  G4double           ActiveXeR;
  G4double           ActiveXeH;
  G4double           FieldSupportOR;
  G4double           FieldSupportIR;
  G4double           FieldSupportH;
  G4double           Cathode_Anode_distance;
  G4double           APD_Wire_Wire_Dist;


  G4double           HDPEPlaceZ;
  G4double           OuterCryoPlaceZ;
  G4double           OuterWaterPlaceZ;
  G4double           InnerWaterPlaceZ;
  G4double           SSupport2PlaceZ;
  G4double           APDPlatterPlaceZ;
  G4double           TeflonInsulatorPlaceZ;
  G4double           KCablesPlaceZ;

  G4Box*             solidWorld;  //pointer to the solid World
  G4LogicalVolume*   logicWorld;  //pointer to the logical World
  G4VPhysicalVolume* physiWorld;  //pointer to the physical World
  
  G4Box*             solidMine;
  G4LogicalVolume*   logicMine;
  G4VPhysicalVolume* physiMine;

  G4Sphere*          solidAirDome;
  G4LogicalVolume*   logicAirDome;
  G4VPhysicalVolume* physiAirDome;

  G4Tubs*            solidWaterRes;
  G4LogicalVolume*   logicWaterRes;
  G4VPhysicalVolume* physiWaterRes;

  G4Tubs*            solidOuterWater;
  G4LogicalVolume*   logicOuterWater;
  G4VPhysicalVolume* physiOuterWater;

  G4Tubs*            solidHDPETank;
  G4LogicalVolume*   logicHDPETank;
  G4VPhysicalVolume* physiHDPETank;

  G4Tubs*            solidInnerWater;
  G4LogicalVolume*   logicInnerWater;
  G4VPhysicalVolume* physiInnerWater; 

  G4Tubs*            solidStSupport2;
  G4LogicalVolume*   logicStSupport2;
  G4VPhysicalVolume* physiStSupport2[2];

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

  G4Tubs*            solidInactiveXe;
  G4LogicalVolume*   logicInactiveXe;
  G4VPhysicalVolume* physiInactiveXe;


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

  G4Tubs*            solidKCables;
  G4LogicalVolume*   logicKCables;
  G4VPhysicalVolume* physiKCables[2];
  
  G4Tubs*            solidTeflonInsulator;
  G4LogicalVolume*   logicTeflonInsulator;
  G4VPhysicalVolume* physiTeflonInsulator[2];


  G4Tubs*            solidFieldSupport;
  G4LogicalVolume*   logicFieldSupport;
  G4VPhysicalVolume* physiFieldSupport;

  G4Tubs*            solidActiveXe;
  G4LogicalVolume*   logicActiveXe;
  G4VPhysicalVolume* physiActiveXe;

  
  G4RotationMatrix  TpcRM ;
  G4RotationMatrix  AcrylicRM;

  nEXODetectorMessenger2* detectorMessenger;  //pointer to the Messenger
  
private:

  void DefineMaterials();
  G4VPhysicalVolume* ConstructDetector();


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#endif
