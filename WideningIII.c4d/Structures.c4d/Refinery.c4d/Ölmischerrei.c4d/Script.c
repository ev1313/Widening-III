// MSC-Script //

/* Nutzt die Grundfunktionalit�t der Werkstatt. */

#strict
#include WRKS
#include BAS5

/* Produktion */

private MenuProduction: // C4Object *pCaller
  // Men� erzeugen und mit Baupl�nen des Spielers f�llen
  CreateMenu(CHEM,Par(0),this(),1,"Keine Baupl�ne verf�gbar");
  SetVar(0,-1);
  while (SetVar(1, GetPlrKnowledge(GetOwner(Par(0)),0,IncVar(0),C4D_Object()) ))
    if (DefinitionCall(Var(1),"IsOLMIProduct"))
      AddMenuItem( "Herstellung: %s", "SelectProduction", Var(1), Par(0), 0, Par(0) );
  return(1);

/* T�rsteuerung */

private SoundOpenDoor:
  return(Sound("SteelGate2"));
private SoundCloseDoor:
  return(Sound("SteelGate2"));

/* Aktivit�t */

private Smoking:
  if (Random(2)) Smoke(+7,-27,8);
  Smoke(-5,-28,Sum(5,Random(3)));
  return(1);

/* Aufnahme */

protected Collection:
  return(Sound("Clonk"));

public GetResearchBase: return(RAF1);

// MSC-Script // 