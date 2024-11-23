#include "Phong.h"
#include "Khachhang.h"
#include <iomanip>
#include <limits>
#include <algorithm>  // Cho hàm transform
using std::numeric_limits;

Phong::Phong(string id, string type, int floor, int capacity, bool available, int price)
    : roomID(id), roomType(type), roomFloor(floor), roomCapacity(capacity), isAvailable(true), roomPrice(price) {   
}
LinkedlistPhong::~LinkedlistPhong() {
    Node* node = head;  
    while (node != NULL) {
        Node* tempnode = node->next;  
        delete node;                
        node = tempnode ;
    }
    head = NULL; 
}

string Phong::getRoomID() const {
    return roomID;
}

string Phong::getRoomType() const {
    return roomType;
}

bool Phong::getIsAvailable() const {
    return isAvailable;
}

int Phong::getRoomFloor() const {
    return roomFloor;
}

int Phong::getRoomCapacity() const {
    return roomCapacity;
}

double Phong::getRoomPrice() const {
    return roomPrice;
}

void Phong::setRoomFloor(int floor) {
    roomFloor = floor;
}
void Phong::setRoomCapacity(int capacity) {
    roomCapacity = capacity;
}
void Phong::setRoomPrice(int price) {
    roomPrice = price;
}
void Phong::setIsAvailable(bool available) {
    isAvailable = available;
}

void Phong::setCheckIn(tm time) {
    checkIn = time;
}

void Phong::setCheckOut(tm time) {
    checkOut = time;
}
void Phong::setRoomType(const string& type) {
    string newType = type;
    transform(newType.begin(), newType.end(), newType.begin(), ::tolower);
    
    if (newType == "vip" || newType == "Vip" || newType == "VIP") {
        roomType = "VIP";
    } else if (newType == "standard" || newType == "Standard" || newType == "STANDARD") {
        roomType = "Standard";
    } else if (newType == "deluxe" || newType == "Deluxe" || newType == "DELUXE") {
        roomType = "Deluxe";
    } else {
        roomType = type; 
    }
}
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos || last == string::npos) return "";
    return str.substr(first, last - first + 1);
}

void Phong::displayRoomInfo() const {
    cout << left << setw(10) << roomID << " | "
         << setw(12) << roomType << " | "
         << setw(14) << (isAvailable ? "Trong" : "Da co khach") << " | "
         << setw(8) << roomFloor << " | "
         << setw(10) << roomCapacity << " | "
         << setw(15) << roomPrice << endl;
}

void LinkedlistPhong::displayRooms() const {
    Node* current = head;
    cout << string(85, '=') << endl;
    cout << left 
        << setw(10) << "RoomID" << " | " 
        << setw(12) << "RoomType" << " | " 
        << setw(14) << "Status" << " | " 
        << setw(8) << "Floor" << " | " 
        << setw(10) << "Capacity" << " | " 
        << setw(15) << "Price(VND/hour)" << endl;
    cout << string(85, '=') << endl;
    while (current != NULL) {
        current->room.displayRoomInfo();
        current = current->next;
    }
    cout << string(85, '=') << endl;
}

int Phong::thoigianthue() const {
    tm checkInTime = getCheckIn();
    tm checkOutTime = getCheckOut();
    
    int gioCheckIn = checkInTime.tm_hour + checkInTime.tm_mday * 24 + checkInTime.tm_mon * 30 * 24;
    int gioCheckOut = checkOutTime.tm_hour + checkOutTime.tm_mday * 24 + checkOutTime.tm_mon * 30 * 24;
    int soGio = gioCheckOut - gioCheckIn;
    return (soGio <= 0) ? 1 : soGio;
}

long long Phong::tienthuephong() const {
    int soGio = thoigianthue();
    return (long long)soGio * roomPrice;
}

void LinkedlistPhong::addRoom(Phong room) {
    string type = room.getRoomType();
    if (type == "vip" || type == "VIP" || type == "Vip") {
        type = "VIP";
    } else if (type == "standard" || type == "Standard" || type == "STANDARD") {
        type = "Standard";
    } else if (type == "deluxe" || type == "Deluxe" || type == "DELUXE") {
        type = "Deluxe";
    }
    room.setRoomType(type);
    Node* newNode = new Node(room);
    newNode->next = head;
    head = newNode;
    sortRooms();
    
}
bool LinkedlistPhong::updateRoom(const string& roomID, bool isAvailable) {
    Phong* room = findRoom(roomID);
    if (room != NULL) {
        room->setIsAvailable(isAvailable);
        cout << "Cap nhat thanh cong trang thai phong: " << roomID << endl;
        return true;
    } else {
        cout << "Khong tim thay phong co ma so: " << roomID << endl;
        return false;
    }
}

bool LinkedlistPhong::deleteRoom(const string& roomID) {
	if (head == NULL) {
		cout << "Danh sach phong dang trong!\n";
		return false; 
	}

	if (head->room.getRoomID() == roomID) {
		Node* temp = head;
		head = head->next;
		delete temp;
		return true;
	}
	Node* temp2 = head;
	while (temp2->next != NULL) {
		if (temp2->next->room.getRoomID() == roomID) {
			Node* temp3 = temp2->next;
			temp2->next = temp2->next->next;
			delete temp3;
			return true;
		}
		temp2 = temp2->next; 
	}
    return false;
}


Phong* LinkedlistPhong::findRoom(const string& roomID) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->room.getRoomID() == roomID) {
            return &temp->room;
        }
        temp = temp->next;
    }
    return NULL;
}

void LinkedlistPhong::readRoomsFile(const string& filename) {
    ifstream file(filename);
    string line;
    if (!file.is_open()) {
        cout << "Mo file khong thanh cong! Xin vui long thu lai." << endl;
        return;
    }
    while (getline(file, line)) {
        stringstream ss(line);
        string id, type, floor, capacity, price;
        bool isAvailable;

        getline(ss, id, ';');
        getline(ss, type, ';');
        getline(ss, floor, ';');
        getline(ss, capacity, ';');
        getline(ss, price, ';');
        try {
            int floorNum = stoi(floor);
            int capacityNum = stoi(capacity);
            int priceNum = stoi(price);
            Phong room(id, type, floorNum, capacityNum, true, priceNum);
            addRoom(room);
        } catch (const invalid_argument& e) {
            cerr << "Loi doc du lieu tai dong: " << line << endl;
            continue;
        }
    }
    file.close();
}

void LinkedlistPhong::calculateRoom(const string& roomID) {
 
    Phong* room = findRoom(roomID);
    if (room != NULL) {
        int Cost = room->tienthuephong();
        cout << "Tien thue phong la: " << Cost << " VND.\n";
    } else {
        cout << "Khong tim thay phong voi ma phong da nhap.\n";
    }
}
bool LinkedlistPhong::isRoomExit(const string& roomID) const{
	Node* temp = head;
	while (temp != NULL) {
		if (temp->room.getRoomID() == roomID ) {
			return true;
		}
		temp = temp->next;
 	}
 	return false;
	
}
void LinkedlistPhong::sortRooms() {
    if (head == NULL || head->next == NULL) {
        return;
    }
    bool swap;
    Node* p1;
    Node* p2 = NULL;
    do {
        swap = false;
        p1 = head;
        while (p1->next != p2) {
            if (p1->room.getRoomID() < p1->next->room.getRoomID()) {
                Phong temp = p1->room;
                p1->room = p1->next->room;
                p1->next->room = temp;
                swap = true;
            }
            p1 = p1->next;
        }
        p2 = p1;
    } while (swap);
}
bool LinkedlistPhong::editRoom(const string& roomID) {
    Phong* room = findRoom(roomID);
    if (room == NULL) {
        cout << "Khong tim thay phong voi ma so: " << roomID << endl;
        return false;
    }

    cout << "Cap nhat thong tin phong co ma: " << roomID << endl;
    cout << "Nhap loai phong moi (Hien tai: " << room->getRoomType() << "): ";
    string newType;
    cin.ignore();
    getline(cin, newType);

    cout << "Nhap so tang moi (Hien tai: " << room->getRoomFloor() << "): ";
    int newFloor;
    cin >> newFloor;

    cout << "Nhap suc chua moi (Hien tai: " << room->getRoomCapacity() << "): ";
    int newCapacity;
    cin >> newCapacity;

    cout << "Nhap gia phong moi (Hien tai: " << room->getRoomPrice() << "): ";
    int newPrice;
    cin >> newPrice;

    cout << "Nhap trang thai moi (1: Trong, 0: Da co khach, Hien tai: " 
         << (room->getIsAvailable() ? "Trong" : "Da co khach") << "): ";
    bool newAvailability;
    cin >> newAvailability;
    room->setRoomType(newType);
    room->setRoomFloor(newFloor);
    room->setRoomCapacity(newCapacity);
    room->setRoomPrice(newPrice); 
    room->setIsAvailable(newAvailability);

    cout << "Cap nhat thong tin phong thanh cong!" << endl;
    return true;
}

bool LinkedlistPhong::DateTime(int& ngay, int& thang, int& nam, int& gio) {   
    do {
        cout << "Nhap ngay (1-31): ";
        if (!(cin >> ngay)) {
            cout << "Vui long nhap so!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (ngay < 1 || ngay > 31) {
            cout << "Ngay khong hop le!\n";
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Nhap thang (1-12): ";
        if (!(cin >> thang)) {
            cout << "Vui long nhap so!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (thang < 1 || thang > 12) {
            cout << "Thang khong hop le!\n";
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Nhap nam (>= 2024): ";
        if (!(cin >> nam)) {
            cout << "Vui long nhap so!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (nam < 2024) {
            cout << "Nam khong hop le!\n";
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Nhap gio (0-23): ";
        if (!(cin >> gio)) {
            cout << "Vui long nhap so!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (gio < 0 || gio > 23) {
            cout << "Gio khong hop le!\n";
            continue;
        }
        break;
    } while (true);

    int ngayTrongThang[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (nam % 4 == 0 && (nam % 100 != 0 || nam % 400 == 0)) {
        ngayTrongThang[1] = 29;
    }
    
    if (ngay > ngayTrongThang[thang - 1]) {
        cout << "Ngay khong hop le voi thang " << thang << "!\n";
        return false;
    }

    return true;
}
void LinkedlistPhong::outputDateTime(const string& time) {
    cout << "\nNhap thoi gian " << time << ":\n";
}
void LinkedlistPhong::bookRoom(const string& roomID) {
    Phong* room = findRoom(roomID);
    if (room == NULL) {
        cout << "Khong tim thay phong voi ma so: " << roomID << endl;
        return;
    }
    if (!room->getIsAvailable()) {
        cout << "Phong da co khach!" << endl;
        return;
    }
    cout << "\nThong tin phong:\n";
    cout << string(85, '=') << endl;
    cout << left 
        << setw(10) << "RoomID" << " | " 
        << setw(12) << "RoomType" << " | " 
        << setw(14) << "Status" << " | " 
        << setw(8) << "Floor" << " | " 
        << setw(10) << "Capacity" << " | " 
        << setw(15) << "Price(VND/hour)" << endl;
    cout << string(85, '=') << endl;
    room->displayRoomInfo();
    cout << string(85, '=') << endl;
    char choice;
    do {
        cout << "Ban co chac chan muon dat phong nay? (y/n): ";
        cin >> choice;
        choice = tolower(choice);
        if (choice != 'y' && choice != 'n') {
            cout << "Vui long chi nhap 'y' hoac 'n'!\n";
        }
    } while (choice != 'y' && choice != 'n');
    if (choice == 'n') {
        cout << "Da huy dat phong!\n";
        return;
    }
    string tenKH, cccd, sdt, queQuan;
    cout << "\n============================ NHAP THONG TIN KHACH HANG ============================\n";
    cout << "Nhap ten khach hang: ";
    cin.ignore();
    getline(cin, tenKH);
    cout << "CCCD: ";
    getline(cin, cccd);
    cout << "So dien thoai: ";
    getline(cin, sdt);
    cout << "Que quan: ";
    getline(cin, queQuan);

    Khachhang kh(tenKH, cccd, sdt, queQuan);
    tm checkin={};
    int ngayVao, thangVao, namVao, gioVao;
    outputDateTime("check-in");
    if(!DateTime(ngayVao, thangVao, namVao, gioVao)) {
        cout << "Ngay thang nam khong hop le!\n";
        return;
    }
    checkin.tm_year = namVao - 1900;
    checkin.tm_mon = thangVao - 1;
    checkin.tm_mday = ngayVao;
    checkin.tm_hour = gioVao;
    cout << "\nXac nhan thong tin dat phong:\n";
    cout << string(85, '=') << endl;
    cout << "Ma phong: " << roomID << endl;
    cout << "Loai phong: " << room->getRoomType() << endl;
    cout << "Gia phong/gio: " << room->getRoomPrice() << " VND" << endl;
    cout << "\nThong tin khach hang:\n";
    cout << string(65, '=') << endl;
    kh.displayInfoKH();
    cout << string(65, '=') << endl;
    cout << "Thoi gian check-in: " << ngayVao << "/" << thangVao << "/" << namVao 
         << " " << gioVao << ":00\n" << endl;
    cout << string(85, '=') << endl;
    do {
        cout << "Xac nhan dat phong? (y/n): ";
        cin >> choice;
        choice = tolower(choice);
        if (choice != 'y' && choice != 'n') {
            cout << "Vui long chi nhap 'y' hoac 'n'!\n";
        }
    } while (choice != 'y' && choice != 'n');

    if (choice == 'n') {
        cout << "Da huy dat phong!\n";
        return;
    }

    room->setIsAvailable(false);
    room->setCheckIn(checkin);

    ifstream outfileCheck("Khachhang.txt");
    if (outfileCheck.is_open()) {
        outfileCheck.close();
    }
    ofstream outfile("Khachhang.txt", ios::app);
    if (outfile.is_open()) {
        outfile << roomID << ";" 
               << checkin.tm_mday << "/" << checkin.tm_mon + 1 << "/" << checkin.tm_year + 1900 
               << " " << checkin.tm_hour << ":00" << ";" 
               << tenKH << ";" << cccd << ";" << sdt << ";" << queQuan << endl;
        outfile.close();
        cout << "\nDa ghi thong tin khach hang vao file thanh cong!\n";
        cout << "Da dat phong thanh cong!\n";
    } else {
        room->setIsAvailable(true);
        cout << "Khong the ghi file!\n";
        cout << "Dat phong that bai!\n";
    }
}

void LinkedlistPhong::checkOutRoom(const string& roomID) {
    Phong* room = findRoom(roomID);
    if (room == NULL) {
        cout << "Khong tim thay phong voi ma so: " << roomID << endl;
        return;
    }
    if (room->getIsAvailable()) {
        cout << "Phong chua duoc khach dat!" << endl;
        return;
    }

    cout << "\nThong tin phong:\n";
    cout << string(85, '=') << endl;
    cout << left 
        << setw(10) << "RoomID" << " | " 
        << setw(12) << "RoomType" << " | " 
        << setw(14) << "Status" << " | " 
        << setw(8) << "Floor" << " | " 
        << setw(10) << "Capacity" << " | " 
        << setw(15) << "Price(VND/hour)" << endl;
    cout << string(85, '=') << endl;
    room->displayRoomInfo();
    cout << string(85, '=') << endl;

    ifstream infile("Khachhang.txt");
    string line;
    string tenKH, cccd, sdt, queQuan, checkinStr;
    bool found = false;

    while (getline(infile, line)) {
        stringstream ss(line);
        string fileRoomID;
        getline(ss, fileRoomID, ';');
        if (fileRoomID == roomID) {
            getline(ss, checkinStr, ';');
            getline(ss, tenKH, ';');
            getline(ss, cccd, ';');
            getline(ss, sdt, ';');
            getline(ss, queQuan);
            found = true;
            break;
        }
    }
    infile.close();

    if (!found) {
        cout << "Khong tim thay khach hang nao dat phong " << roomID << endl;
        return;
    }

    cout << "\nThong tin khach hang:\n";
    cout << string(65, '=') << endl;
    cout << left << setw(15) << "Ho ten" << " | "
         << setw(15) << "CCCD" << " | "
         << setw(15) << "SDT" << " | "
         << setw(15) << "Que quan" << endl;
    cout << string(65, '=') << endl;
    cout << left << setw(15) << tenKH << " | "
         << setw(15) << cccd << " | "
         << setw(15) << sdt << " | "
         << setw(15) << queQuan << endl;
    cout << string(65, '=') << endl;
    cout << "Thoi gian check-in: " << checkinStr << endl;

    tm checkout = {};
    int ngayRa, thangRa, namRa, gioRa;
    outputDateTime("check-out");
    if (!DateTime(ngayRa, thangRa, namRa, gioRa)) {
        cout << "Ngay thang nam khong hop le!\n";
        return;
    }
    tm checkin = room->getCheckIn();
    bool isValid = true;
    
    if (namRa < checkin.tm_year + 1900) {
        isValid = false;
    } else if (namRa == checkin.tm_year + 1900) {
        if (thangRa < checkin.tm_mon + 1) {
            isValid = false;
        } else if (thangRa == checkin.tm_mon + 1) {
            if (ngayRa < checkin.tm_mday) {
                isValid = false;
            } else if (ngayRa == checkin.tm_mday) {
                if (gioRa <= checkin.tm_hour) {
                    isValid = false;
                }
            }
        }
    }

    if (!isValid) {
        cout << "Thoi gian check-out phai sau thoi gian check-in!\n";
        return;
    }

    checkout.tm_mday = ngayRa;
    checkout.tm_mon = thangRa - 1;
    checkout.tm_year = namRa - 1900;
    checkout.tm_hour = gioRa;
    room->setCheckOut(checkout);

    cout << "\n=================== HOA DON THANH TOAN ===================\n";
    cout << "Ma hoa don: HD" << roomID << "_" << ngayRa << thangRa << namRa << endl;
    cout << "Ngay lap: " << ngayRa << "/" << thangRa << "/" << namRa << endl;
    cout << "\nTHONG TIN KHACH HANG:\n";
    cout << "Ho va ten: " << tenKH << endl;
    cout << "CCCD: " << cccd << endl;
    cout << "So dien thoai: " << sdt << endl;
    cout << "Que quan: " << queQuan << endl;
    cout << "\nTHONG TIN PHONG:\n";
    cout << "Ma phong: " << roomID << endl;
    cout << "Loai phong: " << room->getRoomType() << endl;
    cout << "Gia phong/gio: " << room->getRoomPrice() << " VND" << endl;
    cout << "Thoi gian check-in: " << checkinStr << endl;
    cout << "Thoi gian check-out: " << ngayRa << "/" << thangRa << "/" << namRa 
         << " " << gioRa << ":00" << endl;
    cout << "Thoi gian thue: " << room->thoigianthue() << " gio" << endl;
    cout << "\nTHANH TOAN:\n";
    cout << "Tong tien phong: " << room->tienthuephong() << " VND" << endl;
    cout << "=======================================================\n";

    char choice;
    do {
        cout << "Xac nhan thanh toan va tra phong? (y/n): ";
        cin >> choice;
        choice = tolower(choice);
        if (choice != 'y' && choice != 'n') {
            cout << "Vui long chi nhap 'y' hoac 'n'!\n";
        }
    } while (choice != 'y' && choice != 'n');

    if (choice == 'n') {
        cout << "Da huy tra phong!\n";
        return;
    }

    room->setIsAvailable(true);
    cout << "\nTra phong thanh cong!\n";

    ofstream outFile("hoadon.txt", ios::app);
    if (outFile.is_open()) {
        outFile << "HD" << roomID << "_" << ngayRa << thangRa << namRa << ";"
               << ngayRa << "/" << thangRa << "/" << namRa << ";"
               << tenKH << ";"
               << cccd << ";"
               << roomID << ";"
               << checkinStr << ";"
               << ngayRa << "/" << thangRa << "/" << namRa << " " << gioRa << ":00" << ";"
               << room->thoigianthue() << ";"
               << room->tienthuephong() << endl;
        outFile.close();
    } else {
        cout << "Khong the luu thong tin hoa don!\n";
    }
}

