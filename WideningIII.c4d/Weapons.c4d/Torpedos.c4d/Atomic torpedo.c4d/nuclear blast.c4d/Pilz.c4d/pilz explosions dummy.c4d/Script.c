/*-- Explosions Dummy  --*/

#strict

protected Initialize:
	local kiddie_modus;
	kiddie_modus=0;
	local count;
	count=5;
	SetAction("LOOP");
  return(1);
	

protected countdown:
	--count;
	if(kiddie_modus == 0)
	{
		if(LessThan(count,0))  Explode(50);
	}
	if(kiddie_modus == 1)
	{
		if(LessThan(count,0))  Message("B",this());
		if(LessThan(count,-100))  RemoveObject();
	}

	return(1);
nicht_markieren: return(1);
