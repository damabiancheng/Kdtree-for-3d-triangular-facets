//#include "stlread.h"
#include "intersection.h"
//#include "generateparticle.h"

CIntersection::CIntersection()
{
	intsec = 0;
}

CIntersection::~CIntersection()
{

}

void CIntersection::SetValue(SRay _r, CTri _tri)
{
	r = _r;
	tri = _tri;
	intsec = 0;
	edge[0].SetValue(tri.v1, tri.v2);
	edge[1].SetValue(tri.v2, tri.v3);
	edge[2].SetValue(tri.v3, tri.v1);
}

void CIntersection::intersection()
{
	for(int i=0; i < 3; i++)
	{
		orientation[i] = (edge[i].v1.x - r.x)*(edge[i].v2.y - r.y) - (edge[i].v2.x - r.x)*(edge[i].v1.y - r.y);
	}

	if((orientation[0] > 0 && orientation[1] > 0 && orientation[2] > 0)||
		(orientation[0] < 0 && orientation[1] < 0 && orientation[2] < 0))
	{
		intsec = 1;
	}
}

void CIntersection::computecrosspoint()
{
	float a1, b1, c1, a2, b2, c2, a3, b3, c3;
	a1 = r.x - tri.v1.x;
	b1 = r.y - tri.v1.y;

	a2 = tri.v2.x - tri.v1.x;
	b2 = tri.v2.y - tri.v1.y;
	c2 = tri.v2.z - tri.v1.z;

	a3 = tri.v3.x - tri.v1.x;
	b3 = tri.v3.y - tri.v1.y;
	c3 = tri.v3.z - tri.v1.z;

	c1 = (b3*c2*a1 + c3*a2*b1 - a1*b2*c3 - b1*c2*a3)/(a2*b3 - a3*b2);
	cross_z = c1 + tri.v1.z;
}
