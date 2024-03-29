﻿#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#define _max 100
int g_iVisited[_max];
int g_iSoMienLienThong;
int B[_max];

struct Graph {
	int _iSoDinh;
	int A[_max][_max];
};
void visit(const Graph& g, int i, int nLabel) {
	// tạo một hàng đợi được khởi tạo chỉ gồm một đỉnh i
	int* queue = new int[g._iSoDinh];
	queue[0] = i;
	int queueCount = 1; // chỉ có một phần tử trong hàng đợi
	int queueindex = 0; // chỉ số đỉnh đang duyệt trong hàng đợi
	// gán nhãn nLabel cho đỉnh i
	g_iVisited[i] = nLabel;
	// duyệt tất cả các đỉnh trong hàng đợi
	while (queueindex < queueCount)
	{
		// lấy đỉnh x từ hàng đợi
		int x = queue[queueindex];
		queueindex++;
		// xét tất cả đỉnh j chưa được duyệt và có nối với x
		for (int j = 0; j < g._iSoDinh; j++)
			if ((g_iVisited[j] == 0) && (g.A[x][j] != 0))
			{
				// đưa j vào hàng đợi
				queue[queueCount] = j;
				queueCount++;
				// gán nhãn nLabel cho đỉnh j
				g_iVisited[j] = nLabel;
			}
	}
	delete queue;
}
void taoGraph(const string& sFileInput, Graph& g) {
	ifstream fcin{ sFileInput};
	if (fcin.is_open()) {
		fcin >> g._iSoDinh;
		for (int i = 0; i < g._iSoDinh; i++)
			for (int j = 0; j < g._iSoDinh; j++)
				fcin >> g.A[i][j];
		fcin.close();
	}
	else cout << "Khong mo duoc file";
}
void xetLienThong(const Graph&  g)
{
	// khởi tạo nhãn cho tất cả các đỉnh là chưa duyệt
	for (int i = 0; i < g._iSoDinh; i++)
		g_iVisited[i] = 0;
	// đặt số miền liên thông ban đầu la 0
	g_iSoMienLienThong = 0;
	// dùng một vòng for i để tìm đỉnh chưa xét, gọi hàm duyệt cho đỉnh này
	for (int i = 0; i < g._iSoDinh; i++)
		if (g_iVisited[i] == 0) {
			g_iSoMienLienThong++;
			visit(g, i, g_iSoMienLienThong); // g_iSoMienLienThong là nhãn sẽ gán
			                                 // cho các đỉnh trong lần duyệt này
		}
}
void inThanhPhanLienThong(const string& sFileOutput, const Graph& g)
{
	ofstream fcout{ sFileOutput };
	// in ra số miền liên thông
	fcout << ((g_iSoMienLienThong > 1) ? "KHONG LIEN THONG\n" : "LIEN THONG\n");
	// dùng vòng lặp từ 1 đến g_iSoMienLienThong để in ra từng miền liên thông
	fcout << "So mien lien thong: " << g_iSoMienLienThong << '\n';
	fcout << g_iSoMienLienThong << '\n';
	for (int i = 1; i <= g_iSoMienLienThong; i++)
	{
		fcout << "Mien lien thong thu " << i << ": ";
		// xét tất cả các đỉnh, nếu có nhãn trùng với g_iSoMienLienThong thì in ra
		for (int j = 0; j < g._iSoDinh; j++)
			if (g_iVisited[j] == i)
				fcout << j << " ";
		fcout << '\n';
	}
	if (g_iSoMienLienThong > 1)
		fcout << "Can toi thieu " << g_iSoMienLienThong - 1 << " canh de do thi lien thong.\n";
	fcout.close();
}
void xuatThanhPhanLienThong(const Graph& g)
{
	cout << ((g_iSoMienLienThong > 1) ? "KHONG LIEN THONG\n" : "LIEN THONG\n");
	// dùng vòng lặp từ 1 đến g_iSoMienLienThong để in ra từng miền liên thông
	cout << "So mien lien thong: " << g_iSoMienLienThong << '\n';
	for (int i = 1; i <= g_iSoMienLienThong; i++)
	{
		cout << "Mien lien thong thu " << i << ": ";
		// xét tất cả các đỉnh, nếu có nhãn trùng với g_iSoMienLienThong thì in ra
		for (int j = 0; j < g._iSoDinh; j++)
			if (g_iVisited[j] == i)
				cout << j << " ";
		cout << '\n';
	}
}
void xetCanhDeDoThiLienThong(int temp, Graph g) {
	for (int i = 0; i < g._iSoDinh; i++) {
		if (g_iVisited[i] == temp + 1) {
			B[temp] = i;
			if (temp == g_iSoMienLienThong - 1) {
				for (int j = 0; j <= temp; j++) {
					cout << B[j];
					if (j < temp) cout << " -> ";
				}
				cout << '\n';
			}
			else xetCanhDeDoThiLienThong(temp + 1, g);
		}
	}
}
void xuatCanhDeDoThiLienThong(Graph g) {
	cout << "Can toi thieu " << g_iSoMienLienThong - 1 << " canh de do thi lien thong.\n";
	cout << "Chon mot cap canh trong cac lua chon sau day de do thi lien thong:\n";
	xetCanhDeDoThiLienThong(0, g);
}
int main() {
	Graph g;
	string sFileInput = "DoThi_TH02.txt";;
	taoGraph(sFileInput, g);
	string sFileOutput = "Xuat_DoThi_TH02.txt";
	xetLienThong(g);
    //inThanhPhanLienThong(sFileOutput, g);
	xuatThanhPhanLienThong(g);
	xuatCanhDeDoThiLienThong(g);
}