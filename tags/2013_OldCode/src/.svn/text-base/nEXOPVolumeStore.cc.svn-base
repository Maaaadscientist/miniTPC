// **********************************************************************
// * nEXOPVolumeStore                                                    *
// * Contains the functions for accessing and handling the parallel     *
// * world volumes                                                      *
// **********************************************************************

#include "nEXOPVolumeStore.hh"
#include <sstream>


#include "G4VPhysicalVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOPVolumeStore::nEXOPVolumeStore(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

nEXOPVolumeStore::~nEXOPVolumeStore(){}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void nEXOPVolumeStore::AddPVolume(const G4GeometryCell &cell){

  nEXOSetGeometryCell::iterator it = 
    fSetGeometryCell.find(cell);
  if (it != fSetGeometryCell.end()) {
    G4cout << "nEXOPVolumeStore::AddPVolume: cell already stored" 
	   << G4endl;
    return;
  }

  fSetGeometryCell.insert(cell);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

const G4VPhysicalVolume *nEXOPVolumeStore::
GetPVolume(const G4String &name) const {
  const G4VPhysicalVolume *pvol = 0;
  for (nEXOSetGeometryCell::const_iterator it = fSetGeometryCell.begin();
       it != fSetGeometryCell.end(); ++it) {
    const G4VPhysicalVolume &vol = it->GetPhysicalVolume();
    if (vol.GetName() == name) {
      pvol =  &vol;
    } 
  }
  if (!pvol) {
    G4cout << "nEXOPVolumeStore::GetPVolume: no physical volume named: " 
	   << name << " found" << G4endl;
  }
  return pvol;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4String nEXOPVolumeStore::GetPNames() const {
  G4String NameString;
  for (nEXOSetGeometryCell::const_iterator it = fSetGeometryCell.begin();
       it != fSetGeometryCell.end(); ++it) {
    const G4VPhysicalVolume &vol = it->GetPhysicalVolume();
    std::ostringstream os;
    os << vol.GetName() << "_" << it->GetReplicaNumber() 
       << "\n";
    G4String cellname = os.str();
    
    //    G4String cellname(vol.GetName());
    //    cellname += G4String("_");
    //    cellname += std::str(it->GetReplicaNumber());

    NameString += cellname;
  }
  return NameString;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
