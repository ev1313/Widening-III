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
  CastObjects(FLRY,1,20,-7,-10);
  return(1);
  
Hit:
  CastObjects(_IO3,30,19,-7,-10);
  CastObjects(_IO3,40,10,-7,-50);
  CastObjects(_IO3,10,30,-7,-100);
  CastObjects(_IO3,30,10,-7,-60);
  CastObjects(_IO3,5,40,-7,-145);
  Explode(25);
  Explode(25);
  return(1);
  