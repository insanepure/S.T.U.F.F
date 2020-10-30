--load extension
local ai = require("data.lua.ext.AiFunctions")

fishNum = 0;
-----------------------------------------
MaxSpeed = 10.0; -- Maximale Speed + PlayerSpeed (Kommt später dazu)    
AngleSpin = 0.1; -- Drehung in Radiant
HitBoxX = 240 -- Verschiebung der Hitbox aufn Bild in der X Achse
HitBoxY = 160; -- Verschiebung der Hitbox aufn Bild in der Y Achse
HitBoxWidth = 500.0; -- Breite der Hitbox
HitBoxHeight = 280.0; -- Höhe der Hitbox
Width = 917.0; -- Reale Breite
Height = 620.0; -- Reale Höhe
Lifes = 5000; --Wieviele Schüsse sie aushalten
Points = 10; --Wieviele Punkte sie geben
CollideDamage = 0; --Schaden der angerichtet wird wenn er kollidiert
dieoncollide = false; -- Beim kollidieren sterben   
DamageRadius = 0; --Radius indem Schaden gemacht wird
ArraySize = 0; -- Wiegroß der Array ist

value_SwimClose = 400; --Wie nah sich die Fische an den Spieler trauen
SwinCloseVariation = 50;
SwimFar = 600; --Ab wann die Fische schneller Schwimmen um den Spieler zu erreichen

value_MaxForce = 10; --Maximalen Pull zum Spieler
MaxForceVariation = 3; -- Wie sehr er schwankt
value_ConstantForce = 2; -- Standart Pull zum Spieler
ConstantForceVariation = 1; -- Wie sehr er schwankt

State = 0;

SpeedVariation = 3; -- Wie sehr der Speed Schwankt

delete_me_after = 320;
-----------------------------------------
x = 0;
y = 0;
xoffset = 0;
yoffset = 0;
State = 0;
Stance = 0;
i = 0;
Cd = 60;
yoffsetto = 0;
camxprevious = 0;
shootcd = 0;

-- Array Variablen: State, MaxForce, ConstantForce

function Init()
	fishNum = fishNum + 1;
	return DamageRadius,dieoncollide,CollideDamage,ArraySize,Points,Lifes,Height,Width,MaxSpeed,AngleSpin,HitBoxX,HitBoxY,HitBoxWidth,HitBoxHeight;
end

function OnDie()
	fishNum = fishNum - 1;
end
     
function Update(DamageRadius,Size,PlayerSpeed,timeMultiplicator,Animation,DeleteHim,X,Y,Speed,Angle,MoveAngle,Cam_X,Cam_Y,Screen_W,Screen_H,Player_X,Player_Y)
	
	if State == 0 then
		x = X;
		y = Y;
		camxprevious = Cam_X;
		State = 1;
	elseif State == 1 then
		if Cd <= 0 and Stance == 0 then
			local i = math.random(1,4);
			if i == 1 then
				Stance = 1;
				State = 1;
				i = 0;
				Cd =  50;
				Animation = 8;
				yoffsetto = math.random(800) - 400;
			elseif i == 2 then
				Stance = 2;
				PlaySound(22);
				State = 1;
				i = 0;
				Animation = 1;
				yoffsetto = math.random(800) - 400;
			elseif i == 3 then
				Stance = 3;
				State = 1;
				i = 0;
				yoffsetto = math.random(800) - 400;
			elseif i == 4 then
				PlaySound(21);
				Stance = 4;
				State = 1;
				Animation = 7;
				shootcd = 80;
				i = 0;
				Cd = 240;
			end
		end
	end
	
	-- 9 maul lange auf
	-- 8 maul kurz auf
	-- 7 kugle hochhalten
	-- 6 verbuggtes kugel hochhalten
	-- 5 maul ganz wenig auf
	-- 4 kugel geht nach oben und blinkt kurz Oo ?
	-- 3 kugel hoch und schnappt
	-- 2 reist kurz maul auf und leuchtet rot im auge
	-- 1 macht maul extrem weit auf
	if Stance == 3 and (State == 2 or State == 3 or State == 4) then
		x = x - (x - (Cam_X - 500)) * 0.1 * timeMultiplicator;
		y = y - (y - (Cam_Y + (Screen_H / 2))) * 0.02 * timeMultiplicator;
	else
		x = x - (x - (Cam_X + Screen_W)) * 0.1 * timeMultiplicator;
		y = y - (y - (Cam_Y + (Screen_H / 2))) * 0.02 * timeMultiplicator;
	end
	
	if Stance == 1 then -- zuschnappen
		if State == 1 then
			if Cd <= 0 then
				State = 2 ;
			end
		elseif State == 2 then
			i = i + 0.02 * timeMultiplicator;
			xoffset = -Screen_W * 0.5 * ai.Smooth(i);
			yoffset = -yoffsetto * ai.Smooth(i);
			if math.floor(xoffset - 1) <= -Screen_W * 0.5 then
				State = 3;
				Cd = 8;
				PlaySound(20);
			end
		elseif State == 3 then
			if Cd <= 0 then
				State = 4;
				i = 1;
				CreateBullet(0,20,X - 75 + Cam_X - camxprevious,Y + 60,Cam_X - camxprevious + 1,0);
			end
		elseif State == 4 then
			i = i - 0.02 * timeMultiplicator;
			xoffset = -Screen_W * 0.5 * ai.Smooth(i);
			yoffset = -yoffsetto * ai.Smooth(i);
			if math.ceil(xoffset + 1) >= 0 then
				State = 1;
				Stance = 0;
				Cd = math.random(60) + 60;
			end
		end
		
	elseif Stance == 2 then
		if State == 1 then
			i = i + 0.02 * timeMultiplicator;
			yoffset = yoffsetto * ai.Smooth(i);
			if math.floor((yoffset + 0.5)) == math.floor((yoffsetto)) then
				State = 2;
				Cd = 60;
			end
		elseif State == 2 then
			if shootcd <= 0 then
				shootcd = 2;
				PlaySound(34);
				CreateBullet(0,21,X - 75,Y + math.random(180) - 20,20,math.rad(180));
			end
			
			if Cd == 0 then
				State = 3;
			end
		elseif State == 3 then
			i = i - 0.02 * timeMultiplicator;
			yoffset = yoffsetto * ai.Smooth(i);
			if math.floor((yoffset + 0.5) / 10) * 10 == 0 then
				State = 1;
				Stance = 0;
				Cd = math.random(120) + 60;
			end
		end
	
	elseif Stance == 3 then
		if State == 1 then
			i = i + 0.02 * timeMultiplicator;
			xoffset = 500 * ai.Smooth(i);
			if math.ceil((xoffset - 0.5) / 10) * 10 == 500 then
				State = 2;
				Cd = 60;
				Animation = 2;
				x = Cam_X - 500;
				xoffset = 0;
				i = 0;
				Angle = math.rad(180);
			end
		elseif State == 2 then
			i = i + 0.02 * timeMultiplicator;
			xoffset = 1000 * ai.Smooth(i);
			yoffset = yoffsetto * ai.Smooth(i);
			if math.ceil((xoffset - 0.5) / 10) * 10 >= 1000 then
				State = 3;
				Cd = 70;
				shootcd = 10;
				PlaySound(42);
				i = 1;
			end
		elseif State == 3 then
			if shootcd <= 0 then
				local a = math.random(360);
				local b = ai.GetPositionFromAngle(a, 100);
				shootcd = 1;
				CreateBullet(0,22,X + 500 + b.x,Y - 140 + b.y,1,math.rad(a));
			end
			
			if Cd <= 0 then
				State = 4;
			end
		elseif State == 4 then
			i = i - 0.02 * timeMultiplicator;
			yoffset = yoffsetto * ai.Smooth(i);
			xoffset = 1000 * ai.Smooth(i);
			if math.floor((yoffset + 0.5) / 10) * 10 == 0 then
				State = 1;
				Stance = 0;
				Cd = math.random(90) + 120;
				x = Cam_X + Screen_W + 500;
				Angle = 0;
			end
		end
		
	elseif Stance == 4 then
		if State == 1 then
			if shootcd <= 0 then
				CreateBullet(0,24, Cam_X + 15, Cam_Y + math.random(Screen_H),Cam_X - camxprevious + 3,0);
				CreateBullet(0,24, Cam_X + 15, Cam_Y + math.random(Screen_H),Cam_X - camxprevious + 3,0);
				CreateBullet(0,24, Cam_X + 15, Cam_Y + math.random(Screen_H),Cam_X - camxprevious + 3,0);
				CreateBullet(0,24, Cam_X + 15, Cam_Y + math.random(Screen_H),Cam_X - camxprevious + 3,0);
				shootcd = 1000;
			end
	
			if Cd <= 0 then
				shootcd = 0;
				State = 1;
				Stance = 0;
				Cd = math.random(60) + 60;
			end
		end
		
	end
	
	if Cd > 0 then
		Cd = Cd - (1 * timeMultiplicator);
	else
		Cd = 0;
	end
	
	if shootcd > 0 then
		shootcd = shootcd - (1 * timeMultiplicator);
	else
		shootcd = 0;
	end
	
	camxprevious = Cam_X;
	X = x + xoffset;
	Y = y + yoffset;
	
	return DamageRadius,Size,CollideDamage,Animation,DeleteHim,MoveAngle,X,Y,Speed,Angle;
end   
