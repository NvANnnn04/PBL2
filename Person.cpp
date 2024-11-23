#include "Person.h"

Person::Person(string n, string id, string p) 
	:name(n), cccd(id), sdt(p) {		
}

Person::~Person() {
}

string Person::getName() const {
	return name;
}

string Person::getCccd() const {
	return cccd;
}

string Person::getSdt() const  {
	return sdt;
}

void Person::setName(string n) {
	name = n;
}

void Person::setCccd(string id) {
	cccd = id;
}

void Person::setSdt(string p) {
	sdt = p;
}
