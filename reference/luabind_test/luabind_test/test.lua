class 'test_derived' (Test)

function test_derived:__init(v)
-- Record our derived instance of this object in the C++ instance.
	super(self, v)
end

function test_derived:Tick()
    -- do nothing at the moment
end

function test_derived:test_function()
	print('derived class function')
end

-- this is called from C++
function test_derived:member_func()
	print("call member")
-- this should print 2
	print(self:get())

-- this should print 200
	print(self.blah)

-- this should print 'derived class function'
	self:test_function()
end




function main()
	a = test_derived(10)


	a:set(999);
	print(a:get())

-- I want to retain the added methods and this variable
	a.blah = 200
	a:test_function()

	Cpassthrough(a)
	return 0
end



function tt(o)
	o:set(453);
end
