#include "University.h"

University::University(){
	cout << "������ ����������� ������ University" << endl << endl;
	head_student = nullptr;
	number_of_student = 0;
}

University::~University(){
	cout << "������ ���������� ������ University" << endl << endl;
	Student *current;

	for(int i = 0; i < number_of_student; ++i){
		current = head_student;
		head_student = head_student->get_next_student();
		delete current;
	}
}

istream & operator>>(istream &in, University &obj){

	system("cls");
	Student *tmp = new Student;
	++obj.number_of_student;

	if (obj.head_student == nullptr) {
		obj.head_student = tmp;
	}
	else {
		tmp->set_next_student(obj.head_student);		//��������� ���������� ������ �������
		obj.head_student->set_previous_student(tmp);	//���������� ��� ������� �������� ���������� ��������� �������
		obj.head_student = tmp;							//����� ������ �������
	}

	cout << "������� ������� ��������!" << endl << endl;
	system("pause");

	return in;
}

ostream & operator<<(ostream &out, University &obj){
	system("cls");

	try {
		if (obj.get_number_of_student() == 0)
			throw exception("������ ��������� ����!");

		string surname;
		string initials;

		out << "������� �������: ";								//���� ������� ��������
		cin >> surname;
		out << "������� ��������: ";							//���� ��������� ��������
		cin >> initials;

		Student *current = obj.head_student;
		for (int i = 0; i < obj.number_of_student; ++i) {
			if (current->get_surname() == surname && current->get_initials() == initials) {
				if (current == obj.head_student) {									//���� ��������� ������� ������
					obj.head_student = obj.head_student->get_next_student();		//����������� ��������� �� ������ ������ �� ������ �������
					delete current;													//������� ������ �������
					--obj.number_of_student;										//��������� ���������� ���������
				}
				else {																//���� �� ������
					current->get_previous_student()->set_next_student(current->get_next_student());			//���������� ������� �������� �� ������� ����� ��������
					if (current->get_next_student() != nullptr)												//���� ���� ��������� �������	
						current->get_next_student()->set_previous_student(current->get_previous_student());	//���������� ��� ���������� �������� ���������� ���������� ������� ��� ���������� ��������
					delete current;																			//������� ������ �������
					--obj.number_of_student;																//��������� ���������� ���������
				}
				out << "������� ������� ������!" << endl << endl;
				break;
			}

			if (i == obj.number_of_student - 1)						//���� �� ����� �� ���������� ��������, �� ��� � �� ����� ������� ��������
				out << "������ �������� ���!" << endl << endl;

			current = current->get_next_student();
		}
		system("pause");
	}
	catch (exception &ex) {
		system("cls");
		cout << ex.what() << endl << endl;
		system("pause");
	}

	return out;
}

void University::show_student(){
	system("cls");
	Student *current = head_student;

	cout << "������ ���������" << endl << endl;

	try {
		if (number_of_student == 0)
			throw exception("������ ��������� ����!");

		for (int i = 0; i < number_of_student; ++i) {
			current->show_data();
			cout << "------------------------------------------------------" << endl;
			current = current->get_next_student();
		}

	}
	catch (exception &ex) {
		cout << ex.what() << endl << endl;
	}

	system("pause");
}

void University::show_student_two(){
	system("cls");
	Student *current = head_student;
	bool flag = false;

	cout << "������ ���������, � ������� ���� ���� �� ���� ������ 2" << endl << endl;

	try{
		if (number_of_student == 0)
			throw exception("������ ��������� ����!");

		for (int i = 0; i < number_of_student; ++i) {
			if (current->find_mark_two()) {
				flag = true;
				current->show_data();
				cout << "------------------------------------------------------" << endl << endl;
			}
			current = current->get_next_student();
		}

		if (!flag)
			cout << "��������� � ������� 2 ���!" << endl << endl;
	}
	catch (exception &ex) {
		cout << ex.what() << endl << endl;
	}

	system("pause");
}

void University::sort_student(){

	for (int i = 0; i < number_of_student - 1; ++i) {
		Student *current = head_student;

		while (current->get_next_student() != nullptr) {
			if (current->get_average_mark() > current->get_next_student()->get_average_mark()) {

				//��������� �� ��������, ������� ���������� �������� �������
				Student *first = current;									//��������� �� ������� ������� (������)
				Student *second = current->get_next_student();				//��������� �� ��������� ������� (������)

				Student *first_left = first->get_previous_student();		//��������� �� ������� �� ������
				Student *second_right = second->get_next_student();			//��������� �� ������� ����� ������

				if (second_right != nullptr)								//���� ����� ������� ���� �������
					second_right->set_previous_student(first);				//��� ���������� ��������� ���������� ������ �������
				
				if (first == head_student) {								//���� ������ ������� ����� ������ ������
					head_student = second;									//������ ������ ������
					second->set_previous_student(nullptr);					//� ������ ��� ����������� ��������
				}
				else {														//���� �� ������
					first_left->set_next_student(second);					//������� ����� ������ �������� ��������� �� ������ �������
				}

				first->set_next_student(second_right);						//� ������� �������� ��������� - ������� ����� �������
				first->set_previous_student(second);						//� ������� ���������� ������ ������

				second->set_next_student(first);							//� ������� ��������� ������ ������
				second->set_previous_student(first_left);					//� ������� ���������� ������� - ������� ����� ������

				current = second;											//�� ������ �������, �� ������� �� ����
			}
			current = current->get_next_student();							//��������� �� ��������� �������
		}
	}

}

Student* University::find_student(string surname, string initials){
	Student *current = head_student;

	for (int i = 0; i < number_of_student; ++i) {
		if (current->get_surname() == surname && current->get_initials() == initials)
			return current;

		current = current->get_next_student();
	}

	return nullptr;
}