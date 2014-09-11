// MSC-Script //


#strict


protected Hit:
  CastObjects(FLAM, 50, 40 );
  Sound("Inflame");
  RemoveObject();
  return(1);

/* Produkteigenschaften */

public IsChemicalProduct: return(1);

/* Forschung */

public GetResearchBase: return(FBMP);
