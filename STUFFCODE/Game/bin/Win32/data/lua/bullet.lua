local ai = require("data.lua.ext.AiFunctions")
local startzeit = 60;

-- Type 100 - 103 Standart Schuss
-- Type 2 Fetzenfisch Schuss
-- Type 10 Seeigel Stachel

-- 2 stellig: gegner schuss
-- 3 - 4 stellig: Spieler Schuss
-- 1 - 2te stelle: schussart
-- 3te stelle: Spielerart
-- 4te stelle: variation

mini = 4;
light = 10;
medium = 30;
strong = 60;
lazor = 100;
	

function Init(Type,X,Y,Angle,Speed)

	if Type == 100 then -- normal gifttyp schuss
		Damage = medium;       

		Collide = false;     
		hitplayer = false;
		Image = 19;
		Bounce = 0;
		stay = 0.0;
	elseif Type == 110 then -- giftwolke
		Damage = mini;       

		Collide = false;     
		hitplayer = false;
		Image = 12;
		Bounce = 0;
		stay = 3.0;
	elseif Type == 120 then -- giftrakete
		Damage = strong;       

		Collide = false;     
		hitplayer = false;
		Image = 19;
		Bounce = 0;
		stay = 0.0;
	elseif Type == 130 then -- giftwolke explosn
		Damage = light;       

		Collide = false;     
		hitplayer = false;
		Image = 12;
		Bounce = 0;
		stay = 3.0;
	
	elseif Type == 140 then -- giftgranate
		Damage = medium;       

		Collide = true;     
		hitplayer = false;
		Image = 25;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 150 then -- giftrakete explosn
		Damage = medium;       

		Collide = true;     
		hitplayer = false;
		Image = 19;
		Bounce = 0;
		stay = 0.0;
		--HELFER:
	-------------------------------------------------------------------------------
	elseif Type == 101 then -- helfer normal				
		Damage = medium;      
		Collide = false;     
		hitplayer = false;
		Image = 21;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 111 then -- helfer bounce-granaten				
		Damage = strong;      
		Collide = false;     
		hitplayer = false;
		Image = 25;
		Bounce = 2;
		stay = 0.0;
		
	elseif Type == 121 then -- helfer auf berührung granaten/mienen				
		Damage = strong;      
		Collide = false;     
		hitplayer = false;
		Image = 25;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 131 then -- helfer klebe-mienen kleben an wand, warten, boom (wenn möglich) 				   
		Damage = strong;      
		Collide = false;     
		hitplayer = false;
		Image = 25;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 141 then -- helfer cluster mienen					
		Damage = medium;      
		Collide = false;     
		hitplayer = false;
		Image = 25;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 151 then -- helfer HELFERLEIN (spawnpunkt für andere schüsse)	xxxyy	
		Damage = 0;      
		Collide = false;     
		hitplayer = false;
		Image = 20;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 161 then -- helfer HELFERLEIN´s normalschuss drehend (kleiner skalliert weil ja helfer)	(y combo)
		Damage = 0;      
		Collide = false;     
		hitplayer = false;
		Image = 20;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 171 then -- helfer HELFERLEIN´s normalschuss 3x (kleiner skalliert weil ja helfer)	(yx combo)
		Damage = 0;      
		Collide = false;     
		hitplayer = false;
		Image = 20;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 181 then -- helfer HELFERLEIN´s granatomatic
		Damage = 0;      
		Collide = false;     
		hitplayer = false;
		Image = 20;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 191 then -- helfer geschützturm
		Damage = 0;      
		Collide = false;     
		hitplayer = false;
		Image = 20;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 201 then -- helfer nichtlenk-Raketen
		Damage = strong;      
		Collide = false;     
		hitplayer = false;
		Image = 31;
		Bounce = 0;
		stay = 0.0;
			
	elseif Type == 211 then -- helfer normal schuss von helferlein				
		Damage = light;      
		Collide = false;     
		hitplayer = false;
		Image = 21;
		Bounce = 0;
		stay = 0.0;
		
		
		
		--CLUSTER-Typ:
	-----------------------------------------	
			
	elseif Type == 103 then  -- cluster klein
		Damage = medium;      
		Collide = false;     
		hitplayer = false;
		Image = 15;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 113 then  --cluster groß  
		Damage = strong;       
		Collide = false;     
		hitplayer = false;
		Image = 14;
		Bounce = 0;
		stay = 0.0;
	
	elseif Type == 123 then  --cluster klein bounce yxy
		Damage = medium;       
		Collide = false;     
		hitplayer = false;
		Image = 15;
		Bounce = 1;
		stay = 0.0;
		
	elseif Type == 133 then  --cluster groß  bounce xxxyy
		Damage = strong;       
		Collide = false;     
		hitplayer = false;
		Image = 14;
		Bounce = 1;
		stay = 0.0;
		
	elseif Type == 143 then  --cluster groß  "kreist um u-boot herum" xyyyx
		Damage = medium;       
		Collide = false;     
		hitplayer = false;
		Image = 14;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 153 then  -- laser
		Damage = lazor;       
		Collide = false;     
		hitplayer = false;
		Image = 40;
		Bounce = 0;
		stay = 0.0;
	--[[    LASER?
	
	elseif Type == 153 then  -- laser lv 1   (laser hier??? ka ich mach mal)
		Damage = 25;       
		Collide = false;     
		hitplayer = false;
		Image = l_15;
		Bounce = 0;
		stay = 0.0;
		
	elseif Type == 153 then  -- laser lv 2 
		Damage = 40;       
		Collide = false;     
		hitplayer = false;
		Image = l_8;
		Bounce = 0;
		stay = 0.0;
		
	--]]
		
		
		
		--RAKETEN-TYP
	-------------------------
	elseif Type == 102 then -- ncihtlenkrakete
		Damage = medium;       

		Collide = false;     
		hitplayer = false;
		Image = 29;
		Bounce = 0;
		stay = 0.0;
	
	elseif Type == 112 or Type == 1120 then
		Damage = strong;       

		Collide = false;     
		hitplayer = false;
		Image = 29;
		Bounce = 0;
		stay = 0.0;
	elseif Type == 122 then   
		Damage = medium;       
		
		Collide = false;
		hitplayer = false;  
		Image = 27;
		Bounce = 0; 
		stay = 8.0;    
	elseif Type == 132 then   
		Damage = medium;       
		
		Collide = false;
		hitplayer = false;  
		Image = 36;
		Bounce = 2;
		stay = 0.0;    
	elseif Type == 142 then   -- sinus rakete
		Damage = medium;       
		
		Collide = true;
		hitplayer = false;  
		Image = 29;
		Bounce = 0;
		stay = 0.0;    
	elseif Type == 152 then    -- um spieler rumdreh rakete
		Damage = medium;       
		
		Collide = true;
		hitplayer = false;  
		Image = 29;
		Bounce = 0;
		stay = 0.0;    
	elseif Type == 162 then   
		Damage = medium;       
		
		Collide = false;
		hitplayer = false;  
		Image = 26;
		Bounce = 0;
		stay = 8.0;    
	elseif Type == 172 then   -- lenkrakete
		Damage = strong;       
		
		Collide = false;
		hitplayer = false;  
		Image = 29;
		Bounce = 0;
		stay = 0.0;    
	elseif Type == 182 then   -- lasershot
		Damage = medium;       
		
		Collide = false;
		hitplayer = false;  
		Image = 36;
		Bounce = 0;
		stay = 0.0;    
	elseif Type == 1002 then   -- lasershot
		Damage = strong;       
		
		Collide = false;
		hitplayer = false;  
		Image = 1;
		Bounce = 0;
		stay = 0.0;    
	elseif Type == 2 then   
		Damage = 1;       
		
		Speed = 20.0;
		Collide = false;
		hitplayer = true;  
		Image = 17;
		Bounce = 0; 
		stay = 0.0;    
	elseif Type == 3 then   
		Damage = 1;       
		
		Speed = 20.0;
		Collide = false;
		hitplayer = true;  
		Image = 17;
		Bounce = 0; 
		stay = 0.0;    
	elseif Type == 10 then
		Damage = 1;       

		Collide = false;
		hitplayer = true;  
		Image = 16;
		Bounce = 0; 
		stay = 0.0;  
	elseif Type == 20 then -- endbossdmg
		Damage = 1;       

		Collide = false;
		hitplayer = true;  
		Image = 0;
		Bounce = 0; 
		stay = 0.0; 
		Width = 320.0;
		Height = 320.0;
		X_Abstand = 0;
		Y_Abstand = 0;
		
	elseif Type == 21 then -- echsenschuss
		Damage = 1;       

		Collide = false;
		hitplayer = true;  
		Image = 41;
		Bounce = 0; 
		stay = 0.0; 
		BWidth = 130.0;
		BHeight = 54.0;
		Width = 26.0;
		Height = 26.0;
		X_Abstand = 60;
		Y_Abstand = 10;
		
	elseif Type == 22 then -- echsenschuss
		Damage = 1;       

		Collide = false;
		hitplayer = true;  
		Image = math.random(4,7);
		Bounce = 0; 
		stay = 0.5; 
		
	elseif Type == 24 then -- echsenschuss
		Damage = 1;       

		Collide = false;
		hitplayer = true;  
		Image = 24;
		Bounce = 0; 
		stay = 0.0; 
		
	else
		Damage = 1;       
		
		Speed = 20.0;
		Collide = false;
		hitplayer = false;  
		Image = 36;
		Bounce = 0; 
		stay = 0.0;
	end
	
   if Image == 1 then 						 --(ENDBOSS) SCHUSS GROß (Bild 1-3)
      BWidth = 192;
      BHeight = 128;
		--Breite der Hitbox
		Width = 60;
		--Höhe der Hitbox
		Height = 60;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 105;
		Y_Abstand = 33;
		
	elseif Image == 4 or Image == 5 or Image == 6 or Image == 7 then  				--(ENDBOSS) BLITZ LANG (Bild 4-7)
		BWidth = 256;
		BHeight = 128;
		--Breite der Hitbox
		Width = 128;
		--Höhe der Hitbox
		Height = 128;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 64;
		Y_Abstand = 0;
		
	elseif Image == 8 then  				--(ENDOBSS) BLITZ KURZ (Bild 8-11)
		BWidth = 128;
		BHeight = 128;
		--Breite der Hitbox
		Width = 128;
		--Höhe der Hitbox
		Height = 44;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 44;
		
	elseif Image == 12 then  				-- (GIFT-TYP) GIFTWOLKE (Bild 12)
		BWidth = 64;
		BHeight = 64;
		--Breite der Hitbox
		Width = 48;
		--Höhe der Hitbox
		Height = 48;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 9;
		Y_Abstand = 9;
		
	elseif Image == 13 then  				-- (ENDBOSS) RAKETE	(Bild 13)
		BWidth = 13;
		BHeight = 16;
		--Breite der Hitbox
		Width = 9;
		--Höhe der Hitbox
		Height = 9;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 13;
		Y_Abstand = 3;
		
	elseif Image == 14 then  				-- (CLUSTER-TYP) CLUSTER GROß (Bild 14)
		BWidth = 32;
		BHeight = 32;--Breite der Hitbox
		Width = 17;
		--Höhe der Hitbox
		Height = 17;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 8;
		Y_Abstand = 8;
		
	elseif Image == 15 then  				-- (CLUSTER-TYP / HELFER) CLUSTER KLEIN (Bilde 15)
		BWidth = 20;
		BHeight = 16;--Breite der Hitbox
		Width = 7;
		--Höhe der Hitbox
		Height = 7;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 6;
		Y_Abstand = 5;
		
	elseif Image == 16 then  				-- (GEGNER) DRECKSACK-FISCH STACHEL (Bild 16)
		BWidth = 47;
		BHeight = 16;--Breite der Hitbox
		Width = 9;
		--Höhe der Hitbox
		Height = 9;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 23;
		Y_Abstand = 4;
		
	elseif Image == 17 then  				-- (GEGNER) FETZEN-FISCH (Bild 17)
		BWidth = 36;
		BHeight = 18;--Breite der Hitbox
		Width = 8;
		--Höhe der Hitbox
		Height = 8;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 22;
		Y_Abstand = 5;
		
	elseif Image == 18 then  				-- (GEGNER) MASKEN-FISCH (Bild 18)
		BWidth = 47;
		BHeight = 16;
	  --Breite der Hitbox
		Width = 9;
		--Höhe der Hitbox
		Height = 9;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 24;
		Y_Abstand = 4;
		
	elseif Image == 19 then  				-- (GIFT-TYP) PFEILE (Bild 19)
		BWidth = 45;
		BHeight = 16;
		--Breite der Hitbox
		Width = 16;
		--Höhe der Hitbox
		Height = 16;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 26;
		Y_Abstand = 0;
		
	elseif Image == 20 then  				-- (HELFER-TYP) HELFER (Bild 20) "kiene" Hitbox
		BWidth = 20;
		BHeight = 20;
		--Breite der Hitbox
		Width = 2;
		--Höhe der Hitbox
		Height = 2;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 9;
		Y_Abstand = 9;
		
	elseif Image == 21 then  				-- (HELFER-TYP) NORMAL-SCHUSS (Bild 21)
		BWidth = 40;
		BHeight = 16;
		--Breite der Hitbox
		Width = 16;
		--Höhe der Hitbox
		Height = 16;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 21;
		Y_Abstand = 0;
		
	elseif Image == 22 or Image == 23 or Image == 24 then  				-- (FETTES U-BOOT) LIELA FETTER SCHUSS (Bild 22-24)
		BWidth = 128;
		BHeight = 64;
		--Breite der Hitbox
		Width = 45;
		--Höhe der Hitbox
		Height = 45;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 79;
		Y_Abstand = 10;
		
	elseif Image == 25 then  				-- (SPIELER) MIENE (Bild 25)
		BWidth = 32;
		BHeight = 32;
		--Breite der Hitbox
		Width = 32;
		--Höhe der Hitbox
		Height = 32;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 0;
		
	elseif Image == 26 then  				-- (RAKETEN-TYP) SCHALLSCHUSS KLEIN (Bild 26)
		BWidth = 30;
		BHeight = 105;
		--Breite der Hitbox
		Width = 107;
		--Höhe der Hitbox
		Height = 107;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = -76;
		Y_Abstand = 0;
		
	elseif Image == 27 then  				-- (RAKETEN-TYP) SCHALLSCHUSS MITTEL (Bild 27)
		BWidth = 40;
		BHeight = 140;
		--Breite der Hitbox
		Width = 140;
		--Höhe der Hitbox
		Height = 140;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = -100;
		Y_Abstand = 0;
		
	elseif Image == 28 then  				-- (RAKETEN-TYP) SCHALLSCHUSS GROß (Bild 28)
		BWidth = 50;
		BHeight = 175;
		--Breite der Hitbox
		Width = 175;
		--Höhe der Hitbox
		Height = 175;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = -125;
		Y_Abstand = 0;
		
	elseif Image == 29 then  				-- (RAKETEN-TYP) RAKETE (Bild 29)
		BWidth = 30;
		BHeight = 16;
		--Breite der Hitbox
		Width = 13;
		--Höhe der Hitbox
		Height = 13;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 8;
		Y_Abstand = 2;
		
	elseif Image == 30 then  				-- (SPILER) RAKETE BLAU wird im moment nicht benötigt (Bild 30)
		BWidth = 30;
		BHeight = 16;
		--Breite der Hitbox
		Width = 13;
		--Höhe der Hitbox
		Height = 13;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 8;
		Y_Abstand = 2;
		
	elseif Image == 31 then  				-- (HELFER-TYP) RAKETE (Bild 31)
		BWidth = 30;
		BHeight = 16;
		--Breite der Hitbox
		Width = 13;
		--Höhe der Hitbox
		Height = 13;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 8;
		Y_Abstand = 2;
	
	
	elseif Image == 32 then  				-- (GIFT-TYP) RAKETE (Bild 32)
		BWidth = 30;
		BHeight = 16;
		--Breite der Hitbox
		Width = 13;
		--Höhe der Hitbox
		Height = 13;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 8;
		Y_Abstand = 2;
		
	elseif Image == 33 then  				-- (ENDBOSS) SCHALLSCHUSS KLEIN (Bild 33)
		BWidth = 30;
		BHeight = 105;
		--Breite der Hitbox
		Width = 105;
		--Höhe der Hitbox
		Height = 105;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = -74;
		Y_Abstand = 0;
		
	elseif Image == 34 then  				-- (ENDBOSS) SCHALLSCHUSS MITTEL (Bild 34)
		BWidth = 40;
		BHeight = 140;
		--Breite der Hitbox
		Width = 140;
		--Höhe der Hitbox
		Height = 140;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = -100;
		Y_Abstand = 0;
		
	elseif Image == 35 then  				-- (ENDBOSS) SCHALLSCHUSS GROß (Bild 35)
		BWidth = 50;
		BHeight = 175;
		--Breite der Hitbox
		Width = 175;
		--Höhe der Hitbox
		Height = 175;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = -125;
		Y_Abstand = 0;
		
	elseif Image == 36 then  				-- (SPIELER) NORMALSCHUSS ROT (Bild 36)
		BWidth = 55;
		BHeight = 16;
		--Breite der Hitbox
		Width = 12.0;
		--Höhe der Hitbox
		Height = 12.0;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 41;
		Y_Abstand = 2;
		
	elseif Image == 37 then  				-- (SPIELER) NORMALSCHUSS BLAU (Bild 37)
		BWidth = 55;
		BHeight = 16;
		--Breite der Hitbox
		Width = 12.0;
		--Höhe der Hitbox
		Height = 12.0;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 41;
		Y_Abstand = 2;
		
	elseif Image == 38 then  				-- (SPIELER) NORMALSCHUSS GELB (Bild 38)
		BWidth = 55;
		BHeight = 16;
		--Breite der Hitbox
		Width = 12.0;
		--Höhe der Hitbox
		Height = 12.0;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 41;
		Y_Abstand = 2;
		
	elseif Image == 39 then  				-- (SPIELER) NORMALSCHUSS GRÜN (Bild 39)
		BWidth = 55;
		BHeight = 16;
		--Breite der Hitbox
		Width = 12.0;
		--Höhe der Hitbox
		Height = 12.0;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 41;
		Y_Abstand = 2;
	elseif Image == 40 then  				-- (SPIELER) NORMALSCHUSS GRÜN (Bild 39)
		BWidth = 105;
		BHeight = 32;
		--Breite der Hitbox
		Width = 23.0;
		--Höhe der Hitbox
		Height = 23.0;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 36;
		Y_Abstand = 8;
	end
	-- else -- Safe
		-- BWidth = 192;
      -- BHeight = 128;
		-- Breite der Hitbox
		-- Width = 12.0;
		-- Höhe der Hitbox
		-- Height = 12.0;
		-- Abstand der Hitbox zum Bild selber
		-- X_Abstand = 41;
		-- Y_Abstand = 2;
   -- end
	
	ArraySize = 21;
	return ArraySize,stay,Speed,Image,Damage,BWidth,BHeight,Width,Height,X_Abstand,Y_Abstand,Bounce,Collide,hitplayer;
end

function OnDie(Bullet_X,Bullet_Y,Bullet_Type)
	if Bullet_Type == 140 or Bullet_Type == 150 then
		PlaySound(math.random(12,13));
		CreateBullet(0, 130, Bullet_X, Bullet_Y, math.random() * 6, 0);
		CreateBullet(0, 130, Bullet_X, Bullet_Y, math.random() * 6, 0);
		CreateBullet(0, 130, Bullet_X, Bullet_Y, math.random() * 6, 0);
		CreateBullet(0, 130, Bullet_X, Bullet_Y, math.random() * 6, 0);
	elseif Bullet_Type == 141 then
		PlaySound(26);
		CreateBullet(0, 121, Bullet_X, Bullet_Y, 4, math.rad(math.random(360)));
		CreateBullet(0, 121, Bullet_X, Bullet_Y, 4, math.rad(math.random(360)));
		CreateBullet(0, 121, Bullet_X, Bullet_Y, 4, math.rad(math.random(360)));
		CreateBullet(0, 121, Bullet_X, Bullet_Y, 4, math.rad(math.random(360)));
	end
end

------start at image

function PreUpdate(spawn_type,spawn_cd,lifetime,Xprev,Yprev,angle,ii,changeto,x,y,direction_state,direction_change_type,direction_change_intensity,speed_to,speed_change,speed_change_type,size_to,size_change,State,Die,move,Image,Size,timeMultiplicator,LookAngle,Angle,Type,Aim_X,Aim_Y,Player_X,Player_Y,Speed)
	
	x = x / 100;
	y = y / 100;
	angle = angle / 100;
	ii = ii / 100;
	LookAngle = math.deg(LookAngle);
	speed_change = speed_change / 1000;
	direction_change_intensity = direction_change_intensity / 1000;
	Angle = math.deg(Angle);
	Angle = ai.SmallestAngle( 0, Angle);
	lifetime = lifetime / 1000;


	size_change = size_change / 1000;
	spawn_cd = spawn_cd / 100;

	
	if State == 0 then
		Die = 0;
		
		if Speed < 1 then
			Speed = 10;
			move = 1;
		end
		
		lifetime = 1800;
		
		if Type == 10 then
			speed_change_type = 2; -- flat speed changeing, delete when size_to is reached
			speed_change = -0.16;
			speed_to = 0;
		elseif Type == 110 then
			Size = math.random() / 5 + 0.2;
			size_to = math.random() * 2 + 0.5;
			size_change = math.random() / 10;
			direction_change_type = 6;
			direction_change_intensity = math.random();
			Angle = math.random(360);
			lifetime = 900;
		elseif Type == 130 then
			Size = math.random() / 5 + 0.2;
			size_to = math.random() * 3 + 2;
			size_change = math.random() / 5;
			speed_change_type = 1;
			speed_change = -0.1;
			speed_to = 0;
			lifetime = 900;
			Angle = math.random(360);
		elseif Type == 120 then
			spawn_type = 1;
		elseif Type == 112 then
			direction_change_type = 1; -- start at 0° then go to 180° via 90°, then speed up
			direction_change_intensity = 9;
			speed_change = 0.4;
			speed_to = 24;
			changeto = 1;
		elseif Type == 1120 then
			direction_change_type = 2;
			direction_change_intensity = 9;
			speed_change = 0.4;
			speed_to = 24;
			changeto = 1;
		elseif Type == 142 then
			direction_change_type = 4;
			direction_change_intensity = math.random() / 2;
			speed_change = math.random() * 64;
		elseif Type == 152 then
			direction_change_type = 5;
			direction_change_intensity = 0.5;
			ii = 48;
			lifetime = 4800;
		elseif Type == 122 then
			Size = 0.5;
			size_change = 0.05;
			size_to = 2;
		elseif Type == 172 then
			direction_change_type = 3;
			speed_change_type = 1;
			speed_change = 1;
			speed_to = 24;
			direction_change_intensity = 0.1;
		elseif Type == 161 then
			spawn_type = 2;
			spawn_cd = 200;
			lifetime = 1800;
		elseif Type == 171 then
			spawn_type = 3;
			spawn_cd = 200;
			lifetime = 1800;
		elseif Type == 140 then
			lifetime = 110;
		elseif Type == 150 then
			speed_change_type = 1;
			speed_change = 1.8;
			speed_to = 36;
		elseif Type == 151 then
			spawn_type = 4;
			spawn_cd = 100;
			lifetime = 1010;	
		elseif Type == 191 then
			lifetime = 2410;
			spawn_type = 5;
			spawn_cd = 200;
		elseif Type == 143 then
			direction_change_type = 5;
			direction_change_intensity = 0.3;
			lifetime = 1910;
			ii = 64;
		elseif Type == 141 then
			lifetime = 210;
		elseif Type == 181 then
			lifetime = 1810;
			spawn_type = 6;
			spawn_cd = 200;
		elseif Type == 20 then
			lifetime = 40;
		elseif Type == 21 then
			direction_change_type = 4;
			direction_change_intensity = math.random() / 2;
			speed_change = math.random() * 64;
		elseif Type == 22 then
			lifetime = 80;
			LookAngle = Angle;
			angle = Angle;
			Size = 0.8
		elseif Type == 24 then
			lifetime = 8000;
			LookAngle = Angle;
			angle = Angle;
		elseif Type == 3 then
			Size = 3;
		end
		
	elseif State == 1 then
	
		if direction_change_type == 1 then -- turn to front
		
			if direction_state == 0 then
				if Angle > -20 then
					Angle = Angle - direction_change_intensity * timeMultiplicator;
				else
					direction_state = 1;
				end
			elseif direction_state == 1 then
				if Angle < 0 then
					Angle = Angle + direction_change_intensity / 4 * timeMultiplicator;
				else
					if changeto == 1 then
						direction_state = 0;
						Angle = 0;
						speed_change_type = 1;
						direction_change_type = 3;
						direction_change_intensity = 0.1;
					else
						direction_state = 3;
					end
				end
			end
			
		elseif direction_change_type == 2 then -- turn to front via the other way
			
			if direction_state == 0 then
				if math.ceil(Angle/3) * 3 == 180 then
					Angle = -180;
				end
				
				if Angle < 20 then
					Angle = Angle + direction_change_intensity * timeMultiplicator;
				else
					direction_state = 1;
				end
			elseif direction_state == 1 then
				if Angle > 0 then
					Angle = Angle - direction_change_intensity / 4 * timeMultiplicator;
				else
					if changeto == 1 then
						direction_state = 0;
						Angle = 0;
						speed_change_type = 1;
						direction_change_type = 3;
						direction_change_intensity = 0.1;
					else
						direction_state = 3;
					end
				end
			end
			
		elseif direction_change_type == 3 then -- fly to nearest enemy
			
			if Aim_X ~= 0 then
				local a = ai.GetAngle( x, y, Aim_X, Aim_Y);
				local ad = ai.SmallestAngle( Angle, a);
				
				Angle = Angle + (ad * direction_change_intensity * timeMultiplicator);
			end
		elseif direction_change_type == 5 then
			Angle = Angle + Speed * timeMultiplicator;
			ii = ii + direction_change_intensity * timeMultiplicator;
			angle = ai.GetAngle( x, y, Player_X, Player_Y) - 90;
		end
		
		if spawn_type == 2 then
			ii = ii + 0.08 * timeMultiplicator;
		end
		
	end
	
	if Type == 24 then
		Speed = Speed + 0.15 * timeMultiplicator;
	end
	if size_change ~= 0 then
		if size_change > 0 then
			if Size < size_to then
				Size = Size + size_change * timeMultiplicator;
			end
		elseif size_change < 0 then
			if Size > size_to then
				Size = Size + size_change * timeMultiplicator;
			end
		end
	end
	if speed_change_type == 1  or speed_change_type == 2 then -- flat speed change

		if speed_change > 0 then
			if Speed < speed_to then
				Speed = Speed + speed_change * timeMultiplicator;
			end
		elseif speed_change < 0 then
			if Speed > speed_to then
				Speed = Speed + speed_change * timeMultiplicator;
			end
		end
		
		if speed_change_type == 2 then
			if speed_change > 0 then
				if math.ceil(Speed) >= speed_to  - 1 then
					Die = 1;
				end
			elseif speed_change < 0 then
				if math.floor(Speed) <= speed_to + 1 then
					Die = 1;
				end
			end
		end
		
		if Speed < 1 then
			Speed = 1;
			move = 1;
		end
	end
	
	if lifetime > 0 then
		lifetime = lifetime - 9.9 * timeMultiplicator;
	elseif lifetime <= 20 and lifetime ~= 0 then
		Die = 1;
	end

	if lifetime == 0 then
		print("www");
	end
	
	if direction_change_type ~= 6 then
		LookAngle = angle;
	else
		LookAngle = LookAngle + direction_change_intensity * timeMultiplicator;
	end
	
	spawn_cd = spawn_cd * 100;
	LookAngle = math.rad(LookAngle);
	x = x * 100;
	size_change = size_change * 1000;
	lifetime = lifetime * 1000;
	y = y * 100;
	Angle = math.rad(Angle);
	ii = ii * 100;
	angle = angle * 100;
	speed_change = speed_change * 1000;
	direction_change_intensity = direction_change_intensity * 1000;
	return spawn_type,spawn_cd,lifetime,Xprev,Yprev,angle,ii,changeto,x,y,direction_state,direction_change_type,direction_change_intensity,speed_to,speed_change,speed_change_type,size_to,size_change,State,Die,move,Image,Size,LookAngle,Angle,Speed;
end

-----start at playernum

function Update(spawn_type,spawn_cd,lifetime,Xprev,Yprev,angle,ii,changeto,x,y,direction_state,direction_change_type,direction_change_intensity,speed_to,speed_change,speed_change_type,size_to,size_change,State,Die,move,PlayerNum,Type,X,Y,Angle,Aim_X,Aim_Y,Player_X,Player_Y,deltaTime)
	
	Xprev = Xprev / 100;
	angle = angle / 100;
	Yprev = Yprev / 100;
	x = x / 100;
	y = y / 100;
	Angle = math.deg(Angle);
	ii = ii / 100;
	speed_change = speed_change / 1000;
	direction_change_intensity = direction_change_intensity / 1000;
	spawn_cd = spawn_cd / 100;
	
	if State == 0 then
		State = 1;
		x = X;
		y = Y;
	end
	
	--Wird Speed Mal ausgeführt
	if move == 0 then
		if direction_change_type == 5 then
			local d = ai.GetPositionFromAngle(Angle, ii);
			x = Player_X + (d.x * deltaTime);
			y = Player_Y + (d.y * deltaTime);
		elseif direction_change_type == 6 then
		
		else
			local d = ai.GetPositionFromAngle(Angle, 1);
			x = x + (d.x * deltaTime);
			y = y + (d.y * deltaTime);
		end
	end
	
	if direction_change_type == 5 then
		local da = ai.GetPositionFromAngle(Angle, 1);
	end
	
	if Die == 0 then
		die = false;
	else
		die = true;
	end
	
	if direction_change_type ~= 4 then
		X = x;
		Y = y;
	else
		local s = ai.SinusModification( Angle, ii, speed_change);
		X = x + (s.x * deltaTime);
		Y = y + (s.y * deltaTime);
		ii = ii + direction_change_intensity;
	end
	
	if spawn_cd > 0 then
		if spawn_type == 1 then
			spawn_cd = spawn_cd - 1;
		else
			if move == 0 then
				spawn_cd = spawn_cd - (1/ai.GetDistance( Xprev, Yprev, x, y));
			else
				spawn_cd = spawn_cd - 0.1;
			end
		end
	else
		if spawn_type == 1 then
			CreateBullet(0, 110, x + math.random(16) - 8, y + math.random(16) - 8, 1, 0);
			spawn_cd = 64;
		elseif spawn_type == 2 then
			CreateBullet(0, 211, x, y, 6, math.rad(180 + math.sin(ii) * 90));
			spawn_cd = 200;
			PlaySound(38);
		elseif spawn_type == 3 then
			CreateBullet(0, 211, x, y, 6, math.rad(180));
			CreateBullet(0, 211, x, y, 6, math.rad(135));
			CreateBullet(0, 211, x, y, 6, math.rad(-135));
			spawn_cd = 200;
			PlaySound(38);
		elseif spawn_type == 4 then
			CreateBullet(0, 211, x, y, 10, math.rad(90));
			CreateBullet(0, 211, x, y, 10, math.rad(-90));
			spawn_cd = 300;
			PlaySound(38);
		elseif spawn_type == 5 then
			local ang = ai.GetAngle( x, y, Aim_X, Aim_Y);
			CreateBullet(0, 211, x, y, 22, math.rad(ang));
			spawn_cd = 200;
			PlaySound(38);
		elseif spawn_type == 5 then
			local ang = math.random(360);
			CreateBullet(0, 121, x, y, 4, math.rad(ang));
			spawn_cd = 200;
			PlaySound(38);
		end
	end
	
	if move == 0 then
		angle = ai.GetAngle( Xprev, Yprev, X, Y);
	end
	
	spawn_cd = spawn_cd * 100;
	x = x * 100;
	y = y * 100;
	ii = ii * 100;
	Xprev = X;
	Yprev = Y;
	Xprev = Xprev * 100;
	angle = angle * 100;
	Yprev = Yprev * 100;
	speed_change = speed_change * 1000;
	direction_change_intensity = direction_change_intensity * 1000;
	return spawn_type,spawn_cd,lifetime,Xprev,Yprev,angle,ii,changeto,x,y,direction_state,direction_change_type,direction_change_intensity,speed_to,speed_change,speed_change_type,size_to,size_change,State,Die,move,die,X,Y;
end


