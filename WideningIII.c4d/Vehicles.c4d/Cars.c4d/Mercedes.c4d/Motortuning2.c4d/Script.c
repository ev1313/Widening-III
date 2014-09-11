#strict

Where:
  if(Equal(Contained(),0)) return(1);
  if(BitAnd(GetCategory(Contained()),C4D_Vehicle())) return(Call("InVehicle"));
  return(1);

InVehicle:
  if(Local(3,Contained())==1)
  {
    ObjectCall(Contained(),"MTuning",15);
    RemoveObject();
  }
  return(1);

/* Kann chemisch werden */

IsGasProduct: return(1);

/* Forschung */

public GetResearchBase: return(MTP1);
