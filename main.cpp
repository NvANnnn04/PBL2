#include <iostream>
#include <conio.h>
#include <string>
#include <limits>
#include "Phong.h"
#include "Person.h"
#include "Letan.h"
#include "Khachhang.h"

using namespace std;

string adminPassword;
LinkedListLetan listletan;
LinkedlistPhong listphong;
LinkedListKhachhang listkhachhang;
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
            case 1:
                PhongMenu(listphong);
                break;
            case 2:
                KhachhangMenu();
                break;
            case 0:
                cout << "Dang xuat thanh cong!\n";
                return;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
        }
    } while (true);
}

void PhongMenu(LinkedlistPhong& listphong) {
    int choice;
    string roomID;
    char tieptuc;
    do {
        
        cout << "\n===================== QUAN LY PHONG =====================\n";
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
                string roomID;
                getline(cin, roomID);
                listphong.findAndDisplayRoom(roomID);
                break;
            }   
            case 5: {
                cout << "Nhap ma phong can xoa: ";
                getline(cin, roomID);
                Phong* room = listphong.findRoom(roomID);
                if (room != nullptr) {
                    if (!room->getIsAvailable()) {
                        cout << "\nPhong " << roomID << " hien dang co khach thue!\n";
                        cout << "Khong the xoa phong dang co khach.\n";
                        break;
                    }


                    ifstream checkFile("khachhanghientai.txt");
                    string line;
                    bool hasCustomer = false;
                    while (getline(checkFile, line)) {
                        stringstream ss(line);
                        string fileRoomID;
                        getline(ss, fileRoomID, ';');
                        if (fileRoomID == roomID) {
                            hasCustomer = true;
                            break;
                        }
                    }
                    checkFile.close();

                    if (hasCustomer) {
                        cout << "\nPhong " << roomID << " dang co thong tin khach hang!\n";
                        cout << "Khong the xoa phong co thong tin khach hang.\n";
                        break;
                    }

                    cout << "\nThong tin phong can xoa:\n";
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
                    
                    cout << "Luu y: Thong tin lich su khach hang va hoa don cua phong van duoc giu lai.\n";
                    char xacnhan;
                    do {
                        cout << "Ban co chac chan muon xoa phong nay? (y/n): ";
                        cin >> xacnhan;
                        xacnhan = tolower(xacnhan);
                        
                        if (xacnhan != 'y' && xacnhan != 'n') {
                            cout << "Vui long chi nhap 'y' hoac 'n'!\n";
                        }
                    } while (xacnhan != 'y' && xacnhan != 'n');
                    
                    if (xacnhan == 'y') {
                        if (listphong.deleteRoom(roomID)) {
                            cout << "\nDa xoa phong " << roomID << " thanh cong!\n";
                            cout << "Thong tin lich su khach hang va hoa don van duoc luu tru.\n";
                        } else {
                            cout << "Xoa phong that bai!\n";
                        }
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
       
        cout << "\n===================== QUAN LY LE TAN =====================\n";
        cout << "1. Hien thi danh sach cac thong tin le tan\n";
        cout << "2. Quan ly ngay lam viec le tan\n";
        cout << "3. Sua thong tin le tan\n";
        cout << "4. Xoa le tan\n";
        cout << "5. Them le tan\n";
        cout << "6. Tim kiem le tan\n";
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
                cout << "===========================================================================================\n";
                NodeLT* current = listletan.getHead();
                while (current != NULL) {
                    cout << "Le tan: " << setw(30) << left << current->data.getName() 
                         << " | CCCD: " << setw(12) << current->data.getCccd()
                         << " | Ngay lam: " << current->data.getWorkdayLT() << endl;
                    current = current->next;
                }
                cout << "===========================================================================================\n";     
                
                cout << "Nhap CCCD cua le tan can cap nhat ngay lam viec: ";
                getline(cin, cccd);
                NodeLT* letan = listletan.findLetan(cccd);      
                
                if (letan != NULL) {
                    string newWorkday;
                    cout << "Ngay lam viec hien tai: " << letan->data.getWorkdayLT() << endl;
                    
                    do {
                        cout << "Nhap ngay lam viec moi: ";
                        getline(cin, newWorkday);

                        if (newWorkday == letan->data.getWorkdayLT()) {
                            cout << "Ban dang nhap trung voi ngay lam viec hien tai!\n";
                            continue;
                        }

                        if (listletan.updateWorkday(cccd, newWorkday)) {
                            cout << "Cap nhat ngay lam viec thanh cong!\n";
                            cout << "\nDanh sach sau khi cap nhat:\n";
                            cout << "===========================================================================================\n";
                            current = listletan.getHead();
                            while (current != NULL) {
                                cout << "Le tan: " << setw(30) << left << current->data.getName() 
                                     << " | CCCD: " << setw(12) << current->data.getCccd()
                                     << " | Ngay lam: " << current->data.getWorkdayLT() << endl;
                                current = current->next;
                            }
                            cout << "===========================================================================================\n";
                            break;
                        } else {
                            cout << "Vui long nhap ngay lam viec khac!\n";
                        }
                    } while (true);
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
            case 6: {
                string searchTerm;
                cout << "\n========== TIM KIEM LE TAN ==========\n";
                cout << "1. Tim theo CCCD\n";
                cout << "2. Tim theo ten\n";
                cout << "3. Tim theo ngay lam viec\n";
                cout << "Nhap lua chon: ";
                int searchChoice;
                cin >> searchChoice;
                cin.ignore();

                switch(searchChoice) {
                    case 1: {
                        cout << "Nhap CCCD can tim: ";
                        getline(cin, searchTerm);
                        NodeLT* result = listletan.findLetan(searchTerm);
                        if (result != nullptr) {
                            cout << "\nThong tin le tan:\n";
                            cout << string(85, '=') << endl;
                            result->data.displayInfoLT();
                            cout << string(85, '=') << endl;
                        }
                        break;
                    }
                    case 2: {
                        cout << "Nhap ten le tan can tim: ";
                        getline(cin, searchTerm);
                        listletan.findLetanByName(searchTerm);
                        break;
                    }
                    case 3: {
                        cout << "Nhap ngay lam viec can tim: ";
                        getline(cin, searchTerm);
                        listletan.findLetanByWorkday(searchTerm);
                        break;
                    }
                    default:
                        cout << "Lua chon khong hop le!\n";
                        break;
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

void KhachhangMenu() {
    int choice;
    char tieptuc;
    do {
        cout << "\n========== QUAN LY THONG TIN KHACH HANG ==========\n";
        cout << "1. Xem danh sach khach hang dang dat phong\n";
        cout << "2. Tim kiem khach hang\n";
        cout << "3. Cap nhat thong tin khach hang\n";
        cout << "4. Thong ke luong khach hang\n";
        cout << "0. Quay lai\n";
        
        bool validChoice = false;
        do {
            cout << "Hay nhap lua chon: ";
            cin >> choice;
            cin.ignore();

            if (cin.fail() || choice < 0 || choice > 4) {
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
                cout << "Lua chon khong hop le! Vui long chon 0, 1, 2, 3, hoac 4.\n";
            } else {
                validChoice = true;
            }
        } while (!validChoice);

        switch (choice) {
            case 1: {
                cout << "\n========== DANH SACH KHACH HANG DANG DAT PHONG ==========\n\n";
                ifstream file("khachhanghientai.txt");
                if (!file.is_open()) {
                    cout << "Khong co khach hang nao dang dat phong!\n";
                } else {
                    listkhachhang.readKhachHangFile("khachhanghientai.txt");
                    if (listkhachhang.getHead() == NULL) {
                        cout << "Khong co khach hang nao dang dat phong!\n";
                    } else {
                        listkhachhang.displayKhachhang();
                    }
                    file.close();
                }
                break;
            }
            case 2: {
                int searchChoice;
                do {
                    cout << "\n========== TIM KIEM KHACH HANG ==========\n";
                    cout << "1. Tim theo CCCD\n";
                    cout << "2. Tim theo ten\n";
                    cout << "0. Quay lai\n";
                    cout << "Nhap lua chon: ";
                    cin >> searchChoice;
                    cin.ignore();

                    switch(searchChoice) {
                        case 0:
                            break;
                        case 1: {
                            string cccd;
                            cout << "Nhap CCCD can tim: ";
                            getline(cin, cccd);
                            NodeKH* result = listkhachhang.findKhachhang(cccd);
                            if (result != NULL) {
                                cout << "\nThong tin khach hang:\n";
                                cout << string(120, '=') << endl;
                                cout << left << setw(10) << "RoomID" << "| "
                                     << left << setw(25) << "Check-in Time" << "| "
                                     << left << setw(20) << "Ho va ten" << "| " 
                                     << left << setw(15) << "CCCD" << "| "
                                     << left << setw(15) << "So dien thoai" << "| "
                                     << left << setw(20) << "Noi song" << endl;
                                cout << string(120, '-') << endl;

                                // Đọc thông tin phòng và thời gian từ file
                                ifstream file("khachhanghientai.txt");
                                string line;
                                while (getline(file, line)) {
                                    stringstream ss(line);
                                    string roomID, checkInTime, name, cccd;
                                    getline(ss, roomID, ';');
                                    getline(ss, checkInTime, ';');
                                    getline(ss, name, ';');
                                    getline(ss, cccd, ';');
                                    
                                    if (cccd == result->data.getCccd()) {
                                        cout << left << setw(10) << roomID << "| "
                                             << left << setw(25) << checkInTime << "| "
                                             << left << setw(20) << result->data.getName() << "| "
                                             << left << setw(15) << result->data.getCccd() << "| "
                                             << left << setw(15) << result->data.getSdt() << "| "
                                             << left << setw(20) << result->data.getQuequan() << endl;
                                        break;
                                    }
                                }
                                file.close();
                                cout << string(120, '=') << endl;
                            } else {
                                cout << "Khong tim thay khach hang co CCCD: " << cccd << endl;
                            }
                            break;
                        }
                        case 2: {
                            string name;
                            cout << "Nhap ten can tim: ";
                            getline(cin, name);
                            listkhachhang.findKhachHangByName(name);
                            break;
                        }
                        default:
                            cout << "Lua chon khong hop le! Vui long chon 0, 1 hoac 2.\n";
                            break;
                    }

                    if (searchChoice != 0) {
                        do {
                            cout << "\nBan co muon tim kiem tiep khong? (y/n): ";
                            cin >> tieptuc;
                            cin.ignore();
                            tieptuc = tolower(tieptuc);
                            
                            if (tieptuc == 'y' || tieptuc == 'n') {
                                break;
                            } else {
                                cout << "Vui long chi nhap 'y' hoac 'n'!\n";
                            }
                        } while (true);

                        if (tieptuc == 'n') {
                            break;
                        }
                    }
                } while (searchChoice != 0 && tieptuc == 'y');
                break;
            }
            case 3: {
                string cccd;
                cout << "Nhap CCCD cua khach hang can cap nhat: ";
                getline(cin, cccd);
                listkhachhang.readKhachHangFile("khachhanghientai.txt");
                listkhachhang.updateKhachHang(cccd);
                break;
            }
            case 4: {
                // Thống kê khách hàng đang đặt phòng
                cout << "\n========== THONG KE KHACH HANG DANG DAT PHONG ==========\n";
                ifstream currentFile("khachhanghientai.txt");
                if (!currentFile.is_open()) {
                    cout << "Khong co khach hang nao dang dat phong!\n";
                } else {
                    listkhachhang.readKhachHangFile("khachhanghientai.txt");
                    int currentCount = listkhachhang.countKhachHangInFile("khachhanghientai.txt");
                    cout << "So luong khach hang dang dat phong: " << currentCount << endl;
                    if (currentCount > 0) {
                        listkhachhang.displayKhachhang();
                    }
                    currentFile.close();
                }

                // Thống kê khách hàng đã đặt phòng theo tháng
                cout << "\n========== THONG KE KHACH HANG THEO THANG ==========\n";
                int month, year;
                cout << "Nhap thang (1-12): ";
                cin >> month;
                cout << "Nhap nam: ";
                cin >> year;
                cin.ignore();

                ifstream historyFile("lichsukhachhang.txt");
                ofstream outFile("thongkekhachhang.txt", ios::app);
                if (!historyFile.is_open()) {
                    cout << "Khong co lich su khach hang!\n";
                } else {
                    string line;
                    int count = 0;
                    while (getline(historyFile, line)) {
                        stringstream ss(line);
                        string roomID, checkInTime, name, cccd, phone, quequan;
                        getline(ss, roomID, ';');
                        getline(ss, checkInTime, ';');
                        getline(ss, name, ';');
                        getline(ss, cccd, ';');
                        getline(ss, phone, ';');
                        getline(ss, quequan, ';');

                        // Giả sử định dạng checkInTime là "dd/mm/yyyy hh:mm"
                        int day, fileMonth, fileYear;
                        sscanf(checkInTime.c_str(), "%d/%d/%d", &day, &fileMonth, &fileYear);

                        // Kiểm tra nếu tháng và năm trùng với tháng và năm nhập vào
                        if (fileYear == year && fileMonth == month) {
                            outFile << line << endl;
                            count++;
                        }
                    }

                    cout << "So luong khach hang da dat phong trong thang " << month << "/" << year << ": " << count << endl << endl;
                    outFile << endl <<"Tong so khach hang trong thang " << month << "/" << year << ": " << count << endl;
                    historyFile.close();
                    outFile.close();
                }
                break;
            }
            case 0:
                return;
            default:
                cout << "Lua chon khong hop le! Vui long chon lai.\n";
                break;
        }

        bool validInput = false;
        do {
            cout << "\nBan co muon tiep tuc khong? (y/n): ";
            cin >> tieptuc;
            cin.ignore();
            tieptuc = tolower(tieptuc);
            
            if (tieptuc == 'y' || tieptuc == 'n') {
                validInput = true;
            } else {
                cout << "Vui long chi nhap 'y' hoac 'n'!\n";
            }
        } while (!validInput);
        
        if (tieptuc == 'n') {
            return;
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