#include "globals.hh"
#include "G4ios.hh"

#include "EXOPhysicsList.hh"

#include "G4ProcessManager.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EXOPhysicsList::EXOPhysicsList():  G4VUserPhysicsList()
{
  SetVerboseLevel(1);

  customBosons     = true;
  customLeptons    = true;
  customMesons     = true;
  customBaryons    = true;
  customIons       = true;
  customShortLived = true;

  // remember, these options are to speed up start
  //   for regular manipulation use /process/[in]activate <name>
  enableATeam      = false; // obsolete
  enablePenelope   = true;
  enableMuNuclear  = true;
  enableHPNeutron  = true;
  enableOptics     = true;
  
  //Default cuts are applied everywhere, then A G4Region is defined below to set
  //cuts for innerCryostat and all daughters to much finer cuts. 
  defaultCutValue  = 10.0*mm;
  cutForGamma      = defaultCutValue;
  cutForElectron   = defaultCutValue;
  cutForPositron   = defaultCutValue;
  cutForMuon       = 0.0;
  cutForProton     = defaultCutValue;
  cutForNeutron    = 0.0;
  cutForAlpha      = 0.0;
  cutForGenericIon = 0.0;
  cutInsideTPC     = 0.1*mm;
  cutInnerRegion   = 1.0*mm;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EXOPhysicsList::~EXOPhysicsList()
{}

#include "G4ParticleTypes.hh"
#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program.

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
  ConstructIons();
  ConstructShortLived();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructBosons()
{
  if (customBosons) {

    // pseudo-particles
    G4Geantino::GeantinoDefinition();
    G4ChargedGeantino::ChargedGeantinoDefinition();

    // gamma
    G4Gamma::GammaDefinition();

    // optical photon
    G4OpticalPhoton::OpticalPhotonDefinition();

  } else {
    // GEANT defaults
    G4BosonConstructor::ConstructParticle();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructLeptons()
{
  if (customLeptons) {

    // leptons
    G4Electron::ElectronDefinition();
    G4Positron::PositronDefinition();
    G4MuonPlus::MuonPlusDefinition();
    G4MuonMinus::MuonMinusDefinition();

    G4NeutrinoE::NeutrinoEDefinition();
    G4AntiNeutrinoE::AntiNeutrinoEDefinition();
    G4NeutrinoMu::NeutrinoMuDefinition();
    G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();

  } else {
    // GEANT defaults
    G4LeptonConstructor::ConstructParticle();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructMesons()
{
  if (customMesons) {

    //  mesons
    G4PionPlus::PionPlusDefinition();
    G4PionMinus::PionMinusDefinition();
    G4PionZero::PionZeroDefinition();
    G4Eta::EtaDefinition();
    G4EtaPrime::EtaPrimeDefinition();
    G4KaonPlus::KaonPlusDefinition();
    G4KaonMinus::KaonMinusDefinition();
    G4KaonZero::KaonZeroDefinition();
    G4AntiKaonZero::AntiKaonZeroDefinition();
    G4KaonZeroLong::KaonZeroLongDefinition();
    G4KaonZeroShort::KaonZeroShortDefinition();

  } else {
    // GEANT defaults
    G4MesonConstructor::ConstructParticle();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructBaryons()
{
  if (customBaryons) {

    //  barions
    G4Proton::ProtonDefinition();
    G4AntiProton::AntiProtonDefinition();
    G4Neutron::NeutronDefinition();
    G4AntiNeutron::AntiNeutronDefinition();

  } else {
    // GEANT defaults
    G4BaryonConstructor::ConstructParticle();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructIons()
{
  if (customIons) {

    //ions
    G4Deuteron::DeuteronDefinition();
    G4Triton::TritonDefinition();
    G4He3::He3Definition();
    G4Alpha::AlphaDefinition();
    G4GenericIon::GenericIonDefinition();

  } else {
    // GEANT defaults
    G4IonConstructor::ConstructParticle();
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructShortLived()
{
  if (customShortLived) {

    // nothing, really nothing

  } else {
    // GEANT defaults
    G4ShortLivedConstructor::ConstructParticle();
  }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructOp();
  ConstructHad();
  ConstructGeneral();

  if (verboseLevel>2) {
    theParticleIterator->reset();
    while( (*theParticleIterator)() ){
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();
      pmanager->DumpInfo();
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
//#include "G4LowEnergyIonisation.hh"
//#include "G4LowEnergyBremsstrahlung.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"
//#include "EXOSim/EXOElectronConversion.hh"
#include "G4RayleighScattering.hh"

// Penelope Model
#include "G4PenelopeRayleighModel.hh"
#include "G4PenelopeComptonModel.hh"
#include "G4PenelopePhotoElectricModel.hh"
#include "G4PenelopeGammaConversionModel.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4PenelopeBremsstrahlungModel.hh"
#include "G4PenelopeAnnihilationModel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructEM()
{
  //const G4RegionStore* theRegionStore = G4RegionStore::GetInstance();
  //G4Region* InnerRegion = theRegionStore->GetRegion("InnerRegion");
  
  //  EXOElectronConversion* theEXOElectronConversionProcess = new EXOElectronConversion("Conversion");

  G4RayleighScattering* theRayleighScattering = new G4RayleighScattering();
  G4ComptonScattering* theComptonScattering = new G4ComptonScattering();
  G4PhotoElectricEffect* thePhotoElectricEffect = new G4PhotoElectricEffect();
  G4GammaConversion* theGammaConversion = new G4GammaConversion();
  G4eIonisation* theIonisation = new G4eIonisation();
  G4eBremsstrahlung* theBremsstrahlung = new G4eBremsstrahlung();
  G4eplusAnnihilation* theAnnihilation = new G4eplusAnnihilation();

  if (enablePenelope) {
    // Low Energy Electromagnetic Physics, Penelope Model
    theRayleighScattering->SetModel(new G4PenelopeRayleighModel());
    theComptonScattering->SetModel(new G4PenelopeComptonModel());
    G4PenelopePhotoElectricModel* thePenelopePhotoElectricModel = new G4PenelopePhotoElectricModel();
    thePenelopePhotoElectricModel->ActivateAuger(true);
    thePhotoElectricEffect->SetModel(thePenelopePhotoElectricModel);
    theGammaConversion->SetModel(new G4PenelopeGammaConversionModel());
    G4PenelopeIonisationModel* thePenelopeIonisationModel = new G4PenelopeIonisationModel();
    thePenelopeIonisationModel->ActivateAuger(true);
    theIonisation->SetEmModel(thePenelopeIonisationModel);
    theBremsstrahlung->SetEmModel(new G4PenelopeBremsstrahlungModel());
    theAnnihilation->SetModel(new G4PenelopeAnnihilationModel());
  }

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){

    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();


    if        (particleName == "gamma") {
      // gamma
      pmanager->AddDiscreteProcess(thePhotoElectricEffect);
      pmanager->AddDiscreteProcess(theComptonScattering);
      pmanager->AddDiscreteProcess(theGammaConversion);
      pmanager->AddDiscreteProcess(theRayleighScattering);

    } else if (particleName == "e-") {
      //electron
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1, 1);
      pmanager->AddProcess(theIonisation, -1, 2, 2);
      pmanager->AddProcess(theBremsstrahlung, -1, -3, 3);
      //      if (enableATeam)
      //        pmanager->AddDiscreteProcess(theEXOElectronConversionProcess);

    } else if (particleName == "e+") {
      //positron
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1, 1);
      pmanager->AddProcess(theIonisation,        -1, 2, 2);
      pmanager->AddProcess(theBremsstrahlung,    -1, 3, 3);
      pmanager->AddProcess(theAnnihilation,   0,-1, 4);
      //      if (enableATeam)
      //        pmanager->AddDiscreteProcess(theEXOElectronConversionProcess);

    } else if( particleName == "mu+" ||
               particleName == "mu-"    ) {
      //muon
      pmanager->AddProcess(new G4MuMultipleScattering,-1, 1, 1);
      pmanager->AddProcess(new G4MuIonisation,       -1, 2, 2);
      pmanager->AddProcess(new G4MuBremsstrahlung,   -1, 3, 3); // -1,-1, 3
      pmanager->AddProcess(new G4MuPairProduction,   -1, 4, 4); // -1,-1, 4
      //      if (enableATeam)
      //        pmanager->AddDiscreteProcess(theEXOElectronConversionProcess);

    } else if( particleName == "proton" ||
               particleName == "pi-" ||
               particleName == "pi+"    ) {
      //proton
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,         -1, 2, 2);
      pmanager->AddProcess(new G4hBremsstrahlung,     -1, 3, 3);
      pmanager->AddProcess(new G4hPairProduction,     -1, 4, 4);
      //      if (enableATeam)
      //        pmanager->AddDiscreteProcess(theEXOElectronConversionProcess);

    } else if( particleName == "alpha" ||
               particleName == "He3" )     {
      //alpha
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);
      //      if (enableATeam)
      //        pmanager->AddDiscreteProcess(theEXOElectronConversionProcess);

    } else if( particleName == "GenericIon" ) {
      //Ions
      pmanager->AddProcess(new G4hMultipleScattering, -1, 1, 1);
      pmanager->AddProcess(new G4ionIonisation,       -1, 2, 2);
      //      if (enableATeam)
      //        pmanager->AddDiscreteProcess(theEXOElectronConversionProcess);

    } else if ((!particle->IsShortLived()) &&
               (particle->GetPDGCharge() != 0.0) &&
               (particle->GetParticleName() != "chargedgeantino")) {
      //all others charged particles except geantino
      pmanager->AddProcess(new G4hMultipleScattering,-1, 1, 1);
      pmanager->AddProcess(new G4hIonisation,        -1, 2, 2);
    }
  }
}


// optics
#include "G4OpticalPhysics.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpBoundaryProcess.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructOp()
{
  if (!enableOptics) return;

  //G4Cerenkov theCerenkovProcess            = new G4Cerenkov("Cerenkov");
  G4Scintillation* theScintillationProcess = new G4Scintillation("Scintillation");
  G4OpAbsorption* theAbsorptionProcess     = new G4OpAbsorption();
  G4OpRayleigh* theRayleighScatteringProcess = new G4OpRayleigh();
  G4OpBoundaryProcess* theBoundaryProcess  = new G4OpBoundaryProcess();

  //theCerenkovProcess->SetMaxNumPhotonsPerStep(300);
  //theCerenkovProcess->SetTrackSecondariesFirst(true);

  theScintillationProcess->SetScintillationYieldFactor(1.);
  theScintillationProcess->SetTrackSecondariesFirst(true);

  G4OpticalSurfaceModel themodel = unified;
  theBoundaryProcess->SetModel(themodel);

  theParticleIterator->reset();
  while( (*theParticleIterator)() ) {

    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if (theScintillationProcess->IsApplicable(*particle)) {
      // mostly charged ones
      pmanager->AddProcess(theScintillationProcess);
      pmanager->SetProcessOrderingToLast(theScintillationProcess, idxAtRest);
      pmanager->SetProcessOrderingToLast(theScintillationProcess, idxPostStep);
    }
    if (particleName == "opticalphoton") {
      // photons only
      G4cout << " AddDiscreteProcess to OpticalPhoton " << G4endl;
      pmanager->AddDiscreteProcess(theAbsorptionProcess);
      pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
      pmanager->AddDiscreteProcess(theBoundaryProcess);
    }
  }

}


// neutron physic
#include "G4MuNuclearInteraction.hh"
#include "G4MuonMinusCaptureAtRest.hh"
#include "G4NeutronCaptureAtRest.hh"

#include "G4HadronElasticProcess.hh"
#include "G4LElastic.hh"
#include "G4NeutronHPElastic.hh"
#include "G4NeutronHPElasticData.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4HENeutronInelastic.hh"
#include "G4LENeutronInelastic.hh"
#include "G4NeutronHPInelastic.hh"
#include "G4NeutronHPInelasticData.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4LCapture.hh"
#include "G4NeutronHPCapture.hh"
#include "G4NeutronHPCaptureData.hh"
#include "G4HadronFissionProcess.hh"
#include "G4NeutronHPFission.hh"
#include "G4NeutronHPFissionData.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EXOPhysicsList::ConstructHad()
{

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){

    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();

    if       ( particleName == "mu+" ||
               particleName == "mu-"    ) {
      // muon
      if (enableMuNuclear) {
	G4MuNuclearInteraction *theMuNuclearProcess = new G4MuNuclearInteraction;
	pmanager->AddProcess(theMuNuclearProcess);
	pmanager->SetProcessOrderingToLast(theMuNuclearProcess, idxPostStep);
	if( particleName == "mu-" )
	  pmanager->AddRestProcess(new G4MuonMinusCaptureAtRest(), 2*ordDefault);
	    // need this to not interfere with Decay
      }

    } else if( particleName == "neutron" ) {
      // neutrons
      if (enableHPNeutron) {

	// elastic scattering
	G4HadronElasticProcess* theElasticProcess = 
	  new G4HadronElasticProcess;
	G4LElastic *theElasticModel = new G4LElastic;
	theElasticModel->SetMinEnergy(19*MeV);
	G4NeutronHPElastic *theElasticNeutronHP = new G4NeutronHPElastic;
	theElasticNeutronHP->SetMaxEnergy(19*MeV);
	theElasticProcess->RegisterMe(theElasticModel);
	theElasticProcess->RegisterMe(theElasticNeutronHP);
	//G4NeutronHPElasticData * theNeutronData = new G4NeutronHPElasticData;
	theElasticProcess->AddDataSet(new G4NeutronHPElasticData());
	pmanager->AddDiscreteProcess(theElasticProcess);

	// inelastic scattering
	G4NeutronInelasticProcess* theInelasticProcess =
	  new G4NeutronInelasticProcess("inelastic");
	G4HENeutronInelastic* theInelasticModel2 = new G4HENeutronInelastic;
	theInelasticModel2->SetMinEnergy(55*GeV);
	theInelasticProcess->RegisterMe(theInelasticModel2);
	G4LENeutronInelastic* theInelasticModel = new G4LENeutronInelastic;
	theInelasticModel->SetMinEnergy(19*MeV);
	theInelasticProcess->RegisterMe(theInelasticModel);
	G4NeutronHPInelastic * theInelasticNeutronHP =
	  new G4NeutronHPInelastic;
	theInelasticNeutronHP->SetMaxEnergy(19*MeV);
	theInelasticProcess->RegisterMe(theInelasticNeutronHP);
	theInelasticProcess->AddDataSet(new G4NeutronHPInelasticData());
	pmanager->AddDiscreteProcess(theInelasticProcess);

	// capture
	G4HadronCaptureProcess* theCaptureProcess =
	  new G4HadronCaptureProcess;
	G4LCapture* theCaptureModel = new G4LCapture;
	theCaptureModel->SetMinEnergy(19*MeV);
	theCaptureProcess->RegisterMe(theCaptureModel);
	G4NeutronHPCapture * theCaptureNeutronHP = new G4NeutronHPCapture;
	theCaptureNeutronHP->SetMaxEnergy(19*MeV);
	theCaptureProcess->RegisterMe(theCaptureNeutronHP);
	theCaptureProcess->AddDataSet(new G4NeutronHPCaptureData());
	pmanager->AddDiscreteProcess(theCaptureProcess);

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
	pmanager->AddDiscreteProcess(theFissionProcess);

      } else {

        // Elastic scattering
        G4HadronElasticProcess* theElasticProcess = new G4HadronElasticProcess();
        G4LElastic* protelMod = new G4LElastic();
        theElasticProcess->RegisterMe(protelMod);
        pmanager->AddDiscreteProcess(theElasticProcess);
        G4NeutronCaptureAtRest *theCaptureProcess = new G4NeutronCaptureAtRest;
        pmanager->AddProcess(theCaptureProcess);
        pmanager->SetProcessOrdering(theCaptureProcess, idxAtRest);
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


void EXOPhysicsList::ConstructGeneral()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  G4RadioactiveDecay*  theRadioactiveDecay = new G4RadioactiveDecay();

  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle)) {
      pmanager ->AddProcess(theDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }


  const G4IonTable *theIonTable =
    G4ParticleTable::GetParticleTable()->GetIonTable();

  for (G4int i=0; i<theIonTable->Entries(); i++)
    {
      G4String particleName = theIonTable->GetParticle(i)->GetParticleName();
      if (particleName == "GenericIon")
        {
          G4ProcessManager* pmanager =
            theIonTable->GetParticle(i)->GetProcessManager();
          pmanager->SetVerboseLevel(0);
          pmanager ->AddProcess(theRadioactiveDecay);
          pmanager ->SetProcessOrdering(theRadioactiveDecay,idxPostStep);
          pmanager ->SetProcessOrdering(theRadioactiveDecay, idxAtRest);
        }
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "G4RegionStore.hh"

void EXOPhysicsList::SetCuts()
{
  if (verboseLevel >0){
    G4cout << "EXOPhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }
  //G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(250*eV, 100*MeV);
  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
  //

  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(50*eV, 100*MeV);
  if (cutForGamma>0.) SetCutValue(cutForGamma, "gamma");
  if (cutForElectron>0.) SetCutValue(cutForElectron, "e-");
  if (cutForPositron>0.) SetCutValue(cutForPositron, "e+");
  if (cutForMuon>0.) SetCutValue(cutForMuon, "mu-");
  if (cutForMuon>0.) SetCutValue(cutForMuon, "mu+");
  if (cutForProton>0.) SetCutValue(cutForProton, "proton");
  if (cutForNeutron>0.) SetCutValue(cutForNeutron, "neutron");
  if (cutForAlpha>0.) SetCutValue(cutForAlpha, "alpha");
  if (cutForGenericIon>0.) SetCutValue(cutForGenericIon, "GenericIon");
      if (cutInsideTPC>0.) {
    G4Region* region = G4RegionStore::GetInstance()->GetRegion("TPCRegion");
    G4ProductionCuts* cuts = new G4ProductionCuts;
    cuts->SetProductionCut(cutInsideTPC);
    region->SetProductionCuts(cuts);
    }
    if (cutInnerRegion>0.) {
    G4Region* region;
    G4ProductionCuts* cuts;

    // Set cuts for inner detector stuff with finer tracking
    region = G4RegionStore::GetInstance()->GetRegion("CryostatRegion");
    cuts = new G4ProductionCuts;
    cuts->SetProductionCut(0.1*cutInnerRegion,G4ProductionCuts::GetIndex("gamma"));
    cuts->SetProductionCut(cutInnerRegion,G4ProductionCuts::GetIndex("e-"));
    cuts->SetProductionCut(cutInnerRegion,G4ProductionCuts::GetIndex("e+"));
    region->SetProductionCuts(cuts);
    G4cout <<"InnerRegion cuts are set to:" << G4endl;
    G4cout <<"  gamma cut    = "<< cuts->GetProductionCut("gamma")/mm <<" mm"<< G4endl;
    G4cout <<"  electron cut = "<< cuts->GetProductionCut("e-")/mm    <<" mm"<< G4endl;
    G4cout <<"  positron cut = "<< cuts->GetProductionCut("e+")/mm    <<" mm"<< G4endl;
    } 
    if (cutInsideTPC>0.){
    G4Region* region;
    G4ProductionCuts* cuts;
        // Set cuts for inner detector stuff with finer tracking
    region = G4RegionStore::GetInstance()->GetRegion("TPCRegion");
    cuts = new G4ProductionCuts; 
    cuts->SetProductionCut(0.1*cutInsideTPC,G4ProductionCuts::GetIndex("gamma"));
    cuts->SetProductionCut(cutInsideTPC,G4ProductionCuts::GetIndex("e-"));
    cuts->SetProductionCut(cutInsideTPC,G4ProductionCuts::GetIndex("e+"));
    region->SetProductionCuts(cuts);
    G4cout <<"InsideTPC cuts are set to:" << G4endl;
    G4cout <<"  gamma cut    = "<< cuts->GetProductionCut("gamma")/mm <<" mm"<< G4endl;
    G4cout <<"  electron cut = "<< cuts->GetProductionCut("e-")/mm    <<" mm"<< G4endl;
    G4cout <<"  positron cut = "<< cuts->GetProductionCut("e+")/mm    <<" mm"<< G4endl;

    
    }

  if (verboseLevel>0) DumpCutValuesTable();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


