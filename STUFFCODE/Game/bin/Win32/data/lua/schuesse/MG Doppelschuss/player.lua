math.randomseed(os.time());


function Init()
	-----------------------------------------
	HitBoxX = 34; -- Verschiebung der Hitbox aufn Bild in der X Achse
	HitBoxY = 2; -- Verschiebung der Hitbox aufn Bild in der Y Achse
	HitBoxWidth = 60.0; -- Breite der Hitbox
	HitBoxHeight = 60.0; -- Höhe der Hitbox
	Width = 128.0; -- Reale Breite
	Height = 64.0; -- Reale Höhe
	-----------------------------------------
	ArraySize = 0;
	
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

function Laser(Type, Angle,Cooldown)
	--Type = 1 -> Mittleres Schiff
	--Type = 0 -> Vorderes Schiff
	if Type == 0 then	
		ThrowBack = 50.0;	
		ThrowBackSteps = 5;
		length = 500;
		X = 64.0 + (60.0 * math.sin(Angle + math.pi/2));
		Y = 32.0 + (28.0 * math.cos(Angle + math.pi/2));
		Cooldown = 20;
		Duration = 10;
	elseif Type == 1 then
		ThrowBackSteps = 0;	
		ThrowBack = 0.0;
		length = 500;
		X = 64.0 + (60.0 * math.sin(Angle + math.pi/2));
		Y = 32.0 + (28.0 * math.cos(Angle + math.pi/2));
		Cooldown = 0;
		Duration = 1;
	end
	return ThrowBackSteps,ThrowBack,Duration,Cooldown,Angle,length,X,Y;
end
function Shoot(PlayerNum,X,Y,Angle,Speed)

	X = X + 50 --+ 54.0 + (60.0 * math.sin(Angle + math.pi/2)); -- Wo der Schuss auf der X Achse gespawned wird. X input ist die X coordinate des Spielers
	Y = Y - 25 --+ 32.0 - (28.0 * math.cos(Angle + math.pi/2)); -- ^^ Y

	Angle = math.deg(Angle); -- Konvertiert Angle von Rad zu Deg
	
	Cooldown = 3; -- Wie Lange bis zum nächsten Schuss. In 1/60 Sekunden gemessen
	Angle = 0 + math.random(-0,0); -- Beeinflusst den Winkel. In diesem Falle: Füge dem Input Winkel einen zufälligen Winkel von +/- 10 Hinzu
	Type = 1; -- Der Typ des Schusses. Ganze Zahlen verwenden
	
	Angle = math.rad(Angle); -- Konvetiere Angle von Deg zurück zu Rad. muss gemacht werden befor Bullets erstellt werden
	
	CreateBullet(PlayerNum, Type, X, Y, 10, Angle);	-- Spawned einen Schuss mit Angegbene Werten. Dieser Code kann auch mehrmals aufgerufen Werden
	CreateBullet(PlayerNum, Type, X, Y+100, 10, Angle);
	
	return Cooldown; -- Gebe den Cooldown an die Engine zurück
end	 

function UpdateLoop(X,Y,B,A,PlayerNum,Player_X,Player_Y,Player_Angle,Player_LookAngle,Player_Speed,timeMultiplicator)


end


function UpdateAngle(timeMultiplicator,Angle,LookAngle,MovingAngle,Speed,Type)		

	
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
	
	return LookAngle,Angle;
end

function UpdateSpeed(timeMultiplicator,Angle,MovingAngle,LT,RT,Speed,BackSpeed)
	
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
			 
	BackSpeed = BackSpeed - (((Drag * BackSpeed/MaxSpeed) + Stopforce));
	-----------------------------------------
	if Speed < 0 then Speed = 0; end -- Falls es IRGENDWIE passiert, kA, mir passierte es!
	if Speed > MaxSpeed then Speed = MaxSpeed; end
	-----------------------------------------		
	
	--Damit er stehen bleibt, da Drag den Speed nie auf 0 bringt
	if Speed < 0.02 then
		Speed = 0.0;
	end	 
	if BackSpeed < 0.02 then
		BackSpeed = 0.0;
	end
	
	return Speed,BackSpeed;
end 