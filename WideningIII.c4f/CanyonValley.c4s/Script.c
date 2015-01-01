/*-- Canyon Valley --*/

#strict 2

#include CHIC

func Initialize()
{
  Schedule("OpenMenu()", 35);
  return true;
}

func OpenMenu()
{
  if(GetPlayerCount() > 1)
    InitializeChooser([GLDM, MELE, OILP, SDOP, EXTR], [[VALG, 150], [MONE, 150]]);
  else
    InitializeChooser([GLDM, OILP, SDOP, EXTR], [[VALG, 150], [MONE, 150]]);
}

