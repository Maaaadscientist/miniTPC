#include "nEXODetectorMessenger.hh"
#include "nEXODetectorConstruction.hh"

nEXODetectorMessenger::nEXODetectorMessenger(nEXODetectorConstruction* construct)
  : G4UImessenger(), fConstructor(construct){

    fDetDirectory = new G4UIdirectory("/nEXO/TPCInternals/");
    fDetDirectory->SetGuidance("Detector construction control");

    fWWDistanceCmd = new G4UIcmdWithADoubleAndUnit(CommandName("wwDistance"),this);
    fWWDistanceCmd->SetGuidance("Define distance between wires");
    fWWDistanceCmd->SetParameterName("wwDistance",false);
    fWWDistanceCmd->SetUnitCategory("Length");
    fWWDistanceCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fWWDistanceOfAnodeCmd = new G4UIcmdWithADoubleAndUnit(CommandName("wwDistanceOfAnode"),this);
    fWWDistanceOfAnodeCmd->SetGuidance("Define distance between wires of Anode");
    fWWDistanceOfAnodeCmd->SetParameterName("wwDistanceOfAnode",false);
    fWWDistanceOfAnodeCmd->SetUnitCategory("Length");
    fWWDistanceOfAnodeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fFieldRingLengthCmd = new G4UIcmdWithADoubleAndUnit(CommandName("fieldRingLength"),this);
    fFieldRingLengthCmd->SetGuidance("Define field ring length");
    fFieldRingLengthCmd->SetParameterName("fieldRingLength",false);
    fFieldRingLengthCmd->SetUnitCategory("Length");
    fFieldRingLengthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fFieldRingThickCmd = new G4UIcmdWithADoubleAndUnit(CommandName("fieldRingThick"),this);
    fFieldRingThickCmd->SetGuidance("Define field ring thick");
    fFieldRingThickCmd->SetParameterName("fieldRingThick",false);
    fFieldRingThickCmd->SetUnitCategory("Length");
    fFieldRingThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fRingSideDistanceCmd = new G4UIcmdWithADoubleAndUnit(CommandName("ringSideDistance"),this);
    fRingSideDistanceCmd->SetGuidance("Define ring side distance");
    fRingSideDistanceCmd->SetParameterName("ringSideDistance",false);
    fRingSideDistanceCmd->SetUnitCategory("Length");
    fRingSideDistanceCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fRadialRingDistanceCmd = new G4UIcmdWithADoubleAndUnit(CommandName("radialRingDistance"),this);
    fRadialRingDistanceCmd->SetGuidance("Define radial ring distance");
    fRadialRingDistanceCmd->SetParameterName("radialRingDistance",false);
    fRadialRingDistanceCmd->SetUnitCategory("Length");
    fRadialRingDistanceCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
        
    fFieldRingRefCmd = new G4UIcmdWithADouble(CommandName("fieldRingRef"),this);
    fFieldRingRefCmd->SetGuidance("The reflectivity of field rings");
    fFieldRingRefCmd->SetParameterName("fieldRingRef",false);
    fFieldRingRefCmd->SetDefaultValue(1.0);
    fFieldRingRefCmd->AvailableForStates(G4State_PreInit);
    
    fAnodeRefCmd = new G4UIcmdWithADouble(CommandName("anodeRef"),this);
    fAnodeRefCmd->SetGuidance("The reflectivity of anode");
    fAnodeRefCmd->SetParameterName("anodeRef",false);
    fAnodeRefCmd->SetDefaultValue(0.8);
    fAnodeRefCmd->AvailableForStates(G4State_PreInit);
    
    fCathodeRefCmd = new G4UIcmdWithADouble(CommandName("cathodeRef"),this);
    fCathodeRefCmd->SetGuidance("The reflectivity of cathode");
    fCathodeRefCmd->SetParameterName("cathodeRef",false);
    fCathodeRefCmd->SetDefaultValue(0.8);
    fCathodeRefCmd->AvailableForStates(G4State_PreInit);

    fTeflonRefCmd = new G4UIcmdWithADouble(CommandName("teflonRef"),this);
    fTeflonRefCmd->SetGuidance("The reflectivity of teflon");
    fTeflonRefCmd->SetParameterName("teflonRef",false);
    fTeflonRefCmd->SetDefaultValue(0.95);
    fTeflonRefCmd->AvailableForStates(G4State_PreInit);
    
    fBulgeRefCmd = new G4UIcmdWithADouble(CommandName("bulgeRef"),this);
    fBulgeRefCmd->SetGuidance("The reflectivity of bulge");
    fBulgeRefCmd->SetParameterName("bulgeRef",false);
    fBulgeRefCmd->SetDefaultValue(0.8);
    fBulgeRefCmd->AvailableForStates(G4State_PreInit);

    fBulgeRadiusCmd = new G4UIcmdWithADoubleAndUnit(CommandName("bulgeRadius"),this);
    fBulgeRadiusCmd->SetGuidance("The radius of bulge");
    fBulgeRadiusCmd->SetParameterName("bulgeRadius",false);
    fBulgeRadiusCmd->SetUnitCategory("Length");
    fBulgeRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
    fTPCVesselRefCmd = new G4UIcmdWithADouble(CommandName("tpcVesselRef"),this);
    fTPCVesselRefCmd->SetGuidance("The reflectivity of TPC vessel");
    fTPCVesselRefCmd->SetParameterName("tpcVesselRef",false);
    fTPCVesselRefCmd->SetDefaultValue(0.1);
    fTPCVesselRefCmd->AvailableForStates(G4State_PreInit);
    
    fActiveSiPMPadFracCmd = new G4UIcmdWithADouble(CommandName("activeSiPMPadFrac"),this);
    fActiveSiPMPadFracCmd->SetGuidance("The fraction of active SiPM pad area");
    fActiveSiPMPadFracCmd->SetParameterName("activeSiPMPadFrac",false);
    fActiveSiPMPadFracCmd->SetDefaultValue(0.8);
    fActiveSiPMPadFracCmd->AvailableForStates(G4State_PreInit);
    
    fSiPMOptionCmd = new G4UIcmdWithAnInteger(CommandName("SiPMOption"),this);
    fSiPMOptionCmd->SetGuidance("0: barrel, 1: endcap");
    fSiPMOptionCmd->SetParameterName("SiPMOption",false);
    fSiPMOptionCmd->SetDefaultValue(0);
    fSiPMOptionCmd->AvailableForStates(G4State_PreInit);

    fAnodeOptionCmd = new G4UIcmdWithAnInteger(CommandName("AnodeOption"),this);
    fAnodeOptionCmd->SetGuidance("0: Simple disk, 1: Charge tiles on quartz backing");
    fAnodeOptionCmd->SetParameterName("AnodeOption",false);
    fAnodeOptionCmd->SetDefaultValue(1);
    fAnodeOptionCmd->AvailableForStates(G4State_PreInit);

    fRingArrangeIDCmd = new G4UIcmdWithAnInteger(CommandName("ringArrangeID"),this);
    fRingArrangeIDCmd->SetGuidance("The id of ring arrangement");
    fRingArrangeIDCmd->SetParameterName("ringArrangeID",false);
    fRingArrangeIDCmd->SetDefaultValue(0);
    fRingArrangeIDCmd->AvailableForStates(G4State_PreInit);

    fUseWLSCmd = new G4UIcmdWithAnInteger(CommandName("useWLS"),this);
    fUseWLSCmd->SetGuidance("if use WLS");
    fUseWLSCmd->SetParameterName("useWLS",false);
    fUseWLSCmd->SetDefaultValue(0);
    fUseWLSCmd->AvailableForStates(G4State_PreInit);

    fInternalsFlagCmd = new G4UIcmdWithAnInteger(CommandName("internalsFlag"),this);
    fInternalsFlagCmd->SetGuidance("Which TPC Internals are included");
    fInternalsFlagCmd->SetParameterName("internalsFlag",false);
    fInternalsFlagCmd->SetDefaultValue(2);
    fInternalsFlagCmd->AvailableForStates(G4State_PreInit);

    fCathodeAnodeDistanceCmd = new G4UIcmdWithADoubleAndUnit(CommandName("cathodeAnodeDistance"),this);
    fCathodeAnodeDistanceCmd->SetGuidance("Distance between cathode and anode");
    fCathodeAnodeDistanceCmd->SetParameterName("cathodeAnodeDistance",false);
    fCathodeAnodeDistanceCmd->SetUnitCategory("Length"); //default = 1258.75*mm
    fCathodeAnodeDistanceCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fCathodeToBottomRingDistanceCmd = new G4UIcmdWithADoubleAndUnit(CommandName("cathodeToBottomRingDistance"),this);
    fCathodeToBottomRingDistanceCmd->SetGuidance("Distance between cathode and bottom field ring");
    fCathodeToBottomRingDistanceCmd->SetParameterName("cathodeToBottomRingDistance",false);
    fCathodeToBottomRingDistanceCmd->SetUnitCategory("Length"); //default = 17.*mm
    fCathodeToBottomRingDistanceCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fAnodeToTopRingDistanceCmd = new G4UIcmdWithADoubleAndUnit(CommandName("anodeToTopRingDistance"),this);
    fAnodeToTopRingDistanceCmd->SetGuidance("Distance between anode and top field ring");
    fAnodeToTopRingDistanceCmd->SetParameterName("anodeToTopRingDistance",false);
    fAnodeToTopRingDistanceCmd->SetUnitCategory("Length"); //default = 18.*mm
    fAnodeToTopRingDistanceCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fAnodeRadiusCmd = new G4UIcmdWithADoubleAndUnit(CommandName("anodeRadius"),this);
    fAnodeRadiusCmd->SetGuidance("Anode radius (only for simple disk anode)");
    fAnodeRadiusCmd->SetParameterName("anodeRadius",false);
    fAnodeRadiusCmd->SetUnitCategory("Length"); //default = 587.7*mm
    fAnodeRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fAnodeThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("anodeThickness"),this);
    fAnodeThicknessCmd->SetGuidance("Anode thickness (only for simple disk anode)");
    fAnodeThicknessCmd->SetParameterName("anodeThickness",false);
    fAnodeThicknessCmd->SetUnitCategory("Length"); //default = 3.*mm
    fAnodeThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fAnodeZPositionCmd = new G4UIcmdWithADoubleAndUnit(CommandName("anodeZPosition"),this);
    fAnodeZPositionCmd->SetGuidance("Anode z-position");
    fAnodeZPositionCmd->SetParameterName("anodeZPosition",false);
    fAnodeZPositionCmd->SetUnitCategory("Length"); //default = 635.5*mm
    fAnodeZPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fCathodeRadiusCmd = new G4UIcmdWithADoubleAndUnit(CommandName("cathodeRadius"),this);
    fCathodeRadiusCmd->SetGuidance("Cathode radius");
    fCathodeRadiusCmd->SetParameterName("cathodeRadius",false);
    fCathodeRadiusCmd->SetUnitCategory("Length"); //default = 597.7*mm
    fCathodeRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fCathodeThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("cathodeThickness"),this);
    fCathodeThicknessCmd->SetGuidance("Cathode thickness");
    fCathodeThicknessCmd->SetParameterName("cathodeThickness",false);
    fCathodeThicknessCmd->SetUnitCategory("Length"); //default = 0.25*mm
    fCathodeThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fCathodeZPositionCmd = new G4UIcmdWithADoubleAndUnit(CommandName("cathodeZPosition"),this);
    fCathodeZPositionCmd->SetGuidance("Cathode z-position");
    fCathodeZPositionCmd->SetParameterName("cathodeZPosition",false);
    fCathodeZPositionCmd->SetUnitCategory("Length"); //default = -620.*mm
    fCathodeZPositionCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiPMTotalHeightCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMTotalHeight"),this);
    fSiPMTotalHeightCmd->SetGuidance("Total height of all SiPMs");
    fSiPMTotalHeightCmd->SetParameterName("SiPMTotalHeight",false);
    fSiPMTotalHeightCmd->SetUnitCategory("Length"); //default = 1246.*mm
    fSiPMTotalHeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiPMPadHeightCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMPadHeight"),this);
    fSiPMPadHeightCmd->SetGuidance("SiPM pad side length");
    fSiPMPadHeightCmd->SetParameterName("SiPMPadHeight",false);
    fSiPMPadHeightCmd->SetUnitCategory("Length"); //default = 13.4164*mm
    fSiPMPadHeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiPMPadThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMPadThickness"),this);
    fSiPMPadThicknessCmd->SetGuidance("SiPM thickness");
    fSiPMPadThicknessCmd->SetParameterName("SiPMPadThickness",false);
    fSiPMPadThicknessCmd->SetUnitCategory("Length"); //default = 3.5*mm
    fSiPMPadThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiPMStandoffFromTPCCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMStandoffFromTPC"),this);
    fSiPMStandoffFromTPCCmd->SetGuidance("Distance of SiPM outer surface to TPC vessel");
    fSiPMStandoffFromTPCCmd->SetParameterName("SiPMStandoffFromTPC",false);
    fSiPMStandoffFromTPCCmd->SetUnitCategory("Length"); //default = 7.35*mm
    fSiPMStandoffFromTPCCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fChargeModuleLengthCmd = new G4UIcmdWithADoubleAndUnit(CommandName("chargeModuleLength"),this);
    fChargeModuleLengthCmd->SetGuidance("Charge module side length");
    fChargeModuleLengthCmd->SetParameterName("chargeModuleLength",false);
    fChargeModuleLengthCmd->SetUnitCategory("Length"); //default = 100.5*mm
    fChargeModuleLengthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fChargeModuleThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("chargeModuleThickness"),this);
    fChargeModuleThicknessCmd->SetGuidance("Charge module thickness");
    fChargeModuleThicknessCmd->SetParameterName("chargeModuleThickness",false);
    fChargeModuleThicknessCmd->SetUnitCategory("Length"); //default = 0.6*mm
    fChargeModuleThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fChargeModuleBackingThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("chargeModuleBackingThickness"),this);
    fChargeModuleBackingThicknessCmd->SetGuidance("Charge module (quartz) backing thickness");
    fChargeModuleBackingThicknessCmd->SetParameterName("chargeModuleBackingThickness",false);
    fChargeModuleBackingThicknessCmd->SetUnitCategory("Length"); //default = 0.5*mm
    fChargeModuleBackingThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fChargePadDiagonalLengthCmd = new G4UIcmdWithADoubleAndUnit(CommandName("chargePadDiagonalLength"),this);
    fChargePadDiagonalLengthCmd->SetGuidance("Charge pad diagonal length");
    fChargePadDiagonalLengthCmd->SetParameterName("chargePadDiagonalLength",false);
    fChargePadDiagonalLengthCmd->SetUnitCategory("Length"); //default = 3.*mm
    fChargePadDiagonalLengthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fChargePadThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("chargePadThickness"),this);
    fChargePadThicknessCmd->SetGuidance("Charge pad thickness");
    fChargePadThicknessCmd->SetParameterName("chargePadThickness",false);
    fChargePadThicknessCmd->SetUnitCategory("Length"); //default = 0.001*mm
    fChargePadThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fChargePadLinkLengthCmd = new G4UIcmdWithADoubleAndUnit(CommandName("chargePadLinkLength"),this);
    fChargePadLinkLengthCmd->SetGuidance("Charge pad link length");
    fChargePadLinkLengthCmd->SetParameterName("chargePadLinkLength",false);
    fChargePadLinkLengthCmd->SetUnitCategory("Length"); //default = 0.064*mm
    fChargePadLinkLengthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fChargePadLinkHeightCmd = new G4UIcmdWithADoubleAndUnit(CommandName("chargePadLinkHeight"),this);
    fChargePadLinkHeightCmd->SetGuidance("Charge pad link height");
    fChargePadLinkHeightCmd->SetParameterName("chargePadLinkHeight",false);
    fChargePadLinkHeightCmd->SetUnitCategory("Length"); //default = 0.025*mm
    fChargePadLinkHeightCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiPMActiveLayerThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMActiveLayerThickness"),this);
    fSiPMActiveLayerThicknessCmd->SetGuidance("Thickness of SiPM active layer");
    fSiPMActiveLayerThicknessCmd->SetParameterName("SiPMActiveLayerThickness",false);
    fSiPMActiveLayerThicknessCmd->SetUnitCategory("Length"); //default = 0.001*mm
    fSiPMActiveLayerThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiPMActiveLayerDepthCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMActiveLayerDepth"),this);
    fSiPMActiveLayerDepthCmd->SetGuidance("Depth of SiPM active layer from SiPM inner surface");
    fSiPMActiveLayerDepthCmd->SetParameterName("SiPMActiveLayerDepth",false);
    fSiPMActiveLayerDepthCmd->SetUnitCategory("Length"); //default = 1.*mm
    fSiPMActiveLayerDepthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiPMBaseLayerThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMBaseLayerThickness"),this);
    fSiPMBaseLayerThicknessCmd->SetGuidance("Thickness of SiPM pad base layer");
    fSiPMBaseLayerThicknessCmd->SetParameterName("SiPMBaseLayerThickness",false);
    fSiPMBaseLayerThicknessCmd->SetUnitCategory("Length"); //default = 0.5*mm
    fSiPMBaseLayerThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    fSiPMWLSThicknessCmd = new G4UIcmdWithADoubleAndUnit(CommandName("SiPMWLSThickness"),this);
    fSiPMWLSThicknessCmd->SetGuidance("Thickness of WLS layer");
    fSiPMWLSThicknessCmd->SetParameterName("SiPMWLSThickness",false);
    fSiPMWLSThicknessCmd->SetUnitCategory("Length"); //default = 0.1*mm
    fSiPMWLSThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  }

   nEXODetectorMessenger::~nEXODetectorMessenger(){
    delete fDetDirectory;
    delete fWWDistanceOfAnodeCmd;
    delete fWWDistanceCmd;
    delete fFieldRingLengthCmd;
    delete fFieldRingThickCmd;
    delete fRingSideDistanceCmd;
    delete fRadialRingDistanceCmd;
    delete fFieldRingRefCmd;
    delete fAnodeRefCmd;
    delete fCathodeRefCmd;
    delete fTeflonRefCmd;
    delete fBulgeRefCmd;
    delete fBulgeRadiusCmd;
    delete fTPCVesselRefCmd;
    delete fActiveSiPMPadFracCmd;
    delete fSiPMOptionCmd;
    delete fAnodeOptionCmd;
    delete fRingArrangeIDCmd;
    delete fInternalsFlagCmd;
    delete fUseWLSCmd;
    delete fCathodeAnodeDistanceCmd;
    delete fCathodeToBottomRingDistanceCmd;
    delete fAnodeToTopRingDistanceCmd;
    delete fAnodeRadiusCmd;
    delete fAnodeThicknessCmd;
    delete fAnodeZPositionCmd;
    delete fCathodeRadiusCmd;
    delete fCathodeThicknessCmd;
    delete fCathodeZPositionCmd;
    delete fSiPMTotalHeightCmd;
    delete fSiPMPadHeightCmd;
    delete fSiPMPadThicknessCmd;
    delete fSiPMStandoffFromTPCCmd;
    delete fChargeModuleLengthCmd;
    delete fChargeModuleThicknessCmd;
    delete fChargeModuleBackingThicknessCmd;
    delete fChargePadDiagonalLengthCmd;
    delete fChargePadThicknessCmd;
    delete fChargePadLinkLengthCmd;
    delete fChargePadLinkHeightCmd;
    delete fSiPMActiveLayerThicknessCmd;
    delete fSiPMActiveLayerDepthCmd;
    delete fSiPMBaseLayerThicknessCmd;
    delete fSiPMWLSThicknessCmd;

  }

  void nEXODetectorMessenger::SetNewValue(G4UIcommand *cmd, G4String val){
    if( cmd == fWWDistanceOfAnodeCmd) {
      fConstructor->SetWWDistanceOfAnode(fWWDistanceOfAnodeCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fWWDistanceCmd ) {
      fConstructor->SetWWDistance(fWWDistanceCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fFieldRingRefCmd ) {
      fConstructor->SetFieldRingRef(fFieldRingRefCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fFieldRingLengthCmd ) {
      fConstructor->SetFieldRingLength(fFieldRingLengthCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fFieldRingThickCmd ) {
      fConstructor->SetFieldRingThick(fFieldRingThickCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fRingSideDistanceCmd ) {
      fConstructor->SetRingSideDistance(fRingSideDistanceCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fRadialRingDistanceCmd ) {
      fConstructor->SetRadialRingDistance(fRadialRingDistanceCmd->GetNewDoubleValue(val));
    }   
    else if( cmd == fAnodeRefCmd ) {
      fConstructor->SetAnodeRef(fAnodeRefCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fCathodeRefCmd ) {
      fConstructor->SetCathodeRef(fCathodeRefCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fTeflonRefCmd ) {
      fConstructor->SetTeflonRef(fTeflonRefCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fTPCVesselRefCmd ) {
      fConstructor->SetTPCVesselRef(fTPCVesselRefCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fBulgeRadiusCmd ) {
      fConstructor->SetBulgeRadius(fBulgeRadiusCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fBulgeRefCmd ) {
      fConstructor->SetBulgeRef(fBulgeRefCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fActiveSiPMPadFracCmd ) {
      fConstructor->SetActiveSiPMPadFrac(fActiveSiPMPadFracCmd->GetNewDoubleValue(val));
    }
    else if( cmd == fSiPMOptionCmd ) {
      fConstructor->SetSiPMOption(fSiPMOptionCmd->GetNewIntValue(val));
    }
    else if( cmd == fAnodeOptionCmd ) {
      fConstructor->SetAnodeOption(fAnodeOptionCmd->GetNewIntValue(val));
    }
    else if( cmd == fRingArrangeIDCmd ) {
      fConstructor->SetRingArrangeID(fRingArrangeIDCmd->GetNewIntValue(val));
    }
    else if( cmd == fUseWLSCmd ) {
      fConstructor->SetUseWLS(fUseWLSCmd->GetNewIntValue(val));
    }
    else if( cmd == fInternalsFlagCmd ) {
      fConstructor->SetInternalsFlag(fInternalsFlagCmd->GetNewIntValue(val));
    }
    else if(cmd == fCathodeAnodeDistanceCmd){
      fConstructor->SetCathodeAnodeDistance(fCathodeAnodeDistanceCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fCathodeToBottomRingDistanceCmd){
      fConstructor->SetCathodeToBottomRingDistance(fCathodeToBottomRingDistanceCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fAnodeToTopRingDistanceCmd){
      fConstructor->SetAnodeToTopRingDistance(fAnodeToTopRingDistanceCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fAnodeRadiusCmd){
      fConstructor->SetAnodeRadius(fAnodeRadiusCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fAnodeThicknessCmd){
      fConstructor->SetAnodeThickness(fAnodeThicknessCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fAnodeZPositionCmd){
      fConstructor->SetAnodeZPosition(fAnodeZPositionCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fCathodeRadiusCmd){
      fConstructor->SetCathodeRadius(fCathodeRadiusCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fCathodeThicknessCmd){
      fConstructor->SetCathodeThickness(fCathodeThicknessCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fCathodeZPositionCmd){
      fConstructor->SetCathodeZPosition(fCathodeZPositionCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fSiPMTotalHeightCmd){
      fConstructor->SetSiPMTotalHeight(fSiPMTotalHeightCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fSiPMPadHeightCmd){
      fConstructor->SetSiPMPadHeight(fSiPMPadHeightCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fSiPMPadThicknessCmd){
      fConstructor->SetSiPMPadThickness(fSiPMPadThicknessCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fSiPMStandoffFromTPCCmd){
      fConstructor->SetSiPMStandoffFromTPC(fSiPMStandoffFromTPCCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fChargeModuleLengthCmd){
      fConstructor->SetChargeModuleLength(fChargeModuleLengthCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fChargeModuleThicknessCmd){
      fConstructor->SetChargeModuleThickness(fChargeModuleThicknessCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fChargeModuleBackingThicknessCmd){
      fConstructor->SetChargeModuleBackingThickness(fChargeModuleBackingThicknessCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fChargePadDiagonalLengthCmd){
      fConstructor->SetChargePadDiagonalLength(fChargePadDiagonalLengthCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fChargePadThicknessCmd){
      fConstructor->SetChargePadThickness(fChargePadThicknessCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fChargePadLinkLengthCmd){
      fConstructor->SetChargePadLinkLength(fChargePadLinkLengthCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fChargePadLinkHeightCmd){
      fConstructor->SetChargePadLinkHeight(fChargePadLinkHeightCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fSiPMActiveLayerThicknessCmd){
      fConstructor->SetSiPMActiveLayerThickness(fSiPMActiveLayerThicknessCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fSiPMActiveLayerDepthCmd){
      fConstructor->SetSiPMActiveLayerDepth(fSiPMActiveLayerDepthCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fSiPMBaseLayerThicknessCmd){
      fConstructor->SetSiPMBaseLayerThickness(fSiPMBaseLayerThicknessCmd->GetNewDoubleValue(val));
    }
    else if(cmd == fSiPMWLSThicknessCmd){
      fConstructor->SetSiPMWLSThickness(fSiPMWLSThicknessCmd->GetNewDoubleValue(val));
    }
    else {
      //nEXOModuleConstructorMessenger::SetNewValue(cmd,val);
    }
    
  }

  G4String nEXODetectorMessenger::CommandName(G4String name) {
    return "/nEXO/TPCInternals/"+name; 
  }
