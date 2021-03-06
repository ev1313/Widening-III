/*-- Plastiksprengstoff --*/

#strict

local fuse; //ID des Zünders
local caller;
local mass;

local active; //Alle: Angeschaltet?

local time; //Zeitzünder: Zeit bis zur Detonation.

local range; //Bewegungszünder: radius in Pixel


/*---------------------- Triviales -----------------------------*/

func Initialize()
{
  mass=100;
  return(1);
}

public func CalcValue()
{
 var basic = GetValue(0,GetID());
 var fuseprice = 0;
 if(fuse) fuseprice = GetValue(0,fuse);
 return(basic*mass/100+fuseprice);
}

/* Kann chemisch werden */
IsChemicalProduct: return(1);

/*---------------------- Explosion und Timer Call -----------------------------*/

func Check()
{
 if(!active) return(1);

 if(fuse == SFUS) //Zeitzünder
 {
  if(time) time--;
  else Boom(75);
  Message("%d",this(),time);
 }

 if(fuse == MFUS) //Bewegungszünder
 {
  var count, obj, call;
  for(count=ObjectCount(0,-range,-range,range*2,range*2,OCF_Alive());count>0;count--)
  {
   obj = FindObject (0,0,0,0,0,OCF_Alive(),0,0,Contained(),obj); 
   if(Hostile(GetOwner(),GetOwner(obj))) Boom(70);
  }
 }

}

func Boom(value) //Besondere Explosion
{
 var bomb;
 var range = value*mass/100;
 var count = value /10; 

 while(count)
 {
  Explode(range/3,CreateObject(ROCK,RandomX(-range,+range),RandomX(-range,+range),-1));
  count--;
 }
 Explode(range);
}


/*---------------------- Menü -----------------------------*/

func Activate(user)
{
 //Vorbereitungen
 caller = user;
 if(!caller) return(0);

 // Info für den Spieler
 var fusetxt;
 if(!fuse) fusetxt = "kein Zünder";
 if(fuse == SFUS) fusetxt = "Elektrischer Zeitzünder";
 if(fuse == MFUS) fusetxt = "Elektrischer Bewegungszünder";

 if(active) var additional = "AKTIVER ";

 Message("C4, Masse %d Gramm, %s%s", caller, mass, additional, fusetxt);

 // Menü erstellen
 CreateMenu(GetID(),caller,this());

 //Zerteilen
 if(mass > 25 && !fuse) AddMenuItem("Zerteilen","SplitMelt",GetID(),caller,0,1);

 // Zusammenfügen
 var other = FindObject (GetID(),0,0,0,0,0,0,0,caller); 
 if(mass < 300 && other && !fuse) AddMenuItem("Zusammenfügen","SplitMelt",GetID(),caller,0,2);

 if(!fuse ) AddMenuItem("Zünder einbauen","FuseInOut",GetID(),caller,0,1);
 if(fuse && !active) AddMenuItem("Zünder ausbauen","FuseInOut",fuse,caller,0,2);

 if(fuse == SFUS && !active) AddMenuItem("Zeitzünder aktivieren","TimeFuse",fuse,caller,0,1);
 if(fuse == SFUS && active) AddMenuItem("Zeitzünder deaktivieren","TimeFuse",fuse,caller,0,2);

 if(fuse == MFUS) AddMenuItem("Bewegungszünder einstellen","MotionFuse",fuse,caller,0,1);
 if(fuse == MFUS && active) AddMenuItem("Bewegungszünder deaktivieren","MotionFuse",fuse,caller,0,2);

}

/*---------------------- Zerteilen und Zusammenfügen -----------------------------*/

func Size(set)
{
 if(set) return(mass=set);
 else return(mass);
}

func SplitMelt(i,mode)
{
 if(!mode) return(0);

 if(mode==1)
 {
  var new = CreateObject(GetID(),0,0,GetOwner());
  new -> Size(mass/2);
  Size(mass/2);
  return(1);
 }

 if(mode==2)
 {
  var other = FindObject (GetID(),0,0,0,0,0,0,0,caller); 
  var size = other -> Size();
  fuse = other -> Fuse();
  RemoveObject(other);
  mass = mass+ size;
  if(mass > 300) mass = 300; 
  return(1);
 }
}

/*---------------------- Zünderwahl und Wiederausbau -----------------------------*/

func Fuse() { return(fuse); }

func FuseInOut(type,mode)
{

 if(type && !mode)
 {
  if(RemoveObject(FindObject(type,0,0,0,0,0,0,0,caller))) return(fuse=type);
 }

 if(mode == 1)
 {
  CreateMenu(GetID(),caller,this());
  var count, obj, call;
  for(count=ContentsCount(0,Contained())-1;count>0;count--)
  {
   obj = FindObject (0,0,0,0,0,0,0,0,Contained(),obj); 
   call = obj ->~ IsExplosiveFuse();
   if(call) AddMenuItem(GetName(obj),"FuseInOut",GetID(obj),caller,0,0);
  }
 }

 if(mode == 2)
 {
  CreateObject(fuse,0,0,GetOwner());
  return(fuse=0);
 }

}

/*---------------------- Zündermenüs -----------------------------*/

func TimeFuse(i,mode) //Zeitzünder
{

 if(mode==1)
 {
  CreateMenu(GetID(),caller,this());
  AddMenuItem("5 Sekunden","TimeFuse",fuse,caller,0,5);
  AddMenuItem("10 Sekunden","TimeFuse",fuse,caller,0,10);
  AddMenuItem("15 Sekunden","TimeFuse",fuse,caller,0,15);
  AddMenuItem("30 Sekunden","TimeFuse",fuse,caller,0,30);
 }

 if(mode==2)
 {
  active=0;
  time=0;
  Message("OK, abgeschaltet.", caller);
 }

 if(mode > 4)
 {
  active=1;
  time=mode;
  Message("Besser weg hier...", caller);
 }

}

func MotionFuse(i,mode) //Bewegungszünder
{

 if(mode==1)
 {
  CreateMenu(GetID(),caller,this());
  AddMenuItem("25 Pixel","MotionFuse",fuse,caller,0,25);
  AddMenuItem("50 Pixel","MotionFuse",fuse,caller,0,50);
  AddMenuItem("100 Pixel","MotionFuse",fuse,caller,0,100);
 }

 if(mode==2)
 {
  active=0;
  range=0;
  Message("OK, abgeschaltet.", caller);
 }

 if(mode > 4)
 {
  active=1;
  range=mode;
  Message("Der Zünder ist aktiv: Radius %d.", caller, range);
 }

}