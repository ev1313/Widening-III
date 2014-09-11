// MSC-Script //

#strict
#include BAS8
#include DOOR

/* Eingangssteuerung */

private SoundOpenDoor:
  return(Sound("GateOpen"));

private SoundCloseDoor:
  return(Sound("GateClose"));
  
protected Collection:
  return(Sound("Clonk"));


/* Produktion */

private func Burning()
{
  // Noch nicht fertig
  if (GetActTime()<1500) return(1);
  // Fertig
  SetAction("Idle");

  // Ausgangsmaterial suchen
  var pOre;
  if (!(pOre=FindContents(RawID()))) return(1);
  // Erz verbrauchen
  RemoveObject(pOre);

  // Produkt auswerfen

  ExitProduct();

  // Sound
  Sound("Pshshsh");
  // Fertig
  return(1);
}


private func ContentsCheck()
{
  // Warten...
  if (!ActIdle()) 
    return(1);
  // Loren ausleeren und rausschicken
  var obj;
  for(var i = 0; obj = Contents(i); i++)
    if(obj->~IsLorry())
      {
      GrabContents(obj);
      SetCommand(obj,"Exit");
      }
  // Erstes Inhaltsobjekt überprüfen
  obj = Contents(0); var id = GetID(obj);
  // Alles außer Mannschaftsmitgliedern, Rohmaterial und Loren sofort auswerfen
  if (obj)
    if ( !(    GetOCF(obj) & OCF_CrewMember()
            || obj->~IsLorry()
            || id==COAL
            || id==WOOD
            || id==RawID() ) )
      if(GetDefFragile(id))
        SetCommand(obj, "Exit");
      else
        Exit(obj,-27,+13,0,-1);
  // Erz prüfen
  if (!FindContents(RawID())) return(1);
  // Holz verbrennen
  if (ContentsCount(WOOD)>1) return(BurnWood());
  // Kohle verbrennen
  if (!(obj=FindContents(COAL))) return(1);
  RemoveObject(obj);
  SetAction("Burning");
  return(1);
}

private func BurnWood()
{
  RemoveObject(FindContents(WOOD));
  RemoveObject(FindContents(WOOD));
  SetAction("Burning");
  return(1);
}


//--------------------------Produktionsscript------------------------------


/* Steuerung */

protected func ContainedUp(object pCaller)
{
  [$TxtProducemetal$|Image=NORM]
  return(StartProduction(pCaller));
}

/* Kontext */

func ContextConstruction(object pCaller)
{
  [$TxtProducemetal$|Image=NORM|Condition=IsBuilt]
  return(StartProduction(pCaller));
}


func HowToProduce (object clonk, id def) {
  AddCommand (clonk, "Wait", 0, 0, 0, 0, 0, 190);
  Production (clonk, def);
}

func StartProduction(object clonk)
{
  // Arbeitsbefehl setzen
  AddCommand(clonk,"Call",this(),NORM,0,0,0,"Production");
  return(1);
}

func Production(object clonk, id idProduct)
{
  // Kein Brennmaterial
  if (!HasFuel())
    // Der Arbeiter soll welches beschaffen
    WorkerAcquireFuel(clonk);

  // Kein Öl im Gebäude
  if (!FindContents( RawID() ))
    {
    // Der Arbeiter soll welches beschaffen
    AddCommand(clonk,"Call",this(),0,0,0,0,"Acquisition", 0, 3);
    AddCommand(clonk,"Put",this(),0,0,0,0,RawID());
    AddCommand(clonk,"Acquire",0,0,0,0,0,RawID(),3);  
    }
  // Fertig
  return(1);
}
  
func WorkerAcquireFuel (object clonk) {
  AddCommand (clonk, "Call", this (), 0, 0, 0, 0, "Acquisition", 0, 3);
  // Wenn Kohle da (Leider noch keine Überprüfung auf Kohleherstellendes Objekt)
  var obj = GetAvailableObject (COAL, this());
  // Oder Kohle kaufbar
  if (!obj)
    if (GetHomebaseMaterial (GetOwner (clonk), COAL))
      if (GetWealth (GetOwner (clonk)) >= GetValue (0, COAL))
        if (FindBase (GetOwner (clonk)))
          obj = 1;
  if (obj) {
    //Kohle reintun
    AddCommand(clonk,"Put",this(),0,0,0,0,COAL);
    //und vorher besorgen
    AddCommand(clonk,"Acquire",0,0,0,this(),0,COAL);
    return(1);
  }
  // ansonsten Holz verbrennen
  // ..zweites holen
  AddCommand(clonk,"Call",this(),0,0,0,0,"SupportWithWOOD", 0, 1);
  AddCommand(clonk,"Put",this(),0,0,0,0,WOOD);
  AddCommand(clonk,"Acquire",0,0,0,this(),0,WOOD);
  // Damit er es nicht nochmal holt:
  AddCommand(clonk,"Wait",0,0,0,0,0,10);
  // Erstes Holzstück holen...
  AddCommand(clonk,"Put",this(),0,0,0,0,WOOD);
  AddCommand(clonk,"Acquire",0,0,0,this(),0,WOOD);
}    


func SupportWithWOODFailed(pClonk)
{
  // Hat nicht geklappt, also mit Kohle versuchen
  AddCommand(pClonk, "Call", this(), 0, 0, 0, 0, "SupportWithCOAL", 0, 1);
  AddCommand(pClonk, "Put", this(), 0, 0, 0, 0, COAL);
  AddCommand(pClonk, "Acquire", 0, 0, 0, this(), 0, COAL);
  return(1);
}

func SupportWithCOALFailed(pClonk) //Öl ist ja in Raffinerien kein beliebter Brennstoff mehr...
{
  AcquisitionFailed(pClonk);
  return(1);
}


func Acquisition(object pWorker)
{
  // Materialbeschaffung erfolgreich
  return(1);
}

func AcquisitionFailed(object pWorker)
{
  // Materialbeschaffung fehlgeschlagen: Meldung ausgeben
  if (!FindContents(OBRL)) 
    return(Message("$TxtNooreavailable$", pWorker));
  Message("$TxtNeedsfueltoburn$", pWorker);
  return(1);
}

// Einstellungen

func RawID() { return(OBRL); } //Ausgangsmaterial
func SupportWithCOAL() { return(1); } //Kohle unterstützt?
func SupportWithWOOD() { return(1); } //Holz unterstützt?

func HasFuel() //Bedingungen (Energie/Brennmaterial)
{
  if (ContentsCount(COAL)>0) return(1);
  if (ContentsCount(WOOD)>1) return(1);
  return(0);  
}

func ExitProduct() //Produkte
{
  Exit(CreateContents(NORM), 20,+60,0, 0);
  Exit(CreateContents(GRUN), 20,+60,0, 0);
  Exit(CreateContents(TOPS), 20,+60,0, 0);
  Exit(CreateContents(TOPS), 20,+60,0, 0);
  Exit(CreateContents(MDST), 20,+60,0, 0);
  Exit(CreateContents(MDST), 20,+60,0, 0);
  Exit(CreateContents(MDST), 20,+60,0, 0);
  Exit(CreateContents(_NH3), 20,+60,0, 0);
  Exit(CreateContents(ABWA), 20,+60,0, 0);
  Exit(CreateContents(ABWA), 20,+60,0, 0);
  Exit(CreateContents(SRST), 20,+60,0, 0);
  Exit(CreateContents(BARL), 20,+60,0, 0);
  return(1);  
}

func IsBuilt() {
  return(GetCon() >= 100);
}
