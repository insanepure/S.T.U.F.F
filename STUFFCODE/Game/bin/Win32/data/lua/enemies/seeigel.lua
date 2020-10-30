	-----------------------------------------
	MaxSpeed = 5.0; -- Maximale Speed + PlayerSpeed (Kommt später dazu)    
	AngleSpin = 0.1; -- Drehung in Radiant
	HitBoxX = 28; -- Verschiebung der Hitbox aufn Bild in der X Achse
	HitBoxY = 45; -- Verschiebung der Hitbox aufn Bild in der Y Achse
	HitBoxWidth = 77.0; -- Breite der Hitbox
	HitBoxHeight = 35.0; -- Höhe der Hitbox
	Width = 128.0; -- Reale Breite
	Height = 128.0; -- Reale Höhe        
	Lifes = 50; --Wieviele Schüsse sie aushalten      
	Points = 550; --Wieviele Punkte sie geben
	ArraySize = 3; -- Wiegroß der Array ist        
	CollideDamage = 1; --Schaden der angerichtet wird wenn er kollidiert     
	dieoncollide = false; -- Beim kollidieren sterben
   DamageRadius = 0;
	-----------------------------------------

function Init()
	print("blub");
	return DamageRadius,dieoncollide,CollideDamage,ArraySize,Points,Lifes,Height,Width,MaxSpeed,AngleSpin,HitBoxX,HitBoxY,HitBoxWidth,HitBoxHeight,Lifes;
end

function OnDie()
	print("boom");
end

function Update(Cd,Y_start,State,DamageRadius,Size,PlayerSpeed,timeMultiplicator,Animation,DeleteHim,X,Y,hspeed,Angle,MoveAngle,Cam_X,Cam_Y,Screen_W,Screen_H,Player_X,Player_Y) 
   ------------------
   -- isDoing == 0 -> Kommt ins Bild  
   -- isDoing == 1 -> Wartet       
   -- isDoing == 2 -> Angriff     
   -- isDoing == 3 -> Verschwindet
	
	if State == 0 then
		Y = math.floor(Y);
		Y_start = Y;
		State = 1;
		Cd = 200;
		hspeed = 0;
	elseif State == 1 then
		if Cd == 0 then
			State = 2;
		end
	elseif State == 2 then
		PlaySound(6);
		hspeed = -8;
		State = 3;
		Cd = 390;
	elseif State == 3 then
		if Cd == 0 then
			PlaySound(7);
			CreateBullet(0, 10, X, Y, 10, math.rad(180));
			CreateBullet(0, 10, X, Y, 10, math.rad(-45)); 
			CreateBullet(0, 10, X, Y, 10, math.rad(-90)); 
			CreateBullet(0, 10, X, Y, 10, math.rad(0)); 
			CreateBullet(0, 10, X, Y, 10, math.rad(-135)); 
			State = 4;
		end
	elseif State == 4 then
		if Y == Y_start and hspeed == 0 then
			State = 1;
			Cd = 200;
		end
	end
	
	DeleteHim = false;   
	if Cam_X > X then
		DeleteHim = true;
	end
	
	if Cd > 5 then
		Cd = Cd - (10 * timeMultiplicator);
	else
		Cd = 0;
	end
	
	if Y > Y_start then
		if hspeed < 0 then
			hspeed = hspeed + (0.2 * timeMultiplicator);
		else
			hspeed = hspeed + (0.12 * timeMultiplicator);
		end
	end
	
	Y = Y - (hspeed * timeMultiplicator);
	
	if Y < Y_start then
		Y = Y_start;
		hspeed = 0;
	end
	
	return Cd,Y_start,State,DamageRadius,Size,CollideDamage,Animation,DeleteHim,MoveAngle,X,Y,hspeed,Angle;
end
