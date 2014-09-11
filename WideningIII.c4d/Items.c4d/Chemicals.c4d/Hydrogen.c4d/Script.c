// MSC-Script //

#strict

Hit:
  Sound("GlassBreak");
  CastObjects(GIF3,2,70);
  RemoveObject();
  return(1);

Damage:
  Sound("GlassBreak");
  CastObjects(GIF3,2,70);
  RemoveObject();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);

// MSC-Script // 

 
  
  