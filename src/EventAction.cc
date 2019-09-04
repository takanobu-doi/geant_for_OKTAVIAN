#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4UserRunAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"

#include "G4UnitsTable.hh"
#include "Analysis.hh"
#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include <iomanip>


EventAction::EventAction()
 : G4UserEventAction() 
{}


EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  SetFrangePos(10000, 10000);
  SetFrangeVec(10000, 10000);
  SetFrangeEnergy(-1);
  SetFrangeFlag(false);
  SetDetectorPos(10000, 10000);
  SetDetectorVec(10000, 10000);
  SetDetectorEnergy(-1);
  SetDetectorFlag(false);
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(1, GetFrangeEnergy()/MeV);
  analysisManager->FillH2(1, GetFrangePos(0)/cm, GetFrangePos(1)/cm);
  analysisManager->FillNtupleDColumn(0, GetFrangePos(0)/cm);
  analysisManager->FillNtupleDColumn(1, GetFrangePos(1)/cm);
  analysisManager->FillNtupleDColumn(2, GetFrangeVec(0));
  analysisManager->FillNtupleDColumn(3, GetFrangeVec(1));
  analysisManager->FillNtupleDColumn(4, GetFrangeEnergy()/MeV);
  analysisManager->FillNtupleIColumn(5, GetFrangeFlag());
  analysisManager->FillH1(2, GetDetectorEnergy()/MeV);
  analysisManager->FillH2(2, GetDetectorPos(0)/cm, GetDetectorPos(1)/cm);
  analysisManager->FillNtupleDColumn(6, GetDetectorPos(0)/cm);
  analysisManager->FillNtupleDColumn(7, GetDetectorPos(1)/cm);
  analysisManager->FillNtupleDColumn(8, GetDetectorVec(0));
  analysisManager->FillNtupleDColumn(9, GetDetectorVec(1));
  analysisManager->FillNtupleDColumn(10, GetDetectorEnergy()/MeV);
  analysisManager->FillNtupleIColumn(11, GetDetectorFlag());
  analysisManager->FillNtupleIColumn(12, Evt++);
  analysisManager->AddNtupleRow();
}

