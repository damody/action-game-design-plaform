require "Script/object"
require "Script/action"

name = "davis_ball"

file = {
  {path = "media\\davis_ball.png", autoclip=1, w= 81,  h= 46,  row= 4,  col= 3},
}

hp = 1
mess = 1
elasticity = 0.5
objecttype = ObjectType.CHEE
flyingtype = Flyingtype.LINEARLINE_PATH

frame =
{
	default  = {},
	flying = {},
}

frame.default[0] =
{
   pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 1, next = {"flying", 1},
   dvx = 0, dvy = 0,  dvz = 0,  centerx = 56,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[0] =
{
   pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 15, next = {"flying", 1},
   dvx = 1, dvy = 0,  dvz = 0,  centerx = 56,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[1] =
{
   pic_id = 0, pic_x = 2, pic_y = 1, state = Action.Standing, wait = 15, next = {"flying", 2},
   dvx = 1, dvy = 0,  dvz = 0,  centerx = 53,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[2] =
{
   pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 15, next = {"flying", 3},
   dvx = 2, dvy = 0,  dvz = 0,  centerx = 56,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[3] =
{
   pic_id = 0, pic_x = 2, pic_y = 1, state = Action.Standing, wait = 15, next = {"flying", 4},
   dvx = 2, dvy = 0,  dvz = 0,  centerx = 52,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[4] =
{
   pic_id = 0, pic_x = 3, pic_y = 1, state = Action.Standing, wait = 15, next = {"flying", 5},
   dvx = 3, dvy = 0,  dvz = 0,  centerx = 53,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[5] =
{
   pic_id = 0, pic_x = 4, pic_y = 1, state = Action.Standing, wait = 15, next = {"flying", 6},
   dvx = 3, dvy = 0,  dvz = 0,  centerx = 52,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[6] =
{
   pic_id = 0, pic_x = 3, pic_y = 1, state = Action.Standing, wait = 15, next = {"flying", 7},
   dvx = 3, dvy = 0,  dvz = 0,  centerx = 53,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[7] =
{
   pic_id = 0, pic_x = 4, pic_y = 1, state = Action.Standing, wait = 15, next = {"flying", 8},
   dvx = 3, dvy = 0,  dvz = 0,  centerx = 53,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[8] =
{
   pic_id = 0, pic_x = 1, pic_y = 3, state = Action.Standing, wait = 15, next = {"flying", 9},
   dvx = 3, dvy = 0,  dvz = 0,  centerx = 55,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}

frame.flying[9] =
{
   pic_id = 0, pic_x = 2, pic_y = 3, state = Action.Standing, wait = 15, next = {"flying", 8},
   dvx = 3, dvy = 0,  dvz = 0,  centerx = 55,  centery = 24,  clear_key_queue = 0,
   consume = {rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0},
   hit = {},
   blood = {},
   body = {}
}
