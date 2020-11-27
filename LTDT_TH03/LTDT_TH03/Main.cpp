#include<iostream>
#include <iomanip>
#include <fstream>
using namespace std;
struct DoThi {
	int iSoDinh;
	int iMaTran[100][100];
	int LuuVet[100];
	int visited[100];
};

struct QUEUE {
	int size;
	int a[100];
};

void KhoiTao(QUEUE& q) { q.size = 0; }

bool Them(int k, QUEUE& q)
{
	if (q.size + 1 > 100) return false;
	q.a[q.size] = k;
	q.size++;
	return true;
}

bool KiemTraRong(QUEUE q)
{
	return (q.size == 0);
}

bool Lay(int& v, QUEUE& q)
{
	if (KiemTraRong(q)) return false;
	v = q.a[0];
	for (int i = 0; i < q.size - 1; i++)
		q.a[i] = q.a[i + 1];
	q.size--;
	return true;
}

void BFS(int s, DoThi& g)
{
	QUEUE q;
	KhoiTao(q);
	Them(s, q);
	while (!KiemTraRong(q))
	{
		Lay(s, q);
		g.visited[s] = 1;
		for (int i = 0; i < g.iSoDinh; i++)
			if (g.visited[i] == 0 && g.iMaTran[s][i] != 0)
			{
				Them(i, q);
				g.LuuVet[i] = s;
			}
	}
}
void duyetBFS(int s, int f, DoThi& g)
{
	for (int i = 0; i < g.iSoDinh; i++)
	{
		g.visited[i] = 0;
		g.LuuVet[i] = -1;
	}
	BFS(s, g);
	if (g.visited[f] == 1)
	{
		int j = f;
		while (j != s)
		{
			cout << j + 1 << " <- ";
			j = g.LuuVet[j];
		}
		cout << s + 1 << endl;
	}
	else
		cout << "Khong co duong di tu dinh " << s << " den dinh " << f << endl;
}

void nhapMaTranKe(string duongdan, DoThi& dt) {
	ifstream fcin;
	fcin.open(duongdan);
	if (fcin.is_open()) {
		fcin >> dt.iSoDinh;
		for (int i = 0; i < dt.iSoDinh; i++) {
			for (int j = 0; j < dt.iSoDinh; j++) {
				fcin >> dt.iMaTran[i][j];
			}
		}
		fcin.close();
	}
	else {
		cout << "Khong mo duoc file";
		exit(0);
	}
}
void xuatMaTranKe(DoThi& dt) {
	cout << "So dinh cua do thi la: " << dt.iSoDinh << endl;
	for (int i = 0; i < dt.iSoDinh; i++) {
		for (int j = 0; j < dt.iSoDinh; j++) {
			cout << setw(6) << dt.iMaTran[i][j];
		}
		cout << endl;
	}
}
void DFS(int s, DoThi& g)
{
	g.visited[s] = 1;
	for (int i = 0; i < g.iSoDinh; i++) {
		if (g.visited[i] == 0 && g.iMaTran[s][i] != 0)
		{
			g.LuuVet[i] = s;
			DFS(i, g);
		}
	}
}

void duyetDFS(int s, int f, DoThi& g)
{
	for (int i = 0; i < g.iSoDinh; i++)
	{
		g.visited[i] = 0;
		g.LuuVet[i] = -1;
	}
	DFS(s, g);
	if (g.visited[f] == 1)
	{
		int j = f;
		while (j != s)
		{
			cout << j + 1 << " <- ";
			j = g.LuuVet[j];
		}
		cout << s + 1 << endl;
	}
	else
		cout << "Khong co duong di tu dinh " << s + 1 << " den dinh " << f + 1 << endl;
}

int main() {
	DoThi g;
	string duongdan = "MaTranDoThi_TH03.txt";
	nhapMaTranKe(duongdan, g);
	int dinhdi, dinhden, luachon;
	cout << "Nhap dinh di: " << endl;
	cin >> dinhdi;
	cout << "Nhap dinh den: " << endl;
	cin >> dinhden;
	while (true) {
		cout << "Chon cach duyet: \n 1: DFS\n 2: BFS\n";
		cin >> luachon;
		if (luachon == 1) {
			duyetDFS(dinhdi - 1, dinhden - 1, g);
			break;
		}
		else if (luachon == 2) {
			duyetBFS(dinhdi - 1, dinhden - 1, g);
			break;
		}
	}
}