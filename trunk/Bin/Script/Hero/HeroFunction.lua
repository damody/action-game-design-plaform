require	"Script/effect"

function AddCondition(hero,condition_index)
	if condition_index == Effect.Fire then
		condition_Time = GetConditionTime( condition_index );
		hero:AddCondition(condition_index,condition_Time);
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
			hero:ModifyHP( -100 );
		end
	end
end
