count = -1;
function GetEnum()
	count = count + 1;
	return count;
end

ObjectType = {};
ObjectType.CHEE = GetEnum();   --��\
ObjectType.STATIC = GetEnum(); --���a�R�A����
ObjectType.LIGHT = GetEnum();  --�����D��
ObjectType.HEAVY = GetEnum();  --�����D��
ObjectType.SUPPLE = GetEnum(); --�ɵ��~

count = -1;
Flyingtype={};
Flyingtype.DEFAULT = GetEnum(); 		 	--�����O
Flyingtype.BEZIERCURVE_PATH = GetEnum();	--�ۭq���|-BezierCurve����
Flyingtype.BSPLINECURVE_PATH = GetEnum();	--�ۭq���|-BsplineCurve����
Flyingtype.HSPLINECURVE_PATH = GetEnum();	--�ۭq���|-HSplineCurve����
Flyingtype.LINEARLINE_PATH = GetEnum();	    --�ۭq���|-LinearLine����
Flyingtype.CHASE = GetEnum();				--�l��