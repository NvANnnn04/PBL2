#include "Letan.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

Letan::Letan(string n, string id, string p, string e,  string bd, string wd) 
	:Person(n, id, p), emailLT(e), birthdayLT(bd), workdayLT(wd)
{
}

string Letan::getEmailLT() const {
	return emailLT;   
}

string Letan::getBirthdayLT() const {
	return birthdayLT;
}
	
string Letan::getWorkdayLT() const {
	return workdayLT;
}

NodeLT* LinkedListLetan::getHead() const {
	return head;
}
	
void Letan::setEmailLT(string mail) {
	emailLT = mail;
}
void Letan::setBirthdayLT(string birthday) {
	birthdayLT = birthday;
}

void Letan::setWorkdayLT(string workday) {
	workdayLT = workday;
}

void Letan::displayInfoLT() const {
	cout << setw(16) << left << "Ho va ten: " << getName() << endl;
	cout << setw(16) << "CCCD: " << getCccd() << endl;
	cout << setw(16) << "Phone: " << getSdt() << endl;
	cout << setw(16) << "Email: " << getEmailLT() << endl;
	cout << setw(16) << "Ngay sinh: " << getBirthdayLT() << endl;
	cout << setw(16) << "Ngay lam viec: " << getWorkdayLT() << endl;
}

LinkedListLetan::LinkedListLetan() : head(NULL){
}

LinkedListLetan::~LinkedListLetan() {
	NodeLT* node = head;
	while (node != NULL) {
		NodeLT* tempnode = node->next;
		delete node;
		node = tempnode;
	}
}

void LinkedListLetan::addLetan(const Letan& lt) {
	NodeLT* newNode = new NodeLT(lt);
	newNode->next = head;
	head = newNode;
}

NodeLT* LinkedListLetan::findLetan(const string& id) {
	NodeLT* node = head;
	while (node != NULL) {
		if (node->data.getCccd() == id) {
			cout << "Da tim thay thong tin le tan voi cccd " << id << endl; 
			return node;
		}
		node = node->next;
	}
	cout << "Khong tim thay le tan, vui long thu lai! " << endl;
	return NULL;
}

void LinkedListLetan::updateLetan(const string& id) {
	NodeLT* node = findLetan(id);	
	if (node == NULL) {
		cout << "Khong tim thay le tan co CCCD: " << id << endl;
		return;
	}
	cout << "Cap nhat thong tin le tan co ID: " << id << endl;
	cout << "1. So dien thoai\n";
	cout << "2. Email\n";
	cout << "3. Ngay lam viec\n";
	cout << "0. Thoat!\n";
	int choice;
	do {
		cin >> choice;
		cin.ignore();
		switch (choice) {
			case 1: {
				string phone;
				cout << "Nhap so dien thoai moi: ";
				getline(cin, phone);
				node->data.setSdt(phone);
				break;
			}
			case 2: {
				string email;
				cout << "Nhap email moi: ";
				getline(cin, email);
				node->data.setEmailLT(email);
				break;
			}
			case 3: {
				string workday;
				cout << "Cap nhat ngay lam viec moi: ";
				getline(cin, workday);
				node->data.setWorkdayLT(workday);
				break;
			}
			case 0: {
				cout << "Thoat khoi trang thai cap nhat thong tin!\n";
				break;
			}
			default:
				cout << "Lua chon khong hop le, vui long thu lai!\n";
		}
	} while (choice != 0);
	cout << "Cap nhat thanh cong thong tin le tan!" << endl;
}

void LinkedListLetan::deteleLetan(const string& id) {
	if (head == NULL) {
		cout << "Danh sach le tan trong!" << endl;	
		return;
	}
	if (head->data.getCccd() == id) {
		NodeLT* temp = head;
		head = head->next;
		delete temp;
		cout << "Xoa thanh cong le tan ra khoi danh sach! " << endl;
		return;
	}
	
	NodeLT* node = head;
	while (node->next != NULL) {
		if (node->next->data.getCccd() == id) {
		NodeLT* temp = node->next;
		node->next = node->next->next;
		delete temp;
		cout << "Xoa thanh cong le tan ra khoi danh sach! " << endl;
		return;
		}
		node = node->next;
	}
}
void LinkedListLetan::readLetanFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Khong the mo file " << filename << endl;
		return;
	}
	string line;
	while(getline(file, line)) {
		stringstream ss(line);
		string name, cccd, sdt, email, birthday, workday;
		getline(ss, name, ';');
		getline(ss, cccd, ';');
		getline(ss, sdt, ';');
		getline(ss, email, ';');
		getline(ss, birthday, ';');
		getline(ss, workday, ';');
		Letan lt(name, cccd, sdt, email, birthday, workday);
		addLetan(lt);
	}
	file.close();
}

void LinkedListLetan::displayLetan() const {
	NodeLT* node = head;
	while (node != NULL) {
		node->data.displayInfoLT();
		cout << "-------------------------------------------------------------------------------------------" << endl;
		node = node->next;
	}
}


