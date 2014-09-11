// MSC-Script //

#strict


Hit:
  Explode(70);
  Explode(70);
  Sound("HEADCRAS");
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);

/* Forschung */

public GetResearchBase: return(MSFL);