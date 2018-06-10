
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

#include "globals.hh"

/// Event action class

class EventAction : public G4UserEventAction
{
private:
    G4double fTotalEnergyDeposit;
    G4double fAzimuthal;
    G4double fPolar;
    G4double fGlobalTime;
    G4String fName;
    G4double fp2;
    
public:
    EventAction();
    virtual ~EventAction();
    
    virtual void  BeginOfEventAction(const G4Event* );
    virtual void    EndOfEventAction(const G4Event* );

    void addEdep(G4double Edep)                 {fTotalEnergyDeposit    += Edep;        };
    void setAzimuthal(G4double azimuthal)       {fAzimuthal             = azimuthal;    };
    void setPolar(G4double polar)               {fPolar                 = polar;        };
    void setGlobalTime(G4double time)           {fGlobalTime            = time;         };
    void setName(G4String name)                 {fName                  = name;         };
    void setp2(G4double p)                      {fp2                    = p;            };
    
    G4double GetEnergyDeposit()                 {return fTotalEnergyDeposit;            };
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
