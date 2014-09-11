#strict



// Local 0: Horizontale Fluggeschwindigkeit

Initialize:
  Call("Launch");
  return(1);

/* Wird abgefeuert, Par(0) ist Schuﬂrichtung */

public Launch:  
  SetAction("Travel");
  return(1);
  
/* Fliegt */
private Travel:
  SetXDir(0);
  SetYDir(80);
  CastObjects(FLRA,1,20,-7,-10);
  return(1);
  
Hit:
  CastObjects(_IO6,24,19,-7,-10);
  CastObjects(_IO6,12,10,-7,-50);
  CastObjects(_IO6,5,30,-7,-100);
  CastObjects(_IO6,5,10,-7,-60);
  CastObjects(_IO6,7,40,-7,-145);
  Explode(29);
  Explode(29);
  return(1);
  