/*--- Lava ---*/

#strict

local mat;

protected func Initialize() {
  SetAction("Evaporate");
  SetCon(Random(50)+25);
  return(1);
}
  
protected func Hit()
{
	if(!mat) mat="DuroLava";
  CastPXS(mat, GetCon()/2, 35);
  RemoveObject();
  return(1);
}

private func SmokeTrail()
{
  Smoke(0, 0, 5);
  Smoke(0, -5, Random(7));
  return(1);
}
  
