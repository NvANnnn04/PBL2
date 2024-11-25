#include "Letan.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
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
	NodeLT* current = head;
	while (current != NULL) {
		if (current->data.getWorkdayLT() == lt.getWorkdayLT()) {
			cout << "Ngay lam viec " << lt.getWorkdayLT() << " da duoc phan cong cho le tan: "
				 << current->data.getName() << endl;
			return;
		}
		current = current->next;
	}
	NodeLT* newNode = new NodeLT(lt);
	newNode->next = head;
	head = newNode;

	ofstream file("danhsachletan.txt", ios::app);
	if (file.is_open()) {
		file << lt.getName() << ";" 
			 << lt.getCccd() << ";" 
			 << lt.getSdt() << ";" 
			 << lt.getEmailLT() << ";" 
			 << lt.getBirthdayLT() << ";" 
			 << lt.getWorkdayLT() << ";" << endl;
		file.close();
		cout << "Da cap nhat thong tin vao file.\n";
	} else {
		cout << "Khong the cap nhat file!\n";
	}
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

    cout << "\nThong tin hien tai cua le tan:\n";
    cout << "=============================================================================\n";
    node->data.displayInfoLT();
    cout << "=============================================================================\n";

    int choice;
    bool needUpdate = false;
    do {
        cout << "\n===================== MENU SUA THONG TIN =====================\n";
        cout << "1. Sua so dien thoai (Hien tai: " << node->data.getSdt() << ")\n";
        cout << "2. Sua email (Hien tai: " << node->data.getEmailLT() << ")\n";
        cout << "3. Sua ngay lam viec (Hien tai: " << node->data.getWorkdayLT() << ")\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string phone;
                cout << "Nhap so dien thoai moi: ";
                getline(cin, phone);
                node->data.setSdt(phone);
                needUpdate = true;
                cout << "Cap nhat so dien thoai thanh cong!\n";
                break;
            }
            case 2: {
                string email;
                cout << "Nhap email moi: ";
                getline(cin, email);
                node->data.setEmailLT(email);
                needUpdate = true;
                cout << "Cap nhat email thanh cong!\n";
                break;
            }
            case 3: {
                string workday;
                cout << "Nhap ngay lam viec moi: ";
                getline(cin, workday);
                NodeLT* current = head;
                bool isValid = true;
                while (current != NULL) {
                    if (current != node && current->data.getWorkdayLT() == workday) {
                        cout << "Ngay lam viec da duoc phan cong cho le tan " 
                             << current->data.getName() << endl;
                        isValid = false;
                        break;
                    }
                    current = current->next;
                }
                if (isValid) {
                    node->data.setWorkdayLT(workday);
                    needUpdate = true;
                    cout << "Cap nhat ngay lam viec thanh cong!\n";
                }
                break;
            }
            case 0:
                cout << "Thoat cap nhat thong tin.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    if (needUpdate) {
        ofstream tempFile("temp.txt");
        ifstream file("danhsachletan.txt");
        string line;
        
        while (getline(file, line)) {
            stringstream ss(line);
            string name, cccd;
            getline(ss, name, ';');
            getline(ss, cccd, ';');
    
            if (cccd != id) {
                tempFile << line << endl;
            }
        }
        
        tempFile << node->data.getName() << ";"
                << node->data.getCccd() << ";"
                << node->data.getSdt() << ";"
                << node->data.getEmailLT() << ";"
                << node->data.getBirthdayLT() << ";"
                << node->data.getWorkdayLT() << ";" << endl;
        
        file.close();
        tempFile.close();
        remove("danhsachletan.txt");
        rename("temp.txt", "danhsachletan.txt");
        cout << "Da cap nhat thong tin vao file.\n";
    }
}

void LinkedListLetan::deteleLetan(const string& id) {
    if (head == NULL) {
        cout << "Danh sach le tan trong!" << endl;    
        return;
    }

    bool deleted = false;
    if (head->data.getCccd() == id) {
        NodeLT* temp = head;
        head = head->next;
        delete temp;
        deleted = true;
    } else {
        NodeLT* node = head;
        while (node->next != NULL) {
            if (node->next->data.getCccd() == id) {
                NodeLT* temp = node->next;
                node->next = node->next->next;
                delete temp;
                deleted = true;
                break;
            }
            node = node->next;
        }
    }

    if (deleted) {
    
        ofstream tempFile("temp.txt");
        ifstream file("danhsachletan.txt");
        string line;
        
        while (getline(file, line)) {
            stringstream ss(line);
            string name, cccd;
            getline(ss, name, ';');
            getline(ss, cccd, ';');
            if (cccd != id) {
                tempFile << line << endl;
            }
        }
        
        file.close();
        tempFile.close();
        remove("danhsachletan.txt");
        rename("temp.txt", "danhsachletan.txt");
        cout << "Xoa thanh cong le tan ra khoi danh sach va cap nhat file!" << endl;
    }
}

void LinkedListLetan::readLetanFile(const string& filename) {

    while (head != NULL) {
        NodeLT* temp = head;
        head = head->next;
        delete temp;
    }
    head = NULL;

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
        
        NodeLT* newNode = new NodeLT(lt);
        newNode->next = head;
        head = newNode;
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

void LinkedListLetan::findLetanByName(const string& name) {
    if (head == NULL) {
        cout << "Danh sach le tan trong!\n";
        return;
    }

    NodeLT* current = head;
    bool found = false;
    cout << "\nKet qua tim kiem cho ten \"" << name << "\":\n";
    
    while (current != NULL) {
        string currentName = current->data.getName();
        string searchName = name;
        for(char& c : currentName) c = tolower(c);
        for(char& c : searchName) c = tolower(c);
        
        if (currentName.find(searchName) != string::npos) {
            if (!found) {
                cout << string(85, '=') << endl;
                found = true;
            }
            current->data.displayInfoLT();
            cout << string(85, '=') << endl;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "Khong tim thay le tan nao co ten \"" << name << "\"\n";
        return;
    }
}

void LinkedListLetan::findLetanByWorkday(const string& workday) {
    if (head == NULL) {
        cout << "Danh sach le tan trong!\n";
        return;
    }

    NodeLT* current = head;
    bool found = false;
    cout << "\nKet qua tim kiem cho ngay lam viec \"" << workday << "\":\n";
    
    while (current != NULL) {
        if (current->data.getWorkdayLT() == workday) {
            if (!found) {
                cout << string(85, '=') << endl;
                found = true;
            }
            current->data.displayInfoLT();
            cout << string(85, '=') << endl;
        }
        current = current->next;
    }
    
    if (!found) {
        cout << "Khong tim thay le tan nao lam viec vao \"" << workday << "\"\n";
        return;
    }
}

bool LinkedListLetan::updateWorkday(const string& cccd, const string& newWorkday) {
    NodeLT* letan = findLetan(cccd);
    if (letan == NULL) return false;

    // Kiểm tra trùng lịch
    NodeLT* current = head;
    while (current != NULL) {
        if (current != letan && current->data.getWorkdayLT() == newWorkday) {
            cout << "Ngay lam viec da duoc phan cong cho le tan:\n";
            cout << "Ten: " << current->data.getName() 
                 << " (CCCD: " << current->data.getCccd() << ")\n";
            return false;
        }
        current = current->next;
    }

    // Cập nhật ngày làm việc
    letan->data.setWorkdayLT(newWorkday);

    // Cập nhật file
    ofstream tempFile("temp.txt");
    ifstream file("danhsachletan.txt");
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string name, fileCccd;
        getline(ss, name, ';');
        getline(ss, fileCccd, ';');
        if (fileCccd != cccd) {
            tempFile << line << endl;
        }
    }
    
    tempFile << letan->data.getName() << ";"
            << letan->data.getCccd() << ";"
            << letan->data.getSdt() << ";"
            << letan->data.getEmailLT() << ";"
            << letan->data.getBirthdayLT() << ";"
            << letan->data.getWorkdayLT() << ";" << endl;
    
    file.close();
    tempFile.close();
    remove("danhsachletan.txt");
    rename("temp.txt", "danhsachletan.txt");

    return true;
}


