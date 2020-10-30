
   math.randomseed(os.time()); --Damit es immer random ist benutze die Zeit  
function Init()
   ----------------
	mapSize = 10000; -- Anzahl der Punkte, Breite = mapSize * 64
	mapStartY = 700; -- Start bei der Y-Achse
	-----------------------------------------
	return mapSize,mapStartY;
end



function GeneratePoints(X,Y,Start,Type,Split)   
   
	-----------------------------------------
   --
   --    Hier könnt ihr die Punkte so beeinflussen, dass eine Map nach euren Willen generiert wird
   --
	-----------------------------------------
   TileDist = 0;
   NormalChance = 0; --normal mit wabern
   SinChance = 0;	--kurve
   FallChance = 0;	--fallende teile
   SplitChance = 0;	--aufteilung
   SameChance = 0;  --boss
   chance = 0;		
   Fall = false;
   
   if Start == 0 then       
	-----------------------------------------
   -- Setze die nächste LevelEbene
	-----------------------------------------  
    if X == 0 then
        SameChance = 100;
    elseif X < 150 then     
        SameChance = 100;
		 
    elseif X > 150 and X < 600 then      
        NormalChance = 100;
		 
	elseif X > 600 and X < 750 then        
        SinChance = 100;
		 
    elseif X > 750 and X < 850 then  
        NormalChance = 100;
		 
    elseif X > 850 and X < 950 then      
        FallChance = 100;
		 
	elseif X > 950 and X < 1000 then      
        NormalChance = 100;
		 
	elseif X > 1000 and X < 1050 then      
        SplitChance = 100;
		 
	elseif X > 1050 and X < 1150 then      
        NormalChance = 100;
		 
	elseif X > 1150 and X < 1400 then      
        NormalChance = 15; 
        SinChance = 30;
        FallChance = 45;
        SplitChance = 60;
        SameChance = 75; 
		 
	elseif X > 1400 and X < 2200 then      --BOSS fetzenfisch
        SameChance = 100;
		 
	elseif X > 2200 and X < 2250 then      
        NormalChance = 100;
		 
	elseif X > 2250 and X < 3000 then      
        NormalChance = 15; 
        SinChance = 30;
        FallChance = 45;
        SplitChance = 60;
        SameChance = 75; 
		 
	elseif X > 3000 and X < 3800 then      --BOSS rammfisch
        SameChance = 100;
		 
	elseif X > 3800 and X < 3850 then      
        NormalChance = 100;
		 
	elseif X > 3850 and X < 4600 then      
        NormalChance = 15; 
        SinChance = 30;
        FallChance = 45;
        SplitChance = 60;
        SameChance = 75; 
		 
	elseif X > 4600 and X < 10000 then      --ENDBOSS
        SameChance = 100;
		 
		 
	
     else             
    	-----------------------------------------
      -- Wenn X höher ist als 900, dann ist der Rest durchgehend gleich
    	-----------------------------------------
         SameChance = 100; 
     end                           
    	-----------------------------------------
      -- Setze die Chance auf die einzelnen Ebenen und setze ihre Länge
    	-----------------------------------------
     chance = math.random(0,100);
     
     if chance <= NormalChance then
        Start = math.random(5,10); -- Länge  
        Split = 1;
        Type = 1;
     elseif chance <= SinChance then
        Start = math.random(20,40);-- Länge   
        Split = 1;
        Type = 2;
     elseif chance <= FallChance then
        Start = math.random(10,20);-- Länge  
        Split = 1;
        Type = 3;
     elseif chance <= SplitChance then
        Start = math.random(10,20);-- Länge
        Split = math.random(2,3);
        Type = 4;       
     elseif chance <= SameChance then
        Start = math.random(5,10);-- Länge  
        Split = 1;
        Type = 5;
     end
   else   
      Start = Start-1; --Setze die Länge auf Länge-1
   end
   -----------------------------------------
   -- Setze die einzelnen Ebenen nach ihren Typen und ihre Länge
   -----------------------------------------     
   
   if Type == 1 then --NormalEbene
      TileDist = math.random(500,600);
      Y = Y+math.random(-64,64);
   elseif Type == 2 then -- Hoch/Runter
      TileDist = math.random(700,800); 
      Y = Y + math.sin(X/10)*64; 
   elseif Type == 3 then -- Fallende
      fallchance = math.random(0,100);
      if fallchance > 90 then
         Fall = true;
      end
      TileDist = math.random(500,700);  
      Y = Y+math.random(-64,64);
   elseif Type == 4 then -- Aufteilen 
      if Split == 2 then
         TileDist = math.random(700,700);
      elseif Split == 3 then
         TileDist = math.random(800,800);  
      elseif Split == 4 then
         TileDist = math.random(900,900);
      end
      Y = Y+math.random(-64,64); 
   elseif Type == 5 then --Same
      if X < 10 then
         TileDist = 700;  
      else 
         TileDist = math.random(500,700);
      end
      Y = Y;         
   end 
   return Fall,Split,TileDist,Y,Start,Type;   
end