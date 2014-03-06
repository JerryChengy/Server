local _class={}
 -- module "LuaClass"
-- function class(super)
	-- local class_type={}
	-- class_type.ctor=false
	-- class_type.super=super
	-- class_type.new=function(...) 
			-- local obj={}
			-- do
				-- local create
				-- create = function(c,...)
					-- if c.super then
						-- create(c.super,...)
					-- end
					-- if c.ctor then
						-- c.ctor(obj,...)
					-- end
				-- end
 
				-- create(class_type,...)
			-- end
			-- setmetatable(obj,{ __index=_class[class_type] })
			-- return obj
		-- end
	-- local vtbl={}
	-- _class[class_type]=vtbl
 
	-- setmetatable(class_type,{__newindex=
		-- function(t,k,v)
			-- vtbl[k]=v
		-- end
	-- })
 
	-- if super then
		-- setmetatable(vtbl,{__index=
			-- function(t,k)
				-- local ret=_class[super][k]
				-- vtbl[k]=ret
				-- return ret
			-- end
		-- })
	-- end
 
	-- return class_type
-- end

-- base_type=class()		-- 定义一个基类 base_type
 
-- function base_type:ctor(x)	-- 定义 base_type 的构造函数
	-- print("base_type ctor")
	-- self.x=x
-- end
 
-- function base_type:print_x()	-- 定义一个成员函数 base_type:print_x
	-- print(self.x)
-- end
 
-- function base_type:hello()	-- 定义另一个成员函数 base_type:hello
	-- print("hello base_type")
-- end

-- test=class(base_type)	-- 定义一个类 test 继承于 base_type
 
-- function test:ctor()	-- 定义 test 的构造函数
	-- print("test ctor")
-- end
 
-- function test:hello()	-- 重载 base_type:hello 为 test:hello
	-- print("hello test")
-- end

-- function MakeCounter ()
-- local t = 0
-- return function ()
-- t = t + 1
-- return t
-- end
-- end

-- function foobar ()
-- return load [[
-- return " Hello "
-- ]]
-- end
local print = print
local pi = math.pi
local huge = math.huge



local function gen_index(tbl)
	local index = {}
	for k in pairs(tbl) do
		table.insert(index,k)
	end
	table.sort(index)
	local ret = {}
	for k,v in ipairs(index) do
		ret[v] = k
	end
	return ret
end
function TestVarArg(...)
	for i, v in pairs(arg) do
		print(v)
	end

end
function Print()
	local i=1;
	while true do
		
		print("---------------"..i);
		i = i + 1;
	end
	print("hi coroutine");
end

function myipairs (t)
   local i = 0
   local n = table.getn(t)   
   return function ()
             i = i + 1
             if i <= n then return i,t[i] end
          end
end

function f1(strfunc)
	
	local n1 = 1;
	local n2 = 2;
	local n3 = 3;
   local function getn1()
      return n1;
   end
   local function getn2()
      return n2;
   end
   local function getn3()
      return n3;
   end
   if strfunc=="getn1" then
	return getn1;
   elseif strfunc=="getn2" then
	return getn2;
   elseif strfunc=="getn3" then
	return getn3;
   end
end

function printvararg(...)
	print(unpack(arg))
end

-- function TestTable.ctor()
	-- TestTable.key = 111;
-- end
local STable = 
{
	[1] = 77
};
local function init_map(sobj, map)
	for k,v in pairs(map) do
		local value = rawget(sobj,k)
		if value == nil then
			sobj[k] = v
		else
			init_map(value, v)
		end
	end
end

function test_prefunc(str)
	print(str)
end
--local int64 = require "int64"
local stable = {
	foo = {
		hello = 1,	-- number , default value is 1
		world = { "Alice", "Bob" },	-- anonymous enum
		foobar = {
			foobar = "",	-- string
		},
		array = "*number",	-- number array
		bars = "*bar",	-- struct bar array
	},
	bar = {
		first = true,
		second = 1,
		third = "*xx", -- enum xx array
	},
	xx = { "ONE", "TWO" }
}

local player = 
{
	hp = 100, age = 20
	--key = 111,
}
-- local player_mt = 
-- {
	-- __index = function ()
		-- return 3000
	-- end

-- }
-- setmetatable(player, player_mt);
function player:sethp(hp)
	self.hp = hp;
end
function x000002_Test(...)
	player:sethp(2000)
	print(player.hp)
	
	print(GetTestTblData(2, "MP"))
	--local typeinfo = assert(TestTable[3], "test")
	--print(typeinfo[1])
	--print(TestTable:key)
	-- func = f1("getn2")
	-- print(func())
	-- local f, s, var = ipairs(TestTable)	--var:nil; s: TestTable; f:
	-- print(f, s, var)
	-- var = 1
	-- while true do
		-- local var_1, var_2 = f(s, var)
		-- if var_1 == nil then break end
		-- var = var_1
		-- print(var_1)
		-- print(var_2)
	-- end
	-- printvararg(unpack(arg))
	-- local func = myipairs(TestTable);
	-- local func1 = myipairs(TestTable);
	-- func1();
	-- func1();
	
	-- local key, val = func();
	-- print(key , val)
	-- print(table.getn(TestTable))
	-- for _, v, zero in ipairs(TestTable) do
		-- print(v)
		-- print(zero)
	-- end
	
	-- for i, v in pairs(TestTable) do
		-- i = 0;
		-- print(v)
	-- end
	-- local func = player.GetPlayer();
	-- create(func);
	-- print(func(1, 2, 3))
	
end

-- function cannotModifyHp(object)
    -- local proxy = {}
    -- local mt = {
        -- __index = object,
    -- __newindex = function(t,k,v)
        -- if k ~= "hp" then
        -- object[k] = v
        -- end
    -- end
    -- }
    -- setmetatable(proxy,mt)
    -- return proxy
-- end
 
-- object = {hp = 10,age = 11}
-- function object.sethp(self,newhp)
    -- self.hp = newhp
-- end
 
-- o = cannotModifyHp(object)
 
-- o.hp = 100
-- print(o.hp)
 
-- o:sethp(111)
-- print(o.hp)
 
-- object:sethp(100)
-- print(o.hp)

