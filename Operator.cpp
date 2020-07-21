#include<iostream>
#include<fstream>
using namespace std;

class PHANSO
{
private:
	int tu,mau;
public:
	friend istream& operator>>(istream &is,PHANSO &x);
	friend ostream& operator<<(ostream &os,PHANSO x);
	PHANSO operator+(PHANSO x)
	{
		PHANSO p;
		p.tu = tu*x.mau + x.tu*mau;
		p.mau=mau*x.mau;
		return p;
	}
	PHANSO operator-(PHANSO x)
	{
		PHANSO p;
		p.tu = tu*x.mau - x.tu*mau;
		p.mau=mau*x.mau;
		return p;
	}
	PHANSO()
	{
		tu = 1;
		mau = 1;
	}
	PHANSO(int m,int n)
	{
		tu = m;
		mau = n;
	}
};
istream& operator>>(istream &is,PHANSO &x)
{
	cout<<"Nhap gia tri tu :";	is>>x.tu;
	do
	{
		cout<<"Nhap gia tri mau :"; is>>x.mau;
		if(x.mau==0) cout<<"mau phai khac gia tri 0";
	}while(x.mau==0);
	return is;
}
ostream& operator<<(ostream &os,PHANSO x)
{
	os<<x.tu<<"/"<<x.mau;
}
int main()
{
	PHANSO a = PHANSO(2,3);
	PHANSO b = PHANSO(3,4);
	cout<<a<<"\n"<<b<<endl;
	PHANSO d = a + b;
	cout << "a + b ="<<a+b;
	ofstream os("D:\\Text.txt",ios_base::out);
	os<<"Cai con me may : a ---- b = "<<a-b;
	return 0;
}
