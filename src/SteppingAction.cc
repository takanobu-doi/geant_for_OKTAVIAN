#include "SteppingAction.hh"
#include "EventAction.hh"
#include "Geometry.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"


SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVol_Frange(0),
  fScoringVol_Detector(0)
{
}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
    if (!fScoringVol_Frange && !fScoringVol_Detector) {
      const Geometry* geometry
	= static_cast<const Geometry*>
	(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
      fScoringVol_Frange = geometry->GetScoringVol_Frange();
      fScoringVol_Detector = geometry->GetScoringVol_Detector();
    }

  // Get PreStepPoint and TouchableHandle objects
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();
  // 今のステップがある論理物体
    G4LogicalVolume* volume = theTouchable->GetVolume()->GetLogicalVolume();
    G4int copyNo = theTouchable->GetCopyNumber();

//    G4cout << "copy Number = " << copyNo << G4endl;
    
  // スコアする論理物体かどうか
  if (volume != fScoringVol_Frange && volume != fScoringVol_Detector) return;

  // entering position of neutrons
  if(preStepPoint->GetStepStatus()==fGeomBoundary){
    if(copyNo==2000){
      G4ThreeVector prePosition = preStepPoint->GetPosition();
      G4ThreeVector postPosition = step->GetPostStepPoint()->GetPosition();
      fEventAction->SetFrangePos(prePosition.x(), prePosition.y());
      fEventAction->SetFrangeVec(postPosition.x()-prePosition.x(), postPosition.y()-prePosition.y());
      fEventAction->SetFrangeEnergy(preStepPoint->GetKineticEnergy());
      fEventAction->SetFrangeFlag(preStepPoint->GetStepStatus()==fGeomBoundary);
    }
    if(copyNo==3000){
      G4ThreeVector prePosition = preStepPoint->GetPosition();
      G4ThreeVector postPosition = step->GetPostStepPoint()->GetPosition();
      fEventAction->SetDetectorPos(prePosition.x(), prePosition.y());
      fEventAction->SetDetectorVec(postPosition.x()-prePosition.x(), postPosition.y()-prePosition.y());
      fEventAction->SetDetectorEnergy(preStepPoint->GetKineticEnergy());
      fEventAction->SetDetectorFlag(preStepPoint->GetStepStatus()==fGeomBoundary);
    }
  }
}



