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
  G4String fileName = "OKTAVIAN";
  analysisManager->SetFileName(fileName);
  analysisManager->SetActivation(true);

  // Book histograms, ntuple
  //
  
  // Creating histograms
  G4String Hist_Name = "Position";
  analysisManager->CreateH2(Hist_Name, Hist_Name, 100, -10.*cm, 10.*cm, 100, -10*cm, 10.*cm);
  Hist_Name = "Energy";
  analysisManager->CreateH1(Hist_Name, Hist_Name, 150, 0, 15*MeV);

  // Creating ntuple
  analysisManager->CreateNtuple("tree", "X:Y:E:Flag:Evt");
  analysisManager->CreateNtupleDColumn("X");
  analysisManager->CreateNtupleDColumn("Y");
  analysisManager->CreateNtupleDColumn("E");
  analysisManager->CreateNtupleIColumn("Flag");
  analysisManager->CreateNtupleIColumn("Evt");
  analysisManager->FinishNtuple();

  // Creating tree
}

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
    // Get analysis manager and open an output file
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile();
  Evt = 0;
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  //save histograms & ntuple
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}

