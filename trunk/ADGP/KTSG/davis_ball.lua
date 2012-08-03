require "object"
require "action"

name = "Davis_ball"

file = {
  {path = sprite\sys\davis_ball.bmp, autoclip=1, w= 81,  h= 46,  row= 4,  col= 6},
}

hp = 1
mess = 1
elasticity = 0.5
objecttype = ObjectType.CHEE
flyingtype = Flyingtype.LINEARLINE_PATH

frame =
{
	flying = {},
}

frame.flying[0] =
{
   pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 45, next = {"standing", 1},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=34, value=150}},
   body = {
	{kind = 0, points = {{21,-18}, {21,-80}, {64,-80}, {64,-18}}, zwidth = 8}
   }

   --wpoint:
   --   kind: 1  x: 23  y: 55  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}
