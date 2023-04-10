////////////////////////////////////////////////////////
// nEXODetectorConstruction2.cc
// Coarse nEXO Geometry
// No Barium Tagging area
//    .446 cm TPC wall thickness
////////////////////////////////////////////////////////

//Added Kapton Cables, Teflon behind APDs

#include "nEXODetectorConstruction2.hh"
#include "nEXODetectorMessenger2.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Region.hh"
#include "G4RegionStore.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"
#include "G4SDManager.hh"
#include "G4PVParameterised.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4SDManager.hh"
//#include "nEXOSD.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4IStore.hh"

#include "G4ios.hh"
#include <sstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......T
nEXODetectorConstruction2::nEXODetectorConstruction2()  
{
//materials
defaultMaterial=0,
//objects
  solidWorld=0; logicWorld=0; physiWorld=0;
  solidMine=0; logicMine=0; physiMine=0;
  solidAirDome=0; logicAirDome=0; physiAirDome=0;
  solidOuterWater=0; logicOuterWater=0; physiOuterWater=0;
  solidHDPETank=0; logicHDPETank=0; physiHDPETank=0;
  solidInnerWater=0; logicInnerWater=0; physiInnerWater=0;
  solidStSupport2=0; logicStSupport2=0; physiStSupport2[0]=0; 
  physiStSupport2[1]=0;
  solidOuterCryo=0; logicOuterCryo=0; physiOuterCryo=0;
  solidInnerCryo=0; logicInnerCryo=0; physiInnerCryo=0;
  solidVacuumGap=0; logicVacuumGap=0; physiVacuumGap=0;
   solidHFE=0; logicHFE=0; physiHFE=0;
   solidTPC=0; logicTPC=0; physiTPC=0;
   solidInactiveXe=0; logicInactiveXe=0; physiInactiveXe=0;
   solidFieldRing=0; logicFieldRing=0; for(int h=0; h<60; h++){physiFieldRing[h]=0;}
   solidFieldRingLip=0; logicFieldRingLip=0; for(int h=0; h<60; h++){physiFieldRingLip[h]=0;}
   solidFieldSupport=0; logicFieldSupport=0; physiFieldSupport=0;
   solidTReflector=0; logicTReflector=0; physiTReflector=0; 
   solidAPDPlatter=0; logicAPDPlatter=0; physiAPDPlatter[0]=0; physiAPDPlatter[1]=0; 
   solidKCables=0; logicKCables=0; physiKCables[0]=0; physiKCables[1]=0;
   solidTeflonInsulator=0; logicTeflonInsulator=0; physiTeflonInsulator[0]=0; physiTeflonInsulator[1]=0;
 solidActiveXe=0; logicActiveXe=0; physiActiveXe=0;


  //************************************************//
  //************** Default Values ******************//
  //************************************************//
  //
  //     Note on Geometry
  //     Values from Matt Swift 8/1/12
  //     Setup assumes experiment will be at SnoLab
  //     Thicknesses given as 1/2 actual thickness
  //     Heights given as 1/2 heights according to 
  //         Geant4 convention
  //       --TNJ  8/1/12
  ////////////////////////////////////////////////////

  //The World

  WorldSizeXYZ = 4000.*cm;

  //The Mine

  MineRockXYZ = 2000.*cm;



  //Outer Water Shield
  OuterWaterR = 775.05*cm;
  OuterWaterThick = 132.5*cm;        // Full thickness 265 cm
  OuterWaterh = 650*cm;              // Full height = 1300 cm 
  OuterWaterBottom = 259.5*cm; 

  //Air Cavity
  AirDomeR = OuterWaterR;

  //HDPE Tank
  HDPETankR = OuterWaterR - 2*OuterWaterThick;  // Radius 4780.5 cm
  HDPETankThick = 12.5*cm;                    // Full thickness = 25 cm 
  HDPETankh = 292.4*cm;                 // Full height =584.8


  //Inner Water Shield
  InnerWaterR = HDPETankR - 2*HDPETankThick;
  InnerWaterh = HDPETankh - 2*HDPETankThick;  
                       //Adding 3 inches (7.62 cm) to account for 6 inch steel plate above inner water  
  InnerWaterBottom = 93.65*cm;

  //Outer Ti Vessel
  OuterCryoOR = 143.75*cm;     
  OuterCryoThick = 0.635*cm;           // Full Thickness = 12.7 cm
  OuterCryoH = 130.1*cm;               // Full Height = 260.2 cm

  // Vacuum Gap Between Cryostats
  
  VacuumGapOR = OuterCryoOR - 2*OuterCryoThick;
  VacuumGapThick = 14.35*cm;
  VacuumGapH = OuterCryoH- 2*OuterCryoThick;

  //Inner Ti Vessel
  
  InnerCryoOR = VacuumGapOR - 2*VacuumGapThick;
  InnerCryoThick = 0.635*cm;
  InnerCryoH = VacuumGapH - 2*VacuumGapThick;


  //HFE

  HfeOR = InnerCryoOR - 2*InnerCryoThick;
  HfeHeight = InnerCryoH - 2*InnerCryoThick;

  //Steel Supports
  //*****These have a complicated spider-web structure, so I gave them an
  //*****effective height to include the full mass over two plates that 
  //*****span the 6 inch height of the beams used to construct it

  StSupportR = InnerWaterR;
  StSupportH = 0.303*cm;             // Full effective height = .303 cm

  //The TPC Vessel
  //More detail to be added later
  
  //  TpcThick = 0.6*cm;                 //Barrel thickness, subject to change
  TpcLength = 65.807*cm;                 //Total Length = 131.614
  TpcOR = 64.707*cm;               

  //Inactive Xenon
  
  InactiveXeR = 64.2*cm;                 //Corresponds with IR of TPC
  InactiveXeH = 65*cm;

  //Field Shaping Rings
  
  FieldRingIR = 63.01*cm;
  FieldRingOR = 63.16*cm;
  FieldRingWidth = 0.4825*cm;            // Full width .965 cm


  FieldRingLipIR = 62.95*cm;
  FieldRingLipOR = FieldRingIR;
  FieldRingLipH = 0.057*cm;               // Full width .114 cm

  //FieldRingCenterDist = 2.218*cm;        // Dist between center rings = 4.436 cm
  //DistBetweenRings = 0.2*cm + 2*FieldRingWidth;

  //Random values for reference based on scale up of EXO-200 detector
  Cathode_Anode_distance = 62.27*cm;

  //Teflon Reflector

  TReflectorIR = 62.88*cm;
  TReflectorOR = 62.95*cm;
  TReflectorH = Cathode_Anode_distance-1.13*cm;

  //APD Platters
  //Effective thickness based on scale-up from EXO-200; very preliminary

  APDPlatterR = InactiveXeR-.4*cm;
  APDPlatterThick = 0.073*cm;              //Full thickness 0.146 cm
  
  //Kapton Cables
  KCablesR = APDPlatterR;
  KCablesThick = 0.00394*cm;        //Full thickness of 7.87e-3 cm
  // Thickness calculated from EXO200 JINST paper (calculated volume, 
  // found effective thickness)

  //Teflon Insulators

  TeflonInsulatorR = APDPlatterR;
  TeflonInsulatorThick = 0.025*cm;     // Full thickness of 0.05 cm; 
    //this was approximated by taking the thickness from EXO-200, finding
    //the mass of the scaled up insulator, subtractning 1/3 of the mass
    //to account for the holes, and finding the effective thickness

  //Acrylic Field Ring Supports

  FieldSupportOR = 63.2251*cm;
  FieldSupportIR = FieldRingOR;
  FieldSupportH = Cathode_Anode_distance;


  //Active Xenon

  APD_Wire_Wire_Dist = 0.3*cm;

  ActiveXeR = TReflectorIR;
  ActiveXeH = Cathode_Anode_distance-2*APD_Wire_Wire_Dist-0.4*cm;
                                        //Fiducial Cut  


  //Placement Vector Components
  HDPEPlaceZ = HDPETankh + 2*OuterWaterBottom - OuterWaterh;
  SSupport2PlaceZ = -OuterWaterh+2*OuterWaterBottom-StSupportH;
  OuterCryoPlaceZ = OuterCryoH +2*InnerWaterBottom - InnerWaterh;
  OuterWaterPlaceZ = OuterWaterh - 2*OuterWaterBottom - 2*HDPETankThick - 2*InnerWaterBottom - OuterCryoH;

  APDPlatterPlaceZ = InactiveXeH - 1.82*cm;    //1.82 = standoff dist from EXO-200 geometry
  KCablesPlaceZ = APDPlatterPlaceZ + APDPlatterThick + KCablesThick;
  TeflonInsulatorPlaceZ = APDPlatterPlaceZ + 1.*cm;  // Put 1 cm behind APDPlatters

  //2*OuterWaterBottom+2*HDPETankThick+2*InnerWaterBottom+OuterCryoH

  // materials
  DefineMaterials();

  detectorMessenger = new nEXODetectorMessenger2(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nEXODetectorConstruction2::~nEXODetectorConstruction2()
{delete detectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* nEXODetectorConstruction2::Construct()
{
  return ConstructDetector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nEXODetectorConstruction2::DefineMaterials()
{

G4String symbol;             //a=mass of a mole;
G4double a, z, density;      //z=mean number of protons;  
//G4int iz, n;                 //iz=number of protons  in an isotope; 
                             // n=number of nucleons in an isotope;

G4int ncomponents, natoms;
G4double fractionmass;

//**************************************************//
//****************DEFINE ELEMENTS*******************//
//**************************************************//

G4Element* H  = new G4Element("Hydrogen",symbol="H" , z= 1., a= 1.01*g/mole);
G4Element* C  = new G4Element("Carbon"  ,symbol="C" , z= 6., a= 12.01*g/mole);
G4Element* N  = new G4Element("Nitrogen",symbol="N" , z= 7., a= 14.01*g/mole);
G4Element* O  = new G4Element("Oxygen"  ,symbol="O" , z= 8., a= 16.00*g/mole);
G4Element* F  = new G4Element("Fluorine",symbol="F" , z= 9., a= 19.00*g/mole);
G4Element* Mg = new G4Element("Magnesium",symbol="Mg",z= 12.,a= 24.30*g/mole);
G4Element* Si = new G4Element("Silicon",symbol="Si" ,z= 14., a= 28.09*g/mole);
G4Element* Ar = new G4Element("Argon"  ,symbol="Ar" ,z= 18., a= 39.95*g/mole);
G4Element* Ca = new G4Element("Calcium",symbol="Ca" ,z= 20., a= 40.08*g/mole);
G4Element* Ti = new G4Element("Titanium",symbol="Ti",z= 22., a= 42.867*g/mole);
G4Element* Cr = new G4Element("Chromium",symbol="Cr",z= 24., a= 52.00*g/mole);
G4Element* Fe = new G4Element("Iron"    ,symbol="Fe",z= 26., a= 55.84*g/mole);
G4Element* Ni = new G4Element("Nickel"  ,symbol="Ni",z= 28., a= 58.69*g/mole);
G4Element* Cu = new G4Element("Copper"  ,symbol="Cu",z= 29., a= 63.55*g/mole);
G4Element* Xe = new G4Element("Xenon"   ,symbol="Xe",z= 54., a= 131.29*g/mole);
G4Element* Pb = new G4Element("Lead"    ,symbol="Pb",z= 82., a= 207.2*g/mole);

//**************************************************//
//****************DEFINE MATERIALS******************//
//**************************************************//

G4Material* H2O = 
new G4Material("Water", density= 1.000*g/cm3, ncomponents=2);
H2O->AddElement(H, natoms=2);
H2O->AddElement(O, natoms=1);

G4Material* C4H3OF7 = 
new G4Material("HFE", density= 1.77*g/cm3, ncomponents=4);
C4H3OF7->AddElement(H, natoms=3);
C4H3OF7->AddElement(C, natoms=4);
C4H3OF7->AddElement(O, natoms=1);
C4H3OF7->AddElement(F, natoms=7);

G4Material* Air = new G4Material("Air",density= 1.25*mg/cm3,ncomponents=3);
Air->AddElement(N, fractionmass=0.758);
Air->AddElement(O, fractionmass=0.232);
Air->AddElement(Ar, fractionmass=0.010);

G4Material* Kapton = 
new G4Material("Kapton", density = 1.43*g/cm3, ncomponents=4);
 Kapton->AddElement(C, natoms=22);
 Kapton->AddElement(H, natoms=10);
 Kapton->AddElement(N, natoms=2);
 Kapton->AddElement(O, natoms=5);

G4Material* Concrete = 
new G4Material("concrete",density= 2.34*g/cm3, ncomponents=6);
Concrete->AddElement(C, natoms=23);
Concrete->AddElement(O, natoms=40);
Concrete->AddElement(H, natoms=10);
Concrete->AddElement(Si, natoms=12);
Concrete->AddElement(Mg, natoms=2);
Concrete->AddElement(Ca, natoms=12);

G4Material* Copper = new G4Material("Copper",density=8.96*g/cm3,ncomponents=1);
Copper->AddElement(Cu, fractionmass=1.0);

G4Material* Lead = new G4Material("Lead",density= 11.34*g/cm3,ncomponents=1);
Lead->AddElement(Pb, fractionmass=1.0);

G4Material* SStl = 
new G4Material("StainlessSteel",density= 8.*g/cm3, ncomponents=3);
SStl->AddElement(Cr, fractionmass=0.08);
SStl->AddElement(Fe, fractionmass=0.74);
SStl->AddElement(Ni, fractionmass=0.18);

G4Material* RedSStl = 
new G4Material("ReducedStainlessSteel",density= 0.462*g/cm3, ncomponents=1);
RedSStl->AddMaterial(SStl, fractionmass=1.);

G4Material* Poly = 
new G4Material("HDPE",density= 0.95*g/cm3, ncomponents=2);
Poly->AddElement(H, fractionmass=0.144);
Poly->AddElement(C, fractionmass=0.856);

G4Material* Titanium = new G4Material("Titanium",density= 4.506*g/cm3,
                       ncomponents=1);
Titanium->AddElement(Ti, fractionmass=1.0);

G4Material* Vacuum =
new G4Material("Vacuum",density= 1.e-11*g/cm3,ncomponents=1);
Vacuum->AddMaterial(Air, fractionmass=1.);

G4Material* LiquidXe1 = new G4Material("LiquidXe1",density= 3.057*g/cm3,
                       ncomponents=1);
LiquidXe1->AddElement(Xe, fractionmass=1.0);

G4Material* LiquidXe2 = new G4Material("LiquidXe2",density= 3.057*g/cm3,
                       ncomponents=1);
LiquidXe2->AddElement(Xe, fractionmass=1.0);

G4Material* Teflon = new G4Material("Teflon",density= 2.2*g/cm3,
                       ncomponents=2);
Teflon->AddElement(C, fractionmass=0.240183);
Teflon->AddElement(F, fractionmass=0.759817);

G4Material* AcrylicMaterial = new G4Material("AcrylicMaterial", 1.185*g/cm3, 3,kStateSolid, 173.15*kelvin);
AcrylicMaterial->AddElement(H, 8);
AcrylicMaterial->AddElement(O, 2);
AcrylicMaterial->AddElement(C, 5);

//**************************************************//
//****************MATERIALS OF EVERYTHING***********//
//**************************************************//

 defaultMaterial  = Vacuum;
 OuterVessel      = Copper; 
 Hdpe             = Poly;
 VacuumSpace      = Vacuum;
 InnerVessel      = Copper;
 HFEMaterial      = C4H3OF7;
 TpcMaterial      = Copper;
 MineRock         = Concrete;
 Water            = H2O;
 AIR              = Air;
 LEAD             = Lead;
 LXe              = LiquidXe1;
 ActiveLXe         = LiquidXe2;
 Acrylic          = AcrylicMaterial;
 Reflector        = Teflon;
 Insulator        = Teflon;
 SSteel           = SStl;
 Cables           = Kapton;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* nEXODetectorConstruction2::ConstructDetector()
{
  //Clean old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  //************************************************//
  //******************** World *********************//
  //************************************************//

  solidWorld = new G4Box("World", WorldSizeXYZ, WorldSizeXYZ, WorldSizeXYZ);
  
  logicWorld = new G4LogicalVolume(solidWorld,       //its solid  
				   defaultMaterial,  //its material
				   "World");         //its name

  physiWorld = new G4PVPlacement(0,                   //no rotation
				G4ThreeVector(),     //at (0,0,0) 
				logicWorld,          //its logical volume
				"World",             //its name 
				0,                   //its mother volume 
				false,               //no boolean operator
				0);                  //copy number

  //************************************************//
  //****************** The Mine ********************//
  //************************************************//
  
  solidMine = new G4Box("Mine", MineRockXYZ, MineRockXYZ, MineRockXYZ);

  logicMine = new G4LogicalVolume(solidMine, 
				  MineRock,
				  "Mine");

  physiMine = new G4PVPlacement(0,
				G4ThreeVector(),
				logicMine,
				"Mine",
				logicWorld,
				false,
				0);

  //************************************************//
  //************* Outer Water Shield ***************//
  //************************************************//

  solidOuterWater = new G4Tubs("OuterWater",
			       0,
			       OuterWaterR,
			       OuterWaterh,
			       0,
			       360*deg);

  logicOuterWater = new G4LogicalVolume(solidOuterWater,
					Water,
					"OuterWater");
  
  physiOuterWater = new G4PVPlacement(0,
				      G4ThreeVector(0,0,OuterWaterPlaceZ),
				      logicOuterWater,
				      "OuterWater",
				      logicMine,
				      false,
				      0);

  //************************************************//
  //***************** Air Cavity *******************//
  //************************************************//  

  solidAirDome = new G4Sphere("AirDome",   //Name
			      0,           //Inner Radius
			      AirDomeR,    //Outer Radius
			      0,           //Starting phi angle
			      360*deg,     //Ending phi angle
			      0,           //Starting theta angle
			      90*deg);     //Ending theta angle

  logicAirDome = new G4LogicalVolume(solidAirDome,
				     AIR,
				     "AirDome");

  physiAirDome = new G4PVPlacement(0,
				   G4ThreeVector(0,0, OuterWaterPlaceZ+OuterWaterh),
				   logicAirDome,
				   "AirDome",
				   logicMine,
				   false,
				   0);
				     


  //************************************************//
  //****************** HDPE Tank *******************//
  //************************************************//

  solidHDPETank = new G4Tubs("HDPETank",
			     0,
			     HDPETankR,
			     HDPETankh,
			     0,
			     360*deg);

  logicHDPETank = new G4LogicalVolume(solidHDPETank,
				      Hdpe,
				      "HDPETank");

  physiHDPETank = new G4PVPlacement(0,
				    G4ThreeVector(0,0, HDPEPlaceZ),
				    logicHDPETank,
				    "HDPETank",
				    logicOuterWater,
				    false,
				    0);

				   
  //************************************************//
  //************* Inner Water Shield ***************//
  //************************************************//  

  solidInnerWater = new G4Tubs("InnerWater",
			       0,
			       InnerWaterR,
			       InnerWaterh,
			       0,
			       360*deg);

  logicInnerWater = new G4LogicalVolume(solidInnerWater,
					Water,
					"InnerWater");
  
  physiInnerWater = new G4PVPlacement(0,
				      G4ThreeVector(0,0,0),
				      logicInnerWater,
				      "InnerWater",
				      logicHDPETank,
				      false,
				      0);


  //************************************************//
  //************** HDPE Tank Support ***************//
  //************************************************//

  solidStSupport2 = new G4Tubs("StSupport2",
			       0,
			       StSupportR,
			       StSupportH,
			       0,
			       360*deg);

  logicStSupport2 = new G4LogicalVolume(solidStSupport2,
					SSteel,
					"StSupport2");

  physiStSupport2[0] = new G4PVPlacement(0,
					 G4ThreeVector(0,0,SSupport2PlaceZ),
					 logicStSupport2,
					 "StSupport1",
					 logicOuterWater,
					 false,
					 2);
 
 physiStSupport2[1] = new G4PVPlacement(0,
				 G4ThreeVector(0,0,SSupport2PlaceZ-14.094*cm),
				 logicStSupport2,
				 "StSupport2",
				 logicOuterWater,
				 false,
				 2);
  
			       

  //************************************************//
  //*************** Outer Cryostat *****************//
  //************************************************//
  
  solidOuterCryo = new G4Tubs("OuterCryo",
			      0,                    //its name
			      OuterCryoOR,          //inner radius
			      OuterCryoH,           //outer radius
			      0,                    //starting phi angle
			      360*deg);             //segment angle

  logicOuterCryo = new G4LogicalVolume(solidOuterCryo,  //its solid
				       OuterVessel,     //its material
				       "OuterCryo");    //its name

  physiOuterCryo = new G4PVPlacement(0,                 //no rotation
				     G4ThreeVector(0,0,OuterCryoPlaceZ),   
				     logicOuterCryo,    //its logical volume
				     "OuterCryo",       //its name
				     logicInnerWater,   //its mother volume
				     false,             //no boolean operation
				     0);                //copy number


  //************************************************//
  //********** Vacuum Between Cryostats ************//
  //************************************************//

  solidVacuumGap = new G4Tubs("VacuumGap",
			      0,
			      VacuumGapOR,
			      VacuumGapH,
			      0,
			      360*deg);

  logicVacuumGap = new G4LogicalVolume(solidVacuumGap,
				       VacuumSpace,
				       "VacuumGap");

  physiVacuumGap = new G4PVPlacement(0,
				     G4ThreeVector(),
				     logicVacuumGap,
				     "VacuumGap",
				     logicOuterCryo,
				     false,
				     0);


  //************************************************//
  //*************** Inner Cryostat *****************//
  //************************************************//

  solidInnerCryo = new G4Tubs("InnerCryo",
			      0,
			      InnerCryoOR,
			      InnerCryoH,
			      0,
			      360*deg);

  logicInnerCryo = new G4LogicalVolume(solidInnerCryo,
				       InnerVessel,
				       "InnerCryo");

  physiInnerCryo = new G4PVPlacement(0,
				     G4ThreeVector(),
				     logicInnerCryo,
				     "InnerCryo",
				     logicVacuumGap,
				     false,
				     0);



  //************************************************//
  //******************** HFE ***********************//
  //************************************************//

  solidHFE = new G4Tubs("HFE",
			0,
			HfeOR,
			HfeHeight,
			0,
			360*deg);

  logicHFE = new G4LogicalVolume(solidHFE,
				 HFEMaterial,
				 "HFE");

  physiHFE = new G4PVPlacement(0,
			       G4ThreeVector(),
			       logicHFE,
			       "HFE",
			       logicInnerCryo,
			       false,
			       0);

  //************************************************//
  //**************** TPC Vessel ********************//
  //************************************************//

  TpcRM.rotateY(90.*deg);

  solidTPC = new G4Tubs("TPC",
			0,
			TpcOR,
			TpcLength,
			0,
			360*deg);

  logicTPC = new G4LogicalVolume(solidTPC,
				 TpcMaterial,
				 "TPC");

  physiTPC = new G4PVPlacement(&TpcRM,
			       G4ThreeVector(),
			       logicTPC,
			       "TPC",
			       logicHFE,
			       false,
			       0);

 //************************************************//
 //**************** Inactive Xe *******************//
 //************************************************//

  solidInactiveXe = new G4Tubs("InactiveXe",
			       0,
			       InactiveXeR,
			       InactiveXeH,
			       0,
			       360*deg);

  logicInactiveXe = new G4LogicalVolume(solidInactiveXe,
					LXe,
					"InactiveXe");

  physiInactiveXe = new G4PVPlacement(0,
				      G4ThreeVector(),
				      logicInactiveXe,
				      "InactiveXe",
				      logicTPC,
				      false,
				      0);

//**************************************************//
//*************** Field Shaping Rings **************//
//**************************************************//

  solidFieldRing = new G4Tubs("FieldRing",
			      FieldRingIR,
			      FieldRingOR,
			      FieldRingWidth,
			      0,
			      360*deg);

  logicFieldRing = new G4LogicalVolume(solidFieldRing,
				       TpcMaterial,
				       "FieldRing");
  
  for(int h = 0; h<60; h++){
    G4double z;
    if(h<30) z = (h-30.)*(Cathode_Anode_distance/33.);
    else z = (h-29.)*(Cathode_Anode_distance/33.);

    physiFieldRing[h] = new G4PVPlacement(0,
					  G4ThreeVector(0,0,z),
					  logicFieldRing,
					  "FieldRing",
					  logicInactiveXe,
					  false,
					  h);
      }

  solidFieldRingLip = new G4Tubs("FieldRingsLip",
				 FieldRingLipIR,
				 FieldRingLipOR,
				 FieldRingLipH,
				 0,
				 360*deg);

  logicFieldRingLip = new G4LogicalVolume(solidFieldRingLip,
					  TpcMaterial,
					  "FieldRingLip");
  
  for(int h = 0; h<60; h++){
    G4double z1, z2;
    if(h<30){ z1 = (h-30.)*(Cathode_Anode_distance/33.)-FieldRingWidth;
              z2 = (h-30.)*(Cathode_Anode_distance/33.)+FieldRingWidth;}
    else{     z1 = (h-29.)*(Cathode_Anode_distance/33.)-FieldRingWidth;
              z2 = (h-29.)*(Cathode_Anode_distance/33.)+FieldRingWidth;}
	     
    physiFieldRingLip[2*h] = new G4PVPlacement(0,
					       G4ThreeVector(0,0,z1),
					       logicFieldRingLip,
					       "FieldRingLip",
					       logicInactiveXe,
					       false,
					       h);

    physiFieldRingLip[2*h+1] = new G4PVPlacement(0,
					       G4ThreeVector(0,0,z2),
					       logicFieldRingLip,
					       "FieldRingLip",
					       logicInactiveXe,
					       false,
					       h);
  }


 //************************************************//
 //************** Teflon Reflector ****************//
 //************************************************//

  solidTReflector = new G4Tubs("TReflector",
			       TReflectorIR,
			       TReflectorOR,
			       TReflectorH,
			       0*deg,
			       360*deg);

  logicTReflector = new G4LogicalVolume(solidTReflector,
					Reflector,
					"TReflector");
  
  physiTReflector = new G4PVPlacement(0,
				      G4ThreeVector(),
				      logicTReflector,
				      "TReflector",
				      logicInactiveXe,
				      false,
				      0);

//**************************************************//
//****************** APD Platters ******************//
//**************************************************//

  solidAPDPlatter = new G4Tubs("APDPlatter",
			       0,
			       APDPlatterR,
			       APDPlatterThick,
			       0*deg,
			       360*deg);

  logicAPDPlatter = new G4LogicalVolume(solidAPDPlatter,
					TpcMaterial,
					"APDPlatter");

  physiAPDPlatter[0] = new G4PVPlacement(0,
					 G4ThreeVector(0,0,APDPlatterPlaceZ),
					 logicAPDPlatter,
					 "APDPlatter",
					 logicInactiveXe,
					 false,
					 2);
  physiAPDPlatter[1] = new G4PVPlacement(0,
					 G4ThreeVector(0,0,-APDPlatterPlaceZ),
					 logicAPDPlatter,
					 "APDPlatter",
					 logicInactiveXe,
					 false,
					 2);

//**************************************************//
//****************** Kapton Cables *****************//
//**************************************************//

  solidKCables = new G4Tubs("KCables",
			    0,
			    KCablesR,
			    KCablesThick,
			    0*deg,
			    360*deg);

  logicKCables = new G4LogicalVolume(solidKCables,
				     Cables,
				     "KCables");

  physiKCables[0] = new G4PVPlacement(0,
				      G4ThreeVector(0,0,KCablesPlaceZ),
				      logicKCables,
				      "KCables",
				      logicInactiveXe,
				      false,
				      2);

  physiKCables[1] = new G4PVPlacement(0,
				      G4ThreeVector(0,0,-KCablesPlaceZ),
				      logicKCables,
				      "KCables",
				      logicInactiveXe,
				      false,
				      2);

//**************************************************//
//*************** Field Ring Supports **************//
//**************************************************//
  // AcrylicRM.rotateZ(90*deg);

    solidFieldSupport = new G4Tubs("FieldSupport",
				   FieldSupportIR,
				   FieldSupportOR,
				   FieldSupportH,
				   0*deg,
				   360*deg);

    logicFieldSupport = new G4LogicalVolume(solidFieldSupport,
					    Acrylic,
					    "FieldSupport");

    physiFieldSupport = new G4PVPlacement(0,
					  G4ThreeVector(),
					  logicFieldSupport,
					  "FieldSupport",
					  logicInactiveXe,
					  false,
					  0);

//**************************************************//
//**************** Teflon Insulators ***************//
//**************************************************//

    solidTeflonInsulator = new G4Tubs("TeflonInsulator",
				      0,
				      TeflonInsulatorR,
				      TeflonInsulatorThick,
				      0,
				      360*deg);

    logicTeflonInsulator = new G4LogicalVolume(solidTeflonInsulator,
					       Insulator,
					       "TeflonInsulator");

    physiTeflonInsulator[0] = new G4PVPlacement(0,
					     G4ThreeVector(0,0,TeflonInsulatorPlaceZ),
					     logicTeflonInsulator,
					     "TeflonInsulator",
					     logicInactiveXe,
					     false,
					     0);

    physiTeflonInsulator[1] = new G4PVPlacement(0,
					     G4ThreeVector(0,0,-TeflonInsulatorPlaceZ),
					     logicTeflonInsulator,
					     "TeflonInsulator",
					     logicInactiveXe,
					     false,
					     2);
					     
					       

 //************************************************//
 //****************** Active Xe *******************//
 //************************************************//

    solidActiveXe = new G4Tubs("ActiveXe",
			       0,
			       ActiveXeR,
			       ActiveXeH,
			       0,
			       360*deg);

    logicActiveXe = new G4LogicalVolume(solidActiveXe,
					ActiveLXe,
					"ActiveXe");
    
    physiActiveXe = new G4PVPlacement(0,
				      G4ThreeVector(),
				      logicActiveXe,
				      "ActiveXe",
				      logicInactiveXe,
				      false,
				      0);
					

  

//**************************************************//
//************ VISUALIZATION ATTRIBUTES ************//
//**************************************************//

// Attributes of the World
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);

//Attributes of the Mine
  G4VisAttributes* MineAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
  MineAtt->SetVisibility(true);
  MineAtt->SetForceWireframe(true);
  logicMine->SetVisAttributes(MineAtt);
  logicAirDome->SetVisAttributes(MineAtt);

//Attributes of Air Dome
  G4VisAttributes* AirAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5));
  AirAtt->SetVisibility(true);
  //AirAtt->SetForceSolid(true);
  logicAirDome->SetVisAttributes(AirAtt);

//Attributes of the Water Sheilds
  G4VisAttributes* WaterAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
  WaterAtt->SetVisibility(true);
  //  WaterAtt->SetForceSolid(true);  
  logicOuterWater->SetVisAttributes(WaterAtt);
  logicInnerWater->SetVisAttributes(WaterAtt);

//Attributes of the HDPE tank
  G4VisAttributes* HdpeAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  HdpeAtt->SetVisibility(true);
  //HdpeAtt->SetForceSolid(true);
  //HdpeAtt->SetForceWireframe(true);
  logicHDPETank->SetVisAttributes(HdpeAtt);

//Attributes of Stainless Steel
  G4VisAttributes* StStAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
  StStAtt->SetVisibility(true);
  //StStAtt->SetForceSolid(true);
  logicStSupport2->SetVisAttributes(StStAtt);

//Attributes of the Cryostats
  G4VisAttributes* CryoAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
  CryoAtt->SetVisibility(true);
  logicOuterCryo->SetVisAttributes(CryoAtt);
  logicInnerCryo->SetVisAttributes(CryoAtt);

//Attributes of the TPC
  G4VisAttributes *tpcAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));
  tpcAtt->SetVisibility(true);
  //tpcAtt->SetForceSolid(true);
  logicTPC->SetVisAttributes(tpcAtt);

//Attributes of the Inactive LXe
  G4VisAttributes *IXeAtt = new G4VisAttributes(G4Colour(1.0, 0, 1.0));
  IXeAtt->SetVisibility(true);
  //  XeAtt->SetForceSolid(true);
  logicInactiveXe->SetVisAttributes(IXeAtt);

//Attributes of Field Rings
  G4VisAttributes *RingsAtt = new G4VisAttributes(G4Colour(1.0, 0.5, 0.5));
  RingsAtt->SetVisibility(false);
  //RingsAtt->SetForceSolid(true);
  logicFieldRing->SetVisAttributes(RingsAtt);
  logicFieldRingLip->SetVisAttributes(RingsAtt);

//Attributes of the Active LXe
  G4VisAttributes *AXeAtt = new G4VisAttributes(G4Colour(0, 1.0, 0.5));
  AXeAtt->SetVisibility(true);
  //AXeAtt->SetForceSolid(true);
  logicActiveXe->SetVisAttributes(AXeAtt);
  

//Attributes of Teflon Reflector
  G4VisAttributes *RefAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));
  RefAtt->SetVisibility(true);
  //RefAtt->SetForceSolid(true);
  logicTReflector->SetVisAttributes(RefAtt);

//Attributes of APD Platters
  G4VisAttributes *APDPlattAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  APDPlattAtt->SetVisibility(true);
  APDPlattAtt->SetForceSolid(true);
  logicAPDPlatter->SetVisAttributes(APDPlattAtt);
  
//Attributes of the Acrylic Field Ring Supports
  G4VisAttributes *AcrylicAtt = new G4VisAttributes(G4Colour(0, 0, 1.0));
  AcrylicAtt->SetVisibility(true);
  //AcrylicAtt->SetForceSolid(true);
  logicFieldSupport->SetVisAttributes(AcrylicAtt);
  
  return physiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "G4RunManager.hh"

void nEXODetectorConstruction2::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructDetector());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
