
--描述各種的塔
--tower type ={Laser=1, MACHINE_GUN=2, MISSILE=3}
--格式:
--Towers={	typenum=塔的種類數
--			tower1={pic=塔的圖片編號,type=塔的類型, hp=hp, atk=塔的攻擊力,atkspeed=塔的攻速,RotateSpeed=塔的旋轉速度,ballpic=子彈圖片編號, ballspeed=子彈前進速度,
--			picpos={x=子彈在圖上的x座標,y=子彈在圖上的y座標,z=子彈圖有幾行,w=子彈圖有幾列}, size={x=子彈圖的寬,y=子彈圖的長} }...
--}
Towers={
			typenum=3,
			tower1={pic=100, type=1, hp=100, atk=50, atkspeed=0.3, RotateSpeed=0.01, ballpic=100, ballspeed=80, picpos={x=1,y=1,z=1,w=1}, size={x=10,y=20} },
			tower2={pic=100, type=2, hp=1000, atk=50, atkspeed=0.3, RotateSpeed=0.01, ballpic=100, ballspeed=180, picpos={x=1,y=1,z=1,w=1}, size={x=5,y=50} },
			tower3={pic=100, type=3, hp=5000, atk=50, atkspeed=0.3, RotateSpeed=0.01, ballpic=100, ballspeed=280, picpos={x=1,y=1,z=1,w=1}, size={x=100,y=10} },
}


TowerLvUp={	--塔的成長率
			tower1={hp=10, atk=5, atksp=0.1, rotatespeed=0.0001},
			tower2={hp=10, atk=5, atksp=0.1, rotatespeed=0.0001},
			tower3={hp=10, atk=5, atksp=0.1, rotatespeed=0.0001},
}

TowerPos={	Tpos1={px=-200,py=-75},
			Tpos2={px=-160,py=-60},
			Tpos3={px=-120,py=-45},
			Tpos4={px=-80,py=-30},
			Tpos5={px=-40,py=-15},
			Tpos6={px=0,py=0},
			Tpos7={px=0,py=0},
			Tpos8={px=0,py=0},
			Tpos9={px=0,py=0},
			Tpos10={px=0,py=0},
			Tpos11={px=0,py=0},
			Tpos12={px=0,py=0},
			Tpos13={px=0,py=0}
		}
