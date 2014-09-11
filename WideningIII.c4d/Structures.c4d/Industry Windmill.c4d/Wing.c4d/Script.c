// MSC-Script //

#strict

Completion:
  SetR(Random(360));
  return(1);
Wind2Turn:
  DoEnergy( Abs( Mul( GetRDir(),12 ) ) , GetActionTarget() );
  SetRDir( Div( GetWind(),8 ) );
  return(1);
