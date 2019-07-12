#include "stlread.h"
#include "generateray.h"
using namespace std;
#pragma once

class CIntersection
{
public:
	CIntersection();
	void SetValue(SRay _r, CTri _tri);
	~CIntersection();
	SRay r;
	CTri tri;
	CEdge edge[3];
	float orientation[3];
	bool intsec;
	float cross_z;                        //z coordinate of cross point

public:
	void intersection();
	void computecrosspoint();
};

