// PtcGen.cpp : Defines the entry point for the console application.
//

#include "stlread.h"
#include "generateray.h"
#include "intersection.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sys/time.h>
//#pragma once

void TransLevel(KdNode* root, int level)
{
	if (root == NULL)
		return;
	else
	{
		if (level == 0)
			printf("%d  ", root->tri_index.size());
		else
		{
			TransLevel(root->lc, level - 1);
			TransLevel(root->rc, level - 1);
		}
	}
}

void InOrder(KdNode* root)
{
	if (root != NULL)
	{
		InOrder(root->lc);
		std::cout << root->tri_index.size() << endl;
		InOrder(root->rc);
	}
}

int main(int argc, char* argv[])
{
	CPoint p1, p2;
	CSTLModel stlmodel;
	SRay ray;

	stlmodel.LoadStlFile("./timetest/4970.stl");
	
   struct timeval start1, end1;
   gettimeofday(&start1, NULL);

   CPoint pmin, pmax;
	pmin.SetValue(0, 0, 0);
	pmax.SetValue(100, 100, 100);
	float size = 0.1;
	CDomain domain(pmin, pmax, size);
	vector<int> count_tri;

	for (int i = 0; i < stlmodel.arraytri.size(); i++)
	{
		stlmodel.arraytri[i].Boundingbox();
	}

	KdTree kdtree(domain, stlmodel.arraytri);
	kdtree.createTree();
	for (int i = 0; i < 20; i++)
	{
		printf("level: %d\n", i);
		TransLevel(kdtree.GetRoot(), i);
		printf("\n");
	}
	
//	InOrder(kdtree.GetRoot());


  gettimeofday(&end1, NULL);
	printf("ray casting time=%f\n", (double)(end1 .tv_usec - start1.tv_usec));
	return 0;
}

