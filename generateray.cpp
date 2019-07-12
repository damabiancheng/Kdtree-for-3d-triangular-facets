#include <vector>
#include <stdio.h>
#include "generateray.h"

#define MAX_DEPTH 6
#define MAX_NUM 200

CPoint::CPoint()
{

}

void CPoint::SetValue(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

CPoint::~CPoint()
{

}


CDomain::CDomain()
{

}

CDomain::~CDomain()
{

}

CDomain::CDomain(CPoint _pmin, CPoint _pmax, float _step)
{
	pmin = _pmin;
	pmax = _pmax;
	step = _step;
	ptcnumber[0] = (int) ((pmax.x - pmin.x)/step);
	ptcnumber[1] = (int) ((pmax.y - pmin.y)/step);
	ptcnumber[2] = (int) ((pmax.z - pmin.z)/step);
}


bool CDomain::GenerateRay(float _x, float _y)
{
	r.x = _x;
	r.y = _y;
	return 1;
}


KdNode* KdNode::InsertAsLc(CDomain * d, vector<int> v)
{
	return lc = new KdNode(*d, v, this);
}

KdNode* KdNode::InsertAsRc(CDomain * d, vector<int> v)
{
	return rc = new KdNode(*d, v, this);
}

KdTree::KdTree(CDomain d, vector<CTri> t)
{
	compute_domain = d;
	tri_vec = t;
	depth = 0;
}

KdNode* KdTree::GetRoot()
{
	return root;
}

void KdTree::createTree()
{
	for (int i = 0; i < tri_vec.size(); i++)
	{
		index_vec.push_back(i);
	}
	root = CreateTreeNode(compute_domain, index_vec, 0);
}

bool KdTree::Is_intersect(const CDomain& d, const CTri& t)
{
	return !(((d.pmax.x < t.x1) || (d.pmin.y > t.y2) ||
		(d.pmin.x > t.x2) || (d.pmax.y < t.y1)));
}


KdNode* KdTree::CreateTreeNode(CDomain d, vector<int> v, int dim)
{
	if (v.empty())
		return NULL;
	if (v.size() < MAX_NUM)
		return new KdNode(d, v);

	CPoint lpmin, lpmax, rpmin, rpmax;
	vector<int> lv, rv;
	//create left domain
	lpmin.SetValue(d.pmin.x, d.pmin.y, 0);
	if (dim % 2)
		lpmax.SetValue((d.pmin.x + d.pmax.x) / 2, d.pmax.y, 0);
	else
		lpmax.SetValue(d.pmax.x, (d.pmin.y + d.pmax.y) / 2, 0);
	CDomain* ld = new CDomain(lpmin, lpmax, 0.1);
	//create right domain
	rpmax.SetValue(d.pmax.x, d.pmax.y, 0);
	if (dim % 2)
		rpmin.SetValue((d.pmin.x + d.pmax.x) / 2, d.pmin.y, 0);
	else
		rpmin.SetValue(d.pmin.x, (d.pmin.y + d.pmax.y) / 2, 0);
	CDomain* rd = new CDomain(rpmin, rpmax, 0.1);
	//compute left vector
	for (int i = 0; i < v.size(); i++)
	{
		if (Is_intersect(*ld, tri_vec[v[i]]))
			lv.push_back(v[i]);
	}
	//compute right vector
	for (int i = 0; i < v.size(); i++)
	{
		if (Is_intersect(*rd, tri_vec[v[i]]))
			rv.push_back(v[i]);
	}

	KdNode* node = new KdNode(d, v);
//	if (v.size() < MAX_NUM)
//		return node;

	node->lc = CreateTreeNode(*ld, lv, dim + 1);
	if (node->lc != NULL)
		node->lc->parent = node;

	node->rc = CreateTreeNode(*rd, rv, dim + 1);
	if (node->rc != NULL)
		node->rc->parent = node;

	return node;
}
