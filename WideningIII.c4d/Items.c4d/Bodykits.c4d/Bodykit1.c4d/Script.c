// MSC-Script //

#strict



Where:
  if(Equal(Contained(),0)) return(1);
  if(BitAnd(GetCategory(Contained()),C4D_Vehicle())) return(Call("InVehicle"));
  return(1);

InVehicle:
  if(Equal(ObjectCall(Contained(),"Tuning1",20),1)) RemoveObject();
  return(1);


/* Kann chemisch werden */
IsGasProduct: return(1);

/* Forschung */

public GetResearchBase: return(WRKS);


// MSC-Script //