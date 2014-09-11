// MSC-Script //

#strict

Initialize:
  DoScore(0, -7);
  return(1);

Hit:
  Sound("GlassBreak2");
  CastObjects(FRG1, 40, 7);
  return(1);

Damage:
  CastObjects(DFLM, 5, 6);
  return(1);




