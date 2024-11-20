#include "Khachhang.h"
#include <iostream>
#include <iomanip>

using namespace std;

Khachhang::Khachhang(string n, string id, string p, string qq)
	: Person(n, id, p), queQuan(qq) 
{
}

string Khachhang::getQuequan() const {
	return queQuan;
}

void Khachhang::setQuequan(string quequan) {
	queQuan = quequan;
}

void Khachhang::displayInfoKH() const {
	cout << setw(15) << getName() << " | ";
	cout << setw(15) << getCccd() << " | ";
	cout << setw(15) << getSdt() << " | ";
	cout << setw(15) << getQuequan() << endl;
}

LinkedListKhachhang::LinkedListKhachhang() : head(NULL) {	
}

LinkedListKhachhang::~LinkedListKhachhang() {
	NodeKH* node = head;
	while (node != NULL) {
		NodeKH* temp = node;
		node = node->next;
		delete temp; 
	}
}

void LinkedListKhachhang::addKhachhang(const Khachhang& kh) {
	NodeKH* newNode = new NodeKH(kh);
	newNode->next = head;
	head = newNode;
}

void LinkedListKhachhang::deleteKhachhang(const string& id) {
	if (head == NULL) {
		cout << "Danh sach khach hang rong!" << endl;
		return;
	}
	if (head->data.getCccd() == id) {
		NodeKH* temp = head;
		head = head->next;
		delete temp;
		cout << "Xoa thanh cong khach hang trong danh sach!" << endl;
	}
	NodeKH* node = head;
	while (node->next != NULL) {
		if (node->next->data.getCccd() == id) {
			NodeKH* temp = node->next;
			node->next = node->next->next;
			delete temp;
			cout << "Xoa thanh cong khach hang trong danh sach!" << endl;
			return;
		}
		node = node->next; 
	}
	cout << "Khong co khach hang co CCCD " << id << endl;
}

NodeKH* LinkedListKhachhang::findKhachhang(const string& id) {
	NodeKH* node = head;
	while (node != NULL) {
		if (node->data.getCccd() == id) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void LinkedListKhachhang::displayKhachhang() const {
	NodeKH* node = head; 
	cout << "Thong tin khach hang:\n";
	cout << setw(15) << "Ho va ten " << " | " << setw(15) << "CCCD " << " | " << setw(15) << "So dien thoai " << " | " << setw(15) << "Noi song " << endl;
	cout << string(65, '-')<< endl;
	while (node != NULL) {
		node->data.displayInfoKH();
		node = node->next;
	}
} 

 
