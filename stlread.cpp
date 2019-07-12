#include <vector>
#include <stdio.h>
#include "stlread.h"
using namespace std;
#pragma once

CVertex::CVertex()
{

}
CVertex::CVertex(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}
CVertex::~CVertex()
{

}

CTri::CTri()
{

}

CTri::CTri(CVertex _v1, CVertex _v2, CVertex _v3)
{
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	x1 = 0;
	x2 = 0;
	y1 = 0;
	y2 = 0;
}
void CTri::Setvalue(CVertex _v1, CVertex _v2, CVertex _v3)
{
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
}
void CTri::Boundingbox()
{
	x1 = v1.x;
	if (x1>v2.x)
	{
		x1 = v2.x;
	}
	if (x1>v3.x)
	{
		x1 = v3.x;
	}

	y1 = v1.y;
	if (y1>v2.y)
	{
		y1 = v2.y;
	}
	if (y1>v3.y)
	{
		y1 = v3.y;
	}

	x2 = v1.x;
	if (x2<v2.x)
	{
		x2 = v2.x;
	}
	if (x2<v3.x)
	{
		x2 = v3.x;
	}

	y2 = v1.y;
	if (y2<v2.y)
	{
		y2 = v2.y;
	}
	if (y2<v3.y)
	{
		y2 = v3.y;
	}
}

CTri::~CTri()
{

}

CEdge::CEdge()
{

}

CEdge::~CEdge()
{

}

void CEdge::SetValue(CVertex _v1, CVertex _v2)
{
	v1 = _v1;
	v2 = _v2;
}

CSTLModel::CSTLModel()
{

}

CSTLModel::~CSTLModel()
{

}

bool CSTLModel::LoadStlFile(const char* filename)
{
    FILE* f = fopen(filename, "rt");
    char buffer[1024];
	int n = 0;
    CVertex vertex;
	CTri tri;
	trinumber = 0;
    CVertex v0(0,0,0), v1(0,0,0), v2(0,0,0);
    while(fgets(buffer, sizeof(buffer), f))
    {
        if (sscanf(buffer, " vertex %f %f %f", &vertex.x, &vertex.y, &vertex.z) == 3)
        {
            n++;
            switch(n)
            {
            case 1:
                v0 = vertex;
                break;
            case 2:
                v1 = vertex;
                break;
            case 3:
                v2 = vertex;
				tri.Setvalue(v0, v1, v2);
				arraytri.push_back(tri);
				trinumber++;
                n = 0;
                break;
            }
			
        }
		
		
    }
    fclose(f);
    return 1;
}

void CSTLModel::GenerateTree()
{
	int depth = 0;
	for (int i=0; i<arraytri.size(); i++)
	{
		root->tri.push_back(arraytri[i]);
	}
}
