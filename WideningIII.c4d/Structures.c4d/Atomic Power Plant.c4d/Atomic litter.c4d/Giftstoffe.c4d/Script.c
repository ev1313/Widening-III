#strict

Initialize:
  DoScore(0, -1);
  return(1);

Hit:
  //Augen auf, ich komme!!!
  Smoke(0,0,Random(10));
  AssignRemoval();
  Call("Boom");
  return(1);

Completion:
  SetAction("Fly");
  return(1);

Boom:
  DoEnergy(Sum(Random(12),1));
  return(1);
Chck4Boom:
  if(GreaterThan(GetActTime(),80)) return(Call("Boom"));
  return(1);