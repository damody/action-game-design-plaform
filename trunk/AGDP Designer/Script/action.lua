function protect_table (tbl)
  return setmetatable ({},
    {
    __index = tbl,  -- read access gets original table item
    __newindex = function (t, n, v)
       --error ("attempting to change constant " .. tostring (n) .. " to " .. tostring (v), 2)
       -- do nothing
      end -- __newindex
    })

end -- function protect_table


-------------------------- test -----------------
count = -1;
function GetEnum()
	count = count + 1;
	return count;
end

Action = {}
Action.Standing	= GetEnum()					--0 站立
Action.Walking	= GetEnum()					--1 走路
Action.Running	= GetEnum()					--2 跑步
Action.StopRunning		= GetEnum()			--3 煞車
Action.HeavyWeaponWalk	= GetEnum()			--4 負重行走
Action.HeavyWeaponRun   = GetEnum()			--5 負重跑步
Action.LightWeaponStandAttack	= GetEnum()	--6 站立輕武器攻擊
Action.LightWeaponJumpAttack	= GetEnum()	--7 空中輕武器攻擊
Action.LightWeaponRunAttack		= GetEnum()	--8 衝刺輕武器攻擊
Action.LightWeaponDashAttack	= GetEnum()	--9 衝跳輕武器攻擊
Action.LightWeaponThrow			= GetEnum() --10輕武器投擲
Action.HeavyWeaponThrow			= GetEnum()	--11重武器投擲
Action.LightWeaponJumpThrow		= GetEnum()	--12空中投擲輕武器
Action.HeavyWeaponJumpThrow		= GetEnum()	--13空中投擲重武器
Action.Drink			= GetEnum()			--14飲
Action.BeforeAttack		= GetEnum()			--15準備攻擊
Action.Attacking		= GetEnum()			--16攻擊中
Action.AfterAttack		= GetEnum()			--17收招
Action.BeforeSuperAttack= GetEnum()			--18準備重擊
Action.SuperAttacking	= GetEnum()			--19重擊
Action.AfterSuperAttack	= GetEnum()			--20重擊收招
Action.BeforeJumpAttack	= GetEnum()			--21準備跳攻
Action.JumpAttacking	= GetEnum()			--22跳攻
Action.AfterJumpAttack	= GetEnum()			--23跳攻收招
Action.BeforeRunAttack	= GetEnum()			--24準備跑攻
Action.RunAttacking		= GetEnum()			--25跑攻
Action.AfterRunAttack	= GetEnum()			--26跑攻收招
Action.BeforeDashAttack	= GetEnum()			--27準備衝跳攻
Action.DashAttacking	= GetEnum()			--28衝跳攻
Action.AfterDashAttack	= GetEnum()			--29衝跳攻收招
Action.Fliping	    	= GetEnum()				--30空翻
Action.Rolling		= GetEnum()				--31滾
Action.Defend		= GetEnum()				--32擋
Action.FallingFront	= GetEnum()				--33前跌
Action.FallingBack	= GetEnum()				--34後跌
Action.Catching		= GetEnum()				--35抓
Action.Caught		= GetEnum()				--36被抓
Action.Falling		= GetEnum()				--37跌
Action.Jump			= GetEnum()				--38跳
Action.Dash 		= GetEnum()				--39衝跳
Action.Crouch		= GetEnum()				--40蹲
Action.Injured		= GetEnum()				--41被攻擊
Action.Lying		= GetEnum()				--42倒地
Action.InTheAir 	= GetEnum()				--43空中
Action.BeforeSkill 	= GetEnum()				--44準備出招
Action.AfterSkill 	= GetEnum()				--45收招
Action.AirSkill 	= GetEnum()				--46空中技，無重力
Action.XAxisSkill 	= GetEnum()				--47X軸技，可用方向鍵控制Z方向，加速度以DVZ控制
Action.ZAxisSkill 	= GetEnum()				--48Z軸技，可用方向鍵控制X方向，加速度以DVX控制
Action.GroundSkill 	= GetEnum()				--49地面絕招，方向鍵完全無效
Action.FreeSkill 	= GetEnum()				--50自由移動絕招，四方鍵有效，加速度以DVZ、DVX控制
Action.UniqueSkill	= GetEnum()				--51特殊絕招，無重力且可遁地
Action.BasicActionEnd	= GetEnum()			--52人物狀態結尾記號

count = -1;
Body = {}
Body.Neck	= GetEnum()
Body.Leg	= GetEnum()
Body.Waist	= GetEnum()

count = -1;
CheeAction = {}
CheeAction.Flying = GetEnum()
CheeAction.Break = GetEnum()

count = -1;
WeaponAction = {}
WeaponAction.OnFloor = GetEnum()
WeaponAction.InAir = GetEnum()
WeaponAction.OnHand = GetEnum()
WeaponAction.Break = GetEnum()
WeaponAction.Hit = GetEnum()
WeaponAction.Throw = GetEnum()
-- protect my table now
Effect = protect_table (Effect)
Body = protect_table (Body)


--Effect.Fire = 44  --> Error: attempting to change constant WIDTH to 44
