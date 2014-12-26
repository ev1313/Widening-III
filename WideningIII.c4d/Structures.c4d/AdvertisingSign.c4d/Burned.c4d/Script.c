/*-- verbrannt --*/

#strict

/* Fundament (Local 9)*/

protected Construction:
  SetLocal(9,CreateObject(BAS1,0,+8,GetOwner()));
  return(1);
  
protected Destruction:
  if (Local(9)) RemoveObject(Local(9));
  return(1);

