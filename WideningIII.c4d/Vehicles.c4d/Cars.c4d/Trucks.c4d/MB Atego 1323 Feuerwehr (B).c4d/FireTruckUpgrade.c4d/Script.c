// MSC-Script //

#strict



func Where()
{
  if(!Contained()) return(1);
  if(GetCategory(Contained()) & C4D_Vehicle()) return(Call("InVehicle"));
  return(1);
}

func InVehicle()
{
  if(GetID(Contained()) == AC23) if(Contained() ->~ Upgrade()) RemoveObject();
  return(1);
}

/* Kann chemisch werden */
IsGasProduct: return(1);

/* Forschung */

public GetResearchBase: return(AC23);


// MSC-Script //