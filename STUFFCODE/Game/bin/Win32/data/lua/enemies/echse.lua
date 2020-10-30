--load extension
local ai = require("data.lua.ext.AiFunctions")

fishNum = 0;
-----------------------------------------
MaxSpeed = 12.0; -- Maximale Speed + PlayerSpeed (Kommt später dazu)    
AngleSpin = 0.1; -- Drehung in Radiant
HitBoxX = 98 -- Verschiebung der Hitbox aufn Bild in der X Achse
HitBoxY = 98; -- Verschiebung der Hitbox aufn Bild in der Y Achse
HitBoxWidth = 60.0; -- Breite der Hitbox
HitBoxHeight = 60.0; -- Höhe der Hitbox
Width = 256.0; -- Reale Breite
Height = 256.0; -- Reale Höhe
Lifes = 20; --Wieviele Schüsse sie aushalten
Points = 250; --Wieviele Punkte sie geben
CollideDamage = 1; --Schaden der angerichtet wird wenn er kollidiert
dieoncollide = true; -- Beim kollidieren sterben   
DamageRadius = 0; --Radius indem Schaden gemacht wird
ArraySize = 8; -- Wiegroß der Array ist

value_SwimClose = 400; --Wie nah sich die Fische an den Spieler trauen
SwinCloseVariation = 50;
SwimFar = 600; --Ab wann die Fische schneller Schwimmen um den Spieler zu erreichen

value_MaxForce = 10; --Maximalen Pull zum Spieler
MaxForceVariation = 3; -- Wie sehr er schwankt
value_ConstantForce = 2; -- Standart Pull zum Spieler
ConstantForceVariation = 1; -- Wie sehr er schwankt

State = 0;

SpeedVariation = 3; -- Wie sehr der Speed Schwankt

AttackTimer = 6000;
-----------------------------------------

-- Array Variablen: State, MaxForce, ConstantForce

function Init()
	fishNum = fishNum + 1;
	return DamageRadius,dieoncollide,CollideDamage,ArraySize,Points,Lifes,Height,Width,MaxSpeed,AngleSpin,HitBoxX,HitBoxY,HitBoxWidth,HitBoxHeight;
end

function OnDie()
	fishNum = fishNum - 1;
end
     
function Update(player_x_previous,mySpeed,ma,Cd,SwimClose,State,MaxForce,ConstantForce,DamageRadius,Size,PlayerSpeed,timeMultiplicator,Animation,DeleteHim,X,Y,Speed,Angle,MoveAngle,Cam_X,Cam_Y,Screen_W,Screen_H,Player_X,Player_Y)
	
	player_x_previous = player_x_previous / 10;
	
	--------------------------------------------------
	--------------------------------------------------
	
	if AttackTimer > 0 then
		AttackTimer = AttackTimer - ((5/fishNum) * timeMultiplicator) - (1 * timeMultiplicator);
	else
		AttackTimer = 0;
	end
	
	--------------------------------------------------
	--------------------------------------------------
	
	MaxForce = MaxForce / 100;
	ConstantForce = ConstantForce / 100;
	MoveAngle = math.deg(MoveAngle);
	
	
	if State == 0 then
		player_x_previous = Player_X;
		State = 1;
		MaxForce = value_MaxForce + ((math.random() - 0.5) * MaxForceVariation);
		ConstantForce = value_ConstantForce + ((math.random() - 0.5) * ConstantForceVariation);
		Speed = Speed + ((math.random() - 0.5) * SpeedVariation);
		mySpeed = Speed * 100;
		SwimClose = value_SwimClose + ((math.random() - 0.5) * SwinCloseVariation);
		ma = 90;
	elseif State == 1 then
		if ma < 90 then
			ma = ma + 2;
		end
		
		if ma > 90 then
			ma = ma - 2;
		end
		
		if Speed > mySpeed / 100 then
			Speed = Speed - 0.4;
		end
		
		if Speed < mySpeed / 100 then
			Speed = Speed + 0.4;
		end
	elseif State == 2 then
		if ma < 140 then
			ma = ma + 4;
		end

		if Cd == 0 then
			State = 3;
			Cd = 800;
		end
	elseif State == 3 then
		if ma > 2 then
			ma = ma - 8;
		end
		
		if ma < 2 then
			ma = 2;
		end
		
		Speed = Speed + 0.2;
		
		if Cd == 0 then
			State = 1;
		end
	end
	
	local diff = ai.SmallestAngle(MoveAngle,ai.GetAngle( X, Y, Player_X, Player_Y) + ma);
	
	
	MoveAngle = MoveAngle + (diff * 0.2);
	
	local x = X;
	local y = Y;
	local angle = Angle;
	local m = (ai.GetDistance( X, Y, Player_X, Player_Y) - SwimClose) / SwimFar;
	
	local force = ConstantForce + (m * MaxForce);
	local pull = ai.GetPositionFromAngle(ai.GetAngle( X, Y, Player_X, Player_Y), force * timeMultiplicator);
	local push = ai.GetPositionFromAngle(MoveAngle, Speed);
	
	X = X + pull.x + push.x;
	Y = Y + pull.y + push.y;
	
	Angle = ai.GetAngle( x, y, X, Y);
	
	if AttackTimer == 0 then
		local a = ai.GetAngle( X, Y, Player_X, Player_Y);
		if a < -100 and a > -135 and State == 1 then
			State = 2;
			Cd = 600;
			AttackTimer = 6000;
		end
	end
	
	if Player_X > player_x_previous then
		X = X + ((Player_X - player_x_previous) * 0.7);
	end
	
	MaxForce = math.floor(MaxForce * 100);
	ConstantForce = math.floor(ConstantForce * 100);
	
	player_x_previous = Player_X;
	player_x_previous = player_x_previous * 10;
	
	MoveAngle = math.rad(MoveAngle);
	Angle = math.rad(Angle);
	
	if Cd > 0 then
		Cd = Cd - (10 * timeMultiplicator);
	else
		Cd = 0;
	end
	
	return player_x_previous,mySpeed,ma,Cd,SwimClose,State,MaxForce,ConstantForce,DamageRadius,Size,CollideDamage,Animation,DeleteHim,MoveAngle,X,Y,Speed,Angle;
end   
