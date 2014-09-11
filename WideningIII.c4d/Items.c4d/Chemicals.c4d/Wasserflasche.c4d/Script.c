// MSC-Script //



#strict

protected Initialize:
  DoScore(0, 5);
  SetComDir(200);
  return(1);

protected Hit:
  Sound("Glassbreak");
  Sound("Splash1");
  CastPXS("Water",GetComDir(),10);
  SetComDir(0);
  RemoveObject();
  return(1);


/* Kann chemisch werden */
IsChemicalProduct: return(1);
  
// MSC-Script //

