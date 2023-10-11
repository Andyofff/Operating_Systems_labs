#pragma once

#include<istream>
#include<string.h>


struct employee {
	int num;
	char name[10];
	double hours;

public:

	employee();

	employee(int num, char name[10], double hours);

	~employee();

};

employee::employee() {

	num = 0;
	strcpy_s(name, "000000000");
	hours = 0;

}

employee::employee(int num, char name[10], double hours) {
	this->num = num;
	strcpy_s(this->name, name);
	this->hours = hours;
};

employee::~employee() {

};
