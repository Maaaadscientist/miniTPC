#ifndef miniTPCDetectorMessenger_h
#define miniTPCDetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"

class miniTPCDetectorConstruction;

class miniTPCDetectorMessenger : public G4UImessenger
{
public:

  miniTPCDetectorMessenger(miniTPCDetectorConstruction* construct);
  ~miniTPCDetectorMessenger();
  void SetNewValue(G4UIcommand *cmd, G4String val);

  G4String CommandName(G4String name); 

private:
  miniTPCDetectorConstruction* fConstructor;

  G4UIdirectory*           fDetDirectory;

  G4UIcmdWithABool* fCheckoverlapsCmd;
  G4UIcmdWithADouble* fTPCVesselRefCmd;
  G4UIcmdWithADouble* fFieldRingRefCmd;
  G4UIcmdWithADouble* fAnodeRefCmd;
  G4UIcmdWithADouble* fCathodeRefCmd;
  G4UIcmdWithADouble* fBulgeRefCmd;
  G4UIcmdWithADouble* fTeflonRefCmd;
  G4UIcmdWithADouble* fSTeflonRefCmd;
  G4UIcmdWithADouble* fSTPCVesselRefCmd;

  G4UIcmdWithADoubleAndUnit* fSTPCRadiusCmd;
  G4UIcmdWithADoubleAndUnit* fSTPCVesselSideThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fSTPCHalfheightCmd;

  // Parameters for field rings
  G4UIcmdWithAnInteger* nFieldRingsCmd;
  G4UIcmdWithADoubleAndUnit* fTopRingZPositionCmd;
  G4UIcmdWithADoubleAndUnit* fieldRingSweptRCmd;
  G4UIcmdWithADoubleAndUnit* fFieldRingLengthCmd;
  G4UIcmdWithADoubleAndUnit* fFieldRingThickCmd;
  G4UIcmdWithADoubleAndUnit* fWWDistanceCmd;

  // Parameters for Anode/Cathode
  G4UIcmdWithADoubleAndUnit* fAnodeRadiusCmd;
  G4UIcmdWithADoubleAndUnit* fAnodeThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fAnodeZPositionCmd;
  G4UIcmdWithADoubleAndUnit* fCathodeRadiusCmd;
  G4UIcmdWithADoubleAndUnit* fCathodeThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fCathodeZPositionCmd;

  // Parameters for Simple SiPM
  G4UIcmdWithAnInteger* fNSiPMPadAlongZCmd;
  G4UIcmdWithAnInteger* fNSiPMPadAlongPhiCmd; 
  G4UIcmdWithADoubleAndUnit* dGapAlongZCmd;
  G4UIcmdWithADoubleAndUnit* fTopSiPMZPositionCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMPadThicknessCmd; 
  G4UIcmdWithADoubleAndUnit* fSiPMPadHeightCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMStandoffFromTPCCmd;
  
  G4UIcmdWithADoubleAndUnit* fSiPMActiveLayerThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMActiveLayerDepthCmd;
  G4UIcmdWithADoubleAndUnit* fActiveSiPMPadHeightCmd;
  
  G4UIcmdWithADoubleAndUnit* fSiPMBaseLayerThicknessCmd;
  G4UIcmdWithADoubleAndUnit* fSiPMPadBaseHeightCmd;
  
  G4UIcmdWithAnInteger* fRingArrangeIDCmd;
  G4UIcmdWithAnInteger* fSiPMOptionCmd;
  
  G4UIcmdWithAnInteger* fWavelengthRefCmd;
};

#endif

