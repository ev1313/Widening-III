/*-- Spitzberg --*/

#strict 2

#include CHIC

/* Initialisierung */

protected func Initialize()
{
  //SetGamma(RGB(10,9,1), RGB(161,157,129), RGB(255,254,210) ); // Prä-Lenseflare-Werte
  SetGamma(RGB(5,5,1), RGB(140,139,129), RGB(255,255,235) );
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
