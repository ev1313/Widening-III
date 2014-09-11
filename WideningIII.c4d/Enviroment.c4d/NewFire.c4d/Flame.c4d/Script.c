/* Flamme */

#strict

protected func Initialize()
 {
  Incinerate();
  SetAction("Burn");
  return(1);
 }

protected func BurnProcess()
 {
  if (!OnFire()) return(RemoveObject());



  //Etwas nährt die Flamme
  var feed;

  //kleine Flammen absplittern
  if(GetCon() > 150)
  {
   DoCon(-30);
   if(ObjectCount(FLAM,-30,-30,30,30) <= 3) //Suchradius und Anzahl bein Split
   {
    var i = CreateObject(FLAM,0,0,-1);
    i -> SetCon(25);
    SetYDir(RandomX(-10,-5), i);
    SetXDir(RandomX(15,-15), i);
    return(1);
    }
  }

  //Zu viele -> verschmelzen
  if(ObjectCount(FLAM,-20,-20,20,20) > 3) FindObject(FLAM,-20,-20,20,20) -> Melt(this());

  //Ölbrände
  if (FlameConsumeMaterial (0, 7))
  {
   SetXDir(Random(31)-15);
   feed=7;
  }

  //Andere Brände
  var pB;
  pB = FindObject2(Find_OCF(OCF_OnFire()),Find_Distance(30+GetCon()/5),Find_Exclude());
  if(pB) if(GetID(pB) != FLAM) feed=feed+5;

  //Gebäude kaputt machen
  var pB;
  pB = FindObject2(Find_Category(2),Find_Distance(30+GetCon()/5),Find_Exclude());
  if(pB)
  {
   var fDam;
   var i;
   for(i=0;0;i++)
   {
    var id = GetDefCoreVal("Components", "DefCore", GetID(pB), i*2);
    if(!id) break;
    if(id == WOOD) fDam++;
   }

   //Basisschaden: erste Zahl
   fDam=1+fDam*GetCon()/50;
   DoDamage(fDam,pB);

   var size = GetObjWidth(pB) * GetObjHeight(pB);

   //Zeit bis zur Zerstörung: size/x
   if(GetDamage(pB) > size/10) Incinerate(pB);

  }

  //Wachstum
  if(!feed) feed = -2; //Verfallrate hier
  DoCon(feed);

  return(1);
}


func Melt(pObj)
{
 if(!pObj) return(0);
 DoCon(GetCon(pObj));

 //Die Apokalyptica-Sicherung
 if(GetCon() > 150) SetCon(150);

 RemoveObject(pObj);
}