#include<iostream>
#include<string>
#include<iomanip>
#include<stdlib.h>

using namespace std;
struct TienTrinh
{
	//char P[5] = "P"; dung cho cach 1
	string P; 	// ten cua tien trinh
	int Tth; 	// CPU burst time
	int Txh; 	// thoi diem xuat hien
	int TGC;	// thoi gian cho
	int TGXL;	// thoi gian xu ly
	
};
typedef struct TienTrinh Node; 
void Hien() 
{
	cout <<"\t\t\t\t"<< setw(10) << "P";
	cout <<setw(10) << "T(th)";
	cout << setw(10) << "T(xh)" << endl;
}
void Xuat(Node a[], int n)
{
	Hien();
	for (int i = 0; i < n; i++)
	{
		cout <<"\t\t\t\t"<< setw(10) << a[i].P;
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
	int T = a[0].Tth; // thoi gian xu ly 
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
			while (a[i + 1].Txh > T&& i + 1 < n)
				T++;
		}
	}
}
void Gantt(Node a[], int n)
{
	int k = n, p = k, i = 0, T = a[0].Txh, T1 = T, j = 0, ij = 0;
	// tinh so dong 
	int d = k / 10;
	if (k % 10 != 0)
		d++;
	a[0].TGC = a[0].Txh;
	while (i < d)
	{
		int dem = 0;
		cout << setw(4) << "|";
		// viet ra p
		while (j < k)
		{
			if (dem == 10) // gioi han tren 1 dong den
				break;
			dem++;
			if (a[j].Txh <= T1) 
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
		cout << setw(4) << T;
		// viet thoi gian
		while (ij < k)
		{
			if (dem == 10) // tuong tu ben tren dung de gioi han tren 1 dong
				break;
			dem++;
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
			a[ij].TGC = T; 
		}
		i++; 
		int b = p / 10;
		if (p % 10 != 0)
			b++;
		d = b;
		cout << endl;
	}
}
void ThoiGianCho(Node a[], int n)
{
	float Tb = 0;
	// Tinh va hien thi thoi gian cho cua tung tien trinh
	for (int i = 0; i < n; i++)
	{
		cout << "\t\t+ Thoi gian cho cua " << a[i].P << " :" << a[i].TGC <<" - "<<a[i].Txh << " = "<<a[i].TGC - a[i].Txh<< endl;
		a[i].TGC = a[i].TGC - a[i].Txh;
		Tb += a[i].TGC;
	}
	//  Hien thi ra thoi gian trung binh
	cout << "\t\t+ Thoi gian cho trung binh cua he tien trinh :\n\t\t( ";
	for(int i =0;i<n;i++)
	{
		cout<<a[i].TGC;
		if(i!=n-1)
			cout<<" + ";
		else
			cout<<" )/"<<n<<" = ";
	}
	cout<<Tb/n<<endl;
}
void ThoiGianXuLy(Node a[], int n)
{
	float Tb = 0;
	// Tinh va hien thi thoi gian xu ly cua tung tien trinh
	for (int i = 0; i < n; i++)
	{
		cout << "\t\t+ Thoi gian xu ly cua " << a[i].P << " :" << a[i].TGC + a[i].Txh+ a[i].Tth <<" - "<<a[i].Txh<<" = "<<a[i].TGC + a[i].Tth<< endl;
		a[i].TGXL = a[i].TGC + a[i].Tth;
		Tb += a[i].TGXL;
	}
	// Hien thi ra thoi gian trung binh
	cout << "\t\t+ Thoi gian xu ly trung binh cua he tien trinh :\n\t\t( ";
	for(int i =0;i<n;i++)
	{
		cout<<a[i].TGXL;
		if(i!=n-1)
			cout<<" + ";
		else
			cout<<" )/"<<n<<" = ";
	}
	cout<<Tb/n<<endl;
}
int main()
{
	int n;
	cout << "Nhap so luong tien trinh :";
	do{
			cin >> n;
			if(n<2)
				cout<<"So luong tien trinh phai lon hon 1\n Nhap lai:";
	}while(n<2);
	Node* a = new Node[n];
	cout << "Nhap thong tin tien trinh " << endl;
	for (int i = 0; i < n; i++)
	{
//		 Tu dong gian ten tien trinh
//		Cach 1 : 
//		char p[4] ;
//		itoa(i,p,10);
//		strcat(a[i].P,p);
//	 Cach 2 : ( Phai chuyen doi sang c++11 )
		a[i].P = "P"+to_string(i); // c++11
		do
		{
			cout << "Nhap thoi gian thuc hien cua " << a[i].P << " :";
			cin >> a[i].Tth;
			if (a[i].Tth <= 0)
				cout << "Khong hop le!!!" << endl;
		} while (a[i].Tth <= 0);
		do
		{
			cout << "Nhap thoi diem xuat hien cua " << a[i].P << " :";
			cin >> a[i].Txh;
			if (a[i].Txh < 0)
				cout << "Khong hop le!!!" << endl;
		} while (a[i].Txh < 0);
		int j = 0;
		while (j < i)
		{
			if (a[i].Txh == a[j].Txh)
			{
				cout << "Luu y thoi diem xuat hien cua cac tien trinh trong he phai khac nhau!!!" << endl;
				cout << "Thoi gian nhap trung voi tien trinh " << a[j].P;
				cout << "\nNhap lai :";
				cin >> a[i].Txh;
				j = -1; // sau khi nhap lai tiep tuc quay tro lai kiem tra tu dau
			}
			j++;
		}
	}
	system("cls");
	cout<<"\t\t============================ He tien trinh vua nhap ==================================="<<endl;
	Xuat(a, n);
	cout << "\n\t\t=========== Sap xep tien trinh theo thu tu tang dan cua thoi gian xuat hien ============";
	SapXep(a, n);
	SJF(a, n);
	cout << "\n\t\t=================================== Gian do Gantt =====================================" << endl;
	Gantt(a, n);
	cout << "\n\t\t================== Tinh thoi gian cho trung binh cua he tien trinh ====================" << endl;
	ThoiGianCho(a, n);
	cout << "\n\t\t================= Tinh thoi gian xu ly trung binh cua he tien trinh ====================" << endl;
	ThoiGianXuLy(a, n);
	cout<<"\n\t\t\t\t\t======================================="<<endl;
	system("pause");
	return 0;
}
