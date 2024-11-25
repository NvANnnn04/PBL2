#ifndef LETAN_H
#define LETAN_H
#include <string>
#include "Person.h"

using namespace std;

class Letan : public Person {
private:
	string emailLT;
	string birthdayLT;
	string workdayLT;
public:
	Letan(string n, string id, string p, string e, string bd, string wd);
	string getEmailLT() const;
	string getBirthdayLT() const;
	string getWorkdayLT() const;
	void setEmailLT(string mail);
	void setBirthdayLT(string birthday);
	void setWorkdayLT(string workday);
	void displayInfoLT() const; 
};

struct NodeLT {
public:
    Letan data;
    NodeLT* next;
    NodeLT(const Letan& lt) : data(lt), next(nullptr) {}
};
class LinkedListLetan {
private:
	NodeLT* head;
public:
	LinkedListLetan();
	~LinkedListLetan();
	NodeLT* getHead() const;
	void addLetan(const Letan& lt);
	void readLetanFile(const string& filename);
	void displayLetan() const;
	void updateLetan(const string& id);
	NodeLT* findLetan(const string& id);
	void deteleLetan(const string& id);
	bool userLogin(const LinkedListLetan& listletan);
	void findLetanByName(const string& name);
	void findLetanByWorkday(const string& workday);
	bool updateWorkday(const string& id, const string& newWorkday);
};
#endif
