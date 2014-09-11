/*-- Kontoserver --*/

#strict

local cash; //Kontostand, der natürliche Feind des Clonks...
local anger; //Die Geduld der reichen Clonks da oben 0 = OK 5 = Kontosperre

func Transaction(value,credit){
 if(!value) return(cash); // 0 = Anfrage
 else
 {
  return(cash=cash+value);
 }
}

func Anger() { return(anger); }

func Check()
{

 if(anger > 5) return(0);

 //Zinsen

 var rate;

 if(cash > 25) rate=100;
 if(cash > 50) rate=100;
 if(cash > 100) rate=101;

 if(cash < 0) rate = 104;
 if(cash < -25) rate = 106;
 if(cash < -50) rate = 110;
 if(cash < -100) rate = 118;

 cash=cash*rate/100;

 if(cash < 0)
 {
  var bar = GetWealth(GetOwner());
  var rate = -cash/10;
  if(bar < rate) return(anger++);
  DoWealth(GetOwner(),-rate);
  cash=cash+rate;
 }

 if(anger) anger=0;

 return(1);
}
