#include "miniTPCDetectorConstruction.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "nEXOMaterials.hh"
#include "nEXOSimplePhysVolManager.hh"

miniTPCDetectorConstruction::miniTPCDetectorConstruction()
{
  fDetectorMessenger = new miniTPCDetectorMessenger(this);
  
  fSliceAngle = 360.*deg;
  
  fCheckOverlaps = false;
  fRingArrangeID = 20;
  fSiPMOption = 0;
  fWavelengthRef = 178;
  
  fTeflonRef = 0.95;
  fTPCVesselRef = 0.0;
  fSTeflonRef = 0.95;
  fSTPCVesselRef = 0.0;
  fFieldRingRef = 0.86; // From Au surface of rings
  fCathodeRef = 0.8;
  fBulgeRef = 0.8;
  fAnodeRef = 0.5;
  
  fSTPCRadius = 7.5*cm;
  fSTPCVesselSideThickness = 0.2*cm;
  fSTPCHalfheight = 6.25*cm;
  fSTPCBottomThickness = 0.2*cm;
  
  fInnerVesselR = 10.25*cm;
  fInnerVesselThickness = 1*cm;
  fInnerVesselHalfHeight = 15.25*cm;
  fInnerVesselBottomThickness = 5*cm;
  fInnerVesselTopThickness = 2.5*cm;
  fInnerVesselStandOfSTPC = 12.5*cm;
  fInnerVesselZPosition = -fInnerVesselHalfHeight + fSTPCHalfheight + fInnerVesselStandOfSTPC;
  
  fTeflonVesselR = 9*cm;
  fTeflonVesselThickness = fInnerVesselR - fTeflonVesselR;
  fTeflonVesselHalfHeight = 6.4*cm;
  fTeflonVesselBottomThickness = fTeflonVesselThickness;
  fTeflonVesselZPosition = fInnerVesselZPosition - fInnerVesselHalfHeight + fTeflonVesselBottomThickness + fTeflonVesselHalfHeight;
  
  fOuterVesselR = 15*cm;
  fOuterVesselThickness = 1*cm;
  fOuterVesselHalfHeight = 20*cm; // ?
  fInnerStandOfOuter = 1*cm; // ?
  fOuterVesselBottomThickness = 4*cm;
  fOuterVesselTopThickness = 4*cm;
  fOuterVesselZPosition = fInnerVesselZPosition + fInnerVesselHalfHeight + fInnerVesselTopThickness + fInnerStandOfOuter - fOuterVesselHalfHeight;
  
  // Parameters for Anode/Cathode
  fAnodeThickness = 0.2*cm;
  fCathodeThickness = 0.2*cm;
  G4double fCathodeStandoffFromVessel = 0.2*cm;
  G4double fAnodeStandoffFromVessel = 0.2*cm;
  fAnodeZPosition = fSTPCHalfheight - fAnodeThickness / 2.0 - fAnodeStandoffFromVessel;
  fCathodeZPosition = -fSTPCHalfheight + fCathodeThickness / 2.0 + fCathodeStandoffFromVessel;

  // Parameters for field rings
  nFieldRings = 6; // Ring number of miniTPC
  fFieldRingLength = 0.2*cm;
  fFieldRingThick = 0.2*cm;
  fWWDistance = (G4double)(fAnodeZPosition - fCathodeZPosition - fAnodeThickness / 2.0 - fCathodeThickness / 2.0 - nFieldRings * fFieldRingThick) / (nFieldRings + 1);
  fTopRingZPosition = fAnodeZPosition - fAnodeThickness / 2.0 - fWWDistance - fFieldRingThick / 2.0;
  
  // Parameters for Simple SiPM
  fSiPMStaveThickness = 2.5*mm;
  fSiPMPadThickness = 1.3*mm; 
  fSiPMWindowThickness = 0.5*mm; 
  fWindowGapSiPM = fSiPMStaveThickness - fSiPMPadThickness - fSiPMWindowThickness; 
  fSiPMPadHeight = 5.95*mm;
  
  fNSiPMStaveAlongPhi = (G4int)14; // fNSiPMPadAlongPhi should be G4int 14 in miniTPC; 
  fNSiPMPadAlongZ = (G4int)14;
  fSiPMStaveWidth = 3*cm;
  
  fSiPMGapSiPM = 0.5*mm;
  fSiPMStaveHeight = (fNSiPMPadAlongZ / 2) * (fSiPMStaveWidth / 2); // One MPPC has 4 pads
  fSiPMStaveZPosition = 0*mm; // (fAnodeZPosition - fAnodeThickness / 2.0) - fSiPMStaveHeight / 2.0;
  
  fSiPMActiveLayerThickness = 0.0001*cm;
  fSiPMActiveLayerDepth = 0.00*cm; // The pad is SiO2 but the window is already added independently before, so it will be 0.
  fActiveSiPMPadHeight = fSiPMPadHeight;
  
  fSiPMBaseLayerThickness = 0.05*cm;
  fSiPMPadBaseHeight = fSiPMPadHeight;

  PhiIR = (G4double)0.5 * (360 / fNSiPMStaveAlongPhi) * deg;
  IR = (G4double)fSiPMStaveWidth / (2 * tan(PhiIR));
  G4cout << "IR of SiPM Staves: " << IR / cm << " cm" << G4endl;
  SiPMStaveDPhi = (G4double)2 * PhiIR;
  dGapAlongPhi = 0 * deg;
    
  // Adjust the radius of Anode/Cathode/Field Ring
  fAnodeStandoffFromSiPM = 0.1*cm;
  fAnodeRadius = IR - fAnodeStandoffFromSiPM;
  fCathodeRadius = fAnodeRadius;
  fieldRingSweptR = fAnodeRadius - fFieldRingLength / 2.0;
}

miniTPCDetectorConstruction::~miniTPCDetectorConstruction() {;}

G4VPhysicalVolume* miniTPCDetectorConstruction::Construct()
{
  nEXOMaterials::GetInstance();
  G4LogicalVolume* logicWorld = new G4LogicalVolume(new G4Box("World", 500*mm, 500*mm, 500*mm), nEXOMaterials::GetInstance()->GetMaterial("G4_AIR"), "World");
  G4VPhysicalVolume* PhyWorld = new G4PVPlacement(0,
                                                  G4ThreeVector(0, 0, 0),
                                                  logicWorld,
                                                  "World",
                                                  0,
                                                  false,
                                                  0,
                                                  fCheckOverlaps);

  G4cout << "//################################################//" << G4endl;
  G4cout << "//############# nEXO TPC Internals ###############//" << G4endl;
  G4cout << "//################################################//" << G4endl;

  BuildOtherParts(logicWorld);
  SetOpticalSurfaces();

  return PhyWorld;
}

void miniTPCDetectorConstruction::BuildOtherParts(G4LogicalVolume* logicWorld)
{
  // Build the Copper Vessel with bottom
  G4String sVesselName = "/nEXO/TPCInternals/sVessel";
  G4LogicalVolume* LogSVessel = new G4LogicalVolume(new G4Tubs(sVesselName, 0, fSTPCRadius + fSTPCVesselSideThickness, fSTPCHalfheight, 0.*deg, fSliceAngle), nEXOMaterials::GetInstance()->GetMaterial("G4_Cu"), sVesselName);
  G4VPhysicalVolume* PhySVessel = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, 0),
                                  	        LogSVessel,
                                  		    sVesselName,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sVesselName, PhySVessel);
  G4Region* TPCRegion = new G4Region("TPCRegion");                                                                                                  
  TPCRegion->AddRootLogicalVolume(LogSVessel); // 2023-12-20 Add a TPC region for production cut set

  G4String sVesselBottom = "/nEXO/TPCInternals/sVesselBottom";
  G4LogicalVolume* LogSVesselBottom = new G4LogicalVolume(new G4Tubs(sVesselBottom, 0, fSTPCRadius + fSTPCVesselSideThickness, fSTPCBottomThickness / 2, 0.*deg, fSliceAngle), nEXOMaterials::GetInstance()->GetMaterial("G4_Cu"), sVesselBottom);
  G4VPhysicalVolume* PhySVesselBottom = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, -fSTPCHalfheight - fSTPCBottomThickness / 2),
                                  	        LogSVesselBottom,
                                  		    sVesselBottom,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);
  
  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sVesselBottom, PhySVesselBottom);

  // Build Inner Vessel with bottom
  G4String sInnerVessel = "/nEXO/TPCInternals/sInnerVessel";
  G4LogicalVolume* LogInnerVessel = new G4LogicalVolume(new G4Tubs(sInnerVessel, fInnerVesselR, fInnerVesselR + fInnerVesselThickness, fInnerVesselHalfHeight, 0.*deg, fSliceAngle), nEXOMaterials::GetInstance()->GetMaterial("G4_STAINLESS-STEEL"), sInnerVessel);
  G4VPhysicalVolume* PhyInnerVessel = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, fInnerVesselZPosition),
                                  	        LogInnerVessel,
                                  		    sInnerVessel,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sInnerVessel, PhyInnerVessel);
 
  G4String sInnerVesselBottom = "/nEXO/TPCInternals/sInnerVesselBottom";
  G4LogicalVolume* LogInnerVesselBottom = new G4LogicalVolume(new G4Tubs(sInnerVesselBottom, 0, fInnerVesselR + fInnerVesselThickness, fInnerVesselBottomThickness / 2, 0.*deg, fSliceAngle),
                                                                  nEXOMaterials::GetInstance()->GetMaterial("G4_STAINLESS-STEEL"), sInnerVesselBottom);
  G4VPhysicalVolume* PhyInnerVesselBottom = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, fInnerVesselZPosition - fInnerVesselHalfHeight - fInnerVesselBottomThickness / 2),
                                  	        LogInnerVesselBottom,
                                  		    sInnerVesselBottom,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sInnerVesselBottom, PhyInnerVesselBottom);
  
  G4String sInnerVesselTop = "/nEXO/TPCInternals/sInnerVesselTop";
  G4LogicalVolume* LogInnerVesselTop = new G4LogicalVolume(new G4Tubs(sInnerVesselTop, 0, fInnerVesselR + fInnerVesselThickness, fInnerVesselTopThickness / 2, 0.*deg, fSliceAngle),
                                                                  nEXOMaterials::GetInstance()->GetMaterial("G4_STAINLESS-STEEL"), sInnerVesselTop);
  G4VPhysicalVolume* PhyInnerVesselTop = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, fInnerVesselZPosition + fInnerVesselHalfHeight + fInnerVesselTopThickness / 2),
                                  	        LogInnerVesselTop,
                                  		    sInnerVesselTop,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sInnerVesselTop, PhyInnerVesselTop);
  
  // Build Teflon construction
  G4String sTeflonVessel = "/nEXO/TPCInternals/sTeflonVessel";
  G4LogicalVolume* LogTeflonVessel = new G4LogicalVolume(new G4Tubs(sTeflonVessel, fTeflonVesselR, fTeflonVesselR + fTeflonVesselThickness, fTeflonVesselHalfHeight, 0.*deg, fSliceAngle), nEXOMaterials::GetInstance()->GetMaterial("G4_TEFLON"), sTeflonVessel);
  G4VPhysicalVolume* PhyTeflonVessel = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, fTeflonVesselZPosition),
                                  	        LogTeflonVessel,
                                  		    sTeflonVessel,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sTeflonVessel, PhyTeflonVessel);
 
  G4String sTeflonVesselBottom = "/nEXO/TPCInternals/sTeflonVesselBottom";
  G4LogicalVolume* LogTeflonVesselBottom = new G4LogicalVolume(new G4Tubs(sTeflonVesselBottom, 0, fTeflonVesselR + fTeflonVesselThickness, fTeflonVesselBottomThickness / 2, 0.*deg, fSliceAngle), nEXOMaterials::GetInstance()->GetMaterial("G4_TEFLON"), sTeflonVesselBottom);
  G4VPhysicalVolume* PhyTeflonVesselBottom = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, fTeflonVesselZPosition - fTeflonVesselHalfHeight - fTeflonVesselBottomThickness / 2),
                                  	        LogTeflonVesselBottom,
                                  		    sTeflonVesselBottom,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sTeflonVesselBottom, PhyTeflonVesselBottom);
  
  // Build Outer Vessel with bottom
  G4String sOuterVessel = "/nEXO/TPCInternals/sOuterVessel";
  G4LogicalVolume* LogOuterVessel = new G4LogicalVolume(new G4Tubs(sOuterVessel, fOuterVesselR, fOuterVesselR + fOuterVesselThickness, fOuterVesselHalfHeight, 0.*deg, fSliceAngle), nEXOMaterials::GetInstance()->GetMaterial("G4_STAINLESS-STEEL"), sOuterVessel);
  G4VPhysicalVolume* PhyOuterVessel = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, fOuterVesselZPosition),
                                  	        LogOuterVessel,
                                  		    sOuterVessel,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sOuterVessel, PhyOuterVessel);
 
  G4String sOuterVesselBottom = "/nEXO/TPCInternals/sOuterVesselBottom";
  G4LogicalVolume* LogOuterVesselBottom = new G4LogicalVolume(new G4Tubs(sOuterVesselBottom, 0, fOuterVesselR, fOuterVesselBottomThickness / 2, 0.*deg, fSliceAngle), nEXOMaterials::GetInstance()->GetMaterial("G4_STAINLESS-STEEL"), sOuterVesselBottom);
  G4VPhysicalVolume* PhyOuterVesselBottom = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, fOuterVesselZPosition - fOuterVesselHalfHeight - fOuterVesselBottomThickness / 2),
                                  	        LogOuterVesselBottom,
                                  		    sOuterVesselBottom,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sOuterVesselBottom, PhyOuterVesselBottom);
  
  G4String sOuterVesselTop = "/nEXO/TPCInternals/sOuterVesselTop";
  G4LogicalVolume* LogOuterVesselTop = new G4LogicalVolume(new G4Tubs(sOuterVesselTop, 0, fOuterVesselR, fOuterVesselTopThickness / 2, 0.*deg, fSliceAngle), nEXOMaterials::GetInstance()->GetMaterial("G4_STAINLESS-STEEL"), sOuterVesselTop);
  G4VPhysicalVolume* PhyOuterVesselTop = new G4PVPlacement(0,
                                  		    G4ThreeVector(0, 0, fOuterVesselZPosition + fOuterVesselHalfHeight + fOuterVesselTopThickness / 2),
                                  	        LogOuterVesselTop,
                                  		    sOuterVesselTop,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                            fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sOuterVesselTop, PhyOuterVesselTop);
  
  // Build other parts in Copper Vessel
  G4String sTPCLXe = "/nEXO/TPCInternals/sTPCLXe";
  G4LogicalVolume* logicSLXe = new G4LogicalVolume(new G4Tubs(sTPCLXe, 0, fSTPCRadius, fSTPCHalfheight, 0.*deg, fSliceAngle), nEXOMaterials::GetInstance()->GetMaterial("liquidXe"), sTPCLXe);
  G4VPhysicalVolume* PhySTPCLXe = new G4PVPlacement(0,
                                                    G4ThreeVector(0, 0, 0),
                                                    logicSLXe,
                                                    sTPCLXe,
                                                    LogSVessel,
                                                    false,
                                                    0,
                                                    fCheckOverlaps);
  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sTPCLXe, PhySTPCLXe);
 
  G4cout << "Small TPC name -----> " << sTPCLXe << G4endl;

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//############### Field Shaping Rings ##############//" << G4endl;
  G4cout << "//##################################################//" << G4endl;

  G4String fieldRingName = "/nEXO/TPCInternals/FieldRing";

  G4LogicalVolume* logicFieldRing[10000] = {0};
  G4VPhysicalVolume* physFieldRing[10000] = {0};
    
  G4Tubs* midRing = new G4Tubs("MidFieldRing", fieldRingSweptR - fFieldRingLength / 2.0, fieldRingSweptR + fFieldRingLength / 2.0, fFieldRingThick / 2.0, 0, fSliceAngle);
  G4LogicalVolume* logicFieldRingWithHoles = new G4LogicalVolume(midRing, nEXOMaterials::GetInstance()->GetMaterial("G4_Cu"), fieldRingName);
  std::cout << "Field shaping ring, length: " << fFieldRingLength << ", " << fFieldRingThick << ", " << fWWDistance << std::endl;
  
  for (G4int i = 0; i < nFieldRings; i++) {
      // Z position of field ring
      G4double fieldRingZPosition = fTopRingZPosition - i * (fWWDistance + fFieldRingThick);
      G4cout << "FieldRing Z position: " << fieldRingZPosition << " mm" << G4endl;
      // Put field rings in place
      physFieldRing[i] = new G4PVPlacement(0,
                                           G4ThreeVector(0, 0, fieldRingZPosition),
                                           logicFieldRingWithHoles,
                                           fieldRingName,
                                           logicSLXe,
                                           false,
                                           i, fCheckOverlaps);
      nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(fieldRingName, physFieldRing[i], i);   
  }

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//################# Anode Platters #################//" << G4endl;
  G4cout << "//##################################################//" << G4endl;
  
  G4String AnodeName = "/nEXO/TPCInternals/Anode";

  G4Tubs* solidAnode = new G4Tubs(AnodeName, 0.*mm, fAnodeRadius, fAnodeThickness / 2., 0*deg, fSliceAngle);
  G4LogicalVolume* logicAnode = new G4LogicalVolume(solidAnode, nEXOMaterials::GetInstance()->GetMaterial("G4_SILICON_DIOXIDE"), AnodeName);
  G4VPhysicalVolume* physAnode = new G4PVPlacement(0,
                                                  G4ThreeVector(0, 0, fAnodeZPosition),
                                                  logicAnode,
                                                  AnodeName,
                                                  logicSLXe,
                                                  false,
                                                  0, fCheckOverlaps);
  G4cout << "fAnodeZPosition = " << fAnodeZPosition / mm << G4endl;
  G4cout << "fAnodeRadius = " << fAnodeRadius / mm << G4endl;
  G4cout << "fAnodeThickness = " << fAnodeThickness / mm << G4endl;

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(AnodeName, physAnode);   

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//################# Cathode Platters ###############//" << G4endl;
  G4cout << "//##################################################//" << G4endl;

  G4String CathodeName = "/nEXO/TPCInternals/Cathode";

  G4LogicalVolume* logicCathode = new G4LogicalVolume(new G4Tubs(CathodeName,
                                                                 0.*mm, fCathodeRadius,
                                                                 fCathodeThickness / 2.,
                                                                 0*deg, fSliceAngle),
                                                                 nEXOMaterials::GetInstance()->GetMaterial("G4_Cu"),
                                                                 CathodeName);
  
  G4VPhysicalVolume* physCathode = new G4PVPlacement(0,
                                                     G4ThreeVector(0, 0, fCathodeZPosition),
                                                     logicCathode,
                                                     CathodeName,
                                                     logicSLXe,
                                                     false,
                                                     0, fCheckOverlaps);
  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(CathodeName, physCathode);   

  G4cout << "fCathodeZPosition = " << fCathodeZPosition / mm << G4endl;
  G4cout << "fCathodeRadius = " << fCathodeRadius / mm << G4endl;
  G4cout << "fCathodeThickness = " << fCathodeThickness / mm << G4endl;

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//####################### SiPM #####################//" << G4endl;
  G4cout << "//##################################################//" << G4endl;
    
  G4String SiPMStaveName = "/nEXO/TPCInternals/SiPMStaves";

  G4LogicalVolume* logicSiPMStaves[10000] = {0};
  G4VPhysicalVolume* physSiPMStaves[10000] = {0};
    
  G4LogicalVolume* logicSiPMPads[10000] = {0};
  G4VPhysicalVolume* physSiPMPads[10000] = {0};
   
  G4LogicalVolume* logicSiPMWindows[10000] = {0};
  G4VPhysicalVolume* physSiPMWindows[10000] = {0};

  G4LogicalVolume* logicActiveSiPMPads[10000] = {0};
  G4VPhysicalVolume* physActiveSiPMPads[10000] = {0};

  G4LogicalVolume* logicSiPMPadBase[10000] = {0};
  G4VPhysicalVolume* physSiPMPadBase[10000] = {0};

  G4int sipmID = 0;

  G4cout << "LookNumber: " << fNSiPMStaveAlongPhi << G4endl; 
  for(G4int i = 0; i < fNSiPMStaveAlongPhi; i++) {
      G4int fNMPPCAlongZ = 7;
      G4double fMPPCHeight = fSiPMStaveWidth / 2;
      for(G4int j = 0; j < fNMPPCAlongZ; j++) {
          G4RotationMatrix* rotSiPMStave = new G4RotationMatrix();
          rotSiPMStave->rotateZ(-1 * i * (SiPMStaveDPhi + dGapAlongPhi));
          for(G4int k = 0; k < 2; k++) {
              G4double fMPPCYpos = -fSiPMStaveWidth / 2.0 + fMPPCHeight / 2.0 + fMPPCHeight * k;
              G4double fMPPCZpos = fSiPMStaveZPosition + fSiPMStaveHeight / 2.0 - fMPPCHeight / 2.0 - fMPPCHeight * j;
              for(G4int m = 0; m < 4; m++) {
                  // Set the SiPM pad as Staves
                  G4double padXpos = 0;
                  G4double padYpos = 0;
                  G4double padZpos = 0;
              
                  G4String SiPMName = "/nEXO/TPCInternals/SiPMPads";
                  G4double dSiPMPadGapAlongZ = (fSiPMStaveHeight - fSiPMPadHeight * fNSiPMPadAlongZ) / (fNSiPMPadAlongZ - 1);
                  
                  logicSiPMPads[sipmID] = new G4LogicalVolume(new G4Box(SiPMName,
  					                         fSiPMPadThickness / 2,
  						                     fSiPMPadHeight / 2,
  						                     fSiPMPadHeight / 2), 
  						                     nEXOMaterials::GetInstance()->GetMaterial("G4_SILICON_DIOXIDE"),
  						                     SiPMName);
                  
                  G4String SiPMWindowName = "/nEXO/TPCInternals/SiPMWindows";
                    
                  logicSiPMWindows[sipmID] = new G4LogicalVolume(new G4Box(SiPMWindowName,
  					                         fSiPMWindowThickness / 2,
  						                     fSiPMPadHeight / 2,
  						                     fSiPMPadHeight / 2), 
  						                     nEXOMaterials::GetInstance()->GetMaterial("G4_SILICON_DIOXIDE"),
  						                     SiPMWindowName);

                  G4String ActiveSiPMName = "/nEXO/TPCInternals/ActiveSiPMPads";

                  G4double fActiveGap = fSiPMPadHeight - fActiveSiPMPadHeight * 2;

                  logicActiveSiPMPads[sipmID] = new G4LogicalVolume(new G4Box(ActiveSiPMName,
                                                             fSiPMActiveLayerThickness / 2,
							                                 fActiveSiPMPadHeight / 2,
							                                 fActiveSiPMPadHeight / 2),
                                                             nEXOMaterials::GetInstance()->GetMaterial("G4_Si"),
                                                             ActiveSiPMName);
                  
                  G4String SiPMPadBaseName = "/nEXO/TPCInternals/SiPMPadBase";
                    
                  logicSiPMPadBase[sipmID] = new G4LogicalVolume(new G4Box(SiPMPadBaseName,
                                                           fSiPMBaseLayerThickness / 2, fSiPMPadBaseHeight / 2.0,
                                                           fSiPMPadBaseHeight / 2.0),
                                                           nEXOMaterials::GetInstance()->GetMaterial("G4_Si"), SiPMPadBaseName);                                                                                      
                  
                  // SiPM Pad Position from MPPC center
                  // --------
                  // ||1||2||
                  // ||3||4||
                  // --------
                  if(m == 0) {
                      padYpos = fMPPCYpos - fSiPMPadHeight / 2.0 - fSiPMGapSiPM / 2.0;
                      padZpos = fMPPCZpos + fSiPMPadHeight / 2.0 + fSiPMGapSiPM / 2.0;
                  }
                  else if(m == 1) {
                      padYpos = fMPPCYpos + fSiPMPadHeight / 2.0 + fSiPMGapSiPM / 2.0;
                      padZpos = fMPPCZpos + fSiPMPadHeight / 2.0 + fSiPMGapSiPM / 2.0;
                  }
                  else if(m == 2) {
                      padYpos = fMPPCYpos - fSiPMPadHeight / 2.0 - fSiPMGapSiPM / 2.0;
                      padZpos = fMPPCZpos - fSiPMPadHeight / 2.0 - fSiPMGapSiPM / 2.0;
                  }
                  else if(m == 3) {
                      padYpos = fMPPCYpos + fSiPMPadHeight / 2.0 + fSiPMGapSiPM / 2.0;
                      padZpos = fMPPCZpos - fSiPMPadHeight / 2.0 - fSiPMGapSiPM / 2.0;
                  }
                  else G4cout << "Wrong SiPM PAD position" << G4endl;

                  // SiPM Absolute Position in LXe
                  G4double depth = fSiPMStaveThickness / 2.0 - fSiPMPadThickness / 2.0;
                  G4double xpos = IR + fSiPMStaveThickness / 2.0 + depth;
                  G4double ypos = padYpos;
                  G4double zpos = padZpos;
                   
                  G4ThreeVector pad_position(xpos, ypos, zpos);
                  pad_position.rotate(i * (SiPMStaveDPhi + dGapAlongPhi), G4ThreeVector(0, 0, 1));

                  physSiPMPads[sipmID] = new G4PVPlacement(rotSiPMStave, pad_position,
                                                           logicSiPMPads[sipmID],
                                                           SiPMName,
                                                           logicSLXe,
                                                           false,
                                                           sipmID, fCheckOverlaps);
                  if(i == 0) G4cout << "Pad position: " << pad_position << G4endl;
                  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(SiPMName, physSiPMPads[sipmID], sipmID);
                
                  // SiPM Window Position to stave center
                  depth = -fSiPMStaveThickness / 2.0 + fSiPMWindowThickness / 2.0;
                  xpos = IR + fSiPMStaveThickness / 2.0 + depth;
                  
                  G4ThreeVector window_position(xpos, ypos, zpos);
                  window_position.rotate(i * (SiPMStaveDPhi + dGapAlongPhi), G4ThreeVector(0, 0, 1));
                  physSiPMWindows[sipmID] = new G4PVPlacement(rotSiPMStave, window_position,
                                                           logicSiPMWindows[sipmID],
                                                           SiPMWindowName,
                                                           logicSLXe,
                                                           false,
                                                           sipmID, fCheckOverlaps);

                  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(SiPMWindowName, physSiPMWindows[sipmID], sipmID);

                  // Set the Active and Base in SiPM Pads
                  physActiveSiPMPads[sipmID] = new G4PVPlacement(0,
                                                    G4ThreeVector(-fSiPMPadThickness / 2.0 + fSiPMActiveLayerDepth + fSiPMActiveLayerThickness / 2.0, 0, 0), logicActiveSiPMPads[sipmID],
                                                    ActiveSiPMName,
                                                    logicSiPMPads[sipmID],
                                                    false,
                                                    0, fCheckOverlaps);
          
                  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(ActiveSiPMName, physActiveSiPMPads[sipmID], sipmID);   
                  
                  physSiPMPadBase[sipmID] = new G4PVPlacement(0,
                                              G4ThreeVector(-fSiPMPadThickness / 2.0 + fSiPMActiveLayerDepth + fSiPMActiveLayerThickness + fSiPMBaseLayerThickness / 2, 0, 0),
                                              logicSiPMPadBase[sipmID],
                                              SiPMPadBaseName,
                                              logicSiPMPads[sipmID],
                                              false,
                                              0, fCheckOverlaps);

                  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(SiPMPadBaseName, physSiPMPadBase[sipmID], sipmID);   
                  sipmID++; 
              }
          }
      }
  }

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//############### Visible factors #################//" << G4endl;
  G4cout << "//##################################################//" << G4endl;
  // Attributes of Vessels
  G4VisAttributes* VesselAtt = new G4VisAttributes(G4Colour(1, 1, 1));  
  VesselAtt->SetVisibility(false);
  VesselAtt->SetForceSolid(false);
  
  LogInnerVessel->SetVisAttributes(VesselAtt); 
  LogInnerVesselBottom->SetVisAttributes(VesselAtt); 
  LogInnerVesselTop->SetVisAttributes(VesselAtt); 
  
  LogOuterVessel->SetVisAttributes(VesselAtt); 
  LogOuterVesselBottom->SetVisAttributes(VesselAtt); 
  LogOuterVesselTop->SetVisAttributes(VesselAtt); 

  G4VisAttributes* SLXeAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0));
  SLXeAtt->SetVisibility(true);
  SLXeAtt->SetForceSolid(false);
  logicSLXe->SetVisAttributes(SLXeAtt);

  G4VisAttributes* CopperAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));  
  CopperAtt->SetVisibility(true);
  CopperAtt->SetForceSolid(false);
  
  LogSVessel->SetVisAttributes(CopperAtt); 
  LogSVesselBottom->SetVisAttributes(CopperAtt); 
  
  G4VisAttributes* TeflonAtt = new G4VisAttributes(G4Colour(0, 0, 1));
  TeflonAtt->SetVisibility(true);
  TeflonAtt->SetForceSolid(false);
  
  LogTeflonVessel->SetVisAttributes(TeflonAtt); 
  LogTeflonVesselBottom->SetVisAttributes(TeflonAtt); 
  
  // Attributes of Field Rings
  G4VisAttributes* RingsAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));
  RingsAtt->SetVisibility(true);
  RingsAtt->SetForceSolid(false);
  logicFieldRingWithHoles->SetVisAttributes(RingsAtt);
  
  // Attributes of Cathode/Anode
  G4VisAttributes* CathodeAtt = new G4VisAttributes(G4Colour(0, 1, 0));
  CathodeAtt->SetVisibility(true);
  CathodeAtt->SetForceSolid(false);
  logicCathode->SetVisAttributes(CathodeAtt);
  
  G4VisAttributes* AnodeAtt = new G4VisAttributes(G4Colour(0, 1.0, 0));
  AnodeAtt->SetVisibility(true);
  AnodeAtt->SetForceSolid(false);
  logicAnode->SetVisAttributes(AnodeAtt);
  
  // Attributes of SiPMs
  G4VisAttributes* SiPMAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));  
  SiPMAtt->SetVisibility(true);
  SiPMAtt->SetForceSolid(false);
  G4VisAttributes* ActiveSiPMAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0));  
  ActiveSiPMAtt->SetVisibility(true);
  G4VisAttributes* SiPMBaseAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.5));  
  SiPMBaseAtt->SetVisibility(true);
  
  // Hide some components

  //G4VisAttributes* invisible = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0, 0.0)); // Completely invisible
  //LogSVessel->SetVisAttributes(invisible); 
  //LogSVesselBottom->SetVisAttributes(invisible); 
  //LogInnerVessel->SetVisAttributes(invisible); 
  //LogInnerVesselBottom->SetVisAttributes(invisible); 
  //LogInnerVesselTop->SetVisAttributes(invisible); 
  //LogTeflonVessel->SetVisAttributes(invisible); 
  //LogTeflonVesselBottom->SetVisAttributes(invisible); 
  //LogOuterVessel->SetVisAttributes(invisible); 
  //LogOuterVesselBottom->SetVisAttributes(invisible); 
  //LogOuterVesselTop->SetVisAttributes(invisible); 

  //
  //for(G4int i = 0; i < fNSiPMStaveAlongPhi; i++) {
  //    logicSiPMPads[i]->SetVisAttributes(SiPMAtt);
  //    logicActiveSiPMPads[i]->SetVisAttributes(ActiveSiPMAtt);
  //    logicSiPMWindows[i]->SetVisAttributes(SiPMBaseAtt);
  //}

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//############### Check the Overlap ################//" << G4endl;
  G4cout << "//##################################################//" << G4endl;
    
  physAnode->CheckOverlaps();
  physCathode->CheckOverlaps();

  for (G4int i = 0; i < nFieldRings; i++) {
      G4bool overlaps = physFieldRing[i]->CheckOverlaps();
  }
  for (G4int i = 0; i < sipmID; i++) {
         // G4bool overlaps0 = physSiPMPads[i]->CheckOverlaps();
         // G4bool overlaps1 = physSiPMWindows[i]->CheckOverlaps();
         // G4bool overlaps2 = physActiveSiPMPads[i]->CheckOverlaps();
         // G4bool overlaps3 = physSiPMPadBase[i]->CheckOverlaps();
  }
}

void miniTPCDetectorConstruction::SetOpticalSurfaces()
{
  G4double* RefSpecularlobe = new G4double[2];
  RefSpecularlobe[0] = 1.0;
  RefSpecularlobe[1] = 1.0;
  G4double* RefSpecularspike = new G4double[2];
  RefSpecularspike[0] = 0.0;
  RefSpecularspike[1] = 0.0;
  G4double* RefBackscatter = new G4double[2];
  RefBackscatter[0] = 0.0;
  RefBackscatter[1] = 0.0;
  
  G4double* fieldRingReflectivity = new G4double[2];
  fieldRingReflectivity[0] = fFieldRingRef;
  fieldRingReflectivity[1] = fFieldRingRef;

  G4double* anodeReflectivity = new G4double[2];
  anodeReflectivity[0] = fAnodeRef;
  anodeReflectivity[1] = fAnodeRef;

  G4double* cathodeReflectivity = new G4double[2];
  cathodeReflectivity[0] = fCathodeRef;
  cathodeReflectivity[1] = fCathodeRef;

  G4double* bulgeReflectivity = new G4double[2];
  bulgeReflectivity[0] = fBulgeRef;
  bulgeReflectivity[1] = fBulgeRef;

  G4double* tpcVesselReflectivity = new G4double[2];
  tpcVesselReflectivity[0] = fTPCVesselRef;
  tpcVesselReflectivity[1] = fTPCVesselRef;

  G4double* teflonReflectivity = new G4double[2];
  teflonReflectivity[0] = fTeflonRef;
  teflonReflectivity[1] = fTeflonRef;

  std::cout << "Reflectivity of field ring is " << fFieldRingRef << std::endl;
  std::cout << "Reflectivity of anode is " << fAnodeRef << std::endl;
  std::cout << "Reflectivity of cathode is " << fCathodeRef << std::endl;
  std::cout << "Reflectivity of bulge is " << fBulgeRef << std::endl;
  std::cout << "Reflectivity of teflon is " << fTeflonRef << std::endl;

  G4double* photonULEnergies = new G4double[2];
  photonULEnergies[0] = (4.13566743E-15 * 299792458 / (144.5 * 1.E-9)) * eV; 
  photonULEnergies[1] = (4.13566743E-15 * 299792458 / (2058.2 * 1.E-9)) * eV;

  // Optical SiO2 and Pd Surfaces
  const G4int nSiEntries = 44;
  G4double SiliconPhotonEnergy[nSiEntries] =
  { 0.602*eV, 0.689*eV, 1.03*eV,  1.926*eV,
    2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
    2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
    2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
    2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
    2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
    3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
    3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
    3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV,
    4.500*eV, 4.960*eV, 5.520*eV, 6.250*eV,
    7.000*eV, 8.250*eV, 10.00*eV, 12.50*eV };
  G4double siliconRealRefractiveIndex[nSiEntries] =
  { 3.43,  3.44,  3.495, 3.861,
    3.916, 3.939, 3.962, 3.986,
    4.015, 4.015, 4.077, 4.11,
    4.15, 4.192, 4.239, 4.293,
    4.348, 4.416, 4.491, 4.577,
    4.676, 4.793, 4.925, 5.091,
    5.305, 5.587, 5.976, 6.548,
    6.863, 6.014, 5.483, 5.293,
    5.179, 5.102, 5.074, 5.055,
    2.451, 1.580, 1.319, 0.968,
    0.682, 0.444, 0.306, 0.255 };
  G4double siliconImaginaryRefractiveIndex[nSiEntries] =
  { 0.001, 0.001, 0.001, 0.015, 
    0.018, 0.02, 0.021, 0.023,
    0.024, 0.024, 0.028, 0.03,
    0.033, 0.036, 0.039, 0.045,
    0.05, 0.057, 0.064, 0.077,
    0.091, 0.109, 0.134, 0.167,
    0.22, 0.303, 0.465, 0.885,
    2.051, 2.912, 2.904, 2.951,
    3.085, 3.269, 3.559, 4.128,
    5.082, 3.632, 3.285, 2.89,
    2.45, 1.90, 1.38, 0.875 };

  G4double FBK_AOI[27] = {0.092, 0.137, 0.174, 0.226, 0.262, 0.314, 0.349, 0.383, 0.436, 0.471, 0.524, 0.558, 0.593, 0.645, 0.680, 0.733, 0.785, 0.82, 0.872, 0.9, 0.96, 1.01, 1.03, 1.08, 1.117, 1.17, 1.22};
  G4double FBK_Ref[27] = {0.25, 0.25, 0.25, 0.26, 0.26, 0.26, 0.26, 0.26, 0.26, 0.27, 0.27, 0.27, 0.28, 0.29, 0.3, 0.31, 0.32, 0.32, 0.34, 0.35, 0.36, 0.4, 0.41, 0.44, 0.44, 0.46, 0.47};

  G4double HPK_AOI[15] = {0.089, 0.168, 0.244, 0.336, 0.419, 0.5, 0.59, 0.68, 0.767, 0.855, 0.942, 1.029, 1.117, 1.204, 1.31};
  G4double HPK_Ref[15] = {0.33, 0.33, 0.31, 0.31, 0.32, 0.32, 0.31, 0.31, 0.3, 0.29, 0.28, 0.26, 0.24, 0.21, 0.14};

  G4double HPK_IR_AOI[28] = {0.0, 0.09, 0.17, 0.26, 0.35, 0.44, 0.52, 0.61, 0.7, 0.79, 0.87, 0.96, 1.05, 1.08, 1.12, 1.15, 1.19, 1.22, 1.26, 1.29, 1.33, 1.36, 1.4, 1.43, 1.47, 1.5, 1.54, 1.57}; 
  G4double HPK_Ref_500nm[28] = {0.20, 0.20, 0.20, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.19, 0.20, 0.21, 0.21, 0.22, 0.23, 0.24, 0.25, 0.27, 0.29, 0.32, 0.36, 0.40, 0.47, 0.55, 0.66, 0.80, 1.00};
  G4double HPK_Ref_550nm[28] = {0.17, 0.17, 0.17, 0.17, 0.17, 0.17, 0.17, 0.17, 0.17, 0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.27, 0.29, 0.32, 0.36, 0.41, 0.47, 0.55, 0.66, 0.80, 1.00}; 
  G4double HPK_Ref_600nm[28] = {0.16, 0.16, 0.16, 0.16, 0.16, 0.16, 0.16, 0.16, 0.16, 0.17, 0.18, 0.18, 0.20, 0.21, 0.21, 0.23, 0.24, 0.25, 0.27, 0.30, 0.32, 0.36, 0.41, 0.47, 0.55, 0.66, 0.80, 1.00};
  G4double HPK_Ref_700nm[28] = {0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.16, 0.16, 0.16, 0.17, 0.18, 0.19, 0.20, 0.21, 0.22, 0.23, 0.24, 0.26, 0.28, 0.30, 0.33, 0.37, 0.42, 0.48, 0.56, 0.66, 0.80, 1.00};
  G4double HPK_Ref_800nm[28] = {0.15, 0.15, 0.15, 0.15, 0.15, 0.16, 0.16, 0.16, 0.17, 0.17, 0.18, 0.19, 0.21, 0.22, 0.23, 0.24, 0.25, 0.27, 0.28, 0.31, 0.34, 0.37, 0.42, 0.48, 0.56, 0.66, 0.81, 1.00};
  G4double HPK_Ref_900nm[28] = {0.15, 0.15, 0.15, 0.16, 0.16, 0.16, 0.16, 0.17, 0.17, 0.18, 0.18, 0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.27, 0.29, 0.31, 0.34, 0.38, 0.42, 0.48, 0.56, 0.67, 0.81, 1.00};
  G4double HPK_Ref_1000nm[28] = {0.15, 0.15, 0.16, 0.16, 0.16, 0.16, 0.16, 0.17, 0.17, 0.18, 0.18, 0.20, 0.21, 0.22, 0.23, 0.24, 0.25, 0.27, 0.29, 0.31, 0.34, 0.38, 0.42, 0.48, 0.56, 0.67, 0.81, 1.00};

  G4VPhysicalVolume* physActiveLXe = nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/sTPCLXe");

  G4OpticalSurface* SiPMBaseRefOpSurface = new G4OpticalSurface("SiPMBaseRefOpSurface");
  SiPMBaseRefOpSurface->SetModel(unified);
  SiPMBaseRefOpSurface->SetType(dielectric_metal);
  SiPMBaseRefOpSurface->SetFinish(polished);
  
  G4OpticalSurface* ActiveSiPMRefOpSurface = new G4OpticalSurface("ActiveSiPMRefOpSurface");
  ActiveSiPMRefOpSurface->SetModel(unified);
  ActiveSiPMRefOpSurface->SetType(dielectric_metal);
  ActiveSiPMRefOpSurface->SetFinish(polished);

  G4int iSiPMPad = 0; 
  if(fSiPMOption == 0) {
    iSiPMPad = 0;
    for(G4int i = 0; i < 10000; i++) {
        new G4LogicalBorderSurface("ActiveSiPMRefOpSurface",
                                   physActiveLXe,
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/ActiveSiPMPads", i),
                                   ActiveSiPMRefOpSurface);
        /*
        new G4LogicalBorderSurface("SiPMBaseRefOpSurface",
                                   physActiveLXe,
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/SiPMPadBase",i),
                                   SiPMBaseRefOpSurface);
        */
        iSiPMPad++;
    }           
  }

  G4MaterialPropertiesTable* SiPMRefOpticalMPT  = new G4MaterialPropertiesTable();
  G4MaterialPropertiesTable* SiPMBaseRefOpticalMPT  = new G4MaterialPropertiesTable();
  SiPMBaseRefOpticalMPT->AddProperty("REALRINDEX", SiliconPhotonEnergy, siliconRealRefractiveIndex, nSiEntries);
  SiPMBaseRefOpticalMPT->AddProperty("IMAGINARYRINDEX", SiliconPhotonEnergy, siliconImaginaryRefractiveIndex, nSiEntries);
  G4cout << "SiPM reflectivity option is " << fWavelengthRef << G4endl; 

  if (fWavelengthRef == 178) { SiPMRefOpticalMPT->AddProperty("Reflectivity-AOI", HPK_AOI, HPK_Ref, 15); }
  else if (fWavelengthRef == 500) { SiPMRefOpticalMPT->AddProperty("Reflectivity-AOI", HPK_IR_AOI, HPK_Ref_500nm, 28); }
  else if (fWavelengthRef == 550) { SiPMRefOpticalMPT->AddProperty("Reflectivity-AOI", HPK_IR_AOI, HPK_Ref_550nm, 28); }
  else if (fWavelengthRef == 600) { SiPMRefOpticalMPT->AddProperty("Reflectivity-AOI", HPK_IR_AOI, HPK_Ref_600nm, 28); }
  else if (fWavelengthRef == 700) { SiPMRefOpticalMPT->AddProperty("Reflectivity-AOI", HPK_IR_AOI, HPK_Ref_700nm, 28); }
  else if (fWavelengthRef == 800) { SiPMRefOpticalMPT->AddProperty("Reflectivity-AOI", HPK_IR_AOI, HPK_Ref_800nm, 28); }
  else if (fWavelengthRef == 900) { SiPMRefOpticalMPT->AddProperty("Reflectivity-AOI", HPK_IR_AOI, HPK_Ref_900nm, 28); }
  else if (fWavelengthRef == 1000) { SiPMRefOpticalMPT->AddProperty("Reflectivity-AOI", HPK_IR_AOI, HPK_Ref_1000nm, 28); }
  else { G4cout << "SiPM reflectivity option not found" << G4endl; }

  SiPMBaseRefOpSurface->SetMaterialPropertiesTable(SiPMBaseRefOpticalMPT);
  ActiveSiPMRefOpSurface->SetMaterialPropertiesTable(SiPMRefOpticalMPT);

  // Al reflective index from A. G. Mathewson and H. P. Myers. Absolute values of the optical constants of some pure metals, Phys. Scr. 4, 291-292 (1971)
  const G4int nAlEntries = 44;
  G4double AluminumPhotonEnergy[nAlEntries] = 
  {1.204*eV, 1.228*eV, 1.252*eV, 1.278*eV, 1.305*eV, 1.333*eV, 1.362*eV, 1.393*eV, 1.425*eV, 1.459*eV,
   1.494*eV, 1.531*eV, 1.569*eV, 1.61*eV, 1.653*eV, 1.698*eV, 1.746*eV, 1.797*eV, 1.851*eV, 1.907*eV,
   1.968*eV, 2.033*eV, 2.101*eV, 2.175*eV, 2.254*eV, 2.339*eV, 2.431*eV, 2.53*eV, 2.638*eV, 2.755*eV,
   2.883*eV, 3.024*eV, 3.179*eV, 3.351*eV, 3.542*eV, 3.757*eV, 3.999*eV, 4.275*eV, 4.592*eV, 4.959*eV,
   5.391*eV, 5.904*eV, 6.525*eV, 7.293*eV};
  G4double AluminumRealRefractiveIndex[nAlEntries] =
  {1.071, 1.103, 1.154, 1.218, 1.302, 1.415, 1.557, 1.75, 1.974, 2.205,
   2.375, 2.409, 2.315, 2.145, 1.958, 1.786, 1.632, 1.493, 1.365, 1.246,
   1.136, 1.038, 0.949, 0.867, 0.789, 0.721, 0.656, 0.597, 0.54, 0.489,
   0.441, 0.396, 0.355, 0.318, 0.283, 0.252, 0.219, 0.189, 0.165, 0.141,
   0.124, 0.114, 0.107, 0.101};
  G4double AluminumImaginaryRefractiveIndex[nAlEntries] =
  {8.868, 8.63, 8.4, 8.164, 7.929, 7.703, 7.49, 7.31, 7.199, 7.188, 7.288,
   7.449, 7.572, 7.612, 7.571, 7.475, 7.346, 7.197, 7.032, 6.852, 6.663,
   6.467, 6.267, 6.06, 5.852, 5.642, 5.428, 5.213, 4.997, 4.778, 4.559,
   4.337, 4.114, 3.889, 3.664, 3.437, 3.215, 2.982, 2.75, 2.515, 2.275,
   2.028, 1.791, 1.533};

  // Au reflective index form W. S. M. Werner, K. Glantschnig, C. Ambrosch-Draxl. Optical constants and inelastic electron-scattering data for 17 elemental metals, J. Phys Chem Ref. Data 38, 1013-1092 (2009)
  const G4int nAuEntries = 44;
  G4double AurumPhotonEnergy[nAuEntries] =
  {1.204*eV, 1.228*eV, 1.252*eV, 1.278*eV, 1.305*eV, 1.333*eV, 1.362*eV, 1.393*eV, 1.425*eV, 1.459*eV,
   1.494*eV, 1.531*eV, 1.569*eV, 1.61*eV, 1.653*eV, 1.698*eV, 1.746*eV, 1.797*eV, 1.851*eV, 1.907*eV,
   1.968*eV, 2.033*eV, 2.101*eV, 2.175*eV, 2.254*eV, 2.339*eV, 2.431*eV, 2.53*eV, 2.638*eV, 2.755*eV,
   2.883*eV, 3.024*eV, 3.179*eV, 3.351*eV, 3.542*eV, 3.757*eV, 3.999*eV, 4.275*eV, 4.592*eV, 4.959*eV,
   5.391*eV, 5.904*eV, 6.525*eV, 7.293*eV};
  G4double AurumRealRefractiveIndex[nAuEntries] =
  {0.66, 0.639, 0.619, 0.604, 0.59, 0.575, 0.561, 0.547, 0.532, 0.518,
   0.503, 0.495, 0.487, 0.48, 0.473, 0.465, 0.458, 0.46, 0.462, 0.464,
   0.467, 0.477, 0.495, 0.513, 0.533, 0.58, 0.628, 0.691, 0.793, 0.899,
   1.087, 1.287, 1.542, 1.783, 1.984, 2.069, 1.944, 1.668, 1.41, 1.269,
   1.288, 1.4, 1.519, 1.472};
  G4double AurumImaginaryRefractiveIndex[nAuEntries] =
  {8.278, 8.101, 7.923, 7.74, 7.556, 7.373, 7.189, 7.006, 6.823, 6.639,
   6.456, 6.266, 6.074, 5.882, 5.691, 5.499, 5.308, 5.107, 4.904, 4.702,
   4.5, 4.291, 4.075, 3.859, 3.642, 3.409, 3.177, 2.942, 2.699, 2.458,
   2.248, 2.056, 1.96, 1.956, 2.047, 2.24, 2.436, 2.464, 2.292, 2.012,
   1.728, 1.531, 1.482, 1.532};

  G4double Anode_AOI[11] = {0.087, 0.174, 0.261, 0.349, 0.436, 0.524, 0.61, 0.7, 0.785, 0.873, 0.96};
  G4double Anode_Ref[11] = {0.134, 0.133, 0.134, 0.135, 0.136, 0.139, 0.143, 0.148, 0.154, 0.1671, 0.152};

  G4double MgF2_Al_AOI[28] = {0.0, 0.09, 0.17, 0.26, 0.35, 0.44, 0.52, 0.61, 0.7, 0.79,
   0.87, 0.96, 1.05, 1.08, 1.12, 1.15, 1.19, 1.22, 1.26, 1.29,
   1.33, 1.36, 1.4, 1.43, 1.47, 1.5, 1.54, 1.57};
  G4double MgF2_Al_Ref_175nm[28] = {0.85, 0.85, 0.85, 0.85, 0.86, 0.86, 0.88, 0.89, 0.91, 0.92, 0.94, 0.95, 0.96, 0.96, 0.97, 0.97, 0.97, 0.98, 0.98, 0.98, 0.98, 0.99, 0.99, 0.99, 0.99, 1.00, 1.00, 1.00};
  G4double MgF2_Al_Ref_550nm[28] = {0.89, 0.89, 0.89, 0.89, 0.89, 0.89, 0.89, 0.89, 0.89, 0.88, 0.88, 0.88, 0.87, 0.87, 0.87, 0.86, 0.86, 0.86, 0.85, 0.85, 0.85, 0.85, 0.86, 0.87, 0.88, 0.91, 0.95, 1.00};
  G4double MgF2_Al_Ref_600nm[28] = {0.88, 0.88, 0.88, 0.88, 0.88, 0.88, 0.88, 0.88, 0.88, 0.88, 0.87, 0.87, 0.86, 0.86, 0.86, 0.85, 0.85, 0.85, 0.84, 0.84, 0.84, 0.84, 0.84, 0.85, 0.87, 0.90, 0.94, 1.00};
  G4double MgF2_Al_Ref_700nm[28] = {0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.85, 0.85, 0.84, 0.84, 0.83, 0.83, 0.83, 0.82, 0.82, 0.81, 0.80, 0.80, 0.80, 0.80, 0.80, 0.82, 0.85, 0.91, 1.00};
  G4double MgF2_Al_Ref_800nm[28] = {0.81, 0.81, 0.81, 0.81, 0.81, 0.81, 0.81, 0.81, 0.81, 0.81, 0.80, 0.80, 0.79, 0.78, 0.78, 0.77, 0.77, 0.76, 0.75, 0.75, 0.74, 0.73, 0.73, 0.74, 0.76, 0.80, 0.88, 1.00};
  G4double MgF2_Al_Ref_900nm[28] = {0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.85, 0.85, 0.85, 0.84, 0.84, 0.83, 0.83, 0.82, 0.82, 0.81, 0.81, 0.80, 0.80, 0.79, 0.79, 0.80, 0.82, 0.85, 0.91, 1.00};
  G4double MgF2_Al_Ref_1000nm[28] = {0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.86, 0.85, 0.85, 0.85, 0.84, 0.84, 0.83, 0.83, 0.82, 0.82, 0.81, 0.81, 0.80, 0.80, 0.79, 0.79, 0.80, 0.82, 0.85, 0.91, 1.00};

  // Set optical surface for field shaping rings
  G4OpticalSurface* fieldRingRefOpSurface = new G4OpticalSurface("fieldRingRefOpSurface");
  if(fRingArrangeID == 5){
      new G4LogicalBorderSurface("fieldRingRefSurface", nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("RingVirtual", 0),
              nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/FieldRing", 0), fieldRingRefOpSurface);
  }
  else {
    for(int i = 0; i < 10000; i++) {
      if(nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/FieldRing", i) != NULL)
       new G4LogicalBorderSurface("fieldRingRefSurface",
                                                          physActiveLXe,
                                                          nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/FieldRing", i), fieldRingRefOpSurface);
    }
  }

  fieldRingRefOpSurface->SetModel(unified);
  fieldRingRefOpSurface->SetType(dielectric_metal);
  fieldRingRefOpSurface->SetFinish(polished);

  G4MaterialPropertiesTable* fieldRingRefOpticalMPT  = new G4MaterialPropertiesTable();
  fieldRingRefOpticalMPT->AddProperty("REFLECTIVITY", photonULEnergies, fieldRingReflectivity, 2);

  fieldRingRefOpSurface->SetMaterialPropertiesTable(fieldRingRefOpticalMPT);
  
  // Set optical surface for anode
  G4OpticalSurface* anodeRefOpSurface = new G4OpticalSurface("anodeRefOpSurface");
  if(fSiPMOption == 0) {
    new G4LogicalBorderSurface("anodeRefSurface",
                               physActiveLXe,
                               nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/Anode"), anodeRefOpSurface);
  }

  anodeRefOpSurface->SetModel(unified);
  anodeRefOpSurface->SetType(dielectric_metal);
  anodeRefOpSurface->SetFinish(polished);

  G4MaterialPropertiesTable* anodeRefOpticalMPT  = new G4MaterialPropertiesTable();
  anodeRefOpticalMPT->AddProperty("Reflectivity-AOI", Anode_AOI, Anode_Ref, 11);

  anodeRefOpSurface->SetMaterialPropertiesTable(anodeRefOpticalMPT);

  // Set optical surface for cathode
  G4OpticalSurface* cathodeRefOpSurface = new G4OpticalSurface("cathodeRefOpSurface");
  new G4LogicalBorderSurface("cathodeRefSurface",
                             physActiveLXe,
                             nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/Cathode"), cathodeRefOpSurface);

  cathodeRefOpSurface->SetModel(unified);
  cathodeRefOpSurface->SetType(dielectric_metal);
  cathodeRefOpSurface->SetFinish(polished);

  G4MaterialPropertiesTable* cathodeRefOpticalMPT  = new G4MaterialPropertiesTable();
  cathodeRefOpticalMPT->AddProperty("REFLECTIVITY", photonULEnergies, cathodeReflectivity, 2);

  cathodeRefOpSurface->SetMaterialPropertiesTable(cathodeRefOpticalMPT);

  // Set optical surface for bulge
  G4OpticalSurface* bulgeRefOpSurface = new G4OpticalSurface("bulgeRefOpSurface");
  new G4LogicalBorderSurface("bulgeRefSurface",
                             physActiveLXe,
                             nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/Bulge"), bulgeRefOpSurface);

  bulgeRefOpSurface->SetModel(unified);
  bulgeRefOpSurface->SetType(dielectric_metal);
  bulgeRefOpSurface->SetFinish(polished);

  G4MaterialPropertiesTable* bulgeRefOpticalMPT  = new G4MaterialPropertiesTable();
  bulgeRefOpticalMPT->AddProperty("REFLECTIVITY", photonULEnergies, bulgeReflectivity, 2);

  bulgeRefOpSurface->SetMaterialPropertiesTable(bulgeRefOpticalMPT);
}

