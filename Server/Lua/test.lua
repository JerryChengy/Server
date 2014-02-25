module "Counter"
function MakeCounter ()
	local t = 0
	return function ()
		t = t + 4
	return t
	end
end

function x000002_GetCounter()
	local x = MakeCounter ();
	return x();
	--print (222)
end