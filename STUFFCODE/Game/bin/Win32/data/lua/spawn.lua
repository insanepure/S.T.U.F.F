math.randomseed(os.time());
local ai = require("data.lua.ext.AiFunctions")

-- DEBUG VARIABLE
spawnon = true;
debugmsg = false;

-- Creates a empty table
groups = {};
local listlenght = 15
for i = 1, listlenght do
	groups[i] = {};
	for a = 0, 7 do
		groups[i][a] = 0;
	end
end	

-- füllt gruppen tabelle mit fish gruppen
-- erste klammer gruppen nummer
-- zweite klammer gegnertyp, wert = anzahl
-- index 0 der zweiten klammer für minimum ticks
-- index 1 der zweiten klammer für ausschüttzeit in ticks
-- echsenfish = 2
-- seeigel = 3
-- raketenfish = 4 !!! wird nie gespawnt !!!
-- blocker = 5
-- nashorn = 6
-- fetzenfish = 7



-- Groups

--5 echsen
groups[1][0] = 0;   --1 gruppe / 2 ("0") ticks anfangen zu zählen 3 (0) bei ticks 			
groups[1][1] = 70;	--1 gruppe / 2 ("1") ausschüttzeit in ticks anfang zu zählen / ausschüttzeit in ticks 3 (70)
groups[1][2] = 2;	--1 gruppe / 2 (x) fische / 3 wieviele 

groups[2][0] = 50;
groups[2][1] = 20;
groups[2][2] = 2;

groups[3][0] = 100;
groups[3][1] = 40;
groups[3][2] = 4;

groups[4][0] = 300;
groups[4][1] = 40;
groups[4][2] = 5;
groups[4][3] = 1;

groups[5][0] = 600;
groups[5][1] = 40;
groups[5][2] = 4;
groups[5][3] = 2;

groups[6][0] = 850;
groups[6][1] = 50;
groups[6][5] = 2;
groups[6][2] = 2;

groups[7][0] = 850;
groups[7][1] = 100;
groups[7][5] = 2;
groups[7][3] = 1;
groups[7][2] = 4;

groups[8][0] = 1050;
groups[8][1] = 90;
groups[8][2] = 4;
groups[8][5] = 2;

groups[9][0] = 1050;
groups[9][1] = 100;
groups[9][2] = 5;
groups[9][5] = 2;

groups[10][0] = 3000;
groups[10][1] = 80;
groups[10][7] = 2;
groups[10][2] = 3;
groups[10][3] = 1;

groups[11][0] = 3000;
groups[11][1] = 100;
groups[11][7] = 4;
groups[11][5] = 3;

groups[12][0] = 3200;
groups[12][1] = 80;
groups[12][2] = 6;
groups[12][7] = 3;

groups[13][0] = 3900;
groups[13][1] = 70;
groups[13][2] = 6;
groups[13][6] = 2;

groups[14][0] = 4000;
groups[14][1] = 80;
groups[14][7] = 3;
groups[14][6] = 2;

groups[15][0] = 4000;
groups[15][1] = 100;
groups[15][2] = 12;
groups[15][6] = 1;

-- Settings
wavepause = 10; -- how far appart waves are
wavelength = 0; -- how long a wave is in fish
wavelengthgroup = 20; -- how much longer a wave is per additional group it contains

wavegroup = 2; -- how many groups a wave originally contains
wavegroupgain = 0.002; -- how many groups a wave additionally gets per tick
wavegroupcap = 25; -- maximum groups in a wave
wavegrouprand = 2; -- how many more random groups a wave can gain

tickgaintime = 4; -- ticks gained per second  !!(war mal 4)!!
tickgainpoints = 0.002; -- ticks gained per point
tickgaindis = 1; -- ticks gained per tile !!(war mal 1)!!

spawnborder = 128; -- how far enemies spawn outside of the screen

-----------
SpawnSpread = 512; -- Bei Swarmspawn: wie weit die einzelenen Schwarmfische auseinander Spawnen


tick = 0;
tickprevious = 0;
wavetimer = wavepause;
PointsPrevious = 0;
Cam_XPrevious = 0;
wavelengthtimer = -1;
wavetotallength = 0;
spawnfrequency = 0;

groupsize = {};

groupsize[0] = 0;
groupsize[1] = 0;
itemscatter = 128;
deadfish = 0;

spawn = {};
for a = 0, 7 do
	spawn[a] = 0;
end


function OnDieBlock(Block_X,Block_Y,Points,Cam_X,Cam_Y,Screen_W,Screen_H,timeMultiplicator)
	local chance = math.random(0,100);
	if chance < 5 then       
		chance = math.random(0,100);
		if chance < 10 then
			SpawnItem(0,Block_X,Block_Y);   --0
		elseif chance >= 10 and chance < 25 then
			SpawnItem(1,Block_X,Block_Y);	--1
		elseif chance >= 25 and chance < 65 then
			SpawnItem(2,Block_X,Block_Y);	--2
		elseif chance >= 65 and chance < 90 then
			SpawnItem(3,Block_X,Block_Y);	--3
		elseif chance >= 90 and chance < 100 then
			SpawnItem(4,Block_X,Block_Y);	--4
		end
	end
end

function OnDie(Enemy_X,Enemy_Y,Points,Cam_X,Cam_Y,Screen_W,Screen_H,timeMultiplicator)
 --Type Legende
 -- 0 = Feuerrate
 -- 1 = Bombe
 -- 2 = Herz
 -- 3 = Unbesiegbarkeit
 -- 4 = Energie
 -- 5 = Muttern
 
	deadfish = deadfish + 1;
	
	if deadfish >= groupsize[0] then
		if Enemy_X >= Cam_X + (Screen_W / 2) then
			local i = 1;
			while i < groupsize[0] do
				local rp = ai.GetPositionFromAngle( math.random(360), math.random(itemscatter));
				SpawnItem( 5, Enemy_X + rp.x, Enemy_Y + rp.y);
				i = i + 1;
			end

			deadfish = deadfish - groupsize[0];
			groupsize[0] = 0;

		end
	end
	
	if deadfish >= groupsize[1] then
		if Enemy_X >= Cam_X + (Screen_W / 2) then
			local r = math.random(1,10);
			if r == 1 then
				SpawnItem(2,Enemy_X,Enemy_Y);
			end
			
			local i = 1;
			while i < groupsize[1] do
				local rp = ai.GetPositionFromAngle( math.random(360), math.random(itemscatter));
				SpawnItem( 5, Enemy_X + rp.x, Enemy_Y + rp.y);
				i = i + 1;
			end

			deadfish = deadfish - groupsize[1];
			groupsize[1] = 0;
		end
	end
	
	local chance = math.random(0,100); -- << hier gerry!
	if chance < 9 then       
	--Type Legende
 -- 0 = Feuerrate
 -- 1 = Bombe
 -- 2 = Herz
 -- 3 = Unbesiegbarkeit
 -- 4 = Energie
 -- 5 = Muttern
		chance = math.random(0,100);
		if chance < 25 then
			SpawnItem(0,Enemy_X,Enemy_Y);   
		elseif chance >= 25 and chance < 40 then
			SpawnItem(1,Enemy_X,Enemy_Y);
		elseif chance >= 40 and chance < 65 then
			SpawnItem(2,Enemy_X,Enemy_Y);
		elseif chance >= 65 and chance < 85 then
			SpawnItem(3,Enemy_X,Enemy_Y);
		elseif chance >= 85 and chance < 100 then
			SpawnItem(4,Enemy_X,Enemy_Y);
		end
	end   
end

function EnemySpawn(Points,Cam_X,Cam_Y,Screen_W,Screen_H,timeMultiplicator)
	tick = tick + (((1/60) * tickgaintime) * timeMultiplicator) + ((Points - PointsPrevious) * tickgainpoints) + ((Cam_X - Cam_XPrevious) * tickgaindis / 64);
	
	-- Spawn(Type,x,y); --
	-- Type = 0 - Echse
	-- Type = 1 - Ramm
	-- Type = 2 - Fetze
	
	-- when the timer runs out, spawn a wave
	
	if tick >= 1800 and tickprevious < 1800 then
		spawnon = false;
	end
	
	if tick >= 2000 and tickprevious < 2000 then
		Spawn( 5, Cam_X + Screen_W + 200, Cam_Y + Screen_H / 2, 1500, 3);
	end
	
	if tick >= 2300 and tickprevious < 2300 then
		spawnon = true;
	end
	
	if tick >= 3200 and tickprevious < 3200 then
		spawnon = false;
	end
	
	if tick >= 3500 and tickprevious < 3500 then
		Spawn( 4, Cam_X + Screen_W + 200, Cam_Y + Screen_H / 2, 1000, 2);
	end
	
	if tick >= 3900 and tickprevious < 3900 then
		spawnon = true;
	end
	
	if tick >= 4800 and tickprevious < 4800 then
		spawnon = false;
	end
	
	if tick >= 5000 and tickprevious < 5000 then
		Spawn( 6, Cam_X + Screen_W + 200, Cam_Y + Screen_H / 2, 0, 0);
	end
	
	if wavetimer < 0 and spawnon then
		--- Put together new wave
		-- create spawn pool
		local pool = {};
		
		if wavetotallength == 0 then
			-- go through all groups
			for i,v in ipairs(groups) do
				-- breaks the loop, when the minimum ticks are not reached
				if v[0] > tick then break; end
				-- fill the pool with all matching groups
				pool[i] = v;
			end
			
			-- empty the spawn pool
			spawn = {};
			for a = 0, 7 do
				spawn[a] = 0;
			end
			
			--- fill the spawn pool with two random valid groups
			-- reset wavelength
			wavelength = 0;
			local n = 1;
			repeat
				-- choose a group
				local r = math.random(#pool);
				-- fill group contents into spawn
				for i = 0, 7 do
					spawn[i] = spawn[i] + pool[r][i];
					if not (i == 0) and not (i == 1) then
						wavelength = wavelength + pool[r][i];
					end
					
					--fill one of the 2 groupsize variables
					if groupsize[0] == 0 then
						groupsize[0] = wavelength;
					elseif groupsize[1] == 0 then
						groupsize[1] = wavelength;
					end
					
				end
				n = n + 1;
			until n == wavegroup + 1;

			wavelengthtimer = spawn[1];
			wavetotallength = spawn[1];
			spawnfrequency = wavelength / wavetotallength;
			if debugmsg then print(wavelength .. " fish put in pool"); end
		end
		
		if ((spawnfrequency * (tick - tickprevious)) * 1000 >= math.random(1000)) then
			local a = {2,3,4,5,6,7};
			a = arrayShuffle(a);
			for i,v in ipairs(a) do
				if spawn[v] > 0 then
					local s = getFishSide(v - 2);
					spawn[v] = SpawnFish(v - 2, spawn[v], getSpawnPositionX(s, Cam_X, Screen_W), getSpawnPositionY(s, Cam_Y, Screen_H), s);
					if debugmsg then
						print("----------------------------------------");
						print("Spawned fish of type " .. v - 2 .. " from side " .. s);
						print(spawn[v] .. " fish of this type remaining");
					end
					break;
				end
			end
		end
		
		-- Count down for how long the wave spawns
		wavelengthtimer = wavelengthtimer - (tick - tickprevious);
		
		if wavelengthtimer < 0 then
			wavetimer = wavepause;
			wavelengthtimer = -1;
			wavetotallength = 0;
		end
	else
		-- Count down to when next wave spawns
		wavetimer = wavetimer - (tick - tickprevious);
	end
   
	-- Update Previous Values
	PointsPrevious = Points;
	Cam_XPrevious = Cam_X;
	tickprevious = tick;
end

-- side input: 0 = left, 1 = top, 2 = right, 3 = down
function getSpawnPositionX(side, Cam_X, Screen_W)
	local x;
	if side == 0			then x = Cam_X - spawnborder;
		elseif side == 1	then x = math.random( Cam_X - spawnborder, Cam_X + Screen_W + spawnborder);
		elseif side == 2	then x = Cam_X + Screen_W + spawnborder;
		else					 x = math.random( Cam_X - spawnborder, Cam_X + Screen_W + spawnborder);
	end
	if debugmsg then print("X: " .. x); end
	return x;
end

function getSpawnPositionY(side, Cam_Y, Screen_H)
	local y;
	if side == 0			then y = math.random( Cam_Y - spawnborder, Cam_Y + Screen_H + spawnborder);
		elseif side == 1	then y = Cam_Y - spawnborder;
		elseif side == 2	then y = math.random( Cam_Y - spawnborder, Cam_Y + Screen_H + spawnborder);
		else					 y = Cam_Y + Screen_H + spawnborder;
	end
	if debugmsg then print("Y: " .. y); end
	return y;
end

-- table of probabilities for the sides from fish to spawn from
-- returns 0, 1, 2, 3
function getFishSide(fish)
	local m0;
	local m1;
	local m2;
	local m3;
	local r = math.random(100);
	
	if fish == 0 			then m0 = 00; m1 = 00; m2 = 100; m3 = 00;
		elseif fish == 1 	then m0 = 00; m1 = 00; m2 = 100; m3 = 00;
		elseif fish == 2	then m0 = 25; m1 = 25; m2 = 25; m3 = 25;
		elseif fish == 3	then m0 = 00; m1 = 00; m2 = 100; m3 = 00;
		else					 m0 = 25; m1 = 25; m2 = 25; m3 = 25;
	end
	
	if r < m0 then return 0;
		elseif r < (m1 + m0) then return 1;
		elseif r < (m2 + m1 + m0) then return 2;
		else return 3;
	end
end

function SpawnFish(fish,number,x,y,side)
	if fish == 0 then -- echse spawn swarm
		local r0 = math.random(number);
		local r1;
		
		if not r0 == number then r1 = math.random(r0,number);
		else r1 = r0; end
		
		local i;
		
		for i = 0, r1, 1 do
			-- make sure all fish do not spawn at the same point
			if number > 0 then 
				Spawn(0,x,y,0,0);
				number = number - 1;
				if side == 0 then
					x = x - 64 - (SpawnSpread * math.random());
					y = y + (SpawnSpread * (math.random() - 0.5));
				elseif side == 1 then
					y = y - 64 - (SpawnSpread * math.random());
					x = x + (SpawnSpread * (math.random() - 0.5));
				elseif side == 2 then
					x = x + 64 + (SpawnSpread * math.random());
					y = y + (SpawnSpread * (math.random() - 0.5));
				else
					y = y + 64 + (SpawnSpread * math.random());
					x = x + (SpawnSpread * (math.random() - 0.5));
				end
			end
		end
	elseif fish == 1 then
		Spawn(fish, math.floor(x/64.0)*64.0, GetY(x),0,0);
		number = number - 1;
	else
		Spawn(fish, x, y,0,0);
		number = number - 1;
	end
	return number;
end

-- shuffle an array
-- source: http://snippets.luacode.org/snippets/Shuffle_array_145
function arrayShuffle(tab)
	local n, order, res = #tab, {}, {}
	 
	for i=1,n do order[i] = { rnd = math.random(), idx = i } end
	table.sort(order, function(a,b) return a.rnd < b.rnd end)
	for i=1,n do res[i] = tab[order[i].idx] end
	return res
end