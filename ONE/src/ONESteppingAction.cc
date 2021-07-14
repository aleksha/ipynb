
#include "ONESteppingAction.hh"
#include "ONEEventAction.hh"
#include "ONEDetectorConstruction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"
//------------------------------------------------------------------------------
ONESteppingAction::ONESteppingAction(ONEEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fLV00(0), fLV01(0)
{
 myOUT .open( "out.data" , std::ios::trunc);
}
//------------------------------------------------------------------------------
ONESteppingAction::~ONESteppingAction(){  myOUT.close(); }
//------------------------------------------------------------------------------
void ONESteppingAction::UserSteppingAction(const G4Step* step)
{
  if ( !fLV00 || !fLV01 ){
    const ONEDetectorConstruction* detectorConstruction
      = static_cast<const ONEDetectorConstruction*>
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    fLV00 = detectorConstruction->GetLV00();
    fLV01 = detectorConstruction->GetLV01();
  }

  // get volume of the current step
  G4LogicalVolume* volume = step->GetPreStepPoint()->GetTouchableHandle()
                                           ->GetVolume()->GetLogicalVolume();


  int vol=-1;
  // check if we are in scoring volume
  if (volume == fLV00) vol=0 ;
  if (volume == fLV01) vol=1 ;

  if ( vol<0 ) return;

  G4Track* trk = step->GetTrack();
  int    ev_id = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID() ;
  int    tr_id = trk->GetTrackID() ;
  G4int p_code = trk->GetDefinition()->GetPDGEncoding();

  int st_id = 0;
  if( step->IsFirstStepInVolume() ){ st_id = 1; }
  if( step->IsLastStepInVolume()  ){ st_id = 2; }
  if( trk->GetKineticEnergy ()==0 ){ st_id = 3; }


  if(st_id>0){
    double tr_ed = step->GetTotalEnergyDeposit() - step->GetNonIonizingEnergyDeposit() ;

    if( myOUT.is_open() && vol==0  && tr_ed>0 )
//       myOUT << ev_id    << " " << tr_id  << " " << st_id  << " " << vol  << " "  << tr_ed  << " " << p_code << G4endl;
       myOUT << ev_id   << " " << tr_ed  << G4endl;

 }
//  // collect energy deposited in this step
//  G4double edepStep = step->GetTotalEnergyDeposit();
//  fEventAction->AddEdep(edepStep);
}
//------------------------------------------------------------------------------

