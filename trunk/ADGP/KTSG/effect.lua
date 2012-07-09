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
count = 0;
function GetEnum()
	count = count + 1;
	return count;
end

Effect = {}
Effect.Fire	= GetEnum()
Effect.BlackFire	= GetEnum()
Effect.PurpleFire	= GetEnum()
Effect.Freeze	= GetEnum()
Effect.IceSlow	= GetEnum()
Effect.Punch	= GetEnum()
Effect.Knife	= GetEnum()
Effect.Thunder	= GetEnum()
Effect.Palsy	= GetEnum()
Effect.Faint	= GetEnum()

-- protect my table now
Effect = protect_table (Effect)


--Effect.Fire = 44  --> Error: attempting to change constant WIDTH to 44