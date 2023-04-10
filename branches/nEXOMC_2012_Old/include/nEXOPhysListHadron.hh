
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#ifndef nEXOPhysListHadron_h
#define nEXOPhysListHadron_h 1

#include "G4VPhysicsConstructor.hh"
#include "globals.hh"

#include "G4HadronElasticProcess.hh"

#include "G4ProtonInelasticProcess.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4DeuteronInelasticProcess.hh"
#include "G4TritonInelasticProcess.hh"
#include "G4AlphaInelasticProcess.hh"
#include "G4IonInelasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"


class nEXOPhysListHadron : public G4VPhysicsConstructor 
{
  public:
    nEXOPhysListHadron(const G4String& name = "hadron");
    virtual ~nEXOPhysListHadron();

  public:
  // Construct particle and physics
    void ConstructParticle() {};
  //
    void ConstructProcess(); 

  private:

  G4HadronElasticProcess  theElasticProcess;
  G4ProtonInelasticProcess theProtonInelastic;
  G4NeutronInelasticProcess  theNeutronInelastic;
  G4HadronElasticProcess* theNeutronElasticProcess;
  G4HadronFissionProcess* theFissionProcess;
  G4HadronCaptureProcess* theCaptureProcess;
  G4DeuteronInelasticProcess* theDeuteronInelasticProcess;
  G4TritonInelasticProcess* theTritonInelasticProcess;
  G4AlphaInelasticProcess* theAlphaInelasticProcess;
  G4IonInelasticProcess* theIonInelasticProcess;
};

#endif



