#strict


local an,child;
protected Initialize:
  	return(1);

//--Initialisierung--//

Initialize:
  SetAction("stop");
  SetComDir(COMD_Stop());
  SetEntrance(1);
  SetLocal(1,5000);
  SetLocal(2,55);
  return(1);

//--Steuerung--//

ContainedLeft:
  if(OnFire(this())) return(1);
  SetEntrance(0);
  if(Equal(GetDir(),DIR_Right())) return(Call("Drehleft"));
  SetComDir(COMD_Left());
  SetDir();
  if(SEqual(GetAction(),"move")) return(SetAction("move2"));
  if(SEqual(GetAction(),"move2")) return(SetAction("move3"));
  if(SEqual(GetAction(),"move3")) return(SetAction("move4"));
  if(SEqual(GetAction(),"move4")) return(1);
  SetAction("move");
  return(1);
Drehleft:
  SetEntrance(0);
  SetDir();
  SetComDir(COMD_Left());
  SetAction("move");
  return(1);
ContainedRight:
  if(OnFire(this())) return(1);
  SetEntrance(0);
  if(Equal(GetDir(),DIR_Left())) return(Call("Drehright"));
  SetComDir(COMD_Right());
  SetDir(1);
  if(SEqual(GetAction(),"move")) return(SetAction("move2"));
  if(SEqual(GetAction(),"move2")) return(SetAction("move3"));
  if(SEqual(GetAction(),"move3")) return(SetAction("move4"));
  if(SEqual(GetAction(),"move4")) return(1);
  SetAction("move");
  return(1);
Drehright:
  SetEntrance(0);
  SetDir(1);
  SetComDir(COMD_Right());
  SetAction("move");
  return(1);
ContainedDown:
  if(SEqual(GetAction(),"Crashed")) return(SetEntrance(1));
  if(SEqual(GetAction(),"stop")) return(SetEntrance(1));
  if(SEqual(GetAction(),"Crashed")) return(SetEntrance(1));
  if(SEqual(GetAction(),"Tank")) return(SetEntrance(1));
  if(SEqual(GetAction(),"move")) return(Call("Aus"));
  if(SEqual(GetAction(),"move2")) SetAction("move");
  if(SEqual(GetAction(),"move3")) SetAction("move2");
  if(SEqual(GetAction(),"move4")) SetAction("move3");
  SetEntrance(0);
  return(1);
Aus:
  SetAction("stop");
  SetComDir(COMD_Stop());
  SetXDir();
  SetEntrance(0);
  return(1);
Moving:
  if(Equal(Local(1),500)) Message("Nicht mehr viel Benzin!",this());
  if(Equal(Local(1),50)) Message("Nur noch einige Tropfen Benzin im Tank",this());
  if(LessThan(Local(1),1)) return(Call("leer"));
  SetLocal(1,Sum(Local(1),-1));
  SetEntrance(0);
  if(GetDir()) Call("MoveRight");
  if(Not(GetDir())) Call("MoveLeft");
  if(GreaterThan(GetDamage(),10))Smoke(2,1,Sum(10,Random(1)));
  if(GreaterThan(GetDamage(),20))Smoke(1,0,Sum(10,Random(3)));
  if(GreaterThan(GetDamage(),25))Smoke(0,2,Sum(10,Random(4)));
  return(1);
Moving2:
  if(Equal(Local(1),500)) Message("Nicht mehr viel Benzin!",this());
  if(Equal(Local(1),50)) Message("Nur noch einige Tropfen Benzin im Tank",this());
  if(LessThan(Local(1),1)) return(Call("leer"));
  SetLocal(1,Sum(Local(1),-2));
  SetEntrance(0);
  if(GetDir()) Call("MoveRight2");
  if(Not(GetDir())) Call("MoveLeft2");
  if(GreaterThan(GetDamage(),10))Smoke(2,1,Sum(10,Random(1)));
  if(GreaterThan(GetDamage(),20))Smoke(1,0,Sum(10,Random(3)));
  if(GreaterThan(GetDamage(),30))Smoke(0,2,Sum(10,Random(4)));
  return(1);
Moving3:
  if(Equal(Local(1),500)) Message("Nicht mehr viel Benzin!",this());
  if(Equal(Local(1),50)) Message("Nur noch einige Tropfen Benzin im Tank",this());
  if(LessThan(Local(1),1)) return(Call("leer"));
  SetLocal(1,Sum(Local(1),-3));
  SetEntrance(0);
  if(GetDir()) Call("MoveRight3");
  if(Not(GetDir())) Call("MoveLeft3");
  if(GreaterThan(GetDamage(),10))Smoke(2,1,Sum(10,Random(1)));
  if(GreaterThan(GetDamage(),20))Smoke(1,0,Sum(10,Random(3)));
  if(GreaterThan(GetDamage(),30))Smoke(0,2,Sum(10,Random(4)));
  return(1);
Moving4:
  if(Equal(Local(1),500)) Message("Nicht mehr viel Benzin!",this());
  if(Equal(Local(1),50)) Message("Nur noch einige Tropfen Benzin im Tank",this());
  if(LessThan(Local(1),1)) return(Call("leer"));
  SetLocal(1,Sum(Local(1),-3));
  SetEntrance(0);
  if(GetDir()) Call("MoveRight4");
  if(Not(GetDir())) Call("MoveLeft4");
  if(GreaterThan(GetDamage(),10))Smoke(2,1,Sum(10,Random(1)));
  if(GreaterThan(GetDamage(),20))Smoke(1,0,Sum(10,Random(3)));
  if(GreaterThan(GetDamage(),30))Smoke(0,2,Sum(10,Random(4)));
  return(1);
MoveRight:
  SetXDir(0+Local(2)/5);
  return(1);
MoveLeft:
  SetXDir(0-Local(2)/5);
  return(1);
MoveRight2:
  SetXDir(0+Local(2)/3+1);
  return(1);
MoveLeft2:
  SetXDir(0-Local(2)/3-1);
  return(1);
MoveRight3:
  SetXDir(0+Local(2)/2+5);
  return(1);
MoveLeft3:
  SetXDir(0-Local(2)/2-5);
  return(1);
MoveRight4:
  SetXDir(0+Local(2));
  return(1);
MoveLeft4:
  SetXDir(0-Local(2));
  return(1);

Tanken3:
  SetLocal(1,Sum(Local(1),+5000));
  if(GreaterThan(Local(1),25000)) return(Call("FullTank"));
  Message("Treibstoff: %d von 25000",this(),Local(1));
 return(1);
FullTank:
  SetLocal(1,25000);
  Message("Tank ist voll",this());
  return(1);
leer:
  SetEntrance(1);
  Sound("Leer.wav");
  SetAction("stop");
  SetComDir(COMD_Stop());
  SetXDir();
  Message("Kein Benzin mehr",this());
  SetLocal(1,0);
  return(1);

//--Menü--//

ContainedDigSingle:
  CreateMenu(10,Par(0),this());
  if(LessThan(Local(1),500)) AddMenuItem("Treibstoff?","Display",8P2A,Par(0));
  if(GreaterThan(Local(1),499)) AddMenuItem("Treibstoff?","Display",8P2M,Par(0));
  AddMenuItem("Tuningstufen?","TuningInfo",MTP3,Par(0));
  AddMenuItem("Licht","Lichtschalten",MENL,Par(0));
 return(1);
Display:
  Message("Restbenzin (Super plus): %d von 25000",this(),Local(1));
  return(1);




//--Auspuff--//

Smoke:
  AssignVar(0,-22);
  if(Equal(GetDir(),DIR_Left())) AssignVar(0,+22);
  return(1);
Smoke2:
  AssignVar(0,-22);
  if(Equal(GetDir(),DIR_Left())) AssignVar(0,+22);
  Smoke(Var(0),6,4);
  return(1);
Smoke3:
  AssignVar(0,-22);
  if(Equal(GetDir(),DIR_Left())) AssignVar(0,+22);
  Smoke(Var(0),6,5);
  return(1);
Smoke4:
  AssignVar(0,-22);
  if(Equal(GetDir(),DIR_Left())) AssignVar(0,+22);
  Smoke(Var(0),6,5);
  return(1);




//--Schaden--//

Damage:
  if(OnFire(this())) Call("Crash");
  if(GreaterThan(GetDamage(),40)) Call("Crash");
  return(1);

Crash:
  SetEntrance(1);
  Incinerate();
  SetAction("Crashed");
  if(GreaterThan(GetActTime(),400)) Call("Bumm");
  return(1);

Bumm:
  Exit(AssignVar(0,CreateContents(METL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(METL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(METL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(8PTR)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(8PTL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(8PTR)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(8PTL)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  Exit(AssignVar(0,CreateContents(8PTR)),0,0,0,Sub(Random(10),5),Sub(0,Random(5)),Random(360));
  Incinerate(Var(0));
  CastObjects(DFLM,10,10);
  Sound("Bumm.wav");
  Explode(20,CreateObject(AREU,-10,10));
  Explode(15,CreateObject(AREU,-15,10));
  Explode(15,CreateObject(AREU,15,10));
  Explode(20,CreateObject(AREU,10,10));
  Explode(20,CreateObject(AREU,-10,10));
  Explode(20,CreateObject(AREU,-20,10));
  RemoveObject();
  return(1);

ContainedDigDouble:
  Sound("horn2");
  return(1);

Tuning1:
 SetGraphics ("t1"); 
 Sound("Click");
 return(1);

Tuning2:
 SetGraphics ("t2"); 
 Sound("Click");
 return(1);

MTuning:
  SetLocal(2,Local(2)+Par(0));
  ++Local(3);
  Message("Motor ist jetzt auf Stufe %d getunt!|Maximale Leistung: %d",this(),Local(3),Local(2));
  Sound("Connect");
  return(1);

TuningInfo:
  Message("Motor ist auf Stufe %d getunt.",this(),Local(3));
  return(1);

Lichtschalten:
  	Sound("Click");
	if(an==1) {an=0; c_child(0);}
	else if(an==0) { an=1; c_child(1);}
  	return(1);

func c_child(wert)
{
	if(wert==0 && child!=0) RemoveObject(child);

	if(wert==1 && child==0)
        {
         child=CreateObject(LXEN);
         child -> set_parent(this());
        }
	return(1);
}


/* Produkteigenschaften */

public IsCarProduct: return(1);

/* Forschung */

public GetResearchBase: return(E180);
