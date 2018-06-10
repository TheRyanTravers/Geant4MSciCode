
#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    
    G4int nel, natoms;
    G4double density, a, z;
    G4String name;
    
    
    G4NistManager* nist = G4NistManager::Instance();
    // Option to switch on/off checking of volumes overlaps
    //
    G4bool checkOverlaps = true;
    
    G4double env_outer_radius = 20.*cm;
    G4double env_inner_radius = 15.*cm;
    G4Material* env_mat = nist->FindOrBuildMaterial("G4_Galactic");
    
    //
    // World
    //
    G4double worldRadius = 1.2*m;
    G4Material* world_mat = nist->FindOrBuildMaterial("G4_Galactic");
    
    G4Orb* solidWorld =
    new G4Orb("World", worldRadius);
    
    G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
    
    G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
    
    //
    // Envelope
    //
    
    G4Sphere* solidEnv =
    new G4Sphere("Envelope",
                 env_inner_radius,
                 env_outer_radius,
                 0*degree, 360*degree,
                 0*degree, 360*degree);
    
    
    G4LogicalVolume* logicEnv =
    new G4LogicalVolume(solidEnv,            //its solid
                        env_mat,             //its material
                        "Envelope");         //its name
    
    new G4PVPlacement(0,                       //no rotation
                      G4ThreeVector(),         //at (0,0,0)
                      logicEnv,                //its logical volume
                      "Envelope",              //its name
                      logicWorld,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking
    
   
    //
    // Material List
    //
    //
    
    G4Material* el_H = new G4Material(name="Hydrogen", z=1., a=1.00794*g/mole, density=0.0763 *g/cm3);
    G4Material* el_C = new G4Material(name="Carbon", z=6., a=12.0107*g/mole, density=2.267*g/cm3);
    G4Material* el_N = new G4Material(name="Nitrogen", z=7., a=14.0067*g/mole, density=1.027*g/cm3);
    G4Material* el_O = new G4Material(name="Oxygen", z=8., a=15.999*g/mole, density=1.141*g/cm3);
    
    G4Material* CO2 = new G4Material(name="Carbon Dioxide", density = 1.98*mg/cm3, nel=2);
    CO2->AddElement(nist->FindOrBuildElement("C"), natoms=1);
    CO2->AddElement(nist->FindOrBuildElement("O"), natoms=2);
    
    G4Material* TATP = new G4Material(name="TATP", density = 1.2*g/cm3, nel=3);
    TATP->AddElement(nist->FindOrBuildElement("H"), natoms=18);
    TATP->AddElement(nist->FindOrBuildElement("C"), natoms=9);
    TATP->AddElement(nist->FindOrBuildElement("O"), natoms=6);
    
    G4Material* RDX = new G4Material(name="RDX", density = 1.82*g/cm3, nel=4);
    RDX->AddElement(nist->FindOrBuildElement("H"), natoms=6);
    RDX->AddElement(nist->FindOrBuildElement("C"), natoms=3);
    RDX->AddElement(nist->FindOrBuildElement("N"), natoms=6);
    RDX->AddElement(nist->FindOrBuildElement("O"), natoms=6);
    
    G4Material* PETN = new G4Material(name="PETN", density = 1.773*g/cm3, nel=4);
    RDX->AddElement(nist->FindOrBuildElement("H"), natoms=8);
    RDX->AddElement(nist->FindOrBuildElement("C"), natoms=5);
    RDX->AddElement(nist->FindOrBuildElement("N"), natoms=4);
    RDX->AddElement(nist->FindOrBuildElement("O"), natoms=12);
    
    G4Material* styrenebutadiene = new G4Material(name="styrene-butadiene", density = 0.94*g/cm3, nel=2);
    styrenebutadiene->AddElement(nist->FindOrBuildElement("H"), natoms=14);
    styrenebutadiene->AddElement(nist->FindOrBuildElement("C"), natoms=12);
    
    G4Material* noctylphthalate = new G4Material(name="n-octyl-phthalate", density = 0.980*g/cm3, nel=3);
    noctylphthalate->AddElement(nist->FindOrBuildElement("H"), natoms=22);
    noctylphthalate->AddElement(nist->FindOrBuildElement("C"), natoms=16);
    noctylphthalate->AddElement(nist->FindOrBuildElement("O"), natoms=4);
    
    G4Material* tribulatecitrate = new G4Material(name="tribulate-citrate", density = 1.05*g/cm3, nel=3);
    tribulatecitrate->AddElement(nist->FindOrBuildElement("H"), natoms=32);
    tribulatecitrate->AddElement(nist->FindOrBuildElement("C"), natoms=18);
    tribulatecitrate->AddElement(nist->FindOrBuildElement("O"), natoms=7);

    G4Material* nphenyl2naphthylamine = new G4Material(name="n-phenyl-2-naphthylamine", density = 1.24*g/cm3, nel=3);
    nphenyl2naphthylamine->AddElement(nist->FindOrBuildElement("H"), natoms=13);
    nphenyl2naphthylamine->AddElement(nist->FindOrBuildElement("C"), natoms=16);
    nphenyl2naphthylamine->AddElement(nist->FindOrBuildElement("O"), natoms=1);
    
    G4Material* SudanI = new G4Material(name="Sudan-I", density = 1.75*g/cm3, nel=4);
    SudanI->AddElement(nist->FindOrBuildElement("H"), natoms=12);
    SudanI->AddElement(nist->FindOrBuildElement("C"), natoms=16);
    SudanI->AddElement(nist->FindOrBuildElement("N"), natoms=2);
    SudanI->AddElement(nist->FindOrBuildElement("O"), natoms=1);
    
    G4Material* SudanIV = new G4Material(name="Sudan-IV", density = 1.75*g/cm3, nel=4);
    SudanIV->AddElement(nist->FindOrBuildElement("H"), natoms=20);
    SudanIV->AddElement(nist->FindOrBuildElement("C"), natoms=24);
    SudanIV->AddElement(nist->FindOrBuildElement("N"), natoms=4);
    SudanIV->AddElement(nist->FindOrBuildElement("O"), natoms=1);
    
    G4Material* Semtex1A = new G4Material(name="Semtex-1A", density = 1.42*g/cm3, nel=4);
    Semtex1A->AddMaterial(PETN, fractionmass=76.0*perCent);
    Semtex1A->AddMaterial(RDX, fractionmass=4.6*perCent);
    Semtex1A->AddMaterial(styrenebutadiene, fractionmass= 9.4*perCent);
    // The two that follow should have a total fraction of 9.0% but in what mix I'm not so sure
    Semtex1A->AddMaterial(noctylphthalate, fractionmass=9.0*perCent);
    Semtex1A->AddMaterial(tribulatecitrate, fractionmass= 0.0*perCent);
    
    // Choosing which material we want to be interrogated
    G4Material* shape1_mat = TATP;
    
    //
    // Shape 1
    //
    //
    
    G4ThreeVector pos1 = G4ThreeVector(0, 0, 0);
    
    // Orb shape
    G4double shape1Radius = 10.*cm;
    G4Orb* solidShape1 =
    new G4Orb("Shape1", shape1Radius);
    
    G4LogicalVolume* logicShape1 =
    new G4LogicalVolume(solidShape1,         //its solid
                        shape1_mat,          //its material
                        "Shape1");           //its name
    
    new G4PVPlacement(0,                       //no rotation
                      pos1,                    //at position
                      logicShape1,             //its logical volume
                      "Shape1",                //its name
                      logicWorld,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking
    
    //
    // Detector Materials
    //
    
    G4Material* PVT = new G4Material(name="Polyvinyl Toluene", density = 1.03*g/cm3, nel=2);
    PVT->AddElement(nist->FindOrBuildElement("C"), natoms=9);
    PVT->AddElement(nist->FindOrBuildElement("H"), natoms=10);
    
    G4Material* NaI = new G4Material(name="Sodium Iodide", density = 3.67*g/cm3, nel=2);
    NaI->AddElement(nist->FindOrBuildElement("Na"), natoms=1);
    NaI->AddElement(nist->FindOrBuildElement("I"), natoms=1);
    
    G4Material* BGO = new G4Material(name="Bismuth Germanate", density = 7.13*g/cm3, nel=3);
    BGO->AddElement(nist->FindOrBuildElement("Bi"), natoms=4);
    BGO->AddElement(nist->FindOrBuildElement("Ge"), natoms=3);
    BGO->AddElement(nist->FindOrBuildElement("O"), natoms=12);
    
    //
    // Shape 2 (PVT and NaI crystal detector)
    //
    
    G4Material* shape2_mat = BGO;
    
    G4ThreeVector pos2 = G4ThreeVector(0, 0, 0);
    
    // Spherical Shell
    G4double detector_inner_radius = 75.0*cm;
    G4double detector_outer_radius = 77.5*cm;
    
    G4Sphere* solidShape2 =
    new G4Sphere("Shape2",
                 detector_inner_radius,
                 detector_outer_radius,
                 0*degree, 360*degree,
                 0*degree, 360*degree);
    
    
    G4LogicalVolume* logicShape2 =
    new G4LogicalVolume(solidShape2,         //its solid
                        shape2_mat,          //its material
                        "Shape2_LV");        //its name
    
    new G4PVPlacement(0,                       //no rotation
                      pos2,                    //at position
                      logicShape2,             //its logical volume
                      "Shape2",                //its name
                      logicWorld,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking
    
    //
    // Shape 3 (Aluminium conversion layer)
    //
    G4Material* el_Al = new G4Material(name="Aluminium", z=13., a=26.981538*g/mole, density=2.7*g/cm3);
    G4Material* shape3_mat = el_Al;
    
    G4ThreeVector pos3 = G4ThreeVector(0, 0, 0);
    
    // Spherical Shell
    G4double conversion_inner_radius = 75.0*cm - 100 * um; //thickness of conversion layer
    G4double conversion_outer_radius = 75.0*cm;
    
    G4Sphere* solidShape3 =
    new G4Sphere("Shape3",
                 conversion_inner_radius,
                 conversion_outer_radius,
                 0*degree, 360*degree,
                 0*degree, 360*degree);
    
    
    G4LogicalVolume* logicShape3 =
    new G4LogicalVolume(solidShape3,         //its solid
                        shape3_mat,          //its material
                        "Shape3_LV");        //its name
    
    new G4PVPlacement(0,                       //no rotation
                      pos3,                    //at position
                      logicShape3,             //its logical volume
                      "Shape3",                //its name
                      logicWorld,              //its mother  volume
                      false,                   //no boolean operation
                      0,                       //copy number
                      checkOverlaps);          //overlaps checking
    
    //
    //always return the physical World
    //
    return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
