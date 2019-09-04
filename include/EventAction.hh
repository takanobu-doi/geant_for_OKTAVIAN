
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
  inline void SetFrangePos(G4double x, G4double y) {
    Frangepos[0] = x;
    Frangepos[1] = y;
  }
  inline void SetDetectorPos(G4double x, G4double y) {
    Detectorpos[0] = x;
    Detectorpos[1] = y;
  }
  inline void SetFrangeVec(G4double x, G4double y){
    Frangevec[0] = x;
    Frangevec[1] = y;
  }
  inline void SetDetectorVec(G4double x, G4double y){
    Detectorvec[0] = x;
    Detectorvec[1] = y;
  }
  inline void SetFrangeEnergy(G4double e){
    FrangeE = e;
  }
  inline void SetDetectorEnergy(G4double e){
    DetectorE = e;
  }
  inline void SetFrangeFlag(G4bool flag){
    first_Frangeflag = flag;
  }
  inline void SetDetectorFlag(G4bool flag){
    first_Detectorflag = flag;
  }
  inline G4double GetFrangePos(G4int i){
    return Frangepos[i];
  }
  inline G4double GetDetectorPos(G4int i){
    return Detectorpos[i];
  }
  inline G4double GetFrangeVec(G4int i){
    return Frangevec[i];
  }
  inline G4double GetDetectorVec(G4int i){
    return Detectorvec[i];
  }
  inline G4double GetFrangeEnergy(){
    return FrangeE;
  }
  inline G4double GetDetectorEnergy(){
    return DetectorE;
  }
  inline G4bool GetFrangeFlag(){
    return first_Frangeflag;
  }
  inline G4bool GetDetectorFlag(){
    return first_Detectorflag;
  }

private:
  G4double Frangepos[2];
  G4double Frangevec[2];
  G4double FrangeE;
  G4bool first_Frangeflag;
  G4double Detectorpos[2];
  G4double Detectorvec[2];
  G4double DetectorE;
  G4bool first_Detectorflag;
};

#endif

    
