--load extension
local ai = require("data.lua.ext.AiFunctions")


fishNum = 0;
-----------------------------------------
MaxSpeed = 2.0; -- Maximale Speed + PlayerSpeed (Kommt später dazu)	 
AngleSpin = 0.02; -- Drehung in Radiant
HitBoxX = 64; -- Verschiebung der Hitbox aufn Bild in der X Achse
HitBoxY = 64; -- Verschiebung der Hitbox aufn Bild in der Y Achse
HitBoxWidth = 128.0; -- Breite der Hitbox
HitBoxHeight = 128.0; -- Höhe der Hitbox
Width = 256.0; -- Reale Breite
Height = 256.0; -- Reale Höhe		
Lifes = 60; --Wieviele Schüsse sie aushalten
Points = 1500; --Wieviele Punkte sie geben
ArraySize = 7; -- Wiegroß der Array ist   
CollideDamage = 0; --Schaden der angerichtet wird wenn er kollidiert  
dieoncollide = false; -- Beim kollidieren sterben
DamageRadius = 0;
-----------------------------------------

value_SwimClose = 600; --Wie nah sich die Fische an den Spieler trauen
SwinCloseVariation = 50;
SwimFar = 900; --Ab wann die Fische schneller Schwimmen um den Spieler zu erreichen

value_MaxForce = 10; --Maximalen Pull zum Spieler
MaxForceVariation = 3; -- Wie sehr er schwankt
value_ConstantForce = 2; -- Standart Pull zum Spieler
ConstantForceVariation = 1; -- Wie sehr er schwankt

State = 0;

value_Speed = 10.0;
value_ShootSpeed = 2.0;
SpeedVariation = 3; -- Wie sehr der Speed Schwankt

value_ShootCD = 150;

function Init()
	fishNum = fishNum + 1;
	return DamageRadius,dieoncollide,CollideDamage,ArraySize,Points,Lifes,Height,Width,MaxSpeed,AngleSpin,HitBoxX,HitBoxY,HitBoxWidth,HitBoxHeight;
end

function OnDie()
	fishNum = fishNum - 1;
end
				
function Update(Player_Xprevious,ShootCD,SwimClose,MaxForce,ConstantForce,Timer,State,DamageRadius,Size,PlayerSpeed,timeMultiplicator,Animation,DeleteHim,X,Y,Speed,Angle,MoveAngle,Cam_X,Cam_Y,Screen_W,Screen_H,Player_X,Player_Y)
    
	
	Player_Xprevious = Player_Xprevious / 100;
	DeleteHim = false;
	Angle = math.deg(Angle);
	
	if Timer > 0 then
		Timer = Timer - (10 * timeMultiplicator);
	end
	
	if ShootCD > 0 then
		ShootCD = ShootCD - (10 * timeMultiplicator);
	end
	
	MaxForce = MaxForce / 100;
	ConstantForce = ConstantForce / 100;
	MoveAngle = math.deg(MoveAngle);
	
	if State == 0 then
		Timer = 1200;
		State = 1;
		Speed = value_Speed;
		MaxForce = value_MaxForce + ((math.random() - 0.5) * MaxForceVariation);
		ConstantForce = value_ConstantForce + ((math.random() - 0.5) * ConstantForceVariation);
		Speed = Speed + ((math.random() - 0.5) * SpeedVariation);
		SwimClose = value_SwimClose + ((math.random() - 0.5) * SwinCloseVariation);
	elseif State == 1 then
		if Speed < value_Speed then
			Speed = Speed + 0.2;
		end
		
		if Timer <= 0 then
			State = 2;
			Timer = 600;
		end
	elseif State == 2 then
		if Speed > value_ShootSpeed then
			Speed = Speed - 0.5;
		end
		
		local d = ai.SmallestAngle( Angle + 180, ai.GetAngle( X, Y, Player_X, Player_Y));

		Angle = Angle + (d / 15 * timeMultiplicator);
		
		if Timer <= 0 then
			State = 3;
			Timer = 600;
		end
	elseif State == 3 then
		if ShootCD <= 0 then
			PlaySound(9);
			if Size == 1 then
				local i = ai.GetPositionFromAngle(Angle + 180, 128);
				CreateBullet(0,2,X + i.x,Y + i.y,3,math.rad(Angle+180)*-1); 
			else
				local i = ai.GetPositionFromAngle(Angle + 180, 380);
				CreateBullet(0,3,X + i.x,Y + i.y,3,math.rad(Angle+180)*-1); 
			end
			ShootCD = value_ShootCD;
		end
		
		local d = ai.SmallestAngle( Angle + 180, ai.GetAngle( X, Y, Player_X, Player_Y));

		Angle = Angle + (d / 10 * timeMultiplicator);
		
		if Timer <= 0 then
			State = 1;
			Timer = 1200;
		end
	end
	
	MoveAngle = ai.GetAngle( X, Y, Player_X, Player_Y) - 90;
	
	local x = X;
	local y = Y;
	local angle = Angle;
	local m = (ai.GetDistance( X, Y, Player_X, Player_Y) - SwimClose) / SwimFar;
	
	local force = ConstantForce + (m * MaxForce);
	local pull = ai.GetPositionFromAngle(ai.GetAngle( X, Y, Player_X, Player_Y), force * timeMultiplicator);
	local push = ai.GetPositionFromAngle(MoveAngle, Speed * timeMultiplicator);

	X = X + pull.x + push.x;
	Y = Y + pull.y + push.y;
	
	if State ~= 2 and State ~= 3 then
		local d = ai.SmallestAngle( Angle + 180, ai.GetAngle( x, y, X, Y));

		Angle = Angle + (d / 5 * timeMultiplicator);
	end
	
	if Player_X > Player_Xprevious then
		X = X + ((Player_X - Player_Xprevious) * 0.8);
	end
	
	MaxForce = math.floor(MaxForce * 100);
	ConstantForce = math.floor(ConstantForce * 100);
	
	Player_Xprevious = Player_X;
	
	MoveAngle = math.rad(MoveAngle);
	Angle = math.rad(Angle);
	Player_Xprevious = Player_Xprevious * 100;
    
	return Player_Xprevious,ShootCD,SwimClose,MaxForce,ConstantForce,Timer,State,DamageRadius,Size,CollideDamage,Animation,DeleteHim,MoveAngle,X,Y,Speed,Angle;
end
