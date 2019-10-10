#include "University.h"

University::University(){
	cout << "Вызван конструктор класса University" << endl << endl;
	head_student = nullptr;
	number_of_student = 0;
}

University::~University(){
	cout << "Вызван деструктор класса University" << endl << endl;
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
		tmp->set_next_student(obj.head_student);		//Следующим становится первый элемент
		obj.head_student->set_previous_student(tmp);	//Предыдщуий для первого элемента становится созданный элемент
		obj.head_student = tmp;							//Новый первый элемент
	}

	cout << "Студент успешно добавлен!" << endl << endl;
	system("pause");

	return in;
}

ostream & operator<<(ostream &out, University &obj){
	system("cls");

	try {
		if (obj.get_number_of_student() == 0)
			throw exception("Список студентов пуст!");

		string surname;
		string initials;

		out << "Введите фамилию: ";								//Ввод фамилии студента
		cin >> surname;
		out << "Введите инициалы: ";							//Ввод инициалов студента
		cin >> initials;

		Student *current = obj.head_student;
		for (int i = 0; i < obj.number_of_student; ++i) {
			if (current->get_surname() == surname && current->get_initials() == initials) {
				if (current == obj.head_student) {									//Если удаляемый элемент первый
					obj.head_student = obj.head_student->get_next_student();		//Передвигаем указатель на начало списка на второй элемент
					delete current;													//Удаляем первый элемент
					--obj.number_of_student;										//Уменьшаем количество элементов
				}
				else {																//Если не первый
					current->get_previous_student()->set_next_student(current->get_next_student());			//Предыдущий элемент указвает на элемент после текущего
					if (current->get_next_student() != nullptr)												//Если есть следующий элемент	
						current->get_next_student()->set_previous_student(current->get_previous_student());	//Предыдущим для следующего элемента становится предыдущий элемент для удаляемого элемента
					delete current;																			//Удаляем первый элемент
					--obj.number_of_student;																//Уменьшаем количество элементов
				}
				out << "Студент успешно удален!" << endl << endl;
				break;
			}

			if (i == obj.number_of_student - 1)						//Если мы дошли до последнего элемента, но так и не нашли нужного студента
				out << "Такого студента нет!" << endl << endl;

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

	cout << "Список студентов" << endl << endl;

	try {
		if (number_of_student == 0)
			throw exception("Список студентов пуст!");

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

	cout << "Список студентов, у которых есть хотя бы одна оценка 2" << endl << endl;

	try{
		if (number_of_student == 0)
			throw exception("Список студентов пуст!");

		for (int i = 0; i < number_of_student; ++i) {
			if (current->find_mark_two()) {
				flag = true;
				current->show_data();
				cout << "------------------------------------------------------" << endl << endl;
			}
			current = current->get_next_student();
		}

		if (!flag)
			cout << "Студентов с оценкой 2 нет!" << endl << endl;
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

				//Указатели на элементы, которые необходимо поменять местами
				Student *first = current;									//Указатель на текущий элемент (первый)
				Student *second = current->get_next_student();				//Указатель на следующий элемент (второй)

				Student *first_left = first->get_previous_student();		//Указатель на элемент за вторым
				Student *second_right = second->get_next_student();			//Указатель на элемент перед первым

				if (second_right != nullptr)								//Если после второго есть элемент
					second_right->set_previous_student(first);				//Его предыдущим элементом становится первый элемент
				
				if (first == head_student) {								//Если первый элемент равен началу списка
					head_student = second;									//Меняем начало списка
					second->set_previous_student(nullptr);					//У головы нет предыдущего элемента
				}
				else {														//Если не первый
					first_left->set_next_student(second);					//Элемент перед первым начинает указывать на второй элемент
				}

				first->set_next_student(second_right);						//У первого элемента следующий - элемент после второго
				first->set_previous_student(second);						//У первого предыдущий теперь второй

				second->set_next_student(first);							//У второго следующий теперь первый
				second->set_previous_student(first_left);					//У второго предыдущий элемент - элемент перед первым

				current = second;											//Не меняем позицию, на которой мы были
			}
			current = current->get_next_student();							//Переходим на следующий элемент
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