#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;
void Space_delete(string& name)
{
	int i = 0;
	while (name[i] == ' ')
		name.erase(i, 1);

	for (i; i < name.size(); i++)
	{
		if (i + 1 == name.size())
		{
			if (name[i] == ' ')
				name.erase(i, 1);
			break;
		}
		if (name[i] == ' ' && name[i + 1] == ' ')
		{
			name.erase(i, 1);
			i--;
		}
	}
}
void Free_Berth_Check(int& free_berth_number, const vector<string>& ships_at_berthes)
{
	int i = free_berth_number;
	free_berth_number = 0;
	for (; i < ships_at_berthes.size(); i++)
	{
		if (ships_at_berthes[i].empty())
		{
			free_berth_number = i + 1;
			break;
		}
	}
}
void Print_queue(const vector<string>& queue, ofstream& fout)
{
	for (int i = 0; i < queue.size(); i++)
		fout << queue[i] << '\n';
}
void Print_berth_condition(const vector<string>& ships_at_berthes, ofstream& fout)
{
	int berth_number = 0;
	for (int i = 0; i < ships_at_berthes.size(); i++)
	{
		fout << "Причал № " << ++berth_number << ". - ";
		if (ships_at_berthes[i].empty())
			fout << "Пустой\n";
		else
			fout << ships_at_berthes[i] << '\n';
	}
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin("SHIPS.IN");
	ofstream fout("SHIPS.OUT");
	if (!fin.is_open())
	{
		fout << "Ошибка при открытии входного файла!";
		exit(0);
	}
	if (fin.peek() == EOF)
	{
		fout << "Входной файл пуст!";
		exit(0);
	}
	int berth_amount;
	fin >> berth_amount;
	vector<string>queue;
	vector<string> ships_at_berthes(berth_amount);
	int number;
	int free_berth_number = 1;
	int vacated_berth;
	while (fin >> number)
	{
		switch (number)
		{
		case 1:
		{
			string ship_name;
			getline(fin, ship_name);
			//Space_delete(ship_name);
			if (free_berth_number == 0)
			{
				queue.push_back(ship_name);
				break;
			}

			ships_at_berthes[free_berth_number - 1] = ship_name;
			Free_Berth_Check(free_berth_number, ships_at_berthes);
			break;
		}

		case 2:
		{
			fin >> vacated_berth;
			ships_at_berthes[vacated_berth - 1].clear();
			if (queue.empty())
			{
				if (vacated_berth < free_berth_number || free_berth_number == 0)
					free_berth_number = vacated_berth;
				break;
			}

			ships_at_berthes[vacated_berth - 1] = *queue.begin();
			queue.erase(queue.begin());
			break;
		}

		case 3:
		{
			fout << "Очередь в данный момент: ";
			if (queue.empty())
				fout << "Отсутствует" << '\n';
			else
			{
				fout << '\n';
				Print_queue(queue, fout);
			}
			break;
		}

		case 4:
		{
			fout << "Состояние причалов в данный момент: " << '\n';
			Print_berth_condition(ships_at_berthes, fout);
			break;
		}

		default:
			break;
		}
	}
	fin.close();
	fout.close();
}