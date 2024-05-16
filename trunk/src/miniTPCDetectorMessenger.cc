#include "miniTPCDetectorMessenger.hh"
#include "miniTPCDetectorConstruction.hh"

miniTPCDetectorMessenger::miniTPCDetectorMessenger(miniTPCDetectorConstruction* construct)
  : G4UImessenger(), fConstructor(construct){

    fDetDirectory = new G4UIdirectory("/nEXO/TPCInternals/");
    fDetDirectory->SetGuidance("Detector construction control");

    fCheckoverlapsCmd = new G4UIcmdWithABool(CommandName("fCheckOverlaps"),this);
    fCheckoverlapsCmd->SetParameterName("fCheckOverlaps",false);
    fCheckoverlapsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fTPCVesselRefCmd = new G4UIcmdWithADouble(CommandName("TPCVesselRef"),this);
    fTPCVesselRefCmd->SetParameterName("TPCVesselRef",false);
    fTPCVesselRefCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fFieldRingRefCmd = new G4UIcmdWithADouble(CommandName("FieldRingRef"),this);
    fFieldRingRefCmd->SetParameterName("FieldRingRef",false);
    fFieldRingRefCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fAnodeRefCmd = new G4UIcmdWithADouble(CommandName("AnodeRef"),this);
    fAnodeRefCmd->SetParameterName("AnodeRef",false);
    fAnodeRefCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fCathodeRefCmd = new G4UIcmdWithADouble(CommandName("CathodeRef"),this);
    fCathodeRefCmd->SetParameterName("CathodeRef",false);
    fCathodeRefCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fBulgeRefCmd = new G4UIcmdWithADouble(CommandName("BulgeRef"),this);
    fBulgeRefCmd->SetParameterName("BulgeRef",false);
    fBulgeRefCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fTeflonRefCmd = new G4UIcmdWithADouble(CommandName("TeflonRef"),this);
    fTeflonRefCmd->SetParameterName("TeflonRef",false);
    fTeflonRefCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSTeflonRefCmd = new G4UIcmdWithADouble(CommandName("STeflonRef"),this);
    fSTeflonRefCmd->SetParameterName("STeflonRef",false);
    fSTeflonRefCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSTPCVesselRefCmd = new G4UIcmdWithADouble(CommandName("STPCVesselRef"),this);
    fSTPCVesselRefCmd->SetParameterName("STPCVesselRef",false);
    fSTPCVesselRefCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSTPCRadiusCmd = new G4UIcmdWithADoubleAndUnit(CommandName("STPCRadius"),this);
    fSTPCRadiusCmd->SetParameterName("STPCRadius",false);
    fSTPCRadiusCmd->SetUnitCategory("Length");
    fSTPCRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSTPCVesselSideThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("STPCVesselSideThickness"),this);
    fSTPCVesselSideThicknessCmd->SetParameterName("STPCVesselSideThickness",false);
    fSTPCVesselSideThicknessCmd->SetUnitCategory("Length");
    fSTPCVesselSideThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSTPCHalfheightCmd = new G4UIcmdWithADoubleAndUnit(CommandName("STPCHalfheight"),this);
    fSTPCHalfheightCmd->SetParameterName("STPCHalfheight",false);
    fSTPCHalfheightCmd->SetUnitCategory("Length");
    fSTPCHalfheightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    nFieldRingsCmd = new G4UIcmdWithAnInteger(CommandName("nFieldRings"),this);
    nFieldRingsCmd->SetParameterName("nFieldRings",false);
    nFieldRingsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
    fWWDistanceCmd = new G4UIcmdWithADoubleAndUnit(CommandName("wwDistance"),this);
    fWWDistanceCmd->SetGuidance("Define distance between wires");
    fWWDistanceCmd->SetParameterName("wwDistance",false);
    fWWDistanceCmd->SetUnitCategory("Length");
    fWWDistanceCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fTopRingZPositionCmd = new G4UIcmdWithADoubleAndUnit(CommandName("TopRingZPositio"),this);
    fTopRingZPositionCmd->SetParameterName("TopRingZPositio",false);
    fTopRingZPositionCmd->SetUnitCategory("Length");
    fTopRingZPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fieldRingSweptRCmd = new G4UIcmdWithADoubleAndUnit(CommandName("fieldRingSweptR"),this);
    fieldRingSweptRCmd->SetParameterName("fieldRingSweptR",false);
    fieldRingSweptRCmd->SetUnitCategory("Length");
    fieldRingSweptRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fFieldRingLengthCmd = new G4UIcmdWithADoubleAndUnit(CommandName("FieldRingLength"),this);
    fFieldRingLengthCmd->SetParameterName("FieldRingLength",false);
    fFieldRingLengthCmd->SetUnitCategory("Length");
    fFieldRingLengthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fFieldRingThickCmd = new G4UIcmdWithADoubleAndUnit(CommandName("FieldRingThick"),this);
    fFieldRingThickCmd->SetParameterName("FieldRingThick",false);
    fFieldRingThickCmd->SetUnitCategory("Length");
    fFieldRingThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fAnodeRadiusCmd = new G4UIcmdWithADoubleAndUnit(CommandName("AnodeRadius"),this);
    fAnodeRadiusCmd->SetParameterName("AnodeRadius",false);
    fAnodeRadiusCmd->SetUnitCategory("Length");
    fAnodeRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fAnodeThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("AnodeThickness"),this);
    fAnodeThicknessCmd->SetParameterName("AnodeThickness",false);
    fAnodeThicknessCmd->SetUnitCategory("Length");
    fAnodeThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fAnodeZPositionCmd = new G4UIcmdWithADoubleAndUnit(CommandName("AnodeZPosition"),this);
    fAnodeZPositionCmd->SetParameterName("AnodeZPosition",false);
    fAnodeZPositionCmd->SetUnitCategory("Length");
    fAnodeZPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fCathodeRadiusCmd = new G4UIcmdWithADoubleAndUnit(CommandName("CathodeRadius"),this);
    fCathodeRadiusCmd->SetParameterName("CathodeRadius",false);
    fCathodeRadiusCmd->SetUnitCategory("Length");
    fCathodeRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fCathodeThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("CathodeThickness"),this);
    fCathodeThicknessCmd->SetParameterName("CathodeThickness",false);
    fCathodeThicknessCmd->SetUnitCategory("Length");
    fCathodeThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fCathodeZPositionCmd = new G4UIcmdWithADoubleAndUnit(CommandName("CathodeZPosition"),this);
    fCathodeZPositionCmd->SetParameterName("CathodeZPosition",false);
    fCathodeZPositionCmd->SetUnitCategory("Length");
    fCathodeZPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
    fNSiPMPadAlongZCmd = new G4UIcmdWithAnInteger(CommandName("fNSiPMPadAlongZ"),this);
    fNSiPMPadAlongZCmd->SetParameterName("fNSiPMPadAlongZ",false);
    fNSiPMPadAlongZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
    fNSiPMPadAlongPhiCmd = new G4UIcmdWithAnInteger(CommandName("fNSiPMPadAlongPhi"),this);
    fNSiPMPadAlongPhiCmd->SetParameterName("fNSiPMPadAlongPhi",false);
    fNSiPMPadAlongPhiCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
    dGapAlongZCmd = new G4UIcmdWithADoubleAndUnit(CommandName("dGapAlongZ"),this);
    dGapAlongZCmd->SetParameterName("dGapAlongZ",false);
    dGapAlongZCmd->SetUnitCategory("Length");
    dGapAlongZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fTopSiPMZPositionCmd = new G4UIcmdWithADoubleAndUnit(CommandName("TopSiPMZPosition"),this);
    fTopSiPMZPositionCmd->SetParameterName("TopSiPMZPosition",false);
    fTopSiPMZPositionCmd->SetUnitCategory("Length");
    fTopSiPMZPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSiPMPadThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMPadThickness"),this);
    fSiPMPadThicknessCmd->SetParameterName("SiPMPadThickness",false);
    fSiPMPadThicknessCmd->SetUnitCategory("Length");
    fSiPMPadThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSiPMPadHeightCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMPadHeight"),this);
    fSiPMPadHeightCmd->SetParameterName("SiPMPadHeight",false);
    fSiPMPadHeightCmd->SetUnitCategory("Length");
    fSiPMPadHeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSiPMStandoffFromTPCCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMStandoffFromTPC"),this);
    fSiPMStandoffFromTPCCmd->SetParameterName("SiPMStandoffFromTPC",false);
    fSiPMStandoffFromTPCCmd->SetUnitCategory("Length");
    fSiPMStandoffFromTPCCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSiPMActiveLayerThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMActiveLayerThickness"),this);
    fSiPMActiveLayerThicknessCmd->SetParameterName("SiPMActiveLayerThickness",false);
    fSiPMActiveLayerThicknessCmd->SetUnitCategory("Length");
    fSiPMActiveLayerThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSiPMActiveLayerDepthCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMActiveLayerDepth"),this);
    fSiPMActiveLayerDepthCmd->SetParameterName("SiPMActiveLayerDepth",false);
    fSiPMActiveLayerDepthCmd->SetUnitCategory("Length");
    fSiPMActiveLayerDepthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSiPMBaseLayerThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMBaseLayerThickness"),this);
    fSiPMBaseLayerThicknessCmd->SetParameterName("SiPMBaseLayerThickness",false);
    fSiPMBaseLayerThicknessCmd->SetUnitCategory("Length");
    fSiPMBaseLayerThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSiPMPadBaseHeightCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMPadBaseHeight"),this);
    fSiPMPadBaseHeightCmd->SetParameterName("SiPMPadBaseHeight",false);
    fSiPMPadBaseHeightCmd->SetUnitCategory("Length");
    fSiPMPadBaseHeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fRingArrangeIDCmd = new G4UIcmdWithAnInteger(CommandName("RingArrangeID"),this);
    fRingArrangeIDCmd->SetParameterName("RingArrangeID",false);
    fRingArrangeIDCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fSiPMOptionCmd = new G4UIcmdWithAnInteger(CommandName("SiPMOption"),this);
    fSiPMOptionCmd->SetParameterName("SiPMOption",false);
    fSiPMOptionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fWavelengthRefCmd = new G4UIcmdWithAnInteger(CommandName("WavelengthRef"),this);
    fWavelengthRefCmd->SetParameterName("WavelengthRef",false);
    fWavelengthRefCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  }

   miniTPCDetectorMessenger::~miniTPCDetectorMessenger(){
  delete fDetDirectory;
  delete fCheckoverlapsCmd;
  delete fTPCVesselRefCmd;
  delete fFieldRingRefCmd;
  delete fAnodeRefCmd;
  delete fCathodeRefCmd;
  delete fBulgeRefCmd;
  delete fTeflonRefCmd;
  delete fSTeflonRefCmd;
  delete fSTPCVesselRefCmd;
  delete fSTPCRadiusCmd;
  delete fSTPCVesselSideThicknessCmd;
  delete fSTPCHalfheightCmd;
  delete nFieldRingsCmd;
  delete fTopRingZPositionCmd;
  delete fieldRingSweptRCmd;
  delete fFieldRingLengthCmd;
  delete fFieldRingThickCmd;
  delete fWWDistanceCmd;
  delete fAnodeRadiusCmd;
  delete fAnodeThicknessCmd;
  delete fAnodeZPositionCmd;
  delete fCathodeRadiusCmd;
  delete fCathodeThicknessCmd;
  delete fCathodeZPositionCmd;
  delete fNSiPMPadAlongZCmd;
  delete fNSiPMPadAlongPhiCmd; 
  delete dGapAlongZCmd;
  delete fTopSiPMZPositionCmd;
  delete fSiPMPadThicknessCmd; 
  delete fSiPMPadHeightCmd;
  delete fSiPMStandoffFromTPCCmd;
  delete fSiPMActiveLayerThicknessCmd;
  delete fSiPMActiveLayerDepthCmd;
  delete fActiveSiPMPadHeightCmd;
  delete fSiPMBaseLayerThicknessCmd;
  delete fSiPMPadBaseHeightCmd;
  delete fRingArrangeIDCmd;
  delete fSiPMOptionCmd;
  delete fWavelengthRefCmd;
}

  void miniTPCDetectorMessenger::SetNewValue(G4UIcommand *cmd, G4String val){
    if( cmd == fSiPMOptionCmd) {
      fConstructor->SetSiPMOption(fSiPMOptionCmd->GetNewIntValue(val));
    }
    else if( cmd == fWavelengthRefCmd) {
      fConstructor->SetWavelengthRef(fWavelengthRefCmd->GetNewIntValue(val));
    }
    else if( cmd == fRingArrangeIDCmd ) {
      fConstructor->SetRingArrangeID(fRingArrangeIDCmd->GetNewIntValue(val));
    }   
    else if( cmd == fCheckoverlapsCmd ) {
      fConstructor->SetCheckoverlaps(fCheckoverlapsCmd->GetNewBoolValue(val));
    }   
    else if( cmd == fTPCVesselRefCmd ) {
      fConstructor->SetTPCVesselRef(fTPCVesselRefCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fFieldRingRefCmd ) {
      fConstructor->SetFieldRingRef(fFieldRingRefCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fAnodeRefCmd ) {
      fConstructor->SetAnodeRef(fAnodeRefCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fCathodeRefCmd ) {
      fConstructor->SetCathodeRef(fCathodeRefCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fBulgeRefCmd ) {
      fConstructor->SetBulgeRef(fBulgeRefCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fTeflonRefCmd ) {
      fConstructor->SetTeflonRef(fTeflonRefCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fSTeflonRefCmd ) {
      fConstructor->SetSTeflonRef(fSTeflonRefCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fSTPCVesselRefCmd ) {
      fConstructor->SetSTPCVesselRef(fSTPCVesselRefCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fSTPCRadiusCmd ) {
      fConstructor->SetSTPCRadius(fSTPCRadiusCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fSTPCVesselSideThicknessCmd ) {
      fConstructor->SetSTPCVesselSideThickness(fSTPCVesselSideThicknessCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fSTPCHalfheightCmd ) {
      fConstructor->SetSTPCHalfheight(fSTPCHalfheightCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == nFieldRingsCmd ) {
      fConstructor->SetnFieldRings(nFieldRingsCmd->GetNewIntValue(val));
    }   
    else if( cmd == fTopRingZPositionCmd ) {
      fConstructor->SetTopRingZPosition(fTopRingZPositionCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fieldRingSweptRCmd ) {
      fConstructor->SetfieldRingSweptR(fieldRingSweptRCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fFieldRingLengthCmd ) {
      fConstructor->SetFieldRingLength(fFieldRingLengthCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fFieldRingThickCmd ) {
      fConstructor->SetFieldRingThick(fFieldRingThickCmd->GetNewDoubleValue(val));
    } 
    else if( cmd == fWWDistanceCmd ) {
      fConstructor->SetWWDistance(fWWDistanceCmd->GetNewDoubleValue(val));
    } 
    else if( cmd == fAnodeRadiusCmd ) {
      fConstructor->SetAnodeRadius(fAnodeRadiusCmd->GetNewDoubleValue(val));
    } 
    else if( cmd == fAnodeThicknessCmd ) {
      fConstructor->SetAnodeThickness(fAnodeThicknessCmd->GetNewDoubleValue(val));
    } 
    else if( cmd == fAnodeZPositionCmd ) {
      fConstructor->SetAnodeZPosition(fAnodeZPositionCmd->GetNewDoubleValue(val));
    } 
    else if( cmd == fCathodeRadiusCmd ) {
      fConstructor->SetCathodeRadius(fCathodeRadiusCmd->GetNewDoubleValue(val));
    } 
    else if( cmd == fCathodeThicknessCmd ) {
      fConstructor->SetCathodeThickness(fCathodeThicknessCmd->GetNewDoubleValue(val));
    } 
    else if( cmd == fCathodeZPositionCmd ) {
      fConstructor->SetCathodeZPosition(fCathodeZPositionCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fNSiPMPadAlongZCmd ) {
      fConstructor->SetNSiPMPadAlongZ(fNSiPMPadAlongZCmd->GetNewIntValue(val));
    }
    else if( cmd == fNSiPMPadAlongPhiCmd ) {
      fConstructor->SetNSiPMPadAlongPhi(fNSiPMPadAlongPhiCmd->GetNewIntValue(val));
    }
    else if( cmd == dGapAlongZCmd ) {
      fConstructor->SetdGapAlongZ(dGapAlongZCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fTopSiPMZPositionCmd ) {
      fConstructor->SetTopSiPMZPosition(fTopSiPMZPositionCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fSiPMPadThicknessCmd ) {
      fConstructor->SetSiPMPadThickness(fSiPMPadThicknessCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fSiPMPadHeightCmd ) {
      fConstructor->SetSiPMPadHeight(fSiPMPadHeightCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fSiPMStandoffFromTPCCmd ) {
      fConstructor->SetSiPMStandoffFromTPC(fSiPMStandoffFromTPCCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fSiPMActiveLayerThicknessCmd ) {
      fConstructor->SetSiPMActiveLayerThickness(fSiPMActiveLayerThicknessCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fSiPMActiveLayerDepthCmd ) {
      fConstructor->SetSiPMActiveLayerDepth(fSiPMActiveLayerDepthCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fActiveSiPMPadHeightCmd ) {
      fConstructor->SetActiveSiPMPadHeight(fActiveSiPMPadHeightCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fSiPMBaseLayerThicknessCmd ) {
      fConstructor->SetSiPMBaseLayerThickness(fSiPMBaseLayerThicknessCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fSiPMPadBaseHeightCmd ) {
      fConstructor->SetSiPMPadBaseHeight(fSiPMPadBaseHeightCmd->GetNewDoubleValue(val));
    }

    else {
      //nEXOModuleConstructorMessenger::SetNewValue(cmd,val);
    }
    
  }

  G4String miniTPCDetectorMessenger::CommandName(G4String name) {
    return "/nEXO/TPCInternals/"+name; 
  }

