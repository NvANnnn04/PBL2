#ifndef PERSON_H
#define PERSON_H
#include <string>
using namespace std;

class Person {
private:
	string name;
	string cccd;
	string sdt;
public:
	Person(string n, string id, string p);
	virtual	~Person();
	string getName() const;
	string getCccd() const;
	string getSdt() const;
	void setName(string n);
	void setCccd(string id);
	void setSdt(string p);
	
};

#endif

