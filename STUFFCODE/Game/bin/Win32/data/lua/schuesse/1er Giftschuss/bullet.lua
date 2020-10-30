local ai = require("data.lua.ext.AiFunctions")


function Init(Type,X,Y,Angle,Speed)
   --Type = 1 Normaler Schuss
   --Type = 2 Fetzenfisch Schuss
   if Type == 1 then
     --Breite der Hitbox
     Width = 12.0;
     --Höhe der Hitbox
     Height = 12.0;
     --Abstand der Hitbox zum Bild selber
     X_Abstand = 41;
     Y_Abstand = 2;
     --Der Schaden
     Damage = 3;       
     --Speed in Abhängigkeit vom Speed des Spielers
     --Speed = Speed+10.0;
     Collide = false;
     Bounce = 0;
   elseif Type == 2 then   
     --Breite der Hitbox
     Width = 13.0;
     --Höhe der Hitbox
     Height = 8.0;
     --Abstand der Hitbox zum Bild selber
     X_Abstand = 37;
     Y_Abstand = 4;
     --Der Schaden
     Damage = 1;       
     --Speed in Abhängigkeit vom Speed des Spielers
    -- Speed = 20.0;
     Collide = false;
     Bounce = 0;
   end
   --Größe des Arrays
   ArraySize = 0;
	return ArraySize,Speed,Damage,Width,Height,X_Abstand,Y_Abstand,Bounce,Collide;
end

function PreUpdate(timeMultiplicator,LookAngle,Angle,Type,Aim_X,Aim_Y,Player_X,Player_Y,Speed)
		
   return LookAngle,Angle,Speed;
end

function Update(PlayerNum,Type,X,Y,Angle,Aim_X,Aim_Y,Player_X,Player_Y)
   --Wird Speed Mal ausgeführt
	local d = ai.GetPositionFromAngle(math.deg(Angle),1);
	X =X + d.x;
	
	Y =Y + d.y;
	
	die = false;
    if Type == 1 then
		CreateBullet(PlayerNum,2,X-50,Y+30,1.2,math.rad(90)); 
		CreateBullet(PlayerNum,2,X-50,Y+30,1.1,math.rad(90)); 
		CreateBullet(PlayerNum,2,X-50,Y+30,1,math.rad(90));
		die = false;
   end
   return die,X,Y;
end


