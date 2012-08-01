require "object"
require "action"

name = "Bat"

file = {
  {path = sprite\sys\davis_ball.bmp,  w: 81,  h: 46,  row: 4,  col: 6},
}

hp = 200
mess = 1
elasticity = 0.5
objecttype = ObjectType.LIGHT;
fltingtype = Flyingtype.DEFAULT;

frame =
{
	insky = {},
	onhand = {},
	throwing = {},
	ground = {},
	justonground = {},
	
}
