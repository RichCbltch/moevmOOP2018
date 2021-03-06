#include <iostream>
#include "battlefield.h"
#include <string>
#include <sstream>

using namespace std;

int main() {

	//Object blue({ 1,1 }, 1);

	battlefield *game = new battlefield();
	cout << "Printing field..." << endl;
	game->print();
	cout << "Field printed!" << endl;
	int x, y;
	int id = 0;
	string answ_string;
	string da_way;
	//int damage;
	int result = 0;
	int option;
	vector <Object *> temp;
	while (true) {
		cout << "input coordinates of target (separeted by space) [press q to exit]" << endl << "Enter coords: ";

		cin >> answ_string;

		if (answ_string.front() == 'q') break;

		x = atoi(answ_string.c_str());
		cin >> answ_string;
		y = atoi(answ_string.c_str());
		//repair temp from select by coords - just attack
		game->select_by_coords({ x,y });
		temp = game->return_temp();
		if (!temp.empty()) {
			cout << "[Selected object]" << endl;
			for (auto elem : temp) {
				elem->show_stats();
				cout << endl;
			}
			cout << "..." << endl;
			cout << "Choose id..." << endl;
			cin >> id;
			if (cin) {
				if (auto temp_obj = game->select_by_id(id))
				{
					cout << "[Target selected]" << endl;
					cout << "Choose option..." << endl;
					switch (temp_obj->is_a_building())
					{
					case(false):
						cout << "1. Hit" << endl;
						cout << "2. Move" << endl;
						cin >> option;
						switch (option) {
						case(1):
							result = game->command_to_attack(id);
							break;
						case(2):
							cin >> da_way;
							temp_obj = game->relocate(da_way, dynamic_cast<Warior *>(temp_obj));
							break;
						}
						break;
					case(true):
						cout << "1.Spawn " <<endl;
						cin >> option;
						game->add_unit(temp_obj->get_id());
						break;
					default:
						break;
					}
					if (result) {
						cout << "team #" << result << " Ddefeaded!" << endl;
						break;
					}
				}
			}
			else {
				cin.clear();
			}
		}
		else cout << "[Miss]" << endl;
		cin.clear();
		game->print();
	
		
	}
	delete game;
	getchar();
	getchar();
	/*
	cout << "Field fight: START" << endl;
	ifstream fin("data.txt");
	if (fin.eof()) {
		cerr << "File not found!" << endl;
		getchar();
		exit(EXIT_FAILURE);
	}

	const shared_ptr<Crown> crown1(new Crown(1));
	const shared_ptr<Crown> crown2(new Crown(2));


	Warior *w = new Warior(fin,crown1);

	delete w;

	getchar();*/
}
