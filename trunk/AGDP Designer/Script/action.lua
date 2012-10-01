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
Action.Standing	= GetEnum()					--0 ����
Action.Walking	= GetEnum()					--1 ����
Action.Running	= GetEnum()					--2 �]�B
Action.StopRunning		= GetEnum()			--3 �٨�
Action.HeavyWeaponWalk	= GetEnum()			--4 �t���樫
Action.HeavyWeaponRun   = GetEnum()			--5 �t���]�B
Action.LightWeaponStandAttack	= GetEnum()	--6 ���߻��Z������
Action.LightWeaponJumpAttack	= GetEnum()	--7 �Ť����Z������
Action.LightWeaponRunAttack		= GetEnum()	--8 �Ĩ뻴�Z������
Action.LightWeaponDashAttack	= GetEnum()	--9 �ĸ����Z������
Action.LightWeaponThrow			= GetEnum() --10���Z�����Y
Action.HeavyWeaponThrow			= GetEnum()	--11���Z�����Y
Action.LightWeaponJumpThrow		= GetEnum()	--12�Ť����Y���Z��
Action.HeavyWeaponJumpThrow		= GetEnum()	--13�Ť����Y���Z��
Action.Drink			= GetEnum()			--14��
Action.BeforeAttack		= GetEnum()			--15�ǳƧ���
Action.Attacking		= GetEnum()			--16������
Action.AfterAttack		= GetEnum()			--17����
Action.BeforeSuperAttack= GetEnum()			--18�ǳƭ���
Action.SuperAttacking	= GetEnum()			--19����
Action.AfterSuperAttack	= GetEnum()			--20��������
Action.BeforeJumpAttack	= GetEnum()			--21�ǳƸ���
Action.JumpAttacking	= GetEnum()			--22����
Action.AfterJumpAttack	= GetEnum()			--23���𦬩�
Action.BeforeRunAttack	= GetEnum()			--24�ǳƶ]��
Action.RunAttacking		= GetEnum()			--25�]��
Action.AfterRunAttack	= GetEnum()			--26�]�𦬩�
Action.BeforeDashAttack	= GetEnum()			--27�ǳƽĸ���
Action.DashAttacking	= GetEnum()			--28�ĸ���
Action.AfterDashAttack	= GetEnum()			--29�ĸ��𦬩�
Action.Flip	    	= GetEnum()				--30��½
Action.Rolling		= GetEnum()				--31�u
Action.Defend		= GetEnum()				--32��
Action.FallingFront	= GetEnum()				--33�e�^
Action.FallingBack	= GetEnum()				--34��^
Action.Catching		= GetEnum()				--35��
Action.Caught		= GetEnum()				--36�Q��
Action.Falling		= GetEnum()				--37�^
Action.Jump			= GetEnum()				--38��
Action.Dash 		= GetEnum()				--39�ĸ�
Action.Crouch		= GetEnum()				--40��
Action.Injured		= GetEnum()				--41�Q����
Action.Lying		= GetEnum()				--42�˦a
Action.InTheAir 	= GetEnum()				--43�Ť�
Action.BeforeSkill 	= GetEnum()				--44�ǳƥX��
Action.AfterSkill 	= GetEnum()				--45����
Action.AirSkill 	= GetEnum()				--46�Ť��ޡA�L���O
Action.XAxisSkill 	= GetEnum()				--47X�b�ޡA�i�Τ�V�䱱��Z��V�A�[�t�ץHDVZ����
Action.ZAxisSkill 	= GetEnum()				--48Z�b�ޡA�i�Τ�V�䱱��X��V�A�[�t�ץHDVX����
Action.GroundSkill 	= GetEnum()				--49�a�����ۡA��V�䧹���L��
Action.FreeSkill 	= GetEnum()				--50�ۥѲ��ʵ��ۡA�|���䦳�ġA�[�t�ץHDVZ�BDVX����
Action.UniqueSkill	= GetEnum()				--51�S���ۡA�L���O�B�i�P�a
Action.BasicActionEnd	= GetEnum()			--52�H�����A�����O��

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
