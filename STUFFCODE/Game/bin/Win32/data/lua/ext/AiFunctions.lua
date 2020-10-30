local f = {};

function f.SmallestAngle( a0, a1) -- a0: initial angle
	return ((a1 - a0) + 180) % 360 - 180;
end

function f.GetAngle( x0, y0, x1, y1) -- angle from point x0|y0 to x1|y1
	return math.atan2((y1 - y0),(x1 - x0)) * 180 / math.pi;
end

function f.GetPositionFromAngle(angle, length)
	local r = {}
	r.x = length * math.cos(math.rad(angle));
	r.y = length * math.sin(math.rad(angle));
	return r;
end

function f.Smooth( input) -- smooths input with a partial sinus function. input range: 0 to 1
	return (math.cos((( input - 1) * math.pi)) / 2) + 0.5;
end

function f.SinusModification(angle, input, strength) -- adds a sinus wave to a path
	return f.GetPositionFromAngle(angle + 90, math.sin(math.rad(input)) * strength);
end

function f.GetDistance( x0, y0, x1, y1)
	return math.sqrt(((x1 - x0)^2) + ((y1 - y0)^2));
end

return f;