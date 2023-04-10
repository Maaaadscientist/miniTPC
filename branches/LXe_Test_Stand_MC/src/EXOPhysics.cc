#include "globals.hh"
#include "G4ios.hh"

#include "EXOPhysics.hh"
#include "nEXOG4EmLivermorePhysics.hh"

#include "G4LossTableManager.hh"
#include "G4ProcessManager.hh"

#include "G4PhysicsListHelper.hh"
#include "G4BuilderType.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EXOPhysics::EXOPhysics() : G4VPhysicsConstructor("EXOPhysics")
{
  SetVerboseLevel(0);

  enablePenelope   = true;
  enableMuNuclear  = true;
  enableHPNeutron  = true;
  //enableOptics     = false; //true;
  enableOptics     = true;
  
  G4LossTableManager::Instance();
  SetPhysicsType(bElectromagnetic);

  fEMPhysicsList = new nEXOG4EmLivermorePhysics();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EXOPhysics::~EXOPhysics()
{}

#include "G4ParticleTypes.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"
#include "nEXOG4ThermalElectron.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysics::ConstructParticle()
{
  nEXOG4ThermalElectron::ThermalElectronDefinition(); //NEST

  G4BosonConstructor::ConstructParticle();
  G4LeptonConstructor::ConstructParticle();
  G4MesonConstructor::ConstructParticle();
  G4BaryonConstructor::ConstructParticle();
  G4IonConstructor::ConstructParticle();
  G4ShortLivedConstructor::ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysics::ConstructProcess()
{
  ConstructEM();
  ConstructOp();
  ConstructHad();
  ConstructGeneral();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"
#include "G4RayleighScattering.hh"

// Penelope Model
#include "G4PenelopeRayleighModel.hh"
#include "G4PenelopeComptonModel.hh"
#include "G4PenelopePhotoElectricModel.hh"
#include "G4PenelopeGammaConversionModel.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4PenelopeBremsstrahlungModel.hh"
#include "G4PenelopeAnnihilationModel.hh"

#include "G4UniversalFluctuation.hh"

#include "G4UrbanMscModel.hh"
#include "G4WentzelVIModel.hh"
#include "G4CoulombScattering.hh"
#include "G4eCoulombScatteringModel.hh"
#include "G4WentzelVIModel.hh"
#include "G4NuclearStopping.hh"
#include "G4IonParametrisedLossModel.hh"

#include "G4EmProcessOptions.hh"

#include "G4UAtomicDeexcitation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysics::ConstructEM()
{
  fEMPhysicsList->ConstructProcess();
/*
  if(verboseLevel > 1) {
    G4cout << "### " << GetPhysicsName() << " Construct Processes " << G4endl;
  }

  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

  // muon & hadron bremsstrahlung and pair production
  G4MuBremsstrahlung* mub = new G4MuBremsstrahlung();
  G4MuPairProduction* mup = new G4MuPairProduction();
  G4hBremsstrahlung* pib = new G4hBremsstrahlung();
  G4hPairProduction* pip = new G4hPairProduction();
  G4hBremsstrahlung* kb = new G4hBremsstrahlung();
  G4hPairProduction* kp = new G4hPairProduction();
  G4hBremsstrahlung* pb = new G4hBremsstrahlung();
  G4hPairProduction* pp = new G4hPairProduction();

  // muon & hadron multiple scattering
  G4MuMultipleScattering* mumsc = new G4MuMultipleScattering();
  mumsc->AddEmModel(0, new G4WentzelVIModel());
  G4MuMultipleScattering* pimsc = new G4MuMultipleScattering();
  //pimsc->AddEmModel(0, new G4WentzelVIModel());
  G4MuMultipleScattering* kmsc = new G4MuMultipleScattering();
  //kmsc->AddEmModel(0, new G4WentzelVIModel());
  G4MuMultipleScattering* pmsc = new G4MuMultipleScattering();
  //pmsc->AddEmModel(0, new G4WentzelVIModel());
  G4hMultipleScattering* hmsc = new G4hMultipleScattering("ionmsc");

  // high energy limit for e+- scattering models
  G4double highEnergyLimit = 100*MeV;
  
  // nuclear stopping
  G4NuclearStopping* ionnuc = new G4NuclearStopping();
  G4NuclearStopping* pnuc = new G4NuclearStopping();

  // Add EM Processes
  aParticleIterator->reset();

  while( (*aParticleIterator)() ){

    G4ParticleDefinition* particle = aParticleIterator->value();
    G4String particleName = particle->GetParticleName();

    //Applicability range for Penelope models
    //for higher energies, the Standard models are used
    G4double PenelopeHighEnergyLimit = 1.0*GeV;

    if (particleName == "gamma") {
       //Photo-electric effect
       G4PhotoElectricEffect* thePhotoElectricEffect =
                                                  new G4PhotoElectricEffect();
       if (enablePenelope) {
          G4PenelopePhotoElectricModel* thePEPenelopeModel =
                                           new G4PenelopePhotoElectricModel();
          thePEPenelopeModel->SetHighEnergyLimit(PenelopeHighEnergyLimit);
          thePhotoElectricEffect->SetEmModel(thePEPenelopeModel, 1);
       }
       ph->RegisterProcess(thePhotoElectricEffect, particle);

       //Compton scattering
       G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
       if (enablePenelope) {
          G4PenelopeComptonModel* theComptonPenelopeModel =
                                                 new G4PenelopeComptonModel();
          theComptonPenelopeModel->SetHighEnergyLimit(PenelopeHighEnergyLimit);
          theComptonScattering->SetEmModel(theComptonPenelopeModel, 1);
       }
       ph->RegisterProcess(theComptonScattering, particle);

       //Gamma conversion
       G4GammaConversion* theGammaConversion = new G4GammaConversion();
       if (enablePenelope) {
          G4PenelopeGammaConversionModel* theGCPenelopeModel =
                                         new G4PenelopeGammaConversionModel();
          theGammaConversion->SetEmModel(theGCPenelopeModel,1);
       }
       ph->RegisterProcess(theGammaConversion, particle);

       //Rayleigh scattering
       G4RayleighScattering* theRayleigh = new G4RayleighScattering();
       if (enablePenelope) {
          G4PenelopeRayleighModel* theRayleighPenelopeModel =
                                                new G4PenelopeRayleighModel();
          //theRayleighPenelopeModel->
          //                      SetHighEnergyLimit(PenelopeHighEnergyLimit);
          theRayleigh->SetEmModel(theRayleighPenelopeModel, 1);
       }
       ph->RegisterProcess(theRayleigh, particle);

    } else if (particleName == "e-") {

       // multiple scattering
       G4eMultipleScattering* msc = new G4eMultipleScattering;
       msc->SetStepLimitType(fUseDistanceToBoundary);
       G4UrbanMscModel* msc1 = new G4UrbanMscModel();
       G4WentzelVIModel* msc2 = new G4WentzelVIModel();
       msc1->SetHighEnergyLimit(highEnergyLimit);
       msc2->SetLowEnergyLimit(highEnergyLimit);
       msc->SetRangeFactor(0.01);
       msc->AddEmModel(0, msc1);
       msc->AddEmModel(0, msc2);

       G4eCoulombScatteringModel* ssm = new G4eCoulombScatteringModel();
       G4CoulombScattering* ss = new G4CoulombScattering();
       ss->SetEmModel(ssm, 1);
       ss->SetMinKinEnergy(highEnergyLimit);
       ssm->SetLowEnergyLimit(highEnergyLimit);
       ssm->SetActivationLowEnergyLimit(highEnergyLimit);

       //Ionisation
       G4eIonisation* eIoni = new G4eIonisation();
       if (enablePenelope) {
          G4PenelopeIonisationModel* theIoniPenelope =
                                              new G4PenelopeIonisationModel();
          theIoniPenelope->SetHighEnergyLimit(PenelopeHighEnergyLimit);
          eIoni->AddEmModel(0,theIoniPenelope,new G4UniversalFluctuation());
          eIoni->SetStepFunction(0.2, 100*um);
       }

       //Bremsstrahlung
       G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
       if (enablePenelope) {
          G4PenelopeBremsstrahlungModel* theBremPenelope =
                                          new G4PenelopeBremsstrahlungModel();
          theBremPenelope->SetHighEnergyLimit(PenelopeHighEnergyLimit);
          eBrem->AddEmModel(0,theBremPenelope);
       }

       ph->RegisterProcess(msc, particle);
       ph->RegisterProcess(eIoni, particle);
       ph->RegisterProcess(eBrem, particle);
       ph->RegisterProcess(ss, particle);

    } else if (particleName == "e+") {

       // multiple scattering
       G4eMultipleScattering* msc = new G4eMultipleScattering;
       msc->SetStepLimitType(fUseDistanceToBoundary);
       G4UrbanMscModel* msc1 = new G4UrbanMscModel();
       G4WentzelVIModel* msc2 = new G4WentzelVIModel();
       msc1->SetHighEnergyLimit(highEnergyLimit);
       msc2->SetLowEnergyLimit(highEnergyLimit);
       msc->SetRangeFactor(0.01);
       msc->AddEmModel(0, msc1);
       msc->AddEmModel(0, msc2);

       G4eCoulombScatteringModel* ssm = new G4eCoulombScatteringModel();
       G4CoulombScattering* ss = new G4CoulombScattering();
       ss->SetEmModel(ssm, 1);
       ss->SetMinKinEnergy(highEnergyLimit);
       ssm->SetLowEnergyLimit(highEnergyLimit);
       ssm->SetActivationLowEnergyLimit(highEnergyLimit);

       //Ionisation
       G4eIonisation* eIoni = new G4eIonisation();
       if (enablePenelope) {
          G4PenelopeIonisationModel* theIoniPenelope =
                                              new G4PenelopeIonisationModel();
          theIoniPenelope->SetHighEnergyLimit(PenelopeHighEnergyLimit);
          eIoni->AddEmModel(0,theIoniPenelope,new G4UniversalFluctuation());
          eIoni->SetStepFunction(0.2, 100*um);
       }

       //Bremsstrahlung
       G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
       if (enablePenelope) {
          G4PenelopeBremsstrahlungModel* theBremPenelope =
                                          new G4PenelopeBremsstrahlungModel();
          theBremPenelope->SetHighEnergyLimit(PenelopeHighEnergyLimit);
          eBrem->AddEmModel(0,theBremPenelope);
       }

       //Annihilation
       G4eplusAnnihilation* eAnni = new G4eplusAnnihilation();
       if (enablePenelope) {
          G4PenelopeAnnihilationModel* theAnnPenelope =
                                            new G4PenelopeAnnihilationModel();
          theAnnPenelope->SetHighEnergyLimit(PenelopeHighEnergyLimit);
          eAnni->AddEmModel(0,theAnnPenelope);
       }

       ph->RegisterProcess(msc, particle);
       ph->RegisterProcess(eIoni, particle);
       ph->RegisterProcess(eBrem, particle);
       ph->RegisterProcess(eAnni, particle);
       ph->RegisterProcess(ss, particle);

    } else if (particleName == "mu+" ||
               particleName == "mu-"    ) {

      G4MuIonisation* muIoni = new G4MuIonisation();
      muIoni->SetStepFunction(0.2, 50*um);

      ph->RegisterProcess(mumsc, particle);
      ph->RegisterProcess(muIoni, particle);
      ph->RegisterProcess(mub, particle);
      ph->RegisterProcess(mup, particle);
      ph->RegisterProcess(new G4CoulombScattering(), particle);

    } else if (particleName == "alpha" ||
               particleName == "He3" ) {

      G4hMultipleScattering* msc = new G4hMultipleScattering();

      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetStepFunction(0.1, 10*um);

      ph->RegisterProcess(msc,particle);
      ph->RegisterProcess(ionIoni, particle);
      ph->RegisterProcess(ionnuc, particle);

    } else if (particleName == "GenericIon") {

      G4ionIonisation* ionIoni = new G4ionIonisation();
      ionIoni->SetEmModel(new G4IonParametrisedLossModel());
      ionIoni->SetStepFunction(0.1, 1*um);

      ph->RegisterProcess(hmsc, particle);
      ph->RegisterProcess(ionIoni, particle);
      ph->RegisterProcess(ionnuc, particle);

    } else if (particleName == "pi+" ||
               particleName == "pi-" ) {

      G4hIonisation* hIoni = new G4hIonisation();
      hIoni->SetStepFunction(0.2, 50*um);

      ph->RegisterProcess(pimsc, particle);
      ph->RegisterProcess(hIoni, particle);
      ph->RegisterProcess(pib, particle);
      ph->RegisterProcess(pip, particle);

    } else if (particleName == "kaon+" ||
               particleName == "kaon-" ) {

      G4hIonisation* hIoni = new G4hIonisation();
      hIoni->SetStepFunction(0.2, 50*um);

      ph->RegisterProcess(kmsc, particle);
      ph->RegisterProcess(hIoni, particle);
      ph->RegisterProcess(kb, particle);
      ph->RegisterProcess(kp, particle);

    } else if (particleName == "proton" ||
               particleName == "anti_proton") {

      G4hIonisation* hIoni = new G4hIonisation();
      hIoni->SetStepFunction(0.2, 50*um);

      ph->RegisterProcess(pmsc, particle);
      ph->RegisterProcess(hIoni, particle);
      ph->RegisterProcess(pb, particle);
      ph->RegisterProcess(pp, particle);
      ph->RegisterProcess(pnuc, particle);

    } else if (particleName == "B+" ||
               particleName == "B-" ||
               particleName == "D+" ||
               particleName == "D-" ||
               particleName == "Ds+" ||
               particleName == "Ds-" ||
               particleName == "anti_He3" ||
               particleName == "anti_alpha" ||
               particleName == "anti_deuteron" ||
               particleName == "anti_lambda_c+" ||
               particleName == "anti_omega-" ||
               particleName == "anti_sigma_c+" ||
               particleName == "anti_sigma_c++" ||
               particleName == "anti_sigma+" ||
               particleName == "anti_sigma-" ||
               particleName == "anti_triton" ||
               particleName == "anti_xi_c+" ||
               particleName == "anti_xi-" ||
               particleName == "deuteron" ||
               particleName == "lambda_c+" ||
               particleName == "omega-" ||
               particleName == "sigma_c+" ||
               particleName == "sigma_c++" ||
               particleName == "sigma+" ||
               particleName == "sigma-" ||
               particleName == "tau+" ||
               particleName == "tau-" ||
               particleName == "triton" ||
               particleName == "xi_c+" ||
               particleName == "xi-" ) {

      ph->RegisterProcess(hmsc, particle);
      ph->RegisterProcess(new G4hIonisation(), particle);
      ph->RegisterProcess(pnuc, particle);
    }
  }

  // Em options
  //      
  G4EmProcessOptions opt;
  opt.SetVerbose(verboseLevel);
   
  // Multiple Coulomb scattering
  //
  //opt.SetMscStepLimitation(fUseDistanceToBoundary);
  //opt.SetMscRangeFactor(0.02);
     
  // Physics tables
  //
 
  opt.SetMinEnergy(100*eV);
  opt.SetMaxEnergy(10*TeV);
  opt.SetDEDXBinning(220);
  opt.SetLambdaBinning(220);
 
  // Nuclear stopping
  pnuc->SetMaxKinEnergy(1*MeV);
 
  //opt.SetSplineFlag(true);
  opt.SetPolarAngleLimit(CLHEP::pi);
     
  // Ionization
  //
  //opt.SetSubCutoff(true);    

  // Deexcitation
  //
  G4VAtomDeexcitation* deexcitation = new G4UAtomicDeexcitation();
  G4LossTableManager::Instance()->SetAtomDeexcitation(deexcitation);
  deexcitation->SetFluo(true);
  deexcitation->SetAuger(true);
  deexcitation->SetPIXE(false); 
*/
}

// optics
#include "G4OpticalPhysics.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "nEXOG4S1Light.hh"
#include "nEXOG4S2Light.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpWLS.hh"
#include "G4EmSaturation.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysics::ConstructOp()
{
  if (!enableOptics) return;

  G4Cerenkov* theCerenkovProcess            = new G4Cerenkov("Cerenkov");
  //G4Scintillation* theScintillationProcess = new G4Scintillation("Scintillation");
  nEXOG4S1Light* theScintillationProcess = new nEXOG4S1Light();
  G4OpAbsorption* theAbsorptionProcess     = new G4OpAbsorption();
  G4OpRayleigh* theRayleighScatteringProcess = new G4OpRayleigh();
  G4OpBoundaryProcess* theBoundaryProcess  = new G4OpBoundaryProcess();
  G4OpWLS* theWLSProcess  = new G4OpWLS();
  theWLSProcess->UseTimeProfile("delta");

  //theCerenkovProcess->SetMaxNumPhotonsPerStep(300);
  //theCerenkovProcess->SetTrackSecondariesFirst(true);

  theScintillationProcess->SetScintillationYieldFactor(1.); // NEST: 1. = enabled, 0. = disabled
  theScintillationProcess->SetTrackSecondariesFirst(false);

  //G4OpticalSurfaceModel themodel = unified;
  //theBoundaryProcess->SetModel(themodel);

  // Use Birks Correction in the Scintillation process

  //G4EmSaturation* emSaturation =
  //                             G4LossTableManager::Instance()->EmSaturation();
  //theScintillationProcess->AddSaturation(emSaturation);

  aParticleIterator->reset();
  while( (*aParticleIterator)() ) {

    G4ParticleDefinition* particle = aParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (theCerenkovProcess->IsApplicable(*particle)) {
      pmanager->AddProcess(theCerenkovProcess);
      pmanager->SetProcessOrdering(theCerenkovProcess, idxPostStep);
    }

    if (theScintillationProcess->IsApplicable(*particle)) {
      // mostly charged ones
      //pmanager->AddProcess(theScintillationProcess);
      //pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
      //pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
      pmanager->AddProcess(theScintillationProcess, ordDefault, ordInActive, ordDefault); //for nest
    }
    //if (particleName == "opticalphoton") {
    //  // photons only
    //  pmanager->AddDiscreteProcess(theAbsorptionProcess);
    //  pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
    //  pmanager->AddDiscreteProcess(theBoundaryProcess);
    //  pmanager->AddDiscreteProcess(theWLSProcess);
    //} 
  }

}

// neutron physic
#include "G4MuonNuclearProcess.hh"
#include "G4MuonVDNuclearModel.hh"

#include "G4MuonMinusCapture.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4NeutronRadCapture.hh"
#include "G4NeutronCaptureXS.hh"

#include "G4HadronElasticProcess.hh"
#include "G4HadronElastic.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4BGGNucleonInelasticXS.hh"
#include "G4CascadeInterface.hh"

#include "G4FTFModel.hh"
#include "G4TheoFSGenerator.hh"
#include "G4ExcitationHandler.hh"
#include "G4PreCompoundModel.hh"
#include "G4GeneratorPrecompoundInterface.hh"
#include "G4QGSMFragmentation.hh"
#include "G4ExcitedStringDecay.hh"

#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPInelasticData.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4NeutronHPCapture.hh"
#include "G4NeutronHPCaptureData.hh"
#include "G4HadronFissionProcess.hh"
#include "G4LFission.hh"
#include "G4NeutronHPFission.hh"
#include "G4NeutronHPFissionData.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysics::ConstructHad()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

  aParticleIterator->reset();
  while( (*aParticleIterator)() ){

    G4ParticleDefinition* particle = aParticleIterator->value();
    G4String particleName = particle->GetParticleName();

    if       ( particleName == "mu+" ||
               particleName == "mu-"    ) {
      // muon
      if (enableMuNuclear) {
        G4MuonNuclearProcess* theMuNuclearProcess = new G4MuonNuclearProcess();
        G4MuonVDNuclearModel* muNucModel = new G4MuonVDNuclearModel();
        theMuNuclearProcess->RegisterMe(muNucModel);
        ph->RegisterProcess(theMuNuclearProcess,particle);
	if( particleName == "mu-" )
          ph->RegisterProcess(new G4MuonMinusCapture(),particle);
      }

    } else if( particleName == "neutron" ) {
      // neutrons
      if (enableHPNeutron) {

	// elastic scattering
        G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess;
        G4HadronElastic* theElasticModel = new G4HadronElastic;
	theElasticModel->SetMinEnergy(19*MeV);
	G4NeutronHPElastic *theElasticNeutronHP = new G4NeutronHPElastic;
	theElasticNeutronHP->SetMaxEnergy(19*MeV);
	theElasticProcess->RegisterMe(theElasticModel);
	theElasticProcess->RegisterMe(theElasticNeutronHP);
	theElasticProcess->AddDataSet(new G4NeutronHPElasticData());
        ph->RegisterProcess(theElasticProcess,particle);

	// inelastic scattering
	G4NeutronInelasticProcess* theInelasticProcess =
	  new G4NeutronInelasticProcess("inelastic");
        theInelasticProcess->
             AddDataSet( new G4BGGNucleonInelasticXS( G4Neutron::Neutron() ) );

        G4FTFModel* theStringModel = new G4FTFModel;
        G4ExcitedStringDecay* theStringDecay =
                     new G4ExcitedStringDecay( new G4LundStringFragmentation );
        theStringModel->SetFragmentationModel( theStringDecay );
        G4PreCompoundModel* thePreEquilib =
                             new G4PreCompoundModel( new G4ExcitationHandler );
        G4GeneratorPrecompoundInterface* theCascade =
                          new G4GeneratorPrecompoundInterface( thePreEquilib );

        G4TheoFSGenerator* theModel = new G4TheoFSGenerator( "FTFP" );
        theModel->SetHighEnergyGenerator( theStringModel );
        theModel->SetTransport( theCascade );
        const G4double theFTFMin =    4.0*GeV;
        const G4double theFTFMax =  100.0*TeV;
        theModel->SetMinEnergy( theFTFMin );
        theModel->SetMaxEnergy( theFTFMax );

        G4CascadeInterface* theBERTModel = new G4CascadeInterface;
        const G4double theBERTMin =  19.0*MeV;
        const G4double theBERTMax =   5.0*GeV;
        theBERTModel->SetMinEnergy( theBERTMin );
        theBERTModel->SetMaxEnergy( theBERTMax );
       
        theInelasticProcess->RegisterMe(theBERTModel);
        theInelasticProcess->RegisterMe(theModel);

	G4NeutronHPInelastic * theInelasticNeutronHP =
	  new G4NeutronHPInelastic;
	theInelasticNeutronHP->SetMaxEnergy(19*MeV);
	theInelasticProcess->RegisterMe(theInelasticNeutronHP);
	theInelasticProcess->AddDataSet(new G4NeutronHPInelasticData());
        ph->RegisterProcess(theInelasticProcess,particle);

	// capture
        G4HadronCaptureProcess *theCaptureProcess =
                                        new G4HadronCaptureProcess("nCapture");

	G4NeutronHPCapture * theCaptureNeutronHP = new G4NeutronHPCapture;

        const G4double theHPMin =      0.0*GeV;
        const G4double theHPMax =     19.0*MeV;

        theCaptureNeutronHP->SetMinEnergy( theHPMin );
        theCaptureNeutronHP->SetMaxEnergy( theHPMax );

	theCaptureProcess->RegisterMe(theCaptureNeutronHP);
	theCaptureProcess->AddDataSet(new G4NeutronHPCaptureData());
        ph->RegisterProcess(theCaptureProcess,particle);

	// fission
	G4HadronFissionProcess* theFissionProcess =
	  new G4HadronFissionProcess;
	G4LFission* theFissionModel = new G4LFission;
	theFissionModel->SetMinEnergy(19*MeV);
	theFissionProcess->RegisterMe(theFissionModel);
	G4NeutronHPFission * theFissionNeutronHP = new G4NeutronHPFission;
	theFissionNeutronHP->SetMaxEnergy(19*MeV);
	theFissionProcess->RegisterMe(theFissionNeutronHP);
	theFissionProcess->AddDataSet(new G4NeutronHPFissionData());
        ph->RegisterProcess(theFissionProcess,particle);

      } else {

        // Elastic scattering
        G4HadronElasticProcess* theElasticProcess =
                                                  new G4HadronElasticProcess();
        G4HadronElastic* protelMod = new G4HadronElastic;
        theElasticProcess->RegisterMe(protelMod);
        G4PhysicsListHelper::GetPhysicsListHelper()->
                                   RegisterProcess(theElasticProcess,particle);
        G4HadronCaptureProcess *theCaptureProcess =
                                        new G4HadronCaptureProcess("nCapture");
        theCaptureProcess->AddDataSet(new G4NeutronCaptureXS());
        theCaptureProcess->RegisterMe(new G4NeutronRadCapture());
        ph->RegisterProcess(theCaptureProcess,particle);
      }
    //} else if( particleName == "antineutron" ) {
    //} else if( particleName == "proton" ) {
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"
#include "G4IonTable.hh"
#include "G4GenericIon.hh"
#include "G4RadioactiveDecay.hh"

void EXOPhysics::ConstructGeneral()
{
  G4Decay* theDecayProcess = new G4Decay();
  G4RadioactiveDecay*  theRadioactiveDecay = new G4RadioactiveDecay();

  aParticleIterator->reset();
  while( (*aParticleIterator)() ){
    G4ParticleDefinition* particle = aParticleIterator->value();
    if (theDecayProcess->IsApplicable(*particle)) {
       G4PhysicsListHelper::GetPhysicsListHelper()->
                                    RegisterProcess(theDecayProcess,particle);
    }
  }

  G4PhysicsListHelper::GetPhysicsListHelper()->
        RegisterProcess(theRadioactiveDecay,G4GenericIon::GenericIon());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
