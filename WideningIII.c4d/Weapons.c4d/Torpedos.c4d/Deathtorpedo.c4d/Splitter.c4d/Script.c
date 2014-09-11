#strict
// MSC-Script //

Hit:
  Explode(20);
  Sound("HEADCRAS");
  return(1);

Check:
  SetAction("Delay");
  return(1);

Checkit:
  if(SetVar(0,FindObject(0,+1,0,0,0,OCF_Living()))) if(Not(Contained(Var(0)))) Hit();
  return(1);
