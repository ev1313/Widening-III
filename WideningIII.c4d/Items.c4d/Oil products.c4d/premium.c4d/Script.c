#strict

// MSC-Script //

Hit:
  Sound("ClonkHit*");
  return(1);

Damage:
  CastObjects(DFLM, 15, 20 );
  SetVar(0,CreateContents(_AE4));
  Exit(Var(0),0,0,Random(360), Sum(Random(7),-3), Sum(Random(3),-8), +10);
  Incinerate(Var(0));
  Explode(35);  
  return(1);

Where:
  if(Equal(Contained(),0)) return(1);
  if(BitAnd(GetCategory(Contained()),C4D_Vehicle())) return(Call("InVehicle"));
  return(1);

InVehicle:
  if(Equal(ObjectCall(Contained(),"Tanken2",20),1)) RemoveObject();
  return(1);

/* Kann chemisch werden */
IsGasProduct: return(1);




