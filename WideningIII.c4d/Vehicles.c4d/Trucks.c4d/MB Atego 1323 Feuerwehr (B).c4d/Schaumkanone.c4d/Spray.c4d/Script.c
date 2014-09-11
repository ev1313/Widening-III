/* Löschschuss */

#strict


/* Initialisierung */

protected func Initialize()
{
  SetAction("Fly");
  return(1);
}

func Check()
{
  var obj = FindObject(0,-10,-10,20,20, OCF_OnFire());
  if (!obj) return(1);
  Extinguish(obj);
  Sound("Pshshsh");
  return(Remove());
}

/* Treffer */

protected func Hit()
{
  var obj = FindObject(0,-10,-10,20,20, OCF_OnFire());
  if (obj)
  {
  Extinguish(obj);
  Sound("Pshshsh");
  }

  var ph = BoundBy(GetPhase(),0,6);
  SetAction("Attach");
  SetPhase(ph);
  return(1);
}


/* Weg damit */

public func Remove()
{
  return(RemoveObject());
}