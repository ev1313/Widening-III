// MSC-Script //


#strict


private FillCheck:
  // Material an aktueller Position überprüfen
  if (Equal(SetVar(0,GetMaterial(0,0)),-1)) return(0);
  // Mit Wasser füllen
  if (Equal( Var(0), Material("Water") ))
    return (FillWater());
  // Kein passendes Material
  return(1);

/* Aufschlag */ 
  
protected Hit:
  Sound("GlassBreak");
  RemoveObject();
  return(1);
  
/* Unterfunktionen */  
  
private FillWater:
  SetComDir( ExtractMaterialAmount(0,0,Material("Water"),100) );
  ChangeDef(WAFL);
  return(1);


/* Initialisierung */

protected Initialize:
  // ComDir wird als Fullstand mißbraucht
  SetComDir(0);
  return(1);
  
/* Produkteigenschaften */

public IsChemicalProduct: return(1);

// MSC-Script //