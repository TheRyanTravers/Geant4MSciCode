
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"
#include "FTFP_BERT_HP.hh"
#include "QGSP_BERT_HP.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
int main(int argc,char** argv)
{
    // Choose the Random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    
    // Construct the default run manager
    //
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
#else
    G4RunManager* runManager = new G4RunManager;
#endif
    
    // Set mandatory initialization classes
    //
    // Detector construction
    runManager->SetUserInitialization(new DetectorConstruction());
    
    // Physics list
    G4VModularPhysicsList* physicsList = new QBBC;
    G4VModularPhysicsList* physicsList2 = new FTFP_BERT_HP;
    G4VModularPhysicsList* physicsList3 = new QGSP_BERT_HP;
    
    physicsList->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList);
    physicsList2->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList2);
    physicsList3->SetVerboseLevel(1);
    runManager->SetUserInitialization(physicsList3);
    
    // User action initialization
    runManager->SetUserInitialization(new ActionInitialization());
    
    // Initialize G4 kernel
    runManager->Initialize();
    
    // Define UI terminal for interactive mode
    G4UImanager * UI = G4UImanager::GetUIpointer();
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UI->ApplyCommand(command+fileName);

    delete runManager;
    return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
