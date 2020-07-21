#include<iostream>
#include<string>
#include<iomanip>
#include<stdlib.h>

using namespace std;
struct TienTrinh
{
	string P;
	int Tth;
	int Txh;
};
typedef struct TienTrinh Node;
void Hien()
{
	cout << setw(10) << "P";
	cout << setw(10) << "T(th)";
	cout << setw(10) << "T(xh)"<<endl;
}
void Xuat(Node a[], int n)
{
	Hien();
	for (int i = 0; i < n; i++)
	{
		cout << setw(10) << a[i].P;
		cout << setw(10) << a[i].Tth;
		cout << setw(10) << a[i].Txh << endl;
	}
}
void SapXep(Node a[], int n)
{

	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (a[i].Txh > a[j].Txh)
			{
				Node p = a[i];
				a[i] = a[j];
				a[j] = p;
			}
		}
	}
	cout << endl;
	Xuat(a, n);
}
void SJF(Node a[], int n)
{
	int T = a[0].Tth;
	while (a[1].Txh > T)
		T++;
	for (int i = 1; i < n - 1; i++)
	{
		if (a[i].Txh <= T)
		{
			for (int j = i + 1; j < n; j++)
			{
				if ((a[i].Tth > a[j].Tth) && (a[j].Txh < T))
				{
					Node p = a[i];
					a[i] = a[j];
					a[j] = p;
				}
			}
			T += a[i].Tth;
			while (a[i + 1].Txh > T && i+1 <n)
				T++;
		}
	}
}
void Gantt(Node a[], int n)
{
	int k = n, p = k, i = 0, T = a[0].Txh, T1 = T, j = 0, ij = 0;
	int d = k / 10;
	if (k % 10 != 0)
		d++;
	while (i < d)
	{
		int dem = 0;
		cout << setw(4) << "|";
		while (j < k)
		{
			dem++;
			if (dem == 10)
				break;
			if (a[j].Txh <=T1)
			{
				cout << setw(4) << a[j].P << setw(4) << "|";
				T1 += a[j].Tth;
				j++;
			}
			else
			{
				p++;
				cout << setw(8) << "|";
				T1 = a[j].Txh;
			}
		}
		dem = 0;
		cout << endl;
		cout << setw(4) <<T;
		while (ij < k)
		{
			dem++;
			if (dem == 10)
				break;
			if (a[ij].Txh <= T)
			{
				T += a[ij].Tth;
				cout << setw(8) << T;
				ij++;
			}
			else
			{
				T = a[ij].Txh;
				cout << setw(8) << T;
			}
		}
		i++;
		int b = p / 10;
		if (p % 10 != 0)
			b++;
		d = b;
		cout << endl;
	}
}
int main()
{
	int n;
	cout << "Nhap so luong tien trinh :";
	cin >> n;
	Node* a = new Node[n];
	cout << "Nhap thong tin tien trinh " << endl;
	for (int i = 0; i < n; i++)
	{
		a[i].P = "P" + to_string(i);
		cout << "Nhap thoi gian thuc hien cua "<<a[i].P<<" :";
		cin >> a[i].Tth;
		cout << "Nhap thoi gian xuat hien cua " << a[i].P << " :";
		cin >> a[i].Txh;
		int j = 0;
		while (j < i)
		{
			if (a[i].Txh == a[j].Txh)
			{
				cout << "Luu y thoi diem xuat hien cua cac tien trinh trong he phai khac nhau!!!" << endl;
				cout << "Thoi gian nhap trung voi tien trinh " << a[j].P;
				cout << "\nNhap lai :";
				cin >> a[i].Txh;
			}
			j++;
		}
	}
	Xuat(a, n);
	SapXep(a,n);
	SJF(a,n);
	Gantt(a, n);
	system("pause");
	return 0;
}