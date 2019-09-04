//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geometry.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"

#include "G4SDManager.hh"
#include <iostream>

/* use for MultiFumctionalDetector and PrimitiveScorer 使わ無い
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
//#include "G4PSTrackLength.hh"
//#include "G4SDChargedFilter.hh"
*/

//------------------------------------------------------------------------------
Geometry::Geometry(G4double r, G4int materi)
  : G4VUserDetectorConstruction(),
    Radius(r),
    Materi_flag(materi),
    fScoringVol_Frange(0),
    fScoringVol_Detector(0)
{
}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
Geometry::~Geometry() {}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
G4VPhysicalVolume* Geometry::Construct()
//------------------------------------------------------------------------------
{
// Get pointer to 'Material Manager'
   G4NistManager* materi_Man = G4NistManager::Instance();

// Define 'World Volume'
   // Define the shape of solid
   G4double leng_X_World = 4.0*m;         // X-full-length of world 
   G4double leng_Y_World = 4.0*m;         // Y-full-length of world 
   G4double leng_Z_World = 4.0*m;         // Z-full-length of world 
   G4Box* solid_World = 
     new G4Box("Solid_World", leng_X_World/2., leng_Y_World/2., leng_Z_World/2.);

   // Define logical volume
   G4Material* materi_World = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_World = 
     new G4LogicalVolume(solid_World, materi_World, "LogVol_World");
   logVol_World->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of logical volume
   G4int copyNum_World = 0;               // Set ID number of world
   G4PVPlacement* physVol_World  = 
     new G4PVPlacement(G4Transform3D(), "PhysVol_World", logVol_World, 0, 
                       false, copyNum_World);

// Define 'Polyethylene colimetor'
   // Define the shape of solid
   G4double radius_Out = 5.5*cm;
   G4double leng_Z_Out = 1.0*m;
   G4double radius_In = Radius*cm;
   G4double leng_Z_In = leng_Z_Out;
   G4Tubs* solid_Out = new G4Tubs("Solid_Out", 0., radius_Out, leng_Z_Out/2., 0., 360.*deg);
   G4Tubs* solid_In = new G4Tubs("Solid_In", 0., radius_In, leng_Z_In/2., 0., 360.*deg);
   G4SubtractionSolid* solid_Poly = new G4SubtractionSolid("Solid_Poly", solid_Out, solid_In, 0, G4ThreeVector(0, 0, 0));
   // Define logical volume
   G4Material* materi_Poly = materi_Man->FindOrBuildMaterial("G4_POLYETHYLENE");
   G4Material* materi_B2O3 = materi_Man->FindOrBuildMaterial("G4_BORON_OXIDE");
   G4Material* materi_Mix = new G4Material("Mix", 942*kg/m3, 2);
   materi_Mix->AddMaterial(materi_Poly, 90*perCent);
   materi_Mix->AddMaterial(materi_B2O3, 10*perCent);
   G4LogicalVolume* logVol_Poly = 0;
   
   if(Materi_flag==0){ // with B2O3
     logVol_Poly = 
       new G4LogicalVolume(solid_Poly, materi_Mix, "LogVol_Poly");
   }else if(Materi_flag==1){ // without B2O3
     logVol_Poly = 
       new G4LogicalVolume(solid_Poly, materi_Poly, "LogVol_Poly");
   }else if(Materi_flag==2){ // without B2O3
     logVol_Poly = 
       new G4LogicalVolume(solid_Poly, materi_Poly, "LogVol_Poly");
   }
   
//   G4LogicalVolume* logVol_Out =
//     new G4LogicalVolume(solid_Out, materi_Poly, "LogVol_Poly");
//   G4Material* materi_Air = materi_Man->FindOrBuildMaterial("G4_AIR");
//   G4LogicalVolume* logVol_In =
//     new G4LogicalVolume(solid_In, materi_Air, "LogVol_Air");

// Define 'Wall'
   // Define the shape of solid
   G4double leng_X_Wall = 2.*m;
   G4double leng_Y_Wall = 2.*m;
   G4double leng_Z_Wall = 1.*m;
   G4Box* solid_Plate = new G4Box("Solid_Plate", leng_X_Wall/2., leng_Y_Wall/2., leng_Z_Wall/2.);
   G4double radius_Hall = 5.5*cm;
   G4double leng_Z_Hall = 1.0*m;
   G4Tubs* solid_Hall = new G4Tubs("Solid_Hall", 0., radius_Hall, leng_Z_Hall/2., 0., 360.*deg);
   G4SubtractionSolid* solid_Wall = new G4SubtractionSolid("Solid_Wall", solid_Plate, solid_Hall);
   //Define logical volume
   G4Material* materi_Wall = materi_Man->FindOrBuildMaterial("G4_CONCRETE");
   G4LogicalVolume* logVol_Wall =
     new G4LogicalVolume(solid_Wall, materi_Wall, "LogVol_Wall");
//   G4LogicalVolume* logVol_Wall =
//     new G4LogicalVolume(solid_Plate, materi_Wall, "LogVol_Wall");

// Define 'Frange'
   // Define the shape of  solid
   G4double leng_Z_Frange = 20*mm;
   G4double radius_Frange = 55*mm;
   G4Tubs* solid_Frange = new G4Tubs("Solid_Frange", 0., radius_Frange, leng_Z_Frange/2., 0., 360.*deg);
   // Define logical volume
   G4Material* materi_Frange = new G4Material("Acrylic", 1.19*g/cm3, 3);
   G4Element* elH = new G4Element("Hydrogen", "H", 1., 1.01*g/mole);
   G4Element* elC = new G4Element("Carbon", "C", 6., 12.01*g/mole);
   G4Element* elO = new G4Element("Oxygen", "O", 8., 16.00*g/mole);
   materi_Frange->AddElement(elC, 5);
   materi_Frange->AddElement(elH, 8);
   materi_Frange->AddElement(elO, 2);
   G4LogicalVolume* logVol_Frange =
     new G4LogicalVolume(solid_Frange, materi_Frange, "LogVol_Wall");

// Define 'Detector'   
   // Define the shape of solid
   G4double leng_X_Detector = 10.*cm;
   G4double leng_Y_Detector = 15.*cm;
   G4double leng_Z_Detector = 10.*cm;
   G4Box* solid_Detector = new G4Box("Solid_Detector", leng_X_Detector/2., leng_Y_Detector/2., leng_Z_Detector/2.);
   G4Material* materi_Detector = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_Detector =
     new G4LogicalVolume(solid_Detector, materi_Detector, "LogVol_Detector");
   
// define my sensitive volume BGO論理物体を有感としてSteppingActionでチェックする
   fScoringVol_Frange = logVol_Frange;
   fScoringVol_Detector = logVol_Detector;


// Placement of logical volume
   // Set polyethylene
   G4double pos_X_LogV = 0.0*cm;           // X-location LogV
   G4double pos_Y_LogV = 0.0*cm;           // Y-location LogV
   G4double pos_Z_LogV = 0.0*cm;           // Z-location LogV
   G4ThreeVector threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();
   G4Transform3D trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   G4int copyNum_LogV = 1000;                // Set ID number of LogV
   // Set Wall
   new G4PVPlacement(trans3D_LogV, "PhysVol_Wall", logVol_Wall, physVol_World,
		     false, copyNum_LogV);
   copyNum_LogV = 1001;
   new G4PVPlacement(trans3D_LogV, "PhysVol_Poly", logVol_Poly, physVol_World,
		       false, copyNum_LogV);
//   copyNum_LogV = 1002;
//   G4PVPlacement* physVol_Air =
//     new G4PVPlacement(trans3D_LogV, "PhysVol_Air", logVol_In, physVol_Poly,
//		       false, copyNum_LogV);
   // Set Frange
   pos_X_LogV = 0.0*cm;
   pos_Y_LogV = 0.0*cm;
   pos_Z_LogV = leng_Z_Wall/2.+leng_Z_Frange/2.;
   threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   copyNum_LogV = 2000;
   new G4PVPlacement(trans3D_LogV, "PhysVol_Frange", logVol_Frange, physVol_World,
		     false, copyNum_LogV);
   // Set Detector
   pos_X_LogV = 0.0*cm;
   pos_Y_LogV = 0.0*cm;
   pos_Z_LogV = leng_Z_Wall/2.+leng_Z_Frange+leng_Z_Detector/2.;
   threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   copyNum_LogV = 3000;
   new G4PVPlacement(trans3D_LogV, "PhysVol_Detector", logVol_Detector, physVol_World,
		     false, copyNum_LogV);

   G4cout << *(G4Material::GetMaterialTable()) << G4endl;
// Return the physical world
   return physVol_World;
}
