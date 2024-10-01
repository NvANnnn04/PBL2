#include <iostream>
#include <string>
using namespace std; 

enum RoomStatus{
	ON,
	OFF 
}; 
class Room {
	private; 
		string RoomID;
		string RoomType;
		RoomStatus Status;
		int RoomFloor; 
		int RoomCapacity; 
		Room* Next;
	public;
		Room(string id, string type, RoomStatus status, int floor, int capacity); 
		string Get_RoomID() const;
		string Get_RoomType() const;
		RoomStatus Get_Status() const;
		int Get_RoomFloor() const;
		int Get_RoomCapacity() const;
		Room* Get_next()
}; 
