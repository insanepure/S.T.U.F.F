local ai = require("data.lua.ext.AiFunctions")

function Init(Type)
	if Type == 2 then
		Image_B = 5; --Bild des Anfanges
		X_B = 0; --X Abstand vom Bild
		Y_B = 0; -- Y Abstand vom Bild
		W_B = 170.0; --Breite
		H_B = 125.0; --Höhe       
		Image_MS = 6; --Bild der Mitte (erster Teil)
		X_MS = 0.0;
		Y_MS = 0;
		W_MS = 214.0;
		H_MS = 125.0;
		Image_ML = 7; -- Bild des loopenden Teil
		X_ML = 0.0;
		Y_ML = 0;
		W_ML = 4.0; -- Ist die Breite der Kollisionsbox, Länge = W_ML*Length (Wird beim CreateLaser definiert)
		H_ML = 125.0;
		Image_E = 7; --Bild des Endteils
		X_E = 0.0;
		Y_E = 0;
		W_E = 4;
		H_E = 125.0;
		Hitplayer = false;
	elseif Type == 1 then
		Image_B = 2;
		X_B = 0;
		Y_B = 0;
		W_B = 127.0;
		H_B = 125.0;        
		Image_MS = 2;
		X_M = 130.0;
		Y_M = 0;
		W_M = 1.0;
		H_M = 124.0;
		Image_ML = 2;
		X_ML = 130.0;
		Y_ML = 0;
		W_ML = 4.0;
		H_ML = 124.0;
		Image_E = 2;
		X_E = 150.0;
		Y_E = 0;
		W_E = 4;
		H_E = 124.0;   
		Hitplayer = false;
	elseif Type == 103 then
		Image_B = 8;
		X_B = 0;
		Y_B = 0;
		W_B = 16.0;
		H_B = 48.0;        
		Image_MS = 8;
		X_M = 0.0;
		Y_M = 0;
		W_M = 0.0;
		H_M = 0.0;
		Image_ML = 8;
		X_ML = 17.0;
		Y_ML = 0;
		W_ML = 86.0;
		H_ML = 48.0;
		Image_E = 8;
		X_E = 104.0;
		Y_E = 0;
		W_E = 25;
		H_E = 48.0;   
		Hitplayer = false;
	elseif Type == 104 then
		Image_B = 5;
		X_B = 0;
		Y_B = 0;
		W_B = 170.0;
		H_B = 125.0;        
		Image_MS = 6;
		X_M = 0.0;
		Y_M = 0;
		W_M = 214.0;
		H_M = 125.0;
		Image_ML = 7;
		X_ML = 0.0;
		Y_ML = 0;
		W_ML = 214.0;
		H_ML = 125.0;
		Image_E = 0;
		X_E = 0.0;
		Y_E = 0;
		W_E = 0;
		H_E = 0.0;   
		Hitplayer = false;
	end
	return Hitplayer,Image_B,X_B,Y_B,W_B,H_B,Image_MS,X_MS,Y_MS,W_MS,H_MS,Image_ML,X_ML,Y_ML,W_ML,H_ML,Image_E,X_E,Y_E,W_E,H_E;
end     


--Wie PreUpdate, einmal ausgeführt
function Update(timeMultiplicator,Angle,Type,Player_X,Player_Y,Player_Angle)
     X = Player_X + 120;
     Y = Player_Y;	
     Angle = 0;
   return X,Y,Angle;
end


--[[elseif Image == l_1 then    -- (ENDBOSS) DISCOLASER "ANFANG" (Bild l_1)
		--Breite der Hitbox
		Width = 22;
		--Höhe der Hitbox
		Height = 14;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 13;
		
	elseif Image == l_2 then   -- (ENDBOSS) FETTER LASER (Bild l_2 - l_4)
		--Breite der Hitbox
		Width = 250;
		--Höhe der Hitbox
		Height = 58;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 29;
		
	elseif Image == 32 then    -- (GROßES U-BOOT) FETTER LASER (Bild l_5)
		--Breite der Hitbox
		Width = 143;
		--Höhe der Hitbox
		Height = 102;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 11;
		Y_Abstand = 11;
		
	elseif Image == 33 then  -- (GROßES U-BOOT) FETTER LASER (Bild l_6 - l_7)
		--Breite der Hitbox
		Width = 214;
		--Höhe der Hitbox
		Height = 49;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 39;
		
	elseif Image == 33 then  -- (CLUSTER-TYP) LASER LV2 (Bild l_8)
		--Breite der Hitbox
		Width = 128;
		--Höhe der Hitbox
		Height = 18;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 15;
		
	elseif Image == 33 then  -- (ENDBOSS) DISCOLASER LASER SCHUSS 1 LILA (Bild l_9)
		--Breite der Hitbox
		Width = 105;
		--Höhe der Hitbox
		Height = 5;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 16;
		
	elseif Image == 33 then  -- (ENDBOSS) DISCOLASER LASER SCHUSS 2 TÜRKIES (Bild l_10)
		--Breite der Hitbox
		Width = 105;
		--Höhe der Hitbox
		Height = 5;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 17;
		
	elseif Image == 33 then  -- (ENDBOSS) DISCOLASER LASER SCHUSS 3 GRÜN (Bild l_11)
		--Breite der Hitbox
		Width = 0;
		--Höhe der Hitbox
		Height = 17;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 106;
		Y_Abstand = 6;
		
	elseif Image == 33 then  -- (ENDBOSS) DISCOLASER LASER SCHUSS 4  ORANGE (Bild l_12)
		--Breite der Hitbox
		Width = 105;
		--Höhe der Hitbox
		Height = 4;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 18;
		
	elseif Image == 33 then  -- (ENDBOSS) DISCOLASER LASER SCHUSS 5 DUNKELBLAU (Bild l_13)
		--Breite der Hitbox
		Width = 105;
		--Höhe der Hitbox
		Height = 4;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 18;
		
	elseif Image == 33 then  -- (GROßES U-BOOT) ANFANG FETTER LASER ROT (Bild l_14)
		--Breite der Hitbox
		Width = 128;
		--Höhe der Hitbox
		Height = 8;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 12;
		
	elseif Image == 33 then  -- (CLUSTER-TYP) LASER LV 1 (Bild l_15)
		--Breite der Hitbox
		Width = 128;
		--Höhe der Hitbox
		Height = 7;
		--Abstand der Hitbox zum Bild selber
		X_Abstand = 0;
		Y_Abstand = 20;
--]]