require	"Script/effect"
function test(hero,e)
	if e == Effect.Fire  then
		hero:SetEffect( Effect.Fire );
	elseif e == Effect.測試  then
		hero:SetEffect( Effect.Fire );
	end
end
