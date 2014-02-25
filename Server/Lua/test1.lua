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


local TestTable = 
{
	[1] = 1,
	[2] = 3,
	
	["aa"] = 4,
	[4] = 4,
	[5] = 5,
}

function TestVarArg(...)
	for i, v in pairs(arg) do
		print(v)
	end

end
function x000002_Test(...)
	-- local f, s, var = ipairs(TestTable)
	-- while true do
		-- local var_1, var_2 = f(s, var)
		-- if var_1 == nil then break end
		-- var = var_1
		-- print(var_2)
	-- end
	
	
	-- print(table.getn(TestTable))
	-- for _, v, zero in ipairs(TestTable) do
		-- print(v)
		-- print(zero)
	-- end
	
	for i, v in pairs(arg) do
		print(v)
	end
end
