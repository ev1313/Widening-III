#strict

// MSC-Script //

Hit:
  Sound("ClonkHit*");
  return(1);

Damage:
  CastObjects(DFLM, 15, 20 );
  SetVar(0,CreateContents(_AE6));
  Exit(Var(0),0,0,Random(360), Sum(Random(7),-3), Sum(Random(3),-8), +10);
  Incinerate(Var(0));
  Explode(35);  
  return(1);

/* Kann chemisch werden */
IsOLMIProduct: return(1);

/* Forschung */

public GetResearchBase: return(OLMI);


