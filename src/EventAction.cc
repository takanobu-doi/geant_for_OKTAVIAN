#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4UserRunAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"

#include "G4UnitsTable.hh"
#include "Analysis.hh"
#include "Randomize.hh"
#include <iomanip>


EventAction::EventAction()
 : G4UserEventAction() 
{}


EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
  first_flag = true;
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if(!first_flag){
    analysisManager->FillH1(1, GetEnergy());
    analysisManager->FillH2(1, GetPos(0), GetPos(1));
    analysisManager->FillNtupleDColumn(0, GetPos(0));
    analysisManager->FillNtupleDColumn(1, GetPos(1));
    analysisManager->FillNtupleDColumn(2, GetEnergy());
    analysisManager->FillNtupleIColumn(3, 1);
  }else{
    analysisManager->FillNtupleDColumn(0, -20);
    analysisManager->FillNtupleDColumn(1, -20);
    analysisManager->FillNtupleDColumn(2, -1);
    analysisManager->FillNtupleIColumn(3, 0);
  }
  analysisManager->FillNtupleIColumn(4, Evt++);
  analysisManager->AddNtupleRow();
}

