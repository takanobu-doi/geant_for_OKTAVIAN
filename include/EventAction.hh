
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

/// Event action class
///

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();

  virtual void    BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);
  inline void SetPos(G4double x, G4double y) {
    pos[0] = x;
    pos[1] = y;
  }
  inline void SetVec(G4double x, G4double y){
    vec[0] = x;
    vec[1] = y;
  }
  inline void SetEnergy(G4double e){
    E = e;
  }
  inline void SetFlag(G4bool flag){
    first_flag = flag;
  }
  inline G4double GetPos(G4int i){
    return pos[i];
  }
  inline G4double GetVec(G4int i){
    return vec[i];
  }
  inline G4double GetEnergy(){
    return E;
  }
  inline G4bool GetFlag(){
    return first_flag;
  }

private:
  G4double pos[2];
  G4double vec[2];
  G4double E;
  G4bool first_flag;
};

#endif

    
