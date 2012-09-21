require	"effect"
require	"action"

name	=	"Davis"
head	=	"sprite\\sys\\davis_f.bmp"
small	=	"sprite\\sys\\davis_s.bmp"

file = {
{path	=	"media\\davis_0.png",	autoclip	=	1,	w	=	79,	h	=	79,	row	=	10,	col	=	7,	},
{path	=	"media\\davis_1.png",	autoclip	=	1,	w	=	79,	h	=	79,	row	=	10,	col	=	7,	},
{path	=	"media\\davis_2.png",	autoclip	=	1,	w	=	79,	h	=	79,	row	=	10,	col	=	4,	},
}

walking_speed	=	5.000000
walking_speedz	=	2.500000
running_speed	=	10.000000
running_speedz	=	1.600000
heavy_walking_speed	=	3.700000
heavy_walking_speedz	=	1.850000
heavy_running_speed	=	6.200000
heavy_running_speedz	=	1.000000
jump_height	=	32.599998
jump_distance	=	10.000000
jump_distancez	=	3.750000
dash_height	=	25.000000
dash_distance	=	18.000000
dash_distancez	=	5.000000
rowing_height	=	6.000000
rowing_distance	=	5.000000

frame	=	
{
	back_flip		=		{},
	ball		=		{},
	crouch		=		{},
	dash_back		=		{},
	dash_front		=		{},
	dash_kick		=		{},
	dash_punch		=		{},
	default		=		{},
	defend		=		{},
	front_flip		=		{},
	in_the_air		=		{},
	jump		=		{},
	jump_hit		=		{},
	jump_kick		=		{},
	jump_punch		=		{},
	kick		=		{},
	many_punch		=		{},
	punch		=		{},
	rolling		=		{},
	run_kick		=		{},
	run_punch		=		{},
	running		=		{},
	singlong		=		{},
	standing		=		{},
	stop_running		=		{},
	super_kick		=		{},
	super_punch		=		{},
	walking		=		{},
}

frame.back_flip[0]	=
{
	pic_id	=	0,	pic_x	=	7,	pic_y	=	7,	state	=	Action.Standing,	wait	=	4,	next	=	{"back_flip",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	40.000000,	centery	=	80.000000,	clear_key_queue	=	0,	

}

frame.back_flip[1]	=
{
	pic_id	=	0,	pic_x	=	6,	pic_y	=	7,	state	=	Action.Standing,	wait	=	12,	next	=	{"back_flip",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	

}

frame.ball[0]	=
{
	pic_id	=	2,	pic_x	=	1,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[1]	=
{
	pic_id	=	2,	pic_x	=	2,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[2]	=
{
	pic_id	=	2,	pic_x	=	3,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	3},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[3]	=
{
	pic_id	=	2,	pic_x	=	4,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	4},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[4]	=
{
	pic_id	=	2,	pic_x	=	5,	pic_y	=	1,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"ball",	5},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	30.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
newobjects	=	{	{name	=	"davis_ball",	amount	=	1,	x	=	90.000000,	y	=	-43.000000,	
facing	=	0,	frame	=	"flying",	frameID	=	0,	
hp	=	10,	dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	},},

}

frame.ball[5]	=
{
	pic_id	=	2,	pic_x	=	7,	pic_y	=	1,	state	=	Action.AfterSkill,	wait	=	2,	next	=	{"ball",	21},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"ball",	6},},

}

frame.ball[6]	=
{
	pic_id	=	2,	pic_x	=	7,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	7},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[7]	=
{
	pic_id	=	2,	pic_x	=	8,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	8},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[8]	=
{
	pic_id	=	2,	pic_x	=	9,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	9},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	33.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[9]	=
{
	pic_id	=	2,	pic_x	=	10,	pic_y	=	1,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"ball",	10},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	23.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
newobjects	=	{	{name	=	"davis_ball",	amount	=	1,	x	=	90.000000,	y	=	-43.000000,	
facing	=	0,	frame	=	"flying",	frameID	=	0,	
hp	=	10,	dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	},},

}

frame.ball[10]	=
{
	pic_id	=	2,	pic_x	=	6,	pic_y	=	1,	state	=	Action.AfterSkill,	wait	=	2,	next	=	{"ball",	21},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"ball",	11},},

}

frame.ball[11]	=
{
	pic_id	=	2,	pic_x	=	6,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	12},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[12]	=
{
	pic_id	=	2,	pic_x	=	3,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	13},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[13]	=
{
	pic_id	=	2,	pic_x	=	4,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	14},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[14]	=
{
	pic_id	=	2,	pic_x	=	5,	pic_y	=	1,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"ball",	15},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	30.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
newobjects	=	{	{name	=	"davis_ball",	amount	=	1,	x	=	90.000000,	y	=	-43.000000,	
facing	=	0,	frame	=	"flying",	frameID	=	0,	
hp	=	10,	dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	},},

}

frame.ball[15]	=
{
	pic_id	=	2,	pic_x	=	7,	pic_y	=	1,	state	=	Action.AfterSkill,	wait	=	2,	next	=	{"ball",	21},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"ball",	16},},

}

frame.ball[16]	=
{
	pic_id	=	2,	pic_x	=	1,	pic_y	=	2,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	17},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[17]	=
{
	pic_id	=	2,	pic_x	=	2,	pic_y	=	2,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	18},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	34.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[18]	=
{
	pic_id	=	2,	pic_x	=	3,	pic_y	=	2,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"ball",	19},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	26.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
newobjects	=	{	{name	=	"davis_ball",	amount	=	1,	x	=	90.000000,	y	=	-48.000000,	
facing	=	0,	frame	=	"flying",	frameID	=	0,	
hp	=	10,	dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	},},

}

frame.ball[19]	=
{
	pic_id	=	2,	pic_x	=	6,	pic_y	=	1,	state	=	Action.AfterSkill,	wait	=	2,	next	=	{"ball",	21},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"ball",	20},},

}

frame.ball[20]	=
{
	pic_id	=	2,	pic_x	=	6,	pic_y	=	1,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"ball",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.ball[21]	=
{
	pic_id	=	2,	pic_x	=	1,	pic_y	=	1,	state	=	Action.AfterSkill,	wait	=	4,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.crouch[0]	=
{
	pic_id	=	0,	pic_x	=	1,	pic_y	=	7,	state	=	Action.Crouch,	wait	=	6,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-26.000000},	{25.000000,-80.000000},	{56.000000,-80.000000},	{56.000000,-26.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"D",	"rolling",	0},},

}

frame.crouch[1]	=
{
	pic_id	=	0,	pic_x	=	1,	pic_y	=	7,	state	=	Action.Crouch,	wait	=	6,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{26.000000,-36.000000},	{26.000000,-80.000000},	{55.000000,-80.000000},	{55.000000,-36.000000},	},	zwidth	=	8.000000,	},},

}

frame.dash_back[0]	=
{
	pic_id	=	0,	pic_x	=	5,	pic_y	=	7,	state	=	Action.Dash,	wait	=	1,	next	=	{"dash_back",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{20.000000,-5.000000},	{20.000000,-43.000000},	{47.000000,-43.000000},	{47.000000,-5.000000},	},	zwidth	=	8.000000,	},{kind	=	0,	points	=	{{16.000000,-37.000000},	{16.000000,-59.000000},	{52.000000,-59.000000},	{52.000000,-37.000000},	},	zwidth	=	8.000000,	},},

}

frame.dash_back[1]	=
{
	pic_id	=	0,	pic_x	=	5,	pic_y	=	7,	state	=	Action.Dash,	wait	=	15,	next	=	{"dash_back",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{20.000000,-5.000000},	{20.000000,-43.000000},	{47.000000,-43.000000},	{47.000000,-5.000000},	},	zwidth	=	8.000000,	},{kind	=	0,	points	=	{{16.000000,-37.000000},	{16.000000,-59.000000},	{52.000000,-59.000000},	{52.000000,-37.000000},	},	zwidth	=	8.000000,	},},

}

frame.dash_back[2]	=
{
	pic_id	=	1,	pic_x	=	4,	pic_y	=	5,	state	=	Action.Dash,	wait	=	4,	next	=	{"dash_back",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{18.000000,-13.000000},	{18.000000,-64.000000},	{47.000000,-64.000000},	{47.000000,-13.000000},	},	zwidth	=	8.000000,	},},

}

frame.dash_front[0]	=
{
	pic_id	=	0,	pic_x	=	4,	pic_y	=	7,	state	=	Action.Dash,	wait	=	1,	next	=	{"dash_front",	1},	
dvx	=	18.000000,	dvy	=	25.000000,	dvz	=	5.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{43.000000,-5.000000},	{43.000000,-38.000000},	{66.000000,-38.000000},	{66.000000,-5.000000},	},	zwidth	=	8.000000,	},{kind	=	0,	points	=	{{28.000000,-29.000000},	{28.000000,-62.000000},	{49.000000,-62.000000},	{49.000000,-29.000000},	},	zwidth	=	8.000000,	},{kind	=	0,	points	=	{{18.000000,-48.000000},	{18.000000,-69.000000},	{45.000000,-69.000000},	{45.000000,-48.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"B",	"dash_kick",	0},},

}

frame.dash_front[1]	=
{
	pic_id	=	0,	pic_x	=	4,	pic_y	=	7,	state	=	Action.Dash,	wait	=	15,	next	=	{"dash_front",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{43.000000,-5.000000},	{43.000000,-38.000000},	{66.000000,-38.000000},	{66.000000,-5.000000},	},	zwidth	=	8.000000,	},{kind	=	0,	points	=	{{28.000000,-29.000000},	{28.000000,-62.000000},	{49.000000,-62.000000},	{49.000000,-29.000000},	},	zwidth	=	8.000000,	},{kind	=	0,	points	=	{{18.000000,-48.000000},	{18.000000,-69.000000},	{45.000000,-69.000000},	{45.000000,-48.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"B",	"dash_kick",	0},},

}

frame.dash_front[2]	=
{
	pic_id	=	1,	pic_x	=	3,	pic_y	=	5,	state	=	Action.Dash,	wait	=	4,	next	=	{"dash_front",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	78.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{35.000000,-8.000000},	{35.000000,-35.000000},	{62.000000,-35.000000},	{62.000000,-8.000000},	},	zwidth	=	8.000000,	},{kind	=	0,	points	=	{{16.000000,-30.000000},	{16.000000,-67.000000},	{55.000000,-67.000000},	{55.000000,-30.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"B",	"dash_kick",	0},},

}

frame.dash_kick[0]	=
{
	pic_id	=	1,	pic_x	=	3,	pic_y	=	7,	state	=	Action.BeforeDashAttack,	wait	=	2,	next	=	{"dash_kick",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	36.000000,	centery	=	75.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{18.000000,-10.000000},	{18.000000,-67.000000},	{53.000000,-67.000000},	{53.000000,-10.000000},	},	zwidth	=	8.000000,	},},

}

frame.dash_kick[1]	=
{
	pic_id	=	1,	pic_x	=	4,	pic_y	=	7,	state	=	Action.BeforeDashAttack,	wait	=	2,	next	=	{"dash_kick",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	74.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{22.000000,-9.000000},	{22.000000,-65.000000},	{57.000000,-65.000000},	{57.000000,-9.000000},	},	zwidth	=	8.000000,	},},

}

frame.dash_kick[2]	=
{
	pic_id	=	1,	pic_x	=	5,	pic_y	=	7,	state	=	Action.BeforeDashAttack,	wait	=	2,	next	=	{"dash_kick",	3},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	35.000000,	centery	=	75.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{24.000000,-6.000000},	{24.000000,-66.000000},	{53.000000,-66.000000},	{53.000000,-6.000000},	},	zwidth	=	8.000000,	},},

}

frame.dash_kick[3]	=
{
	pic_id	=	1,	pic_x	=	6,	pic_y	=	7,	state	=	Action.DashAttacking,	wait	=	14,	next	=	{"dash_kick",	4},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	25.000000,	centery	=	70.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{11.000000,-2.000000},	{11.000000,-65.000000},	{40.000000,-65.000000},	{40.000000,-2.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{17.000000,-37.000000},	{17.000000,-54.000000},	{69.000000,-54.000000},	{69.000000,-37.000000},	},	zwidth	=	8.000000,	
dvx	=	14.000000,	dvy	=	15.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	80,	strength	=	50,	},},

}

frame.dash_kick[4]	=
{
	pic_id	=	1,	pic_x	=	7,	pic_y	=	7,	state	=	Action.DashAttacking,	wait	=	2,	next	=	{"dash_kick",	5},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	25.000000,	centery	=	71.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{11.000000,-5.000000},	{11.000000,-68.000000},	{39.000000,-68.000000},	{39.000000,-5.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{32.000000,-40.000000},	{32.000000,-56.000000},	{68.000000,-56.000000},	{68.000000,-40.000000},	},	zwidth	=	8.000000,	
dvx	=	14.000000,	dvy	=	15.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	80,	strength	=	50,	},},

}

frame.dash_kick[5]	=
{
	pic_id	=	1,	pic_x	=	8,	pic_y	=	7,	state	=	Action.AfterDashAttack,	wait	=	2,	next	=	{"dash_kick",	5},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	33.000000,	centery	=	72.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-6.000000},	{21.000000,-64.000000},	{50.000000,-64.000000},	{50.000000,-6.000000},	},	zwidth	=	8.000000,	},},

}

frame.default[0]	=
{
	pic_id	=	0,	pic_x	=	1,	pic_y	=	1,	state	=	Action.Standing,	wait	=	30,	next	=	{"standing",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-60.000000},	{24.000000,-77.000000},	{54.000000,-76.000000},	{48.000000,-59.000000},	{54.000000,-57.000000},	{50.000000,-37.000000},	{45.000000,-33.000000},	{49.000000,-19.000000},	{33.000000,-16.000000},	{25.000000,-20.000000},	{28.000000,-32.000000},	{20.000000,-39.000000},	{18.000000,-57.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.defend[0]	=
{
	pic_id	=	0,	pic_x	=	7,	pic_y	=	6,	state	=	Action.Defend,	wait	=	24,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{20.000000,-19.000000},	{20.000000,-79.000000},	{58.000000,-79.000000},	{58.000000,-19.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.defend[1]	=
{
	pic_id	=	0,	pic_x	=	7,	pic_y	=	6,	state	=	Action.Defend,	wait	=	1,	next	=	{"defend",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	40.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{16.000000,-19.000000},	{16.000000,-79.000000},	{58.000000,-79.000000},	{58.000000,-19.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.front_flip[0]	=
{
	pic_id	=	1,	pic_x	=	8,	pic_y	=	5,	state	=	Action.Standing,	wait	=	6,	next	=	{"front_flip",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	42.000000,	centery	=	72.000000,	clear_key_queue	=	0,	

}

frame.front_flip[1]	=
{
	pic_id	=	1,	pic_x	=	9,	pic_y	=	5,	state	=	Action.Standing,	wait	=	12,	next	=	{"front_flip",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	

}

frame.in_the_air[0]	=
{
	pic_id	=	0,	pic_x	=	3,	pic_y	=	7,	state	=	Action.InTheAir,	wait	=	2,	next	=	{"in_the_air",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{20.000000,-11.000000},	{20.000000,-72.000000},	{49.000000,-72.000000},	{49.000000,-11.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"B",	"jump_kick",	0},},

}

frame.jump[0]	=
{
	pic_id	=	0,	pic_x	=	1,	pic_y	=	7,	state	=	Action.Crouch,	wait	=	2,	next	=	{"jump",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{22.000000,-24.000000},	{22.000000,-82.000000},	{57.000000,-82.000000},	{57.000000,-24.000000},	},	zwidth	=	8.000000,	},},

}

frame.jump[1]	=
{
	pic_id	=	0,	pic_x	=	2,	pic_y	=	7,	state	=	Action.Jump,	wait	=	2,	next	=	{"jump",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{26.000000,-26.000000},	{26.000000,-82.000000},	{60.000000,-82.000000},	{60.000000,-26.000000},	},	zwidth	=	8.000000,	},},

}

frame.jump[2]	=
{
	pic_id	=	0,	pic_x	=	3,	pic_y	=	7,	state	=	Action.Jump,	wait	=	2,	next	=	{"in_the_air",	0},	
dvx	=	10.000000,	dvy	=	32.599998,	dvz	=	3.750000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{20.000000,-11.000000},	{20.000000,-72.000000},	{49.000000,-72.000000},	{49.000000,-11.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"B",	"jump_kick",	0},},

}

frame.jump_hit[0]	=
{
	pic_id	=	2,	pic_x	=	1,	pic_y	=	3,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"jump_hit",	1},	
dvx	=	8.000000,	dvy	=	32.000000,	dvz	=	0.000000,	centerx	=	32.000000,	centery	=	75.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{13.000000,-8.000000},	{13.000000,-69.000000},	{51.000000,-69.000000},	{51.000000,-8.000000},	},	zwidth	=	8.000000,	},},

}

frame.jump_hit[1]	=
{
	pic_id	=	2,	pic_x	=	2,	pic_y	=	3,	state	=	Action.BeforeSkill,	wait	=	4,	next	=	{"jump_hit",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	31.000000,	centery	=	75.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{15.000000,-8.000000},	{15.000000,-70.000000},	{49.000000,-70.000000},	{49.000000,-8.000000},	},	zwidth	=	8.000000,	},},

}

frame.jump_hit[2]	=
{
	pic_id	=	2,	pic_x	=	2,	pic_y	=	3,	state	=	Action.BeforeSkill,	wait	=	30,	next	=	{"jump_hit",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	37.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-8.000000},	{21.000000,-74.000000},	{55.000000,-74.000000},	{55.000000,-8.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"jump_hit",	3},},

}

frame.jump_hit[3]	=
{
	pic_id	=	2,	pic_x	=	3,	pic_y	=	3,	state	=	Action.GroundSkill,	wait	=	6,	next	=	{"jump_hit",	4},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	26.000000,	centery	=	72.000000,	clear_key_queue	=	1,	
body	=	{	{kind	=	0,	points	=	{{16.000000,-20.000000},	{16.000000,-66.000000},	{62.000000,-66.000000},	{62.000000,-20.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{17.000000,-19.000000},	{17.000000,-64.000000},	{62.000000,-64.000000},	{62.000000,-19.000000},	},	zwidth	=	8.000000,	
dvx	=	22.000000,	dvy	=	-15.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	50,	strength	=	50,	},},

}

frame.jump_hit[4]	=
{
	pic_id	=	2,	pic_x	=	4,	pic_y	=	3,	state	=	Action.AfterSkill,	wait	=	30,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	26.000000,	centery	=	72.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{16.000000,-20.000000},	{16.000000,-66.000000},	{62.000000,-66.000000},	{62.000000,-20.000000},	},	zwidth	=	8.000000,	},},

}

frame.jump_kick[0]	=
{
	pic_id	=	1,	pic_x	=	3,	pic_y	=	7,	state	=	Action.BeforeJumpAttack,	wait	=	2,	next	=	{"jump_kick",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	36.000000,	centery	=	75.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{18.000000,-10.000000},	{18.000000,-67.000000},	{53.000000,-67.000000},	{53.000000,-10.000000},	},	zwidth	=	8.000000,	},},

}

frame.jump_kick[1]	=
{
	pic_id	=	1,	pic_x	=	4,	pic_y	=	7,	state	=	Action.BeforeJumpAttack,	wait	=	2,	next	=	{"jump_kick",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	74.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{22.000000,-9.000000},	{22.000000,-65.000000},	{57.000000,-65.000000},	{57.000000,-9.000000},	},	zwidth	=	8.000000,	},},

}

frame.jump_kick[2]	=
{
	pic_id	=	1,	pic_x	=	5,	pic_y	=	7,	state	=	Action.BeforeJumpAttack,	wait	=	2,	next	=	{"jump_kick",	3},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	35.000000,	centery	=	75.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{24.000000,-6.000000},	{24.000000,-66.000000},	{53.000000,-66.000000},	{53.000000,-6.000000},	},	zwidth	=	8.000000,	},},

}

frame.jump_kick[3]	=
{
	pic_id	=	1,	pic_x	=	6,	pic_y	=	7,	state	=	Action.JumpAttacking,	wait	=	6,	next	=	{"jump_kick",	4},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	25.000000,	centery	=	70.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{18.000000,-10.000000},	{18.000000,-67.000000},	{53.000000,-67.000000},	{53.000000,-10.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{17.000000,-37.000000},	{17.000000,-54.000000},	{69.000000,-54.000000},	{69.000000,-37.000000},	},	zwidth	=	8.000000,	
dvx	=	9.000000,	dvy	=	15.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	60,	strength	=	50,	},},

}

frame.jump_kick[4]	=
{
	pic_id	=	1,	pic_x	=	7,	pic_y	=	7,	state	=	Action.JumpAttacking,	wait	=	2,	next	=	{"jump_kick",	5},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	25.000000,	centery	=	71.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{11.000000,-5.000000},	{11.000000,-68.000000},	{39.000000,-68.000000},	{39.000000,-5.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{32.000000,-40.000000},	{32.000000,-56.000000},	{68.000000,-56.000000},	{68.000000,-40.000000},	},	zwidth	=	8.000000,	
dvx	=	9.000000,	dvy	=	15.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	60,	strength	=	50,	},},

}

frame.jump_kick[5]	=
{
	pic_id	=	1,	pic_x	=	8,	pic_y	=	7,	state	=	Action.AfterJumpAttack,	wait	=	6,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	33.000000,	centery	=	72.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-6.000000},	{21.000000,-64.000000},	{50.000000,-64.000000},	{50.000000,-6.000000},	},	zwidth	=	8.000000,	},},

}

frame.kick[0]	=
{
	pic_id	=	0,	pic_x	=	5,	pic_y	=	2,	state	=	Action.BeforeAttack,	wait	=	2,	next	=	{"kick",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	42.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{26.000000,-12.000000},	{26.000000,-80.000000},	{53.000000,-80.000000},	{53.000000,-12.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	2,effect	=	Effect.End,
points	=	{{25.000000,-58.000000},	{25.000000,-79.000000},	{62.000000,-79.000000},	{62.000000,-58.000000},	},	zwidth	=	8.000000,	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	0,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},

}

frame.kick[1]	=
{
	pic_id	=	0,	pic_x	=	6,	pic_y	=	2,	state	=	Action.Attacking,	wait	=	2,	next	=	{"kick",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	24.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{13.000000,-11.000000},	{13.000000,-78.000000},	{45.000000,-78.000000},	{45.000000,-11.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{23.000000,-38.000000},	{23.000000,-53.000000},	{64.000000,-53.000000},	{64.000000,-38.000000},	},	zwidth	=	8.000000,	
dvx	=	2.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	0,	breakDefend	=	-858993460,	
injury	=	20,	strength	=	50,	},},

}

frame.kick[2]	=
{
	pic_id	=	0,	pic_x	=	7,	pic_y	=	2,	state	=	Action.AfterAttack,	wait	=	2,	next	=	{"kick",	3},	
dvx	=	2.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	28.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{17.000000,-15.000000},	{17.000000,-79.000000},	{54.000000,-79.000000},	{54.000000,-15.000000},	},	zwidth	=	8.000000,	},},

}

frame.kick[3]	=
{
	pic_id	=	0,	pic_x	=	8,	pic_y	=	2,	state	=	Action.AfterAttack,	wait	=	2,	next	=	{"default",	0},	
dvx	=	2.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	41.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{28.000000,-9.000000},	{28.000000,-81.000000},	{60.000000,-81.000000},	{60.000000,-9.000000},	},	zwidth	=	8.000000,	},},

}

frame.many_punch[0]	=
{
	pic_id	=	2,	pic_x	=	4,	pic_y	=	2,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"many_punch",	1},	
dvx	=	7.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	37.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},

}

frame.many_punch[1]	=
{
	pic_id	=	2,	pic_x	=	5,	pic_y	=	2,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	2},	
dvx	=	5.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	33.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{63.000000,-9.000000},	{63.000000,-76.000000},	{79.000000,-76.000000},	{79.000000,-9.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},{kind	=	0,effect	=	Effect.Punch,
points	=	{{17.000000,-35.000000},	{17.000000,-48.000000},	{78.000000,-48.000000},	{78.000000,-35.000000},	},	zwidth	=	8.000000,	
dvx	=	7.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	1,	breakDefend	=	-858993460,	
injury	=	25,	strength	=	50,	},},

}

frame.many_punch[2]	=
{
	pic_id	=	2,	pic_x	=	6,	pic_y	=	2,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	3},	
dvx	=	3.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	38.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{49.000000,-9.000000},	{49.000000,-73.000000},	{67.000000,-73.000000},	{67.000000,-9.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},},

}

frame.many_punch[3]	=
{
	pic_id	=	2,	pic_x	=	7,	pic_y	=	2,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	4},	
dvx	=	3.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	32.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{57.000000,-9.000000},	{57.000000,-76.000000},	{75.000000,-76.000000},	{75.000000,-9.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},{kind	=	0,effect	=	Effect.Punch,
points	=	{{14.000000,-35.000000},	{14.000000,-53.000000},	{72.000000,-53.000000},	{72.000000,-35.000000},	},	zwidth	=	8.000000,	
dvx	=	7.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	1,	breakDefend	=	-858993460,	
injury	=	25,	strength	=	50,	},},

}

frame.many_punch[4]	=
{
	pic_id	=	2,	pic_x	=	8,	pic_y	=	2,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	5},	
dvx	=	3.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	24.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{49.000000,-9.000000},	{49.000000,-73.000000},	{67.000000,-73.000000},	{67.000000,-9.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},},

}

frame.many_punch[5]	=
{
	pic_id	=	2,	pic_x	=	9,	pic_y	=	2,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	6},	
dvx	=	5.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	24.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{49.000000,-9.000000},	{49.000000,-73.000000},	{67.000000,-73.000000},	{67.000000,-9.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},},

}

frame.many_punch[6]	=
{
	pic_id	=	2,	pic_x	=	10,	pic_y	=	2,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	7},	
dvx	=	5.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	22.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{64.000000,-10.000000},	{64.000000,-78.000000},	{82.000000,-78.000000},	{82.000000,-10.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},{kind	=	0,effect	=	Effect.Punch,
points	=	{{-1.000000,-22.000000},	{-1.000000,-47.000000},	{80.000000,-47.000000},	{80.000000,-22.000000},	},	zwidth	=	8.000000,	
dvx	=	10.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	1,	breakDefend	=	-858993460,	
injury	=	25,	strength	=	50,	},},

}

frame.many_punch[7]	=
{
	pic_id	=	2,	pic_x	=	10,	pic_y	=	3,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	8},	
dvx	=	3.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	18.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{49.000000,-9.000000},	{49.000000,-73.000000},	{67.000000,-73.000000},	{67.000000,-9.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},},

}

frame.many_punch[8]	=
{
	pic_id	=	2,	pic_x	=	9,	pic_y	=	3,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	9},	
dvx	=	5.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	22.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{49.000000,-9.000000},	{49.000000,-73.000000},	{67.000000,-73.000000},	{67.000000,-9.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},},
hit	=	{	{"D^A",	"singlong",	0},},

}

frame.many_punch[9]	=
{
	pic_id	=	2,	pic_x	=	8,	pic_y	=	3,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	10},	
dvx	=	7.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	26.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{49.000000,-9.000000},	{49.000000,-73.000000},	{67.000000,-73.000000},	{67.000000,-9.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},},
hit	=	{	{"D^A",	"singlong",	0},},

}

frame.many_punch[10]	=
{
	pic_id	=	2,	pic_x	=	7,	pic_y	=	3,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"many_punch",	11},	
dvx	=	3.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	22.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{10.000000,-2.000000},	{10.000000,-70.000000},	{85.000000,-70.000000},	{85.000000,-2.000000},	},	zwidth	=	8.000000,	
dvx	=	12.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	45,	strength	=	50,	},{kind	=	0,effect	=	Effect.Punch,
points	=	{{12.000000,-11.000000},	{12.000000,-62.000000},	{82.000000,-62.000000},	{82.000000,-11.000000},	},	zwidth	=	8.000000,	
dvx	=	7.000000,	dvy	=	15.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	25,	strength	=	50,	},},

}

frame.many_punch[11]	=
{
	pic_id	=	2,	pic_x	=	6,	pic_y	=	3,	state	=	Action.AfterSkill,	wait	=	4,	next	=	{"many_punch",	12},	
dvx	=	3.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	27.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"J",	"jump_hit",	0},},

}

frame.many_punch[12]	=
{
	pic_id	=	2,	pic_x	=	5,	pic_y	=	3,	state	=	Action.AfterSkill,	wait	=	6,	next	=	{"default",	0},	
dvx	=	3.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	34.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{21.000000,-18.000000},	{21.000000,-80.000000},	{64.000000,-80.000000},	{64.000000,-18.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"J",	"jump_hit",	0},},

}

frame.punch[0]	=
{
	pic_id	=	0,	pic_x	=	1,	pic_y	=	2,	state	=	Action.BeforeAttack,	wait	=	2,	next	=	{"punch",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	42.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{28.000000,-12.000000},	{28.000000,-82.000000},	{61.000000,-82.000000},	{61.000000,-12.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	2,effect	=	Effect.End,
points	=	{{27.000000,-57.000000},	{27.000000,-82.000000},	{63.000000,-82.000000},	{63.000000,-57.000000},	},	zwidth	=	8.000000,	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	0,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},

}

frame.punch[1]	=
{
	pic_id	=	0,	pic_x	=	2,	pic_y	=	2,	state	=	Action.Attacking,	wait	=	2,	next	=	{"punch",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	23.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{13.000000,-11.000000},	{13.000000,-82.000000},	{61.000000,-82.000000},	{61.000000,-11.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{21.000000,-31.000000},	{21.000000,-49.000000},	{64.000000,-49.000000},	{64.000000,-31.000000},	},	zwidth	=	8.000000,	
dvx	=	2.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	0,	breakDefend	=	-858993460,	
injury	=	20,	strength	=	50,	},},

}

frame.punch[2]	=
{
	pic_id	=	0,	pic_x	=	3,	pic_y	=	2,	state	=	Action.AfterAttack,	wait	=	2,	next	=	{"punch",	3},	
dvx	=	2.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	28.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{17.000000,-9.000000},	{17.000000,-81.000000},	{48.000000,-81.000000},	{48.000000,-9.000000},	},	zwidth	=	8.000000,	},},

}

frame.punch[3]	=
{
	pic_id	=	0,	pic_x	=	4,	pic_y	=	2,	state	=	Action.AfterAttack,	wait	=	2,	next	=	{"default",	0},	
dvx	=	2.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	41.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{29.000000,-10.000000},	{29.000000,-80.000000},	{61.000000,-80.000000},	{61.000000,-10.000000},	},	zwidth	=	8.000000,	},},

}

frame.rolling[0]	=
{
	pic_id	=	0,	pic_x	=	9,	pic_y	=	6,	state	=	Action.Rolling,	wait	=	4,	next	=	{"rolling",	1},	
dvx	=	10.000000,	dvy	=	0.000000,	dvz	=	5.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
attack	=	{
{kind	=	7,effect	=	Effect.End,
points	=	{{36.000000,-54.000000},	{36.000000,-79.000000},	{49.000000,-79.000000},	{49.000000,-54.000000},	},	zwidth	=	8.000000,	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	0,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},
hit	=	{	{"D^A",	"singlong",	0},{"D^J",	"jump_hit",	0},},

}

frame.rolling[1]	=
{
	pic_id	=	0,	pic_x	=	10,	pic_y	=	6,	state	=	Action.Rolling,	wait	=	4,	next	=	{"rolling",	2},	
dvx	=	5.000000,	dvy	=	0.000000,	dvz	=	5.000000,	centerx	=	34.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
attack	=	{
{kind	=	7,effect	=	Effect.End,
points	=	{{36.000000,-54.000000},	{36.000000,-79.000000},	{49.000000,-79.000000},	{49.000000,-54.000000},	},	zwidth	=	8.000000,	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	0,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},
hit	=	{	{"D^A",	"singlong",	0},{"D^J",	"jump_hit",	0},},

}

frame.rolling[2]	=
{
	pic_id	=	0,	pic_x	=	10,	pic_y	=	7,	state	=	Action.Rolling,	wait	=	4,	next	=	{"rolling",	3},	
dvx	=	3.000000,	dvy	=	0.000000,	dvz	=	5.000000,	centerx	=	34.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
attack	=	{
{kind	=	7,effect	=	Effect.End,
points	=	{{36.000000,-54.000000},	{36.000000,-79.000000},	{49.000000,-79.000000},	{49.000000,-54.000000},	},	zwidth	=	8.000000,	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	0,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},
hit	=	{	{"D^A",	"singlong",	0},{"D^J",	"jump_hit",	0},},

}

frame.rolling[3]	=
{
	pic_id	=	0,	pic_x	=	9,	pic_y	=	6,	state	=	Action.Rolling,	wait	=	4,	next	=	{"crouch",	1},	
dvx	=	2.000000,	dvy	=	0.000000,	dvz	=	5.000000,	centerx	=	38.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
attack	=	{
{kind	=	7,effect	=	Effect.End,
points	=	{{36.000000,-54.000000},	{36.000000,-79.000000},	{49.000000,-79.000000},	{49.000000,-54.000000},	},	zwidth	=	8.000000,	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	0,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},
hit	=	{	{"D^A",	"singlong",	0},{"D^J",	"jump_hit",	0},},

}

frame.run_punch[0]	=
{
	pic_id	=	1,	pic_x	=	1,	pic_y	=	4,	state	=	Action.BeforeRunAttack,	wait	=	4,	next	=	{"run_punch",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	35.000000,	centery	=	79.000000,	clear_key_queue	=	1,	
body	=	{	{kind	=	0,	points	=	{{17.000000,-25.000000},	{17.000000,-79.000000},	{61.000000,-79.000000},	{61.000000,-25.000000},	},	zwidth	=	8.000000,	},},

}

frame.run_punch[1]	=
{
	pic_id	=	1,	pic_x	=	2,	pic_y	=	4,	state	=	Action.BeforeRunAttack,	wait	=	2,	next	=	{"run_punch",	2},	
dvx	=	16.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	30.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-24.000000},	{25.000000,-79.000000},	{56.000000,-79.000000},	{56.000000,-24.000000},	},	zwidth	=	8.000000,	},},

}

frame.run_punch[2]	=
{
	pic_id	=	1,	pic_x	=	3,	pic_y	=	4,	state	=	Action.RunAttacking,	wait	=	2,	next	=	{"run_punch",	3},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	25.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{15.000000,-19.000000},	{15.000000,-81.000000},	{52.000000,-81.000000},	{52.000000,-19.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{-18.000000,-24.000000},	{-18.000000,-54.000000},	{70.000000,-54.000000},	{70.000000,-24.000000},	},	zwidth	=	8.000000,	
dvx	=	20.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	55,	strength	=	50,	},},
hit	=	{	{"A",	"run_punch",	4},},

}

frame.run_punch[3]	=
{
	pic_id	=	1,	pic_x	=	4,	pic_y	=	4,	state	=	Action.RunAttacking,	wait	=	6,	next	=	{"run_punch",	4},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	20.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{14.000000,-14.000000},	{14.000000,-81.000000},	{57.000000,-81.000000},	{57.000000,-14.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{28.000000,-25.000000},	{28.000000,-52.000000},	{71.000000,-52.000000},	{71.000000,-25.000000},	},	zwidth	=	8.000000,	
dvx	=	17.000000,	dvy	=	0.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	40,	strength	=	50,	},},
hit	=	{	{"A",	"run_punch",	4},},

}

frame.run_punch[4]	=
{
	pic_id	=	1,	pic_x	=	5,	pic_y	=	4,	state	=	Action.AfterRunAttack,	wait	=	4,	next	=	{"run_punch",	5},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	20.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{18.000000,-10.000000},	{18.000000,-67.000000},	{53.000000,-67.000000},	{53.000000,-10.000000},	},	zwidth	=	8.000000,	},},

}

frame.run_punch[5]	=
{
	pic_id	=	1,	pic_x	=	6,	pic_y	=	4,	state	=	Action.AfterRunAttack,	wait	=	4,	next	=	{"run_punch",	6},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	30.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{20.000000,-11.000000},	{20.000000,-79.000000},	{51.000000,-79.000000},	{51.000000,-11.000000},	},	zwidth	=	8.000000,	},},

}

frame.run_punch[6]	=
{
	pic_id	=	1,	pic_x	=	7,	pic_y	=	4,	state	=	Action.AfterRunAttack,	wait	=	2,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	32.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{20.000000,-11.000000},	{20.000000,-79.000000},	{51.000000,-79.000000},	{51.000000,-11.000000},	},	zwidth	=	8.000000,	},},

}

frame.running[0]	=
{
	pic_id	=	0,	pic_x	=	1,	pic_y	=	3,	state	=	Action.Running,	wait	=	6,	next	=	{"running",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	36.000000,	centery	=	80.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-19.000000},	{25.000000,-79.000000},	{63.000000,-79.000000},	{63.000000,-19.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"run_punch",	0},{"J",	"dash_front",	0},{"D",	"rolling",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.running[1]	=
{
	pic_id	=	0,	pic_x	=	2,	pic_y	=	3,	state	=	Action.Running,	wait	=	6,	next	=	{"running",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	37.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-19.000000},	{25.000000,-79.000000},	{63.000000,-79.000000},	{63.000000,-19.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"run_punch",	0},{"J",	"dash_front",	0},{"D",	"rolling",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.running[2]	=
{
	pic_id	=	0,	pic_x	=	3,	pic_y	=	3,	state	=	Action.Running,	wait	=	6,	next	=	{"running",	3},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	32.000000,	centery	=	78.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-19.000000},	{25.000000,-79.000000},	{63.000000,-79.000000},	{63.000000,-19.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"run_punch",	0},{"J",	"dash_front",	0},{"D",	"rolling",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.running[3]	=
{
	pic_id	=	0,	pic_x	=	2,	pic_y	=	3,	state	=	Action.Running,	wait	=	6,	next	=	{"running",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	37.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-19.000000},	{25.000000,-79.000000},	{63.000000,-79.000000},	{63.000000,-19.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"run_punch",	0},{"J",	"dash_front",	0},{"D",	"rolling",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.singlong[0]	=
{
	pic_id	=	2,	pic_x	=	1,	pic_y	=	4,	state	=	Action.BeforeSkill,	wait	=	2,	next	=	{"singlong",	1},	
dvx	=	7.000000,	dvy	=	36.000000,	dvz	=	0.000000,	centerx	=	30.000000,	centery	=	76.000000,	clear_key_queue	=	0,	
sound	=	"¬—f",	
}

frame.singlong[1]	=
{
	pic_id	=	2,	pic_x	=	2,	pic_y	=	4,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"singlong",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	28.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{10.000000,-3.000000},	{10.000000,-78.000000},	{82.000000,-78.000000},	{82.000000,-3.000000},	},	zwidth	=	8.000000,	
dvx	=	7.000000,	dvy	=	39.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},
sound	=	"",	
}

frame.singlong[2]	=
{
	pic_id	=	2,	pic_x	=	3,	pic_y	=	4,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"singlong",	3},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	26.000000,	centery	=	81.000000,	clear_key_queue	=	0,	
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{13.000000,1.000000},	{13.000000,-79.000000},	{80.000000,-79.000000},	{80.000000,1.000000},	},	zwidth	=	8.000000,	
dvx	=	7.000000,	dvy	=	33.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},

}

frame.singlong[3]	=
{
	pic_id	=	2,	pic_x	=	4,	pic_y	=	4,	state	=	Action.GroundSkill,	wait	=	2,	next	=	{"singlong",	4},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	26.000000,	centery	=	78.000000,	clear_key_queue	=	0,	
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{11.000000,2.000000},	{11.000000,-78.000000},	{74.000000,-78.000000},	{74.000000,2.000000},	},	zwidth	=	8.000000,	
dvx	=	7.000000,	dvy	=	27.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},

}

frame.singlong[4]	=
{
	pic_id	=	2,	pic_x	=	5,	pic_y	=	4,	state	=	Action.GroundSkill,	wait	=	4,	next	=	{"singlong",	5},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	34.000000,	centery	=	81.000000,	clear_key_queue	=	0,	
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{19.000000,-1.000000},	{19.000000,-81.000000},	{80.000000,-81.000000},	{80.000000,-1.000000},	},	zwidth	=	8.000000,	
dvx	=	7.000000,	dvy	=	21.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	0,	strength	=	0,	},},

}

frame.singlong[5]	=
{
	pic_id	=	2,	pic_x	=	6,	pic_y	=	4,	state	=	Action.AfterSkill,	wait	=	4,	next	=	{"singlong",	6},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	33.000000,	centery	=	75.000000,	clear_key_queue	=	0,	

}

frame.singlong[6]	=
{
	pic_id	=	2,	pic_x	=	7,	pic_y	=	4,	state	=	Action.AfterSkill,	wait	=	6,	next	=	{"singlong",	7},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	29.000000,	centery	=	74.000000,	clear_key_queue	=	0,	

}

frame.singlong[7]	=
{
	pic_id	=	2,	pic_x	=	8,	pic_y	=	4,	state	=	Action.AfterSkill,	wait	=	4,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	29.000000,	centery	=	73.000000,	clear_key_queue	=	0,	

}

frame.standing[0]	=
{
	pic_id	=	0,	pic_x	=	1,	pic_y	=	1,	state	=	Action.Standing,	wait	=	30,	next	=	{"standing",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-60.000000},	{24.000000,-77.000000},	{54.000000,-76.000000},	{48.000000,-59.000000},	{54.000000,-57.000000},	{50.000000,-37.000000},	{45.000000,-33.000000},	{49.000000,-19.000000},	{33.000000,-16.000000},	{25.000000,-20.000000},	{28.000000,-32.000000},	{20.000000,-39.000000},	{18.000000,-57.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.standing[1]	=
{
	pic_id	=	0,	pic_x	=	2,	pic_y	=	1,	state	=	Action.Standing,	wait	=	30,	next	=	{"standing",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-60.000000},	{24.000000,-77.000000},	{54.000000,-76.000000},	{48.000000,-59.000000},	{54.000000,-57.000000},	{50.000000,-37.000000},	{45.000000,-33.000000},	{49.000000,-19.000000},	{33.000000,-16.000000},	{25.000000,-20.000000},	{28.000000,-32.000000},	{20.000000,-39.000000},	{18.000000,-57.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.standing[2]	=
{
	pic_id	=	0,	pic_x	=	3,	pic_y	=	1,	state	=	Action.Standing,	wait	=	30,	next	=	{"standing",	3},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-60.000000},	{24.000000,-77.000000},	{54.000000,-76.000000},	{48.000000,-59.000000},	{54.000000,-57.000000},	{50.000000,-37.000000},	{45.000000,-33.000000},	{49.000000,-19.000000},	{33.000000,-16.000000},	{25.000000,-20.000000},	{28.000000,-32.000000},	{20.000000,-39.000000},	{18.000000,-57.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.standing[3]	=
{
	pic_id	=	0,	pic_x	=	4,	pic_y	=	1,	state	=	Action.Standing,	wait	=	30,	next	=	{"standing",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-60.000000},	{24.000000,-77.000000},	{54.000000,-76.000000},	{48.000000,-59.000000},	{54.000000,-57.000000},	{50.000000,-37.000000},	{45.000000,-33.000000},	{49.000000,-19.000000},	{33.000000,-16.000000},	{25.000000,-20.000000},	{28.000000,-32.000000},	{20.000000,-39.000000},	{18.000000,-57.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},

}

frame.stop_running[0]	=
{
	pic_id	=	1,	pic_x	=	5,	pic_y	=	5,	state	=	Action.StopRunning,	wait	=	30,	next	=	{"default",	0},	
dvx	=	1.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{17.000000,-25.000000},	{17.000000,-80.000000},	{47.000000,-80.000000},	{61.000000,-79.000000},	{61.000000,-47.000000},	{47.000000,-25.000000},	},	zwidth	=	8.000000,	},},

}

frame.super_punch[0]	=
{
	pic_id	=	0,	pic_x	=	8,	pic_y	=	7,	state	=	Action.BeforeSuperAttack,	wait	=	4,	next	=	{"super_punch",	1},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	32.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{25.000000,-16.000000},	{25.000000,-77.000000},	{55.000000,-77.000000},	{55.000000,-16.000000},	},	zwidth	=	8.000000,	},},

}

frame.super_punch[1]	=
{
	pic_id	=	0,	pic_x	=	9,	pic_y	=	7,	state	=	Action.BeforeSuperAttack,	wait	=	2,	next	=	{"super_punch",	2},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	23.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{20.000000,-14.000000},	{20.000000,-80.000000},	{54.000000,-80.000000},	{54.000000,-14.000000},	},	zwidth	=	8.000000,	},},

}

frame.super_punch[2]	=
{
	pic_id	=	0,	pic_x	=	9,	pic_y	=	1,	state	=	Action.SuperAttacking,	wait	=	4,	next	=	{"super_punch",	3},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	28.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{26.000000,-12.000000},	{26.000000,-78.000000},	{61.000000,-78.000000},	{61.000000,-12.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{40.000000,-5.000000},	{40.000000,-50.000000},	{75.000000,-50.000000},	{75.000000,-5.000000},	},	zwidth	=	8.000000,	
dvx	=	3.000000,	dvy	=	30.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	40,	strength	=	50,	},},

}

frame.super_punch[3]	=
{
	pic_id	=	0,	pic_x	=	10,	pic_y	=	1,	state	=	Action.AfterSuperAttack,	wait	=	2,	next	=	{"super_punch",	4},	
dvx	=	5.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	27.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{23.000000,-10.000000},	{23.000000,-79.000000},	{52.000000,-79.000000},	{52.000000,-10.000000},	},	zwidth	=	8.000000,	},},

}

frame.super_punch[4]	=
{
	pic_id	=	0,	pic_x	=	10,	pic_y	=	2,	state	=	Action.BeforeSuperAttack,	wait	=	4,	next	=	{"super_punch",	5},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	28.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{18.000000,-15.000000},	{18.000000,-80.000000},	{59.000000,-80.000000},	{59.000000,-15.000000},	},	zwidth	=	8.000000,	},},

}

frame.super_punch[5]	=
{
	pic_id	=	0,	pic_x	=	10,	pic_y	=	3,	state	=	Action.BeforeSuperAttack,	wait	=	2,	next	=	{"super_punch",	6},	
dvx	=	6.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	32.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{24.000000,-10.000000},	{24.000000,-80.000000},	{58.000000,-80.000000},	{58.000000,-10.000000},	},	zwidth	=	8.000000,	},},

}

frame.super_punch[6]	=
{
	pic_id	=	0,	pic_x	=	10,	pic_y	=	4,	state	=	Action.SuperAttacking,	wait	=	4,	next	=	{"super_punch",	7},	
dvx	=	1.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	38.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{29.000000,-6.000000},	{29.000000,-78.000000},	{52.000000,-78.000000},	{52.000000,-6.000000},	},	zwidth	=	8.000000,	},},
attack	=	{
{kind	=	0,effect	=	Effect.Punch,
points	=	{{40.000000,-4.000000},	{40.000000,-48.000000},	{72.000000,-48.000000},	{72.000000,-4.000000},	},	zwidth	=	8.000000,	
dvx	=	7.000000,	dvy	=	39.000000,	dvz	=	0.000000,	fall	=	70,	breakDefend	=	-858993460,	
injury	=	40,	strength	=	50,	},},

}

frame.super_punch[7]	=
{
	pic_id	=	0,	pic_x	=	10,	pic_y	=	5,	state	=	Action.AfterSuperAttack,	wait	=	4,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	33.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{22.000000,-13.000000},	{22.000000,-81.000000},	{56.000000,-81.000000},	{56.000000,-13.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"J",	"jump_hit",	0},},

}

frame.walking[0]	=
{
	pic_id	=	0,	pic_x	=	5,	pic_y	=	1,	state	=	Action.Walking,	wait	=	6,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{48.000000,-58.000000},	{55.000000,-56.000000},	{51.000000,-39.000000},	{46.000000,-35.000000},	{49.000000,-22.000000},	{43.000000,-14.000000},	{28.000000,-15.000000},	{26.000000,-30.000000},	{20.000000,-36.000000},	{17.000000,-53.000000},	{24.000000,-56.000000},	{29.000000,-50.000000},	{32.000000,-75.000000},	{44.000000,-75.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},
catch	=	{
{kind	=	0,	strong	=	0,	catchx	=	0.000000,	catchy	=	0.000000,	where	=	Body.Neck,	points	=	{{40.000000,-16.000000},	{40.000000,-81.000000},	{65.000000,-81.000000},	{65.000000,-16.000000},	},	
},},

}

frame.walking[1]	=
{
	pic_id	=	0,	pic_x	=	6,	pic_y	=	1,	state	=	Action.Walking,	wait	=	6,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	78.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{48.000000,-58.000000},	{52.000000,-55.000000},	{51.000000,-39.000000},	{46.000000,-35.000000},	{49.000000,-22.000000},	{43.000000,-14.000000},	{27.000000,-19.000000},	{29.000000,-32.000000},	{21.000000,-39.000000},	{20.000000,-56.000000},	{26.000000,-61.000000},	{29.000000,-55.000000},	{32.000000,-75.000000},	{44.000000,-76.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},
catch	=	{
{kind	=	0,	strong	=	0,	catchx	=	0.000000,	catchy	=	0.000000,	where	=	Body.Neck,	points	=	{{40.000000,-16.000000},	{40.000000,-81.000000},	{65.000000,-81.000000},	{65.000000,-16.000000},	},	
},},

}

frame.walking[2]	=
{
	pic_id	=	0,	pic_x	=	7,	pic_y	=	1,	state	=	Action.Walking,	wait	=	6,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{48.000000,-58.000000},	{49.000000,-49.000000},	{51.000000,-39.000000},	{46.000000,-35.000000},	{48.000000,-23.000000},	{43.000000,-14.000000},	{25.000000,-18.000000},	{29.000000,-32.000000},	{25.000000,-36.000000},	{23.000000,-43.000000},	{26.000000,-50.000000},	{29.000000,-56.000000},	{26.000000,-76.000000},	{50.000000,-78.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},
catch	=	{
{kind	=	0,	strong	=	0,	catchx	=	0.000000,	catchy	=	0.000000,	where	=	Body.Neck,	points	=	{{40.000000,-16.000000},	{40.000000,-81.000000},	{65.000000,-81.000000},	{65.000000,-16.000000},	},	
},},

}

frame.walking[3]	=
{
	pic_id	=	0,	pic_x	=	8,	pic_y	=	1,	state	=	Action.Walking,	wait	=	6,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	78.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{48.000000,-58.000000},	{48.000000,-49.000000},	{51.000000,-39.000000},	{46.000000,-35.000000},	{49.000000,-22.000000},	{43.000000,-14.000000},	{28.000000,-15.000000},	{22.000000,-39.000000},	{28.000000,-52.000000},	{23.000000,-74.000000},	{33.000000,-78.000000},	{40.000000,-65.000000},	{44.000000,-78.000000},	{55.000000,-76.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},
catch	=	{
{kind	=	0,	strong	=	0,	catchx	=	0.000000,	catchy	=	0.000000,	where	=	Body.Neck,	points	=	{{40.000000,-16.000000},	{40.000000,-81.000000},	{65.000000,-81.000000},	{65.000000,-16.000000},	},	
},},

}

frame.walking[4]	=
{
	pic_id	=	0,	pic_x	=	7,	pic_y	=	1,	state	=	Action.Walking,	wait	=	6,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	77.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{48.000000,-58.000000},	{49.000000,-50.000000},	{51.000000,-39.000000},	{46.000000,-35.000000},	{49.000000,-22.000000},	{43.000000,-14.000000},	{28.000000,-16.000000},	{26.000000,-25.000000},	{30.000000,-32.000000},	{23.000000,-39.000000},	{23.000000,-46.000000},	{29.000000,-50.000000},	{26.000000,-77.000000},	{52.000000,-77.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},
catch	=	{
{kind	=	0,	strong	=	0,	catchx	=	0.000000,	catchy	=	0.000000,	where	=	Body.Neck,	points	=	{{40.000000,-16.000000},	{40.000000,-81.000000},	{65.000000,-81.000000},	{65.000000,-16.000000},	},	
},},

}

frame.walking[5]	=
{
	pic_id	=	0,	pic_x	=	6,	pic_y	=	1,	state	=	Action.Walking,	wait	=	6,	next	=	{"default",	0},	
dvx	=	0.000000,	dvy	=	0.000000,	dvz	=	0.000000,	centerx	=	39.000000,	centery	=	79.000000,	clear_key_queue	=	0,	
body	=	{	{kind	=	0,	points	=	{{48.000000,-58.000000},	{52.000000,-55.000000},	{51.000000,-39.000000},	{45.000000,-34.000000},	{48.000000,-22.000000},	{43.000000,-14.000000},	{25.000000,-19.000000},	{29.000000,-30.000000},	{22.000000,-37.000000},	{20.000000,-55.000000},	{25.000000,-59.000000},	{29.000000,-56.000000},	{32.000000,-75.000000},	{44.000000,-75.000000},	},	zwidth	=	8.000000,	},},
hit	=	{	{"A",	"punch",	0},{"B",	"kick",	0},{"J",	"jump",	0},{"D",	"defend",	0},{"D>A",	"ball",	0},{"D^A",	"singlong",	0},{"DvA",	"many_punch",	0},{"D^J",	"jump_hit",	0},},
catch	=	{
{kind	=	0,	strong	=	0,	catchx	=	0.000000,	catchy	=	0.000000,	where	=	Body.Neck,	points	=	{{40.000000,-16.000000},	{40.000000,-81.000000},	{65.000000,-81.000000},	{65.000000,-16.000000},	},	
},},

}

