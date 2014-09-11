/*--- Löschschaumkanone ---*/

#strict

local controller;

protected func RotationSpeed() { return(8); }

protected func CannonPower(object obj) { return(Random(3)+6); }

/* Auto weg? */

protected func AttachTargetLost()
{
  RemoveObject();
}

/* Kommandos aus dem Auto */

public func ComLeft(object pClonk)
{
  SetAction("Rotating",GetActionTarget());
  SetRDir(-RotationSpeed() );
  return(1);
}

public func ComRight(object pClonk)
{
  SetAction("Rotating",GetActionTarget());
  SetRDir(RotationSpeed() );
  return(1);
}

public func ComStop(object pClonk)
{
  SetAction("Attaching",GetActionTarget());
  SetRDir(0);
  return(1);
}

public func ComFire(object pClonk, type)
{
 //Ein potentielles Gimmik: man kann den Objkettyp setzten, der verschossen wird. Upgrades?
 var shot = type;
 //Standart: Löschschaum
 if (!shot) shot = EX_S;
 //i= Anzahl der Objekte / sec
 var i = 15;
 while(i--) Exit(CreateContents(shot), Sin(GetR(), 13), -Cos(GetR(), 13), GetR(), Sin(GetR(), CannonPower(this())), -Cos(GetR(), CannonPower(this())), 20);
}