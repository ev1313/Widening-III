/*-- Feuer und Stahl --*/

#strict

static TargetScore;

func Initialize() {
  CreateObject(DRAI,1700,2600,-1); //Abfluss im Vulkan
  CreateObject(DRAI,1800,2600,-1); //Abfluss im Vulkan
  CreateObject(DRAI,1900,2600,-1); //Abfluss im Vulkan
  TargetScore = 10000; //Punkte
  ScriptGo(1);
  return(1);
}

func Script1()
{

  var iPlayers,i,overall;
  for (iPlayers = GetPlayerCount(); iPlayers; i++)
    if (GetPlayerName(i))
    {
      iPlayers--;
      overall=overall+GetPlrValueGain(i);
    }
  if(overall < TargetScore) return(0);

  Sound("Trumpet");
  GameOver(50);
  return(ScriptGo(0));
}

func Script10()
{
  if(!Random(120)) WeatherChange();
  if(!Random(2000)) return(LavaHail());
  goto(1);
  return(1);
}

func WeatherChange()
 {

  if(!FindObject(FXP1))
  {
   for(var i=RandomX(4,8); i>0; --i)
     {
     var pRain=CreateObject(FXP1,LandscapeWidth()/2,-50,-1);
     pRain->~Activate(Material("DuroLava"), LandscapeWidth(), 20);
     }
   return(1);
  }
  else return(RemoveAll(FXP1));
 }

/*--- Event: Lavaregen ---*/

func LavaHail()
{
 Message("Der Nachbarvulkan ist ausgebrochen!");
 var r = Random(10);

 if(r <= 5) goto(85);
 else goto (185);
}

func Script100()
{
 Sound("Lava*");
 var i=Random(10)+5;
 while (i--)
 {
  var lava = CreateObject(LAVA,RandomX(LandscapeWidth()/2,LandscapeWidth()),5,-1);
  SetXDir(RandomX(-20,-1),lava);
  SetYDir(RandomX(-20,1),lava);
 }
 if(!Random(20)) goto(1);
 else goto(99);
}

func Script200()
{
 Sound("Lava*");
 var i=Random(10)+5;
 while (i--)
 {
  var lava = CreateObject(LAVA,RandomX(0,LandscapeWidth()/2),5,-1);
  SetXDir(RandomX(20,1),lava);
  SetYDir(RandomX(-20,1),lava);
 }
 if(!Random(20)) goto(1);
 else goto(199);
}