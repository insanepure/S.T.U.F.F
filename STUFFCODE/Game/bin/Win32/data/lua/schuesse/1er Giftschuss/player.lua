math.randomseed(os.time());
local ai = require("data.lua.ext.AiFunctions")


function Init()
	-----------------------------------------
	HitBoxX = 34; -- Verschiebung der Hitbox aufn Bild in der X Achse
	HitBoxY = 2; -- Verschiebung der Hitbox aufn Bild in der Y Achse
	HitBoxWidth = 60.0; -- Breite der Hitbox
	HitBoxHeight = 60.0; -- Höhe der Hitbox
	Width = 128.0; -- Reale Breite
	Height = 64.0; -- Reale Höhe
	-----------------------------------------
	ArraySize = 6;
	
	return ArraySize,Height,Width,HitBoxX,HitBoxY,HitBoxWidth,HitBoxHeight;
end							 


-----------------------------------------
	--Änderbare Werte--
MaxSpeed = 8.0; -- MaximalSpeed
AngleSpin = 7; -- Wieviel Grad er sich pro Update dreht 
LookAngleSpin = 9; -- Wie schnell das boot die Bildrichtung ändert
Acceleration = 0.8; -- Beschleunigung
Drag = 0.1;	-- Drag
Stopforce = 0.05;
Brakeforce = 0.25;

--nicht ändern
SpeedLimit = MaxSpeed;

-----------------------------------------

function Laser(c0,c1,c2,c3,c4,c5,Type, Angle,Cooldown)
	--Type = 1 -> Mittleres Schiff
	--Type = 0 -> Vorderes Schiff
	-- if Type == 0 then	
		-- ThrowBack = 50.0;	
		-- ThrowBackSteps = 5;
		-- length = 500;
		-- X = 64.0 + (60.0 * math.sin(Angle + math.pi/2));
		-- Y = 32.0 + (28.0 * math.cos(Angle + math.pi/2));
		-- Cooldown = 20;
		-- Duration = 10;
	-- elseif Type == 1 then
		-- ThrowBackSteps = 0;	
		-- ThrowBack = 0.0;
		-- length = 500;
		-- X = 64.0 + (60.0 * math.sin(Angle + math.pi/2));
		-- Y = 32.0 + (28.0 * math.cos(Angle + math.pi/2));
		-- Cooldown = 0;
		-- Duration = 1;
	-- end
	ThrowBack = 0;
	ThrowBackSteps = 0;
	Duration = 0;
	length = 0;
	X = 0;
	Y = 0;
	return c0,c1,c2,c3,c4,c5,ThrowBackSteps,ThrowBack,Duration,Cooldown,Angle,length,X,Y;
end

function Shoot(c0,c1,c2,c3,c4,c5,PlayerNum,X,Y,Angle,Speed,Cooldown)
	Angle = math.deg(Angle); -- Konvertiert Angle von Rad zu Deg

	X = X+50; --64.0 + (60.0 * math.sin(Angle + math.pi/2)); -- Wo des Schuss auf der X Achse gespawned wird. X input ist die X coordinate des Spielers
	Y = Y; --32.0 - (28.0 * math.cos(Angle + math.pi/2)); -- ^^ Y

	Cooldown = 160; -- Wie Lange bis zum nächsten Schuss. In 1/60 Sekunden gemessen
	Angle = 0 --Angle + math.random(-10,10); -- Beeinflusst den Winkel. In diesem Falle: Füge dem Input Winkel einen zufälligen Winkel von +/- 10 Hinzu
	Type = 1; -- Der Typ des Schusses. Ganze Zahlen verwenden
	
	Angle = math.rad(Angle); -- Konvetiere Angle von Deg zurück zu Rad. muss gemacht werden befor Bullets erstellt werden
	
	CreateBullet(PlayerNum, 1, X, Y, 10, math.rad(0));	-- Spawned einen Schuss mit Angegbene Werten. Dieser Code kann auch mehrmals aufgerufen Werden
	
	
	return c0,c1,c2,c3,c4,c5,Cooldown; -- Gebe den Cooldown an die Engine zurück
end	 

function UpdateLoop(ComboList,LastKey,Cd,Charge,Expire,pressed,X,Y,B,A,PlayerNum,Player_X,Player_Y,Player_Angle,Player_LookAngle,Player_Speed,timeMultiplicator)
	
	if pressed == 0 then
		if X then
			LastKey = 1;
		elseif Y then
			LastKey = 2;
		end
	end
	
	if LastKey ~= 0 and pressed == 0 and Cd == 0 then
		if LastKey == 1 then
			ComboList = ComboList .. "1";
		elseif LastKey == 2 then
			ComboList = ComboList .. "2";
		end
		
		if tonumber(ComboList) == 1 then
			SpawnBullet(PlayerNum, 2, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 11 then
			SpawnBullet(PlayerNum, 2, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 111 then
			SpawnBullet(PlayerNum, 2, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 1111 then
			SpawnBullet(PlayerNum, 3, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 11111 then
			SpawnBullet(PlayerNum, 3, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 111111 then
			SpawnBullet(PlayerNum, 3, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 21 then
			SpawnBullet(PlayerNum, 5, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 2121 then
			SpawnBullet(PlayerNum, 5, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 212121 then
			SpawnBullet(PlayerNum, 5, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 2221 then
			SpawnBullet(PlayerNum, 11, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 2 then
			SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 112 then
			SpawnBullet(PlayerNum, 7, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 1122 then
			SpawnBullet(PlayerNum, 10, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 11222 then
			SpawnBullet(PlayerNum, 10, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 112222 then
			SpawnBullet(PlayerNum, 10, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 1112 then
			SpawnBullet(PlayerNum, 6, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 11112 then
			SpawnBullet(PlayerNum, 8, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 111112 then
			SpawnBullet(PlayerNum, 9, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 212 then
			SpawnBullet(PlayerNum, 5, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 21212 then
			SpawnBullet(PlayerNum, 5, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 2121212 then
			SpawnBullet(PlayerNum, 5, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 22 then
			SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 222 then
			SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 2222 then
			SpawnBullet(PlayerNum, 4, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 22222 then
			SpawnBullet(PlayerNum, 4, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		elseif tonumber(ComboList) == 222222 then
			SpawnBullet(PlayerNum, 4, Player_X, Player_Y, Player_Speed, Player_LookAngle);
		else
			if LastKey == 1 then
				SpawnBullet(PlayerNum, 2, Player_X, Player_Y, Player_Speed, Player_LookAngle);
				ComboList = 1;
			elseif LastKey == 2 then
				SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle);
				ComboList = 2;
			end
		end
		
		pressed = 1;
		Cd = 180;
		LastKey = 0;
		Expire = 400;
		
	end
	
	if Y ~= true and X ~= true then
		pressed = 0;
	end
	
	if pressed == 1 then
		Charge = Charge + (10 * timeMultiplicator);
	else
		Charge = 0;
	end
	
	if string.len(ComboList) > 10 then
		ComboList = 0;
	end
	
	if Cd > 0 then
		Cd = Cd - (10 * timeMultiplicator);
	end
	
	if Cd < 10 then
		Cd = 0;
	end
	
	if Expire > 0 then
		Expire = Expire - (10 * timeMultiplicator);
	end
	
	if Expire < 10 then
		Expire = 0;
		ComboList = 0;
	end
	
	return ComboList,LastKey,Cd,Charge,Expire,pressed;
end


function UpdateAngle(c0,c1,c2,c3,c4,c5,timeMultiplicator,Angle,LookAngle,MovingAngle,Speed,Type)		

	
	-----------------------------------------
	--Angle = Aktueller Winkel des Bootes in der gefahren wird
	--LookAngle = Aktueller Winkel des Bootes in der das Boot schaut
	--MovingAngle = Winkel von dem Controller	
	-----------------------------------------
	
	Angle = Angle/math.pi*180; -- Konvertiert in Degree um 
	LookAngle = LookAngle/math.pi*180; -- Konvertiert in Degree um	
	MovingAngle = MovingAngle/math.pi*180;	-- Konvertiert in Degree um	
	-----------------------------------------
	
	DiffAngle = MovingAngle - LookAngle; -- Winkelunterschied, wichtig für unten 
	DiffAngle = (DiffAngle + 180) % 360 - 180; --Echter kleinster Winkel		 

	if DiffAngle < -45 then DiffAngle = -45; end --Maximaler auschlag
	if DiffAngle > 45 then DiffAngle = 45; end
	LookAngle = LookAngle + ((((DiffAngle / 45) * LookAngleSpin) * (Speed / MaxSpeed))*timeMultiplicator);
	
	------------------------------------------
	DiffAngle = MovingAngle - Angle; -- Winkelunterschied, wichtig für unten	
	DiffAngle = (DiffAngle + 180) % 360 - 180; --Echter kleinster Winkel	
	
	if DiffAngle < -45 then DiffAngle = -45; end --Maximaler auschlag
	if DiffAngle > 45 then DiffAngle = 45; end
	Angle = Angle + ((((DiffAngle / 45) * AngleSpin) * (Speed / MaxSpeed))*timeMultiplicator);
	------------------------------------------

	-----------------------------------------
	Angle = Angle*math.pi/180; --Der RückgabeWert wird wieder in Radiant zurückkonvertiert	 
	LookAngle = LookAngle*math.pi/180; --Der RückgabeWert wird wieder in Radiant zurückkonvertiert 
	----------------------------------------- 
	
	return c0,c1,c2,c3,c4,c5,LookAngle,Angle;
end

function UpdateSpeed(c0,c1,c2,c3,c4,c5,timeMultiplicator,Angle,MovingAngle,LT,RT,Speed)
	
	-- höhere empfindlichkeit auf kleinem anschlag
	RT = RT^2;
	-----------------------------------------
	SpeedLimit = MaxSpeed * RT;	
	-- La Formel
	if RT == 0 then
		Speed = Speed - (((Drag * Speed/MaxSpeed) + Stopforce));
	else
		Speed = Speed + (Acceleration * ((Speed * -1) + SpeedLimit) /MaxSpeed * RT);
	end

	-----------------------------------------
	if Speed < 0 then Speed = 0; end -- Falls es IRGENDWIE passiert, kA, mir passierte es!
	if Speed > MaxSpeed then Speed = MaxSpeed; end
	-----------------------------------------		
	
	--Damit er stehen bleibt, da Drag den Speed nie auf 0 bringt
	if Speed < 0.02 then
		Speed = 0.0;
	end
	
	return c0,c1,c2,c3,c4,c5,Speed;
end 

function SpawnBullet(PlayerNum,Typ,X,Y,Speed,Angle)
	Angle = math.deg(Angle);
	if Typ == 1 then
		local a = ai.GetPositionFromAngle(Angle * -1 + 90, 64);
		local b = ai.GetPositionFromAngle(Angle * -1 - 90, 64);
		CreateBullet(PlayerNum, 1, X + a.x, Y + a.y, Speed + 5, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X + b.x, Y + b.y, Speed + 5, math.rad(Angle) * -1);
	elseif Typ == 2 then
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle) * -1);
	elseif Typ == 3 then
		CreateBullet(PlayerNum, 1, X, Y, Speed + 12, math.rad(Angle + 5) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 12, math.rad(Angle - 5) * -1);
	elseif Typ == 4 then
		local a = ai.GetPositionFromAngle(Angle * -1 + 90, 64);
		local b = ai.GetPositionFromAngle(Angle * -1 - 90, 64);
		local c = ai.GetPositionFromAngle(Angle * -1 + 90, 128);
		local d = ai.GetPositionFromAngle(Angle * -1 - 90, 128);
		CreateBullet(PlayerNum, 1, X + a.x, Y + a.y, Speed + 5, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X + b.x, Y + b.y, Speed + 5, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X + c.x, Y + c.y, Speed + 5, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X + d.x, Y + d.y, Speed + 5, math.rad(Angle) * -1);
	elseif Typ == 5 then
		local a = ai.GetPositionFromAngle(Angle * -1 + 90, 64);
		local b = ai.GetPositionFromAngle(Angle * -1 - 90, 64);
		CreateBullet(PlayerNum, 1, X + a.x, Y + a.y, Speed + 12, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X + b.x, Y + b.y, Speed + 12, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 12, math.rad(Angle) * -1);
	elseif Typ == 6 then
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 45) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 45) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 90) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 90) * -1);
	elseif Typ == 7 then
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 45) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 45) * -1);
	elseif Typ == 8 then
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 45) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 45) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 90) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 90) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 135) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 135) * -1);
	elseif Typ == 9 then
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 45) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 45) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 90) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 90) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 135) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 135) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 180) * -1);
	elseif Typ == 10 then
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle + 45) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 8, math.rad(Angle - 45) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 5, math.rad(Angle + 120) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 5, math.rad(Angle - 120) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 5, math.rad(Angle + 140) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 5, math.rad(Angle - 140) * -1);
	elseif Typ == 11 then
		local a = ai.GetPositionFromAngle(Angle * -1 + 90, 64);
		local b = ai.GetPositionFromAngle(Angle * -1 - 90, 64);
		CreateBullet(PlayerNum, 1, X + a.x, Y + a.y, Speed + 5, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X + b.x, Y + b.y, Speed + 5, math.rad(Angle) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 5, math.rad(Angle + 90) * -1);
		CreateBullet(PlayerNum, 1, X, Y, Speed + 5, math.rad(Angle - 90) * -1);
	end
end