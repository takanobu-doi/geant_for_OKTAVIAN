
#include "EventAction.hh"

#include "G4RunManager.hh"
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
    analysisManager->FillH2(1, GetPos(0), GetPos(1));
    analysisManager->FillH1(1, GetEnergy());
  }
  analysisManager->FillH1(2, 0.5);
}

