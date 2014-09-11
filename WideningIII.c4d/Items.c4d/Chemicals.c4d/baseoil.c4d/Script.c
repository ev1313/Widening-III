// MSC-Script //

#strict

Hit:
  Sound("GlassBreak2");
  CastObjects(FRG1, 40, 7);
  RemoveObject();
  return(1);

Damage:
  CastObjects(DFLM, 5, 6);
  RemoveObject();
  return(1);

IsOilProduct: return(1);

