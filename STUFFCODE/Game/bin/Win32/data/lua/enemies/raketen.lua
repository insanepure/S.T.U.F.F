	-----------------------------------------
   MaxSpeed = 5.0; -- Maximale Speed + PlayerSpeed (Kommt später dazu)    
   AngleSpin = 0.1; -- Drehung in Radiant
	 HitBoxX = 3; -- Verschiebung der Hitbox aufn Bild in der X Achse
	 HitBoxY = 4; -- Verschiebung der Hitbox aufn Bild in der Y Achse
	 HitBoxWidth = 250.0; -- Breite der Hitbox
	 HitBoxHeight = 120.0; -- Höhe der Hitbox
	 Width = 256.0; -- Reale Breite
	 Height = 128.0; -- Reale Höhe        
   Lifes = 3; --Wieviele Schüsse sie aushalten   
   Points = 10; --Wieviele Punkte sie geben
   ArraySize = 3; -- Wiegroß der Array ist      
   CollideDamage = 1; --Schaden der angerichtet wird wenn er kollidiert 
   dieoncollide = false; -- Beim kollidieren sterben
   DamageRadius = 0;
	-----------------------------------------

function Init()
	return DamageRadius,dieoncollide,CollideDamage,ArraySize,Points,Lifes,Height,Width,MaxSpeed,AngleSpin,HitBoxX,HitBoxY,HitBoxWidth,HitBoxHeight,Lifes;
end
  
function OnDie()

end

function Update(isDoing,Cooldown,Attacks,DamageRadius,Size,PlayerSpeed,timeMultiplicator,Animation,DeleteHim,X,Y,Speed,Angle,MoveAngle,Cam_X,Cam_Y,Screen_W,Screen_H,Player_X,Player_Y) 
   ------------------
   -- isDoing == 0 -> Kommt ins Bild  
   -- isDoing == 1 -> Wartet       
   -- isDoing == 2 -> Angriff     
   -- isDoing == 3 -> Verschwindet
   ------------------ 
   DeleteHim = false;   
	if isDoing == 3 then -- "Geht" aus dem Bild 
      Angle = 0.0;
      X = X-1;
      DeleteHim = true; -- Wird benutzt um den Rammfisch beim verlassen des Bildes zu löschen
	elseif isDoing == 2 then --Wenn der Rammfisch angreift 
		X = X + (Speed * timeMultiplicator * math.sin(Angle + math.pi/2));
		Y = Y - (Speed * timeMultiplicator * math.cos(Angle + math.pi/2));
      --Wenn er aus dem Bild ist, setze ihn ins Bild
      if X < Cam_X then
		   X = Cam_X;
			isDoing = 1;
			Cooldown = 100;
         Attacks = Attacks+1;
		elseif X > Cam_X+Screen_W-Width then
			X = Cam_X+Screen_W-Width;
			isDoing = 1;
			Cooldown = 100; 
         Attacks = Attacks+1;
		elseif Y < Cam_Y then
			Y = Cam_Y;
			isDoing  = 1;
			Cooldown = 100;
         Attacks = Attacks+1;
		elseif Y > Cam_Y+Screen_H-Height then
			Y = Cam_Y+Screen_H-Height;
			isDoing  = 1;
			Cooldown = 100;
         Attacks = Attacks+1;
      end
	elseif isDoing == 1 then -- Wenn er wartet
         if Attacks == 3 then -- Wenn er schon dreimal angegriffen hat
            isDoing = 3; -- Lasse ihn gehen
         else
            Angle = math.atan2(Player_Y - Y,Player_X - X); -- Lasse ihn den Spieler beobachten
            Cooldown = Cooldown-1; -- Und reduziere den Cooldown
            if Cooldown == 0 then
               isDoing = 2; -- Angriff starten!
            end
         end
	elseif isDoing == 0 then -- Er geht ins Bild
      Angle = math.pi;
      X = X-1;
      if X < Cam_X + Screen_W then --Ist im Bild  
			Cooldown = 100;
         isDoing = 1;
      end
   end          
   return isDoing,Cooldown,Attacks,DamageRadius,Size,CollideDamage,Animation,DeleteHim,MoveAngle,X,Y,Speed,Angle;
end
