// MSC-Script //

/* Initialisierung */

#strict

protected Initialize:
  CreateWindwing();
  return(1);

/* Fundament (Local 9)*/

protected Construction:
  SetLocal(9,CreateObject(BAS1,0,+8));
  return(1);
  
protected Destruction:
  if (Local(9)) RemoveObject(Local(9));
  return(1);

/* Windrad erzeugen */

private CreateWindwing:
  ObjectSetAction(CreateObject(IWWK),"Turn",this());
  return(1);

/* TimerCall */

private CheckWindwing:
  // Komplett, aber kein Windrad da: reduzieren für Neuaufbau/Reparatur
  if (Equal(GetCon(),100))
    if (Not(FindObject(IWWK,0,0,0,0,0,"Turn",this())))
      DoCon(-1);
  return(1);


/* Forschung */

public GetResearchBase: return(WKRA);

// MSC-Script //
