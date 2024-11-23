#include <iostream>
#include <conio.h>
#include <string>
#include "Phong.h"
#include "Person.h"
#include "Letan.h"
#include "Khachhang.h"

using namespace std;

string adminPassword;
LinkedListLetan listletan;
LinkedlistPhong listphong;
void createAdminpassword();
void PhongMenu(LinkedlistPhong& listphong);
void LetanMenu(LinkedListLetan& listletan);
void KhachhangMenu();
void adminMenu();
void userMenu(LinkedListLetan& listletan);
bool adminLogin();
void createAdminpassword () {
	string tempPassword, tempPassword2;
	do {
		cout << "Hay tao mat khau cho admin: ";
        char ch;
        tempPassword = "";
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if(tempPassword.length() > 0) {
                    cout << "\b \b";
                    tempPassword.pop_back();
                }
            } else {
                    cout << "*";
                    tempPassword += ch;
            }
        }
        cout << endl;
		cout << "Nhap lai mat khau: ";
        tempPassword2 = "";
		while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if(tempPassword2.length() > 0) {
                    cout << "\b \b";
                    tempPassword2.pop_back();
                }
            } else {
                cout << "*";
                tempPassword2 += ch;
            }
		}
		cout << endl;
		if (tempPassword == tempPassword2) {
			adminPassword  = tempPassword;
			cout << "Tao mat khau thanh cong!\n";
			system("cls");
			break;
		}
		else {
			cout << "Tao mat khau khong thanh cong, xin vui long thu lai!\n";
		}
	} while (true);
}

bool adminLogin() {
	string password;
    int temp = 0;
    const int max_temp = 3;
	cout << "\n========== DANG NHAP ADMIN ==========\n";
    do {
        cout << "Nhap mat khau:";
        char ch;
        password = "";
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if(password.length() > 0) {
                    cout << "\b \b";
                    password.pop_back();
                }
            } else {
                cout << "*";
                password += ch;
            }
        }
        cout << endl;
        if (password  == adminPassword) {
            cout << "Dang nhap thanh cong admin!\n";
            return true;
        }
        temp++; 
        if (temp < max_temp) {
            cout << "Mat khau khong dung!\n";
            cout << "Ban con " << max_temp - temp << " lan thu.\n";
         }
    } while (temp < max_temp);
    cout << "Ban da nhap sai qua " << max_temp<<  " lan. Vui long thu lai sau!\n";
    return false;
}
bool LinkedListLetan::userLogin(const LinkedListLetan& listletan) {
    string cccd, password;
    int temp = 0;
    const int MAX_TEMP = 3;
    
    do {
        cout << "\n========== DANG NHAP USER ==========\n";
        cout << "Nhap CCCD: ";
        getline(cin, cccd);
        cout << "Nhap mat khau (ngay sinh): ";
        getline(cin, password);
        
        NodeLT* node = head;
        bool found = false;
        while (node != NULL) {
            if (node->data.getCccd() == cccd) {
                found = true;
                if (node->data.getBirthdayLT() == password) {
                    cout << "\nDang nhap thanh cong!\n";
                    cout << "Xin chao, " << node->data.getName() << "!\n";
                    return true;
                } else {
                    cout << "Mat khau khong dung!\n";
                    temp++;
                    break;
                }
            }
            node = node->next;
        }
        
        if (!found) {
            cout << "CCCD khong ton tai trong he thong!\n";
            temp++;
        }
        
        if (temp < MAX_TEMP) {
            cout << "Con " << MAX_TEMP - temp << " lan thu.\n";
        }
        
    } while (temp < MAX_TEMP);
    
    cout << "Ban da nhap sai qua " << MAX_TEMP << " lan. Vui long thu lai sau!\n";
    return false;
} 

void adminMenu() {
	int choice;
	do {
	cout << "\n========== MENU ADMIN ==========\n";
	cout << "1. Quan ly phong\n";
	cout << "2. Quan ly le tan\n";
	cout << "3. Quan ly thong tin khach hang\n";
	cout << "0. Dang xuat\n";
	cout << "Hay nhap lua chon: ";
 	cin >> choice;
    cin.ignore();
        switch (choice) {
            case 1:
                PhongMenu(listphong);
                break;
            case 2:
                LetanMenu(listletan);
                break;
            case 3:
                KhachhangMenu();
                break;
            case 0:
                cout << "Thoat chuong trinh...\n";
                return;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
        }
    } while (true); 	
	
}

void userMenu(LinkedListLetan& listletan) {
    int choice;
    do {
        cout << "\n========== MENU USER ==========\n";
        cout << "1. Quan ly phong\n";
        cout << "2. Quan ly khach hang\n";
        cout << "0. Dang xuat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                int phongChoice;
                char tieptuc;
                do {
                    cout << "\n========== QUAN LY PHONG ==========\n";
                    cout << "1. Hien thi danh sach phong\n";
                    cout << "2. Cap nhat trang thai phong\n";
                    cout << "3. Tim phong\n";
                    cout << "4. Tinh gia tien phong\n";
                    cout << "0. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    cin >> phongChoice;
                    cin.ignore();

                    switch (phongChoice) {
                        case 1: {
                            listphong.displayRooms();
                            break;
                        }
                        case 2: {
                            string roomID;
                            int trangthai;
                            bool newtrangthai;
                            
                            cout << "Nhap ma phong can cap nhat trang thai: ";
                            cin >> roomID;
                            while (true) {
                                cout << "Nhap trang thai moi cua phong (1 - Trong, 0 - Da co khach): ";
                                cin >> trangthai;
                                if (trangthai == 0 || trangthai == 1) {
                                    newtrangthai = (trangthai == 1);
                                    break;
                                } else {
                                    cout << "Gia tri khong hop le, vui long thu lai.\n";
                                }
                            }
                            if (listphong.updateRoom(roomID, newtrangthai)) {
                                cout << "Trang thai phong da cap nhat thanh cong.\n";
                            } else {
                                cout << "Cap nhat trang thai phong that bai!\n";
                            }
                            break;
                        }
                        case 3: {
                            string roomID;
                            cout << "Nhap ma phong can tim: ";
                            cin >> roomID;
                            Phong* room = listphong.findRoom(roomID);
                            if (room != NULL) {
                                cout << "=============================================================================\n";
                                room->displayRoomInfo();
                                cout << "=============================================================================\n";
                            } else {
                                cout << "Khong tim thay phong!\n";
                            }
                            break;
                        }
                        case 4: {
                            string roomID;
                            cout << "Nhap ma phong can tinh tien: ";
                            cin >> roomID;
                            Phong* room = listphong.findRoom(roomID);
                            if (room != nullptr) {
                                if (room->getIsAvailable()) {
                                    cout << "Phong nay hien dang trong, khong the tinh tien!\n";
                                    break;
                                }
                                
                                tm checkin = {}, checkout = {};
                                int ngayVao, thangVao, namVao, gioVao;
                                int ngayRa, thangRa, namRa, gioRa;
                                
                                cout << "Nhap thoi gian check-in (ngay thang nam gio): ";
                                cin >> ngayVao >> thangVao >> namVao >> gioVao;
                                cout << "Nhap thoi gian check-out (ngay thang nam gio): ";
                                cin >> ngayRa >> thangRa >> namRa >> gioRa;
                                
                                checkin.tm_mday = ngayVao;
                                checkin.tm_mon = thangVao - 1;
                                checkin.tm_year = namVao - 1900;
                                checkin.tm_hour = gioVao;
                                
                                checkout.tm_mday = ngayRa;
                                checkout.tm_mon = thangRa - 1;
                                checkout.tm_year = namRa - 1900;
                                checkout.tm_hour = gioRa;
                                
                                room->setCheckIn(checkin);
                                room->setCheckOut(checkout);
                                
                                cout << "\nThong tin tinh tien phong " << roomID << ":\n";
                                cout << "Loai phong: " << room->getRoomType() << endl;
                                cout << "Gia phong/gio: " << room->getRoomPrice() << " VND" << endl;
                                cout << "Thoi gian thue: " << room->thoigianthue() << " gio" << endl;
                                cout << "Tong tien: " << room->tienthuephong() << " VND" << endl;
                            }
                            break;
                        }
                        case 0:
                            break;
                        default:
                            cout << "Lua chon khong hop le!\n";
                            break;
                    }

                    if (phongChoice != 0) {
                        do {
                            cout << "Ban co muon tiep tuc quan ly phong? (y/n): ";
                            cin >> tieptuc;
                            cin.ignore();
                            if (tieptuc == 'n' || tieptuc == 'N') {
                                break;
                            } else if (tieptuc == 'y' || tieptuc == 'Y') {
                                break;
                            } else {
                                cout << "Lua chon khong hop le!\n";
                            }
                        } while (true);
                        if (tieptuc == 'n' || tieptuc == 'N') break;
                    }
                } while (phongChoice != 0);
                break;
            }
            case 2:
                KhachhangMenu();
                break;
            case 0:
                cout << "Thoat menu user.\n";
                return;
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }
    } while (true);
}

void PhongMenu(LinkedlistPhong& listphong) {
    int choice;
    string roomID;
    char tieptuc;
    do {
        cout << "\n========== QUAN LY PHONG ==========\n";
        cout << "1. Hien thi danh sach phong\n";
        cout << "2. Dat phong\n";
        cout << "3. Tra phong\n";
        cout << "4. Tim phong\n";
        cout << "5. Xoa phong\n";
        cout << "6. Them phong\n";
        cout << "7. Sua thong tin phong\n";
        cout << "0. Quay lai\n";
        cout << "Hay nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                listphong.displayRooms();
                break;
            }
            case 2: {
                cout << "Nhap ma phong muon dat: ";
                getline(cin, roomID);
                listphong.bookRoom(roomID);
                break;
            }
            case 3: {
                cout << "Nhap ma phong muon tra: ";
                getline(cin, roomID);
                listphong.checkOutRoom(roomID);
                break;
            }
            case 4: {
                cout << "Nhap ma phong can tim: ";
                getline(cin, roomID);
                Phong* room = listphong.findRoom(roomID);
                if (room != NULL) {
                    cout << "===================================================================================\n";
                    room->displayRoomInfo();
                    cout << "===================================================================================\n";
                } else {
                    cout << "Khong tim thay phong voi ma phong: " << roomID << endl;
                }
                break;
            }
            case 5: {
                cout << "Nhap ma phong can xoa: ";
                getline(cin, roomID);
                Phong* room = listphong.findRoom(roomID);
                if (room != nullptr) {
                    char xacnhan;
                    cout << "\nThong tin phong can xoa:\n";
                    cout << "=============================================================================\n";
                    room->displayRoomInfo();
                    cout << "=============================================================================\n";
                    
                    do {
                        cout << "Ban co chac chan muon xoa phong nay? (y/n): ";
                        cin >> xacnhan;
                        xacnhan = tolower(xacnhan);
                        
                        if (xacnhan != 'y' && xacnhan != 'n') {
                            cout << "Vui long chi nhap 'y' hoac 'n'!\n";
                        }
                    } while (xacnhan != 'y' && xacnhan != 'n');
                    
                    if (xacnhan == 'y') {
                        listphong.deleteRoom(roomID);
                        cout << "\nDa xoa phong " << roomID << " thanh cong!\n";
                    } else {
                        cout << "Da huy xoa phong!\n";
                    }
                } else {
                    cout << "Khong tim thay phong co ma " << roomID << " de xoa!\n";
                }
                break;
            }
            case 6: {
                string roomID, loaiPhong;
                int tang, sucChua, giaPhong;
                bool isAvailable;
                
                cout << "Nhap ma phong: ";
                cin >> roomID;
                cin.ignore();
                
                if (listphong.isRoomExit(roomID)) {
                    cout << "Phong " << roomID << " da ton tai, vui long nhap lai.\n";
                    break;
                }
                
                do {
                    cout << "Nhap loai phong (Standard/VIP/Deluxe): ";
                    getline(cin, loaiPhong);
                    if (loaiPhong == "Standard" || loaiPhong == "standard") {
                        loaiPhong = "Standard";
                        break;
                    } else if (loaiPhong == "VIP" || loaiPhong == "vip" || loaiPhong == "Vip") {
                        loaiPhong = "VIP";
                        break;
                    } else if (loaiPhong == "Deluxe" || loaiPhong == "deluxe") {
                        loaiPhong = "Deluxe";
                        break;
                    } else {
                        cout << "Loai phong khong hop le! Vui long nhap lai.\n";
                    }
                } while (true);
                
                cout << "Nhap tang cua phong: ";
                cin >> tang;
                cout << "Nhap suc chua cua phong: ";
                cin >> sucChua;
                cout << "Nhap gia phong: ";
                cin >> giaPhong;
                
                isAvailable = true;
                
                Phong newRoom(roomID, loaiPhong, tang, sucChua, isAvailable, giaPhong);
                listphong.addRoom(newRoom);
                cout << "Them phong thanh cong!\n";
                break;
            }
            case 7: {
                cout << "Nhap ma phong can sua: ";
                getline(cin, roomID);
                Phong* room = listphong.findRoom(roomID);
                if (room != nullptr) {
                    cout << "\nThong tin phong hien tai:\n";
                    cout << "=============================================================================\n";
                    room->displayRoomInfo();
                    cout << "=============================================================================\n";
                    
                    listphong.editRoom(roomID);
                } else {
                    cout << "Khong tim thay phong co ma " << roomID << "!\n";
                }
                break;
            }
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
        }
        do {
            cout << "Ban co muon tiep tuc lua chon khac khong? (y/n): ";
            cin >> tieptuc;
            cin.ignore();
            if (tieptuc == 'n' || tieptuc == 'N') {
                return;
            } else if (tieptuc == 'y' || tieptuc == 'Y') {
                break;
            } else {
                cout << "Lua chon khong hop le! Vui long nhap 'y' hoac 'n'.\n";
            }
        } while (true);
    } while (true);
}

void LetanMenu(LinkedListLetan& listletan) {
    int choice;
    char tieptuc;
    do {
        cout << "\n========== QUAN LY LE TAN ==========\n";
        cout << "1. Hien thi danh sach cac thong tin le tan\n";
        cout << "2. Quan ly ngay lam viec le tan\n";
        cout << "3. Sua thong tin le tan\n";
        cout << "4. Xoa le tan\n";
        cout << "5. Them le tan\n";
        cout << "0. Quay lai\n";
        cout << "Hay nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "\nDanh sach le tan:\n";
                cout << "===========================================================================================\n";
                listletan.displayLetan();
                break;
            }
            case 2: {
                string cccd;
                cout << "\nDanh sach le tan va ngay lam viec:\n";
                cout << "=============================================================================\n";
                NodeLT* current = listletan.getHead();
                while (current != NULL) {
                    cout << "Le tan: " << setw(30) << left << current->data.getName() 
                         << " | CCCD: " << setw(12) << current->data.getCccd()
                         << " | Ngay lam: " << current->data.getWorkdayLT() << endl;
                    current = current->next;
                }
                cout << "=============================================================================\n";     
                
                cout << "Nhap CCCD cua le tan can cap nhat ngay lam viec: ";
                getline(cin, cccd);
                NodeLT* letan = listletan.findLetan(cccd);      
                
                if (letan != NULL) {
                    string newWorkday;
                    bool isValidWorkday;
                    
                    cout << "Ngay lam viec hien tai: " << letan->data.getWorkdayLT() << endl;
                    
                    do {
                        isValidWorkday = true;
                        cout << "Nhap ngay lam viec moi: ";
                        getline(cin, newWorkday);
    
                        if (newWorkday == letan->data.getWorkdayLT()) {
                            cout << "Ban dang nhap trung voi ngay lam viec hien tai!\n";
                            isValidWorkday = false;
                            continue;
                        }
                        current = listletan.getHead();
                        while (current != NULL) {
                            if (current != letan && current->data.getWorkdayLT() == newWorkday) {
                                cout << "Ngay lam viec da duoc phan cong cho le tan:\n";
                                cout << "Ten: " << current->data.getName() 
                                     << " (CCCD: " << current->data.getCccd() << ")\n";
                                isValidWorkday = false;
                                break;
                            }
                            current = current->next;
                        }
                        
                        if (isValidWorkday) {
                            letan->data.setWorkdayLT(newWorkday);
                            cout << "Cap nhat ngay lam viec thanh cong!\n";
                            cout << "\nDanh sach sau khi cap nhat:\n";
                            cout << "=============================================================================\n";
                            current = listletan.getHead();
                            while (current != NULL) {
                                cout << "Le tan: " << setw(30) << left << current->data.getName() 
                                     << " | CCCD: " << setw(12) << current->data.getCccd()
                                     << " | Ngay lam: " << current->data.getWorkdayLT() << endl;
                                current = current->next;
                            }
                            cout << "=============================================================================\n";
                        } else {
                            cout << "Vui long nhap ngay lam viec khac!\n";
                        }
                        
                    } while (!isValidWorkday);
                }
                break;
            }
            
            case 3: {
                string cccd;
                cout << "Nhap CCCD cua le tan can sua thong tin: ";
                getline(cin, cccd);
                listletan.updateLetan(cccd);
                break;
            }
            
            case 4: {
                string cccd;
                cout << "Nhap CCCD cua le tan can xoa: ";
                getline(cin, cccd);
                NodeLT* letan = listletan.findLetan(cccd);
                if (letan != nullptr) {
                    char xacnhan;
                    cout << "\nThong tin le tan can xoa:\n";
                    cout << "=============================================================================\n";
                    letan->data.displayInfoLT();
                    cout << "=============================================================================\n";
                    
                    do {
                        cout << "Ban co chac chan muon xoa le tan nay? (y/n): ";
                        cin >> xacnhan;
                        xacnhan = tolower(xacnhan);
                        
                        if (xacnhan != 'y' && xacnhan != 'n') {
                            cout << "Vui long chi nhap 'y' hoac 'n'!\n";
                        }
                    } while (xacnhan != 'y' && xacnhan != 'n');
                    
                    if (xacnhan == 'y') {
                        listletan.deteleLetan(cccd);
                        cout << "Da xoa le tan thanh cong!\n";
                    } else {
                        cout << "Da huy xoa le tan!\n";
                    }
                }
                break;
            }
            case 5: {
                string name, cccd, phone, email, birthday, workday;
                cout << "Nhap thong tin le tan moi:\n";
                cout << "Ho va ten: ";
                getline(cin, name);
                cout << "CCCD: ";
                getline(cin, cccd);
                cout << "So dien thoai: ";
                getline(cin, phone);
                cout << "Email: ";
                getline(cin, email);
                cout << "Ngay sinh: ";
                getline(cin, birthday);
                cout << "Ngay lam viec: ";
                getline(cin, workday);
                
                Letan newLetan(name, cccd, phone, email, birthday, workday);
                listletan.addLetan(newLetan);
                cout << "Them le tan thanh cong!\n";
                break;
            }
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
        }
        do {
            cout << "Ban co muon tiep tuc lua chon khac khong? (y/n): ";
            cin >> tieptuc;
            cin.ignore();
            if (tieptuc == 'n' || tieptuc == 'N') {
                return;
            } else if (tieptuc == 'y' || tieptuc == 'Y') {
                break;
            } else {
                cout << "Lua chon khong hop le! Vui long nhap 'y' hoac 'n'.\n";
            }
        } while (true);
    } while (true); 
}

void KhachhangMenu() {
    int choice;
    char tieptuc;
    do {
        cout << "\n========== QUAN LY THONG TIN KHACH HANG ==========\n";
        cout << "1. Cap nhat luu thong tin khach hang\n";
        cout << "2. Xem danh sach thong tin khach hang\n";
        cout << "3. Tim kiem thong tin khach hang\n";
        cout << "0. Quay lai\n";
        cout << "Hay nhap lua chon: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                // Cập nhật thông tin khách hàng
                break;
            case 2:
                // Xem danh sách khách hàng
                break;
            case 3:
                // Tim kiem thong tin khach hang
                break;
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
        }
    } while (true);
}

int main() {

	createAdminpassword();
	listletan.readLetanFile("danhsachletan.txt");
	listphong.readRoomsFile("danhsachphong.txt");
	int choice;
    bool loggedIn = false;
    do {
        cout << "========== CHON LOAI DANG NHAP ==========\n";
        cout << "1. Dang nhap admin\n";
        cout << "2. Dang nhap user\n";
        cout << "0. Thoat\n";
        cout << "Hay nhap lua chon: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                if (adminLogin()) {
                    adminMenu();
                }
                break;
        	}
            case 2:{ 
                if (listletan.userLogin(listletan)) {
                    userMenu(listletan);
                break;
       			} 
     			}
            case 0: {
                cout << "Thoat chuong trinh.\n";
                break; 
            }
            default: {
                cout << "Lua chon khong hop le, vui long nhap lai.\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;  
}