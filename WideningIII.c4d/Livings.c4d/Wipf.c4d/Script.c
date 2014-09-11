// MSC-Script //

#strict

/* Initialisierung */

protected Initialize:
  SetAction("Walk");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);

/* TimerCall */

protected Activity: 
  // Nix machen
  if (Random(2)) return(1);
  // Bisschen herumhampeln
  if (Not(Or( SEqual(GetAction(),"Walk"),SEqual(GetAction(),"Swim") ))) return(1);
  // Lärm machen
  if (Not(Random(15))) Sound("Snuff*");
  // Die Sache mit den Bienchen und Blümchen...
  if (Not(Random(750))) Reproduction();
  // ´Rumhüpfen
  if (SEqual(GetAction(),"Walk"))
    if (Not(Random(3))) return(DoJump());
  // Irgendwo hinpflanzen und dämlich glotzen
  if (SEqual(GetAction(),"Walk"))
    if (Not(Random(3))) return(SitDown());
  // Sich nicht entscheiden können, ob links oder rechts lang laufen
  if (Random(2)) return(TurnRight());
  return(TurnLeft());

/* Kontakt */

protected ContactLeft:
  return(TurnRight());
  
protected ContactRight:
  return(TurnLeft());

/* Bewegungssteuerung */

private Sitting:
  // Und weiter geht´s
  if (Not(Random(10))) SetAction("Walk");
  return(1);

private TurnRight:
  if (Stuck()) return(0);
  if (Not(Equal(GetDir(),DIR_Right()))) if (Not(SetAction("Turn"))) return(0);
  SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right()); 
  return(1);

private TurnLeft:
  if (Stuck()) return(0);
  if (Not(Equal(GetDir(),DIR_Left()))) if (Not(SetAction("Turn"))) return (0);
  SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left()); 
  return(1);

private DoJump:
  Jump();
  return(1);

private SitDown:
  SetAction("Sit");
  SetDir(0);
  return(1);


/* Einwirkungen */

protected CatchBlow:
  if (SEqual(GetAction(),"Dead")) return(0);
  if (Not(Random(3))) Sound("WipfHurt");
  return(1);

protected Death:
  // Das hasste davon, Harharhar!
  Sound("WipfDead");
  SetDir(0);
  CastObjects(LUMP,25,20);
  RemoveObject();
  return(1);

/* Fortpflanzung */

public Reproduction:
  // Ohh ja du geile ******** Bwuahaha
  if (Not(GetAlive())) return(0);
  if (LessThan(GetCon(),100)) return(0);
  SetVar(0, CreateConstruction(WIPF,0,0,-1,40) );
  ObjectCall(Var(0),"Birth");
  return(1);

public Birth:
  // Bin da! :)
  SetAction("Walk");
  SetComDir(COMD_Left());
  if (Random(2)) SetComDir(COMD_Right());
  return(1);
