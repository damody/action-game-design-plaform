﻿--require("Script.mydebug").GoZeroBrane()
--require("Script.mobdebug").start()

require("Script.action")
require("Script.effect")

name	= "Davis"
head	= "sprite\\sys\\davis_f.bmp"
small	= "sprite\\sys\\davis_s.bmp"

file = {
{path = "media\\sprite\\davis_0.png", autoclip = 1, w = 79, h = 79, row = 10, col = 7 },
{path = "media\\sprite\\davis_1.png", autoclip = 1, w = 79, h = 79, row = 10, col = 7 },
{path = "media\\sprite\\davis_2.png", autoclip = 1, w = 79, h = 79, row = 10, col = 4 },
}

walking_speed        = 5.000000
walking_speedz       = 2.500000
running_speed        = 10.000000
running_speedz       = 1.600000
heavy_walking_speed  = 3.700000
heavy_walking_speedz = 1.850000
heavy_running_speed  = 6.200000
heavy_running_speedz = 1.000000
jump_height          = 32.599998
jump_distance        = 10.000000
jump_distancez       = 3.750000
dash_height          = 25.000000
dash_distance        = 18.000000
dash_distancez       = 5.000000
rowing_height        = 6.000000
rowing_distance      = 5.000000

air_crouch_map = {
{Action.BeforeDashAttack, "crouch", 1},
{Action.DashAttacking, "crouch", 1},
{Action.AfterDashAttack, "crouch", 1},
{Action.FallingFront, "lying", 1},
{Action.FallingBack, "lying", 0},
{Action.Dash, "crouch", 1},
{Action.InTheAir, "crouch", 0},
}

frame = 
{
	back_flip = {},
	ball = {},
	crouch = {},
	dash_back = {},
	dash_front = {},
	dash_kick = {},
	dash_punch = {},
	default = {},
	defend = {},
	falling_back = {},
	falling_front = {},
	front_flip = {},
	in_the_air = {},
	injured = {},
	jump = {},
	jump_hit = {},
	jump_kick = {},
	jump_punch = {},
	kick = {},
	lying = {},
	many_punch = {},
	punch = {},
	rolling = {},
	run_kick = {},
	run_punch = {},
	running = {},
	singlong = {},
	standing = {},
	stop_running = {},
	super_kick = {},
	super_punch = {},
	walking = {},
	TTEST = {},
}

frame.back_flip[0] =
{
	pic_id = 0, pic_x = 7, pic_y = 7, state = Action.Fliping, wait = 4, next = { "back_flip", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 40, centery = 80, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.back_flip[1] =
{
	pic_id = 0, pic_x = 6, pic_y = 7, state = Action.Fliping, wait = 12, next = { "back_flip", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.ball[0] =
{
	pic_id = 2, pic_x = 1, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 40, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[1] =
{
	pic_id = 2, pic_x = 2, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[2] =
{
	pic_id = 2, pic_x = 3, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[3] =
{
	pic_id = 2, pic_x = 4, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 4}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[4] =
{
	pic_id = 2, pic_x = 5, pic_y = 1, state = Action.GroundSkill, wait = 2, next = { "ball", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 30, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	newobjects = {
		{
		name = "davis_ball", amount = 10, x = 90, y = -43, facing = 0, 
		frame = "flying", frameID = 0, hp = 10, dvx = 0, dvy = 0, dvz = 0, fanoutZ = 10,
		},
	},
}

frame.ball[5] =
{
	pic_id = 2, pic_x = 7, pic_y = 1, state = Action.AfterSkill, wait = 2, next = { "ball", 21}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"A", "ball", 6 }, },
}

frame.ball[6] =
{
	pic_id = 2, pic_x = 7, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 7}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 40, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[7] =
{
	pic_id = 2, pic_x = 8, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 8}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[8] =
{
	pic_id = 2, pic_x = 9, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 9}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 33, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[9] =
{
	pic_id = 2, pic_x = 10, pic_y = 1, state = Action.GroundSkill, wait = 2, next = { "ball", 10}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 23, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	newobjects = {
		{
		name = "davis_ball", amount = 10, x = 90, y = -43, facing = 0, 
		frame = "flying", frameID = 0, hp = 10, dvx = 0, dvy = 0, dvz = 0, fanoutZ = 20,
		},
	},
}

frame.ball[10] =
{
	pic_id = 2, pic_x = 6, pic_y = 1, state = Action.AfterSkill, wait = 2, next = { "ball", 21}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"A", "ball", 11 }, },
}

frame.ball[11] =
{
	pic_id = 2, pic_x = 6, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 12}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 40, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[12] =
{
	pic_id = 2, pic_x = 3, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 13}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[13] =
{
	pic_id = 2, pic_x = 4, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 14}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[14] =
{
	pic_id = 2, pic_x = 5, pic_y = 1, state = Action.GroundSkill, wait = 2, next = { "ball", 15}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 30, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	newobjects = {
		{
		name = "Davis", amount = 5, x = 96, y = -61, facing = 0, 
		frame = "rolling", frameID = 0, hp = 10, dvx = 100, dvy = 0, dvz = 0, fanoutZ = 50,
		},
	},
}

frame.ball[15] =
{
	pic_id = 2, pic_x = 7, pic_y = 1, state = Action.AfterSkill, wait = 2, next = { "ball", 21}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"A", "ball", 16 }, },
}

frame.ball[16] =
{
	pic_id = 2, pic_x = 1, pic_y = 2, state = Action.BeforeSkill, wait = 2, next = { "ball", 17}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 40, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[17] =
{
	pic_id = 2, pic_x = 2, pic_y = 2, state = Action.BeforeSkill, wait = 2, next = { "ball", 18}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 34, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[18] =
{
	pic_id = 2, pic_x = 3, pic_y = 2, state = Action.GroundSkill, wait = 2, next = { "ball", 19}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 26, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	newobjects = {
		{
		name = "davis_ball", amount = 1, x = 90, y = -48, facing = 0, 
		frame = "flying", frameID = 0, hp = 10, dvx = 0, dvy = 0, dvz = 0, fanoutZ = 10,
		},
	},
}

frame.ball[19] =
{
	pic_id = 2, pic_x = 6, pic_y = 1, state = Action.AfterSkill, wait = 2, next = { "ball", 21}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"A", "ball", 20 }, },
}

frame.ball[20] =
{
	pic_id = 2, pic_x = 6, pic_y = 1, state = Action.BeforeSkill, wait = 2, next = { "ball", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 40, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.ball[21] =
{
	pic_id = 2, pic_x = 1, pic_y = 1, state = Action.AfterSkill, wait = 4, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.crouch[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 7, state = Action.Crouch, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {25,-26}, {25,-80}, {56,-80}, {56,-26}, }, zwidth = 16},
	},
	hit = { {"D", "rolling", 0 }, },
}

frame.crouch[1] =
{
	pic_id = 0, pic_x = 1, pic_y = 7, state = Action.Crouch, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {26,-36}, {26,-80}, {55,-80}, {55,-36}, }, zwidth = 16},
	},
}

frame.dash_back[0] =
{
	pic_id = 0, pic_x = 5, pic_y = 7, state = Action.DashAttacking, wait = 1, next = { "dash_back", 1}, 
	dvx = -18, dvy = 25, dvz = 5, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {20,-5}, {20,-43}, {47,-43}, {47,-5}, }, zwidth = 16},
		{kind = 0, points = { {16,-37}, {16,-59}, {52,-59}, {52,-37}, }, zwidth = 16},
	},
}

frame.dash_back[1] =
{
	pic_id = 0, pic_x = 5, pic_y = 7, state = Action.Dash, wait = 15, next = { "dash_back", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {20,-5}, {20,-43}, {47,-43}, {47,-5}, }, zwidth = 16},
		{kind = 0, points = { {16,-37}, {16,-59}, {52,-59}, {52,-37}, }, zwidth = 16},
	},
}

frame.dash_back[2] =
{
	pic_id = 1, pic_x = 4, pic_y = 5, state = Action.Dash, wait = 4, next = { "dash_back", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {18,-13}, {18,-64}, {47,-64}, {47,-13}, }, zwidth = 16},
	},
}

frame.dash_front[0] =
{
	pic_id = 0, pic_x = 4, pic_y = 7, state = Action.DashAttacking, wait = 1, next = { "dash_front", 1}, 
	dvx = 18, dvy = 25, dvz = 5, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {43,-5}, {43,-38}, {66,-38}, {66,-5}, }, zwidth = 16},
		{kind = 0, points = { {28,-29}, {28,-62}, {49,-62}, {49,-29}, }, zwidth = 16},
		{kind = 0, points = { {18,-48}, {18,-69}, {45,-69}, {45,-48}, }, zwidth = 16},
	},
	hit = { {"B", "dash_kick", 0 }, },
}

frame.dash_front[1] =
{
	pic_id = 0, pic_x = 4, pic_y = 7, state = Action.Dash, wait = 15, next = { "dash_front", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {43,-5}, {43,-38}, {66,-38}, {66,-5}, }, zwidth = 16},
		{kind = 0, points = { {28,-29}, {28,-62}, {49,-62}, {49,-29}, }, zwidth = 16},
		{kind = 0, points = { {18,-48}, {18,-69}, {45,-69}, {45,-48}, }, zwidth = 16},
	},
	hit = { {"B", "dash_kick", 0 }, },
}

frame.dash_front[2] =
{
	pic_id = 1, pic_x = 3, pic_y = 5, state = Action.Dash, wait = 4, next = { "dash_front", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 78, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {35,-8}, {35,-35}, {62,-35}, {62,-8}, }, zwidth = 16},
		{kind = 0, points = { {16,-30}, {16,-67}, {55,-67}, {55,-30}, }, zwidth = 16},
	},
	hit = { {"B", "dash_kick", 0 }, },
}

frame.dash_kick[0] =
{
	pic_id = 1, pic_x = 3, pic_y = 7, state = Action.BeforeDashAttack, wait = 2, next = { "dash_kick", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 36, centery = 75, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {18,-10}, {18,-67}, {53,-67}, {53,-10}, }, zwidth = 16},
	},
}

frame.dash_kick[1] =
{
	pic_id = 1, pic_x = 4, pic_y = 7, state = Action.BeforeDashAttack, wait = 2, next = { "dash_kick", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 74, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {22,-9}, {22,-65}, {57,-65}, {57,-9}, }, zwidth = 16},
	},
}

frame.dash_kick[2] =
{
	pic_id = 1, pic_x = 5, pic_y = 7, state = Action.BeforeDashAttack, wait = 2, next = { "dash_kick", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 35, centery = 75, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {24,-6}, {24,-66}, {53,-66}, {53,-6}, }, zwidth = 16},
	},
}

frame.dash_kick[3] =
{
	pic_id = 1, pic_x = 6, pic_y = 7, state = Action.DashAttacking, wait = 14, next = { "dash_kick", 4}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 25, centery = 70, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {11,-2}, {11,-65}, {40,-65}, {40,-2}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {17,-37}, {17,-54}, {69,-54}, {69,-37}, }, zwidth = 16,
		dvx = 14, dvy = 15, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 18, injury = 80, strength = 50, 
		},
	},
}

frame.dash_kick[4] =
{
	pic_id = 1, pic_x = 7, pic_y = 7, state = Action.DashAttacking, wait = 2, next = { "dash_kick", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 25, centery = 71, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {11,-5}, {11,-68}, {39,-68}, {39,-5}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {32,-40}, {32,-56}, {68,-56}, {68,-40}, }, zwidth = 16,
		dvx = 14, dvy = 15, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 18, injury = 80, strength = 50, 
		},
	},
}

frame.dash_kick[5] =
{
	pic_id = 1, pic_x = 8, pic_y = 7, state = Action.AfterDashAttack, wait = 2, next = { "dash_kick", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 33, centery = 72, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-6}, {21,-64}, {50,-64}, {50,-6}, }, zwidth = 16},
	},
}

frame.default[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 30, next = { "standing", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.defend[0] =
{
	pic_id = 0, pic_x = 7, pic_y = 6, state = Action.Defend, wait = 24, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {20,-19}, {20,-79}, {58,-79}, {58,-19}, }, zwidth = 16},
	},
	hit = { {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.defend[1] =
{
	pic_id = 0, pic_x = 7, pic_y = 6, state = Action.Defend, wait = 1, next = { "defend", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 40, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {16,-19}, {16,-79}, {58,-79}, {58,-19}, }, zwidth = 16},
	},
	hit = { {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.falling_back[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 4, state = Action.FallingBack, wait = 1, next = { "falling_back", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 37, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 1, points = { {25,-25}, {25,-45}, {46,-45}, {46,-25}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 4, effect = Effect.Punch,
		points = { {21,-14}, {21,-58}, {50,-58}, {50,-14}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
	hit = { {"J", "back_flip", 0 }, },
}

frame.falling_back[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 4, state = Action.FallingBack, wait = 1, next = { "falling_back", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 37, centery = 85, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 1, points = { {22,-20}, {22,-43}, {46,-43}, {46,-20}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 4, effect = Effect.Punch,
		points = { {8,-15}, {8,-47}, {38,-47}, {38,-15}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
		{
		kind = 4, effect = Effect.Punch,
		points = { {27,-35}, {27,-56}, {55,-56}, {55,-35}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
	hit = { {"J", "back_flip", 0 }, },
}

frame.falling_back[2] =
{
	pic_id = 0, pic_x = 3, pic_y = 4, state = Action.FallingBack, wait = 1, next = { "falling_back", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 1, points = { {27,-22}, {27,-40}, {47,-40}, {47,-22}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 4, effect = Effect.Punch,
		points = { {13,-18}, {13,-44}, {59,-44}, {59,-18}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
	hit = { {"J", "back_flip", 0 }, },
}

frame.falling_back[3] =
{
	pic_id = 0, pic_x = 4, pic_y = 4, state = Action.FallingBack, wait = 1, next = { "falling_back", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 1, points = { {22,-30}, {22,-51}, {49,-51}, {49,-30}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 4, effect = Effect.Punch,
		points = { {32,-18}, {32,-45}, {65,-45}, {65,-18}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
		{
		kind = 4, effect = Effect.Punch,
		points = { {10,-38}, {10,-59}, {48,-59}, {48,-38}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
	hit = { {"J", "back_flip", 0 }, },
}

frame.falling_back[4] =
{
	pic_id = 0, pic_x = 5, pic_y = 4, state = Action.FallingBack, wait = 1, next = { "falling_back", 4}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 66, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.falling_back[5] =
{
	pic_id = 0, pic_x = 6, pic_y = 4, state = Action.FallingBack, wait = 1, next = { "falling_back", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.falling_front[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 5, state = Action.FallingFront, wait = 1, next = { "falling_front", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {31,-24}, {31,-47}, {56,-47}, {56,-24}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 4, effect = Effect.Punch,
		points = { {22,-12}, {22,-62}, {58,-62}, {58,-12}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
	hit = { {"J", "front_flip", 0 }, },
}

frame.falling_front[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 5, state = Action.FallingFront, wait = 1, next = { "falling_front", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-27}, {28,-53}, {52,-53}, {52,-27}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 4, effect = Effect.Punch,
		points = { {33,-6}, {33,-52}, {59,-52}, {59,-6}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
		{
		kind = 4, effect = Effect.Punch,
		points = { {26,-43}, {26,-72}, {47,-72}, {47,-43}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
	hit = { {"J", "front_flip", 0 }, },
}

frame.falling_front[2] =
{
	pic_id = 0, pic_x = 3, pic_y = 5, state = Action.FallingFront, wait = 1, next = { "falling_front", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {30,-31}, {30,-52}, {54,-52}, {54,-31}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 4, effect = Effect.Punch,
		points = { {14,-29}, {14,-52}, {72,-52}, {72,-29}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
	hit = { {"J", "front_flip", 0 }, },
}

frame.falling_front[3] =
{
	pic_id = 0, pic_x = 4, pic_y = 5, state = Action.FallingFront, wait = 1, next = { "falling_front", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {30,-39}, {30,-60}, {53,-60}, {53,-39}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 4, effect = Effect.Punch,
		points = { {24,-27}, {24,-55}, {50,-55}, {50,-27}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
		{
		kind = 4, effect = Effect.Punch,
		points = { {37,-45}, {37,-73}, {68,-73}, {68,-45}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 70, breakDefend = 10, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
	hit = { {"J", "front_flip", 0 }, },
}

frame.falling_front[4] =
{
	pic_id = 0, pic_x = 5, pic_y = 5, state = Action.FallingFront, wait = 1, next = { "falling_front", 4}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 71, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.falling_front[5] =
{
	pic_id = 0, pic_x = 6, pic_y = 5, state = Action.FallingFront, wait = 1, next = { "falling_front", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.front_flip[0] =
{
	pic_id = 1, pic_x = 8, pic_y = 5, state = Action.Fliping, wait = 6, next = { "front_flip", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 42, centery = 72, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.front_flip[1] =
{
	pic_id = 1, pic_x = 9, pic_y = 5, state = Action.Fliping, wait = 12, next = { "front_flip", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.in_the_air[0] =
{
	pic_id = 0, pic_x = 3, pic_y = 7, state = Action.InTheAir, wait = 2, next = { "in_the_air", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {20,-11}, {20,-72}, {49,-72}, {49,-11}, }, zwidth = 16},
	},
	hit = { {"B", "jump_kick", 0 }, {"DAda", "TTEST", 0 }, },
}

frame.injured[0] =
{
	pic_id = 1, pic_x = 1, pic_y = 6, state = Action.Injured, wait = 4, next = { "injured", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 35, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {25,-17}, {25,-78}, {54,-78}, {54,-17}, }, zwidth = 16},
	},
}

frame.injured[1] =
{
	pic_id = 1, pic_x = 2, pic_y = 6, state = Action.Injured, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 34, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {32,-16}, {32,-79}, {59,-79}, {59,-16}, }, zwidth = 16},
		{kind = 0, points = { {22,-37}, {22,-79}, {48,-79}, {48,-37}, }, zwidth = 16},
	},
}

frame.injured[2] =
{
	pic_id = 1, pic_x = 4, pic_y = 6, state = Action.Injured, wait = 4, next = { "injured", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 36, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {11,-24}, {11,-55}, {50,-55}, {50,-24}, }, zwidth = 16},
		{kind = 0, points = { {25,-53}, {25,-80}, {65,-80}, {65,-53}, }, zwidth = 16},
	},
}

frame.injured[3] =
{
	pic_id = 1, pic_x = 5, pic_y = 6, state = Action.Injured, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 43, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {12,-23}, {12,-60}, {52,-60}, {52,-23}, }, zwidth = 16},
		{kind = 0, points = { {27,-56}, {27,-80}, {63,-80}, {63,-56}, }, zwidth = 16},
	},
}

frame.injured[4] =
{
	pic_id = 1, pic_x = 1, pic_y = 7, state = Action.Injured, wait = 4, next = { "injured", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 43, centery = 76, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {25,-13}, {25,-78}, {55,-78}, {55,-13}, }, zwidth = 16},
	},
}

frame.injured[5] =
{
	pic_id = 1, pic_x = 2, pic_y = 7, state = Action.Injured, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 44, centery = 78, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {24,-18}, {24,-81}, {59,-81}, {59,-18}, }, zwidth = 16},
	},
}

frame.injured[6] =
{
	pic_id = 1, pic_x = 1, pic_y = 6, state = Action.Injured, wait = 12, next = { "injured", 7}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {27,-22}, {27,-80}, {69,-80}, {69,-22}, }, zwidth = 16},
	},
}

frame.injured[7] =
{
	pic_id = 1, pic_x = 3, pic_y = 6, state = Action.Injured, wait = 12, next = { "injured", 8}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-24}, {28,-81}, {67,-81}, {67,-24}, }, zwidth = 16},
	},
}

frame.injured[8] =
{
	pic_id = 1, pic_x = 2, pic_y = 6, state = Action.Injured, wait = 12, next = { "injured", 9}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 38, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-23}, {28,-81}, {63,-81}, {63,-23}, }, zwidth = 16},
	},
}

frame.injured[9] =
{
	pic_id = 1, pic_x = 3, pic_y = 6, state = Action.Injured, wait = 12, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {29,-26}, {29,-79}, {66,-79}, {66,-26}, }, zwidth = 16},
	},
}

frame.jump[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 7, state = Action.Crouch, wait = 2, next = { "jump", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {22,-24}, {22,-82}, {57,-82}, {57,-24}, }, zwidth = 16},
	},
}

frame.jump[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 7, state = Action.Jump, wait = 2, next = { "jump", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {26,-26}, {26,-82}, {60,-82}, {60,-26}, }, zwidth = 16},
	},
}

frame.jump[2] =
{
	pic_id = 0, pic_x = 3, pic_y = 7, state = Action.Jump, wait = 2, next = { "in_the_air", 0}, 
	dvx = 10, dvy = 32.6, dvz = 3.75, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {20,-11}, {20,-72}, {49,-72}, {49,-11}, }, zwidth = 16},
	},
	hit = { {"B", "jump_kick", 0 }, },
}

frame.jump_hit[0] =
{
	pic_id = 2, pic_x = 1, pic_y = 3, state = Action.BeforeSkill, wait = 2, next = { "jump_hit", 1}, 
	dvx = 8, dvy = 32, dvz = 0, centerx = 32, centery = 75, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 25, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {13,-8}, {13,-69}, {51,-69}, {51,-8}, }, zwidth = 16},
	},
}

frame.jump_hit[1] =
{
	pic_id = 2, pic_x = 2, pic_y = 3, state = Action.BeforeSkill, wait = 4, next = { "jump_hit", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 31, centery = 75, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {15,-8}, {15,-70}, {49,-70}, {49,-8}, }, zwidth = 16},
	},
}

frame.jump_hit[2] =
{
	pic_id = 2, pic_x = 2, pic_y = 3, state = Action.BeforeSkill, wait = 30, next = { "jump_hit", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 37, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-8}, {21,-74}, {55,-74}, {55,-8}, }, zwidth = 16},
	},
	hit = { {"A", "jump_hit", 3 }, },
}

frame.jump_hit[3] =
{
	pic_id = 2, pic_x = 3, pic_y = 3, state = Action.GroundSkill, wait = 6, next = { "jump_hit", 4}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 26, centery = 72, clear_key_queue = 1, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {16,-20}, {16,-66}, {62,-66}, {62,-20}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {17,-19}, {17,-64}, {62,-64}, {62,-19}, }, zwidth = 16,
		dvx = 22, dvy = -15, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 24, injury = 50, strength = 50, 
		},
	},
}

frame.jump_hit[4] =
{
	pic_id = 2, pic_x = 4, pic_y = 3, state = Action.AfterSkill, wait = 30, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 26, centery = 72, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {16,-20}, {16,-66}, {62,-66}, {62,-20}, }, zwidth = 16},
	},
}

frame.jump_kick[0] =
{
	pic_id = 1, pic_x = 3, pic_y = 7, state = Action.BeforeJumpAttack, wait = 2, next = { "jump_kick", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 36, centery = 75, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {18,-10}, {18,-67}, {53,-67}, {53,-10}, }, zwidth = 16},
	},
}

frame.jump_kick[1] =
{
	pic_id = 1, pic_x = 4, pic_y = 7, state = Action.BeforeJumpAttack, wait = 2, next = { "jump_kick", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 74, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {22,-9}, {22,-65}, {57,-65}, {57,-9}, }, zwidth = 16},
	},
}

frame.jump_kick[2] =
{
	pic_id = 1, pic_x = 5, pic_y = 7, state = Action.BeforeJumpAttack, wait = 2, next = { "jump_kick", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 35, centery = 75, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {24,-6}, {24,-66}, {53,-66}, {53,-6}, }, zwidth = 16},
	},
}

frame.jump_kick[3] =
{
	pic_id = 1, pic_x = 6, pic_y = 7, state = Action.JumpAttacking, wait = 6, next = { "jump_kick", 4}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 25, centery = 70, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {18,-10}, {18,-67}, {53,-67}, {53,-10}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {17,-37}, {17,-54}, {69,-54}, {69,-37}, }, zwidth = 16,
		dvx = 9, dvy = 5, dvz = 0, fall = 70, breakDefend = 30, 
		arest = 8, reAttackRest = 30, injury = 60, strength = 50, 
		},
	},
}

frame.jump_kick[4] =
{
	pic_id = 1, pic_x = 7, pic_y = 7, state = Action.JumpAttacking, wait = 2, next = { "jump_kick", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 25, centery = 71, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {11,-5}, {11,-68}, {39,-68}, {39,-5}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {32,-40}, {32,-56}, {68,-56}, {68,-40}, }, zwidth = 16,
		dvx = 9, dvy = 5, dvz = 0, fall = 70, breakDefend = 30, 
		arest = 8, reAttackRest = 30, injury = 60, strength = 50, 
		},
	},
}

frame.jump_kick[5] =
{
	pic_id = 1, pic_x = 8, pic_y = 7, state = Action.AfterJumpAttack, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 33, centery = 72, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-6}, {21,-64}, {50,-64}, {50,-6}, }, zwidth = 16},
	},
}

frame.kick[0] =
{
	pic_id = 0, pic_x = 5, pic_y = 2, state = Action.BeforeAttack, wait = 2, next = { "kick", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 42, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {26,-12}, {26,-80}, {53,-80}, {53,-12}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 2, effect = Effect.End,
		points = { {25,-58}, {25,-79}, {62,-79}, {62,-58}, }, zwidth = 16,
		dvx = 0, dvy = 0, dvz = 0, fall = 0, breakDefend = 0, 
		arest = 0, reAttackRest = 1, injury = 0, strength = 0, 
		},
	},
}

frame.kick[1] =
{
	pic_id = 0, pic_x = 6, pic_y = 2, state = Action.Attacking, wait = 2, next = { "kick", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 24, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {13,-11}, {13,-78}, {45,-78}, {45,-11}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {23,-38}, {23,-53}, {64,-53}, {64,-38}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 20, breakDefend = 16, 
		arest = 8, reAttackRest = 20, injury = 20, strength = 50, 
		},
	},
}

frame.kick[2] =
{
	pic_id = 0, pic_x = 7, pic_y = 2, state = Action.AfterAttack, wait = 2, next = { "kick", 3}, 
	dvx = 2, dvy = 0, dvz = 0, centerx = 28, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {17,-15}, {17,-79}, {54,-79}, {54,-15}, }, zwidth = 16},
	},
}

frame.kick[3] =
{
	pic_id = 0, pic_x = 8, pic_y = 2, state = Action.AfterAttack, wait = 2, next = { "default", 0}, 
	dvx = 2, dvy = 0, dvz = 0, centerx = 41, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-9}, {28,-81}, {60,-81}, {60,-9}, }, zwidth = 16},
	},
}

frame.lying[0] =
{
	pic_id = 0, pic_x = 5, pic_y = 4, state = Action.Lying, wait = 60, next = { "crouch", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 38, centery = 73, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.lying[1] =
{
	pic_id = 0, pic_x = 5, pic_y = 5, state = Action.Lying, wait = 60, next = { "crouch", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 75, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.many_punch[0] =
{
	pic_id = 2, pic_x = 4, pic_y = 2, state = Action.BeforeSkill, wait = 2, next = { "many_punch", 1}, 
	dvx = 7, dvy = 0, dvz = 0, centerx = 37, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 75, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
}

frame.many_punch[1] =
{
	pic_id = 2, pic_x = 5, pic_y = 2, state = Action.GroundSkill, wait = 2, next = { "many_punch", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 33, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {63,-9}, {63,-76}, {79,-76}, {79,-9}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
		{
		kind = 0, effect = Effect.Punch,
		points = { {17,-35}, {17,-48}, {78,-48}, {78,-35}, }, zwidth = 16,
		dvx = 7, dvy = 0, dvz = 0, fall = 1, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 25, strength = 50, 
		},
	},
}

frame.many_punch[2] =
{
	pic_id = 2, pic_x = 6, pic_y = 2, state = Action.GroundSkill, wait = 2, next = { "many_punch", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 38, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {49,-9}, {49,-73}, {67,-73}, {67,-9}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
	},
}

frame.many_punch[3] =
{
	pic_id = 2, pic_x = 7, pic_y = 2, state = Action.GroundSkill, wait = 2, next = { "many_punch", 4}, 
	dvx = 1, dvy = 0, dvz = 0, centerx = 32, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {57,-9}, {57,-76}, {75,-76}, {75,-9}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
		{
		kind = 0, effect = Effect.Punch,
		points = { {14,-35}, {14,-53}, {72,-53}, {72,-35}, }, zwidth = 16,
		dvx = 7, dvy = 0, dvz = 0, fall = 1, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 25, strength = 50, 
		},
	},
}

frame.many_punch[4] =
{
	pic_id = 2, pic_x = 8, pic_y = 2, state = Action.GroundSkill, wait = 2, next = { "many_punch", 5}, 
	dvx = 1, dvy = 0, dvz = 0, centerx = 24, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {49,-9}, {49,-73}, {67,-73}, {67,-9}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
	},
}

frame.many_punch[5] =
{
	pic_id = 2, pic_x = 9, pic_y = 2, state = Action.GroundSkill, wait = 2, next = { "many_punch", 6}, 
	dvx = 5, dvy = 0, dvz = 0, centerx = 24, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {49,-9}, {49,-73}, {67,-73}, {67,-9}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
	},
}

frame.many_punch[6] =
{
	pic_id = 2, pic_x = 10, pic_y = 2, state = Action.GroundSkill, wait = 2, next = { "many_punch", 7}, 
	dvx = 1, dvy = 0, dvz = 0, centerx = 22, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {64,-10}, {64,-78}, {82,-78}, {82,-10}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
		{
		kind = 0, effect = Effect.Punch,
		points = { {-1,-22}, {-1,-47}, {80,-47}, {80,-22}, }, zwidth = 16,
		dvx = 10, dvy = 0, dvz = 0, fall = 1, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 25, strength = 50, 
		},
	},
}

frame.many_punch[7] =
{
	pic_id = 2, pic_x = 10, pic_y = 3, state = Action.GroundSkill, wait = 2, next = { "many_punch", 8}, 
	dvx = 1, dvy = 0, dvz = 0, centerx = 18, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {49,-9}, {49,-73}, {67,-73}, {67,-9}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
	},
}

frame.many_punch[8] =
{
	pic_id = 2, pic_x = 9, pic_y = 3, state = Action.GroundSkill, wait = 2, next = { "many_punch", 9}, 
	dvx = 5, dvy = 0, dvz = 0, centerx = 22, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {49,-9}, {49,-73}, {67,-73}, {67,-9}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
	},
	hit = { {"D^A", "singlong", 0 }, },
}

frame.many_punch[9] =
{
	pic_id = 2, pic_x = 8, pic_y = 3, state = Action.GroundSkill, wait = 2, next = { "many_punch", 10}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 26, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {49,-9}, {49,-73}, {67,-73}, {67,-9}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
	},
	hit = { {"D^A", "singlong", 0 }, },
}

frame.many_punch[10] =
{
	pic_id = 2, pic_x = 7, pic_y = 3, state = Action.GroundSkill, wait = 2, next = { "many_punch", 11}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 22, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 10, effect = Effect.Punch,
		points = { {10,-2}, {10,-70}, {85,-70}, {85,-2}, }, zwidth = 16,
		dvx = 12, dvy = 0, dvz = 0, fall = 70, breakDefend = 16, 
		arest = 8, reAttackRest = 14, injury = 45, strength = 50, 
		},
		{
		kind = 0, effect = Effect.Punch,
		points = { {12,-11}, {12,-62}, {82,-62}, {82,-11}, }, zwidth = 16,
		dvx = 7, dvy = 30, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 30, injury = 25, strength = 50, 
		},
	},
}

frame.many_punch[11] =
{
	pic_id = 2, pic_x = 6, pic_y = 3, state = Action.AfterSkill, wait = 4, next = { "many_punch", 12}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 27, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"J", "jump_hit", 0 }, },
}

frame.many_punch[12] =
{
	pic_id = 2, pic_x = 5, pic_y = 3, state = Action.AfterSkill, wait = 6, next = { "default", 0}, 
	dvx = 1, dvy = 0, dvz = 0, centerx = 34, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"J", "jump_hit", 0 }, },
}

frame.punch[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 2, state = Action.BeforeAttack, wait = 2, next = { "punch", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 42, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-12}, {28,-82}, {61,-82}, {61,-12}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 2, effect = Effect.End,
		points = { {27,-57}, {27,-82}, {63,-82}, {63,-57}, }, zwidth = 16,
		dvx = 0, dvy = 0, dvz = 0, fall = 0, breakDefend = 0, 
		arest = 0, reAttackRest = 1, injury = 0, strength = 0, 
		},
	},
}

frame.punch[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 2, state = Action.Attacking, wait = 2, next = { "punch", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 23, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {13,-11}, {13,-82}, {61,-82}, {61,-11}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Fire,
		points = { {21,-31}, {21,-49}, {64,-49}, {64,-31}, }, zwidth = 16,
		dvx = 2, dvy = 0, dvz = 0, fall = 20, breakDefend = 16, 
		arest = 8, reAttackRest = 10, injury = 20, strength = 50, 
		},
	},
}

frame.punch[2] =
{
	pic_id = 0, pic_x = 3, pic_y = 2, state = Action.AfterAttack, wait = 2, next = { "punch", 3}, 
	dvx = 2, dvy = 0, dvz = 0, centerx = 28, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {17,-9}, {17,-81}, {48,-81}, {48,-9}, }, zwidth = 16},
	},
}

frame.punch[3] =
{
	pic_id = 0, pic_x = 4, pic_y = 2, state = Action.AfterAttack, wait = 2, next = { "default", 0}, 
	dvx = 2, dvy = 0, dvz = 0, centerx = 41, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {29,-10}, {29,-80}, {61,-80}, {61,-10}, }, zwidth = 16},
	},
}

frame.rolling[0] =
{
	pic_id = 0, pic_x = 9, pic_y = 6, state = Action.Rolling, wait = 4, next = { "rolling", 1}, 
	dvx = 10, dvy = 0, dvz = 5, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	attack = {
		{
		kind = 7, effect = Effect.End,
		points = { {36,-54}, {36,-79}, {49,-79}, {49,-54}, }, zwidth = 16,
		dvx = 0, dvy = 0, dvz = 0, fall = 0, breakDefend = 0, 
		arest = 0, reAttackRest = 1, injury = 0, strength = 0, 
		},
	},
	hit = { {"D^A", "singlong", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.rolling[1] =
{
	pic_id = 0, pic_x = 10, pic_y = 6, state = Action.Rolling, wait = 4, next = { "rolling", 2}, 
	dvx = 5, dvy = 0, dvz = 5, centerx = 34, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	attack = {
		{
		kind = 7, effect = Effect.End,
		points = { {36,-54}, {36,-79}, {49,-79}, {49,-54}, }, zwidth = 16,
		dvx = 0, dvy = 0, dvz = 0, fall = 0, breakDefend = 0, 
		arest = 0, reAttackRest = 1, injury = 0, strength = 0, 
		},
	},
	hit = { {"D^A", "singlong", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.rolling[2] =
{
	pic_id = 0, pic_x = 10, pic_y = 7, state = Action.Rolling, wait = 4, next = { "rolling", 3}, 
	dvx = 3, dvy = 0, dvz = 5, centerx = 34, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	attack = {
		{
		kind = 7, effect = Effect.End,
		points = { {36,-54}, {36,-79}, {49,-79}, {49,-54}, }, zwidth = 16,
		dvx = 0, dvy = 0, dvz = 0, fall = 0, breakDefend = 0, 
		arest = 0, reAttackRest = 1, injury = 0, strength = 0, 
		},
	},
	hit = { {"D^A", "singlong", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.rolling[3] =
{
	pic_id = 0, pic_x = 9, pic_y = 6, state = Action.Rolling, wait = 4, next = { "crouch", 1}, 
	dvx = 2, dvy = 0, dvz = 5, centerx = 38, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	attack = {
		{
		kind = 7, effect = Effect.End,
		points = { {36,-54}, {36,-79}, {49,-79}, {49,-54}, }, zwidth = 16,
		dvx = 0, dvy = 0, dvz = 0, fall = 0, breakDefend = 0, 
		arest = 0, reAttackRest = 1, injury = 0, strength = 0, 
		},
	},
	hit = { {"D^A", "singlong", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.run_punch[0] =
{
	pic_id = 1, pic_x = 1, pic_y = 4, state = Action.BeforeRunAttack, wait = 4, next = { "run_punch", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 35, centery = 79, clear_key_queue = 1, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {17,-25}, {17,-79}, {61,-79}, {61,-25}, }, zwidth = 16},
	},
}

frame.run_punch[1] =
{
	pic_id = 1, pic_x = 2, pic_y = 4, state = Action.BeforeRunAttack, wait = 2, next = { "run_punch", 2}, 
	dvx = 16, dvy = 0, dvz = 0, centerx = 30, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {25,-24}, {25,-79}, {56,-79}, {56,-24}, }, zwidth = 16},
	},
}

frame.run_punch[2] =
{
	pic_id = 1, pic_x = 3, pic_y = 4, state = Action.RunAttacking, wait = 2, next = { "run_punch", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 25, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {15,-19}, {15,-81}, {52,-81}, {52,-19}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {-18,-24}, {-18,-54}, {70,-54}, {70,-24}, }, zwidth = 16,
		dvx = 30, dvy = 0, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 14, injury = 55, strength = 50, 
		},
	},
	hit = { {"A", "run_punch", 4 }, },
}

frame.run_punch[3] =
{
	pic_id = 1, pic_x = 4, pic_y = 4, state = Action.RunAttacking, wait = 6, next = { "run_punch", 4}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 20, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {14,-14}, {14,-81}, {57,-81}, {57,-14}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {28,-25}, {28,-52}, {71,-52}, {71,-25}, }, zwidth = 16,
		dvx = 26, dvy = 0, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 20, injury = 40, strength = 50, 
		},
	},
	hit = { {"A", "run_punch", 4 }, },
}

frame.run_punch[4] =
{
	pic_id = 1, pic_x = 5, pic_y = 4, state = Action.AfterRunAttack, wait = 4, next = { "run_punch", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 20, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {18,-10}, {18,-67}, {53,-67}, {53,-10}, }, zwidth = 16},
	},
}

frame.run_punch[5] =
{
	pic_id = 1, pic_x = 6, pic_y = 4, state = Action.AfterRunAttack, wait = 4, next = { "run_punch", 6}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 30, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {20,-11}, {20,-79}, {51,-79}, {51,-11}, }, zwidth = 16},
	},
}

frame.run_punch[6] =
{
	pic_id = 1, pic_x = 7, pic_y = 4, state = Action.AfterRunAttack, wait = 2, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 32, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {20,-11}, {20,-79}, {51,-79}, {51,-11}, }, zwidth = 16},
	},
}

frame.running[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 3, state = Action.Running, wait = 6, next = { "running", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 36, centery = 80, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {25,-19}, {25,-79}, {63,-79}, {63,-19}, }, zwidth = 16},
	},
	hit = { {"A", "run_punch", 0 }, {"J", "dash_front", 0 }, {"D", "rolling", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.running[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 3, state = Action.Running, wait = 6, next = { "running", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 37, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {25,-19}, {25,-79}, {63,-79}, {63,-19}, }, zwidth = 16},
	},
	hit = { {"A", "run_punch", 0 }, {"J", "dash_front", 0 }, {"D", "rolling", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.running[2] =
{
	pic_id = 0, pic_x = 3, pic_y = 3, state = Action.Running, wait = 6, next = { "running", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 32, centery = 78, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {25,-19}, {25,-79}, {63,-79}, {63,-19}, }, zwidth = 16},
	},
	hit = { {"A", "run_punch", 0 }, {"J", "dash_front", 0 }, {"D", "rolling", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.running[3] =
{
	pic_id = 0, pic_x = 2, pic_y = 3, state = Action.Running, wait = 6, next = { "running", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 37, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {25,-19}, {25,-79}, {63,-79}, {63,-19}, }, zwidth = 16},
	},
	hit = { {"A", "run_punch", 0 }, {"J", "dash_front", 0 }, {"D", "rolling", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.singlong[0] =
{
	pic_id = 2, pic_x = 1, pic_y = 4, state = Action.BeforeSkill, wait = 2, next = { "singlong", 1}, 
	dvx = 7, dvy = 36, dvz = 0, centerx = 30, centery = 76, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 225, backFrame = "super_punch", backFrameID = 0, },
	sound = "media\\music\\095.wav",
}

frame.singlong[1] =
{
	pic_id = 2, pic_x = 2, pic_y = 4, state = Action.GroundSkill, wait = 2, next = { "singlong", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 28, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {10,-3}, {10,-78}, {82,-78}, {82,-3}, }, zwidth = 16,
		dvx = 7, dvy = 39, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 20, injury = 85, strength = 50, 
		},
	},
	sound = "media\\music\\031.wav",
}

frame.singlong[2] =
{
	pic_id = 2, pic_x = 3, pic_y = 4, state = Action.GroundSkill, wait = 2, next = { "singlong", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 26, centery = 81, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {19,-7}, {19,-78}, {55,-78}, {55,-7}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {13,1}, {13,-79}, {80,-79}, {80,1}, }, zwidth = 16,
		dvx = 7, dvy = 33, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 20, injury = 60, strength = 50, 
		},
	},
}

frame.singlong[3] =
{
	pic_id = 2, pic_x = 4, pic_y = 4, state = Action.GroundSkill, wait = 2, next = { "singlong", 4}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 26, centery = 78, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {22,-6}, {22,-75}, {52,-75}, {52,-6}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {11,2}, {11,-78}, {74,-78}, {74,2}, }, zwidth = 16,
		dvx = 7, dvy = 27, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 20, injury = 45, strength = 50, 
		},
	},
}

frame.singlong[4] =
{
	pic_id = 2, pic_x = 5, pic_y = 4, state = Action.GroundSkill, wait = 4, next = { "singlong", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 34, centery = 81, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-12}, {28,-78}, {57,-78}, {57,-12}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {19,-1}, {19,-81}, {80,-81}, {80,-1}, }, zwidth = 16,
		dvx = 7, dvy = 21, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
}

frame.singlong[5] =
{
	pic_id = 2, pic_x = 6, pic_y = 4, state = Action.AfterSkill, wait = 4, next = { "singlong", 6}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 33, centery = 75, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {27,-7}, {27,-72}, {55,-72}, {55,-7}, }, zwidth = 16},
	},
}

frame.singlong[6] =
{
	pic_id = 2, pic_x = 7, pic_y = 4, state = Action.AfterSkill, wait = 6, next = { "singlong", 7}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 29, centery = 74, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {23,-11}, {23,-72}, {53,-72}, {53,-11}, }, zwidth = 16},
	},
}

frame.singlong[7] =
{
	pic_id = 2, pic_x = 8, pic_y = 4, state = Action.AfterSkill, wait = 4, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 29, centery = 73, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-3}, {21,-71}, {54,-71}, {54,-3}, }, zwidth = 16},
	},
}

frame.standing[0] =
{
	pic_id = 0, pic_x = 1, pic_y = 1, state = Action.Standing, wait = 30, next = { "standing", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.standing[1] =
{
	pic_id = 0, pic_x = 2, pic_y = 1, state = Action.Standing, wait = 30, next = { "standing", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.standing[2] =
{
	pic_id = 0, pic_x = 3, pic_y = 1, state = Action.Standing, wait = 30, next = { "standing", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.standing[3] =
{
	pic_id = 0, pic_x = 4, pic_y = 1, state = Action.Standing, wait = 30, next = { "standing", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {21,-18}, {21,-80}, {64,-80}, {64,-18}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
}

frame.stop_running[0] =
{
	pic_id = 1, pic_x = 5, pic_y = 5, state = Action.StopRunning, wait = 30, next = { "default", 0}, 
	dvx = 1, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {17,-25}, {17,-80}, {47,-80}, {61,-79}, {61,-47}, {47,-25}, }, zwidth = 16},
	},
}

frame.super_punch[0] =
{
	pic_id = 0, pic_x = 8, pic_y = 7, state = Action.BeforeSuperAttack, wait = 4, next = { "super_punch", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 32, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {25,-16}, {25,-77}, {55,-77}, {55,-16}, }, zwidth = 16},
	},
}

frame.super_punch[1] =
{
	pic_id = 0, pic_x = 9, pic_y = 7, state = Action.BeforeSuperAttack, wait = 2, next = { "super_punch", 2}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 23, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {20,-14}, {20,-80}, {54,-80}, {54,-14}, }, zwidth = 16},
	},
}

frame.super_punch[2] =
{
	pic_id = 0, pic_x = 9, pic_y = 1, state = Action.SuperAttacking, wait = 4, next = { "super_punch", 3}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 28, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {26,-12}, {26,-78}, {61,-78}, {61,-12}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {40,-5}, {40,-50}, {75,-50}, {75,-5}, }, zwidth = 16,
		dvx = 3, dvy = 30, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 30, injury = 40, strength = 50, 
		},
	},
}

frame.super_punch[3] =
{
	pic_id = 0, pic_x = 10, pic_y = 1, state = Action.AfterSuperAttack, wait = 2, next = { "super_punch", 4}, 
	dvx = 5, dvy = 0, dvz = 0, centerx = 27, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {23,-10}, {23,-79}, {52,-79}, {52,-10}, }, zwidth = 16},
	},
}

frame.super_punch[4] =
{
	pic_id = 0, pic_x = 10, pic_y = 2, state = Action.BeforeSuperAttack, wait = 4, next = { "super_punch", 5}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 28, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {18,-15}, {18,-80}, {59,-80}, {59,-15}, }, zwidth = 16},
	},
}

frame.super_punch[5] =
{
	pic_id = 0, pic_x = 10, pic_y = 3, state = Action.BeforeSuperAttack, wait = 2, next = { "super_punch", 6}, 
	dvx = 6, dvy = 0, dvz = 0, centerx = 32, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {24,-10}, {24,-80}, {58,-80}, {58,-10}, }, zwidth = 16},
	},
}

frame.super_punch[6] =
{
	pic_id = 0, pic_x = 10, pic_y = 4, state = Action.SuperAttacking, wait = 4, next = { "super_punch", 7}, 
	dvx = 1, dvy = 0, dvz = 0, centerx = 38, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {29,-6}, {29,-78}, {52,-78}, {52,-6}, }, zwidth = 16},
	},
	attack = {
		{
		kind = 0, effect = Effect.Punch,
		points = { {40,-4}, {40,-48}, {72,-48}, {72,-4}, }, zwidth = 16,
		dvx = 7, dvy = 39, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 30, injury = 40, strength = 50, 
		},
	},
}

frame.super_punch[7] =
{
	pic_id = 0, pic_x = 10, pic_y = 5, state = Action.AfterSuperAttack, wait = 4, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 33, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {22,-13}, {22,-81}, {56,-81}, {56,-13}, }, zwidth = 16},
	},
	hit = { {"J", "jump_hit", 0 }, },
}

frame.walking[0] =
{
	pic_id = 0, pic_x = 5, pic_y = 1, state = Action.Walking, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 78, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-15}, {28,-80}, {55,-80}, {55,-15}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
	catch = {
		{
		kind = 0, strong = 0, catchx = 0, catchy = 0, where = Body.Neck, 
		points = { {40,-16}, {40,-81}, {65,-81}, {65,-16}, }, zwidth = 0
		},
	},
}

frame.walking[1] =
{
	pic_id = 0, pic_x = 6, pic_y = 1, state = Action.Walking, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-15}, {28,-80}, {55,-80}, {55,-15}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
	catch = {
		{
		kind = 0, strong = 0, catchx = 0, catchy = 0, where = Body.Neck, 
		points = { {40,-16}, {40,-81}, {65,-81}, {65,-16}, }, zwidth = 0
		},
	},
}

frame.walking[2] =
{
	pic_id = 0, pic_x = 7, pic_y = 1, state = Action.Walking, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-15}, {28,-80}, {55,-80}, {55,-15}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
	catch = {
		{
		kind = 0, strong = 0, catchx = 0, catchy = 0, where = Body.Neck, 
		points = { {40,-16}, {40,-81}, {65,-81}, {65,-16}, }, zwidth = 0
		},
	},
}

frame.walking[3] =
{
	pic_id = 0, pic_x = 8, pic_y = 1, state = Action.Walking, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 78, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-15}, {28,-80}, {55,-80}, {55,-15}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
	catch = {
		{
		kind = 0, strong = 0, catchx = 0, catchy = 0, where = Body.Neck, 
		points = { {40,-16}, {40,-81}, {65,-81}, {65,-16}, }, zwidth = 0
		},
	},
}

frame.walking[4] =
{
	pic_id = 0, pic_x = 7, pic_y = 1, state = Action.Walking, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-15}, {28,-80}, {55,-80}, {55,-15}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
	catch = {
		{
		kind = 0, strong = 0, catchx = 0, catchy = 0, where = Body.Neck, 
		points = { {40,-16}, {40,-81}, {65,-81}, {65,-16}, }, zwidth = 0
		},
	},
}

frame.walking[5] =
{
	pic_id = 0, pic_x = 6, pic_y = 1, state = Action.Walking, wait = 6, next = { "default", 0}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	body = {
		{kind = 0, points = { {28,-15}, {28,-80}, {55,-80}, {55,-15}, }, zwidth = 16},
	},
	hit = { {"A", "punch", 0 }, {"B", "kick", 0 }, {"J", "jump", 0 }, {"D", "defend", 0 }, {"D>A", "ball", 0 }, {"D^A", "singlong", 0 }, {"DvA", "many_punch", 0 }, {"D^J", "jump_hit", 0 }, },
	catch = {
		{
		kind = 0, strong = 0, catchx = 0, catchy = 0, where = Body.Neck, 
		points = { {40,-16}, {40,-81}, {65,-81}, {65,-16}, }, zwidth = 0
		},
	},
}

frame.TTEST[0] =
{
	pic_id = 0, pic_x = 7, pic_y = 7, state = Action.TTEST, wait = 4, next = { "TTEST", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 40, centery = 80, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
}

frame.TTEST[1] =
{
	pic_id = 0, pic_x = 6, pic_y = 7, state = Action.TTEST, wait = 12, next = { "TTEST", 1}, 
	dvx = 0, dvy = 0, dvz = 0, centerx = 39, centery = 79, clear_key_queue = 0, 
	consume = { rule = 1, HP = 0, MP = 0, backFrame = "default", backFrameID = 0, },
	attack = {
		{
		kind = 0, effect = Effect.TTEST,
		points = { {5,-32}, {31,-83}, {57,-70}, {31,-1}, }, zwidth = 10,
		dvx = 2, dvy = -10, dvz = 0, fall = 70, breakDefend = 60, 
		arest = 8, reAttackRest = 20, injury = 30, strength = 50, 
		},
	},
}

