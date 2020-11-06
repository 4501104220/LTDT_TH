#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#define _max 100
using namespace std;
//Cau truc do thi gom so dinh va ma tran ke
struct Graph {
	int _iSoDinh;
	int a[_max][_max];
};
//Nhap do thi tu file test1.txt
void createGraph(Graph& g) {
	ifstream fcin;
	fcin.open("test1.txt");
	if (fcin.is_open()) {
		fcin >> g._iSoDinh;
		for (int i = 0; i < g._iSoDinh; i++)
			for (int j = 0; j < g._iSoDinh; j++)
				fcin >> g.a[i][j];
		fcin.close();
	}
	else
		cout << "Khong mo duoc file";
}
//Kiem tra do thi co huong
bool isDirectedGraph(const Graph& g) {
	for (int i = 1; i < g._iSoDinh; i++)
		for (int j = 0; j < i; j++)
			if (g.a[i][j] != g.a[j][i]) return true;
	return false;
}
//kiem tra ma tran hop le
bool validGraph(const Graph& g) {
	for (int i = 0; i < g._iSoDinh; i++)
		if (g.a[i][i] != 0)return false;
	return true;
}
//Lay gia tri so canh
int getSoCanh(const Graph& g) {
	int iSoCanh = 0;
	for (int i = 0; i < g._iSoDinh; i++)
		for (int j = 0; j < g._iSoDinh; j++)
			iSoCanh += g.a[i][j];
	if (!isDirectedGraph(g)) return iSoCanh / 2;
	return iSoCanh;
}
//Tao mang cua dinh
vector<int> degArray(const Graph& g) {
	vector<int> res(g._iSoDinh);
	if (isDirectedGraph(g)) {
		for (int i = 0; i < g._iSoDinh; i++)
			for (int j = 0; j < g._iSoDinh; j++)
				res[i] += g.a[i][j] + g.a[j][i];
	}
	else {
		for (int i = 1; i < g._iSoDinh; i++)
			for (int j = 0; j < i; j++) {
				res[i] += g.a[i][j];
				res[j] += g.a[i][j];
			}
	}
	return res;
}
//Ham main
int main() {
	Graph g;
	createGraph(g);
	//Kiem tra tinh hop le cua do thi
	cout << "Kiem tra tinh hop le do thi:\n";
	cout << (validGraph(g) ? "Hop le\n" : "Khong hop le\n");
	cout<<"Do thi " << (isDirectedGraph(g) ? "co" : "vo") << " huong\n";
	if (validGraph(g)) {
		cout << "So canh va so dinh cua do thi:\n";
		//So canh cua do thi
		cout << "So canh: " << getSoCanh(g) << "\n";
		//So dinh cua do thi
		cout << "So dinh: " << g._iSoDinh << "\n";
		//Bac cua tat ca cac dinh
		cout << "Xuat bac cua tat ca cac dinh:\n";
		vector<int>degs = degArray(g);
		for (int i = 0; i < g._iSoDinh; i++)
			cout << "Dinh thu " << i + 1 << " co bac la: " << degs[i] <<"\n";
		//Dinh bac lon nhat
		{
			cout << "Dinh bac lon nhat: ";
			auto max = max_element(degs.begin(), degs.end());
			for (int i = 0; i < g._iSoDinh; i++)
				if (degs[i] == *max) cout << i + 1 << ' ';
		}
		cout << '\n';
		//Dinh bac nho nhat
		{
			cout << "Dinh bac nho nhat: ";
			auto min = min_element(degs.begin(), degs.end());
			for (int i = 0; i < g._iSoDinh; i++)
				if (degs[i] == *min) cout << i + 1 << ' ';
		}
		cout << '\n';
		//Dinh bac le
		{
			bool bFlag = false;
			cout << "Dinh bac le la : ";
			for (int i = 0; i < degs.size(); i++)
				if (degs[i] % 2 == 1) {
					cout << i + 1 << ' ';
					bFlag = true;
				}
			if (!bFlag) cout << "khong co.";
		}
		cout << '\n';
		//Dinh bac chan
		{
			bool bFlag = false;
			cout << "Dinh bac chan la : ";
			for (int i = 0; i < degs.size(); i++)
				if (degs[i] % 2 == 0) {
					cout << i + 1 << ' ';
					bFlag = true;
				}
			if (!bFlag) cout << "khong co.";
		}
		cout << '\n';
		//Dinh co lap
		{
			bool bFlag = false;
			cout << "Dinh co lap la: ";
			for (int i = 0; i < degs.size(); i++)
				if (degs[i] == 0) {
					cout << i + 1 << ' ';
					bFlag = true;
				}
			if (!bFlag) cout << "khong co.";
		}
		cout << '\n';
		//Dinh treo
		{
			bool bFlag = false;
			cout << "Dinh treo la: ";
			for (int i = 0; i < degs.size(); i++)
				if (degs[i] == 1) {
					cout << i + 1 << ' ';
					bFlag = true;
				}
			if (!bFlag) cout << "khong co.";
		}
	}
}