// MSC-Script //

#strict

/*-- Ölflasche --*/

protected Initialize:
  SetComDir(200);
  return(1);

protected Hit:
  Sound("Glassbreak");
  Sound("Splash1");
  CastPXS("Oil",GetComDir(),30);
  SetComDir(0);
  RemoveObject();
  return(1);
  
