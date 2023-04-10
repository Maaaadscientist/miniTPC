#include "nEXOPrimaryGeneratorMessenger.hh"

#include "nEXOPrimaryGeneratorAction.hh"

nEXOPrimaryGeneratorMessenger::nEXOPrimaryGeneratorMessenger(
		    nEXOPrimaryGeneratorAction* nEXOGun):
  nEXOAction(nEXOGun),
  fDirectory("/generator/"),
  GenCmd("/generator/setGenerator",this),
  nCaptureXeSimCmd("/generator/setnCaptureXeSimMethod", this),
  XeComponentCmd("/generator/setXeComponent", this),
  CuIsoCmd("/generator/setCuIsotope", this),
  CuComponentCmd("/generator/setCuComponent", this)

{

  fDirectory.SetGuidance("Generator commands");

  GenCmd.SetGuidance("Choose the primary event generator");
  GenCmd.SetGuidance(" Choices: generalParticleSource(default), bb0n, bb2n, nCaptureXe136, nCaptureCu");
  GenCmd.SetParameterName("choice", true);
  GenCmd.SetDefaultValue("generalParticleSource");
  GenCmd.SetCandidates("gps generalParticleSource bb0n bb2n nCaptureXe136 nCaptureCu");
  GenCmd.AvailableForStates(G4State_PreInit, G4State_Idle);

  nCaptureXeSimCmd.SetGuidance("Enter the LXe Component component to confine n-capture decays (default = RandomGammas)");
  nCaptureXeSimCmd.SetGuidance("Choices : InternalConversions, RandomGammas, ImbalancedCascade");
  nCaptureXeSimCmd.SetParameterName("choice", true);
  nCaptureXeSimCmd.SetDefaultValue("RandomGammas");
  nCaptureXeSimCmd.SetCandidates("InternalConversions RandomGammas ImbalancedCascade");
  nCaptureXeSimCmd.AvailableForStates(G4State_PreInit, G4State_Idle);
  
  XeComponentCmd.SetGuidance("Enter the LXe Component component to confine n-capture decays (default = ActiveLXe)");
  XeComponentCmd.SetGuidance("Choices : ActiveLXe, InactiveLXe");
  XeComponentCmd.SetParameterName("choice", true);
  XeComponentCmd.SetDefaultValue("ActiveLXe");
  XeComponentCmd.SetCandidates("ActiveLXe InactiveLXe");
  XeComponentCmd.AvailableForStates(G4State_PreInit, G4State_Idle);
  
  CuIsoCmd.SetGuidance("Enter the Cu isotope (63 or 65) for n-Capture (default = 63)");
  CuIsoCmd.SetParameterName("isotope", false, false);
  CuIsoCmd.SetDefaultValue(63);
  CuIsoCmd.AvailableForStates(G4State_PreInit, G4State_Idle);

  CuComponentCmd.SetGuidance("Enter the copper component to confine n-capture decays (default = TPC)");
  CuComponentCmd.SetGuidance("Choices : TPC, APDPlatter, FieldRing, InnerCryo, OuterCryo");
  CuComponentCmd.SetParameterName("choice", true);
  CuComponentCmd.SetDefaultValue("TPC");
  CuComponentCmd.SetCandidates("TPC InnerCryo OuterCryo APDPlatter FieldRing");
  CuComponentCmd.AvailableForStates(G4State_PreInit, G4State_Idle);
}

void nEXOPrimaryGeneratorMessenger::SetNewValue(
				G4UIcommand* command, G4String newValue)
{
  if( command == &GenCmd)
    { nEXOAction->set_generator(newValue);}

  else if ( command == &nCaptureXeSimCmd )
    { nEXOAction->set_nCaptureXe_Method(newValue);}

  else if ( command == &XeComponentCmd)
    { nEXOAction->set_Xe_Component(newValue);}

  else if ( command == &CuIsoCmd )
    { nEXOAction->set_Cu_isotope(CuIsoCmd.GetNewIntValue(newValue));}

  else if ( command == &CuComponentCmd)
    { nEXOAction->set_Cu_Component(newValue);}

}


