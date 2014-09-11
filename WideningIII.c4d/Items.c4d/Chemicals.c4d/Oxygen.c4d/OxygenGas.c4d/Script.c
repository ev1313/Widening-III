/*-- Wasserstoff --*/

#strict

local target;


protected func Initialize()
{
 //Ein wenig Schummeln...
 SetPosition(GetX(),GetY()+15);
 //Wasserstoff: fast durchsichtig. fast.
 SetClrModulation(RGBa(210,210,210,200));
 // Zufälliges Aussehen
 SetAction(Format("%d",(Random(14)+1) ));
}

private func FlyProcess() { 
  var xdir,ydir;

  xdir=Random(13)-6;
  ydir=Random(9)-4;

  //xdir+=BoundBy((GetX(target)-GetX()),-15,15);
  //ydir+=BoundBy((GetY(target)-GetY())/5,-9,9);

  if(GBackLiquid(xdir,ydir)) return(SetSpeed());
  SetSpeed(xdir,ydir);
}

protected func Activity() {

  //Reaktion auf Lebewesen und Feuer
  var obj;
  //CrewMember ist auch bei allen Tieren gesetzt daher...
  if(obj=FindObject(0,-10,-10,20,20,OCF_CrewMember(),0,0,NoContainer())) Sting(obj);
  if(FindObject(0,-20,-20,40,40,OCF_OnFire(),0,0,NoContainer())) Damage();

  if(!Random(20)) return(Death());
}
  
private func Sting(obj) {
  Punch(obj,1+Random(1));
}

public func FindTarget(maxdist) {  
  var obj;
  if(obj=FindObject(0,0,0,-1,-1,OCF_Prey(),0,0,NoContainer()))
    if(ObjectDistance(obj)<maxdist)
      if(!GBackSemiSolid(GetX(obj)-GetX(),GetY(obj)-GetY()))
        return(obj);
}

//Explosionseigenschaften

func Death() { RemoveObject(); }

func Damage()
{
 return(CastObjects(DFLM,2,15));
}