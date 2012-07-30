require "effect"
require "action"
name= "Davis"
head= "sprite\\sys\\davis_f.bmp"
small= "sprite\\sys\\davis_s.bmp"

file = {
{path = "media\\davis_0_.png", autoclip=1,  w = 79,  h = 79,  row = 10,  col = 7},
{path = "media\\davis_1_.png", autoclip=1,  w = 79,  h = 79,  row = 10,  col = 7},
}

walking_speed   = 5.000000
walking_speedz  = 2.500000
running_speed   = 10.000000
running_speedz  = 1.600000
heavy_walking_speed = 3.700000
heavy_walking_speedz= 1.850000
heavy_running_speed = 6.200000
heavy_running_speedz= 1.000000
jump_height     = -16.299999
jump_distance   = 10.000000
jump_distancez  = 3.750000
dash_height     = -10.000000
dash_distance   = 18.000000
dash_distancez  = 5.000000
rowing_height   = -2.000000
rowing_distance = 5.000000

frame =
{
	default  = {},
	standing = {},
	walking  = {},
	running  = {},
	stop_running = {},
	ball     = {},
	many_punch={},
	jump_hit = {},
	singlong = {},

}

frame.default[0] =
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

frame.standing[0] =
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

frame.standing[1] =
{
   pic_id = 0, pic_x = 2, pic_y = 1, state = Action.Standing, wait = 45, next = {"standing", 2},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=33, value=150}},
   body = {
   {kind = 0, points = {{21,-18}, {21,-80}, {64,-80}, {64,-18}}, zwidth = 8}
   }

   --wpoint:
   --   kind: 1  x: 23  y: 54  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.standing[2] =
{
   pic_id = 0, pic_x = 3, pic_y = 1, state = Action.Standing, wait = 45, next = {"standing", 3},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=33, value=150}},
   body = {
   {kind = 0, points = {{21,-18}, {21,-80}, {64,-80}, {64,-18}}, zwidth = 8}
   }

   --wpoint:
   --   kind: 1  x: 23  y: 53  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.standing[3] =
{
   pic_id = 0, pic_x = 4, pic_y = 1, state = Action.Standing, wait = 45, next = {"standing", 0},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=33, value=150}},
   body = {
   {kind = 0, points = {{21,-18}, {21,-80}, {64,-80}, {64,-18}}, zwidth = 8}
   }

   --wpoint:
   --   kind: 1  x: 23  y: 53  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.walking[0] =
{
   pic_id = 0, pic_x = 5, pic_y = 1, state = Action.Walking, wait = 10, next = {"default", 0},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 78,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=33, value=150}},
   body = {
   {kind = 0, points = {{28,-15}, {28,-80}, {55,-80}, {55,-15}}, zwidth = 8}
   },
   catch = {
   {kind = 0, strong=0, catchx=0, catchy=0, where=Body.Neck, points = {{40,-16}, {40,-81}, {65,-81}, {65,-16}}}
   }

   --wpoint:
   --   kind: 1  x: 23  y: 53  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.walking[1] =
{
   pic_id = 0, pic_x = 6, pic_y = 1, state = Action.Walking, wait = 10, next = {"default", 0},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=33, value=150}},
   body = {
   {kind = 0, points = {{28,-15}, {28,-80}, {55,-80}, {55,-15}}, zwidth = 8}
   },
   catch = {
   {kind = 0, strong=0, catchx=0, catchy=0, where=Body.Neck, points = {{40,-16}, {40,-81}, {65,-81}, {65,-16}}}
   }

   --wpoint:
   --   kind: 1  x: 26  y: 54  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.walking[2] =
{
   pic_id = 0, pic_x = 7, pic_y = 1, state = Action.Walking, wait = 10, next = {"default", 0},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=33, value=150}},
   body = {
   {kind = 0, points = {{28,-15}, {28,-80}, {55,-80}, {55,-15}}, zwidth = 8}
   },
   catch = {
   {kind = 0, strong=0, catchx=0, catchy=0, where=Body.Neck, points = {{40,-16}, {40,-81}, {65,-81}, {65,-16}}}
   }

   --wpoint:
   --   kind: 1  x: 26  y: 54  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.walking[3] =
{
   pic_id = 0, pic_x = 8, pic_y = 1, state = Action.Walking, wait = 10, next = {"default", 0},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 78,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=34, value=150}},
   body = {
   {kind = 0, points = {{28,-15}, {28,-80}, {55,-80}, {55,-15}}, zwidth = 8}
   },
   catch = {
   {kind = 0, strong=0, catchx=0, catchy=0, where=Body.Neck, points = {{40,-16}, {40,-81}, {65,-81}, {65,-16}}}
   }

   --wpoint:
   --   kind: 1  x: 36  y: 52  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.walking[4] =
{
   pic_id = 0, pic_x = 7, pic_y = 1, state = Action.Walking, wait = 10, next = {"default", 0},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=33, value=150}},
   body = {
   {kind = 0, points = {{28,-15}, {28,-80}, {55,-80}, {55,-15}}, zwidth = 8}
   },
   catch = {
   {kind = 0, strong=0, catchx=0, catchy=0, where=Body.Neck, points = {{40,-16}, {40,-81}, {65,-81}, {65,-16}}}
   }

   --wpoint:
   --   kind: 1  x: 26  y: 54  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.walking[5] =
{
   pic_id = 0, pic_x = 6, pic_y = 1, state = Action.Walking, wait = 10, next = {"default", 0},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 39,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=39, y=33, value=150}},
   body = {
   {kind = 0, points = {{28,-15}, {28,-80}, {55,-80}, {55,-15}}, zwidth = 8}
   },
   catch = {
   {kind = 0, strong=0, catchx=0, catchy=0, where=Body.Neck, points = {{40,-16}, {40,-81}, {65,-81}, {65,-16}}}
   }

   --wpoint:
   --   kind: 1  x: 26  y: 54  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.running[0] =
{
   pic_id = 0, pic_x = 1, pic_y = 3, state = Action.Running, wait = 10, next = {"running", 1},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 36,  centery = 80,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=49, y=38, value=150}},
   body = {
   {kind = 0, points = {{25,-19}, {25,-79}, {63,-79}, {63,-19}}, zwidth = 8}
   }

   --sound: data\003.wav
   --wpoint:
   --   kind: 1  x: 23  y: 53  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.running[1] =
{
   pic_id = 0, pic_x = 2, pic_y = 3, state = Action.Running, wait = 10, next = {"running", 2},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 37,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=49, y=38, value=150}},
   body = {
   {kind = 0, points = {{25,-19}, {25,-79}, {63,-79}, {63,-19}}, zwidth = 8}
   }

   --wpoint:
   --   kind: 1  x: 23  y: 53  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.running[2] =
{
   pic_id = 0, pic_x = 3, pic_y = 3, state = Action.Running, wait = 10, next = {"running", 3},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 32,  centery = 78,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=45, y=37, value=150}},
   body = {
   {kind = 0, points = {{25,-19}, {25,-79}, {63,-79}, {63,-19}}, zwidth = 8}
   }

   --sound: data\004.wav
   --wpoint:
   --   kind: 1  x: 26  y: 53  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.running[3] =
{
   pic_id = 0, pic_x = 2, pic_y = 3, state = Action.Running, wait = 10, next = {"running", 0},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 37,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {{"d>a", "ball", 1}, {"d^a", "singlong", 1}, {"dva", "many_punch", 1}, {"d^j", "jump_hit", 1}},
   blood = {{scale = 1.0, x=49, y=38, value=150}},
   body = {
   {kind = 0, points = {{25,-19}, {25,-79}, {63,-79}, {63,-19}}, zwidth = 8}
   }

   --wpoint:
   --   kind: 1  x: 23  y: 53  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

frame.stop_running[0] =
{
   pic_id = 1, pic_x = 5, pic_y = 5, state = Action.StopRunning, wait = 15, next = {"default", 0},
   dvx = 1, dvy = 0,  dvz = 0,  centerx = 39,  centery = 79,  clear_key_queue = 0,
   consume = {HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {{scale = 1.0, x=39, y=36, value=150}},
   body = {
   {kind = 0, points = {{17,-25}, {17,-80}, {47,-80}, {47,-25}}, zwidth = 8},
   {kind = 0, points = {{45,-47}, {45,-79}, {61,-79}, {61,-47}}, zwidth = 8}
   }

   --sound: data\009.wav
   --wpoint:
   --   kind: 1  x: 23  y: 53  weaponact: 23  attacking: 0  cover: 0  dvx: 0  dvy: 0  dvz: 0
   --wpoint_end:

}

