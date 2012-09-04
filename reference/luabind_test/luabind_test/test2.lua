


-- First, define the two new subclasses of Foo
class 'Bar' (Foo)
function Bar:__init(name)
	super(self, name);	-- Call for Foo::Foo(self, name)
	print("A " .. self.name .. " a day keeps the doctor away.");
end
function Bar:Think()
	print(self.name .. " is cool.");
end

a = Foo(nil,"123");

bar = Bar("44");
