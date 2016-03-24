#include "stdafx.h"
#include "CppUnitTest.h"
#include "bellman-ford-plain.cpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{	
	ifstream in_data, out_data;

	int n, m, v;
	vector<edge> e;

	string expected = "";
	
	void read_in_data(string filename_in) {
		in_data.open(filename_in, ios::in);
		if (in_data.is_open()) {
			in_data >> n >> m;
			for (int i = 0; i < m; ++i) {
				struct edge current_edge;
				in_data >> current_edge.a >> current_edge.b >> current_edge.cost;
				--current_edge.a;
				--current_edge.b;
				e.push_back(current_edge);
			}
			in_data >> v;
			--v;
			in_data.close();
		}
	}

	void read_out_data(string filename_out) {
		out_data.open(filename_out, ios::in);
		if (out_data.is_open()) {
			getline(out_data, expected);
			expected += '\n';
			out_data.close();
		}
	}

	void vipe_data() {
		n = m = v = 0;
		e.clear();
		expected = "";
	}

	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test1)
		{
			vipe_data();
			read_in_data("..\\tests\\1_in.txt");
			read_out_data("..\\tests\\1_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test2)
		{
			vipe_data();
			read_in_data("..\\tests\\2_in.txt");
			read_out_data("..\\tests\\2_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test3_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\3_neg_cycle_in.txt");
			read_out_data("..\\tests\\3_neg_cycle_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test4)
		{
			vipe_data();
			read_in_data("..\\tests\\4_in.txt");
			read_out_data("..\\tests\\4_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test5_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\5_neg_cycle_in.txt");
			read_out_data("..\\tests\\5_neg_cycle_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test100)
		{
			vipe_data();
			read_in_data("..\\tests\\100_in.txt");
			read_out_data("..\\tests\\100_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test100_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\100_neg_cycle_in.txt");
			read_out_data("..\\tests\\100_neg_cycle_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test1k_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_neg_cycle_in.txt");
			read_out_data("..\\tests\\1k_neg_cycle_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test3k_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_neg_cycle_in.txt");
			read_out_data("..\\tests\\3k_neg_cycle_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}

		TEST_METHOD(Test100_full)
		{
			vipe_data();
			read_in_data("..\\tests\\100_full_in.txt");
			read_out_data("..\\tests\\100_full_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}
		TEST_METHOD(Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			Assert::AreEqual(BFplain(n, m, e, v), expected);

		}
	};

	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(Threads2Test1)
		{
			vipe_data();
			read_in_data("..\\tests\\1_in.txt");
			read_out_data("..\\tests\\1_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);
		}

		TEST_METHOD(Threads2Test2)
		{
			vipe_data();
			read_in_data("..\\tests\\2_in.txt");
			read_out_data("..\\tests\\2_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test3_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\3_neg_cycle_in.txt");
			read_out_data("..\\tests\\3_neg_cycle_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test4)
		{
			vipe_data();
			read_in_data("..\\tests\\4_in.txt");
			read_out_data("..\\tests\\4_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test5_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\5_neg_cycle_in.txt");
			read_out_data("..\\tests\\5_neg_cycle_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test100)
		{
			vipe_data();
			read_in_data("..\\tests\\100_in.txt");
			read_out_data("..\\tests\\100_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test1k)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_in.txt");
			read_out_data("..\\tests\\1k_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test3k)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_in.txt");
			read_out_data("..\\tests\\3k_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test100_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\100_neg_cycle_in.txt");
			read_out_data("..\\tests\\100_neg_cycle_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test1k_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\1k_neg_cycle_in.txt");
			read_out_data("..\\tests\\1k_neg_cycle_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test3k_neg_cycle)
		{
			vipe_data();
			read_in_data("..\\tests\\3k_neg_cycle_in.txt");
			read_out_data("..\\tests\\3k_neg_cycle_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads2Test100_full)
		{
			vipe_data();
			read_in_data("..\\tests\\100_full_in.txt");
			read_out_data("..\\tests\\100_full_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}
		TEST_METHOD(Threads2Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 2, into), expected);

		}

		TEST_METHOD(Threads4Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 4, into), expected);

		}

		TEST_METHOD(Threads8Test500_semifull)
		{
			vipe_data();
			read_in_data("..\\tests\\500_semifull_in.txt");
			read_out_data("..\\tests\\500_semifull_out.txt");
			vector<vector<edge>> into(n);
			count_incoming_edges(e, into, m);
			Assert::AreEqual(BFThreads(n, m, e, v, 8, into), expected);

		}
	};

	TEST_CLASS(UnitTest3)
	{
	public:

		/*TEST_METHOD(OpenMPTest1)
		{
		vipe_data();
		read_in_data("..\\tests\\1_in.txt");
		read_out_data("..\\tests\\1_out.txt");
		Assert::AreEqual(BFplain(n, m, e, v), expected);

		}*/
	};
}