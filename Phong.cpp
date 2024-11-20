#include "phong.h"
#include <iomanip>
Phong::Phong(string id, string type, int floor, int capacity, bool available, int price)
    : roomID(id), roomType(type), roomFloor(floor), roomCapacity(capacity), isAvailable(true), roomPrice(price) {
    checkIn = {};
    checkOut = {};    
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

tm Phong::getCheckIn() const {
    return checkIn;
}

tm Phong::getCheckOut() const {
    return checkOut;
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

void Phong::setCheckIn(const tm& checkinTime) {
    checkIn = checkinTime;
}

void Phong::setCheckOut(const tm& checkoutTime) {
    checkOut = checkoutTime;
}
void Phong::setRoomType(const string& type) {
    roomType = type;
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
    if (checkIn.tm_year == 0 || checkOut.tm_year == 0) {
        return 0;
    }
    time_t inTime = mktime(const_cast<tm*>(&checkIn));
    time_t outTime = mktime(const_cast<tm*>(&checkOut));

    double thoigianthue = difftime(outTime, inTime); 
    return thoigianthue / 3600;
}

int Phong::tienthuephong() const {
    return thoigianthue()*roomPrice;
}


void LinkedlistPhong::addRoom(Phong room) {
    string type = room.getRoomType();
    if (type == "vip" || type == "VIP") {
        type = " VIP";
    } else if (type == "standard" || type == "Standard") {
        type = " Standard";
    } else if (type == "deluxe" || type == "Deluxe") {
        type = " Deluxe";
    }
    room.setRoomType(type);
    Node* newNode = new Node(room);
    newNode->next = head;
    head = newNode;
    sortRooms();
    
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
        getline(ss, id, ';');
        getline(ss, type, ';');
        getline(ss, floor, ';');
        getline(ss, capacity, ';');
        getline(ss, price, ';');
        Phong room(id, type, stoi(floor), stoi(capacity), true, stoi(price));
        addRoom(room);
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

    // Áp dụng cập nhật
    room->setRoomType(newType);
    room->setRoomFloor(newFloor);
    room->setRoomCapacity(newCapacity);
    room->setRoomPrice(newPrice); 
    room->setIsAvailable(newAvailability);

    cout << "Cap nhat thong tin phong thanh cong!" << endl;
    return true;
}
