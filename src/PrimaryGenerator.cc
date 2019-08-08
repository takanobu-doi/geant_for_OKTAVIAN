//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PrimaryGenerator.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "PrimaryGenerator.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//------------------------------------------------------------------------------
  PrimaryGenerator::PrimaryGenerator()
  : fpParticleGun(0) 
//------------------------------------------------------------------------------
{
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  fpParticleGun = new G4ParticleGun();

  G4String particleName = "neutron";
  G4ParticleDefinition* particle = particleTable->FindParticle(particleName);
  G4double particleEnergy = 14.0*MeV;

  fpParticleGun->SetParticleDefinition(particle);
  fpParticleGun->SetParticleEnergy(particleEnergy);
}

//------------------------------------------------------------------------------
  PrimaryGenerator::~PrimaryGenerator()
//------------------------------------------------------------------------------
{
  delete fpParticleGun;
}

//------------------------------------------------------------------------------
  void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
//------------------------------------------------------------------------------
{
  G4double pos_x = 0.;
  G4double pos_y = 0.;
  G4double pos_z = -3.*m;
  G4ThreeVector position = G4ThreeVector(pos_x, pos_y, pos_z);
  G4double theta = -atan(5.5*cm/(pos_z+0.5*m))*rad*G4UniformRand();
  G4double phi = 360.*deg*G4UniformRand();
  G4ThreeVector direction = G4ThreeVector(0., 0., 1.).rotateY(theta);
  direction = direction.rotateZ(phi);
  fpParticleGun->SetParticleMomentumDirection(direction);  fpParticleGun->SetParticlePosition(position);
  fpParticleGun->GeneratePrimaryVertex(anEvent);
}

