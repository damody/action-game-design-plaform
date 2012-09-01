--UI lua file
--控制項type編號={1=button,2=text,3=combo box, 4=slider}
--formate
--uinum = UI的數量
--ui1={
--		cmdnum=控制項數量,
--		cmd1={cid=id編號(數字), ctext=控制項的字, ctype=控制項類型(數字), cpx=控制項x座標, cpy=控制項y座標,
--		cw=控制項寬度, ch=控制項長度}
--		cmd2.....
--		}
--ui2={...
--		}
--預設畫面size=1440*900
--物件座標和長寬會自動轉換
--
--如果控制項為combo box格式為
--		...,
--		cmd1={cid=id編號(數字), ctext=控制項的字, ctype=控制項類型(數字), cpx=控制項x座標, cpy=控制項y座標,
--		cw=控制項寬度, ch=控制項長度, itemnum=物件數,
--		item1 = item的字,
--		item2 = hello
--		...
--		}
--如果控制項為slider格式為
--		...,
--		cmd1={cid=id編號(數字), ctext=控制項的字, ctype=控制項類型(數字), cpx=控制項x座標, cpy=控制項y座標,
--		cw=控制項寬度, ch=控制項長度, cmin=slider的最小值, cmax=slider的最大值, cval=slider的初始值
--		...
--		}
uinum = 4

ui1={	--main menu
		cmdnum=3,
		cmd1={cid=1, ctext="Start Game", ctype=1, cpx=590, cpy=450, cw=260, ch=80},
		cmd2={cid=2, ctext="Option", ctype=1, cpx=590, cpy=600, cw=260, ch=80},
		cmd3={cid=3, ctext="Exit", ctype=1, cpx=590, cpy=750, cw=260, ch=80}
}
textch = 80;
ui2={	--option menu
		cmdnum=15,
		cmd1={cid=4, ctext="volume", ctype=2, cpx=300, cpy=200, cw=100, ch = 50},
		cmd2={cid=5, ctext="", ctype=4, cpx=400, cpy=200, cw=640, ch = 50, cmin=0, cmax=7000, cval=5000},

		cmd3={cid=6, ctext="Up", ctype=2, cpx=350, cpy=300, cw=80, ch=textch},
		cmd4={cid=7, ctext="up", ctype=1, cpx=400, cpy=300, cw=120, ch=50},

		cmd5={cid=8, ctext="Down", ctype=2, cpx=350, cpy=400, cw=80, ch=textch},
		cmd6={cid=9, ctext="Down", ctype=1, cpx=400, cpy=400, cw=120, ch=50},

		cmd7={cid=10, ctext="Skill", ctype=2, cpx=350, cpy=500, cw=80, ch=textch},
		cmd8={cid=11, ctext="Skill", ctype=1, cpx=400, cpy=500, cw=120, ch=50},

		cmd9={cid=12, ctext="Left", ctype=2, cpx=950, cpy=300, cw=80, ch=textch},
		cmd10={cid=13, ctext="Left", ctype=1, cpx=1000, cpy=300, cw=120, ch=50},

		cmd11={cid=14, ctext="Right", ctype=2, cpx=950, cpy=400, cw=80, ch=textch},
		cmd12={cid=15, ctext="Right", ctype=1, cpx=1000, cpy=400, cw=120, ch=50},

		cmd13={cid=16, ctext="time", ctype=2, cpx=950, cpy=500, cw=80, ch=textch},
		cmd14={cid=17, ctext="time", ctype=1, cpx=1000, cpy=500, cw=120, ch=50},

		cmd15={cid=18, ctext="Back", ctype=1, cpx=50, cpy=100, cw=120, ch=70}
}

ui3={	--tower setting page
		cmdnum=14,
		cmd1={cid=19, ctext="", ctype=3, cpx=50, cpy=50, cw=200, ch = 40, itemnum=13,		--砲塔數
		item1="tower 1",
		item2="tower 2",
		item3="tower 3",
		item4="tower 4",
		item5="tower 5",
		item6="tower 6",
		item7="tower 7",
		item8="tower 8",
		item9="tower 9",
		item10="tower 10",
		item11="tower 11",
		item12="tower 12",
		item13="tower 13"},
		cmd2={cid=20, ctext="Lv up/cost:--", ctype=1, cpx=250, cpy=30, cw=200, ch=35},
		cmd3={cid=21, ctext="Sell/gold:--", ctype=1, cpx=250, cpy=80, cw=200, ch=35},
		cmd4={cid=22, ctext="Type:--", ctype=2, cpx=50, cpy=150, cw=200, ch=50},
		cmd5={cid=23, ctext="Lv:--", ctype=2, cpx=50, cpy=190, cw=200, ch=80},
		cmd6={cid=59, ctext="Hp:--", ctype=2, cpx=50, cpy=230, cw=200, ch=80},
		cmd7={cid=24, ctext="Atk:--", ctype=2, cpx=50, cpy=270, cw=200, ch=80},
		cmd8={cid=25, ctext="Atk speed:--", ctype=2, cpx=50, cpy=310, cw=150, ch=80},

		cmd9={cid=26, ctext="", ctype=3, cpx=50, cpy=400, cw=200, ch = 40, itemnum=3,		--砲塔種數
		item1="Laser",	--機槍
		item2="Machine gun",		--飛彈
		item3="Missile"			--雷射
		},
		cmd10={cid=27, ctext="buy/cost:--", ctype=1, cpx=250, cpy=400, cw=200, ch=40},
		cmd11={cid=28, ctext="Option", ctype=1, cpx=1200, cpy=50, cw=100, ch=50},
		cmd12={cid=29, ctext="Back", ctype=1, cpx=1200, cpy=150, cw=100, ch=50},
		cmd13={cid=60, ctext="Exit", ctype=1, cpx=1200, cpy=250, cw=100, ch=50},

		cmd14={cid=61, ctext="Gold:--", ctype=1, cpx=50, cpy=10, cw=100, ch=50},
}

ui4={	--//game play page
		cmdnum=29,
		cmd1={cid=30, ctext="tower1", ctype=2, cpx=20, cpy=20, cw=100, ch=50},
		cmd2={cid=31, ctext="hp:--", ctype=2, cpx=20, cpy=50, cw=100, ch=50},

		cmd3={cid=32, ctext="tower2", ctype=2, cpx=20, cpy=100, cw=100, ch=50},
		cmd4={cid=33, ctext="hp:--", ctype=2, cpx=20, cpy=130, cw=100, ch=50},

		cmd5={cid=34, ctext="tower3", ctype=2, cpx=120, cpy=20, cw=100, ch=50},
		cmd6={cid=35, ctext="hp:--", ctype=2, cpx=120, cpy=50, cw=100, ch=50},

		cmd7={cid=36, ctext="tower4", ctype=2, cpx=120, cpy=100, cw=100, ch=50},
		cmd8={cid=37, ctext="hp:--", ctype=2, cpx=120, cpy=130, cw=100, ch=50},

		cmd9={cid=38, ctext="tower5", ctype=2, cpx=220, cpy=20, cw=100, ch=50},
		cmd10={cid=39, ctext="hp:--", ctype=2, cpx=220, cpy=50, cw=100, ch=50},

		cmd11={cid=40, ctext="tower6", ctype=2, cpx=220, cpy=100, cw=100, ch=50},
		cmd12={cid=41, ctext="hp:--", ctype=2, cpx=220, cpy=130, cw=100, ch=50},

		cmd13={cid=42, ctext="tower7", ctype=2, cpx=320, cpy=20, cw=100, ch=50},
		cmd14={cid=43, ctext="hp:--", ctype=2, cpx=320, cpy=50, cw=100, ch=50},

		cmd15={cid=44, ctext="tower8", ctype=2, cpx=320, cpy=100, cw=100, ch=50},
		cmd16={cid=45, ctext="hp:--", ctype=2, cpx=320, cpy=130, cw=100, ch=50},

		cmd17={cid=46, ctext="tower9", ctype=2, cpx=420, cpy=20, cw=100, ch=50},
		cmd18={cid=47, ctext="hp:--", ctype=2, cpx=420, cpy=50, cw=100, ch=50},

		cmd19={cid=48, ctext="tower10", ctype=2, cpx=420, cpy=100, cw=100, ch=50},
		cmd20={cid=49, ctext="hp:--", ctype=2, cpx=420, cpy=130, cw=100, ch=50},

		cmd21={cid=50, ctext="tower11", ctype=2, cpx=520, cpy=20, cw=100, ch=50},
		cmd22={cid=51, ctext="hp:--", ctype=2, cpx=520, cpy=50, cw=100, ch=50},

		cmd23={cid=52, ctext="tower12", ctype=2, cpx=520, cpy=100, cw=100, ch=50},
		cmd24={cid=53, ctext="hp:--", ctype=2, cpx=520, cpy=130, cw=100, ch=50},

		cmd25={cid=54, ctext="tower13", ctype=2, cpx=620, cpy=20, cw=100, ch=50},
		cmd26={cid=55, ctext="hp:--", ctype=2, cpx=620, cpy=50, cw=100, ch=50},

		cmd27={cid=56, ctext="Gold:--", ctype=2, cpx=1000, cpy=20, cw=100, ch=50},
		cmd28={cid=57, ctext="cd:--", ctype=2, cpx=1000, cpy=60, cw=100, ch=50},

		cmd29={cid=58, ctext="Menu", ctype=1, cpx=1300, cpy=20, cw=100, ch=60}
}
--next id 61




































