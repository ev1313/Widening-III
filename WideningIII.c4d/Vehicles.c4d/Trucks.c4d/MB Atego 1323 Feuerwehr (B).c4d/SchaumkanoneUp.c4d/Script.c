/*--- Löschschaumkanone ---*/

#strict
#include C_EX

protected func CannonPower(object obj) { return(Random(3)+Random(3)+8); }

public func ComFire(object pClonk, type)
{
 //Ein potentielles Gimmik: man kann den Objkettyp setzten, der verschossen wird. Upgrades?
 var shot = type;
 //Standart: Löschschaum
 if (!shot) shot = EX_S;
 //i= Anzahl der Objekte / sec
 var i = 20;
 while(i--) Exit(CreateContents(shot), Sin(GetR(), 17), -Cos(GetR(), 17), GetR(), Sin(GetR(), CannonPower(this())), -Cos(GetR(), CannonPower(this())), 20);
}