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
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material* leadMat = nist->FindOrBuildMaterial("G4_Pb");
    G4Material* detMat = nist->FindOrBuildMaterial("G4_SODIUM_IODIDE");

    G4double xWorld = 1. * m;
    G4double yWorld = 1. * m;
    G4double zWorld = 1. * m;

    G4Box *solidworld = new G4Box("solidworld", xWorld * 0.5, yWorld * 0.5, zWorld * 0.5);
    G4LogicalVolume *logicalWorld = new G4LogicalVolume(solidworld, worldMat, "logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalWorld, "physworld", 0, false, 0, checkOverlaps);

    G4double leadThickness = 2. * mm;
    G4double leadSize = 10. * cm;
    G4Box *solidLead = new G4Box("SolidLead", leadSize * 0.5, leadSize * 0.5, leadThickness * 0.5);
    G4LogicalVolume *logicLead = new G4LogicalVolume(solidLead, leadMat, "logicalLead");
    G4VPhysicalVolume *physLead = new G4PVPlacement(0, G4ThreeVector(0, 0, 5. * cm), logicLead, "physLead", logicalWorld, false, checkOverlaps );

    G4VisAttributes *leadVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5)); 
    leadVisAtt->SetForceSolid(true);
    logicLead->SetVisAttributes(leadVisAtt);

    G4double detectorSize = 5.0 * cm;
    G4Box *solidDetector = new G4Box("SolidDetector", detectorSize * 0.5, detectorSize * 0.5, detectorSize * 0.5);

    LogicDetector = new G4LogicalVolume(solidDetector, detMat, "logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., 10.5 * cm), LogicDetector, "physDetector", logicalWorld, false, checkOverlaps);
    G4VisAttributes *detectorVisAtt = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 0.3));
    detectorVisAtt->SetForceSolid(true);
    LogicDetector->SetVisAttributes(detectorVisAtt);

    return physWorld;
    
}

void PMDetectorConstruction::ConstructSDandField()
{
    PMSensitiveDetector *sensDetector = new PMSensitiveDetector("SensitiveDetector");
    LogicDetector->SetSensitiveDetector(sensDetector);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDetector);
}