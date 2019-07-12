#include <vector>

#pragma once

using namespace std;

class CVertex
{
public:
	CVertex();
	CVertex(float _x, float _y, float _z);
	~CVertex();
public:
	float x;
	float y;
	float z;
	
};

class CTri
{
public:
	CTri();
	CTri(CVertex _v1, CVertex _v2, CVertex _v3);
	~CTri();
	void Setvalue(CVertex _v1, CVertex _v2, CVertex _v3);
	void Boundingbox();
public:
	CVertex v1;
	CVertex v2;
	CVertex v3;
	float x1,y1,x2,y2;
	
};

class CEdge
{
public:
	CEdge();
	~CEdge();
	void SetValue(CVertex _v1, CVertex _v2);
public:
	CVertex v1;
	CVertex v2;
};

struct Snode 
{
	vector<CTri> tri;
	Snode* left;
	Snode* right;
};


class CSTLModel
{
public:
	CSTLModel();
	~CSTLModel();
public:
	vector<CTri> arraytri;
	long int trinumber;
	Snode* root;
public:
	bool LoadStlFile(const char* filename);
	void GenerateTree();
};
