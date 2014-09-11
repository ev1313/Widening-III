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
  CastObjects(FLRZ,1,20,-7,-10);
  return(1);
  
Hit:
  CastObjects(_ION,10,19,-7,-10);
  CastObjects(_ION,9,10,-7,-50);
  CastObjects(_ION,4,30,-7,-100);
  CastObjects(_ION,6,10,-7,-60);
  CastObjects(_ION,5,40,-7,-145);
  Explode(25);
  Explode(25);
  return(1);
  