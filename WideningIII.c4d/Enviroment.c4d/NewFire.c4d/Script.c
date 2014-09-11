/*-- Neues Feuer --*/

#strict

// An dieser Stelle ein Dank an Matthes Bender für die gute Beratung (=

global func FxFireTimer(pObj,a,b,c,d,e,f,g,h)
 {
   //Sicherung
   if(!pObj) return(_inherited(pObj,a,b,c,d,e,f,g,h));

   //Wie groß ist unser Objekt?
   var ObjWidth = GetObjWidth(pObj);
   var ObjHeight = GetObjHeight(pObj);

   //Kleine Objekte funzeln nicht
   if(ObjWidth < 5 | ObjHeight < 5) return(_inherited(pObj,a,b,c,d,e,f,g,h));

   //Anzahl: ObjectCount(....) < x, x ist die maximale Zahl im Radius
   //Suchradius: Ermittelte Objekthöhe und -breite, Multiplikator ändern zum heben/senken
   //Siehe ObjectCount in der Entwicklerdoku

   if(!Random(15) && pObj -> ObjectCount(FLAM,-ObjWidth,-ObjHeight,ObjWidth*2,ObjHeight*2) <= 2)
   {
    //Sonst vermehren sich Flammen ins endlose
    if(GetID(pObj) != FLAM && GetID(pObj) != DFLM && !(GetOCF(pObj) & OCF_CrewMember()))
    {
     var New = pObj -> CreateObject(FLAM,RandomX(-ObjWidth/2,ObjWidth/2),RandomX(-ObjHeight/2,ObjHeight/2),-1);
     New -> SetCon(25);
     New -> SetXDir(RandomX(-10,10));
    }
   }

   //Und zurück an den Chefkoch...
   return(_inherited(pObj,a,b,c,d,e,f,g,h));
 }