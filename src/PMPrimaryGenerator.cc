#include "PMPrimaryGenerator.hh"

PMPrimaryGenerator::PMPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
    
    //Particle position
    G4double x = 0. * m;
    G4double y = 0. * m;
    G4double z = 0. * m; 
    
    G4ThreeVector pos(x, y, z);

    //particle direction
    G4double px = 0. * m;
    G4double py = 0. * m;
    G4double pz = 0. * m; 

    G4ThreeVector  mom(px, py, pz);

    //particle type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("e+");

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(1. * GeV);
    fParticleGun->SetParticleDefinition(particle);  
    fParticleGun->SetParticleEnergy(1. * GeV);
    fParticleGun->SetParticleDefinition(particle);    

}

PMPrimaryGenerator::~PMPrimaryGenerator()
{
    delete fParticleGun;
}

void PMPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
}