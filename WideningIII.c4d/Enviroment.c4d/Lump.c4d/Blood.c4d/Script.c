// MSC-Script //

#strict

Process:
  if (GreaterThan(GetActTime(),Random(400))) return(AssignRemoval());
  return(1);
Completion:
  SetAction("Sparkle");
  return(1);

// MSC-Script //