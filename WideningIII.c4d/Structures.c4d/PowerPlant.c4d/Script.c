// MSC-Script //

#strict

/* Fundament (Local 9) */

protected Construction:
  SetLocal(9,CreateObject(BAS4,+1,+8,GetOwner()));
  return(1);
  
protected Destruction:
  if (Local(9)) RemoveObject(Local(9));
  return(1);

/* Initialisierung */

protected Initialize:
  // Auch eine Möglichkeit um an Heizöl zu kommen
  CreateContents(HOIL);
  return(1);

/* Eingangssteuerung */

protected ActivateEntrance: 
  if (ActIdle()) SetAction("OpenDoor");
  return(1);
  
private OpenEntrance:
  SetEntrance(1);
  return(1);

private CloseEntrance:
  SetEntrance(0);
  return(1);

private SoundOpenDoor:
  return(Sound("GateOpen"));

private SoundCloseDoor:
  return(Sound("GateClose"));
  
protected Collection:
  return(Sound("Clonk"));


/* Produktion */

private Burning:
  // Rauch
  Smoke(-15,-20,12);
  Smoke(-1,-23,8);
  // Energieerzeugung
  DoEnergy(+100);
  // Weiter
  if (LessThan(GetActTime(),GetBurnTime())) return(1);
  // Feddich
  SetAction("Idle");
  return(1);

/* Inhaltsüberprüfung */

private ContentsCheck:
  // Noch aktiv
  if (Not(ActIdle())) return(1);
  // Loren ausleeren und rausschicken
  SetVar(0,-1);
  while(SetVar(1,Contents(IncVar(0))))
    if (ObjectCall(Var(1), "IsLorry"))
      And( GrabContents(Var(1)), SetCommand(Var(1),"Exit") );  
  // Erstes Inhaltsobjekt überprüfen
  SetVar(1,Contents(0)); SetVar(0,GetID(Var(1)));
  // Alles außer Rohmaterial rauslegen
  if ( Not( Or( Equal(Var(0),COAL),
		            Equal(Var(0),HOIL),
                Equal(Var(0),WOOD) ) ) )
    SetCommand(Var(1),"Exit");
  // Wird Energie benötigt?
  if (Not(CheckEnergyNeedChain())) return(1);
  // Holz verbrennen
  if (GreaterThan(ContentsCount(WOOD),1))
    return(BurnWood());
  // Heizöl verbrennen
  if (GreaterThan(ContentsCount(HOIL),0))
    return(BurnOil());
  // Kohle verbrennen... willst du das wirklich tun?
  if (Not(SetVar(0,FindContents(COAL)))) return(1);
  RemoveObject(Var(0));
  SetAction("Burning");
  return(1);

private BurnWood:
  SetVar(0,FindContents(WOOD));
  RemoveObject(Var(0));
  SetVar(0,FindContents(WOOD));
  RemoveObject(Var(0));
  SetAction("Burning");
  return(1);

private BurnOil:
  if (Not(SetVar(0,FindContents(HOIL)))) return(0);
  RemoveObject(Var(0));
  SetAction("Burning");
  return(1);

/* Brenndauer */
private GetBurnTime: return(2500);
