/*-- Bestellung --*/

#strict

func Room()
{
 return(20-ContentsCount()-19*HasVehicle());
}

func HasVehicle()
{
 var c = ContentsCount();
 while (c--) if(GetCategory(Contents(c)) & C4D_Vehicle()) return(1);
}

func ContValue()
{
 var c = ContentsCount();
 var price; //Preis
 while (c--) price = price+GetValue(Contents(c));
 return(10+price*175/100); //75% draufgeschlagen, Grundpreis für Kiste und Liefern 50 Clunker
}

func Deliver(plr)
{
 //War mal basis
 var base = GetCursor(plr); 
 if(!HasVehicle()) var crate = CreateObject(KIST,GetX(base)-GetX(),-GetY()+1,plr);

 var c = ContentsCount();
 while (c--)
 {
  var obj = Contents(c);
  if(HasVehicle()) CreateObject(GetID(obj),GetX(base)-GetX(),-GetY()+1,plr);
  else CreateContents(GetID(obj),crate);
  RemoveObject(obj);
 }
 PlayerMessage(plr,"Bestätigt, die Bestellung wird über Ihrer aktuellen Position abgeworfen.");
 RemoveObject();
}