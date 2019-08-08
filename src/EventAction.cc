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
  SetPos(10000, 10000);
  SetVec(10000, 10000);
  SetEnergy(-1);
  SetFlag(false);
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(1, GetEnergy()/MeV);
  analysisManager->FillH2(1, GetPos(0)/cm, GetPos(1)/cm);
  analysisManager->FillNtupleDColumn(0, GetPos(0)/cm);
  analysisManager->FillNtupleDColumn(1, GetPos(1)/cm);
  analysisManager->FillNtupleDColumn(2, GetVec(0));
  analysisManager->FillNtupleDColumn(3, GetVec(1));
  analysisManager->FillNtupleDColumn(4, GetEnergy()/MeV);
  analysisManager->FillNtupleIColumn(5, GetFlag());
  analysisManager->FillNtupleIColumn(6, Evt++);
  analysisManager->AddNtupleRow();
}

