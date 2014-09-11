
// MSC-Script //

#strict
#include BAS8
#include DOOR
  
/* Türsteuerung */

private SoundOpenDoor:
  return(Sound("GateOpen"));
  
private SoundCloseDoor:
  return(Sound("GateClose"));
  
/* Forschung */

public GetResearchBase: return(CST3);

// MSC-Script //