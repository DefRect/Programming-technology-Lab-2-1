#pragma once
#include "Student.h"

class University {
	Student *head_student;
	int number_of_student;

public:
	University();
	~University();

	int get_number_of_student() { return number_of_student; }

	void show_student();
	void show_student_two();
	void sort_student();
	Student* find_student(string, string);

	friend istream& operator >>(istream&, University&);
	friend ostream& operator <<(ostream&, University&);
};