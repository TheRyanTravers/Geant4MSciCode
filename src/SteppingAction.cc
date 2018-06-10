
#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SteppingManager.hh"
#include "G4ios.hh"
#include "G4Gamma.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  G4Track* trajectory(step->GetTrack());
  G4StepPoint* PrePoint = step->GetPreStepPoint();
  
  const G4ParticleDefinition* particle = trajectory->GetParticleDefinition();
  G4double EdepStep = step->GetTotalEnergyDeposit();
  G4String currentVolumeName = PrePoint->GetTouchableHandle()->GetVolume()->GetName();

    
    
  if ( strcmp(currentVolumeName,"Shape2") == 0 || strcmp(currentVolumeName,"Shape2_LV") == 0)
  {
      if (EdepStep > 0.) fEventAction->addEdep(EdepStep);
      
      if (PrePoint->GetStepStatus() == fGeomBoundary)
      {
          fEventAction->setName(particle->GetParticleName());
          G4ThreeVector momentum = trajectory->GetMomentum();
          G4double p2 = momentum[0] * momentum[0] + momentum[1] * momentum[1] + momentum[2] * momentum[2];
          G4double sqrtp2 = std::sqrt(p2);
          G4ThreeVector pHat { momentum[0] / sqrtp2, momentum[1] / sqrtp2, momentum[2] / sqrtp2 };
          
          G4double azimuthal = std::atan2( pHat[1] , pHat[0] );
          G4double polar = std::atan2( std::hypot(pHat[0], pHat[1]) , pHat[2] );
          G4double globalTime = trajectory->GetGlobalTime();
          
          fEventAction->setp2(p2);
          fEventAction->setAzimuthal(azimuthal);
          fEventAction->setPolar(polar);
          fEventAction->setGlobalTime(globalTime);
      }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

