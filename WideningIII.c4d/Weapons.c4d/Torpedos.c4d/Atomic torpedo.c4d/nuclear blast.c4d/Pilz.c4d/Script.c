// MSC-Script //
#strict



	
protected Initialize:
	Sound("NukeBlast");
	DoCon(-90,CreateObject(ABP1,0,-50,-1));
	CreateObject(ABFO,0,0,-1);
	local yc;
	yc=10;
	ObjectCall(CreateObject(ABDW,0,0,-1),"nach_rechts");
	ObjectCall(CreateObject(ABDW,0,0,-1),"nach_links");

	Smoke(Random(80)-40,Random(80)-40,100);
	Smoke(Random(80)-40,Random(80)-40,100);
	Smoke(Random(80)-40,Random(80)-40,100);
	Smoke(Random(80)-40,Random(80)-40,100);
	Smoke(Random(80)-40,Random(80)-40,100);
	Smoke(Random(80)-40,Random(80)-40,100);
	Smoke(Random(80)-40,Random(80)-40,100);
	Smoke(Random(80)-40,Random(80)-40,100);
	Smoke(Random(80)-40,Random(80)-40,100);
	Smoke(Random(80)-40,Random(80)-40,100);


	
	ObjectCall(CreateObject(ABSR,150,Random(-50)+yc,-1),"nach_rechts");
	//ObjectCall(CreateObject(ABSR,130,Random(-45)+yc,-1),"nach_rechts");
	ObjectCall(CreateObject(ABSR,110,Random(-45)+yc,-1),"nach_rechts");
	//ObjectCall(CreateObject(ABSR,90,Random(-40)+yc,-1),"nach_rechts");
	ObjectCall(CreateObject(ABSR,70,Random(-40)+yc,-1),"nach_rechts");
	//ObjectCall(CreateObject(ABSR,60,Random(-35)+yc,-1),"nach_rechts");
	ObjectCall(CreateObject(ABSR,50,Random(-35)+yc,-1),"nach_rechts");
	//ObjectCall(CreateObject(ABSR,40,Random(-35)+yc,-1),"nach_rechts");
	ObjectCall(CreateObject(ABSR,30,Random(-30)+yc,-1),"nach_rechts");
	//ObjectCall(CreateObject(ABSR,20,Random(-30)+yc,-1),"nach_rechts");
	ObjectCall(CreateObject(ABSR,10,Random(-30)+yc,-1),"nach_rechts");
	
	//ObjectCall(CreateObject(ABSR,20,Random(10)+20+yc,-1),"static");
	ObjectCall(CreateObject(ABSR,40,Random(10)+20+yc,-1),"static");
	//ObjectCall(CreateObject(ABSR,-20,Random(10)+20+yc,-1),"static");
	ObjectCall(CreateObject(ABSR,-40,Random(10)+20+yc,-1),"static");
	//ObjectCall(CreateObject(ABSR,-1,Random(20)-10+yc,-1),"static");
	
	ObjectCall(CreateObject(ABSR,-150,Random(-50)+yc,-1),"nach_links");
	//ObjectCall(CreateObject(ABSR,-120,Random(-45)+yc,-1),"nach_links");
	ObjectCall(CreateObject(ABSR,-110,Random(-45)+yc,-1),"nach_links");
	//ObjectCall(CreateObject(ABSR,-90,Random(-40)+yc,-1),"nach_links");
	ObjectCall(CreateObject(ABSR,-70,Random(-40)+yc,-1),"nach_links");
	//ObjectCall(CreateObject(ABSR,-60,Random(-35)+yc,-1),"nach_links");
	ObjectCall(CreateObject(ABSR,-50,Random(-35)+yc,-1),"nach_links");
	//ObjectCall(CreateObject(ABSR,-40,Random(-30)+yc,-1),"nach_links");
	ObjectCall(CreateObject(ABSR,-30,Random(-30)+yc,-1),"nach_links");
	//ObjectCall(CreateObject(ABSR,-20,Random(50)+yc,-1),"nach_links");
	ObjectCall(CreateObject(ABSR,-10,Random(50)+yc,-1),"nach_links");




	CreateObject(ABPD,-50,-10,-1);
	CreateObject(ABPD,0,0,-1);
	CreateObject(ABPD,50,-10,-1);

	CastObjects(ABRW,25,70,0,-100);

	SetClimate(-50);
	SetTemperature(-50);


	NewGamma(RGB(255,255,255),RGB(255,255,255),RGB(255,255,255),0,300);
	NewGamma(RGB(0,0,0),RGB(128,128,128),RGB(255,255,255),0,60);

	RemoveObject();
	return(1);

nicht_markieren: return(1);