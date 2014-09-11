/*-- Kraftwerk --*/

/* Fundament (Local 9) */

#strict

protected Construction:
  SetLocal(9,CreateObject(BAS4,+1,+8));
  return(1);
  
protected Destruction:
  if (Local(9)) RemoveObject(Local(9));
  return(1);

/* Initialisierung */

protected Initialize:
  // Netterweise gibt's zu Beginn einmal Plutonium
  CreateContents(PLUT);
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
  Smoke(-15,-20,3);
  Smoke(-1,-23,1);
  // Energieerzeugung
  DoEnergy(+200);
  // Weiter
  if (LessThan(GetActTime(),4500)) return(1);
  // Fertig
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
  if ( Not( Or( Equal(Var(0),PLUT),
		            Equal(Var(0),PLU2) ) ) )
    SetCommand(Var(1),"Exit");
  // Wird Energie benötigt?
  if (Not(CheckEnergyNeedChain())) return(1);
  // Holz verbrennen
  if (GreaterThan(ContentsCount(PLUT),0))
    return(BurnOil());
  // Heizöl verbrennen
  if (GreaterThan(ContentsCount(PLU2),0))
    return(BurnOil2());


private BurnOil:
  SetVar(0,FindContents(PLUT));
  ChangeDef(ATOM,Var(0));
  SetAction("Burning");
  return(1);

private BurnOil2:
  if (Not(SetVar(0,FindContents(PLU2)))) return(0);
  ChangeDef(ATOM,Var(0));
  SetAction("Burning");
  return(1);





public GetResearchBase: return(POWR);
