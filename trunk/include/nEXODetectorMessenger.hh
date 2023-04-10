#ifndef nEXODetectorMessenger_h
#define nEXODetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"

class nEXODetectorConstruction;

class nEXODetectorMessenger : public G4UImessenger
{
public:

  nEXODetectorMessenger(nEXODetectorConstruction* construct);
  ~nEXODetectorMessenger();
  void SetNewValue(G4UIcommand *cmd, G4String val);

  G4String CommandName(G4String name); 

private:
  nEXODetectorConstruction* fConstructor;

  G4UIdirectory*           fDetDirectory;

  G4UIcmdWithADoubleAndUnit* fWWDistanceCmd;
  G4UIcmdWithADoubleAndUnit* fWWDistanceOfAnodeCmd;
  G4UIcmdWithADoubleAndUnit* fFieldRingLengthCmd;
  G4UIcmdWithADoubleAndUnit* fFieldRingThickCmd;
  G4UIcmdWithADoubleAndUnit* fRingSideDistanceCmd;
  G4UIcmdWithADoubleAndUnit* fRadialRingDistanceCmd;
  G4UIcmdWithADouble* fFieldRingRefCmd;
  G4UIcmdWithADouble* fAnodeRefCmd;
  G4UIcmdWithADouble* fCathodeRefCmd;
  G4UIcmdWithADouble* fTeflonRefCmd;
  G4UIcmdWithADouble* fBulgeRefCmd;
  G4UIcmdWithADoubleAndUnit* fBulgeRadiusCmd;
  G4UIcmdWithADouble* fTPCVesselRefCmd;
  G4UIcmdWithADouble* fActiveSiPMPadFracCmd;
  G4UIcmdWithAnInteger* fSiPMOptionCmd;
  G4UIcmdWithAnInteger* fAnodeOptionCmd;
  G4UIcmdWithAnInteger* fRingArrangeIDCmd;
  G4UIcmdWithAnInteger* fInternalsFlagCmd;
  G4UIcmdWithAnInteger* fUseWLSCmd;

   G4UIcmdWithADoubleAndUnit* fCathodeAnodeDistanceCmd;
  G4UIcmdWithADoubleAndUnit* fCathodeToBottomRingDistanceCmd;
  G4UIcmdWithADoubleAndUnit* fAnodeToTopRingDistanceCmd;
  G4UIcmdWithADoubleAndUnit* fAnodeRadiusCmd;
  G4UIcmdWithADoubleAndUnit* fAnodeThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fAnodeZPositionCmd;
  G4UIcmdWithADoubleAndUnit* fCathodeRadiusCmd;
  G4UIcmdWithADoubleAndUnit* fCathodeThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fCathodeZPositionCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMTotalHeightCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMPadHeightCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMPadThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMStandoffFromTPCCmd;
  G4UIcmdWithADoubleAndUnit* fChargeModuleLengthCmd;
  G4UIcmdWithADoubleAndUnit* fChargeModuleThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fChargeModuleBackingThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fChargePadDiagonalLengthCmd;
  G4UIcmdWithADoubleAndUnit* fChargePadThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fChargePadLinkLengthCmd;
  G4UIcmdWithADoubleAndUnit* fChargePadLinkHeightCmd;

  G4UIcmdWithADoubleAndUnit* fSiPMActiveLayerThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMActiveLayerDepthCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMBaseLayerThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMWLSThicknessCmd;
};

#endif
