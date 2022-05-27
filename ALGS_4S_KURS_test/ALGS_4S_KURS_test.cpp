#include "pch.h"
#include "CppUnitTest.h"
#include "../ALGS_4S_KURS/main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ALGS4SKURStest
{
	TEST_CLASS(ALGS4SKURStest)
	{
	public:
		
		TEST_METHOD(Path1)
		{

			List<Edge> edgeList;
			edgeList.push_back(Edge("S", "A", 16));
			edgeList.push_back(Edge("S", "B", 13));
			edgeList.push_back(Edge("A", "B", 10));
			edgeList.push_back(Edge("B", "A", 4));
			edgeList.push_back(Edge("A", "C", 12));
			edgeList.push_back(Edge("C", "B", 9));
			edgeList.push_back(Edge("B", "D", 14));
			edgeList.push_back(Edge("D", "C", 7));
			edgeList.push_back(Edge("C", "T", 20));
			edgeList.push_back(Edge("D", "T", 4));

			double maxpath = findMaxFlow(edgeList, "S", "T");

			Assert::AreEqual(maxpath, 23.0);
		}


		TEST_METHOD(Path2)
		{
			List<Edge> edgeList;
			edgeList.push_back(Edge("S", "O", 3));
			edgeList.push_back(Edge("S", "P", 3));
			edgeList.push_back(Edge("O", "Q", 3));
			edgeList.push_back(Edge("O", "P", 2));
			edgeList.push_back(Edge("P", "R", 2));
			edgeList.push_back(Edge("Q", "R", 4));
			edgeList.push_back(Edge("Q", "T", 2));
			edgeList.push_back(Edge("R", "T", 3));

			double maxpath = findMaxFlow(edgeList, "S", "T");

			Assert::AreEqual(maxpath, 5.0);
		}
	};
}
