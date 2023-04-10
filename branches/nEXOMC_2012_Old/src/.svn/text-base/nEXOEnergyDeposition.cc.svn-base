#include "nEXOEnergyDeposition.hh"


//
// Default constructor
//
nEXOEnergyDeposition::nEXOEnergyDeposition()
{;}
//
// Specific constructor
//
nEXOEnergyDeposition::nEXOEnergyDeposition( G4double energy,
				    G4double time,
                                    G4double weight,
                                    G4int parentid,
                                    G4int trackid,
                                    G4int gamid )
  : Energy(energy),
    Time(time),
    Weight(weight),
    Parentid(parentid),
    Trackid(trackid),
    Gamid(gamid)
{;}


//
// Copy constructor
//
nEXOEnergyDeposition::nEXOEnergyDeposition( const nEXOEnergyDeposition &right )
  : Energy(right.Energy),
    Time(right.Time),
    Weight(right.Weight),
    Parentid(right.Parentid),
    Trackid(right.Trackid),
    Gamid(right.Gamid)
{;}

//
// Destructor
//
nEXOEnergyDeposition::~nEXOEnergyDeposition() {;}

//
// Equivalence operator
//
G4bool nEXOEnergyDeposition::operator==( const nEXOEnergyDeposition &right ) const
{
  return Time == right.Time;
}

//
// Order operators
//
G4bool nEXOEnergyDeposition::operator<( const nEXOEnergyDeposition &right ) const
{
  return Time < right.Time;
}

G4bool nEXOEnergyDeposition::operator<=( const nEXOEnergyDeposition &right ) const
{
  return Time <= right.Time;
}

