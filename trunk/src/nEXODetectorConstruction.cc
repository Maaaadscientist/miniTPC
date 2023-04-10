#include "nEXODetectorConstruction.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "nEXOMaterials.hh"
#include "nEXOSimplePhysVolManager.hh"


nEXODetectorConstruction::nEXODetectorConstruction()
{
  fDetectorMessenger = new nEXODetectorMessenger(this);

  fCheckOverlaps = false;

  // Parameters
  // -- general
  fInternalsFlag = 2;
  fUseWLS = 0;
  fSiPMOption = 0;
  fAnodeOption = 0;

  // -- TPC Vessel 
  fTPCRadius = 650.*mm;  // LXe volume only
  fTPCHalfheight = 650.*mm;  // LXe volume only
  fTPCVesselSideThickness = 3.*mm;
  fTPCVesselEndCapThickness = 6.6*mm;
  //fTPCRadius = 658.5*mm;
  //fTPCHalfheight = 652.5*mm;
  fTeflonRef = 0.95;
  fTPCVesselRef = 0.0;

  // -- TPC Small_Vessel
  fSTPCRadius = 75.*mm;
  fSTPCHalfheight = 75.*mm;
  fSTPCVesselSideThickness =3.*mm; 
  fSTPCVesselEndCapThickness = 6.6*mm;
  fSTeflonRef = 0.95;
  fSTPCVesselRef = 0.0;
  
  // -- Field shaping rings
  fRingArrangeID = 20;
  fFieldRingLength = 2.5*mm;  // What`s the meaning
  fFieldRingThick = 2.5*mm;
  fWWDistance = 6.5*mm;
  fRingSideDistance = 60.8*mm;  // no use in Pin
  fRadialRingDistance = 6*mm;  // Obsolete    no use?
  fFieldRingRef = 0.8;
  
  // -- Cathode, bulge and anode
  //fCathodeAnodeDistance = 1258.75*mm;
  fCathodeAnodeDistance = 136.5*mm; //center to center
  fCathodeToBottomRingDistance = 5.25*mm;
  fAnodeToTopRingDistance = 5.25*mm;

  // -- cathode
  fCathodeRef = 0.8;
  fBulgeRadius = 10.*mm;
  fBulgeRef = 0.8;
  fCathodeRadiusOffset = 15.0*mm ; // difference between LXeradius and cathode radius.
  fCathodeRadius = fSTPCRadius - fCathodeRadiusOffset; 
  fCathodeThickness = 0.4*mm;
  fCathodeStandoff = 6.35*mm;  //Distance from vessel inner side of bottom surface.
  //fCathodeZPosition = -fTPCHalfheight + fCathodeStandoff + fCathodeThickness/2.;
  fCathodeZPosition = -fSTPCHalfheight + fCathodeStandoff + fCathodeThickness/2.;
 
  // -- anode
  fAnodeRadiusOffset = 15.0*mm;
  fAnodeRadius = fSTPCRadius - fAnodeRadiusOffset;
  //fAnodeThickness = 3.*mm;
  //fAnodeStandoff = 13.*mm;
  fAnodeThickness = 0.4*mm;
  fAnodeStandoff = 6.75*mm; //front face of charge tiles from vessel inner surface
  fAnodeZPosition = fSTPCHalfheight - fAnodeStandoff + fAnodeThickness/2.;

  fAnodeRef = 0.5;


  // -- SiPM
  fSiPMTotalHeight = fCathodeAnodeDistance; //1253.625*mm;
  //fSiPMPadHeight = 13.4164*mm;
  //fSiPMPadHeight = 22.36*mm; // Area of pad = 5 cm^2, Side length = sqrt(500 mm^2) = 22.36 mm
  fSiPMPadHeight = 7.5*mm; // Area of pad = 5 cm^2, Side length = sqrt(500 mm^2) = 22.36 mm
  //fSiPMPadThickness = 3.5*mm;
  fSiPMPadThickness = 2.*mm;
  fSiPMStandoffFromTPC = 3.*mm;
  fActiveSiPMPadFrac = 0.8;

  fSiPMActiveLayerThickness = 0.001*mm;
  fSiPMActiveLayerDepth = 1.*mm;
  fSiPMBaseLayerThickness = 0.5*mm;
  fSiPMWLSThickness = 0.1*mm;

  // Charge tiles
  fChargeModuleLength = 100.5*mm;
  fChargeModuleThickness = 0.5*mm;
  fChargeModuleBackingThickness = 0.5*mm;

  fChargeModuleGlueThickness = (0.03 * 25.4) *mm; // 30 mil
  fChargeModuleGlueRadius = 0.5 * (0.03 * 25.4) *mm;  // 30 mil diameter
  fChargeModuleGluePosition = 45.*mm; 

  fChargeModuleChipLength = 10.*mm;
  fChargeModuleChipThickness = 1.*mm;
  fChargeModuleChipPosition = 10.*mm;

  fChargeModuleSupportThickness = 3.*mm;
  fChargeModuleSupportWidth = 30.*mm;  //Width of rim, bridge and rungs
  
  fChargePadDiagonalLength = 3.*mm;
  fChargePadThickness = 0.001*mm;
  fChargePadLinkLength = 0.064*mm;
  fChargePadLinkHeight = 0.025*mm;
}

nEXODetectorConstruction::~nEXODetectorConstruction(){;}

G4VPhysicalVolume* nEXODetectorConstruction::Construct()
{
  nEXOMaterials::GetInstance();

  G4LogicalVolume* logicWorld = new G4LogicalVolume(new G4Box("World",100*mm, 100*mm, 100*mm), nEXOMaterials::GetInstance()->GetMaterial("G4_AIR"), "World");
  G4VPhysicalVolume* PhyWorld = new G4PVPlacement(0,
                                                  G4ThreeVector(0,0,0),
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

void nEXODetectorConstruction::BuildOtherParts(G4LogicalVolume* logicWorld)
{

  G4String sVesselName = "/nEXO/TPCInternals/sVessel";
  G4LogicalVolume* LogSVessel = new G4LogicalVolume(new G4Tubs(sVesselName,0,fSTPCRadius+fSTPCVesselSideThickness,fSTPCHalfheight,0.*deg,360.*deg),nEXOMaterials::GetInstance()->GetMaterial("G4_Cu"), sVesselName);
  G4VPhysicalVolume* PhySVessel = new G4PVPlacement(0,
                                  		    G4ThreeVector(0,0,0),
                                  	            LogSVessel,
                                  		    sVesselName,
                                  		    logicWorld,
                                  		    false,
                                  		    0,
                                                    fCheckOverlaps);

  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sVesselName, PhySVessel);

  G4String sTPCLXe = "/nEXO/TPCInternals/sTPCLXe";
  G4LogicalVolume* logicSLXe = new G4LogicalVolume(new G4Tubs(sTPCLXe,0,fSTPCRadius,fSTPCHalfheight,0.*deg,360.*deg),nEXOMaterials::GetInstance()->GetMaterial("liquidXe"), sTPCLXe);
  G4VPhysicalVolume* PhySTPCLXe = new G4PVPlacement(0,
                                                    G4ThreeVector(0,0,0),
                                                    logicSLXe,
                                                    sTPCLXe,
                                                    LogSVessel,
                                                    false,
                                                    0,
                                                    fCheckOverlaps);
  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(sTPCLXe, PhySTPCLXe);
  //G4PhysicalVolumeStore::GetInstance()->Register(PhySTPCLXe);
 
  G4cout <<"Small TPC name -----> " << sTPCLXe << G4endl;

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//############### Field Shaping Rings ##############//" << G4endl;
  G4cout << "//##################################################//" << G4endl;

  G4String fieldRingName = "/nEXO/TPCInternals/FieldRing";
  G4double fieldRingSweptR;

  //G4double fFieldRingLength = fFieldRingLength; 
  G4double fieldRingThick = fFieldRingThick/2.0;  //not used in default
  G4double fieldRingIR = 0*mm;  //not used in default
  G4double fieldRingOR = fieldRingThick;  //not used in default (fRingArrangeID == 2)

  G4LogicalVolume* logicFieldRing[10000] = {0};
  G4VPhysicalVolume* physFieldRing[10000] = {0};

  //G4int nFieldRings = (G4int) ((fCathodeAnodeDistance-1*cm)/fWWDistance);
  G4int nFieldRings = (G4int) ((fCathodeAnodeDistance-fCathodeToBottomRingDistance-fAnodeToTopRingDistance-fFieldRingThick)/fWWDistance + 1);
 
  // horizontal plate ring (Current baseline, Apr 2015)
  if(fRingArrangeID == 2) {
    G4cout << "Constructing field wire rings based on horizontal plate ring model." << G4endl;

    // Parameters for field rings
    //fieldRingSweptR = legRadialPosition; //inactiveLXeR2 - fRingSideDistance - fFieldRingLength/2.0;
    fieldRingSweptR = 61.25*mm; //inactiveLXeR2 - fRingSideDistance - fFieldRingLength/2.0;

    
    G4Tubs* midRing = new G4Tubs("MidFieldRing", fieldRingSweptR - fFieldRingLength/2.0, fieldRingSweptR + fFieldRingLength/2.0, fFieldRingThick/2.0, 0, 360*deg);
    G4LogicalVolume * logicFieldRingWithHoles = new G4LogicalVolume(midRing, nEXOMaterials::GetInstance()->GetMaterial("G4_Cu"), fieldRingName);
std::cout << "field shaping ring, length: " << fFieldRingLength << ", " << fFieldRingThick << ", " << fWWDistance << std::endl;
    for (G4int i = 0; i < nFieldRings; i++) {
      // Z position of field ring
      G4double fieldRingZPosition = fAnodeZPosition - fAnodeThickness/2. - fAnodeToTopRingDistance - fFieldRingThick/2. - i*fWWDistance;

      // Put field rings in place
      physFieldRing[i] = new G4PVPlacement(0,
                                           G4ThreeVector(0,0,fieldRingZPosition),
                                           logicFieldRingWithHoles,
                                           //midRingLog,
                                           fieldRingName,
                                           logicSLXe,
                                           false,
                                           i,fCheckOverlaps);
      nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(fieldRingName,physFieldRing[i],i);   

    }

    //Attributes of Field Rings
    G4VisAttributes* RingsAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0));
    RingsAtt->SetVisibility(true);
    RingsAtt->SetForceSolid(true);
    logicFieldRingWithHoles->SetVisAttributes(RingsAtt);
  }
 

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//####################### SiPM #####################//" << G4endl;
  G4cout << "//##################################################//" << G4endl;

  G4double fSiPMGlueThickness = (0.001* 25.4)*mm;
  G4double fSiPMSupportThickness = 3.*mm;
  G4double fSiPMElectronicsThickness = 1.*mm;
  G4double fSiPMCablesThickness = 1.*mm;
  G4double fSiPMCableWiresThickness = 0.4*mm;

  if (fInternalsFlag == 1){
    G4cout << "Building simplified SiPM geometry...\n";
  //  fSiPMPadHeight = fSiPMTotalHeight/2.;
  }
  
  G4int iSiPMPad = 0;
  if(fSiPMOption == 0){   // Default
    G4String SiPMName = "/nEXO/TPCInternals/SiPMPads";
    fNSiPMPadAlongZ = (G4int) (fSiPMTotalHeight/fSiPMPadHeight);
    G4double dGapAlongZ = (fSiPMTotalHeight - fSiPMPadHeight*fNSiPMPadAlongZ)/(fNSiPMPadAlongZ - 1);

    //G4int nSiPMPadAlongPhi[10000] = {0};

   G4LogicalVolume* logicSiPMPads[10000] = {0};
    //G4VPhysicalVolume* physSiPMPads[100000] = {0};

    G4LogicalVolume* logicActiveSiPMPads[10000] = {0};
    G4VPhysicalVolume* physActiveSiPMPads[10000] = {0};

    G4LogicalVolume* logicSiPMPadBase[10000] = {0};
    G4VPhysicalVolume* physSiPMPadBase[10000] = {0};

    G4LogicalVolume* logicWLS[10000] = {0};
    G4VPhysicalVolume* physWLS[10000] = {0};

    iSiPMPad = 0;

    for(G4int i = 0; i < fNSiPMPadAlongZ; i++) {

      // SiPM Pads
      //G4double SiPMPadPlaceZ = inactiveLXeH-13*mm-3*mm-11*mm-fSiPMPadHeight/2.0-i*fSiPMPadHeight-i*dGapAlongZ;
      G4double SiPMPadPlaceZ = fAnodeZPosition - (fCathodeAnodeDistance+0.4*mm-fSiPMTotalHeight)/2. -(0.5+i)*fSiPMPadHeight - i*dGapAlongZ;
      //G4double radius = inactiveLXeR2 + (inactiveLXeH - SiPMPadPlaceZ)*(inactiveLXeR1 - inactiveLXeR2)/(2*inactiveLXeH);
      G4double radius = fSTPCRadius;
      G4double SiPMOR = radius - fSiPMStandoffFromTPC;
      G4double SiPMIR = SiPMOR - fSiPMPadThickness;


      fNSiPMPadAlongPhi[i] = (G4int) (CLHEP::pi/atan(fSiPMPadHeight/(2*SiPMIR)));
      G4double SiPMPadDPhi = 2*atan(fSiPMPadHeight/(2*SiPMIR))*180/CLHEP::pi*deg;
      G4double dGapAlongPhi = (360.0*deg - SiPMPadDPhi*fNSiPMPadAlongPhi[i])/fNSiPMPadAlongPhi[i];

     logicSiPMPads[i] = new G4LogicalVolume(new G4Box(SiPMName,
					              fSiPMPadThickness/2,
						      fSiPMPadHeight/2,
						      fSiPMPadHeight/2), 
						      nEXOMaterials::GetInstance()->GetMaterial("G4_SILICON_DIOXIDE"),
						      SiPMName);
      
      // Put SiPM pads and electronics in place
      for(G4int j = 0; j < fNSiPMPadAlongPhi[i]; j++) {
        G4RotationMatrix* rotSiPMPad = new G4RotationMatrix();
        rotSiPMPad->rotateZ(j*(SiPMPadDPhi+dGapAlongPhi));

        // SiPM Pads
        G4double xpos = (SiPMIR+fSiPMPadThickness/2.)*cos(j*(SiPMPadDPhi+dGapAlongPhi));
        G4double ypos = (SiPMIR+fSiPMPadThickness/2.)*sin(j*(SiPMPadDPhi+dGapAlongPhi));
        G4VPhysicalVolume* physSiPMPad = new G4PVPlacement(rotSiPMPad,
                                                   G4ThreeVector(xpos,ypos,SiPMPadPlaceZ),
                                                   logicSiPMPads[i],
                                                   SiPMName,
                                                   logicSLXe,
                                                   false,
                                                   i*10000+j,fCheckOverlaps);

        nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(SiPMName,physSiPMPad,iSiPMPad);

        iSiPMPad++;

      }

      //G4cout << "//##################################################//" << G4endl;
      //G4cout << "//#################### ActiveSiPM ##################//" << G4endl;
      //G4cout << "//##################################################//" << G4endl;

      G4double ActiveSiPMPadIR = SiPMIR + fSiPMActiveLayerDepth;
      G4double ActiveSiPMPadOR = ActiveSiPMPadIR + fSiPMActiveLayerThickness;
      
      G4String ActiveSiPMName = "/nEXO/TPCInternals/ActiveSiPMPads";
      //G4double ActiveSiPMPadR = SiPMR + fSiPMActiveLayerDepth;
      //G4double ActiveSiPMPadHeight = fSiPMPadHeight*sqrt(fActiveSiPMPadFrac);
      G4double ActiveSiPMPadHeight = 5.95*mm;
      //G4double ActiveSiPMPadDPhi = SiPMPadDPhi*sqrt(fActiveSiPMPadFrac);

      logicActiveSiPMPads[i] = new G4LogicalVolume(new G4Box(ActiveSiPMName,
                                                              fSiPMActiveLayerThickness/2,
							      ActiveSiPMPadHeight/2,
							      ActiveSiPMPadHeight/2),
                                                   nEXOMaterials::GetInstance()->GetMaterial("G4_Si"),
                                                   ActiveSiPMName);

      physActiveSiPMPads[i] = new G4PVPlacement(0,
                                                G4ThreeVector(-fSiPMPadThickness/2.+fSiPMActiveLayerDepth+fSiPMActiveLayerThickness/2.0,0,0),
                                                logicActiveSiPMPads[i],
                                                ActiveSiPMName,
                                                logicSiPMPads[i],
                                                false,
                                                0,fCheckOverlaps);
      
      nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(ActiveSiPMName,physActiveSiPMPads[i],i);   
      
      //G4cout << "//##################################################//" << G4endl;
      //G4cout << "//################### SiPMPadBase ##################//" << G4endl;
      //G4cout << "//##################################################//" << G4endl;


      G4String SiPMPadBaseName = "/nEXO/TPCInternals/SiPMPadBase";
      G4double SiPMPadBaseHeight = fSiPMPadHeight;
        
      logicSiPMPadBase[i] = new G4LogicalVolume(new G4Box(SiPMPadBaseName,
                                                           fSiPMBaseLayerThickness/2, SiPMPadBaseHeight/2.0,
                                                           SiPMPadBaseHeight/2.0),
                                                nEXOMaterials::GetInstance()->GetMaterial("G4_Si"),
                                                SiPMPadBaseName);                                                                                                                 
      physSiPMPadBase[i] = new G4PVPlacement(0,
                                          G4ThreeVector(-fSiPMPadThickness/2.+fSiPMActiveLayerDepth+fSiPMActiveLayerThickness+fSiPMBaseLayerThickness/2,0,0),
                                          logicSiPMPadBase[i],
                                          SiPMPadBaseName,
                                          logicSiPMPads[i],
                                          false,
                                          0,fCheckOverlaps);

      nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(SiPMPadBaseName,physSiPMPadBase[i],i);   

    }

    G4VisAttributes* SiPMAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));  
    SiPMAtt->SetVisibility(true);
    G4VisAttributes* ActiveSiPMAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 1.0));  
    ActiveSiPMAtt->SetVisibility(true);
    G4VisAttributes* SiPMBaseAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.5));  
    SiPMBaseAtt->SetVisibility(true);
    //G4VisAttributes* SiPMElectronicsAtt = new G4VisAttributes(G4Colour(0.25, 0.5, 1.0));  
    //SiPMElectronicsAtt->SetVisibility(true);
    //SiPMAtt->SetForceSolid(true);
    //logicSiPMs->SetVisAttributes(SiPMAtt);
    for(G4int i = 0; i < fNSiPMPadAlongZ; i++) {
      logicSiPMPads[i]->SetVisAttributes(SiPMAtt);
      logicActiveSiPMPads[i]->SetVisAttributes(ActiveSiPMAtt);
      logicSiPMPadBase[i]->SetVisAttributes(SiPMBaseAtt);
      //logicSiPMElectronics[i]->SetVisAttributes(SiPMElectronicsAtt);
    }
  }

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//################# Anode Platters #################//" << G4endl;
  G4cout << "//##################################################//" << G4endl;
  G4String AnodeName = "/nEXO/TPCInternals/Anode";

  if((fSiPMOption == 0 || fSiPMOption ==2) && fAnodeOption == 0) {  // Baseline Apr 2015

    G4Tubs * solidAnode = new G4Tubs(AnodeName, 0.*mm, fAnodeRadius, fAnodeThickness/2., 0*deg, 360*deg);

    G4LogicalVolume* logicAnode = new G4LogicalVolume(solidAnode, nEXOMaterials::GetInstance()->GetMaterial("G4_SILICON_DIOXIDE"), AnodeName);
    //G4LogicalVolume* logicAnode = new G4LogicalVolume(solidAnode, nEXOMaterials::GetInstance()->GetMaterial("G4_Cu"), AnodeName);

    G4VPhysicalVolume* physAnode = new G4PVPlacement(0,
                                                     G4ThreeVector(0,0, fAnodeZPosition),
                                                     logicAnode,
                                                     AnodeName,
                                                     logicSLXe,
                                                     false,
                                                     0,fCheckOverlaps);

    nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(AnodeName,physAnode);   
    G4VisAttributes* AnodeAtt = new G4VisAttributes(G4Colour(0.5, 1.0, 0.5));
    AnodeAtt->SetVisibility(true);
    //APDPlattAtt->SetForceSolid(true);
    logicAnode->SetVisAttributes(AnodeAtt);

  }
  
  G4cout << "//##################################################//" << G4endl;
  G4cout << "//################# Cathode Platters ###############//" << G4endl;
  G4cout << "//##################################################//" << G4endl;

  G4String CathodeName = "/nEXO/TPCInternals/Cathode";

  G4LogicalVolume* logicCathode = new G4LogicalVolume(new G4Tubs(CathodeName,
                                                                 //0.*mm, fCathodeRadius-fBulgeRadius,
                                                                 0.*mm, fCathodeRadius,
                                                                 fCathodeThickness/2.,
                                                                 0*deg,360*deg),
                                                      nEXOMaterials::GetInstance()->GetMaterial("G4_Cu"),
                                                      CathodeName);
  
  G4VPhysicalVolume* physCathode = new G4PVPlacement(0,
                                                     G4ThreeVector(0,0, fCathodeZPosition),
                                                     logicCathode,
                                                     CathodeName,
                                                     logicSLXe,
                                                     false,
                                                     0,fCheckOverlaps);
  nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(CathodeName,physCathode);   

  G4VisAttributes* CathodeAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 1.0));
  CathodeAtt->SetVisibility(true);
  logicCathode->SetVisAttributes(CathodeAtt);

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//#################### Bulge #######################//" << G4endl;
  G4cout << "//##################################################//" << G4endl;

  G4String BulgeName = "/nEXO/TPCInternals/Bulge";
                                       
}

void nEXODetectorConstruction::SetOpticalSurfaces()
{
 
  G4double* RefSpecularlobe = new  G4double[2];
  RefSpecularlobe[0] = 1.0;
  RefSpecularlobe[1] = 1.0;
  G4double* RefSpecularspike = new  G4double[2];
  RefSpecularspike[0] = 0.0;
  RefSpecularspike[1] = 0.0;
  G4double* RefBackscatter = new  G4double[2];
  RefBackscatter[0] = 0.0;
  RefBackscatter[1] = 0.0;
  
  G4double* fieldRingReflectivity = new  G4double[2];
  fieldRingReflectivity[0] = fFieldRingRef;
  fieldRingReflectivity[1] = fFieldRingRef;

  G4double* anodeReflectivity = new  G4double[2];
  anodeReflectivity[0] = fAnodeRef;
  anodeReflectivity[1] = fAnodeRef;

  G4double* cathodeReflectivity = new  G4double[2];
  cathodeReflectivity[0] = fCathodeRef;
  cathodeReflectivity[1] = fCathodeRef;

  G4double* bulgeReflectivity = new  G4double[2];
  bulgeReflectivity[0] = fBulgeRef;
  bulgeReflectivity[1] = fBulgeRef;

  G4double* tpcVesselReflectivity = new  G4double[2];
  tpcVesselReflectivity[0] = fTPCVesselRef;
  tpcVesselReflectivity[1] = fTPCVesselRef;

  G4double* teflonReflectivity = new  G4double[2];
  teflonReflectivity[0] = fTeflonRef;
  teflonReflectivity[1] = fTeflonRef;

  std::cout << "Reflectivity of field ring is " << fFieldRingRef << std::endl;
  std::cout << "Reflectivity of anode is " << fAnodeRef << std::endl;
  std::cout << "Reflectivity of cathode is " << fCathodeRef << std::endl;
  std::cout << "Reflectivity of bulge is " << fBulgeRef << std::endl;
  std::cout << "Reflectivity of teflon is " << fTeflonRef << std::endl;
  //std::cout << "Reflectivity of TPC vessel is " << fTPCVesselRef << std::endl;

  G4double* photonULEnergies = new G4double[2];
  photonULEnergies[0] = (4.13566743E-15*299792458/(144.5*1.E-9))*eV; 
  photonULEnergies[1] = (4.13566743E-15*299792458/(2058.2*1.E-9))*eV;

  //Optical SiO2 and Pd Surfaces
  const G4int nSiEntries = 44;
  //cubic silicon
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

  //set optical surface for SiPMPadBase and SiO2
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
    for(G4int i = 0; i < fNSiPMPadAlongZ; i++) {
      for(G4int j = 0; j < fNSiPMPadAlongPhi[i]; j++) {
        new G4LogicalBorderSurface("SiPMBaseRefSurface",
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/SiPMPads", iSiPMPad), // physiSiPMPads[iSiPMPad],
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/SiPMPadBase", i),     // physiSiPMBase[i],
                                   SiPMBaseRefOpSurface);
        new G4LogicalBorderSurface("SiPMBaseRefSurface",
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/SiPMPadBase", i),     // physiSiPMBase[i],
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/SiPMPads", iSiPMPad), // physiSiPMPads[iSiPMPad],
                                   SiPMBaseRefOpSurface);

        new G4LogicalBorderSurface("ActiveSiPMRefSurface",
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/SiPMPads", iSiPMPad), // physiSiPMPads[iSiPMPad],
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/ActiveSiPMPads", i),  // physiActiveSiPMPads[i],
                                   ActiveSiPMRefOpSurface);
        new G4LogicalBorderSurface("ActiveSiPMRefSurface",
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/ActiveSiPMPads", i),  // physiActiveSiPMPads[i],
                                   nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/SiPMPads", iSiPMPad), // physiSiPMPads[iSiPMPad],
                                   ActiveSiPMRefOpSurface);
        iSiPMPad++;
      }
    }           
  }

  G4MaterialPropertiesTable* SiPMRefOpticalMPT  = new G4MaterialPropertiesTable();
  SiPMRefOpticalMPT->AddProperty("REALRINDEX", SiliconPhotonEnergy, siliconRealRefractiveIndex, nSiEntries);
  SiPMRefOpticalMPT->AddProperty("IMAGINARYRINDEX", SiliconPhotonEnergy, siliconImaginaryRefractiveIndex, nSiEntries);

  SiPMBaseRefOpSurface->SetMaterialPropertiesTable(SiPMRefOpticalMPT);
  ActiveSiPMRefOpSurface->SetMaterialPropertiesTable(SiPMRefOpticalMPT);

  //set optical surface for ActiveSiPMPad and SiO2

  G4VPhysicalVolume* physActiveLXe = nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/LXe/ActiveRegion");
  
  //set optical surface for field shaping rings
  G4OpticalSurface* fieldRingRefOpSurface = new G4OpticalSurface("fieldRingRefOpSurface");
  if(fRingArrangeID==5){
      new G4LogicalBorderSurface("fieldRingRefSurface",nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("RingVirtual",0),
              nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/FieldRing",0),//physiFieldRing[i],
              fieldRingRefOpSurface);
  }
  else{
//    G4LogicalBorderSurface* fieldRingRefSurface[10000] = {0};
    for(int i = 0; i < 10000; i++) {
      if(nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/FieldRing",i) != NULL)
       new G4LogicalBorderSurface("fieldRingRefSurface",
                                                          physActiveLXe,
                                                          nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/FieldRing",i),//physiFieldRing[i],
                                                          fieldRingRefOpSurface);
    }
  }
  fieldRingRefOpSurface->SetModel(unified);
  fieldRingRefOpSurface->SetType(dielectric_metal);
  fieldRingRefOpSurface->SetFinish(polished);

  G4MaterialPropertiesTable* fieldRingRefOpticalMPT  = new G4MaterialPropertiesTable();
  fieldRingRefOpticalMPT->AddProperty("REFLECTIVITY", photonULEnergies, fieldRingReflectivity, 2);
  //fieldRingRefOpticalMPT->AddProperty("SPECULARLOBECONSTANT", photonULEnergies, RefSpecularlobe, 2);
  //fieldRingRefOpticalMPT->AddProperty("SPECULARSPIKECONSTANT", photonULEnergies, RefSpecularspike, 2);
  //fieldRingRefOpticalMPT->AddProperty("BACKSCATTERCONSTANT", photonULEnergies, RefBackscatter, 2);

  fieldRingRefOpSurface->SetMaterialPropertiesTable(fieldRingRefOpticalMPT);
  
  //set optical surface for anode
  G4OpticalSurface* anodeRefOpSurface = new G4OpticalSurface("anodeRefOpSurface");
  if(fSiPMOption == 0) {
    new G4LogicalBorderSurface("anodeRefSurface",
                                                 physActiveLXe,
                                                 nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/Anode"), // physiAnode,
                                                 anodeRefOpSurface);
  }


  anodeRefOpSurface->SetModel(unified);
  anodeRefOpSurface->SetType(dielectric_metal);
  anodeRefOpSurface->SetFinish(polished);

  G4MaterialPropertiesTable* anodeRefOpticalMPT  = new G4MaterialPropertiesTable();
  anodeRefOpticalMPT->AddProperty("REFLECTIVITY", photonULEnergies, anodeReflectivity, 2);

  anodeRefOpSurface->SetMaterialPropertiesTable(anodeRefOpticalMPT);

  //set optical surface for cathode
  G4OpticalSurface* cathodeRefOpSurface = new G4OpticalSurface("cathodeRefOpSurface");
  new G4LogicalBorderSurface("cathodeRefSurface",
                                             physActiveLXe,
                                             nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/Cathode"), // physiCathode,
                                             cathodeRefOpSurface);

  cathodeRefOpSurface->SetModel(unified);
  cathodeRefOpSurface->SetType(dielectric_metal);
  cathodeRefOpSurface->SetFinish(polished);

  G4MaterialPropertiesTable* cathodeRefOpticalMPT  = new G4MaterialPropertiesTable();
  cathodeRefOpticalMPT->AddProperty("REFLECTIVITY", photonULEnergies, cathodeReflectivity, 2);
  //cathodeRefOpticalMPT->AddProperty("SPECULARLOBECONSTANT", photonULEnergies, RefSpecularlobe, 2);
  //cathodeRefOpticalMPT->AddProperty("SPECULARSPIKECONSTANT", photonULEnergies, RefSpecularspike, 2);
  //cathodeRefOpticalMPT->AddProperty("BACKSCATTERCONSTANT", photonULEnergies, RefBackscatter, 2);

  cathodeRefOpSurface->SetMaterialPropertiesTable(cathodeRefOpticalMPT);

  //set optical surface for bulge
  G4OpticalSurface* bulgeRefOpSurface = new G4OpticalSurface("bulgeRefOpSurface");
   new G4LogicalBorderSurface("bulgeRefSurface",
                                             physActiveLXe,
                                             nEXOSimplePhysVolManager::GetInstance()->GetPhysicalVolume("/nEXO/TPCInternals/Bulge"), // physiBulge,
                                             bulgeRefOpSurface);

  bulgeRefOpSurface->SetModel(unified);
  bulgeRefOpSurface->SetType(dielectric_metal);
  bulgeRefOpSurface->SetFinish(polished);

  G4MaterialPropertiesTable* bulgeRefOpticalMPT  = new G4MaterialPropertiesTable();
  bulgeRefOpticalMPT->AddProperty("REFLECTIVITY", photonULEnergies, bulgeReflectivity, 2);
  //bulgeRefOpticalMPT->AddProperty("SPECULARLOBECONSTANT", photonULEnergies, RefSpecularlobe, 2);
  //bulgeRefOpticalMPT->AddProperty("SPECULARSPIKECONSTANT", photonULEnergies, RefSpecularspike, 2);
  //bulgeRefOpticalMPT->AddProperty("BACKSCATTERCONSTANT", photonULEnergies, RefBackscatter, 2);

  bulgeRefOpSurface->SetMaterialPropertiesTable(bulgeRefOpticalMPT);

}
