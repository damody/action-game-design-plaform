require "effect"
require "action"

name="Firen"					--人物名稱
head="sprite\sys\firen_f.bmp"	--人物大頭貼圖檔路徑
small="sprite\sys\firen_s.bmp"	--人物小圖圖檔路徑

--圖檔
file = {
	{
		path="sprite\sys\firen_0.bmp",	--圖檔路徑
		autoclip=1, 					--圖檔切割方式，1:同大小方塊自動裁切
		w=79, h=79, 					--顯示的寬高，w:寬, h:高
		row=10, col=7					--方塊的行數及列數，row:直行數, col:橫列數
	},
	{path="sprite\sys\firen_1.bmp", autoclip=1, w=79, h=79, row=10, col=7},
	{path="sprite\sys\firen_2.bmp", autoclip=1, w=79, h=79, row=10, col=7},
	{
		path="sprite\sys\firen_X.bmp",	--圖檔路徑
		autoclip=0,						--圖檔切割方式，0:全自訂
		pic= {
			{x=0, y=0, w=50, h=50},		--x,y: 參考點，即圖格左上角。w,h:圖格寬高
			{x=40, y=40, w=50, h=50},
		}
	},
}

--人物基本數據
walking_speed=5.000000
walking_speedz=2.500000
running_speed=9.600000
running_speedz=1.580000
heavy_walking_speed=3.700000
heavy_walking_speedz=1.850000
heavy_running_speed=6.200000
heavy_running_speedz=1.000000

--落地切換設定，只要這裡沒設定的，落地時都切換到 crouch[0]
air_crouch_map={
--格式： { Action, Frame, FrameID }
{Action.InTheAir, "crouch", 0},
{Action.Dash, "crouch", 1},
{Action.BeforeDashAttack, "crouch", 1},
{Action.DashAttacking, "crouch", 1},
{Action.AfterDashAttack, "crouch", 1}
}


frame =
{
	--必要 Frame
	default  = {},		--預設，人物初始 Frame ，通常也作為所有招式結束後跳轉對象，必須要是 Action.Standing
	standing = {},		--地上站立
	walking  = {},		--地上行走
	in_the_air = {},	--必須有 in_the_air[0]，在空中的預設 Frame ，只要在空中處於 Action.Standing 就會切換到 in_the_air[0]
	injured = {},		--被擊中
	lying = {},			--倒地
	falling_front = {},	--從後方被擊飛
	falling_back = {},	--從前方被擊飛
	crouch = {},		--必須有 crouch[0] 給落地切換，預設支援LF2式的衝跳切換
	--通常都會有的 Frame
	running      = {},	--與stop_running一組。預設按法為>>，不靠 hit 切換
	stop_running = {},	--與running一組，見上方說明
	jump         = {},	--跳躍
	dash_front   = {},	--與 dash_back 一組，預設在此 Frame 按下反向方向建會跳到 dash_back
	dash_back    = {},	--與 dash_front 一組，見上方說明
}

frame.standing[1]=
{
	pic_id=0, pic_x=1, pic_y=2, --圖片資訊，pic_id: 第幾個圖檔，pic_x pic_y: 圖檔中的第幾欄第幾列
	state=Action.Standing, 		--狀態
	wait=60, 					--停留在此 frame 的時間
	next={frame.standing, 2},	--此 frame 結束後的下一個 frame 之名稱及序號A
	dvx=0, dvy=0, dvz=0, 		--進入此 frame 時得到的加速度
	centerx=39, centery=79, 	--人物支點(position)相對於圖片左上角的位置
	clear_key_queue=0,			--進入此 frame 時是否清除按鍵佇列，0：完全不清除，1：清除末項，2：清空

	--進入此 frame 必須付出的代價
	consume = {
		rule = 0, 				--標示以何種方式進入此 frame 必須付出此代價： -1:next , 0:both , 1:hit
		HP = 0, MP = 0,			--代價
		backFrame = "default", backFrameID = 0			--若無法付出此代價，將跳到哪個 frame ，若填 default 0 表示保持原來的 frame 不跳
	},

	--按鍵跳轉，格式：{按鍵組合, frame, 序號}
	hit = {{"d>.a", "super_punch", 1}, {"dja", "super_punch2", 1}},

	--身體範圍
	body={
		--格式：種類, 凸多邊形頂點集合, z方向厚度
		{kind=0, points={{0,0}, {30,50}, {80,90}}, zwidth=10},
		{kind=1, points={{12,43}, {40,50}, {-80,60}}, zwidth=10},
	},

	--血跡，格式：{大小, x, y}座標以圖片左上角為基準
	blood={{size=1.0,0,0}, {size=2.0,30,50}, {size=3.3,80,90}},

	--攻擊
	attack={
		{kind=FOLLOW_EFFECT, 	--攻擊種類
		effect=EFFECT_FIRE, 	--擊中效果，僅在特殊種類之攻擊有效，否則多填 Effect.End
		points={{0,0}, {30,50}, {80,90}}, zwidth=10,	--攻擊範圍，格式同 body
		dvx=10, dvy=-10, dvz=30,--被擊中方獲得的加速度
		fall=70, 				--擊倒值
		breakDefend=16,			--破防值
		arest=50,				--攻擊停頓時間
		reAttackRest=60,		--再度判定時間
		injury=45, 				--攻擊力
		strength=50,			--判定強度
		}
	},

	--抓擊
	catch={
		{kind=0, 				--種類
		strong=100, 			--判定強度
		catchx=60, catchy=-30,	--抓人的位置
		where = Body.Neck		--抓住的部位
		points={{0,0}, {30,50}, {80,90}}, zwidth=10		--有效範圍，格式同 body
		}
	},

	--創造物件
	newobjects={
		{name="XXX", 			--欲創造物件之名稱
		amount=1, 				--創造數量
		x = 60, y = 30,			--產出物件相對於自己的位置
		facing=0, 				--面對方向， 0:與自己同向，1:與自己反向
		frame="fly",	 		--該物件的初始 frame 名稱
		frameID=1,				--該物件的初始 frame 序號
		hp=500, 				--產出物件的血量
		ai="XXX", 				--產出物件的 ai ?
		dvx=0, dvy=0, dvz=0		--產出物件的初速度
		},
		{name="XXX", amount=5, facing=0, frame=1, hp=500, ai="XXX", dvx=0, dvy=0, dvz=0},
	}

	--持有武器
	--未完成

	--進入此 frame 播放之音效，直接以字串輸入該音效檔路徑
	sound = "data\\001.wav"
}
