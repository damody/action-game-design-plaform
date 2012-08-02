require "object"
require "action"

name = "Davis_ball"

file = {
  {path = sprite\sys\davis_ball.bmp,  w: 81,  h: 46,  row: 4,  col: 6},
}

hp = 1
mess = 1
elasticity = 0.5
objecttype = ObjectType.CHEE;
fltingtype = Flyingtype.LINEARLINE_PATH;

frame =
{
	flying = {},
}