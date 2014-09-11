/* Langzeitflamme */

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

  //Abbrennen
  if(GetActTime() > 800)
  {
   ChangeDef(FLAM);
   SetAction("Burn");
  }

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
   fDam=2+fDam*GetCon()/50;
   DoDamage(fDam,pB);

   var size = GetObjWidth(pB) * GetObjHeight(pB);
   if(GetDamage(pB) > size/10) Incinerate(pB);
  }

  return(1);
 }