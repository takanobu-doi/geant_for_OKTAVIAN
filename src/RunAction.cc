#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include <string>

RunAction::RunAction(G4double Radius, G4int Materi_flag)
  : G4UserRunAction()
{ 
// Create analysis manager
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);        // Histo Id starts from 1 not from0
  G4String fileName = "OKTAVIAN";
  switch(Materi_flag){
  case 0:
    fileName = fileName+"-BoronPolyethy";
    break;
  case 1:
    fileName = fileName;
    break;
  case 2:
    fileName = fileName+"-10mm_Zure";
    break;
  default:
    break;
  }
  
  fileName = fileName+std::to_string((int)(Radius*10));
  analysisManager->SetFileName(fileName);
  analysisManager->SetActivation(true);

  // Book histograms, ntuple
  //
  
  // Creating histograms
  G4String Hist_Name = "Position_Frange";
  analysisManager->CreateH2(Hist_Name, Hist_Name, 100, -10., 10., 100, -10., 10.);
  Hist_Name = "Energy_Frange";
  analysisManager->CreateH1(Hist_Name, Hist_Name, 150, 0, 15);
  Hist_Name = "Position_Detector";
  analysisManager->CreateH2(Hist_Name, Hist_Name, 100, -10., 10., 100, -10., 10.);
  Hist_Name = "Energy_Detector";
  analysisManager->CreateH1(Hist_Name, Hist_Name, 150, 0, 15);

  // Creating ntuple
  analysisManager->CreateNtuple("tree",
				"PX:PY:VX:VY:E:Flag:Evt");
  analysisManager->CreateNtupleDColumn("PX_Frange");
  analysisManager->CreateNtupleDColumn("PY_Frange");
  analysisManager->CreateNtupleDColumn("VX_Frange");
  analysisManager->CreateNtupleDColumn("VY_Frange");
  analysisManager->CreateNtupleDColumn("E_Frange");
  analysisManager->CreateNtupleIColumn("Flag_Frange");
  analysisManager->CreateNtupleDColumn("PX_Detector");
  analysisManager->CreateNtupleDColumn("PY_Detector");
  analysisManager->CreateNtupleDColumn("VX_Detector");
  analysisManager->CreateNtupleDColumn("VY_Detector");
  analysisManager->CreateNtupleDColumn("E_Detector");
  analysisManager->CreateNtupleIColumn("Flag_Detector");
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

