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
  fScoringVol(0)
{}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
    if (!fScoringVol) {
        const Geometry* geometry
             = static_cast<const Geometry*>
            (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
         fScoringVol = geometry->GetScoringVol();
    }

  // Get PreStepPoint and TouchableHandle objects
    G4StepPoint* preStepPoint = step->GetPreStepPoint();
    G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();
  // 今のステップがある論理物体
    G4LogicalVolume* volume = theTouchable->GetVolume()->GetLogicalVolume();
    G4int copyNo = theTouchable->GetCopyNumber();

//    G4cout << "copy Number = " << copyNo << G4endl;
    
  // スコアする論理物体かどうか
  if (volume != fScoringVol) return;

  // entering position of neutrons
  if(preStepPoint->GetStepStatus()==fGeomBoundary && copyNo==3000){
    G4ThreeVector prePosition = preStepPoint->GetPosition();
    G4ThreeVector postPosition = step->GetPostStepPoint()->GetPosition();
    fEventAction->SetPos(prePosition.x(), prePosition.y());
    fEventAction->SetVec(postPosition.x()-prePosition.x(), postPosition.y()-prePosition.y());
    fEventAction->SetEnergy(preStepPoint->GetKineticEnergy());
    fEventAction->SetFlag(preStepPoint->GetStepStatus()==fGeomBoundary);
  }
}



