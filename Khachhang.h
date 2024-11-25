#ifndef KHACHHANG_H
#define KHACHHANG_H
#include <string>
#include "Person.h"
using namespace std;

class Khachhang : public Person {
private: 
	string queQuan;
public:
	Khachhang(string n, string id, string p, string qq);
	string getQuequan() const;
	void setQuequan(string quequan);
	void displayInfoKH() const;

};

struct NodeKH {
public:
	Khachhang data;
	NodeKH* next;
	NodeKH(const Khachhang& kh) : data(kh), next(NULL){}
};

class LinkedListKhachhang {
private: 
	NodeKH* head;
public:
	LinkedListKhachhang();
	~LinkedListKhachhang();
	NodeKH* getHead() const { return head; }
	void addKhachhang(const Khachhang& kh);
	void deleteKhachhang(const string& id);
	NodeKH* findKhachhang(const string& id);
	void displayKhachhang() const;
	void readKhachHangFile(const string& filename);
	void findKhachHangByName(const string& name);
	void displayCurrentKhachHang();
	void displayHistoryKhachHang();
	bool updateKhachHang(const string& id);
	void saveToFile(const string& filename) const;
	int countKhachHangInFile(const string& filename) const;
	void thongKeKhachHang();
};
#endif
