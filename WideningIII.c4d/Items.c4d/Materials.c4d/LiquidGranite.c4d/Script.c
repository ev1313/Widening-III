// MSC-Script //

#strict

protected Hit:
  CastPXS("Granite",150,30);
  RemoveObject();
  return(1);

/* Kann chemisch werden */
IsConcreteProduct: return(1);

public GetResearchBase: return(CNCR);

