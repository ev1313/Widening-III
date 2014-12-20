/*-- Neues Szenario --*/

#strict 2

static goalChosen;
static newMenu;
static curMenu;

static const MENU_NONE = -1;
static const MENU_MAIN = 0;
static const MENU_GOALS  = 1;
static const MENU_MULTI_GOAL  = 2;

static chooseAbleGoals;
static chooseAbleGoalsMulti;
static mainMenuSel;

func InitializeChooser(array chooseAbles, chooseAblesMulti)
{
  chooseAbleGoals = chooseAbles;
  chooseAbleGoalsMulti = chooseAblesMulti;
  goalChosen = false;
  newMenu = false;
  curMenu = MENU_NONE;
  ChooserMenu();
  return(1);
}

func ChooserMenu()
{
  if(!GetCursor(0))
    Schedule("ChooserMenu()", 35);
  else
  {
    if(curMenu == MENU_NONE)
      Log("$StartSettings$", GetTaggedPlayerName(0));
    curMenu = MENU_MAIN;
    newMenu = true;
    CreateMenu(CHIC, GetCursor(0), 0, 0, "$Settings$", 0, C4MN_Style_Context, true);
    AddMenuItem("$Goals$", "Goals", CHIC, GetCursor(0));
    for(var i = 0; i < GetLength(chooseAbleGoalsMulti); ++i)
    {
      AddMenuItem("%s", "MultiGoal", chooseAbleGoalsMulti[i][0], GetCursor(0), 0, i, GetDesc(0, chooseAbleGoalsMulti[i][0]));
    }
    AddMenuItem("$Finish$", "FinishChooser", CHIC, GetCursor(0), 0, 0, "",2, 3);
    newMenu = false;
  }
}

func FinishChooser()
{
  goalChosen = true;
  CloseMenu(GetCursor(0));
  for(var goal in chooseAbleGoalsMulti)
  {
    RemoveAll(goal[0]);
    CastObjects(goal[0], goal[2]);
  }
  Log("$FinishSettings$", GetTaggedPlayerName(0));
}

func MenuQueryCancel(int selection, object menuObj)
{
  if(newMenu)
    return false;
  if(curMenu == MENU_GOALS || curMenu == MENU_MULTI_GOAL)
  {
    ChooserMenu();
    SelectMenuItem(mainMenuSel, GetCursor(0));
    return true;
  }
  if(menuObj != GetCursor(0))
    return false;
  return !goalChosen;
}

func Goals()
{
  newMenu = true;
  if(curMenu == MENU_MAIN) mainMenuSel = GetMenuSelection(GetCursor(0));
  CloseMenu(GetCursor(0));
  curMenu = MENU_GOALS;
  CreateMenu(CHIC, GetCursor(0), 0, 0, "$NoGoals", 0, C4MN_Style_Normal, true);
  for(var goal in chooseAbleGoals)
  {
    var count = ObjectCount(goal);
    var tempObj = CreateObject(goal, 0, 0, NO_OWNER);
    if(count)
    {
      SetGraphics("Check", tempObj, CHIC, 1, GFXOV_MODE_Picture);
      SetObjDrawTransform(650,0,5000,0,650,5000, tempObj, 1);
    }
    AddMenuItem("%s", "ToggleGoal", goal, GetCursor(0), 0, 0, GetDesc(0, goal), 4, tempObj);
    if(tempObj) RemoveObject(tempObj);
  }
  newMenu = false;
}

func ToggleGoal(id id)
{
  if(ObjectCount(id))
    RemoveAll(id);
  else
    CreateObject(id, 0, 0, NO_OWNER);
  var sel = GetMenuSelection(GetCursor(0));
  Goals();
  SelectMenuItem(sel, GetCursor(0));
}

func MultiGoal(id id, int index, int sel)
{
  newMenu = true;
  if(curMenu == MENU_MAIN) mainMenuSel = GetMenuSelection(GetCursor(0));
  CloseMenu(GetCursor(0));
  curMenu = MENU_MULTI_GOAL;
  CreateMenu(id, GetCursor(0), 0, 0, Format("%dx %s", chooseAbleGoalsMulti[index][2], GetName(0, id)), 0, C4MN_Style_Context, true);
  if(chooseAbleGoalsMulti[index][2] < chooseAbleGoalsMulti[index][1]) AddMenuItem("$More$", Format("(++chooseAbleGoalsMulti[%d][2] || true) && MultiGoal(%i, %d, GetMenuSelection(GetCursor(0)))", index, id, index), CHIC, GetCursor(0), 0, 0, "", 2, 1);
  if(chooseAbleGoalsMulti[index][2]) AddMenuItem("$Less$", Format("(--chooseAbleGoalsMulti[%d][2] || true) && MultiGoal(%i, %d, GetMenuSelection(GetCursor(0)))", index, id, index), CHIC, GetCursor(0), 0, 0, "", 2, 2);
  SelectMenuItem(sel, GetCursor(0));
  newMenu = false;
}
