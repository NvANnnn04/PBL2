#include "Room.h"

Room::Room(string id, string type, RoomStatus status, int floor, int capcacity)
	: RoomID(id), RoomType(type), Status(status), RoomFloor(floor), RoomCapacity(capacity), Next(NULL) {
}
Room::Get_RoomID() const {
	return RoomID;
} 
Room::Get_RoomType() const {
	return RoomType;
}
Room::Get_RoomStatus() const {
	return Status;
}
Room::Get_RoomFloor() const {
	return RoomFloor;
}
Room::Get_RoomCapacity() const {
	return RoomCapacity;
}
string Room::Get_StatusString(RoomStatus newStatus) {
	Status = newStatus;
	return (Status="ON") ? "Phong hoat dong" : "Phong trong"; 
} 
void Show_Room() const {
	cout << "Ma phong: " << Get_RoomID() << endl;
		 << "Loai phong: " << Get_RoomType() << endl;
		 << "Trang thai phong: " << Get_StatusString(Get_RoomStatus()) << endl; 
 		 << "Tang: " << Get_RoomFloor << endl;
		 << "So luong nguoi toi da" << Get_RoomCapacity() << endl;	
} 
