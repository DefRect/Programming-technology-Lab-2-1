#include "University.h"

int main() {
	setlocale(LC_ALL, "");

	University obj;
	Student *ptr;
	string surname;
	string initials;
	int button;
	bool flag = true;

	while (flag) {
		system("cls");
		cout << "1 - Добавить студента" << endl;
		cout << "2 - Удалить студента" << endl;
		cout << "3 - Вывод студентов на экран" << endl;
		cout << "4 - Вывод студентов, которые имеют хотя бы одну оценку 2" << endl;
		cout << "5 - Сортировка студентов по возрастанию среднего балла" << endl;
		cout << "6 - Найти студента" << endl;
		cout << "0 - Выход" << endl;
		cin >> button;

		if (cin.fail()) {
			button = -1;
			cin.clear();
			cin.ignore(10000, '\n');
		}

		switch (button) {
		case 1:
			cin >> obj;
			break;
		case 2:
			cout << obj;
			break;
		case 3:
			obj.show_student();
			break;
		case 4:
			obj.show_student_two();
			break;
		case 5:
			obj.sort_student();
			break;
		case 6:
			if (obj.get_number_of_student() == 0) {
				system("cls");
				cout << "Список студентов пуст!" << endl << endl;
				system("pause");
			}
			else {
				cout << "Введите фамилию: ";
				cin >> surname;
				cout << "Введите инициалы: ";
				cin >> initials;
				ptr = obj.find_student(surname, initials);
				if (ptr == nullptr) {
					cout << "Такого студента нет!" << endl << endl;
					system("pause");
				}
				else {
					ptr->change_data();
				}
			}
			break;
		case 0:
			flag = false;
			break;
		default:
			cout << "Введена некорректная команда" << endl << endl;
			system("pause");
		}
	}

	return 0;
}