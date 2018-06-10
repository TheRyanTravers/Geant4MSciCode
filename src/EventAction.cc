
#include "EventAction.hh"
#include "Analysis.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
:G4UserEventAction(),
 fTotalEnergyDeposit(0.),
 fAzimuthal(0.),
 fPolar(0.),
 fGlobalTime(0.),
 fName(""),
 fp2(0.)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
    fTotalEnergyDeposit = 0.;
    fAzimuthal = 0.;
    fPolar = 0.;
    fGlobalTime = 0.;
    fName = "";
    fp2 = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{
    if ( strcmp( fName , "gamma" ) == 0 || strcmp( fName , "e-" ) == 0 )
    {
        if (fTotalEnergyDeposit > 0.5 && fp2 > 0)
        {
            G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
            analysisManager->FillNtupleDColumn(0, fTotalEnergyDeposit / MeV);
            analysisManager->FillNtupleDColumn(1, fAzimuthal);
            analysisManager->FillNtupleDColumn(2, fPolar);
            analysisManager->FillNtupleDColumn(3, fGlobalTime / ns);
            analysisManager->AddNtupleRow();
        }
    }
    
//    G4cout << "-------------------------------------" << G4endl;
//    G4cout << "Particle Name: " << fName                                       << G4endl;
//    G4cout << "Energy       : " << fTotalEnergyDeposit / MeV   << " MeV"       << G4endl;
//    G4cout << "Azimuthal    : " << fAzimuthal                  << " radians"   << G4endl;
//    G4cout << "Polar        : " << fPolar                      << " radians"   << G4endl;
//    G4cout << "Time         : " << fGlobalTime / ns            << " ns"        << G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


