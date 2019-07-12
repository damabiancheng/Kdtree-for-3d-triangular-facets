#include "stlread.h"
#include <vector>
#include <algorithm>
using namespace std;
#pragma once


class CPoint
{
public:
	float x,y,z;
public:
	CPoint();
	void SetValue(float _x, float _y, float _z);
	~CPoint();
};

struct SRay
{
	float x, y;              //start point of ray

};
class CDomain
{
public:
	CPoint pmin,pmax;
	float step;
	int ptcnumber[3];
	SRay r;
public:
	CDomain();
	CDomain(CPoint _pmin, CPoint _pmax, float _step);
	~CDomain();
	bool GenerateRay(float _x, float _y);
};

struct KdNode {
	CDomain domain;
	vector<int> tri_index;
	KdNode* parent;
	KdNode* lc;
	KdNode* rc;
	int height;

	KdNode() :
		parent(NULL), lc(NULL), rc(NULL), height(0) {}
	KdNode(CDomain d, vector<int> v, KdNode* parent = NULL, KdNode* lc = NULL, KdNode* rc = NULL, int h = 0) :
		domain(d), tri_index(v), parent(parent), lc(lc), rc(rc), height(h) { }
	KdNode* InsertAsLc(CDomain *, vector<int>);
	KdNode* InsertAsRc(CDomain *, vector<int>);
};

class KdTree
{
private:
	int dimension;
	KdNode * root;
	CDomain compute_domain;
	vector<CTri> tri_vec;
	vector<int> index_vec;
	int depth;
public:
	KdTree(CDomain d, vector<CTri> t);
	KdNode* GetRoot();
	void createTree();
	bool Is_intersect(const CDomain& d, const CTri& t);
	KdNode * CreateTreeNode(CDomain, vector<int>, int);

};
