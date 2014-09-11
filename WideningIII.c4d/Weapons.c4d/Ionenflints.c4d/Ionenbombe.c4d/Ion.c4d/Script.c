#strict

// MSC-Script //

Hit:
  Smoke(0,0,Random(4));
  AssignRemoval();
  return(1);

Completion:
  SetAction("Fly");
  return(1);

Boom:
  Explode(Sum(Random(25),1));
  return(1);
Chck4Boom:
  if(GreaterThan(GetActTime(),12)) return(Call("Boom"));
  return(1);