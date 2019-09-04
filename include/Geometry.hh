//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geometry.hh
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef Geometry_h
#define Geometry_h 1

#include "G4VUserDetectorConstruction.hh"
class G4VPhysicalVolume;
class G4LogicalVolume;
//enum{noBGO=20};
//------------------------------------------------------------------------------
class Geometry : public G4VUserDetectorConstruction
//------------------------------------------------------------------------------
{
public:
  Geometry(G4double r, G4int materi);
  ~Geometry();
  
  G4VPhysicalVolume* Construct();
  G4LogicalVolume* GetScoringVol_Frange() const { return fScoringVol_Frange; }
  G4LogicalVolume* GetScoringVol_Detector() const { return fScoringVol_Detector; }
protected:
  G4LogicalVolume* fScoringVol_Frange;
  G4LogicalVolume* fScoringVol_Detector;
  G4double Radius;
  G4int Materi_flag;
};
#endif
