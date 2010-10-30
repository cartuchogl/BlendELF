
ELF_API elfBezierPoint* ELF_APIENTRY elfCreateBezierPoint()
{
	elfBezierPoint* point;

	point = (elfBezierPoint*)malloc(sizeof(elfBezierPoint));
	memset(point, 0x0, sizeof(elfBezierPoint));
	point->objType = ELF_BEZIER_POINT;
	point->objDestr = elfDestroyBezierPoint;

	elfIncObj(ELF_BEZIER_POINT);

	return point;
}

void elfDestroyBezierPoint(void* data)
{
	elfBezierPoint* point = (elfBezierPoint*)data;

	free(point);

	elfDecObj(ELF_BEZIER_POINT);
}

ELF_API void ELF_APIENTRY elfSetBezierPointPosition(elfBezierPoint* point, float x, float y)
{
	point->p.x = x;
	point->p.y = y;
}

ELF_API void ELF_APIENTRY elfSetBezierPointControl1(elfBezierPoint* point, float x, float y)
{
	point->c1.x = x;
	point->c1.y = y;
}

ELF_API void ELF_APIENTRY elfSetBezierPointControl2(elfBezierPoint* point, float x, float y)
{
	point->c2.x = x;
	point->c2.y = y;
}

ELF_API elfVec2f ELF_APIENTRY elfGetBezierPointPosition(elfBezierPoint* point)
{
	return point->p;
}

ELF_API elfVec2f ELF_APIENTRY elfGetBezierPointControl1(elfBezierPoint* point)
{
	return point->c1;
}

ELF_API elfVec2f ELF_APIENTRY elfGetBezierPointControl2(elfBezierPoint* point)
{
	return point->c2;
}

ELF_API elfBezierCurve* ELF_APIENTRY elfCreateBezierCurve()
{
	elfBezierCurve* curve;

	curve = (elfBezierCurve*)malloc(sizeof(elfBezierCurve));
	memset(curve, 0x0, sizeof(elfBezierCurve));
	curve->objType = ELF_BEZIER_CURVE;
	curve->objDestr = elfDestroyBezierCurve;

	curve->points = elfCreateList();
	elfIncRef((elfObject*)curve->points);

	elfIncObj(ELF_BEZIER_CURVE);

	return curve;
}

void elfDestroyBezierCurve(void* data)
{
	elfBezierCurve* curve = (elfBezierCurve*)data;

	elfDecRef((elfObject*)curve->points);

	free(curve);

	elfDecObj(ELF_BEZIER_CURVE);
}

ELF_API void ELF_APIENTRY elfSetBezierCurveType(elfBezierCurve* curve, int type)
{
	if(type >= ELF_LOC_X && type <= ELF_QUA_W)
	{
		curve->curveType = type;
	}
}

ELF_API int ELF_APIENTRY elfGetBezierCurveType(elfBezierCurve* curve)
{
	return curve->curveType;
}

ELF_API void ELF_APIENTRY elfAddBezierCurvePoint(elfBezierCurve* curve, elfBezierPoint* point)
{
	int i;
	elfBezierPoint* pnt;

	for(i = 0, pnt = (elfBezierPoint*)elfBeginList(curve->points); pnt;
		pnt = (elfBezierPoint*)elfGetListNext(curve->points), i++)
	{
		if(pnt->p.x > point->p.x)
		{
			elfInsertListObject(curve->points, i, (elfObject*)point);
			return;
		}
	}

	elfAppendListObject(curve->points, (elfObject*)point);
}

int elfGetCurvePointCount(elfBezierCurve* curve)
{
	return elfGetListLength(curve->points);
}

ELF_API elfBezierPoint* ELF_APIENTRY elfGetPointFromBezierCurve(elfBezierCurve* curve, int idx)
{
	return (elfBezierPoint*)elfGetListObject(curve->points, idx);
}

ELF_API float ELF_APIENTRY elfGetBezierCurveValue(elfBezierCurve* curve, float x)
{
	elfBezierPoint* pnt;
	elfBezierPoint* point1 = NULL;
	elfBezierPoint* point2 = NULL;
	float t;

	for(pnt = (elfBezierPoint*)elfBeginList(curve->points); pnt;
		pnt = (elfBezierPoint*)elfGetListNext(curve->points))
	{
		if(pnt->p.x > x)
		{
			point2 = pnt;
			break;
		}
		point1 = pnt;
	}

	if(!point1 && !point2) return 0.0f;
	if(!point2) return point1->p.y;

	t = (x-point1->p.x)/(point2->p.x-point1->p.x);
	return point1->p.y+(point2->p.y-point1->p.y)*t;
}

ELF_API elfIpo* ELF_APIENTRY elfCreateIpo()
{
	elfIpo* ipo;

	ipo = (elfIpo*)malloc(sizeof(elfIpo));
	memset(ipo, 0x0, sizeof(elfIpo));
	ipo->objType = ELF_IPO;
	ipo->objDestr = elfDestroyIpo;

	ipo->curves = elfCreateList();
	elfIncRef((elfObject*)ipo->curves);

	elfIncObj(ELF_IPO);

	return ipo;
}

void elfDestroyIpo(void* data)
{
	elfIpo* ipo = (elfIpo*)data;

	elfDecRef((elfObject*)ipo->curves);

	free(ipo);

	elfDecObj(ELF_IPO);
}

ELF_API unsigned char ELF_APIENTRY elfAddIpoCurve(elfIpo* ipo, elfBezierCurve* curve)
{
	elfBezierCurve* cur;

	for(cur = (elfBezierCurve*)elfBeginList(ipo->curves); cur;
		cur = (elfBezierCurve*)elfGetListNext(ipo->curves))
	{
		if(cur->curveType == curve->curveType) return ELF_FALSE;
	}

	elfAppendListObject(ipo->curves, (elfObject*)curve);

	if(curve->curveType <= ELF_LOC_Z) ipo->loc = ELF_TRUE;
	if(curve->curveType <= ELF_ROT_Z) ipo->rot = ELF_TRUE;
	if(curve->curveType <= ELF_SCALE_Z) ipo->scale = ELF_TRUE;
	if(curve->curveType <= ELF_QUA_W) ipo->qua = ELF_TRUE;

	return ELF_TRUE;
}

ELF_API int ELF_APIENTRY elfGetIpoCurveCount(elfIpo* ipo)
{
	return elfGetListLength(ipo->curves);
}

ELF_API elfBezierCurve* ELF_APIENTRY elfGetCurveFromIpo(elfIpo* ipo, int idx)
{
	return (elfBezierCurve*)elfGetListObject(ipo->curves, idx);
}

ELF_API elfVec3f ELF_APIENTRY elfGetIpoLoc(elfIpo* ipo, float x)
{
	elfBezierCurve* curve;
	elfVec3f result;

	memset(&result, 0x0, sizeof(elfVec3f));

	for(curve = (elfBezierCurve*)elfBeginList(ipo->curves); curve;
		curve = (elfBezierCurve*)elfGetListNext(ipo->curves))
	{
		if(curve->curveType == ELF_LOC_X) result.x = elfGetBezierCurveValue(curve, x);
		else if(curve->curveType == ELF_LOC_Y) result.y = elfGetBezierCurveValue(curve, x);
		else if(curve->curveType == ELF_LOC_Z) result.z = elfGetBezierCurveValue(curve, x);
	}

	return result;
}

ELF_API elfVec3f ELF_APIENTRY elfGetIpoRot(elfIpo* ipo, float x)
{
	elfBezierCurve* curve;
	elfVec3f result;

	memset(&result, 0x0, sizeof(elfVec3f));

	for(curve = (elfBezierCurve*)elfBeginList(ipo->curves); curve;
		curve = (elfBezierCurve*)elfGetListNext(ipo->curves))
	{
		if(curve->curveType == ELF_ROT_X) result.x = elfGetBezierCurveValue(curve, x);
		else if(curve->curveType == ELF_ROT_Y) result.y = elfGetBezierCurveValue(curve, x);
		else if(curve->curveType == ELF_ROT_Z) result.z = elfGetBezierCurveValue(curve, x);
	}

	return result;
}

ELF_API elfVec3f ELF_APIENTRY elfGetIpoScale(elfIpo* ipo, float x)
{
	elfBezierCurve* curve;
	elfVec3f result;

	memset(&result, 0x0, sizeof(elfVec3f));

	for(curve = (elfBezierCurve*)elfBeginList(ipo->curves); curve;
		curve = (elfBezierCurve*)elfGetListNext(ipo->curves))
	{
		if(curve->curveType == ELF_SCALE_X) result.x = elfGetBezierCurveValue(curve, x);
		else if(curve->curveType == ELF_SCALE_Y) result.y = elfGetBezierCurveValue(curve, x);
		else if(curve->curveType == ELF_SCALE_Z) result.z = elfGetBezierCurveValue(curve, x);
	}

	return result;
}

ELF_API elfVec4f ELF_APIENTRY elfGetIpoQua(elfIpo* ipo, float x)
{
	elfBezierCurve* curve;
	elfVec4f result;

	memset(&result, 0x0, sizeof(elfVec4f));

	for(curve = (elfBezierCurve*)elfBeginList(ipo->curves); curve;
		curve = (elfBezierCurve*)elfGetListNext(ipo->curves))
	{
		if(curve->curveType == ELF_QUA_X) result.x = elfGetBezierCurveValue(curve, x);
		else if(curve->curveType == ELF_QUA_Y) result.y = elfGetBezierCurveValue(curve, x);
		else if(curve->curveType == ELF_QUA_Z) result.z = elfGetBezierCurveValue(curve, x);
		else if(curve->curveType == ELF_QUA_W) result.w = elfGetBezierCurveValue(curve, x);
	}

	return result;
}

