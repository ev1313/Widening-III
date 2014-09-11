/*-- Plastiksprengstoff --*/

#strict

local fuse; //ID des Z�nders
local caller;
local mass;

local active; //Alle: Angeschaltet?

local time; //Zeitz�nder: Zeit bis zur Detonation.

local range; //Bewegungsz�nder: radius in Pixel


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

 if(fuse == SFUS) //Zeitz�nder
 {
  if(time) time--;
  else Boom(75);
  Message("%d",this(),time);
 }

 if(fuse == MFUS) //Bewegungsz�nder
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


/*---------------------- Men� -----------------------------*/

func Activate(user)
{
 //Vorbereitungen
 caller = user;
 if(!caller) return(0);

 // Info f�r den Spieler
 var fusetxt;
 if(!fuse) fusetxt = "kein Z�nder";
 if(fuse == SFUS) fusetxt = "Elektrischer Zeitz�nder";
 if(fuse == MFUS) fusetxt = "Elektrischer Bewegungsz�nder";

 if(active) var additional = "AKTIVER ";

 Message("C4, Masse %d Gramm, %s%s", caller, mass, additional, fusetxt);

 // Men� erstellen
 CreateMenu(GetID(),caller,this());

 //Zerteilen
 if(mass > 25 && !fuse) AddMenuItem("Zerteilen","SplitMelt",GetID(),caller,0,1);

 // Zusammenf�gen
 var other = FindObject (GetID(),0,0,0,0,0,0,0,caller); 
 if(mass < 300 && other && !fuse) AddMenuItem("Zusammenf�gen","SplitMelt",GetID(),caller,0,2);

 if(!fuse ) AddMenuItem("Z�nder einbauen","FuseInOut",GetID(),caller,0,1);
 if(fuse && !active) AddMenuItem("Z�nder ausbauen","FuseInOut",fuse,caller,0,2);

 if(fuse == SFUS && !active) AddMenuItem("Zeitz�nder aktivieren","TimeFuse",fuse,caller,0,1);
 if(fuse == SFUS && active) AddMenuItem("Zeitz�nder deaktivieren","TimeFuse",fuse,caller,0,2);

 if(fuse == MFUS) AddMenuItem("Bewegungsz�nder einstellen","MotionFuse",fuse,caller,0,1);
 if(fuse == MFUS && active) AddMenuItem("Bewegungsz�nder deaktivieren","MotionFuse",fuse,caller,0,2);

}

/*---------------------- Zerteilen und Zusammenf�gen -----------------------------*/

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

/*---------------------- Z�nderwahl und Wiederausbau -----------------------------*/

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

/*---------------------- Z�ndermen�s -----------------------------*/

func TimeFuse(i,mode) //Zeitz�nder
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

func MotionFuse(i,mode) //Bewegungsz�nder
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
  Message("Der Z�nder ist aktiv: Radius %d.", caller, range);
 }

}