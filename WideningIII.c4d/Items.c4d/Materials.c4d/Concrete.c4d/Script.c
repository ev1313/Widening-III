#strict

// MSC-Script //

protected Hit:
  CastPXS("Rock",100,30);
  RemoveObject();
  return(1);

/* Kann chemisch werden */
IsConcreteProduct: return(1);

public GetResearchBase: return(ZEME);
