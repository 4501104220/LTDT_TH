#include<iostream>
#include<fstream>
using namespace std;
struct GRAPH
{
	int iSoDinh;//so dinh do thi
	int a[100][100];//ma tran ke	
	int visited[100]; //danh dau dinh i da xet hay chua, 0 la chua xet
};
struct CANH
{
	int u;//Dinh thu nhat
	int v;//Dinh thu hai
	int trongso;
};

CANH T[100];//Mang luu c�c canh trong thuat to�n Prim

void nhapMaTranKe(string duongdan, GRAPH& dt) {
	ifstream inp;
	inp.open(duongdan);
	if (inp.is_open()) {
		inp >> dt.iSoDinh;
		for (int i = 0; i < dt.iSoDinh; i++) {
			for (int j = 0; j < dt.iSoDinh; j++) {
				inp >> dt.a[i][j];
			}
		}
		inp.close();
	}
	else {
		cout << "Khong mo duoc file";
		exit(0);
	}
}
void Prim(char v, GRAPH g, bool type)
{
	//B1: G�n so canh cua c�y khung ban dau l� 0
	int nT = 0;
	//B2: Khoi tao nh�n c�c dinh l� chua duyet (0)
	for (int i = 0; i < g.iSoDinh; i++)
		g.visited[i] = 0;

	//B3: ��nh dau dinh 0 l� d� duyet
	g.visited[v - 'A'] = 1;

	while (nT < g.iSoDinh - 1)//neu bang n -1 canh th� dung (*)	
	{
		CANH canhnhonhat;//d�ng de luu tru canh nho nhat tu mot dinh da x�t toi dinh chua x�t
		int tmp = -1;	//(*)
		for (int i = 0; i < g.iSoDinh; i++)
			if (g.visited[i] == 0) //neu l� dinh chua duyet. �ieu kien d�ng khi j thuoc tap Y hay V\Y
			{
				for (int j = 0; j < g.iSoDinh; j++)
					if (g.visited[j] == 1 && (g.a[i][j] != 0))
					{
						if ((type == true && (tmp == -1 || g.a[i][j] < tmp)) || (type == false && (tmp == -1 || g.a[i][j] > tmp)))
						{
							tmp = g.a[i][j];
							canhnhonhat.u = i;
							canhnhonhat.v = j;
							canhnhonhat.trongso = g.a[i][j];
						}
					}
			}

		//Th�m canh nho nhat v�o tap T
		T[nT] = canhnhonhat;
		nT++;//tang so canh l�n 1

		g.visited[canhnhonhat.u] = 1;//(*)

	}
	char c = 'A';
	//T?ng tr?ng s? c?a c�y khung
	int sum = 0;
	if (type) cout << "\nCay khung nho nhat cua do thi la: " << endl;
	else cout << "\nCay khung lon nhat cua do thi la: " << endl;
	for (int i = 0; i < nT; i++)
	{
		cout << "(" << char(c + T[i].v) << ", " << char(c + T[i].u) << ") ";
		sum += T[i].trongso;
	}
	cout << endl;
	cout << "Tong gia tri cua cay la: " << sum << endl;
}
int main() {
	GRAPH g;
	char c;
	string duongdan = "DoThi_TH04.txt";
	nhapMaTranKe(duongdan, g);

	while (true) {
		cout << "nhap dinh bat dau: (vd A B C D)\n";
		cin >> c;
		if (c >= 'A' && c <= char(65 + g.iSoDinh - 1)) {
			Prim(c, g, true);
			Prim(c, g, false);
			return 0;
		}
		else {
			cout << "Khong hop le" << endl;
		}
	}
}
//Cau 3 (*) Giai thich
//Dong 44: tai vi nT xet tu 0 va neu nT == n(so dinh) - 1 thi co nghia la thuat toan da duyet qua tat ca cac dinh, nen dung thuat toan.
//dong 47: tmp = -1 boi vi trong so ban dau theo bai la luon duong nen tmp = -1 se khong lam anh huong den thuat toan
//Dong 68: De danh dau nhan biet la dinh do da duyet rui va da luu tru vao tap Y
/* Cau 2:
buoc1 : 38 - 44
buoc2 : 46 - 64
buoc3 : 67 - 70
// Cau 4 : trong ham Prim(GRAPH g, bool type) type == true duyet cau khung no nhat, type == false duyet cay khung lon nhat
//Cau 6:
Thuat toan tren van chay duoc voi trong so am, tru khi thay vi bien tmp = -1 th� tmp nen bang so vo cung lon hoac vo cung be
*/
