/*--- Flint ---*/

#strict

Initialize:
  SetAction("Start");
  SetOwner(-1);
  return(1);

End:
  RemoveObject();
  return(1);

protected Hit:
  RemoveObject();
  return(1);

