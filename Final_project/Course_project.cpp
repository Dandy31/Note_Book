#include "Header.h"

int check_number() {
	bool digit = false;
	string input;
	int b = 0;
	while (!digit) {
		cin >> input;
		for (int i = 0; i < input.length(); i++) {
			if (isdigit(input[i]) == 0 || stoi(input) <= 0)
			{
				cout << "Ви НЕ ввели натуральне число, спробуйте ще раз" << endl;
				digit = false;
				break;
			}
			else {
				digit = true;
			}
		}
	}
	b = stoi(input);
	return b;
}
bool check_bool() {
	bool checked = false;
	string input;
	int b = 0;
	while (!checked) {
		cin >> input;
		if (input.size() != 1)
		{
			cout << "Ви ввели НЕ 1 та НЕ 0, спробуйте ще раз" << endl;
			checked = false;
		}
		else if (stoi(input) == 1 || stoi(input) == 0) {
			b = stoi(input);
			return b;
		}
		else {
			cout << "Ви ввели НЕ 1 та НЕ 0, спробуйте ще раз" << endl;
			checked = false;
		}
	}
};
vector<string> split(string source, char it) {
	vector<string> array;
	istringstream is(source);
	string s;
	while (getline(is, s, it)) {
		array.push_back(s);
	}
	return array;
};
bool word_find(string word, string word_plus_chars) {
	string temp = "";
	if (word == word_plus_chars) {
		return true;
	}
	for (int i = 0; word.length() >= i && word_plus_chars.length() > i; i++) {
		if (word_plus_chars[i] != '.' ||
			word_plus_chars[i] != ',' ||
			word_plus_chars[i] != '(' ||
			word_plus_chars[i] != ')') 
		{
			temp.push_back(word_plus_chars[i]);
		}
		if (word == temp) {
			return true;
		}
	}
	return false;
};
void save_info() {
	ifstream save_from("Physics.txt");
	ofstream save_to("Physics_backup.txt", ios::trunc);
	string output;

	while (getline(save_from, output)) {
		if (output.empty()) {
			continue;
		}
		save_to << output << endl;
	}
	save_from.close();
	save_to.close();
	cout << "\t-------------------Збереження виконано успішно-------------------" << endl;
};
void load_info() {
	ifstream load_from("Physics_backup.txt");
	if (!load_from.is_open()) {
		cout << "\t-------------------Збережень не знайдено-------------------" << endl;
	}
	ofstream load_to("Physics.txt", ios::trunc);
	string output;

	while (getline(load_from, output)) {
		if (output.empty()) {
			continue;
		}
		load_to << output << endl;
	}
	load_from.close();
	load_to.close();
	cout << "\t-------------------Завантаження виконано успішно-------------------" << endl;
}
void input_info() {
	Book new_book;
	Author_check check;
	string temp;
	new_book.i_paragraph = 1;
	new_book.i_Rozdil = 1;
	bool flag = true, pointed = false;

	fstream file("Physics.txt", ios::in);
	string temp_s;
	file.seekg(0, ios::beg);
	while (getline(file, temp_s)) {
		if (temp_s == "") {
			continue;
		}
		vector<string> words = split(temp_s, ' ');
		if (words[0] == "#") {
			new_book.Number = stoi(words[1]) + 1;
		}
		else if (words[1] == "клас") {
			check.Grade.push_back(stoi(words[0]));
		}
		else if (words[0] == "Книга") {
			check.Authors_c.push_back(temp_s);
		}
		else if (words[0] == "Рік") {
			check.Year.push_back(stoi(words[2]));
		}
		words.clear();
	}
	file.close();

	file.open("Physics.txt", ios::app | ios::out | ios::binary);
	
	cout << "Клас: ";
	new_book.Grade = check_number();
	if (new_book.Grade > 12 || new_book.Year < 0) {
		cout << "\tКлас не є корректним!" << endl;
		return;
	}

	cout << "Рік видавництва: ";
	new_book.Year = check_number();
	if (new_book.Year > 2021 || new_book.Year < 1000) {
		cout << "Рік видавництва книги не є корректним!" << endl;
		return;
	}
	
	cout << "Введіть авторів/автора книги: " << endl;
	getline(cin >> ws, new_book.Authors);
	temp = "Книга за авторством: " + new_book.Authors;
	for (int i = 0; i < check.Authors_c.size(); i++) {
		if (temp == check.Authors_c[i] && new_book.Grade == check.Grade[i] && new_book.Year == check.Year[i]) {
			cout << "\tВведена книга вже існує!" << endl;
			return;
		}
	}

	file << endl << "# " << new_book.Number;
	file << endl << new_book.Grade << " клас";
	file << endl << "Книга за авторством: " << new_book.Authors;
	file << endl << "Рік видавництва: " << new_book.Year;
	do {
		if (new_book.i_Rozdil > 1) {
			cout << "\t| Продовжити введення нових розділів(та параграфів) для даної книги? (Так - 1; Ні - 0) |" << endl;
			flag = check_bool();
			if (!flag) {
				break;
			}
		}
		cout << "Назва розділу № " << new_book.i_Rozdil << ":" << endl;
		getline(cin >> ws, new_book.Rozdil);
		file << endl << "Розділ " << new_book.i_Rozdil << " " << new_book.Rozdil;
		new_book.i_Rozdil++;
		while (flag) {
			if (new_book.i_paragraph > 1 && !pointed) {
				cout << "\t| Щоб зупинити введення нових параграфів введіть - '0' замість назви |" << endl;
				pointed = true;
			}
			cout << "Назва параграфу № " << new_book.i_paragraph << ":" << endl;
			getline(cin >> ws, new_book.paragraph);
			if (new_book.paragraph == "0") {
				break;
			}
			file << endl << "§ " << new_book.i_paragraph << " " << new_book.paragraph;
			new_book.i_paragraph++;
		}
		pointed = false;
	} while (flag);
	cout << "-------------------Книга створена-------------------" << endl;
	file.close();
};
void search_info() {
	Book Info;
	fstream file("Physics.txt", ios::in);
	string output, input, temp_s;
	bool word_found = false, flag = false;
	int criterion, count = 0;
	cout << endl << "Оберіть предмет пошуку:" << endl;
	cout << "\t| 1 - Книга за автором " << endl;
	cout << "\t| 2 - Книги за класом  " << endl;
	cout << "\t| 3 - Розділ книги та його параграфи  " << endl;
	cout << "\t| 4 - Параграф його розділ та клас " << endl;
	cout << "\t| Інші натуральні числа - Назад" << endl;
	criterion = check_number();
	switch (criterion) {
	case 1:
		cout << "Введіть фамілію або ім'я одного з авторів книги: " << endl;
		getline(cin >> ws, input);
		cout << "-------------------Виведення-------------------" << endl;
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			vector<string> words = split(output, ' ');
			
			if (words[0] == "Книга") {
				for (int i = 0; i < words.size(); i++) {
					if (words[i] == input || words[i] == (input + ",")) {
						cout << endl << "\t--------------------------------------" << endl;
						cout << "# "<< Info.Number << endl;
						cout << "клас " << Info.Grade << endl;
						cout << output << endl;
						word_found = true;
						break;
					}
					else {
						word_found = false;
					}
				}
			} 
			else if (words[0] == "#") {
				Info.Number = stoi(words[1]);
			}
			else if (words[1] == "клас") {
				Info.Grade = stoi(words[0]);
			} 
			else if (word_found) {
				cout << output << endl;
			}
			words.clear();
		}
		break;
	case 2:
		cout << "Введіть клас: " << endl;
		cin >> input;
		cout << "-------------------Виведення-------------------" << endl;
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			vector<string> words = split(output, ' ');
			if (words[0] == "#") {
				Info.Number = stoi(words[1]);
			} 
			else if (words[1] == "клас") {
				if (input == words[0]) {
					cout << endl << "\t--------------------------------------" << endl;
					cout << "# " << Info.Number << endl;
					cout << output << endl;
					word_found = true;
					flag = true;
				}
				else {
					word_found = false;
				}
			}
			else if (word_found) {
				if (words[0] == "Розділ") {
					cout << "\t" << output << endl;

				}
				else if (words[0] == "§") {
					cout << "\t\t" << output << endl;
				}
				else {
					cout << output << endl;
				}
				flag = true;
			}
			words.clear();
		}
		if (!flag) {
			cout << "Книги світньої програми " << input << "-го класу немає в базі" << endl;
		}
		break;
	case 3:
		cout << "Введіть слово з назви розділу: " << endl;
		cin >> input;
		cout << "-------------------Виведення-------------------" << endl;
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			vector<string> words = split(output, ' ');
			if (words[0] == "Розділ") {
				for (int i = 0; i < words.size(); i++) {
					if (words[i] == input || word_find(input, words[i]))
					{
						Info.Rozdil = output;
						word_found = true;
						break;
					}
					else {
						word_found = false;
					}
				}
			}
			if (words[0] == "#") {
				Info.Number = stoi(words[1]);
				count = 0;
			}
			else if (words[1] == "клас") {
				Info.Grade = stoi(words[0]);
				count++;
			}
			else if (words[0] == "Книга") {
				Info.Authors = output;
				count++;
			}
			else if (words[0] == "Рік") {
				Info.Year = stoi(words[2]);
				count++;
			} 
			else if (word_found) {
				if (count == 3) {
					cout << endl << "\t--------------------------------------" << endl;
					cout << "# " << Info.Number << endl;
					cout << "клас " << Info.Grade << endl;
					cout << Info.Authors << endl;
					cout << "Рік видавництва: " << Info.Year << endl;
					count++;
				}
				if (words[0] == "§") {
				cout << "\t\t" << output << endl;
				} else {
					cout << "\t" << Info.Rozdil << endl;
				}
			}
			words.clear();
		}
		break;
	case 4:
		cout << "Введіть слово з назви параграфа: " << endl;
		cin >> input;
		cout << "-------------------Виведення-------------------" << endl;
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			vector<string> words = split(output, ' ');
			if (words[0] == "§") {
				for (int i = 0; i < words.size(); i++) {
					if (word_find(input, words[i])) {
						Info.paragraph = output;
						word_found = true;
						break;
					}
					else {
						word_found = false;
					}
				}
			}
			if (words[0] == "#") {
				Info.Number = stoi(words[1]);
				count = 0;
			}
			else if (words[1] == "клас") {
				Info.Grade = stoi(words[0]);
				count++;
			}
			else if (words[0] == "Книга") {
				Info.Authors = output;
				count++;
			}
			else if (words[0] == "Рік") {
				Info.Year = stoi(words[2]);
				count++;
			}
			else if (words[0] == "Розділ") {
				Info.Rozdil = output;
				flag = true;
			}
			else if (word_found) {
				if (count == 3) {
					cout << endl << "\t--------------------------------------" << endl;
					cout << "# " << Info.Number << endl;
					cout << "клас " << Info.Grade << endl;
					cout << Info.Authors << endl;
					cout << "Рік видавництва: " << Info.Year << endl;
					count++;
				} 
				if(flag){
					cout << "\t" << Info.Rozdil << endl;
					cout << "\t\t" << Info.paragraph << endl;
					flag = false;
				}
				else {
					cout << "\t\t" << Info.paragraph << endl;
				}
			}
			words.clear();
		}
		break;
	default:
		break;
	}
	cout << "-----------------------------------------------------------------------------------" << endl;
	file.close();
};
void delete_info(vector<int> books) {
	Book Delete;
	ifstream file("Physics.txt");
	ofstream fileTemp("Temp.txt", ios::trunc);
	int criterion, count = 0, input;
	bool save = false, book_found = false, input_found = false;
	vector<string> words;
	string output;

	cout << "\t| Зберегти файл? (Так - 1; Ні - 0)" << endl;
	save = check_bool();
	if (save) {
		save_info();
	}

	cout << "Введіть номер книги для подальших дій:" << endl;
	Delete.Number = check_number();
	while (Delete.Number > books.size() || Delete.Number < 1) {
		cout << "Книги під номером " << Delete.Number << " немає в базі" << endl;
		cout << "\t--------------------------------------" << endl;
		cout << "Введіть номер книги для подальших дій:" << endl;
		Delete.Number = check_number();
	}

	cout << endl << "Оберіть критерій:" << endl;
	cout << "\t| 1 - Видалити Книгу " << endl;
	cout << "\t| 2 - Видалити Розділ та його параграфи " << endl;
	cout << "\t| 3 - Видалити Параграф " << endl;
	cout << "\t| Інші натуральні числа - Назад" << endl;
	criterion = check_number();
	switch (criterion) {
	case 1:
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			if (output[0] == '#') {
				words = split(output, ' ');
				if (words[1] == to_string(Delete.Number)) {
					if (Delete.Number != books.size()) {
						file.seekg(books[Delete.Number] + 5, ios::beg);
					}
					else {
						file.seekg(0, ios::end);
						break;
					}
				}
				Delete.Number++;
				fileTemp << "# " << Delete.Number << endl;
				continue;
			}
			else {
				fileTemp << output << endl;
			}
		}
		file.close();
		fileTemp.close();
		remove("Physics.txt");
		rename("Temp.txt", "Physics.txt");
		cout << "\t-----------------Книгу # " << Delete.Number << " Видалено---------------------" << endl;
		break;
	case 2:
		cout << "Введіть номер Розділу:" << endl;
		input = check_number();
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			words = split(output, ' ');
			if (words[0] == "#") {
				if (words[1] == to_string(Delete.Number)) {
					book_found = true;
				}
				else {
					book_found = false;
				}
			}
			if (book_found) {
				if (words[0] == "Розділ" && words[1] == to_string(input)) {
					input_found = true;
				}
				else if (words[0] == "Розділ"){
					Delete.i_Rozdil++;
					fileTemp << "Розділ " << Delete.i_Rozdil << " ";
					for (int i = 2; i < words.size(); i++) {
						if (i + 1 == words.size()) {
							fileTemp << words[i] << endl;
						}
						else {
							fileTemp << words[i] << " ";
						}
					}
					input_found = false;
					continue;
				} 
				else if (words[0] == "§" && !input_found) {
					Delete.i_paragraph++;
					fileTemp << "§ " << Delete.i_paragraph << " ";
					for (int i = 2; i < words.size(); i++) {
						if (i + 1 == words.size()) {
							fileTemp << words[i] << endl;
						} else {
							fileTemp << words[i] << " ";
						}
					}
					continue;
				}
			}
			if (!input_found){
				fileTemp << output << endl;
			}
			words.clear();
		}
		file.close();
		fileTemp.close();
		remove("Physics.txt");
		rename("Temp.txt", "Physics.txt");
		cout << "\t-----------------Розділ # "<< input << " Видалено---------------------" << endl;
		break;
	case 3:
		cout << "Введіть номер Параграфа:" << endl;
		input = check_number();
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			words = split(output, ' ');
			if (words[0] == "#") {
				if (words[1] == to_string(Delete.Number)) {
					book_found = true;
				}
				else {
					book_found = false;
				}
			}
			if (book_found) {
				if (words[0] == "§" && words[1] == to_string(input)) {
					input_found = true;
				}
				else if (words[0] == "§") {
					Delete.i_paragraph++;
					fileTemp << "§ " << Delete.i_paragraph << " ";
					for (int i = 2; i < words.size(); i++) {
						if (i + 1 == words.size()) {
							fileTemp << words[i] << endl;
						}
						else {
							fileTemp << words[i] << " ";
						}
					}
					input_found = false;
					continue;
				}
				else {
					fileTemp << output << endl;
				}
			}
			else if (!input_found) {
				fileTemp << output << endl;
			}
			words.clear();
		}
		file.close();
		fileTemp.close();
		remove("Physics.txt");
		rename("Temp.txt", "Physics.txt");
		cout << "\t-----------------Параграф # " << input << " Видалено---------------------" << endl;
		break;
	default:
		break;
	}
};
void update_info(vector<int> books) {
	Book Fixed;
	Fixed.i_Rozdil = 1, Fixed.i_paragraph = 1;
	ifstream file("Physics.txt");
	ofstream fileTemp("Temp.txt", ios::trunc);
	int criterion, count = 0, input, save;
	bool book_found = false, input_found = false, clas_num = false;
	vector<string> words;
	string output;

	cout << "\t| Зберегти файл? (Так - 1; Ні - 0)" << endl;
	save = check_bool();
	if (save) {
		save_info();
	}

	cout << "Введіть номер книги для подальших дій:" << endl;
	Fixed.Number = check_number();
	while (Fixed.Number > books.size() || Fixed.Number < 1) {
		cout << "Книги під номером " << Fixed.Number << " немає в базі" << endl;
		cout << "\t--------------------------------------" << endl;
		cout << "Введіть номер книги для подальших дій:" << endl;
		Fixed.Number = check_number();
	}

	cout << endl << "Оберіть критерій:" << endl;
	cout << "\t| 1 - Відредагувати номер класу " << endl;
	cout << "\t| 2 - Відредагувати рядок авторів " << endl;
	cout << "\t| 3 - Відредагувати рік видавництва " << endl;
	cout << "\t| 4 - Відредагувати Розділ " << endl;
	cout << "\t| 5 - Відредагувати Параграф " << endl;
	cout << "\t| Інші натуральні числа - Назад" << endl;
	criterion = check_number();
	switch (criterion) {
	case 1:
		cout << "Введіть новий номер класу:" << endl;
		Fixed.Grade = check_number();
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			words = split(output, ' ');
			if (output[0] == '#' && words[1] == to_string(Fixed.Number)) {
				book_found = true;
			}
			if (book_found) {
				if (words[1] == "клас") {
					fileTemp << Fixed.Grade << " клас" << endl;
					book_found = false;
				}
				else {
					fileTemp << output << endl;
				}
			}
			else {
				fileTemp << output << endl;
			}
			words.clear();
		}
		file.close();
		fileTemp.close();
		remove("Physics.txt");
		rename("Temp.txt", "Physics.txt");
		cout << "\t-----------------Номер класу відредаговано на: " << Fixed.Grade << " ---------------------" << endl;
		break;
	case 2:
		cout << "Введіть новий рядок авторів:" << endl;
		getline(cin >> ws, Fixed.Authors);
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			words = split(output, ' ');
			if (output[0] == '#' && words[1] == to_string(Fixed.Number)) {
				book_found = true;
			}
			if (book_found) {
				if (words[0] == "Книга") {
					fileTemp << "Книга за авторством: " << Fixed.Authors << endl;
					book_found = false;
				}
				else {
					fileTemp << output << endl;
				}
			}
			else {
				fileTemp << output << endl;
			}
			words.clear();
		}
		file.close();
		fileTemp.close();
		remove("Physics.txt");
		rename("Temp.txt", "Physics.txt");
		cout << "\t-----------------Ряд авторів відредаговано ---------------------" << endl;
		break;
	case 3:
		cout << "Введіть новий рік видавництва:" << endl;
		Fixed.Year = check_number();
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			words = split(output, ' ');
			if (output[0] == '#' && words[1] == to_string(Fixed.Number)) {
				book_found = true;
			}
			if (book_found) {
				if (words[0] == "Рік") {
					fileTemp << "Рік видавництва: " << Fixed.Year << endl;
					book_found = false;
				}
				else {
					fileTemp << output << endl;
				}
			}
			else {
				fileTemp << output << endl;
			}
			words.clear();
		}
		file.close();
		fileTemp.close();
		remove("Physics.txt");
		rename("Temp.txt", "Physics.txt");
		cout << "\t-----------------Рік видавництва відредаговано на: "<< Fixed.Year << " ---------------------" << endl;
		break;
	case 4:
		cout << "Введіть номер розділу:" << endl;
		input = check_number();
		cout << "Введіть нову назву розділу:" << endl;
		getline(cin >> ws, Fixed.Rozdil);
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			words = split(output, ' ');
			if (words[0] == "#") {
				if (words[1] == to_string(Fixed.Number)) {
					book_found = true;
				}
				else {
					book_found = false;
				}
			}
			if (book_found) {
				if (words[0] == "Розділ" && words[1] == to_string(input)) {
					fileTemp << "Розділ " << Fixed.i_Rozdil << " " << Fixed.Rozdil << endl;
					input_found = true;
				}
				else if (words[0] == "Розділ") {
					Fixed.i_Rozdil++;
					input_found = false;
				}
				else {
					fileTemp << output << endl;
					continue;
				}
			}
			if (!input_found) {
				fileTemp << output << endl;
			}
			words.clear();
		}
		file.close();
		fileTemp.close();
		remove("Physics.txt");
		rename("Temp.txt", "Physics.txt");
		break;
	case 5:
		cout << "Введіть номер параграфу:" << endl;
		input = check_number();
		cout << "Введіть нову назву параграфу:" << endl;
		getline(cin >> ws, Fixed.paragraph);
		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			words = split(output, ' ');
			if (words[0] == "#") {
				if (words[1] == to_string(Fixed.Number)) {
					book_found = true;
				}
				else {
					book_found = false;
				}
			}
			if (book_found) {
				if (words[0] == "§" && words[1] == to_string(input)) {
					fileTemp << "§ " << Fixed.i_paragraph << " " << Fixed.paragraph << endl;
					input_found = true;
				}
				else if (words[0] == "§") {
					Fixed.i_paragraph++;
					input_found = false;
				}
				else {
					fileTemp << output << endl;
					continue;
				}
			}
			if (!input_found) {
				fileTemp << output << endl;
			}
			words.clear();
		}
		file.close();
		fileTemp.close();
		remove("Physics.txt");
		rename("Temp.txt", "Physics.txt");
		break;
	default:
		break;
	}
};
void show_info() {
	int option, book_num, count = 0, temp;
	string output;
	vector<int> books;
	vector<string> words;

	ifstream file("Physics.txt", ios::binary);
	cout << "-------------------Виведення Книг-------------------" << endl;
	while (getline(file, output)) {
		if (output.empty()) {
			continue;
		}
		words = split(output, ' ');
		if (words[0] == "#") {
			temp = file.tellg();
			books.push_back(temp - 5);
		}
		if (words[0] != "§" && words[0] != "Розділ" && output != "") {
			cout << output << endl;
		}
		words.clear();
	}
	file.close();
	cout << "--------------------------------------" << endl;

	cout << "\t| 1 - Видалення даних" << endl;
	cout << "\t| 2 - Редагування даних" << endl;
	cout << "\t| 3 - Відкрити книгу" << endl;
	cout << "\t| Інші натуральні числа - Назад" << endl;
	option = check_number();

	switch (option) {
	case 1:
		delete_info(books);
		break;
	case 2:
		update_info(books);
		break;
	case 3:
		cout << "Введіть номер книги: " << endl;
		book_num = check_number();
		if (book_num > books.size() || book_num < 1) {
			cout << "Книги під номером " << book_num << " немає в базі" << endl;
			cout << "\t--------------------------------------" << endl;
			break;
		}
		file.open("Physics.txt", ios::binary);
		file.seekg(books[book_num - 1], ios::beg);
		cout << "-------------------Виведення Книги-------------------" << endl;

		while (getline(file, output)) {
			if (output.empty()) {
				continue;
			}
			if (output[0] == '#') {
				count++;
			}
			if (count == 2) {
				break;
			}
			cout << output << endl;
		}
		cout << "\t--------------------------------------" << endl;
		books.clear();
		break;
	default:
		break;
	}
};
void choose() {
	int operation = 0;
	cout << "Виберіть номер операції роботи з даними:" << endl;
	cout << "\t| 1 - Введення нової книги " << endl;
	cout << "\t| 2 - Пошук " << endl;
	cout << "\t| 3 - Виведення " << endl;
	cout << "\t| 4 - Зберегти файл " << endl;
	cout << "\t| 5 - Завантажити останній збережений файл" << endl;
	cout << "\t| 6 - Вихід " << endl;
 	operation = check_number();
	switch (operation) {
	case 1:
		input_info();
		choose();
		break;
	case 2:
		search_info();
		choose();
		break;
	case 3:
		show_info();
		choose();
		break;
	case 4:
		save_info();
		choose();
		break;
	case 5:
		load_info();
		choose();
		break;
	case 6:
		break;
	default:
		cout << "Операції під номером " << operation << " не знайдено" << endl;
		cout << endl;
		choose();
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ofstream file("Physics.txt", ios::app);
	ofstream file_backup("Physics_backup.txt", ios::app);
	if (file.is_open() && file_backup.is_open()) {
		file.close();
		file_backup.close();
	}
	else {
		cout << "Програма не може створити необхідні файли для роботи з даними" << endl;
		return 0;
	}

	cout << "Вітаю в інформаційно-пошуковій програмі знань по Фізиці шкільної програми." << endl;
	choose();
	system("pause");
	return 0;
}