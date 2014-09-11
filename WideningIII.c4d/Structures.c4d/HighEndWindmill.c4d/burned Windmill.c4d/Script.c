// MSC-Script //
#strict

/*-- Verbranntes Windrad --*/

/* Fundament (Local 9)*/

protected Destruction:
  if (Local(9)) RemoveObject(Local(9));
  return(1);

