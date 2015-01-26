local count = -1;
local function GetEnum()
	count = count + 1;
	return count;
end

ObjectType = {};
ObjectType.CHEE = GetEnum();   --氣功
ObjectType.STATIC = GetEnum(); --場地靜態物件
ObjectType.LIGHT = GetEnum();  --輕型道具
ObjectType.HEAVY = GetEnum();  --重型道具
ObjectType.SUPPLE = GetEnum(); --補給品

count = -1;
FlyingType={};
FlyingType.DEFAULT = GetEnum(); 		 	--受重力
FlyingType.BEZIERCURVE_PATH = GetEnum();	--自訂路徑-BezierCurve內插
FlyingType.BSPLINECURVE_PATH = GetEnum();	--自訂路徑-BsplineCurve內插
FlyingType.HSPLINECURVE_PATH = GetEnum();	--自訂路徑-HSplineCurve內插
FlyingType.LINEARLINE_PATH = GetEnum();	    --自訂路徑-LinearLine內插
FlyingType.CHASE = GetEnum();				--追蹤

local object = {
  _NAME = "object",
  _VERSION = 0.1,
  _COPYRIGHT = "Damody",
  _DESCRIPTION = "Init Debugger for the Lua",
}

return action

