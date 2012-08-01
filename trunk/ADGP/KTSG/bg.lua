name="Forbidden_Tower"
width = 40000
space_bounding =
{

	{xmin=0, ymin=0, zmin=0, xmax=40000, ymax=500, zmax=1700},
	{xmin=150, ymin=0, zmin=1600, xmax=600, ymax=500, zmax=1850},
	{xmin=800, ymin=0, zmin=1600, xmax=1250, ymax=500, zmax=1850},
	--{xmin=100, ymin=0, zmin=1000, xmax=700, ymax=500, zmax=1900},
	--{xmin=0, ymin=0, zmin=0, xmax=500, ymax=500, zmax=500},
	--{xmin=400, ymin=0, zmin=400, xmax=900, ymax=500, zmax=900},
}

ban_bounding =
{
	{xmin=100, ymin=0, zmin=100, xmax=200, ymax=100, zmax=500},
}

layer =
{
	{picture_path="bg\\ft\\sky.bmp", ground=0, x=0, y=0,z=2100, w=1594, h=148, loop_distance=0, timeline=1, time_start=0, time_end=0},
	{picture_path="bg\\ft\\w1.png", ground=0, x=0, y=174,  z=2000, w=288, h=62, loop_distance=288, timeline=1, time_start=0, time_end=0},
	{picture_path="bg\\ft\\w2.bmp", ground=0, x=0, y=60, z=2000, w=48, h=114, loop_distance=288, timeline=1, time_start=0, time_end=0},
	{picture_path="bg\\ft\\w3.bmp", ground=0, x=0, y=0,  z=2000, w=288, h=60, loop_distance=288, timeline=1, time_start=0, time_end=0},
	{picture_path="bg\\ft\\g1.bmp", ground=1, x=0, y=0,  z=2000, w=324, h=118, loop_distance=162, timeline=1, time_start=0, time_end=0},
	{picture_path="bg\\ft\\g2.bmp", ground=1, x=0, y=0,  z=1882, w=280, h=22, loop_distance=140, timeline=1, time_start=0, time_end=0},
	--{picture_path="bg\\ft\\g5.bmp", ground=1, x=0, y=0,  z=1860, w=280, h=1794, loop_distance=140, timeline=1, time_start=0, time_end=0},
	{picture_path="bg\\ft\\g3.bmp", ground=1, x=0, y=0,   z=66, w=280, h=24, loop_distance=140, timeline=1, time_start=0, time_end=0},
	{picture_path="bg\\ft\\g4.bmp", ground=1, x=0, y=0,   z=42, w=256, h=42, loop_distance=128, timeline=1, time_start=0, time_end=0},
	{picture_path="bg\\ft\\c1.bmp", ground=0, x=6, y=38,  z=1900, w=108, h=268, loop_distance=648, timeline=1, time_start=0, time_end=0},
	{picture_path="bg\\ft\\c2.bmp", ground=0, x=0, y=0,  z=1900, w=120, h=38, loop_distance=648, timeline=1, time_start=0, time_end=0},

	{picture_path="bg\\ft\\f1.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=0, time_end=0},
	{picture_path="bg\\ft\\f2.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=1, time_end=1},
	{picture_path="bg\\ft\\f3.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=2, time_end=2},
	{picture_path="bg\\ft\\f4.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=3, time_end=3},
	{picture_path="bg\\ft\\f5.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=4, time_end=4},
	{picture_path="bg\\ft\\f6.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=5, time_end=5},
	{picture_path="bg\\ft\\f7.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=6, time_end=6},
	{picture_path="bg\\ft\\f8.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=7, time_end=7},
	{picture_path="bg\\ft\\f9.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=8, time_end=8},
	{picture_path="bg\\ft\\fa.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=9, time_end=9},
	{picture_path="bg\\ft\\fb.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=10, time_end=10},
	{picture_path="bg\\ft\\fc.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=11, time_end=11},
	{picture_path="bg\\ft\\fd.bmp", ground=0, x=6, y=152, z=1900, w=108, h=154, loop_distance=648, timeline=13, time_start=12, time_end=12},
}

color_rect =
{
	{r=0.566, g=0.06, b=0.06, a=1, ground=1, x=0, y=0, z=1860, w=40000, h=1794},
	{r=0.06, g=0.06, b=0.566, a=1, ground=1, x=100, y=0, z=500, w=100, h=400},
}

parallel_light = 
{
	{x=2, y= -1.5, z= -1, light=3, timeline=1000, time_start=0, time_end=0},
	{x=0, y= -1.5, z= -1, light=10, timeline=1000, time_start=500, time_end=0},
	{x=-2, y= -1.5, z= -1, light=3, timeline=1000, time_start=1000, time_end=0},
}

