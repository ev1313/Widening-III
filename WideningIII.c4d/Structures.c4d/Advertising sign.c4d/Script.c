// MSC-Script //

#strict

local cash; //Auszahlung

protected func Construction()
{
  if(FindObjectOwner (GetID(),GetOwner()))
  {
   Message("Wir haben bereits eine Werbetafel.",GetCursor(GetOwner()) );
   return(RemoveObject());
  }

  SetLocal(9,CreateObject(BAS4,0,+8,GetOwner()));
  SetAction("Stop");
  return(1);
}
  
protected func Destruction()
{
  if (Local(9)) RemoveObject(Local(9));
  return(1);
}

protected func ControlDigDouble(caller)
{

  if(GetOwner() != GetOwner(caller)) return(Message("Nicht authorisierter Zugriff!",this()));

  var m = GetWealth(GetOwner());

  CreateMenu(_MW0,caller,this());
  if(m>=50) AddMenuItem("%s","Menu",WE01,caller);
  if(m>=35) AddMenuItem("%s","Menu",WE02,caller);
  if(m>=40) AddMenuItem("%s","Menu",WE03,caller);
  if(m>=50) AddMenuItem("%s","Menu",WE04,caller);
  if(m>=65) AddMenuItem("%s","Menu",WE05,caller); 
  AddMenuItem("%s","Menu",WE06,caller);
  return(1);  
}

func Menu()
{
 var c = Par(0);
 var m = GetWealth(GetOwner());

 if(c == WE01)
 {
  cash = 8;
  SetWealth(GetOwner(),m-50);
  SetAction("Mercedes");
  Message("Vertrag wird abgeschlossen: 50",this());
  Sound("cash2");
 }

 if(c == WE02)
 {
  cash = 10;
  SetWealth(GetOwner(),m-35);
  SetAction("Opel");
  Message("Vertrag wird abgeschlossen: 35",this());
  Sound("cash2");
 }

 if(c == WE03)
 {
  cash = 12;
  SetWealth(GetOwner(),m-40);
  SetAction("DEA");
  Message("Vertrag wird abgeschlossen: 40",this());
  Sound("cash2");
 }


 if(c == WE04)
 {
  cash = 15;
  SetWealth(GetOwner(),m-50);
  SetAction("SHELL");
  Message("Vertrag wird abgeschlossen: 50",this());
  Sound("cash2");
 }

 if(c == WE05)
 {
  cash = 20;
  SetWealth(GetOwner(),m-65);
  SetAction("Signum");
  Message("Vertrag wird abgeschlossen: 65",this());
  Sound("cash2");
 }

 if(c == WE06)
 {
  Sound("HGfinal");
  cash = 0;
  SetAction("Stop");
  Message("Transaktion eingestellt",this());
 }

  return(1);
}    

func PayOut()
{
 SetWealth(GetOwner(),GetWealth(GetOwner())+cash);
 Sound("cash2");
 Message("Geld überwiesen: %d",this(), cash );
 CreateObject(DOLL,0,-40);
 return(1);
}

// MSC-Script //

public GetResearchBase: return(FNDR);  