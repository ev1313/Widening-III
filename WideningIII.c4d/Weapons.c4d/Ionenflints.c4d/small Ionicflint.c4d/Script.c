/*-- Torpedo --*/



/* Aufschlag */

public Hit:
  CreateObject(ENE3,0,-400);
  RemoveObject();
  return(1);


/* Produkteigenschaften */

public IsChemicalProduct: return(1);


/* Forschung */

public GetResearchBase: return(IBOM);
