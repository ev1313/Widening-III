#strict


// MSC-Script //

private FlyProcess:
  // Clonks zum Stechen suchen
  if (Not(Random(3)))
    if (SetVar(0,FindObject( 0, +1,0,0,0, OCF_Prey(), 0,0, NoContainer() )))
      Sting(Var(0));
  return(1);

protected Activity: // TimerCall
  // Nix machen
  if (Random(2)) return(1);
  // Nur beim Fliegen
  if (Not( SEqual(GetAction(),"Fly") )) return(1);
  // Verschüttet: sterben
  if (GBackSolid()) return(Death());
  // Einfach so sterben
  if (Not(Random(50))) return(Death());
  // Richtung ändern
  if (Not(Random(2))) SetComDir(Sum(Random(9),+1));
  // Verfolgung aufgeben
  if (Not(Random(2))) SetCommand(this(),"None");
  // Neues Ziel verfolgen
  if (Not(Random(10)))
    if (SetVar(0, FindObject(0, 0,0,-1,-1, OCF_Prey(), 0,0, NoContainer()) ))
      SetCommand(this(),"Follow",Var(0));
  // Fertich
  return(1);
  
private Sting:
  Punch(Par(0),Sum(2,Random(5)));
  return(1);

protected Initialize:
  SetAction("Fly");
  SetComDir(Sum(Random(5),+1));
  return(1);

protected Death:
  RemoveObject();
  return(1);

