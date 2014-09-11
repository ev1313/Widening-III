// MSC-Script //

#strict

Initialize:
  DoScore(0, 200);
  return(1);

protected Hit:
  Sound("MetalHit*");
  return(1);

/* Kann chemisch werden */
IsGasProduct: return(1);

/* Forschung */

public GetResearchBase: return(PLUT);



