#strict

// MSC-Script //

Activate:
  SetAction("Fly");
  return(1);

Automatic:
  if (Contained()) SetDir(GetDir(Contained()));
  //if (Not(SEqual(GetAction(),"Fly"))) return(0);
  //SetYDir(10);
  return(1);

SlowDown:
  SetComDir(COMD_Down());
  if(GBackSolid(0,20)) SetAction("Walk");
  SetYDir(10);
  return(1);

ContactBottom:
  SetAction("Walk");
  return(1);

ContactRight:
  SetAction("Walk");
  return(1);
ContactLeft:
  SetAction("Walk");
  return(1);

Hit:
  Sound("RockHit*");
  return(1);

Completion:
  SetAction("Walk");
  SetComDir(COMD_Stop());
  return(1);

Damage:
  if ( LessThan( GetDamage(), 30 ) ) return(0);
  // Crack open
  while (Contents()) Exit(Contents());
  CastObjects(_CF1,1,20,0,-10);
  CastObjects(_CF2,5,20,0,-10);
  Sound("CrateCrack");
  Sound("Blast2");
  RemoveObject();  
  return(1);