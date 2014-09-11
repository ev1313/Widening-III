// MSC-Script //

#strict

Hit:
  Sound("GlassBreak");
  if (Random(10)) Smoke(+50,-1,1);
  Smoke(-1,-1,Sum(5,Random(10)));
  if (Random(10)) Smoke(+50,-1,1);
  Smoke(-1,-1,Sum(5,Random(10)));
  if (Random(10)) Smoke(+50,-1,1);
  Smoke(-1,-1,Sum(5,Random(10)));
  CastObjects(GIF2, 5, 10);
  RemoveObject();
  return(1);

Damage:
  Sound("GlassBreak");
  if (Random(10)) Smoke(+50,-1,1);
  Smoke(-1,-1,Sum(5,Random(10)));
  if (Random(10)) Smoke(+50,-1,1);
  Smoke(-1,-1,Sum(5,Random(10)));
  if (Random(10)) Smoke(+50,-1,1);
  Smoke(-1,-1,Sum(5,Random(10)));
  CastObjects(GIF2, 5, 10);
  RemoveObject();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);

// MSC-Script // 
  
  
