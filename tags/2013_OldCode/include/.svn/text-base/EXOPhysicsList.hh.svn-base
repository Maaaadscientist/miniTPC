#ifndef EXOPhysicsList_h
#define EXOPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// class G4Cerenkov;
class G4Scintillation;
class G4OpAbsorption;
class G4OpRayleigh;
class G4OpBoundaryProcess;

class EXOPhysicsList: public G4VUserPhysicsList
{
  public:
    EXOPhysicsList();
   ~EXOPhysicsList();

   void AddParallelWorldName(G4String& pname)
        {paraWorldName.push_back(pname);}


  // use only before Construct*()
  void SetEnablePenelope( G4bool val ) { enablePenelope = val; }
  void SetEnableMuNuclear( G4bool val ) { enableMuNuclear = val; }
  void SetEnableHPNeutron( G4bool val ) { enableHPNeutron = val; }
  void SetEnableOptics( G4bool val ) { enableOptics = val; }
  void SetEnableATeam( G4bool val ) { enableATeam = val; }
  void SetEnableFineTPC( G4bool val ) { cutInsideTPC = val ? 0.0005*mm : 0.; }
  void SetEnableInnerCut( G4bool val ) { cutInnerRegion = val ? 0.1*mm : 0.; }

  protected:
    // Construct particle and physics
    void ConstructParticle();
    void ConstructProcess();
 
    void SetCuts();

   
  protected:
    // these methods Construct particles 
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBaryons();
    void ConstructIons();
    void ConstructShortLived();

  protected:
    // these methods Construct physics processes and register them
    void ConstructGeneral();
    void ConstructEM();
    void ConstructHad();
    void ConstructOp();

  private:
  //    G4Cerenkov*          theCerenkovProcess;
    G4Scintillation*     theScintillationProcess;
    G4OpAbsorption*      theAbsorptionProcess;
    G4OpRayleigh*        theRayleighScatteringProcess;
    G4OpBoundaryProcess* theBoundaryProcess;

   std::vector<G4String> paraWorldName;

  G4bool   customBosons;
  G4bool   customLeptons;
  G4bool   customMesons;
  G4bool   customBaryons;
  G4bool   customIons;
  G4bool   customShortLived;

  G4bool   enableATeam;
  G4bool   enablePenelope;
  G4bool   enableMuNuclear;
  G4bool   enableHPNeutron;
  G4bool   enableOptics;
  
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
  G4double cutForMuon;
  G4double cutForProton;
  G4double cutForNeutron;
  G4double cutForAlpha;
  G4double cutForGenericIon;
  G4double cutInsideTPC;
  G4double cutInnerRegion;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif



