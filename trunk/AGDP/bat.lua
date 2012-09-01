require "object"
require "action"

name = "Bat"

file = {
  {path = "media\\bat.png",  w= 48,  h= 48,  row= 10,  col= 4},
}

hp = 200
mess = 1
elasticity = 0.5
objecttype = ObjectType.LIGHT;
flyingtype = Flyingtype.DEFAULT;

frame =
{
	default={},
}

frame.default[0] =
{
   pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 1, next = {"default", 0},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 24,  centery = 48,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}
