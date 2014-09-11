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
  CastObjects(FLRX,1,20,-7,-10);
  return(1);
  
Hit:
  CastObjects(_IO5,40,19,-7,-10);
  CastObjects(_IO5,20,10,-7,-50);
  CastObjects(_IO5,15,30,-7,-100);
  CastObjects(_IO5,20,10,-7,-150);
  CastObjects(_IO5,30,40,-7,-200);
  Explode(25);
  Explode(25);
  Explode(25);
  return(1);
  