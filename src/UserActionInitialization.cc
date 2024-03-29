//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// UserActionInitialization.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "UserActionInitialization.hh"
#include "PrimaryGenerator.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "RunAction.hh"

//------------------------------------------------------------------------------
UserActionInitialization::UserActionInitialization(G4double r,G4int flag)
  : G4VUserActionInitialization(),Radius(r),Materi_flag(flag)
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
UserActionInitialization::~UserActionInitialization()
//------------------------------------------------------------------------------
{}

  
// RunAction  ヒストグラムの準備と書き出し用ファイルの操作
// SteppingAction BGO中にステップがあればエネルギー付与を求める
// EventAction　エネルギー付与の和を求めヒストをFillする
//------------------------------------------------------------------------------
void UserActionInitialization::Build() const
//------------------------------------------------------------------------------
{
    EventAction* eventaction = new EventAction();
    SetUserAction( new PrimaryGenerator() );
    SetUserAction(eventaction);
    SetUserAction( new SteppingAction(eventaction) );
    SetUserAction(new RunAction(Radius,Materi_flag));
}




