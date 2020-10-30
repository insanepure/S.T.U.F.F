local ai = require("data.lua.ext.AiFunctions")

Cam_to_Xprevious = 0;


function SetCam(Player_X,Player_Y,Screen_Width,Screen_Height,Cam_to_X,Cam_to_Y,Cam_D_X,Cam_D_Y,Cam_D_Angle,LevelEnd)
	--Setzt die Cam fest auf den vordersten Player
	-- if (Player_X - (Screen_Width * 1 / 3)) > Cam_to_X then
	
		-- Cam_to_X = (Player_X - (Screen_Width * 1 / 3));
		-- Cam_to_Y = (Player_Y - (Screen_Height / 2));
	-- elseif (Player_X - (Screen_Width * 1 / 5)) < Cam_to_X then			
	
		-- Cam_to_X = (Player_X - (Screen_Width * 1 / 5));
		-- Cam_to_Y = (Player_Y - (Screen_Height / 2));
	-- end
	
	local t = ai.GetPositionFromAngle( math.deg(Cam_D_Angle) * -1, 128);
	
	Cam_to_X = (Cam_D_X + t.x - (Screen_Width * 0.3));
	Cam_to_Y = (Cam_D_Y + t.y - (Screen_Height / 2));
	
	if Cam_to_Xprevious > Cam_to_X then
		Cam_to_X = Cam_to_Xprevious;
	end
	
	if Cam_to_X < 0 then
		Cam_to_X = 0;
	elseif Cam_to_X > LevelEnd - Screen_Width then
		Cam_to_X = LevelEnd - Screen_Width;
	end
	
	Cam_to_Xprevious = Cam_to_X;
	
	return Cam_to_X,Cam_to_Y;
end

function UpdateCam(Cam_to_X,Cam_to_Y,Cam_X,Cam_Y,PlayerSpeed,timeMultiplicator)
	-- if Cam_to_X ~= Cam_X then
		-- Cam_Speed = (Cam_to_X-Cam_X)/8.0;
		-- if Cam_Speed > 22.0 then
			-- Cam_Speed = 22.0;
		-- elseif Cam_Speed < 0 then
			-- Cam_Speed = 0;
		-- end
		-- Cam_X = Cam_X + ((math.pow( Cam_Speed,3)/800.0) + (PlayerSpeed * 0.5)) * timeMultiplicator;
	-- end
	
	-- if Cam_to_Y ~= Cam_Y then
		-- Cam_Speed = (Cam_to_Y-Cam_Y)/20.0;
		-- if Cam_Speed > 20.0 then
			-- Cam_Speed = 20.0;
		-- elseif Cam_Speed < -20.0 then
			-- Cam_Speed = -20.0;
		-- end
		-- Cam_Y = Cam_Y + (math.pow( Cam_Speed,3)/1000.0) * timeMultiplicator;
	-- end
	
	Cam_X = Cam_X + ((Cam_to_X - Cam_X) * 0.1) * timeMultiplicator;
	Cam_Y = Cam_Y + ((Cam_to_Y - Cam_Y) * 0.1) * timeMultiplicator;
	
	return Cam_X,Cam_Y;
end