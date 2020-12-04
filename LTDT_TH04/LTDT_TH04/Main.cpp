#include<iostream>
#include<fstream>
using namespace std;
struct GRAPH
{
	int iSoDinh;//so dinh do thi
	int iMaTran[100][100];//ma tran ke	
	int visited[100]; //danh dau dinh i da xet hay chua, 0 la chua xet
};
struct CANH
{
	int u;//Dinh thu nhat
	int v;//Dinh thu hai
	int trongso;
};

CANH T[100];//Mang luu cac canh trong thuat toan Prim

void nhapMaTranKe(string duongdan, GRAPH& dt) {
	ifstream inp;
	inp.open(duongdan);
	if (inp.is_open()) {
		inp >> dt.iSoDinh;
		for (int i = 0; i < dt.iSoDinh; i++) {
			for (int j = 0; j < dt.iSoDinh; j++) {
				inp >> dt.iMaTran[i][j];
			}
		}
		inp.close();
	}
	else {
		cout << "Khong mo duoc file!";
		exit(0);
	}
}
void Prim(char v, GRAPH g, bool type)
{
	//B1: Gan so canh cua cay khung ban dau là 0
	int nT = 0;
	//B2: Khoi tao nhan cac dinh la chua duyet (0)
	for (int i = 0; i < g.iSoDinh; i++)
		g.visited[i] = 0;

	//B3: Danh dau dinh 0 la da duyet
	g.visited[v - 'A'] = 1;

	while (nT < g.iSoDinh - 1)//neu bang n -1 canh thi dung	vi nT xet tu 0 va neu nT == n(so dinh) - 1 thi co nghia la thuat toan da duyet qua tat ca cac dinh, vay nen dung thuat toan
	{
		CANH canhnhonhat;//dung de luu tru canh nho nhat tu mot dinh da xét toi dinh chua xet
		int tmp = -1;	//tmp = -1 boi vi trong so ban dau theo bai la luon duong, nen tmp = -1 se khong lam anh huong den thuat toan
		for (int i = 0; i < g.iSoDinh; i++)
			if (g.visited[i] == 0) //neu la dinh chua duyet. Dieu kien dung khi j thuoc tap Y hay V\Y
			{
				for (int j = 0; j < g.iSoDinh; j++)
					if (g.visited[j] == 1 && (g.iMaTran[i][j] != 0))
					{
						if ((type == true && (tmp == -1 || g.iMaTran[i][j] < tmp)) || (type == false && (tmp == -1 || g.iMaTran[i][j] > tmp)))
							//type == true duyet cau khung no nhat, type == false duyet cay khung lon nhat
						{
							tmp = g.iMaTran[i][j];
							canhnhonhat.u = i;
							canhnhonhat.v = j;
							canhnhonhat.trongso = g.iMaTran[i][j];
						}
					}
			}

		//Them canh nho nhat vao tap T
		T[nT] = canhnhonhat;
		nT++;//Tang so canh len 1

		g.visited[canhnhonhat.u] = 1;//De danh dau nhan biet la dinh do da duyet rui va da luu tru vao tap Y

	}
	char c = 'A';
	//Tang trong so cua cay khung
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
		cout << "Nhap dinh bat dau: (vd: A)\n";
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
