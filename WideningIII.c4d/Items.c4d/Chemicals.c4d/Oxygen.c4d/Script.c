// MSC-Script //

#strict

Hit:
  Sound("GlassBreak");
  CastObjects(GIF4,2,20);
  RemoveObject();
  return(1);

Damage:
  Sound("GlassBreak");
  CastObjects(GIF4,2,20);
  RemoveObject();
  return(1);

/* Kann chemisch werden */
IsChemicalProduct: return(1);

// MSC-Script // 

 
  
  