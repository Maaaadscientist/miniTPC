#include "miniTPCDetectorConstruction.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "nEXOMaterials.hh"
#include "nEXOSimplePhysVolManager.hh"


miniTPCDetectorConstruction::miniTPCDetectorConstruction()
{
  fCheckOverlaps = false;
  fRingArrangeID = 20;
  fSiPMOption = 0;
  
  fTeflonRef = 0.95;
  fTPCVesselRef = 0.0;
  fSTeflonRef = 0.95;
  fSTPCVesselRef = 0.0;
  fFieldRingRef = 0.8;
  fCathodeRef = 0.8;
  fBulgeRef = 0.8;
  fAnodeRef = 0.5;
  
  
  
  fSTPCRadius = 80*mm;
  fSTPCVesselSideThickness = 10*mm;
  fSTPCHalfheight = 85*mm;

  // Parameters for field rings
  nFieldRings = 6;//Ring number of miniTPC
  fTopRingZPosition = 50*mm;
  fieldRingSweptR = 62.5*mm;
  fFieldRingLength = 2*mm;
  fFieldRingThick = 2*mm;
  fWWDistance = 20*mm;

  // Parameters for Anode/Cathode
  fAnodeRadius = 62.5*mm;
  fAnodeThickness = 2*mm;
  fAnodeZPosition = fSTPCHalfheight-fAnodeThickness/2.0;
  fCathodeRadius = 62.5*mm;
  fCathodeThickness = 2*mm;
  fCathodeZPosition = -fSTPCHalfheight+fCathodeThickness/2.0;

  // Parameters for Simple SiPM
  fNSiPMPadAlongZ = 14;
  fNSiPMPadAlongPhi = 14*4; 
  dGapAlongZ = 1*mm;
  fTopSiPMZPosition = 50*mm;
  fSiPMPadThickness = 2*mm; 
  fSiPMPadHeight = 7.5*mm;
  fSiPMStandoffFromTPC = 5*mm;
  
  fSiPMActiveLayerThickness = 0.001*mm;
  fSiPMActiveLayerDepth = 1.*mm;
  fActiveSiPMPadHeight = 5.95*mm;
  
  fSiPMBaseLayerThickness = 0.5*mm;
  fSiPMPadBaseHeight = fSiPMPadHeight;
}

miniTPCDetectorConstruction::~miniTPCDetectorConstruction(){;}

G4VPhysicalVolume* miniTPCDetectorConstruction::Construct()
{
  nEXOMaterials::GetInstance();

  G4LogicalVolume* logicWorld = new G4LogicalVolume(new G4Box("World",500*mm, 500*mm, 500*mm), nEXOMaterials::GetInstance()->GetMaterial("G4_AIR"), "World");
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

void miniTPCDetectorConstruction::BuildOtherParts(G4LogicalVolume* logicWorld)
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
  

  G4LogicalVolume* logicFieldRing[10000] = {0};
  G4VPhysicalVolume* physFieldRing[10000] = {0};
    
  G4Tubs* midRing = new G4Tubs("MidFieldRing", fieldRingSweptR - fFieldRingLength/2.0, fieldRingSweptR + fFieldRingLength/2.0, fFieldRingThick/2.0, 0, 360*deg);
  G4LogicalVolume * logicFieldRingWithHoles = new G4LogicalVolume(midRing, nEXOMaterials::GetInstance()->GetMaterial("G4_Cu"), fieldRingName);
  std::cout << "field shaping ring, length: " << fFieldRingLength << ", " << fFieldRingThick << ", " << fWWDistance << std::endl;
  
  for (G4int i = 0; i < nFieldRings; i++) {
      // Z position of field ring
      G4double fieldRingZPosition = fTopRingZPosition - i*fWWDistance;

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
 

  G4cout << "//##################################################//" << G4endl;
  G4cout << "//################# Anode Platters #################//" << G4endl;
  G4cout << "//##################################################//" << G4endl;
  
  G4String AnodeName = "/nEXO/TPCInternals/Anode";

  G4Tubs * solidAnode = new G4Tubs(AnodeName, 0.*mm, fAnodeRadius, fAnodeThickness/2., 0*deg, 360*deg);
  G4LogicalVolume* logicAnode = new G4LogicalVolume(solidAnode, nEXOMaterials::GetInstance()->GetMaterial("G4_SILICON_DIOXIDE"), AnodeName);
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
    logicAnode->SetVisAttributes(AnodeAtt);

  
  G4cout << "//##################################################//" << G4endl;
  G4cout << "//################# Cathode Platters ###############//" << G4endl;
  G4cout << "//##################################################//" << G4endl;

  G4String CathodeName = "/nEXO/TPCInternals/Cathode";

  G4LogicalVolume* logicCathode = new G4LogicalVolume(new G4Tubs(CathodeName,
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
  G4cout << "//####################### SiPM #####################//" << G4endl;
  G4cout << "//##################################################//" << G4endl;
  
    G4String SiPMName = "/nEXO/TPCInternals/SiPMPads";
    G4int iSiPMPad = 0;


    G4LogicalVolume* logicSiPMPads[10000] = {0};
    G4VPhysicalVolume* physSiPMPads[10000] = {0};

    G4LogicalVolume* logicActiveSiPMPads[10000] = {0};
    G4VPhysicalVolume* physActiveSiPMPads[10000] = {0};

    G4LogicalVolume* logicSiPMPadBase[10000] = {0};
    G4VPhysicalVolume* physSiPMPadBase[10000] = {0};

    for(G4int i = 0; i < fNSiPMPadAlongZ; i++) {

      // SiPM Pads
      G4double SiPMPadPlaceZ = fTopSiPMZPosition-i*fSiPMPadHeight - i*dGapAlongZ;
      G4double radius = fSTPCRadius;
      G4double SiPMOR = radius - fSiPMStandoffFromTPC;
      G4double SiPMIR = SiPMOR - fSiPMPadThickness;


      G4double SiPMPadDPhi = (G4double) 2*CLHEP::pi/fNSiPMPadAlongPhi;

      logicSiPMPads[i] = new G4LogicalVolume(new G4Box(SiPMName,
					                         fSiPMPadThickness/2,
						                     fSiPMPadHeight/2,
						                     fSiPMPadHeight/2), 
						                     nEXOMaterials::GetInstance()->GetMaterial("G4_SILICON_DIOXIDE"),
						                     SiPMName);
      
      // Put SiPM pads and electronics in place
      for(G4int j = 0; j < fNSiPMPadAlongPhi; j++) {
        G4int sipmID = i*fNSiPMPadAlongPhi+j;
        G4RotationMatrix* rotSiPMPad = new G4RotationMatrix();
        rotSiPMPad->rotateZ(j*SiPMPadDPhi);

        // SiPM Pads
        G4double xpos = (SiPMIR+fSiPMPadThickness/2.)*cos(j*SiPMPadDPhi);
        G4double ypos = (SiPMIR+fSiPMPadThickness/2.)*sin(j*SiPMPadDPhi);
        
        physSiPMPads[sipmID] = new G4PVPlacement(rotSiPMPad,
                                                   G4ThreeVector(xpos,ypos,SiPMPadPlaceZ),
                                                   logicSiPMPads[i],
                                                   SiPMName,
                                                   logicSLXe,
                                                   false,
                                                   i*10000+j,fCheckOverlaps);

        nEXOSimplePhysVolManager::GetInstance()->AddPhysicalVolume(SiPMName,physSiPMPads[sipmID],iSiPMPad);

        iSiPMPad++;

      }

      G4cout << "//##################################################//" << G4endl;
      G4cout << "//#################### ActiveSiPM ##################//" << G4endl;
      G4cout << "//##################################################//" << G4endl;

      
      G4double ActiveSiPMPadIR = SiPMIR + fSiPMActiveLayerDepth;
      G4double ActiveSiPMPadOR = ActiveSiPMPadIR + fSiPMActiveLayerThickness;
      
      G4String ActiveSiPMName = "/nEXO/TPCInternals/ActiveSiPMPads";

      logicActiveSiPMPads[i] = new G4LogicalVolume(new G4Box(ActiveSiPMName,
                                                             fSiPMActiveLayerThickness/2,
							                                 fActiveSiPMPadHeight/2,
							                                 fActiveSiPMPadHeight/2),
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
      
      G4cout << "//##################################################//" << G4endl;
      G4cout << "//################### SiPMPadBase ##################//" << G4endl;
      G4cout << "//##################################################//" << G4endl;


      G4String SiPMPadBaseName = "/nEXO/TPCInternals/SiPMPadBase";
      
        
      logicSiPMPadBase[i] = new G4LogicalVolume(new G4Box(SiPMPadBaseName,
                                                           fSiPMBaseLayerThickness/2, fSiPMPadBaseHeight/2.0,
                                                           fSiPMPadBaseHeight/2.0),
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
    
    for(G4int i = 0; i < fNSiPMPadAlongZ; i++) {
      logicSiPMPads[i]->SetVisAttributes(SiPMAtt);
      logicActiveSiPMPads[i]->SetVisAttributes(ActiveSiPMAtt);
      logicSiPMPadBase[i]->SetVisAttributes(SiPMBaseAtt);
    }

      G4cout << "//##################################################//" << G4endl;
      G4cout << "//############### Check the Overlap ################//" << G4endl;
      G4cout << "//##################################################//" << G4endl;
        
        
  physAnode->CheckOverlaps();
  physCathode->CheckOverlaps();

  for (G4int i = 0; i < nFieldRings; i++) {
      G4bool overlaps = physFieldRing[i]->CheckOverlaps();
      if (overlaps) {
        G4cout << i <<" Ring is Overlap" << G4endl;
      } 
  }

  for (G4int i = 0; i < fNSiPMPadAlongZ; i++) {
    for (G4int j = 0; j < fNSiPMPadAlongPhi; j++) {
         G4int id = i*fNSiPMPadAlongPhi+j;
         G4bool overlaps = physSiPMPads[id]->CheckOverlaps();
         if (overlaps) {
            G4cout << id <<" SiPM is Overlap" << G4endl;
         } 
    }
  }

}

void miniTPCDetectorConstruction::SetOpticalSurfaces()
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
      for(G4int j = 0; j < fNSiPMPadAlongPhi; j++) {
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
