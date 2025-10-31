#include "PMDetectorConstruction.hh"

PMDetectorConstruction::PMDetectorConstruction()
{
}

PMDetectorConstruction::~PMDetectorConstruction()
{   
}

G4VPhysicalVolume *PMDetectorConstruction::Construct()
{
    G4bool checkOverlaps = true;
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();

    // World
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");

    double xWorld = 1. * m;
    double yWorld = 1. * m;
    double zWorld = 1. * m;

    G4Box *solidworld = new G4Box("solidworld", xWorld * 0.5, yWorld * 0.5, zWorld * 0.5);
    G4LogicalVolume *logicalWorld = new G4LogicalVolume(solidworld, worldMat, "logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalWorld, "physworld", 0, false, 0, checkOverlaps);

    return physWorld;

}