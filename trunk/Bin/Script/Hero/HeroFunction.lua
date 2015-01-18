--require("Script.mydebug").GoZeroBrane()
--require("Script.mobdebug").start()


require("Script.effect")

function AddCondition(hero, condition_index)
	if condition_index == Effect.Fire then
		condition_Time = GetConditionTime( condition_index );
		hero:AddCondition(condition_index,condition_Time);
	elseif condition_index == Effect.TTEST then
		hero:AddCondition(condition_index,2);
	end
end

function GetConditionTime(condition_index)
	if condition_index == Effect.Fire then
		return 2;
	end
end

function ConditionUpdate(hero, condition_index ,_time)
	if condition_index == Effect.Fire then
		if (_time % 60) == 0 then
			hero:ModifyHP( -10 );
		end
	elseif condition_index == Effect.TTEST then
		if (_time % 60) == 0 then
			hero:ModifyFall( -2 );
		end
	end
end
