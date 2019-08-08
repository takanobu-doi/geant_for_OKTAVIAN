//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UserActionInitialization.hh
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifndef UserActionInitialization_h
#define UserActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"

//------------------------------------------------------------------------------
class UserActionInitialization : public G4VUserActionInitialization
//------------------------------------------------------------------------------
{
public:
  UserActionInitialization(G4double r,G4int flag);
  virtual ~UserActionInitialization();
  
  virtual void Build() const;
private:
  G4double Radius;
  G4int Materi_flag;
};
#endif



