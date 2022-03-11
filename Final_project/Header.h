#pragma once
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>

using namespace std;

class Book {
public:
	int Number = 0;
	int Grade = 0;
	string Authors;
	int Year = 0;
	int i_Rozdil = 0;
	int i_paragraph = 0;
	string Rozdil;
	string paragraph;
};
class Author_check {
public:
	vector<int> Grade;
	vector<string> Authors_c;
	vector<int> Year;
};

vector<string> split(const string&, const char);
int check_number();
bool word_find(const string&, const string&);
bool check_bool();

void choose();
void input_info();
void show_info();
void delete_info(vector<int>&);
void update_info(vector<int>&);
void save_info();
void load_info();