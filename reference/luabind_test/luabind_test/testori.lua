function G(i)
	return i*3;
end

local a = testlua("hello lua!");

a:myprint();

a:setstr("yes lua!");

a:myprint();

Triple(G(3));



