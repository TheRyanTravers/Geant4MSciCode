
#include "RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

#include <stdio.h>
#include <time.h>

#include <Randomize.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
: G4UserRunAction()
{
    // set printing event number per each 1000 events
    G4RunManager::GetRunManager()->SetPrintProgress(1000);
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(1);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
    long seeds[2];
    time_t systime = time(NULL);
    seeds[0] = (long) systime;
    seeds[1] = (long) (systime * G4UniformRand());
    G4Random::setTheSeeds(seeds);
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // Open an output file
    //
    G4String fileName = "NADetector";
    analysisManager->OpenFile(fileName);
    
    analysisManager->CreateNtuple("NA", "Energy, Azimuthal, Polar and Time");
    analysisManager->CreateNtupleDColumn("Energy");
    analysisManager->CreateNtupleDColumn("Azimuthal");
    analysisManager->CreateNtupleDColumn("Polar");
    analysisManager->CreateNtupleDColumn("Time");
    analysisManager->FinishNtuple();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* )
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    analysisManager->Write();
    analysisManager->CloseFile();
    
    int timeNow = static_cast<int>(time(NULL));
    G4cout << "Total time elapsed: " << timeNow - timeStart << " s" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
