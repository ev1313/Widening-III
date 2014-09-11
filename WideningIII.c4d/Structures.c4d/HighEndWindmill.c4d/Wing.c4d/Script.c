// MSC-Script //

#strict

Completion:
  SetR(Random(360));
  return(1);
Wind2Turn:
  DoEnergy( Abs( Mul( GetRDir(),18 ) ) , GetActionTarget() );
  SetRDir( Div( GetWind(),10 ) );
  return(1);
