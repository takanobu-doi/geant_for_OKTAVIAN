//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geant4 Application: Tutorial course for Hep/Space Users: 2015.08.24 @Hiroshima
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "UserActionInitialization.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BIC.hh"
#include <iostream>

//-------------------------------------------------------------------------------
int main( int argc, char** argv )
//-------------------------------------------------------------------------------
{
  if(argc<3){
    return 1;
  }
   // ============= [ Setting up the application environment ] ================
   typedef  QGSP_BIC PhysicsList;                   // Physics List
   G4String nameMainMacro = "GlobalSetup.mac";      // Initialization  macros
   G4String nameGeneratorMacro = "primaryGeneratorSetup.mac";
   G4String nameVerboseMacro = "verboseSetup.mac";
   G4String nameVisMacro = "visSetup_Simplex.mac";
   G4String eventNumber = argv[1];
   // =========================================================================

// Construct the default run manager
   G4RunManager * runManager = new G4RunManager;

// Set up mandatory user initialization: Geometry
   runManager->SetUserInitialization( new Geometry(atof(argv[2])) );

// Set up mandatory user initialization: Physics-List
   runManager->SetUserInitialization( new PhysicsList );

// Set up user initialization: User Actions
   runManager->SetUserInitialization( new UserActionInitialization() );

// Initialize G4 kernel
   runManager->Initialize();

// Create visualization environment
   G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();

// Start interactive session
   G4UImanager*   uiManager = G4UImanager::GetUIpointer();
   G4UIExecutive* ui = new G4UIExecutive(argc, argv);
//   uiManager->ApplyCommand("/control/execute " + nameMainMacro);
//   uiManager->ApplyCommand("/control/execute " + nameGeneratorMacro);
//   uiManager->ApplyCommand("/control/execute " + nameVerboseMacro);
//   uiManager->ApplyCommand("/control/execute " + nameVisMacro);
   uiManager->ApplyCommand("/run/beamOn " + eventNumber);
   
//   ui->SessionStart();

// Job termination
   delete ui;
   delete visManager;
   delete runManager;

   return 0;
}
