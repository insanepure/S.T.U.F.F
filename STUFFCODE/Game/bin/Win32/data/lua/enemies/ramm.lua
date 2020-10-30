local ai = require("data.lua.ext.AiFunctions")

-----------------------------------------
MaxSpeed = 12; -- Maximale Speed + PlayerSpeed (Kommt später dazu)    
AngleSpin = 0.1; -- Drehung in Radiant
HitBoxX = 64; -- Verschiebung der Hitbox aufn Bild in der X Achse
HitBoxY = 64; -- Verschiebung der Hitbox aufn Bild in der Y Achse
HitBoxWidth = 128.0; -- Breite der Hitbox
HitBoxHeight = 128.0; -- Höhe der Hitbox
Width = 256.0; -- Reale Breite
Height = 256.0; -- Reale Höhe        
Lifes = 100; --Wieviele Schüsse sie aushalten
Points = 1700; --Wieviele Punkte sie geben
ArraySize = 4; -- Wiegroß der Array ist      
CollideDamage = 0; --Schaden der angerichtet wird wenn er kollidiert
dieoncollide = false; -- Beim kollidieren sterben
DamageRadius = 0;
-----------------------------------------

MinSpeed = 1;
RammSpeed = 35;
RammAcc = 4;
Acceleration = 0.1;

BorderFleeSpeed = 30;
BorderHFear = 512;
BorderVFear = 480;

function Init()
	return DamageRadius,dieoncollide,CollideDamage,ArraySize,Points,Lifes,Height,Width,MaxSpeed,AngleSpin,HitBoxX,HitBoxY,HitBoxWidth,HitBoxHeight,Lifes;
end

function OnDie()

end

function Update(Player_X_previous,State,Timer,Attacks,DamageRadius,Size,PlayerSpeed,timeMultiplicator,Animation,DeleteHim,X,Y,Speed,Angle,MoveAngle,Cam_X,Cam_Y,Screen_W,Screen_H,Player_X,Player_Y) 

	MoveAngle = math.deg(MoveAngle);
	Angle = math.deg(Angle);
	Player_X_previous = Player_X_previous / 100;
	
	if Player_X_previous == 0 then
		Player_X_previous = Player_X;
	end
	
	if Timer > 0 then
		Timer = Timer - (10 * timeMultiplicator);
	end
	
	local diff = ai.SmallestAngle(MoveAngle,ai.GetAngle( X, Y, Player_X, Player_Y)); -- Calculate Angle Change
	
	if State == 0 then
		--Load
		State = 10;
		PlaySound(32);
		diff = ai.SmallestAngle(MoveAngle,ai.GetAngle( X, Y, Player_X, Player_Y));
	elseif State == 10 then
		-- Swim to Player
		if Speed > MaxSpeed then
			Speed = Speed - (RammAcc * timeMultiplicator);
		end
		
		if Speed < MaxSpeed then
			Speed = Speed + (Acceleration * timeMultiplicator);
		end
		
		if Timer <= 0 then
			State = 1;
			Timer = 800;
		end

		CollideDamage = 0;
		diff = diff / 8; -- Allow to turn slowly
		
	elseif State == 1 then
		--Slow Down
		if Speed >= MinSpeed then
			Speed = Speed - (Acceleration * timeMultiplicator);
		end
		
		if Speed > MaxSpeed then
			Speed = Speed - (RammAcc * timeMultiplicator);
		end
		
		if Timer <= 0 then
			State = 2;
			Timer = 600;
			PlaySound(31);
		end

		CollideDamage = 0;
		diff = diff / 10; -- Allow to turn slowly
		
	elseif State == 2 then
		--turn to Player
		if Speed >= MinSpeed then
			Speed = Speed - (RammAcc * timeMultiplicator);
		end
		
		if Timer <= 0 then
			State = 3;
			Timer = ai.GetDistance(X, Y, Player_X, Player_Y) / 3;
		end
		
		CollideDamage = 0;
		diff = diff / 2;
		
	elseif State == 3 then
	
		if ai.GetDistance(X, Y, Player_X, Player_Y) < 128 then
			Timer = Timer + (10 * timeMultiplicator);
		end
		
		diff = 0;
		
		if Speed < RammSpeed then
			Speed = Speed + (RammAcc * timeMultiplicator) + PlayerSpeed;
		end
		
		if Timer <= 0 then
			State = 1;
			Timer = 800;
			PlaySound(32);
		end
		
		CollideDamage = 1;
	end
	
	MoveAngle = MoveAngle + (diff * 0.2); -- apply Angle Change
	
	local x = X;
	local y = Y;
	
	local f = ai.GetPositionFromAngle( MoveAngle, Speed);
	X = X + f.x;
	Y = Y + f.y;
	
	if State ~= 2 then
		Angle = ai.GetAngle( x, y, X, Y);
	else
		Angle = MoveAngle;
	end
	
	
	--Screenborderphobia
	if Player_X > Player_X_previous then
		X = X + (Player_X - Player_X_previous);
	end
	
	Angle = math.rad(Angle);
	MoveAngle = math.rad(MoveAngle);
	Player_X_previous = Player_X;
	Player_X_previous = Player_X_previous * 100;

	return Player_X_previous,State,Timer,Attacks,DamageRadius,Size,CollideDamage,Animation,DeleteHim,MoveAngle,X,Y,Speed,Angle;
end
