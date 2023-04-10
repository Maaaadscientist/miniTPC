////////////////////////////////////////////////////////
// nEXODetectorConstruction.cc
// Coarse nEXO Geometry
// No Barium Tagging area
//    .446 cm TPC wall thickness
//
// Square cylinder cryostats
////////////////////////////////////////////////////////

//Added Kapton Cables, Teflon behind APDs

#include "nEXODetectorConstruction.hh"
#include "nEXODetectorMessenger.hh"

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
nEXODetectorConstruction::nEXODetectorConstruction()  
{
//materials
defaultMaterial=0,
//objects
  solidWorld=0; logicWorld=0; physiWorld=0;
  solidMine=0; logicMine=0; physiMine=0;
  solidAirDome=0; logicAirDome=0; physiAirDome=0;
  solidOuterWater1=0; logicOuterWater1=0; physiOuterWater1=0;
  solidOuterWater2=0; logicOuterWater2=0; physiOuterWater2=0;
  solidHDPETank=0; logicHDPETank=0; physiHDPETank=0;
  solidInnerWater1=0; logicInnerWater1=0; physiInnerWater1=0;
  solidInnerWater2=0; logicInnerWater2=0; physiInnerWater2=0;
  //  solidStSupport2=0; logicStSupport2=0; physiStSupport2[0]=0; 
  //  physiStSupport2[1]=0;
  solidOuterCryo=0; logicOuterCryo=0; physiOuterCryo=0;
  solidInnerCryo=0; logicInnerCryo=0; physiInnerCryo=0;
  solidVacuumGap=0; logicVacuumGap=0; physiVacuumGap=0;
   solidHFE=0; logicHFE=0; physiHFE=0;
   solidTPC=0; logicTPC=0; physiTPC=0;
   solidInactiveLXe=0; logicInactiveLXe=0; physiInactiveLXe=0;
   solidFieldRing=0; logicFieldRing=0; for(int h=0; h<60; h++){physiFieldRing[h]=0;}
   solidFieldRingLip=0; logicFieldRingLip=0; for(int h=0; h<60; h++){physiFieldRingLip[h]=0;}
   solidFieldSupport=0; logicFieldSupport=0; physiFieldSupport=0;
   solidTReflector=0; logicTReflector=0; physiTReflector=0; 
   solidAPDPlatter=0; logicAPDPlatter=0; physiAPDPlatter[0]=0; physiAPDPlatter[1]=0; 
   solidSiPMs = 0; logicSiPMs = 0; physiSiPMs[0] = 0; physiSiPMs[1] = 0;
   solidKCables=0; logicKCables=0; physiKCables[0]=0; physiKCables[1]=0;
   solidTeflonInsulator=0; logicTeflonInsulator=0; physiTeflonInsulator[0]=0; physiTeflonInsulator[1]=0;
   solidActiveLXe=0; logicActiveLXe=0; physiActiveLXe=0;

   //      fCryostatRegion = 0; fTPCRegion = 0;
   
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

  // Surrounding 2 m of rock
  SurroundRockR = 955*cm;               // For 2 m of U&Th decays
  SurroundRockh = 845*cm; 
  SurroundRockPlaceZ = -110*cm;

  // Shotcrete
  ShotcreteR = 755*cm;
  Shotcreteh = 735*cm;                  //Full height = 1470 cm
  ShotcretePlaceZ = SurroundRockh - Shotcreteh;

  //Floor
  FloorR = ShotcreteR;
  Floorh = 110*cm;                     //Full height = 2.2 m
  FloorPlaceZ = Floorh - SurroundRockh;

  //Inner Water Shield
  InnerWater1R = 440.*cm;
  InnerWater1h = 440.*cm;
  InnerWater1PlaceZ = 0.;

  InnerWater2R = 326.*cm;
  InnerWater2h = 326.*cm;
  InnerWater2PlaceZ = 0.;

  //HDPE Tank
  HDPETankThick = 12.5*cm;                    //Full thickness = 25 cm
  HDPETankR = InnerWater1R+2*HDPETankThick;
  HDPETankh = InnerWater1h+2*HDPETankThick;    
  HDPETankPlaceZ = 0.;
 

  //**************************************************//
  // 2 separate water shields for calculating fluxes
  // halfway through the water
  //**************************************************//

  //Outer Water Shield1
  OuterWater1R = 735.*cm;
  //  OuterWaterThick = 148.5*cm;        // Full thickness 297 cm
  OuterWater1h = 735.*cm;              // Full height = 1550.1 cm 
  OuterWaterPlace1Z = Shotcreteh - OuterWater1h;

  //Outer Water Shield2
  OuterWater2R = (OuterWater1R + HDPETankR)/2.; //halfway through OW tank
  OuterWater2h = (OuterWater1h + HDPETankh)/2.; //halfway through OW tank

  //Air Cavity
  RockDomeR = SurroundRockR;
  SCDomeR = ShotcreteR;
  AirDomeR = OuterWater1R;


  VesselThickness = 2.43*cm;

  //Outer Ti Vessel
  OuterCryoOR = 187*cm;     
  OuterCryoThick = VesselThickness; 
  OuterCryoH = 187*cm;               

  // Vacuum Gap Between Cryostats
  
  VacuumGapOR = OuterCryoOR - 2*OuterCryoThick;
  VacuumGapThick = 14.35*cm;                       //Full thickness 28.7 cm
  VacuumGapH = OuterCryoH- 2*OuterCryoThick;

  //Inner Ti Vessel
  
  InnerCryoOR = VacuumGapOR - 2*VacuumGapThick;
  InnerCryoThick = VesselThickness;  
  InnerCryoH = VacuumGapH - 2*VacuumGapThick;


  //HFE

  HfeOR = InnerCryoOR - 2*InnerCryoThick;
  HfeHeight = InnerCryoH - 2*InnerCryoThick;

  //Steel Supports
  //*****These have a complicated spider-web structure, so I gave them an
  //*****effective height to include the full mass over two plates that 
  //*****span the 6 inch height of the beams used to construct it

  //  StSupportR = InnerWaterR;
  //StSupportH = 0.303*cm;             // Full effective height = .303 cm

  //The TPC Vessel
  //More detail to be added later
  
  TpcLength = 65.66*cm;                 
  TpcOR = 65.3*cm;               

  //Liquid Xenon
  
  InactiveLXeR = 65.*cm;                 //Corresponds with IR of TPC
  InactiveLXeH = 65.*cm;

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

  TReflectorIR = 62.80*cm;
  TReflectorOR = 62.95*cm;
  TReflectorH = Cathode_Anode_distance-1.13*cm;

  //APD Platters
  //Effective thickness based on scale-up from EXO-200; very preliminary

  APDPlatterR = InactiveLXeR-0.4*cm;
  APDPlatterThick = 0.073*cm;              //Full thickness 0.146 cm

  SiPMR = APDPlatterR;
  SiPMThick = 0.05*cm;                   //Full thickness 0.5 mm
  // Increased thickenss by 2 and decreased density by 2.  
  // Actual Thickness of 0.05 cm 

  //Kapton Cables
  KCablesR = APDPlatterR;
  //  KCablesThick = 0.00394*cm;        //Full thickness of 7.87e-3 cm
  KCablesThick = 0.0394*cm;          
  // Thickness calculated from EXO200 JINST paper (calculated volume, 
  // found effective thickness)

  //Teflon Insulators

  TeflonInsulatorR = APDPlatterR;
  // Increase thickness by 2 and decrease density by 2 so that the
  // volume can be confined to
  TeflonInsulatorThick = 0.05*cm;     // Full thickness of 0.05 cm; 
    //this was approximated by taking the thickness from EXO-200, finding
    //the mass of the scaled up insulator, subtractning 1/3 of the mass
    //to account for the holes, and finding the effective thickness

  //Acrylic Field Ring Supports

  FieldSupportOR = 63.2251*cm;
  FieldSupportIR = FieldRingOR;
  FieldSupportH = Cathode_Anode_distance;


  //Active Xenon

  APD_Wire_Wire_Dist = 0.3*cm;

  //  ActiveXeR = TReflectorIR - 1.5*cm;
  //  ActiveXeH = Cathode_Anode_distance-2*APD_Wire_Wire_Dist-1.0*cm;
                                        //Fiducial Cut  


  APDPlatterPlaceZ = InactiveLXeH - 1.82*cm;    //1.82 = standoff dist from EXO-200 geometry
  KCablesPlaceZ = APDPlatterPlaceZ + 2*APDPlatterThick + KCablesThick;
  TeflonInsulatorPlaceZ = APDPlatterPlaceZ + 1.*cm;  // Put 1 cm behind APDPlatters
  SiPMPlaceZ = APDPlatterPlaceZ - APDPlatterThick - SiPMThick;


  ActiveLXeR = TReflectorIR;
  //  ActiveLXeH = APDPlatterPlaceZ - APDPlatterThick - .007; 
  ActiveLXeH = APDPlatterPlaceZ - APDPlatterThick; 
  // Total Volume of Active Xe = 62.8^2*63.1*2pi = 1.564x10^6 cm^3 


  // Placement Vectors


  //2*OuterWaterBottom+2*HDPETankThick+2*InnerWaterBottom+OuterCryoH

  // materials
  DefineMaterials();

  detectorMessenger = new nEXODetectorMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
nEXODetectorConstruction::~nEXODetectorConstruction()
{delete detectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4VPhysicalVolume* nEXODetectorConstruction::Construct()
{
  return ConstructDetector();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void nEXODetectorConstruction::DefineMaterials()
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
G4Element* Na = new G4Element("Sodium",  symbol="Na",z= 11.,a= 22.99*g/mole);
G4Element* Mg = new G4Element("Magnesium",symbol="Mg",z= 12.,a= 24.30*g/mole);
G4Element* Al = new G4Element("Aluminum",symbol="Al" ,z= 13.,a= 26.98*g/mole);
G4Element* Si = new G4Element("Silicon",symbol="Si" ,z= 14., a= 28.09*g/mole);
G4Element* Ar = new G4Element("Argon"  ,symbol="Ar" ,z= 18., a= 39.95*g/mole);
G4Element* K  = new G4Element("Potassium",symbol="K" ,z= 19., a= 39.10*g/mole);
G4Element* Ca = new G4Element("Calcium",symbol="Ca" ,z= 20., a= 40.08*g/mole);
G4Element* Ti = new G4Element("Titanium",symbol="Ti",z= 22., a= 42.867*g/mole);
G4Element* Cr = new G4Element("Chromium",symbol="Cr",z= 24., a= 52.00*g/mole);
G4Element* Mn = new G4Element("Manganese",symbol="Mn",z= 25.,a= 54.94*g/mole);
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

G4Material* Air = new G4Material("Air",density= 1.25*mg/cm3,ncomponents=3);
Air->AddElement(N, fractionmass=0.758);
Air->AddElement(O, fractionmass=0.232);
Air->AddElement(Ar, fractionmass=0.010);


G4Material* ShotCrete = new G4Material("ShotCrete",density=2.32*g/cm3,ncomponents=9);
ShotCrete->AddElement(Al, fractionmass=0.061);
ShotCrete->AddElement(Ca, fractionmass=0.096);
ShotCrete->AddElement(Fe, fractionmass=0.026);
ShotCrete->AddElement(K, fractionmass=0.018);
ShotCrete->AddElement(Mg, fractionmass=0.012);
ShotCrete->AddElement(Mn, fractionmass=0.004);
ShotCrete->AddElement(Na, fractionmass=0.023);
ShotCrete->AddElement(Si, fractionmass=0.28);
ShotCrete->AddElement(O, fractionmass=0.48);

G4Material* Concrete = new G4Material("Concrete",density=2.32*g/cm3,ncomponents=9);
Concrete->AddElement(Al, fractionmass=0.060);
Concrete->AddElement(Ca, fractionmass=0.101);
Concrete->AddElement(Fe, fractionmass=0.026);
Concrete->AddElement(K, fractionmass=0.017);
Concrete->AddElement(Mg, fractionmass=0.012);
Concrete->AddElement(Mn, fractionmass=0.004);
Concrete->AddElement(Na, fractionmass=0.023);
Concrete->AddElement(Si, fractionmass=0.277);
Concrete->AddElement(O, fractionmass=0.48);

G4Material* Rock = new G4Material("Rock",density=2.32*g/cm3,ncomponents=9);
Rock->AddElement(Al, fractionmass=0.060);
Rock->AddElement(Ca, fractionmass=0.101);
Rock->AddElement(Fe, fractionmass=0.026);
Rock->AddElement(K, fractionmass=0.017);
Rock->AddElement(Mg, fractionmass=0.012);
Rock->AddElement(Mn, fractionmass=0.004);
Rock->AddElement(Na, fractionmass=0.023);
Rock->AddElement(Si, fractionmass=0.277);
Rock->AddElement(O, fractionmass=0.48);

G4Material* C4H3OF7 = 
new G4Material("HFE", density= 1.77*g/cm3, ncomponents=4);
C4H3OF7->AddElement(H, natoms=3);
C4H3OF7->AddElement(C, natoms=4);
C4H3OF7->AddElement(O, natoms=1);
C4H3OF7->AddElement(F, natoms=7);

G4Material* Kapton = 
new G4Material("Kapton", density = 0.143*g/cm3, ncomponents=4);
//Should be 1.43g/cm3, but had to increase the volume by 10 so am decreasing the density by 10.
 Kapton->AddElement(C, natoms=22);
 Kapton->AddElement(H, natoms=10);
 Kapton->AddElement(N, natoms=2);
 Kapton->AddElement(O, natoms=5);

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

G4Material* LiquidXe = new G4Material("LiquidXe",density= 3.057*g/cm3,
                       ncomponents=1);
LiquidXe->AddElement(Xe, fractionmass=1.0);

G4Material* Teflon = new G4Material("Teflon",density= 2.2*g/cm3,
                       ncomponents=2);
Teflon->AddElement(C, fractionmass=0.240183);
Teflon->AddElement(F, fractionmass=0.759817);

G4Material* TeflonDecrease = new G4Material("TeflonDecrease",density= 1.1*g/cm3,
                       ncomponents=2);
TeflonDecrease->AddElement(C, fractionmass=0.240183);
TeflonDecrease->AddElement(F, fractionmass=0.759817);



G4Material* AcrylicMaterial = new G4Material("AcrylicMaterial", 1.185*g/cm3, 3,kStateSolid, 173.15*kelvin);
AcrylicMaterial->AddElement(H, 8);
AcrylicMaterial->AddElement(O, 2);
AcrylicMaterial->AddElement(C, 5);

 G4Material* SiliconMaterial = new G4Material("SiliconMaterial", density = 1.165*g/cm3, ncomponents = 1);
 SiliconMaterial->AddElement(Si, fractionmass = 1.0);
 //Density decreased by a factor of 2 (should be 2.33) to account for increased
 //thickness so that G4 recongizes the volume

//**************************************************//
//****************MATERIALS OF EVERYTHING***********//
//**************************************************//

 defaultMaterial  = Vacuum;
 Hdpe             = Poly;
 VacuumSpace      = Vacuum;
 MineRock         = Rock;
 Coating          = ShotCrete;
 Floor            = Concrete;
 Water1           = H2O;
 Water2           = H2O; 
 WaterInner1      = H2O;
 WaterInner2      = H2O;
 OuterVessel      = Copper;
 InnerVessel      = Copper;
 AIR              = Air;
 HFEMaterial      = C4H3OF7;
 TpcMaterial      = Copper;
 Water            = H2O;
 AIR              = Air;
 LEAD             = Lead;
 LXe              = LiquidXe;
 Acrylic          = AcrylicMaterial;
 Reflector        = Teflon;
 Insulator        = TeflonDecrease;
 SSteel           = SStl;
 Cables           = Kapton;
 SiPMMaterial     = SiliconMaterial;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
 
G4VPhysicalVolume* nEXODetectorConstruction::ConstructDetector()
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
  //*************** SurroundRock *******************//
  //************************************************//

  solidSurroundRock = new G4Tubs("SurroundRock",
			       0,
			       SurroundRockR,
			       SurroundRockh,
			       0,
			       360*deg);

  logicSurroundRock = new G4LogicalVolume(solidSurroundRock,
					MineRock,
					"SurroundRock");
  
  physiSurroundRock = new G4PVPlacement(0,
				     G4ThreeVector(0,0,SurroundRockPlaceZ),
				      logicSurroundRock,
				      "SurroundRock",
				      logicMine,
				      false,
				      0);

  //************************************************//
  //************* Shotcrete Coating ****************//
  //************************************************//

  solidShotcrete = new G4Tubs("Shotcrete",
			       0,
			       ShotcreteR,
			       Shotcreteh,
			       0,
			       360*deg);

  logicShotcrete = new G4LogicalVolume(solidShotcrete,
					Coating,
					"Shotcrete");
  
  physiShotcrete = new G4PVPlacement(0,
				      G4ThreeVector(0,0,ShotcretePlaceZ),
				      logicShotcrete,
				      "Shotcrete",
				      logicSurroundRock,
				      false,
				      0);

  //************************************************//
  //******************* Floor **********************//
  //************************************************//

  solidFLOOR = new G4Tubs("FLOOR",
			       0,
			       FloorR,
			       Floorh,
			       0,
			       360*deg);

  logicFLOOR = new G4LogicalVolume(solidFLOOR,
				   Floor,
				   "FLOOR");
  
  physiFLOOR = new G4PVPlacement(0,
				 G4ThreeVector(0,0,FloorPlaceZ),
				 logicFLOOR,
				 "FLOOR",
				 logicSurroundRock,
				 false,
				 0);

  //************************************************//
  //************* Outer Water Shield 1 *************//
  //************************************************//

  solidOuterWater1 = new G4Tubs("OuterWater1",
			       0,
			       OuterWater1R,
			       OuterWater1h,
			       0,
			       360*deg);

  logicOuterWater1 = new G4LogicalVolume(solidOuterWater1,
					Water1,
					"OuterWater1");
  
  physiOuterWater1 = new G4PVPlacement(0,
				      G4ThreeVector(0,0,OuterWaterPlace1Z),
				      logicOuterWater1,
				      "OuterWater1",
				      logicShotcrete,
				      false,
				      0);

  //************************************************//
  //************* Outer Water Shield 2 *************//
  //************************************************//

  solidOuterWater2 = new G4Tubs("OuterWater2",
			       0,
			       OuterWater2R,
			       OuterWater2h,
			       0,
			       360*deg);

  logicOuterWater2 = new G4LogicalVolume(solidOuterWater2,
					Water2,
					"OuterWater2");
  
  physiOuterWater2 = new G4PVPlacement(0,
				      G4ThreeVector(0,0,OuterWaterPlace2Z),
				      logicOuterWater2,
				      "OuterWater2",
				      logicOuterWater1,
				      false,
				      0);

  //************************************************//
  //******** Air Cavity Surrounding Rock  **********//
  //************************************************//  

  
  solidRockDome = new G4Sphere("RockDome",   //Name
			      0,           //Inner Radius
			      RockDomeR,    //Outer Radius
			      0,           //Starting phi angle
			      360*deg,     //Ending phi angle
			      0,           //Starting theta angle
			      90*deg);     //Ending theta angle

  logicRockDome = new G4LogicalVolume(solidRockDome,
				      MineRock,
				     "RockDome");

  physiRockDome = new G4PVPlacement(0,
				    G4ThreeVector(0,0,SurroundRockPlaceZ+SurroundRockh),
				   logicRockDome,
				   "RockDome",
				   logicMine,
				   false,
				   0);

  //************************************************//
  //************* Air Cavity Coating ***************//
  //************************************************//  

  solidShotDome = new G4Sphere("ShotDome",   //Name
			      0,           //Inner Radius
			      SCDomeR,    //Outer Radius
			      0,           //Starting phi angle
			      360*deg,     //Ending phi angle
			      0,           //Starting theta angle
			      90*deg);     //Ending theta angle

  logicShotDome = new G4LogicalVolume(solidShotDome,
				     Coating,
				     "ShotDome");

  physiShotDome = new G4PVPlacement(0,
				    G4ThreeVector(0,0,0),
				   logicShotDome,
				   "ShotDome",
				   logicRockDome,
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
				   G4ThreeVector(0,0,0),
				   logicAirDome,
				   "AirDome",
				   logicShotDome,
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
				    G4ThreeVector(0,0, HDPETankPlaceZ),
				    logicHDPETank,
				    "HDPETank",
				    logicOuterWater2,
				    false,
				    0);

				   
  //************************************************//
  //************ Inner Water Shield 1 **************//
  //************************************************//  

  solidInnerWater1 = new G4Tubs("InnerWater1",
			       0,
			       InnerWater1R,
			       InnerWater1h,
			       0,
			       360*deg);

  logicInnerWater1 = new G4LogicalVolume(solidInnerWater1,
					WaterInner1,
					"InnerWater1");
  
  physiInnerWater1 = new G4PVPlacement(0,
				      G4ThreeVector(0,0,InnerWater1PlaceZ),
				      logicInnerWater1,
				      "InnerWater1",
				      logicHDPETank,
				      false,
				      0);

  //************************************************//
  //************ Inner Water Shield 2 **************//
  //************************************************//  

  solidInnerWater2 = new G4Tubs("InnerWater2",
			       0,
			       InnerWater2R,
			       InnerWater2h,
			       0,
			       360*deg);

  logicInnerWater2 = new G4LogicalVolume(solidInnerWater2,
					WaterInner2,
					"InnerWater2");
  
  physiInnerWater2 = new G4PVPlacement(0,
				      G4ThreeVector(0,0,InnerWater2PlaceZ),
				      logicInnerWater2,
				      "InnerWater2",
				      logicInnerWater1,
				      false,
				      0);

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
				     G4ThreeVector(0,0,0),   
				     logicOuterCryo,    //its logical volume
				     "OuterCryo",       //its name
				     logicInnerWater2,   //its mother volume
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
 //************* Inactive Liquid Xe ***************//
 //************************************************//

  solidInactiveLXe = new G4Tubs("InactiveLXe",
			       0,
			       InactiveLXeR,
			       InactiveLXeH,
			       0,
			       360*deg);

  logicInactiveLXe = new G4LogicalVolume(solidInactiveLXe,
					LXe,
					"InactiveLXe");

  physiInactiveLXe = new G4PVPlacement(0,
				      G4ThreeVector(),
				      logicInactiveLXe,
				      "InactiveLXe",
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
					  logicInactiveLXe,
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
					       logicInactiveLXe,
					       false,
					       h);

    physiFieldRingLip[2*h+1] = new G4PVPlacement(0,
					       G4ThreeVector(0,0,z2),
					       logicFieldRingLip,
					       "FieldRingLip",
					       logicInactiveLXe,
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
				      logicInactiveLXe,
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
					 logicInactiveLXe,
					 false,
					 2);
  physiAPDPlatter[1] = new G4PVPlacement(0,
					 G4ThreeVector(0,0,-APDPlatterPlaceZ),
					 logicAPDPlatter,
					 "APDPlatter",
					 logicInactiveLXe,
					 false,
					 2);

//**************************************************//
//********************** SiPMs *********************//
//**************************************************//
/*
  solidSiPMs = new G4Tubs("SiPMs",
			  0,
			  SiPMR,
			  SiPMThick,
			  0*deg,
			  360*deg);

  logicSiPMs = new G4LogicalVolume(solidSiPMs,
				   SiPMMaterial,
				   "SiPMs");

  physiSiPMs[0] = new G4PVPlacement(0,
				    G4ThreeVector(0,0,SiPMPlaceZ),
				    logicSiPMs,
				    "SiPMs",
				    logicInactiveLXe,
				    false,
				    2);

  physiSiPMs[1] = new G4PVPlacement(0,
				    G4ThreeVector(0,0,-SiPMPlaceZ),
				    logicSiPMs,
				    "SiPMs",
				    logicInactiveLXe,
				    false,
				    2);
*/

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
				      logicInactiveLXe,
				      false,
				      2);

  physiKCables[1] = new G4PVPlacement(0,
				      G4ThreeVector(0,0,-KCablesPlaceZ),
				      logicKCables,
				      "KCables",
				      logicInactiveLXe,
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
					  logicInactiveLXe,
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
					      logicInactiveLXe,
					     false,
					     0);

    physiTeflonInsulator[1] = new G4PVPlacement(0,
					     G4ThreeVector(0,0,-TeflonInsulatorPlaceZ),
					     logicTeflonInsulator,
					     "TeflonInsulator",
					     logicInactiveLXe,
					     false,
					     2);
					     
					       
 //************************************************//
 //*************** Active Liquid Xe ***************//
 //************************************************//

  solidActiveLXe = new G4Tubs("ActiveLXe",
			       0,
			       ActiveLXeR,
			       ActiveLXeH,
			       0,
			       360*deg);

  logicActiveLXe = new G4LogicalVolume(solidActiveLXe,
					LXe,
					"ActiveLXe");

  physiActiveLXe = new G4PVPlacement(0,
				      G4ThreeVector(),
				      logicActiveLXe,
				      "ActiveLXe",
				      logicInactiveLXe,
				      false,
				      0);



    //  if(fCryostatRegion !=0) delete fCryostatRegion;
    //if(fCryostatRegion == 0) 
  G4Region*  fCryostatRegion = new G4Region("CryostatRegion");
  fCryostatRegion->AddRootLogicalVolume(logicOuterCryo);

  //  if(fTPCRegion !=0) delete fTPCRegion;
  //if(fTPCRegion == 0) 
  G4Region* fTPCRegion = new G4Region("TPCRegion");
  fTPCRegion->AddRootLogicalVolume(logicTPC);

  

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
  logicOuterWater1->SetVisAttributes(WaterAtt);
  logicOuterWater2->SetVisAttributes(WaterAtt);
  logicInnerWater1->SetVisAttributes(WaterAtt);
  logicInnerWater2->SetVisAttributes(WaterAtt);

//Attributes of the HDPE tank
  G4VisAttributes* HdpeAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  HdpeAtt->SetVisibility(true);
  //HdpeAtt->SetForceSolid(true);
  //HdpeAtt->SetForceWireframe(true);
  logicHDPETank->SetVisAttributes(HdpeAtt);

//Attributes of Stainless Steel
/*  G4VisAttributes* StStAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
  StStAtt->SetVisibility(true);
  //StStAtt->SetForceSolid(true);
  logicStSupport2->SetVisAttributes(StStAtt);*/

//Attributes of the Cryostats
  G4VisAttributes* CryoAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  CryoAtt->SetVisibility(true);
  logicOuterCryo->SetVisAttributes(CryoAtt);
  logicInnerCryo->SetVisAttributes(CryoAtt);

//Attributes of the TPC
  G4VisAttributes *tpcAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0));
  tpcAtt->SetVisibility(true);
  //tpcAtt->SetForceSolid(true);
  logicTPC->SetVisAttributes(tpcAtt);

//Attributes of the LXe
  G4VisAttributes *XeAtt = new G4VisAttributes(G4Colour(1.0, 0, 1.0));
  XeAtt->SetVisibility(true);
  //  XeAtt->SetForceSolid(true);
  logicInactiveLXe->SetVisAttributes(XeAtt);

//Attributes of Field Rings
  G4VisAttributes *RingsAtt = new G4VisAttributes(G4Colour(1.0, 0.5, 0.5));
  RingsAtt->SetVisibility(false);
  RingsAtt->SetForceSolid(true);
  logicFieldRing->SetVisAttributes(RingsAtt);
  logicFieldRingLip->SetVisAttributes(RingsAtt);

  

//Attributes of Teflon Reflector
  G4VisAttributes *RefAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));
  RefAtt->SetVisibility(true);
  //  RefAtt->SetForceSolid(true);
  logicTReflector->SetVisAttributes(RefAtt);



//Attributes of Teflon Insulators
  G4VisAttributes *InsAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));  
  InsAtt->SetVisibility(true);
  //  InsAtt->SetForceSolid(true);
  logicTeflonInsulator->SetVisAttributes(InsAtt);

//Attributes of Kapton Cables
  G4VisAttributes *KCaAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));  
  KCaAtt->SetVisibility(true);
  //KCaAtt->SetForceSolid(true);
  logicKCables->SetVisAttributes(KCaAtt);




//Attributes of APD Platters
  G4VisAttributes *APDPlattAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
  APDPlattAtt->SetVisibility(true);
  //APDPlattAtt->SetForceSolid(true);
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

void nEXODetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructDetector());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
