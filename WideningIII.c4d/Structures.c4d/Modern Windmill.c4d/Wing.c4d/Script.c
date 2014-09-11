
#strict

Completion:
  SetR(Random(360));
  return(1);
Wind2Turn:
  DoEnergy( Abs( Mul( GetRDir(),6 ) ) , GetActionTarget() );
  SetRDir( Div( GetWind(),6 ) );
  return(1);
