#include "Khachhang.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

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
	cout << "\nThong tin khach hang:\n";
	cout << string(120, '=') << endl;
	cout << left << setw(10) << "RoomID" << "| "
		 << left << setw(25) << "Check-in Time" << "| "
		 << left << setw(20) << "Ho va ten" << "| " 
		 << left << setw(15) << "CCCD" << "| "
		 << left << setw(15) << "So dien thoai" << "| "
		 << left << setw(20) << "Noi song" << endl;
	cout << string(120, '-') << endl;
	
	ifstream file("khachhanghientai.txt");
	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			stringstream ss(line);
			string roomID, checkInTime, name, cccd, phone, quequan;
			getline(ss, roomID, ';');
			getline(ss, checkInTime, ';');
			getline(ss, name, ';');
			getline(ss, cccd, ';');
			getline(ss, phone, ';');
			getline(ss, quequan, ';');
			
			cout << left << setw(10) << roomID << "| "
				 << left << setw(25) << checkInTime << "| "
				 << left << setw(20) << name << "| "
				 << left << setw(15) << cccd << "| "
				 << left << setw(15) << phone << "| "
				 << left << setw(20) << quequan << endl;
		}
		file.close();
	}
	cout << string(120, '=') << endl;
}

int LinkedListKhachhang::countKhachHangInFile(const string& filename) const {
    ifstream file(filename);
    if (!file.is_open()) {
        return 0;
    }
    
    int count = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            count++;
        }
    }
    file.close();
    return count;
}

void LinkedListKhachhang::displayCurrentKhachHang() {
    readKhachHangFile("khachhanghientai.txt");
    if (head == NULL) {
        cout << "Khong co khach hang nao dang o!\n";
        return;
    }
    displayKhachhang();
}

void LinkedListKhachhang::displayHistoryKhachHang() {
    readKhachHangFile("lichsukhachhang.txt");
    if (head == NULL) {
        cout << "Chua co lich su khach hang!\n";
        return;
    }
    displayKhachhang();
}

void LinkedListKhachhang::thongKeKhachHang() {
    cout << "\n========== THONG KE KHACH HANG ==========\n";
    
    // Đếm số khách hàng hiện tại
    int currentCount = countKhachHangInFile("khachhanghientai.txt");
    cout << "So luong khach hang dang o: " << currentCount << " khach hang\n";
    
    // Đếm tổng số khách hàng đã từng đến
    int historyCount = countKhachHangInFile("lichsukhachhang.txt");
    cout << "Tong so khach hang da tung den: " << historyCount << " khach hang\n";
    
    // Hiển thị chi tiết khách hàng hiện tại
    if (currentCount > 0) {
        cout << "\nDanh sach khach hang dang o:\n";
        displayCurrentKhachHang();
    }
}

void LinkedListKhachhang::readKhachHangFile(const string& filename) {
    // Xóa danh sách hiện tại
    while (head != NULL) {
        NodeKH* temp = head;
        head = head->next;
        delete temp;
    }
    head = NULL;

    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string roomID, checkInTime, name, cccd, phone, quequan;
        getline(ss, roomID, ';');
        getline(ss, checkInTime, ';');
        getline(ss, name, ';');
        getline(ss, cccd, ';');
        getline(ss, phone, ';');
        getline(ss, quequan, ';');

        Khachhang kh(name, cccd, phone, quequan);
        addKhachhang(kh);
    }
    file.close();
}

bool LinkedListKhachhang::updateKhachHang(const string& id) {
    // Đọc thông tin từ file
    ifstream readFile("khachhanghientai.txt");
    if (!readFile.is_open()) {
        cout << "Khong the mo file khachhanghientai.txt\n";
        return false;
    }

    // Tìm và hiển thị thông tin khách hàng cần cập nhật
    string currentRoomID, currentCheckInTime, currentName, currentCCCD, currentPhone, currentAddress;
    bool found = false;
    string line;
    while (getline(readFile, line)) {
        stringstream ss(line);
        string roomID, checkInTime, name, cccd, phone, quequan;
        getline(ss, roomID, ';');
        getline(ss, checkInTime, ';');
        getline(ss, name, ';');
        getline(ss, cccd, ';');
        getline(ss, phone, ';');
        getline(ss, quequan, ';');

        if (cccd == id) {
            currentRoomID = roomID;
            currentCheckInTime = checkInTime;
            currentName = name;
            currentCCCD = cccd;
            currentPhone = phone;
            currentAddress = quequan;
            found = true;
            break;
        }
    }
    readFile.close();

    if (!found) {
        cout << "Khong tim thay khach hang co CCCD: " << id << endl;
        return false;
    }

    // Hiển thị thông tin hiện tại
    cout << "\nThong tin hien tai cua khach hang:\n";
    cout << string(120, '=') << endl;
    cout << left << setw(10) << "RoomID" << "| "
         << left << setw(25) << "Check-in Time" << "| "
         << left << setw(20) << "Ho va ten" << "| " 
         << left << setw(15) << "CCCD" << "| "
         << left << setw(15) << "So dien thoai" << "| "
         << left << setw(20) << "Noi song" << endl;
    cout << string(120, '-') << endl;
    cout << left << setw(10) << currentRoomID << "| "
         << left << setw(25) << currentCheckInTime << "| "
         << left << setw(20) << currentName << "| "
         << left << setw(15) << currentCCCD << "| "
         << left << setw(15) << currentPhone << "| "
         << left << setw(20) << currentAddress << endl;
    cout << string(120, '=') << endl;

    // Menu cập nhật
    int choice;
    bool needUpdate = false;
    string newPhone = currentPhone;
    string newAddress = currentAddress;

    do {
        cout << "\n========== CAP NHAT THONG TIN ==========\n";
        cout << "1. Sua so dien thoai (Hien tai: " << currentPhone << ")\n";
        cout << "2. Sua que quan (Hien tai: " << currentAddress << ")\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "Nhap so dien thoai moi: ";
                getline(cin, newPhone);
                needUpdate = true;
                cout << "Cap nhat so dien thoai thanh cong!\n";
                break;
            }
            case 2: {
                cout << "Nhap que quan moi: ";
                getline(cin, newAddress);
                needUpdate = true;
                cout << "Cap nhat que quan thanh cong!\n";
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
        // Cập nhật file khachhanghientai.txt
        ifstream inFile("khachhanghientai.txt");
        ofstream outFile("temp.txt");
        
        while (getline(inFile, line)) {
            stringstream ss(line);
            string roomID, checkInTime, name, cccd;
            getline(ss, roomID, ';');
            getline(ss, checkInTime, ';');
            getline(ss, name, ';');
            getline(ss, cccd, ';');
            
            if (cccd != id) {
                outFile << line << endl;
            } else {
                outFile << currentRoomID << ";"
                       << currentCheckInTime << ";"
                       << currentName << ";"
                       << currentCCCD << ";"
                       << newPhone << ";"
                       << newAddress << ";" << endl;
            }
        }
        
        inFile.close();
        outFile.close();
        remove("khachhanghientai.txt");
        rename("temp.txt", "khachhanghientai.txt");

        // Cập nhật file lichsukhachhang.txt
        ifstream historyFile("lichsukhachhang.txt");
        ofstream tempHistoryFile("temp_history.txt");
        
        while (getline(historyFile, line)) {
            stringstream ss(line);
            string roomID, checkInTime, name, cccd;
            getline(ss, roomID, ';');
            getline(ss, checkInTime, ';');
            getline(ss, name, ';');
            getline(ss, cccd, ';');
            
            if (cccd != id) {
                tempHistoryFile << line << endl;
            } else {
                tempHistoryFile << roomID << ";"
                              << checkInTime << ";"
                              << currentName << ";"
                              << currentCCCD << ";"
                              << newPhone << ";"
                              << newAddress << ";" << endl;
            }
        }
        
        historyFile.close();
        tempHistoryFile.close();
        remove("lichsukhachhang.txt");
        rename("temp_history.txt", "lichsukhachhang.txt");

        cout << "Da cap nhat thong tin vao ca hai file.\n";
        return true;
    }
    return false;
}

void LinkedListKhachhang::findKhachHangByName(const string& name) {
    if (head == NULL) {
        cout << "Danh sach khach hang trong!\n";
        return;
    }

    bool found = false;
    cout << "\nKet qua tim kiem cho ten \"" << name << "\":\n";
    cout << string(120, '=') << endl;
    cout << left << setw(10) << "RoomID" << "| "
         << left << setw(25) << "Check-in Time" << "| "
         << left << setw(20) << "Ho va ten" << "| " 
         << left << setw(15) << "CCCD" << "| "
         << left << setw(15) << "So dien thoai" << "| "
         << left << setw(20) << "Noi song" << endl;
    cout << string(120, '-') << endl;

    // Đọc thông tin từ file để lấy RoomID và Check-in Time
    ifstream file("khachhanghientai.txt");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string roomID, checkInTime, currentName, cccd, phone, quequan;
        getline(ss, roomID, ';');
        getline(ss, checkInTime, ';');
        getline(ss, currentName, ';');
        getline(ss, cccd, ';');
        getline(ss, phone, ';');
        getline(ss, quequan, ';');

        // Chuyển đổi cả hai chuỗi về chữ thường để so sánh
        string lowerCurrentName = currentName;
        string lowerSearchName = name;
        for(char& c : lowerCurrentName) c = tolower(c);
        for(char& c : lowerSearchName) c = tolower(c);

        if (lowerCurrentName.find(lowerSearchName) != string::npos) {
            cout << left << setw(10) << roomID << "| "
                 << left << setw(25) << checkInTime << "| "
                 << left << setw(20) << currentName << "| "
                 << left << setw(15) << cccd << "| "
                 << left << setw(15) << phone << "| "
                 << left << setw(20) << quequan << endl;
            found = true;
        }
    }
    file.close();

    if (!found) {
        cout << "Khong tim thay khach hang nao co ten \"" << name << "\"\n";
    } else {
        cout << string(120, '=') << endl;
    }
}

 
