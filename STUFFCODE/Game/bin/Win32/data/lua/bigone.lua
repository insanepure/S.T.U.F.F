math.randomseed(os.time());
local ai = require("data.lua.ext.AiFunctions")

charge_type_0 = {};
charge_type_0.charge = 100;
charge_type_0.r = 1.0;
charge_type_0.g = 1.0;
charge_type_0.b = 1.0;

charge_type_11221 = {};
charge_type_11221.charge = 120;
charge_type_11221.r = 1.0;
charge_type_11221.g = 0.0;
charge_type_11221.b = 0.0;

charge_type_1121 = {};
charge_type_1121.charge = 400;
charge_type_1121.r = 1.0;
charge_type_1121.g = 0.0;
charge_type_1121.b = 1.0;

charge_type_2 = {};
charge_type_2.charge = 50;
charge_type_2.r = 1.0;
charge_type_2.g = 1.0;
charge_type_2.b = 1.0;

charge_type_21 = {};
charge_type_21.charge = 70;
charge_type_21.r = 1.0;
charge_type_21.g = 1.0;
charge_type_21.b = 1.0;

charge_type_212 = {};
charge_type_212.charge = 90;
charge_type_212.r = 1.0;
charge_type_212.g = 1.0;
charge_type_212.b = 1.0;

charge_toleranz = 60;

Players = 0;
hspeed = 0;
angle = 0;

function Init()
		-----------------------------------------
	HitBoxX = 83; -- Verschiebung der Hitbox aufn Bild in der X Achse
	HitBoxY = 206; -- Verschiebung der Hitbox aufn Bild in der Y Achse
	HitBoxWidth = 260.0; -- Breite der Hitbox
	HitBoxHeight = 106.0; -- Höhe der Hitbox
	Width = 445.0; -- Reale Breite
	Height = 512.0; -- Reale Höhe
	-----------------------------------------
	ArraySize = 13;
	
	Players = Players + 1;
	
	return ArraySize,Height,Width,HitBoxX,HitBoxY,HitBoxWidth,HitBoxHeight;
end							 

---------------------------------

--- Wert ist iwie null und gibt error
MaxSpeed = 5;
			 
---------------------------------

-----------------------------------------
	--Änderbare Werte--
value_MaxSpeed = 8.0; -- MaximalSpeed
AngleSpin = 7; -- Wieviel Grad er sich pro Update dreht 
LookAngleSpin = 9; -- Wie schnell das boot die Bildrichtung ändert
Acceleration = 0.8; -- Beschleunigung
Drag = 0.1;	-- Drag
Stopforce = 0.05;
Brakeforce = 0.25;

--nicht ändern
SpeedLimit = MaxSpeed;


Bonus_Speed_Border = 512;
Bonus_Speed_Max = 0.2;

Speed_Up_limit = 10;
Speed_Up_persecond = 1.5;
Speed_Up_penalty = 0.5;
Speed_Up_penalty_flat =3;

Speed_Up = Speed_Up_limit;
-----------------------------------------
function OnRespawn()
	Speed_Up = Speed_Up * Speed_Up_penalty;
	if Speed_Up - Speed_Up_penalty_flat > 0 then
		Speed_Up = Speed_Up - Speed_Up_penalty_flat;
	else
		Speed_Up = 0;
	end
end

function OnDie()
	Players = Players - 1;
end


function UpdateLoop(specialcd,fire_cd,fire_ex,mtp,myX,BulletNum,ComboList,LastKey,Cd,Charge,Expire,pressed,inCombo,Ship_Position,Player_Ship,FireRate,X,Y,B_key,A,PlayerNum,Player_X,Player_Y,Player_Angle,Player_LookAngle,Player_Speed,timeMultiplicator)
	mtp = mtp / 1000;
	
	Player_Ship = Player_Ship - 1;
	
	if Speed_Up < Speed_Up_limit then
		Speed_Up = Speed_Up + Speed_Up_persecond / 60 * timeMultiplicator / Players;
	end
	
	R = 0;
	G = 0;
	B = 0;
	
	if FireRate then
		if fire_cd == 0 then
			SpawnBullet(PlayerNum, 6, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
			fire_cd = math.random(190);
		end
	end
	
	-- if B_key then
      -- CreateLaser(PlayerNum,Type,X,Y,Angle,Cooldown,Length,DMG,Collide,Bounce)
		-- CreateLaser(PlayerNum,1,Player_X,Player_Y,0,2,512,1,true,false);
	-- end
   
	if pressed == 0 then
		if X then
			LastKey = 1;
			--pressed = 1;
		elseif Y then
			LastKey = 2;
			--pressed = 1;
		end
	end
	
	if (X or Y) and inCombo == 0 then
		local t = false;
		
		if tonumber(ComboList ) == 2 then
			--beispiel
			
			R = charge_type_2.r * (Charge / charge_type_2.charge);
			G = charge_type_2.g * (Charge / charge_type_2.charge);
			B = charge_type_2.b * (Charge / charge_type_2.charge);
			
			if Charge >= charge_type_2.charge + charge_toleranz then
				SpawnBullet(PlayerNum, 9, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
				ComboList = 0;
			end
			
			if Charge >= charge_type_2.charge then
				t = true;
			end
		elseif tonumber(ComboList ) == 21 then
			--beispiel
			
			R = charge_type_21.r * (Charge / charge_type_21.charge);
			G = charge_type_21.g * (Charge / charge_type_21.charge);
			B = charge_type_21.b * (Charge / charge_type_21.charge);
			
			if Charge >= charge_type_21.charge + charge_toleranz then
				SpawnBullet(PlayerNum,10, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
				ComboList = 0;
			end
			
			if Charge >= charge_type_21.charge then
				t = true;
			end
		elseif tonumber(ComboList ) == 212 then
			--beispiel
			
			R = charge_type_212.r * (Charge / charge_type_212.charge);
			G = charge_type_212.g * (Charge / charge_type_212.charge);
			B = charge_type_212.b * (Charge / charge_type_212.charge);
			
			if Charge >= charge_type_212.charge + charge_toleranz then
				SpawnBullet(PlayerNum,11, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
				ComboList = 0;
			end
			
			if Charge >= charge_type_212.charge then
				t = true;
			end
		elseif tonumber(ComboList ) == 11221 then
			R = charge_type_11221.r * (Charge / charge_type_11221.charge);
			G = charge_type_11221.g * (Charge / charge_type_11221.charge);
			B = charge_type_11221.b * (Charge / charge_type_11221.charge);
			
			if Charge >= charge_type_11221.charge + charge_toleranz then
				SpawnBullet(PlayerNum, 5, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
				inCombo = 3;
				BulletNum = 3;
				Cd = 80;
			end
			
			if Charge >= charge_type_11221.charge then
				t = true;
			end
		elseif tonumber(ComboList ) == 1121 then
			R = charge_type_1121.r * (Charge / charge_type_1121.charge);
			G = charge_type_1121.g * (Charge / charge_type_1121.charge);
			B = charge_type_1121.b * (Charge / charge_type_1121.charge);
			
			if Charge >= charge_type_1121.charge then
				t = true;
			end
		end
		
		if R > 1.0 then R = 1.0; end
		if G > 1.0 then G = 1.0; end
		if B > 1.0 then B = 1.0; end
		
		if t then
			RumbleStrength = 1.0;
			RumbleLength = 100;
		end
	end
	
	if pressed == 1 and not X and not Y and inCombo == 0 then		
		if tonumber(ComboList) == 2 then
			if Charge >= charge_type_2.charge then
				SpawnBullet(PlayerNum, 9, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
			end
		elseif tonumber(ComboList) == 21 then
			if Charge >= charge_type_21.charge then
				SpawnBullet(PlayerNum,10, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
			end
		elseif tonumber(ComboList) == 212 then
			if Charge >= charge_type_212.charge then
				SpawnBullet(PlayerNum,11, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
			end
		elseif tonumber(ComboList) == 11221 then
			if Charge >= charge_type_11221.charge then
				SpawnBullet(PlayerNum, 5, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
				inCombo = 3;
				BulletNum = 3;
				Cd = 80;
			end
		-- elseif tonumber(ComboList) == 1121 then
			-- if Charge >= charge_type_1121.charge then
				-- SpawnBullet(PlayerNum, 6, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
				-- inCombo = 4;
				-- if Charge >= 600 then
					-- Charge = 600;
				-- end
				-- Expire = Charge * 2;
				-- Cd = 40;
			-- end
		end
	end
	
	if inCombo ~= 0 then -- auto continue Combos go here. inCombo describes what combo is being executed
		if Cd == 0 then
			if inCombo == 1 then
				SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle, Player_Ship);
				Cd = 100;
			elseif inCombo == 2 then
				SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle, Player_Ship);
				BulletNum = BulletNum - 1;
				Cd = 40;
				if BulletNum == 0 then
					inCombo = 0;
				end
			elseif inCombo == 3 then
				SpawnBullet(PlayerNum,5.1,Player_X, Player_Y, Player_Speed, Player_LookAngle, Player_Ship);
				BulletNum = BulletNum - 1;
				Cd = 80;
				if BulletNum == 0 then
					inCombo = 0;
				end
			elseif inCombo == 4 then
				SpawnBullet(PlayerNum,6,Player_X, Player_Y, Player_Speed, Player_LookAngle, Player_Ship);
				Cd = math.random(190);
			elseif inCombo == 5 then
				SpawnBullet(PlayerNum,12, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
				BulletNum = BulletNum - 1;
				Cd = 180;
				if BulletNum == 0 then
					inCombo = 0;
				end
			end
		end
		pressed = 1;
	end
	
	firerate = 0;
	shield = 0;
	Energie = 0;  
	Schub = 0;
	
	if LastKey ~= 0 and pressed == 0 and Cd == 0 and inCombo == 0 then
		if LastKey == 1 then
			ComboList = ComboList .. "1";
		elseif LastKey == 2 then
			ComboList = ComboList .. "2";
		end
		
		Expire = 400; -- set longer before hold combos
		Cd = 140; 

		
		if tonumber(ComboList) == 1 then
			SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 11 then
			SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 111 then
			SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 112 then
			SpawnBullet(PlayerNum, 3, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 1122 then
			SpawnBullet(PlayerNum, 4, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 11221 then
			------------------------------------------------------------------------------------------
		--elseif tonumber(ComboList) == 1121 then
			------------------------------------------------------------------------------------------
		elseif tonumber(ComboList) == 12 then
			SpawnBullet(PlayerNum, 7, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 122 then
			SpawnBullet(PlayerNum,7.1,Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 1222 then
			SpawnBullet(PlayerNum,7.2,Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 12221 then
			SpawnBullet(PlayerNum, 8, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 1112 then
			SpawnBullet(PlayerNum, 13, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 11122 then
			SpawnBullet(PlayerNum, 14, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 2 then
			------------------------------------------------------------------------------------------
		elseif tonumber(ComboList) == 21 then
			------------------------------------------------------------------------------------------
		elseif tonumber(ComboList) == 212 then
			------------------------------------------------------------------------------------------
		elseif tonumber(ComboList) == 1111 then
			SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle,Player_Ship);
		elseif tonumber(ComboList) == 11112 then
			if specialcd == 0 then
				if Ship_Position == 0 then
					specialcd = 1800;
					-- Player,Type,X,Y,Speed,Damage*10,Length,Stay in Seconds,collide,bounce
					CreateLaser(PlayerNum,104,Player_X,Player_Y,0,60,10,3,false,false);
				elseif Ship_Position == 1 then
					specialcd = 3600;
					firerate = 120;
					shield = 3;
				elseif Ship_Position == 2 then
					specialcd = 3600;
					Energie = 42;
				elseif Ship_Position == 3 then
					specialcd = 3600;
					Schub = 20;
				end
			end
		else
			if LastKey == 1 then
				SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle, Player_Ship);
				ComboList = 1;
			elseif LastKey == 2 then
				-- SpawnBullet(PlayerNum, 1, Player_X, Player_Y, Player_Speed, Player_LookAngle, Player_Ship);
				ComboList = 2;
			end
		end
		
		pressed = 1;
		LastKey = 0;
		
	end
	
	if pressed == 1 then
		Charge = Charge + (10 * timeMultiplicator);
		
	else
		Charge = 0;
	end
	
	if Y ~= true and X ~= true then
		pressed = 0;
		RumbleLength = 0;
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
	
	if specialcd > 0 then
		specialcd = specialcd - (10 * timeMultiplicator);
	end
	
	if specialcd < 10 then
		specialcd = 0;
	end

	if fire_cd > 0 then
		fire_cd = fire_cd - 10 * timeMultiplicator;
	end
	
	if fire_cd < 10 then
		fire_cd = 0;
	end
	
	if fire_ex > 0 then
		fire_ex = fire_ex - 10 * timeMultiplicator;
	end
	
	if fire_ex < 10 then
		fire_ex = 0;
	end
	
	if Expire > 0 then
		if pressed == 0 or inCombo ~= 0 then
			Expire = Expire - (10 * timeMultiplicator);
		end
	end
	
	if Expire < 10 then
		Expire = 0;
		ComboList = 0;
		inCombo = 0;
	end
   -- R = 0.0;
   -- G = 1.0;
   -- B = 0.0;	
	mtp = mtp * 1000;
	myX = Player_X;
	return specialcd,fire_cd,fire_ex,mtp,myX,BulletNum,ComboList,LastKey,Cd,Charge,Expire,pressed,inCombo,shield,firerate,Energie,Schub,R,G,B,RumbleStrength,RumbleLength;
end


function UpdateAngle(specialcd,fire_cd,fire_ex,mtp,myX,c0,c1,c2,c3,c4,c5,c6,c7,timeMultiplicator,Angle,LookAngle,MovingAngle,Speed)		
	mtp = mtp / 1000;
	
	-----------------------------------------
	--Angle = Aktueller Winkel des Bootes in der gefahren wird
	--LookAngle = Aktueller Winkel des Bootes in der das Boot schaut
	--MovingAngle = Winkel von dem Controller	
	-----------------------------------------
	
	Angle = Angle/math.pi*180; -- Konvertiert in Degree um 
	LookAngle = LookAngle/math.pi*180; -- Konvertiert in Degree um	
	MovingAngle = MovingAngle/math.pi*180;	-- Konvertiert in Degree um	
	-----------------------------------------
	
	-- DiffAngle = MovingAngle - LookAngle; -- Winkelunterschied, wichtig für unten 
	-- DiffAngle = (DiffAngle + 180) % 360 - 180; --Echter kleinster Winkel		 

	-- if DiffAngle < -45 then DiffAngle = -45; end --Maximaler auschlag
	-- if DiffAngle > 45 then DiffAngle = 45; end
	-- LookAngle = LookAngle + ((((DiffAngle / 45) * LookAngleSpin) * (Speed / MaxSpeed))*timeMultiplicator);
	
	------------------------------------------
	MovingAngle = ai.SmallestAngle( 0, MovingAngle);
	
	if math.abs(MovingAngle) < 90 then
		DiffAngle = MovingAngle - Angle; -- Winkelunterschied, wichtig für unten	
		DiffAngle = (DiffAngle + 180) % 360 - 180; --Echter kleinster Winkel	
		
		if DiffAngle < -45 then DiffAngle = -45; end --Maximaler auschlag
		if DiffAngle > 45 then DiffAngle = 45; end
		Angle = Angle + ((((DiffAngle / 45) * AngleSpin) * (Speed / MaxSpeed))*timeMultiplicator);
	end
	------------------------------------------
	
	local f = ai.SmallestAngle(0,Angle);
	mtp = math.abs(math.abs(f) - 180) / 180;
	
	if f > 90 then
		f = 90;
	end
	
	if f < - 90 then
		f = -90;
	end
	
	Angle = f;
	
	if math.abs(MovingAngle) > 130 then
		Angle = Angle * 0.95;
	end
	
	local fd = ai.SmallestAngle( LookAngle, f / 2);
	
	LookAngle = LookAngle + fd * 0.05 * timeMultiplicator;
	angle = LookAngle;
	
	-----------------------------------------
	Angle = Angle*math.pi/180; --Der RückgabeWert wird wieder in Radiant zurückkonvertiert	 
	LookAngle = LookAngle*math.pi/180; --Der RückgabeWert wird wieder in Radiant zurückkonvertiert 
	----------------------------------------- 
	
	mtp = mtp * 1000;
	return specialcd,fire_cd,fire_ex,mtp,myX,c0,c1,c2,c3,c4,c5,c6,c7,LookAngle,Angle;
end

function UpdateSpeed(specialcd,fire_cd,fire_ex,mtp,myX,c0,c1,c2,c3,c4,c5,c6,c7,Cam_X,timeMultiplicator,Angle,MovingAngle,LT,RT,Speed)
	mtp = mtp / 1000;
	
	MovingAngle = math.deg(MovingAngle);
	MovingAngle = ai.SmallestAngle( 0, MovingAngle);
	
	local dis = myX - Cam_X;
	local bonus = 1;
	
	if dis < Bonus_Speed_Border then
		bonus = (((math.abs(dis - Bonus_Speed_Border) / Bonus_Speed_Border) * Bonus_Speed_Max) * mtp)+ 1;
	end
	
	-- höhere empfindlichkeit auf kleinem anschlag
	RT = RT^2;
	-----------------------------------------
	MaxSpeed = (value_MaxSpeed + Speed_Up) * bonus;
	SpeedLimit = (MaxSpeed) * RT;
	
	-- La Formel
	if math.abs(MovingAngle) <= 130 then
		if RT == 0 then
			hspeed = hspeed - (((Drag * hspeed/MaxSpeed) + Stopforce)) * timeMultiplicator;
		else
			hspeed = hspeed + (Acceleration * ((hspeed * -1) + SpeedLimit) /MaxSpeed * RT) * timeMultiplicator;
		end
	else
		hspeed = hspeed - (((Drag * hspeed/MaxSpeed) + (Brakeforce * RT * ( (math.abs(MovingAngle) - 90) / 90)))) * timeMultiplicator;
	end

	-----------------------------------------
	if hspeed < 0 then hspeed = 0; end -- Falls es IRGENDWIE passiert, kA, mir passierte es!
	if hspeed > MaxSpeed then hspeed = MaxSpeed; end
	-----------------------------------------		
	
	--Damit er stehen bleibt, da Drag den Speed nie auf 0 bringt
	if hspeed < 0.02 then
		hspeed = 0.0;
	end
	
	Speed = hspeed * (1 / math.cos( math.rad(angle)));
	
	mtp = mtp * 1000;
	return specialcd,fire_cd,fire_ex,mtp,myX,c0,c1,c2,c3,c4,c5,c6,c7,Speed;
end 

function SpawnBullet(PlayerNum,Typ,X,Y,Speed,Angle,PT)
	Angle = math.deg(Angle);
	if Typ == 1 then -- X
	
		if PT == 0 then
			CreateBullet(PlayerNum, 100, X, Y, Speed + 8, math.rad(Angle) * -1); -- gift
			PlaySound(43);
		elseif PT == 1 then
			PlaySound(math.random(39,41));
			CreateBullet(PlayerNum, 101, X, Y, Speed + 8, math.rad(Angle) * -1); -- helfer
		elseif PT == 2 then
			PlaySound(34);
			CreateBullet(PlayerNum, 102, X, Y, Speed + 8, math.rad(Angle) * -1); -- raketen
		elseif PT == 3 then
			PlaySound(math.random(2,3));
			CreateBullet(PlayerNum, 103, X, Y, Speed + 8, math.rad(Angle) * -1); -- cluster
		end
		
	elseif Typ == 2 then
	
		if PT == 0 then
			CreateBullet(PlayerNum, 100, X, Y, Speed + 8, math.rad(Angle) * -1);
		elseif PT == 1 then
			CreateBullet(PlayerNum, 101, X, Y, Speed + 8, math.rad(Angle) * -1);
		elseif PT == 2 then
			CreateBullet(PlayerNum, 102, X, Y, Speed + 8, math.rad(Angle) * -1);
		elseif PT == 3 then
			CreateBullet(PlayerNum, 103, X, Y, Speed + 8, math.rad(Angle) * -1);
		end
		
	elseif Typ == 3 then -- XXY
		local a = ai.GetPositionFromAngle( (Angle * -1) + 45, 32);
		local b = ai.GetPositionFromAngle( (Angle * -1) - 45, 32);
		
		if PT == 0 then
			PlaySound(34);
			CreateBullet(PlayerNum, 120, X + a.x, Y + a.y, Speed + 12, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 120, X + b.x, Y + b.y, Speed + 12, math.rad(Angle) * -1);
		elseif PT == 1 then
			PlaySound(42);
			CreateBullet(PlayerNum, 151, X, Y, 12, math.rad(Angle + 180) * -1);
		elseif PT == 2 then
			PlaySound(34);
			PlaySound(42);
			CreateBullet(PlayerNum, 112, X, Y, (Speed / 2) + 4, math.rad(180) * -1);
			CreateBullet(PlayerNum, 1120, X, Y, (Speed / 2) + 4, math.rad(180) * -1);
			CreateBullet(PlayerNum, 122, X, Y, 10, math.rad(180) * -1);
		elseif PT == 3 then
			PlaySound(3);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle + 20) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle - 20) * -1);
		end
		
	elseif Typ == 4 then -- XXYY
		local a = ai.GetPositionFromAngle( (Angle * -1) + 45, 32);
		local b = ai.GetPositionFromAngle( (Angle * -1) - 45, 32);
		
		if PT == 0 then
			PlaySound(34);
			CreateBullet(PlayerNum, 120, X + a.x, Y + a.y, Speed + 12, math.rad(Angle + 10) * -1);
			CreateBullet(PlayerNum, 120, X + b.x, Y + b.y, Speed + 12, math.rad(Angle - 10) * -1);
			CreateBullet(PlayerNum, 100, X + a.x, Y + a.y, Speed + 12, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 100, X + b.x, Y + b.y, Speed + 12, math.rad(Angle) * -1);
		elseif PT == 1 then
			PlaySound(25);
			CreateBullet(PlayerNum, 141, X, Y, Speed + 4, math.rad(Angle) * -1);
		elseif PT == 2 then
			PlaySound(34);
			PlaySound(42);
			CreateBullet(PlayerNum, 102, X + a.x, Y + a.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 102, X + b.x, Y + b.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 122, X, Y, 10, math.rad(135) * -1);
			CreateBullet(PlayerNum, 122, X, Y, 10, math.rad(-135) * -1);
		elseif PT == 3 then
			PlaySound(39);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle + 20) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle - 20) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle + 25) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle - 25) * -1);
		end
		
	elseif Typ == 5 then -- XXYYX
		local a = ai.GetPositionFromAngle( (Angle * -1) + 45, 48);
		local b = ai.GetPositionFromAngle( (Angle * -1) - 45, 48);
		
		if PT == 0 then
			PlaySound(34);
			CreateBullet(PlayerNum, 1002, X, Y, Speed + 16, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 4, math.rad(Angle + 75) * -1);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 4, math.rad(Angle - 75) * -1);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 4, math.rad(Angle + 115) * -1);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 4, math.rad(Angle - 115) * -1);
			
			CreateBullet(PlayerNum, 140, X, Y, Speed + 4, math.rad(Angle + 170) * -1);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 4, math.rad(Angle - 170) * -1);
		elseif PT == 1 then
			PlaySound(33);
			CreateBullet(PlayerNum, 1002, X, Y, Speed + 16, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 171, X, Y + 64, Speed - 1, math.rad(0) * -1);
			CreateBullet(PlayerNum, 171, X, Y - 64, Speed - 1, math.rad(0) * -1);
			
			CreateBullet(PlayerNum, 101, X, Y, Speed + 16, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 101, X, Y, Speed + 16, math.rad(Angle + 10) * -1);
			CreateBullet(PlayerNum, 101, X, Y, Speed + 16, math.rad(Angle - 10) * -1);
		elseif PT == 2 then
			PlaySound(34);
			PlaySound(42);
			CreateBullet(PlayerNum, 132, X + a.x, Y + a.y, Speed + 10, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 1002, X, Y, Speed + 16, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 132, X + b.x, Y + b.y, Speed + 10, math.rad(Angle) * -1);
			
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 70) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 110) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle - 70) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle - 110) * -1);
			
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle - 90) * -1);
			
			CreateBullet(PlayerNum, 102, X, Y, 12, math.rad(Angle + 30) * -1);
			CreateBullet(PlayerNum, 102, X, Y, 12, math.rad(Angle - 30) * -1);
		elseif PT == 3 then
			PlaySound(3);
			local c = ai.GetPositionFromAngle( (Angle * -1) + 90, 32);
			local d = ai.GetPositionFromAngle( (Angle * -1) - 90, 32);
			local e = ai.GetPositionFromAngle( (Angle * -1) + 90, 48);
			local f = ai.GetPositionFromAngle( (Angle * -1) - 90, 48);
			CreateBullet(PlayerNum, 1002, X, Y, Speed + 16, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle + 40) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle - 40) * -1);
			CreateBullet(PlayerNum, 113, X + c.x, Y + c.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 113, X + d.x, Y + d.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 103, X + e.x, Y + e.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 103, X + f.x, Y + f.y, Speed + 8, math.rad(Angle) * -1);
		end
		
	elseif Typ == 5.1 then --XXYYX charge
		local a = ai.GetPositionFromAngle( (Angle * -1) + 45, 48);
		local b = ai.GetPositionFromAngle( (Angle * -1) - 45, 48);
		
		if PT == 0 then
			PlaySound(43);
			CreateBullet(PlayerNum, 100, X, Y, Speed + 12, math.rad(Angle) * -1);
		elseif PT == 1 then
			PlaySound(25);
			CreateBullet(PlayerNum, 101, X, Y, Speed + 12, math.rad(Angle) * -1);
		elseif PT == 2 then
			PlaySound(42);
			CreateBullet(PlayerNum, 132, X + a.x, Y + a.y, Speed + 10, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 162, X, Y, Speed + 10, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 132, X + b.x, Y + b.y, Speed + 10, math.rad(Angle) * -1);
		elseif PT == 3 then
			PlaySound(41);
			local c = ai.GetPositionFromAngle( (Angle * -1) + 90, 32);
			local d = ai.GetPositionFromAngle( (Angle * -1) - 90, 32);
			local e = ai.GetPositionFromAngle( (Angle * -1) + 90, 48);
			local f = ai.GetPositionFromAngle( (Angle * -1) - 90, 48);
		
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle + 40) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle - 40) * -1);
			CreateBullet(PlayerNum, 113, X + c.x, Y + c.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 113, X + d.x, Y + d.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 103, X + e.x, Y + e.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 103, X + f.x, Y + f.y, Speed + 8, math.rad(Angle) * -1);
		end
		
	elseif Typ == 6 then
		CreateBullet(PlayerNum, 142, X, Y, Speed + 8, math.rad(Angle) * -1);		
	elseif Typ == 7 then -- XY
		
		if PT == 0 then
			PlaySound(25);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 5, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 5, math.rad(Angle + 180) * -1);
		elseif PT == 1 then
			PlaySound(25);
			CreateBullet(PlayerNum, 121, X, Y, Speed - 2, math.rad(0) * -1);
		elseif PT == 2 then
			PlaySound(33);
			CreateBullet(PlayerNum, 152, X, Y, 4, math.rad(Angle) * -1);
		elseif PT == 3 then
			PlaySound(2);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle) * -1);
		end
	
	elseif Typ == 7.1 then -- XYY
		if PT == 0 then
			PlaySound(25);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 5, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 5, math.rad(Angle - 135) * -1);
		elseif PT == 1 then
			PlaySound(25);
			CreateBullet(PlayerNum, 121, X + 48, Y + 48, Speed - 2, math.rad(0) * -1);
			CreateBullet(PlayerNum, 121, X + 48, Y - 48, Speed - 2, math.rad(0) * -1);
			CreateBullet(PlayerNum, 121, X, Y + 64, Speed - 2, math.rad(0) * -1);
			CreateBullet(PlayerNum, 121, X, Y - 64, Speed - 2, math.rad(0) * -1);
		elseif PT == 2 then
			PlaySound(33);
			CreateBullet(PlayerNum, 152, X, Y, 4, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 152, X, Y, 4, math.rad(Angle - 90) * -1);
		elseif PT == 3 then
			PlaySound(2);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle - 90) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle + 180) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle) * -1);
		end
	
	elseif Typ == 7.2 then -- XYYY
		if PT == 0 then
			PlaySound(25);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 5, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 5, math.rad(Angle - 90) * -1);
		elseif PT == 1 then
			PlaySound(34);
			CreateBullet(PlayerNum, 121, X, Y + 48, Speed - 2, math.rad(0) * -1);
			CreateBullet(PlayerNum, 121, X, Y - 48, Speed - 2, math.rad(0) * -1);
			
			CreateBullet(PlayerNum, 101, X, Y + 48, Speed + 10, math.rad(0) * -1);
			CreateBullet(PlayerNum, 101, X, Y - 48, Speed + 10, math.rad(0) * -1);
			
			CreateBullet(PlayerNum, 201, X, Y, 10, math.rad(180) * -1);
		elseif PT == 2 then
			PlaySound(33);
			CreateBullet(PlayerNum, 152, X, Y, 4, math.rad(Angle + 120) * -1);
			CreateBullet(PlayerNum, 152, X, Y, 4, math.rad(Angle + 240) * -1);
			CreateBullet(PlayerNum, 152, X, Y, 4, math.rad(Angle) * -1);
		elseif PT == 3 then
			PlaySound(2);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle - 90) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle + 180) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle - 45) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle + 135) * -1);
			CreateBullet(PlayerNum, 143, X, Y, 5, math.rad(Angle - 135) * -1);
		end
	
	elseif Typ == 8 then -- X Y Y Y X 
		if PT == 0 then
			PlaySound(34);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 8, math.rad(Angle + 70) * -1);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 8, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 8, math.rad(Angle + 110) * -1);
			
			CreateBullet(PlayerNum, 140, X, Y, Speed + 8, math.rad(Angle - 70) * -1);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 8, math.rad(Angle - 90) * -1);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 8, math.rad(Angle - 110) * -1);
		elseif PT == 1 then
			PlaySound(42);
			CreateBullet(PlayerNum, 121, X, Y + 128, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X - 64, Y + 64, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X - 128, Y, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X + 64, Y - 64, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X, Y - 128, Speed  - 4, math.rad(Angle) * -1);
			
			local a = ai.GetPositionFromAngle( (Angle * -1) + 45, 128);
			local b = ai.GetPositionFromAngle( (Angle * -1) - 45, 128);
			
			CreateBullet(PlayerNum, 191, X + a.x, Y + a.y, Speed, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 191, X + b.x, Y + b.y, Speed, math.rad(Angle) * -1);
		elseif PT == 2 then
			PlaySound(34);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle + 135) * -1);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle + 180) * -1);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle - 135) * -1);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle - 90) * -1);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle - 45) * -1);
			
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 135) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 180) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle - 135) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle - 90) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle - 45) * -1);
		elseif PT == 3 then
			PlaySound(3);
			local a = ai.GetPositionFromAngle( (Angle * -1) + 45, 96);
			local b = ai.GetPositionFromAngle( (Angle * -1) - 45, 96);
			local c = ai.GetPositionFromAngle( (Angle * -1) + 90, 96);
			local d = ai.GetPositionFromAngle( (Angle * -1) - 90, 96);
			local e = ai.GetPositionFromAngle( (Angle * -1) + 135, 96);
			local f = ai.GetPositionFromAngle( (Angle * -1) - 135, 96);
		
			CreateBullet(PlayerNum, 113, X + a.x, Y + a.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 113, X + b.x, Y + b.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 113, X + c.x, Y + c.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 113, X + d.x, Y + d.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 113, X + e.x, Y + e.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 113, X + f.x, Y + f.y, Speed + 8, math.rad(Angle) * -1);
		end
	
	elseif Typ == 9 then -- Y charge´
		
		if PT == 0 then
			PlaySound(34);
			CreateBullet(PlayerNum, 120, X, Y, Speed + 8, math.rad(Angle) * -1);
		elseif PT == 1 then
			PlaySound(42);
			CreateBullet(PlayerNum, 161, X, Y, Speed - 3, math.rad(Angle) * -1);
		elseif PT == 2 then
			PlaySound(34);
			CreateBullet(PlayerNum, 172, X, Y, Speed, math.rad(Angle) * -1);
		elseif PT == 3 then
			PlaySound(41);
			CreateBullet(PlayerNum, 153, X, Y, Speed + 22, math.rad(Angle) * -1);
		end
	
	elseif Typ == 10 then -- Y X charge
		local a = ai.GetPositionFromAngle( (Angle * -1) + 135, 48);
		local b = ai.GetPositionFromAngle( (Angle * -1) - 135, 48);
		
		if PT == 0 then
			PlaySound(34);
			CreateBullet(PlayerNum, 120, X, Y, Speed + 10, math.rad(Angle + 20) * -1);
			CreateBullet(PlayerNum, 120, X, Y, Speed + 10, math.rad(Angle - 20) * -1);
		elseif PT == 1 then
			PlaySound(42);
			CreateBullet(PlayerNum, 171, X + a.x, Y + a.y, Speed - 2, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 171, X + b.x, Y + b.y, Speed - 2, math.rad(Angle) * -1);
		elseif PT == 2 then
			PlaySound(34);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle + 35) * -1);
			CreateBullet(PlayerNum, 172, X, Y, Speed, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 172, X, Y, 12, math.rad(Angle - 35) * -1);
		elseif PT == 3 then
			PlaySound(41);
			CreateBullet(PlayerNum, 153, X, Y, Speed + 22, math.rad(Angle + 5) * -1);
			CreateBullet(PlayerNum, 153, X, Y, Speed + 22, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 153, X, Y, Speed + 22, math.rad(Angle - 5) * -1);
		end
	
	elseif Typ == 11 then -- YXY
		local a = ai.GetPositionFromAngle( (Angle * -1) + 45, 48);
		local b = ai.GetPositionFromAngle( (Angle * -1) - 45, 48);
		
		if PT == 0 then
			PlaySound(34);
			CreateBullet(PlayerNum, 140, X, Y, 8, math.rad(Angle - 115) * -1);
			CreateBullet(PlayerNum, 140, X, Y, 8, math.rad(Angle + 115) * -1);
			
			CreateBullet(PlayerNum, 120, X, Y, Speed + 10, math.rad(Angle) * -1);
			
			CreateBullet(PlayerNum, 100, X + a.x, Y + a.y, 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 100, X + b.x, Y + b.y, 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 100, X + a.x, Y + a.y, 8, math.rad(Angle + 5) * -1);
			CreateBullet(PlayerNum, 100, X + b.x, Y + b.y, 8, math.rad(Angle - 5) * -1);
		elseif PT == 1 then	
			PlaySound(42);
			CreateBullet(PlayerNum, 121, X, Y + 256, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X, Y + 128, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X, Y + 64, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X, Y, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X, Y - 64, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X, Y - 128, Speed  - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X, Y - 256, Speed - 4, math.rad(Angle) * -1);
			
			CreateBullet(PlayerNum, 101, X, Y, Speed + 8, math.rad(Angle + 15) * -1);
			CreateBullet(PlayerNum, 101, X, Y, Speed + 8, math.rad(Angle - 15) * -1);
			
			CreateBullet(PlayerNum, 191, X, Y + 48, Speed + 2, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 191, X, Y - 48, Speed + 2, math.rad(Angle) * -1);
		elseif PT == 2 then
			PlaySound(34);
			PlaySound(42);
			CreateBullet(PlayerNum, 112, X, Y, Speed + 4, math.rad(180) * -1);
			CreateBullet(PlayerNum, 112, X - 48, Y, Speed + 4, math.rad(180) * -1);
			CreateBullet(PlayerNum, 1120, X, Y, Speed + 4, math.rad(180) * -1);
			CreateBullet(PlayerNum, 1120, X - 48, Y, Speed + 4, math.rad(180) * -1);
			
			CreateBullet(PlayerNum, 122, X, Y, 12, math.rad(-90) * -1);
			CreateBullet(PlayerNum, 122, X, Y, 12, math.rad(90) * -1);
			
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 135) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle - 135) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle - 45) * -1);
		elseif PT == 3 then
			PlaySound(42);
			CreateBullet(PlayerNum, 153, X, Y, 22, math.rad(Angle + 135) * -1);
			CreateBullet(PlayerNum, 153, X, Y, 22, math.rad(Angle - 135) * -1);
			CreateBullet(PlayerNum, 153, X, Y, 22, math.rad(Angle + 180) * -1);
			CreateBullet(PlayerNum, 153, X, Y, Speed + 22, math.rad(Angle) * -1);
			
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle + 115) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle - 115) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle + 55) * -1);
			CreateBullet(PlayerNum, 133, X, Y, Speed + 8, math.rad(Angle - 55) * -1);
		end
	
	elseif Typ == 12 then -- X X X X Y
		if PT == 0 then
			PlaySound(12);
			CreateBullet(PlayerNum, 130, X, Y, math.random() * 6, 0);
			CreateBullet(PlayerNum, 130, X, Y, math.random() * 6, 0);
			CreateBullet(PlayerNum, 130, X, Y, math.random() * 6, 0);
			CreateBullet(PlayerNum, 130, X, Y, math.random() * 6, 0);
			CreateBullet(PlayerNum, 130, X, Y, math.random() * 6, 0);
			CreateBullet(PlayerNum, 130, X, Y, math.random() * 6, 0);
			CreateBullet(PlayerNum, 130, X, Y, math.random() * 6, 0);
		elseif PT == 1 then
			PlaySound(26);
			CreateBullet(PlayerNum, 111, X, Y, Speed + 10, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 111, X, Y, Speed + 10, math.rad(Angle - 90) * -1);
			CreateBullet(PlayerNum, 111, X, Y, Speed + 10, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 111, X, Y, Speed + 10, math.rad(Angle - 45) * -1);
			CreateBullet(PlayerNum, 111, X, Y, Speed + 10, math.rad(Angle + 135) * -1);
			CreateBullet(PlayerNum, 111, X, Y, Speed + 10, math.rad(Angle - 135) * -1);
			CreateBullet(PlayerNum, 111, X, Y, Speed + 10, math.rad(Angle + 180) * -1);
			CreateBullet(PlayerNum, 111, X, Y, Speed + 10, math.rad(Angle) * -1);
		elseif PT == 2 then
			PlaySound(42);
			CreateBullet(PlayerNum, 122, X, Y, Speed + 10, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 122, X, Y, Speed + 10, math.rad(Angle - 90) * -1);
			CreateBullet(PlayerNum, 122, X, Y, Speed + 10, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 122, X, Y, Speed + 10, math.rad(Angle - 45) * -1);
			CreateBullet(PlayerNum, 122, X, Y, Speed + 10, math.rad(Angle + 135) * -1);
			CreateBullet(PlayerNum, 122, X, Y, Speed + 10, math.rad(Angle - 135) * -1);
			CreateBullet(PlayerNum, 122, X, Y, Speed + 10, math.rad(Angle + 180) * -1);
			CreateBullet(PlayerNum, 122, X, Y, Speed + 10, math.rad(Angle) * -1);
		elseif PT == 3 then
			PlaySound(3);
			CreateBullet(PlayerNum, 103, X, Y, Speed + 10, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 103, X, Y, Speed + 10, math.rad(Angle - 90) * -1);
			CreateBullet(PlayerNum, 103, X, Y, Speed + 10, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 103, X, Y, Speed + 10, math.rad(Angle - 45) * -1);
			CreateBullet(PlayerNum, 103, X, Y, Speed + 10, math.rad(Angle + 135) * -1);
			CreateBullet(PlayerNum, 103, X, Y, Speed + 10, math.rad(Angle - 135) * -1);
			CreateBullet(PlayerNum, 103, X, Y, Speed + 10, math.rad(Angle + 180) * -1);
			CreateBullet(PlayerNum, 103, X, Y, Speed + 10, math.rad(Angle) * -1);
		end
	
	elseif Typ == 13 then --XXXY
	
		if PT == 0 then
			PlaySound(34);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 8, math.rad(Angle + 15) * -1);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 8, math.rad(Angle - 15) * -1);
		elseif PT == 1 then
			PlaySound(34);
			CreateBullet(PlayerNum, 201, X, Y, 8, math.rad(Angle + 135) * -1);
			CreateBullet(PlayerNum, 201, X, Y, 8, math.rad(Angle + 180) * -1);
			CreateBullet(PlayerNum, 201, X, Y, 8, math.rad(Angle - 135) * -1);
		elseif PT == 2 then
			PlaySound(34);
			CreateBullet(PlayerNum, 102, X, Y, Speed + 8, math.rad(Angle + 10) * -1);
			CreateBullet(PlayerNum, 172, X, Y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 102, X, Y, Speed + 8, math.rad(Angle - 10) * -1);
		elseif PT == 3 then
			PlaySound(2);
			local a = ai.GetPositionFromAngle( (Angle * -1) + 45, 64);
			local b = ai.GetPositionFromAngle( (Angle * -1) - 45, 64);
			local c = ai.GetPositionFromAngle( (Angle * -1) + 90, 64);
			local d = ai.GetPositionFromAngle( (Angle * -1) - 90, 64);
			local e = ai.GetPositionFromAngle( (Angle * -1) + 135, 64);
			local f = ai.GetPositionFromAngle( (Angle * -1) - 135, 64);
		
			CreateBullet(PlayerNum, 123, X + a.x, Y + a.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 123, X + b.x, Y + b.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 123, X + c.x, Y + c.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 123, X + d.x, Y + d.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 123, X + e.x, Y + e.y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 123, X + f.x, Y + f.y, Speed + 8, math.rad(Angle) * -1);
		end
	
	elseif Typ == 14 then -- xxxyy
	
		if PT == 0 then
			PlaySound(43);
			PlaySound(34);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 8, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 150, X, Y, Speed + 8, math.rad(Angle - 90) * -1);
			
			CreateBullet(PlayerNum, 140, X, Y, Speed + 9, math.rad(Angle + 40) * -1);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 9, math.rad(Angle - 20) * -1);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 9, math.rad(Angle + 40) * -1);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 9, math.rad(Angle - 20) * -1);
			CreateBullet(PlayerNum, 140, X, Y, Speed + 9, math.rad(Angle) * -1);
		elseif PT == 1 then
			PlaySound(34);
			PlaySound(42);
			CreateBullet(PlayerNum, 151, X, Y, Speed + 4, math.rad(Angle) * -1);
			
			CreateBullet(PlayerNum, 121, X, Y + 64, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X, Y, Speed - 4, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 121, X, Y - 64, Speed - 4, math.rad(Angle) * -1);
		elseif PT == 2 then
			PlaySound(34);
			PlaySound(33);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle) * -1);
			CreateBullet(PlayerNum, 172, X, Y, Speed + 8, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 172, X, Y, Speed + 8, math.rad(Angle - 45) * -1);
			
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle - 135) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 90) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle - 90) * -1);
			CreateBullet(PlayerNum, 182, X, Y, Speed + 8, math.rad(Angle + 135) * -1);
		elseif PT == 3 then
			PlaySound(3);
			local a = ai.GetPositionFromAngle( (Angle * -1) + 45, 64);
			local b = ai.GetPositionFromAngle( (Angle * -1) - 45, 64);
			local c = ai.GetPositionFromAngle( (Angle * -1) + 90, 64);
			local d = ai.GetPositionFromAngle( (Angle * -1) - 90, 64);
			local e = ai.GetPositionFromAngle( (Angle * -1) + 135, 64);
			local f = ai.GetPositionFromAngle( (Angle * -1) - 135, 64);
		
			CreateBullet(PlayerNum, 113, X + a.x, Y + a.y, Speed + 8, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 113, X + b.x, Y + b.y, Speed + 8, math.rad(Angle - 45) * -1);
			CreateBullet(PlayerNum, 113, X + c.x, Y + c.y, Speed + 8, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 113, X + d.x, Y + d.y, Speed + 8, math.rad(Angle - 45) * -1);
			CreateBullet(PlayerNum, 113, X + e.x, Y + e.y, Speed + 8, math.rad(Angle + 45) * -1);
			CreateBullet(PlayerNum, 113, X + f.x, Y + f.y, Speed + 8, math.rad(Angle - 45) * -1);
		end
		
	end
end