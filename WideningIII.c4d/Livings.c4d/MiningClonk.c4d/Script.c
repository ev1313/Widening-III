/* --Bergarbeiter-- */

#strict
#include CLNK

protected Death:
  Sound("SFTot");
  DeathAnnounce();
  return(1);

/* Itemlimit */
public func MaxContentsCount() { return(10); }


private func Chopping()
{
  Sound("Chop*");
  CastParticles("Dust",Random(3)+1,6,-8+16*GetDir(),1,10,12);
  return(1);
}

public ControlSpecial:
  ObjectCall(Contents(0,this()),"StopLoading");
  if(Not(ShiftContents())) return(0);
  ObjectCall(Contents(0,this()),"CheckLoading");
  Sound("Change"); 
  return(1);


/*----------------------------- Kreditkarte -----------------------------------*/
//Es war mal ein Objekt, aber jetzt integrier ichs einfach...

local server;
local server2; //anderer Server
local clonk;
local transfer; //saver für den Betrag bei Transfer1()

local best; //Bestellung

func ContextCreditCard(caller)
{
 [Internet|Image=BEST]

 caller=this();
 clonk=this();

 CreateMenu(GetID(),caller,this());
 AddMenuItem("Geldgeschäfte","Banking", CCM1,caller,0,caller);
 AddMenuItem("Einkaufen","Shop", CCM2,caller,0,0);
}

func Shop(i,mode) //Einkaufen
{
 //Bestellung anlegen falls nicht da
 if(!best) best=CreateObject(BEST,0,0,-1);

 //Verfügbarer Platz
 var room = best -> Room();
 //Preis der Bestellung
 var price = best -> ContValue();

 //Das Geld vom konto kann man auch verwenden

 server = FindObjectOwner(CNTS,GetOwner());
 if(!server) server = CreateObject(CNTS,0,0,GetOwner());
 var cash = server -> Transaction(); 
 var cashbar = GetWealth(GetOwner());


 //Baumaterial
 if(mode == 1)
 {
  CreateMenu(GetID(),clonk,this());
  //Liste der Gegenstände
  AddMenuItem("%s","Add",WOOD,clonk);
  AddMenuItem("%s","Add",COAL,clonk);
  AddMenuItem("%s","Add",ROCK,clonk);
  AddMenuItem("%s","Add",CNCR,clonk);
  AddMenuItem("%s","Add",METL,clonk);
  AddMenuItem("%s","Add",ALU1,clonk);
  AddMenuItem("%s","Add",KUPF,clonk);
  AddMenuItem("%s","Add",STAH,clonk);
  AddMenuItem("%s","Add",CHRO,clonk);
  AddMenuItem("%s","Add",KNST,clonk);
  AddMenuItem("%s","Add",CNKT,clonk);
  AddMenuItem("%s","Add",LNKT,clonk);
  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Shop",CCM3,clonk,0,0);
  return(1);
 }

 //Ölprodukte
 if(mode == 2)
 {
  CreateMenu(GetID(),clonk,this());
  //Liste der Gegenstände
  AddMenuItem("%s","Add",OBRL,clonk);
  AddMenuItem("%s","Add",DIES,clonk);
  AddMenuItem("%s","Add",NORM,clonk);
  AddMenuItem("%s","Add",SUPE,clonk);
  AddMenuItem("%s","Add",SUPP,clonk);
  AddMenuItem("%s","Add",HOIL,clonk);
  AddMenuItem("%s","Add",LMAS,clonk);
  AddMenuItem("%s","Add",SMAS,clonk);
  AddMenuItem("%s","Add",0W40,clonk);
  AddMenuItem("%s","Add",1W40,clonk);
  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Shop",CCM3,clonk,0,0);
  return(1);
 }

 //Sprengstoffe und Chemikalien
 if(mode == 8)
 {
  CreateMenu(GetID(),clonk,this());
  //Liste der Gegenstände

  AddMenuItem("%s","Add",FLNT,clonk);
  AddMenuItem("%s","Add",SFLN,clonk);
  AddMenuItem("%s","Add",TFLN,clonk);
  AddMenuItem("%s","Add",MSFL,clonk);
  AddMenuItem("%s","Add",MSHF,clonk);
  AddMenuItem("%s","Add",PLUT,clonk);
  AddMenuItem("%s","Add",_NH3,clonk);
  AddMenuItem("%s","Add",_H2G,clonk);
  AddMenuItem("%s","Add",_N2G,clonk);
  AddMenuItem("%s","Add",_O2G,clonk);
  AddMenuItem("%s","Add",_SO2,clonk);
  AddMenuItem("%s","Add",GRUN,clonk);
  AddMenuItem("%s","Add",TOPS,clonk);
  AddMenuItem("%s","Add",MDST,clonk);
  AddMenuItem("%s","Add",BITU,clonk);
  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Shop",CCM3,clonk,0,0);
  return(1);
 }

 if(mode == 3) //Spezialwaffen
 {
  CreateMenu(GetID(),clonk,this());
  //Liste der Gegenstände
  AddMenuItem("%s","Add",IBOM,clonk);
  AddMenuItem("%s","Add",KIFL,clonk);
  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Shop",CCM3,clonk,0,0);
  return(1);
 }

 if(mode == 4) //Vehikel (Auswahl)
 {
  CreateMenu(GetID(),clonk,this());
  //Liste der Gegenstände
  AddMenuItem("%s","Add",LORG,clonk,0,1);
  AddMenuItem("%s","Add",OA14,clonk,0,1);
  AddMenuItem("%s","Add",OAV7,clonk,0,1);
  AddMenuItem("%s","Add",OV18,clonk,0,1);
  AddMenuItem("%s","Add",OZ16,clonk,0,1);
  AddMenuItem("%s","Add",C18T,clonk,0,1);
  AddMenuItem("%s","Add",E180,clonk,0,1);
  AddMenuItem("%s","Add",A815,clonk,0,1);
  AddMenuItem("%s","Add",ACTR,clonk,0,1);
  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Shop",CCM3,clonk,0,0);
  return(1);
 }

 //Bestellung einsehen
 if(mode == 5)
 {
  //Preis und Platz angeben
  PlayerMessage(GetOwner(),"Aktueller Preis: %d Clunker|%d von 20 Plätzen belegt",this(),price,20-room);

  //Inhalte zeigen
  var number = 20-room;
  if(best -> HasVehicle()) number=1;
  CreateMenu(GetID(),clonk,this());
  while(number--) AddMenuItem("%s","Add",GetID(Contents(number,best)),clonk,0,11);

  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Shop",CCM3,clonk,0,0);
  return(1);
 }

 //Bestellung löschen
 if(mode == 6)
 {
  PlayerMessage(GetOwner(),"Bestellung gelöscht",this());
  RemoveObject(best);
  return(Shop());
 }

 //Bestellung senden
 if(mode == 7)
 {
  if(cashbar < price)
  {
   var secondpay = price - cashbar;
   PlayerMessage(GetOwner(),"Es wurden %d Clunker von Ihrem MSC-Konto abgebucht, um die Rechnung zu bezahlen.",this(),secondpay);
   server -> Transaction(-secondpay);
   DoWealth(GetOwner(),secondpay);
  }
  DoWealth(GetOwner(),-price);
  best -> Deliver(GetOwner());
  return(1);
 }

 //Startmenü
 CreateMenu(GetID(),clonk,this());
 if(room) AddMenuItem("Baumaterial","Shop",METL,clonk,0,1);
 if(room) AddMenuItem("Ölprodukte","Shop",0W40,clonk,0,2);
 if(room) AddMenuItem("Sprengstoffe und Chemikalien","Shop",SFLN,clonk,0,8);
 if(room) AddMenuItem("Spezialwaffen","Shop",IBOM,clonk,0,3);
 if(room == 20) AddMenuItem("Fahrzeuge","Shop",LORG,clonk,0,4);
 if(room < 20) AddMenuItem("Bestellung einsehen","Shop",KIST,clonk,0,5);
 if(room < 20) AddMenuItem("Bestellung löschen","Shop",CCM4,clonk,0,6);
 //Bezahlbar? na dann...
 if(cash+cashbar >= price && room < 20) AddMenuItem("Bestellung senden","Shop",CCM5,clonk,0,7);

}

func Add(id,number)
{
 //Verfügbarer Platz
 var room = best -> Room();

 //Anzahl noch nicht festgelegt
 if(!number)
 {
  CreateMenu(GetID(),clonk,this());
  if(room) AddMenuItem("1","Add",id,clonk,0,1);
  if(room >= 5) AddMenuItem("5","Add",id,clonk,0,5);
  if(room >= 10) AddMenuItem("10","Add",id,clonk,0,10);
  return(1);
 }

 if(number <= 10) while(number--) best -> CreateContents(id);

 //Objekt löschen
 if(number==11)
 {
  RemoveObject(FindContents(id,best)); 
  //Zurück zum Menü
  Shop(GetID(),5);
  return(1);
 }

 //Zurück zum Menü
 Shop();

}


func Banking(i,caller) //Geldgeschäfte
{

 //Konto anwählen / drauf zugreifen
 server = FindObjectOwner(CNTS,GetOwner());
 if(!server) server = CreateObject(CNTS,0,0,GetOwner());

 //Alle wichtigen Werte
 var cash = server -> Transaction(); 
 var cashbar = GetWealth(GetOwner());
 var seriousity = GetScore(GetOwner()); //Kredite nur für abgesicherte Kunden.

 // Kredit nicht gezahlt?
 var anger = server -> Anger();
 if(anger > 5)
 {
  PlayerMessage(GetOwner(),"Ihr MSC-Konto ist in hohem Maße belastet.|Wir haben kein weiteres Interesse an Geschäften mit Ihnen.",this());
  return(Incinerate());
 }
 if(anger > 3)
 {
  PlayerMessage(GetOwner(),"Bitte Zahlen sie ihren Kredit zurück!",this());
 }
 if(anger && anger < 4 )
 {
  PlayerMessage(GetOwner(),"Bitte denken sie an ihren Kredit.",this());
 }

 //Kontostand anzeigen

 CreateMenu(GetID(),caller,this());

 AddMenuItem("Kontostand abfragen","Menu",CCM9,caller,0,4);
 if(cash)AddMenuItem("Geld übertragen","Menu",CCM8,caller,0,0);
 if(cash) AddMenuItem("Geld abheben","Menu",CCM6,caller,0,1);
 if(cashbar) AddMenuItem("Geld einzahlen","Menu",CCM7,caller,0,2);
 if(cashbar < 10 && cash > -1 && cash < 10) AddMenuItem("Kredit anfordern","Menu",CCM1,caller,0,3);

}

func Menu(i,mode)
{
 CreateMenu(GetID(),clonk,this());

 //Alle wichtigen Werte
 var cash = server -> Transaction(); 
 var cashbar = GetWealth(GetOwner());
 var seriousity = GetScore(GetOwner()); //Kredite nur für abgesicherte Kunden.

 if(mode==0){
  if(cash >= 10) AddMenuItem("10 Clunker","Transfer1",CC10,clonk,0,10);
  if(cash >= 30) AddMenuItem("30 Clunker","Transfer1",CC30,clonk,0,30);
  if(cash >= 50) AddMenuItem("50 Clunker","Transfer1",CC50,clonk,0,50);
  if(cash >= 100) AddMenuItem("100 Clunker","Transfer1",CC1X,clonk,0,100);
  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Banking",CCM3,clonk,0,clonk);
  return(1);
 }

 if(mode==1){
  if(cash >= 10) AddMenuItem("10 Clunker","Take",CC10,clonk,0,10);
  if(cash >= 30) AddMenuItem("30 Clunker","Take",CC30,clonk,0,30);
  if(cash >= 50) AddMenuItem("50 Clunker","Take",CC50,clonk,0,50);
  if(cash >= 100) AddMenuItem("100 Clunker","Take",CC1X,clonk,0,100);
  if(cash >= 1) AddMenuItem("Alles","Take",CCAL,clonk,0,cash);
  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Banking",CCM3,clonk,0,clonk);
  return(1);
 }

 if(mode==2){
  if(cashbar >= 10) AddMenuItem("10 Clunker","Give",CC10,clonk,0,10);
  if(cashbar >= 30) AddMenuItem("30 Clunker","Give",CC30,clonk,0,30);
  if(cashbar >= 50) AddMenuItem("50 Clunker","Give",CC50,clonk,0,50);
  if(cashbar >= 100) AddMenuItem("100 Clunker","Give",CC1X,clonk,0,100);
  if(cashbar >= 1) AddMenuItem("Alles","Give",CCAL,clonk,0,cashbar);
  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Banking",CCM3,clonk,0,clonk);
  return(1);
 }

 if(mode==3){
  if(seriousity >= 10) AddMenuItem("10 Clunker","Credit",CC10,clonk,0,10);
  if(seriousity >= 30) AddMenuItem("30 Clunker","Credit",CC30,clonk,0,30);
  if(seriousity >= 50) AddMenuItem("50 Clunker","Credit",CC50,clonk,0,50);
  if(seriousity >= 100) AddMenuItem("100 Clunker","Credit",CC1X,clonk,0,100);
  //Rückkehr zum menü anbieten
  AddMenuItem("Zurück","Banking",CCM3,clonk,0,clonk);
  return(1);
 }

 if(mode==4)
 {
  PlayerMessage(GetOwner(),"Kontostand: %d Clunker",this(),cash);
  Banking(GetID(),clonk);
 }

}

// Geschäfte mit der Bank

func Give(i,value)
{
 DoWealth(GetOwner(),-value);
 server -> Transaction(value);
 PlayerMessage(GetOwner(),"Betrag eingezahlt: %d",this(),value);
 Banking(GetID(),clonk);
}

func Take(i,value)
{
 DoWealth(GetOwner(),value);
 server -> Transaction(-value);
 PlayerMessage(GetOwner(),"Betrag abgehoben: %d",this(),value);
 Banking(GetID(),clonk);
}

func Credit(i,value)
{
 DoWealth(GetOwner(),value);
 server -> Transaction(-value,1);
 PlayerMessage(GetOwner(),"Kredit bewilligt: %d",this(),value);
 Banking(GetID(),clonk);
}

// Transaktionen

func Transfer1(i,value)
{
 transfer=value;

 var maxplrs=11; //Maximale Anzahl der Spieler nach NET2/RAGE
 var name;

 CreateMenu(GetID(),clonk,this());
 while(maxplrs > -1)
 {
  if (GetOwner() != maxplrs) if(name = GetPlayerName(maxplrs))  AddMenuItem(GetPlayerName(maxplrs),"Transfer2",GetID(),clonk,0,maxplrs);
  maxplrs--;
 }
 //Rückkehr zum menü anbieten
 AddMenuItem("Zurück","Banking",CCM3,clonk,0,clonk);
 return(1);
}

func Transfer2(i,plr)
{
 //Konto anwählen / erstellen
 server2 = FindObjectOwner(CNTS,plr);
 if(!server2) server2 = CreateObject(CNTS,0,0,plr);

 server -> Transaction(-transfer);
 server2 -> Transaction(transfer);

 PlayerMessage(GetOwner(),"Betrag überwiesen: %d",this(),transfer);
 PlayerMessage(plr,"Betrag von %s überwiesen: %d",0,GetPlayerName(GetOwner()),transfer);

 Banking(GetID(),clonk);
}

/*-------------------------------die Abrissfunktion------------------------ */

func ContextDemolish()
{
 [Abriss|Image=BERG|Condition=CanDemolish]
 var v;
 CreateMenu(BERG);
 v = FindObject2(Find_Owner(GetOwner()),Find_Category(C4D_Structure()),Find_OCF(OCF_Fullcon()),Find_Exclude(v),Find_Distance(70));
  if(v) AddMenuItem("Abriss: %s","Demolish",GetID(v),this(),0,v);
}

func CanDemolish()
{
 if(FindObjectOwner(MC_D,GetOwner())) return(0);
 var v;
 v = FindObject2(Find_Owner(GetOwner()),Find_Category(C4D_Structure()),Find_OCF(OCF_Fullcon()),Find_Exclude(v),Find_Distance(70));
  if(v) return(1);
}

func Demolish(i,obj)
{
 if(!obj) return(1); //Sicherung
 var v = CreateObject(MC_D,0,0,GetOwner());
 v -> Target(obj);
}

func ContextStopDemolish()
{
 [Abriss stoppen|Image=BERG|Condition=CanStopDemolish]
 RemoveObject(FindObjectOwner(MC_D,GetOwner()));
}

func CanStopDemolish()
{
 if(FindObjectOwner(MC_D,GetOwner())) return(1);
}