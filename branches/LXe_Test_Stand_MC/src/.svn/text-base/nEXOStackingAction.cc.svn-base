#include "nEXOStackingAction.hh"

nEXOStackingAction::nEXOStackingAction(){}
nEXOStackingAction::~nEXOStackingAction(){}

G4ClassificationOfNewTrack nEXOStackingAction::ClassifyNewTrack(const G4Track* track) 
{
  /// can choose what particles to kill, etc., or ask analysis to perform some action
  //G4cout << "Track id = " << track->GetTrackID() << " parent " << track->GetParentID() << "particle def " << track->GetDefinition()->GetParticleName() << G4endl;
  //track->GetDynamicParticle()->DumpInfo();
  //return fUrgent;
  //if(track->GetTrackID() > 1)
  //return fKill;
  return fUrgent;
}
