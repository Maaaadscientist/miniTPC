
#ifndef nEXOPrimaryGeneratorAction_h
#define nEXOPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "nEXOPrimaryGeneratorMessenger.hh"
#include <string>

class G4GeneralParticleSource;
class G4ParticleGun;
class G4Event;
class nEXOPrimaryGeneratorMessenger;
class G4ParticleDefinition;

class nEXOPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  nEXOPrimaryGeneratorAction();
  ~nEXOPrimaryGeneratorAction();

public:
  void GeneratePrimaries(G4Event* anEvent);
  void set_generator( G4String value);
  void generate_bb0n( G4Event *anEvent);
  void generate_bb2n( G4Event *anEvent);
  void generate_nCaptureXe136(G4Event *anEvent, G4String nCaptureXeMethod, G4String XeComponent);
  void generate_nCaptureCu(G4Event *anEvent, G4int isotope, G4String);
  G4double D_bb0n_spectral_max(G4double K);
  G4double D_bb0n_spectrum(G4double K, G4double D);
  G4double fermi_function( G4int Z, G4double KE );
  G4double bb2n_sum_spectrum( G4double K, G4double &D_spectral_max );
  G4double D_spectrum ( G4double K, G4double D);
  G4double SimpsonsRule(G4double x0, G4double xn, G4int N, G4double f[]);
  void set_norm( G4double q_value );
  void set_nCaptureXe_Method ( G4String value );
  void set_Xe_Component ( G4String value );
  void set_Cu_isotope ( G4int value );
  void set_Cu_Component ( G4String value );

private:
  G4GeneralParticleSource* particleGun;
  G4ParticleGun*           particleGun2;
  nEXOPrimaryGeneratorMessenger gunMessenger; //messenger of this class

  G4String generator;
  G4ParticleDefinition*   aBeta;
  G4ParticleDefinition*   aGamma;  
  G4double q_value;
  G4double ELECTRON_MASS;
  G4int ff_factor;
  G4double K_spectral_max;
  G4double normalization;
  G4String nCaptureXe_Method;
  G4String XeComponent;
  G4int CuIsotope;
  G4String CuComponent;
  G4bool norm_calculated;
};

#endif



