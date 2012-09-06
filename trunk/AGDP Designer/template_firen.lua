require "effect"
require "action"

name="Firen"					--�H���W��
head="sprite\sys\firen_f.bmp"	--�H���j�Y�K���ɸ��|
small="sprite\sys\firen_s.bmp"	--�H���p�Ϲ��ɸ��|

--����
file = {
	{
		path="sprite\sys\firen_0.bmp",	--���ɸ��|
		autoclip=1, 					--���ɤ��Τ覡�A1:�P�j�p����۰ʵ���
		w=79, h=79, 					--����������e���Aw:�e, h:��
		row=10, col=7					--�������ƤΦC�ơArow:�����, col:��C��
	},
	{path="sprite\sys\firen_1.bmp", autoclip=1, w=79, h=79, row=10, col=7},
	{path="sprite\sys\firen_2.bmp", autoclip=1, w=79, h=79, row=10, col=7},
	{
		path="sprite\sys\firen_X.bmp",	--���ɸ��|
		autoclip=0,						--���ɤ��Τ覡�A0:���ۭq
		pic= {
			{x=0, y=0, w=50, h=50},		--x,y: �Ѧ��I�A�Y�Ϯ楪�W���Cw,h:�Ϯ�e��
			{x=40, y=40, w=50, h=50},
		}
	},
}
--�H���򥻼ƾ�
walking_speed=5.000000
walking_speedz=2.500000
running_speed=9.600000
running_speedz=1.580000
heavy_walking_speed=3.700000
heavy_walking_speedz=1.850000
heavy_running_speed=6.200000
heavy_running_speedz=1.000000
jump_height=-16.299999
jump_distance=10.000000
jump_distancez=3.750000
dash_height=-10.000000
dash_distance=18.000000
dash_distancez=5.000000
rowing_height=-2.000000
rowing_distance=5.000000


frame =
{
	standing = {}
}

frame.standing[1]=
{
	pic_id=0, pic_x=1, pic_y=2, --�Ϥ���T�Apic_id: �ĴX�ӹ��ɡApic_x pic_y: ���ɤ����ĴX��ĴX�C
	state=STANDING, 			--���A
	wait=60, 					--���d�b�� frame ���ɶ�
	next={frame.standing, 2},	--�� frame �����᪺�U�@�� frame ���W�٤ΧǸ�A
	dvx=0, dvy=0, dvz=0, 		--�i�J�� frame �ɱo�쪺�[�t��
	centerx=39, centery=79, 	--�H�����I(position)�۹��Ϥ����W������m
	clear_key_queue=0,			--�i�J�� frame �ɬO�_�M�������C

	--�i�J�� frame �����I�X���N��(��������Ū��)
	consume = {
		rule = 0, 				--�ХܥH��ؤ覡�i�J�� frame �����I�X���N���G -1:next , 0:both , 1:hit
		HP = 0, MP = 0,			--�N��
		backFrame = "default", backFrameID = 0			--�Y�L�k�I�X���N���A�N������� frame �A�Y�� default 0 ���ܫO����Ӫ� frame ����
	},

	--�������A�榡�G{����զX, frame, �Ǹ�}
	hit = {{"d>.a", "super_punch", 1}, {"dja", "super_punch2", 1}},

	--����d��
	body={
		--�榡�G����, �Y�h��γ��I���X, z��V�p��
		{kind=0, points={{0,0}, {30,50}, {80,90}}, zwidth=10},
		{kind=1, points={{12,43}, {40,50}, {-80,60}}, zwidth=10},
	},

	--���A�榡�G{�j�p, x, y}�y�ХH�Ϥ����W�������
	blood={{size=1.0,0,0}, {size=2.0,30,50}, {size=3.3,80,90}},

	--����(��������Ū��)
	attack={
		{kind=FOLLOW_EFFECT, 	--��������
		effect=EFFECT_FIRE, 	--�����ĪG�A�Ȧb�S���������������ġA�_�h�h�� Effect.End
		points={{0,0}, {30,50}, {80,90}}, zwidth=10,	--�����d��A�榡�P body
		dvx=10, dvy=-10, dvz=30,--�Q��������o���[�t��
		fall=70, 				--���˭�
		breakDefend=16,			--�}����
		arest=50,				--�������y�ɶ�
		reAttackRest=60,		--�A�קP�w�ɶ�
		injury=45, 				--�����O
		strength=50,			--�P�w�j��
		}
	},

	--����
	catch={
		{kind=0, 				--����
		strong=100, 			--�P�w�j��
		catchx=60, catchy=-30,	--��H����m
		where = Body.Neck		--���������
		points={{0,0}, {30,50}, {80,90}}, zwidth=10		--���Ľd��A�榡�P body
		}
	},

	--�гy����(��������Ū��)
	newobjects={
		{name="XXX", 			--���гy���󤧦W��
		amount=1, 				--�гy�ƶq
		x = 60, y = 30,			--���X����۹��ۤv����m
		facing=0, 				--�����V�A 0:�P�ۤv�P�V�A1:�P�ۤv�ϦV
		frame="fly",	 		--�Ӫ��󪺪�l frame �W��
		frameID=1,				--�Ӫ��󪺪�l frame �Ǹ�
		hp=500, 				--���X���󪺦�q
		ai="XXX", 				--���X���� ai ?
		dvx=0, dvy=0, dvz=0		--���X���󪺪�t��
		},
		{name="XXX", amount=5, facing=0, frame=1, hp=500, ai="XXX", dvx=0, dvy=0, dvz=0},
	}

	--�����Z��
	--������

	--�i�J�� frame ���񤧭���
	--������
}