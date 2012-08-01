count = -1;
function GetEnum()
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
Flyingtype={};
Flyingtype.DEFAULT = GetEnum(); 		 	--受重力
Flyingtype.BEZIERCURVE_PATH = GetEnum();	--自訂路徑-BezierCurve內插
Flyingtype.BSPLINECURVE_PATH = GetEnum();	--自訂路徑-BsplineCurve內插
Flyingtype.HSPLINECURVE_PATH = GetEnum();	--自訂路徑-HSplineCurve內插
Flyingtype.LINEARLINE_PATH = GetEnum();	    --自訂路徑-LinearLine內插
Flyingtype.CHASE = GetEnum();				--追蹤