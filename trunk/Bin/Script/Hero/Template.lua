require	"Script/effect"
require	"Script/action"

name	= "Template"
head	= ""
small	= ""

file = {
{path = "Media\\sprite\\template01.png", autoclip = 1, w = 100, h = 100, row = 10, col = 7 },
}

walking_speed        = 5.000000
walking_speedz       = 5.000000
running_speed        = 15.000000
running_speedz       = 15.000000
heavy_walking_speed  = -431602080.000000
heavy_walking_speedz = -431602080.000000
heavy_running_speed  = -431602080.000000
heavy_running_speedz = -431602080.000000
jump_height          = -431602080.000000
jump_distance        = -431602080.000000
jump_distancez       = -431602080.000000
dash_height          = -431602080.000000
dash_distance        = -431602080.000000
dash_distancez       = -431602080.000000
rowing_height        = -431602080.000000
rowing_distance      = -431602080.000000

air_crouch_map = {
}

frame = 
{
	crouch = {},
	default = {},
	falling_back = {},
	falling_front = {},
	in_the_air = {},
	injured = {},
	jump = {},
	lying = {},
	right_punch = {},
	running = {},
	standing = {},
	stop_running = {},
	walking = {},
}

frame.crouch[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 7, state = Action.Standing, wait = 1, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 91, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.default[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 10, next = { "standing", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.falling_back[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 1, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 0, centery = 0, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.falling_front[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 1, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 0, centery = 0, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.in_the_air[0] =
{
	pic_id = 0, pic_x = 3, pic_y = 7, state = Action.InTheAir, wait = 1, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 86, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.injured[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 1, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 0, centery = 0, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.injured[1] =
{
	pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 1, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 0, centery = 0, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.jump[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 7, state = Action.Jump, wait = 6, next = { "jump", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 91, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.jump[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 7, state = Action.Jump, wait = 6, next = { "jump", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 89, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.jump[2] =
{
	pic_id = 0, pic_x = 3, pic_y = 7, state = Action.Jump, wait = 10, next = { "default", 0}, 
	dvx = 10, dvy = 30, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.lying[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 1, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 0, centery = 0, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.right_punch[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 2, state = Action.Attacking, wait = 6, next = { "right_punch", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.right_punch[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 2, state = Action.Attacking, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {53,-39}, {60,-45}, {73,-49}, {81,-40}, {78,-31}, {59,-34}, }, zwidth = 5,
		dvx = 0, dvy = 0, dvz = 0, fall = 10, breakDefend = 5, 
		arest = 5, reAttackRest = 5, injury = 10, strength = 0, 
		},
	},
}

frame.running[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 3, state = Action.Running, wait = 6, next = { "running", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.running[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 3, state = Action.Running, wait = 6, next = { "running", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.running[2] =
{
	pic_id = 0, pic_x = 3, pic_y = 3, state = Action.Running, wait = 6, next = { "running", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.running[3] =
{
	pic_id = 0, pic_x = 2, pic_y = 3, state = Action.Running, wait = 6, next = { "running", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.standing[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 10, next = { "standing", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	hit = { {"J", "jump", 0 }, {"A", "right_punch", 0 }, },
}

frame.standing[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 1, state = Action.Standing, wait = 10, next = { "standing", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	hit = { {"J", "jump", 0 }, {"A", "right_punch", 0 }, },
}

frame.standing[2] =
{
	pic_id = 0, pic_x = 3, pic_y = 1, state = Action.Standing, wait = 3, next = { "standing", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	hit = { {"J", "jump", 0 }, {"A", "right_punch", 0 }, },
}

frame.standing[3] =
{
	pic_id = 0, pic_x = 4, pic_y = 1, state = Action.Standing, wait = 10, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	hit = { {"J", "jump", 0 }, {"A", "right_punch", 0 }, },
}

frame.stop_running[0] =
{
	pic_id = 0, pic_x = 8, pic_y = 7, state = Action.StopRunning, wait = 6, next = { "stop_running", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.stop_running[1] =
{
	pic_id = 0, pic_x = 9, pic_y = 7, state = Action.StopRunning, wait = 6, next = { "stop_running", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.stop_running[2] =
{
	pic_id = 0, pic_x = 10, pic_y = 7, state = Action.StopRunning, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.walking[0] =
{
	pic_id = 0, pic_x = 6, pic_y = 1, state = Action.Walking, wait = 10, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	hit = { {"J", "jump", 0 }, },
}

frame.walking[1] =
{
	pic_id = 0, pic_x = 7, pic_y = 1, state = Action.Walking, wait = 10, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	hit = { {"J", "jump", 0 }, },
}

frame.walking[2] =
{
	pic_id = 0, pic_x = 8, pic_y = 1, state = Action.Walking, wait = 10, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	hit = { {"J", "jump", 0 }, },
}

frame.walking[3] =
{
	pic_id = 0, pic_x = 5, pic_y = 1, state = Action.Walking, wait = 10, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 53, centery = 87, clear_key_queue = 0, 
	consume = { rule = 0, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	hit = { {"J", "jump", 0 }, },
}

