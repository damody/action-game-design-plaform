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
Action.Standing	= GetEnum()
Action.Walking	= GetEnum()
Action.Running	= GetEnum()
Action.StopRunning	= GetEnum()
Action.HeavyWeaponWalk	= GetEnum()
Action.HeavyWeaponRun   = GetEnum()
Action.LightWeaponStandAttack	= GetEnum()
Action.LightWeaponJumpAttack	= GetEnum()
Action.LightWeaponRunAttack	= GetEnum()
Action.LightWeaponDashAttack	= GetEnum()
Action.LightWeaponThrow	= GetEnum()
Action.HeavyWeaponThrow	= GetEnum()
Action.LightWeaponJumpThrow	= GetEnum()
Action.HeavyWeaponJumpThrow	= GetEnum()
Action.Drink		= GetEnum()
Action.LightPunch	= GetEnum()
Action.LightKick	= GetEnum()
Action.HeavyPunch	= GetEnum()
Action.HeavyKick	= GetEnum()
Action.SuperPunch	= GetEnum()
Action.SuperKick	= GetEnum()
Action.JumpPunch	= GetEnum()
Action.JumpKick	= GetEnum()
Action.RunPuch	= GetEnum()
Action.RunKick	= GetEnum()
Action.ForwardFlyRowing	= GetEnum()
Action.BackwardFlyRowing= GetEnum()
Action.ForwardRowing	= GetEnum()
Action.BackwardRowing	= GetEnum()
Action.Defend	= GetEnum()
Action.DefendPunch	= GetEnum()
Action.DefendKick	= GetEnum()
Action.Catching	= GetEnum()
Action.Caught	= GetEnum()
Action.Falling	= GetEnum()
Action.Jump	= GetEnum()
Action.Dash = GetEnum()
Action.Crouch	= GetEnum()
Action.Injured	= GetEnum()
Action.ForwardLying	= GetEnum()
Action.BackwardLying	= GetEnum()
Action.InTheAir = GetEnum()
Action.AirSkill = GetEnum()
Action.XAxisSkill = GetEnum()
Action.ZAxisSkill = GetEnum()
Action.GroundSkill = GetEnum()
Action.UniqueSkill	= GetEnum()
Action.BasicActionEnd	= GetEnum()

count = 0;
Body = {}
Body.Neck	= GetEnum()
Body.Leg	= GetEnum()
Body.Waist	= GetEnum()

count = -1;
CheeAction = {}
Chee.Flying = GetEnum()
Chee.Break = GetEnum()

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
