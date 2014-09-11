/*-- Abriss --*/

#strict

local target;

func Initialize()
{
 SetAction("Active");
}

func Boom()
{
 //Kein Ziel?
 if(!target) return(RemoveObject());

 var num;

 //Hälfte der Metalle ausgeben
 num = GetComponent(METL,0,target)/2;
 target -> CastObjects(METL,num,Random(10));
 num = GetComponent(KUPF,0,target)/2;
 target -> CastObjects(KUPF,num,Random(10));
 num = GetComponent(ALU1,0,target)/2;
 target -> CastObjects(ALU1,num,Random(10));
 num = GetComponent(CHRO,0,target)/2;
 target -> CastObjects(CHRO,num,Random(10));
 num = GetComponent(STAH,0,target)/2;
 target -> CastObjects(CHRO,num,Random(10));

 //50% Chance auf Bausatz
 num = Random(100);
 if(num > 50) target -> CastObjects(CNKT,1,Random(10));

 //Flamm und ende
 Sound("Blast3");
 Incinerate(target);
 RemoveObject();
}

func Target(a) { target=a; }