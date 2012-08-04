require "object"
require "action"

name = "Bat"

file = {
  {path = sprite\sys\weapon0.bmp,  w: 48,  h: 48,  row: 10,  col: 10},
}

hp = 200
mess = 1
elasticity = 0.5
objecttype = ObjectType.LIGHT;
flyingtype = Flyingtype.DEFAULT;

frame =
{
	insky = {},
	onhand = {},
	throwing = {},
	ground = {},
	justonground = {},
	
}
