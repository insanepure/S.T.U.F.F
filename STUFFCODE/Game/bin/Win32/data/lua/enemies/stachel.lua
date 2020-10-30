local ai = require("data.lua.ext.AiFunctions")

	-----------------------------------------
   MaxSpeed = 5.0; -- Maximale Speed + PlayerSpeed (Kommt später dazu)    
   AngleSpin = 0.1; -- Drehung in Radiant
	 HitBoxX = 25; -- Verschiebung der Hitbox aufn Bild in der X Achse
	 HitBoxY = 30; -- Verschiebung der Hitbox aufn Bild in der Y Achse
	 HitBoxWidth = 70.0; -- Breite der Hitbox
	 HitBoxHeight = 70.0; -- Höhe der Hitbox
	 Width = 128.0; -- Reale Breite
	 Height = 128.0; -- Reale Höhe        
   Lifes = 80; --Wieviele Schüsse sie aushalten  
   Points = 650; --Wieviele Punkte sie geben
   ArraySize = 4; -- Wiegroß der Array ist     
   CollideDamage = 1; --Schaden der angerichtet wird wenn er kollidiert 
   dieoncollide = true; -- Beim kollidieren sterben
   DamageRadius = 1; --Radius indem Schaden gemacht wird
	-----------------------------------------

function Init()
	print("its MEEEEEE!");
	return DamageRadius,dieoncollide,CollideDamage,ArraySize,Points,Lifes,Height,Width,MaxSpeed,AngleSpin,HitBoxX,HitBoxY,HitBoxWidth,HitBoxHeight,Lifes;
end

function OnDie()
	print("KABOOM");
end

function Update(timestamp,X_real,Y_real,State,DamageRadius,Size,PlayerSpeed,timeMultiplicator,Animation,DeleteHim,X,Y,Speed,Angle,MoveAngle,Cam_X,Cam_Y,Screen_W,Screen_H,Player_X,Player_Y) 
	
	Y_real = Y_real / 10;
	X_real = X_real / 10;
	Angle = math.deg(Angle);
	
	-- if Size < 5 then
		-- Size = Size+0.05;
		-- DamageRadius = DamageRadius + (Width*0.05);
	-- end
	
	if State == 0 then
		X_real = X;
		Y_real = Y;
		State = 1;
		MoveAngle = ((Cam_Y + (Screen_H / 2)) - Y) / 12;
		Speed = 4;
	elseif State == 1 then
		if ai.GetDistance( X, Y, Player_X, Player_Y) < 200 then
			State = 2;
		end
	elseif State == 2 then
		Size = Size + 0.2 * timeMultiplicator;
			
		if Size >= 2.5 then
			DeleteHim = true;
		end
	end
	
	Angle = Angle + 1 * timeMultiplicator;
	timestamp = timestamp + 10 * timeMultiplicator;

	local m = ai.SinusModification( MoveAngle, timestamp / 5, 64);
	local push = ai.GetPositionFromAngle( MoveAngle, Speed);
	
	X_real = X_real + push.x;
	Y_real = Y_real + push.y;
	
	X = X_real + m.x;
	Y = Y_real + m.y;
	
	Angle = math.rad(Angle);
	X_real = X_real * 10;
	Y_real = Y_real * 10;
	
	return timestamp,X_real,Y_real,State,DamageRadius,Size,CollideDamage,Animation,DeleteHim,MoveAngle,X,Y,Speed,Angle;
end
