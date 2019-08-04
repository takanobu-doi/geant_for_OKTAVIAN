#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


RunAction::RunAction()
 : G4UserRunAction()
{ 
// Create analysis manager
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);        // Histo Id starts from 1 not from0
  analysisManager->SetActivation(true);

  // Book histograms, ntuple
  //
  
  // Creating histograms
  G4String Hist_Name = "Position";
  analysisManager->CreateH2(Hist_Name, Hist_Name, 100, -1.*m, 1.*m, 100, -1*m, 1.*m);
  Hist_Name = "Energy";
  analysisManager->CreateH1(Hist_Name, Hist_Name, 100, 0, 15*MeV);
  Hist_Name = "Event_num";
  analysisManager->CreateH1(Hist_Name, Hist_Name, 1, 0, 1);

  // Creating ntuple
}

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    // Get analysis manager and open an output file
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4String fileName = "OKTAVIAN";
  analysisManager->OpenFile(fileName);
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  //save histograms & ntuple
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

