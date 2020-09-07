#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Input/Output defines
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"

// Book fields
enum
{
	SURNAME,
	FIRSTNAME,
	NUMBER,
	SIZE
};

// Convert fields for user input
map<int, int> convert =
{
	{ 1, FIRSTNAME },
	{ 2, SURNAME },
	{ 3, NUMBER }
};

// Reverse conversion from fields to user input
int reverseConvert(int second)
{
	for (pair<int, int> data : convert)
	{
		if (data.second == second)
		{
			return data.first;
		}
	}

	cout << "Second value \"" << second << "\" not defined!" << endl;
	return -1;
}

// User dialog for getting the sort type
int getSortTypeDialog()
{
	cout << "Select type sort:" << endl
		<< "1) For firstname" << endl
		<< "2) For surname" << endl
		<< "3) Sor number" << endl;

	cout << "> ";
	int sortType;
	cin >> sortType;
	system("cls");

	// Check valid 'sortType'
	if (sortType < 1 || sortType > SIZE)
	{
		return getSortTypeDialog();
	}

	return convert[sortType];
}

class PhoneBook
{
public:
	PhoneBook()
	{}

	~PhoneBook()
	{}

	void loadFromFile(const string& file)
	{
		ifstream fin(INPUT_FILE);
		string str;

		if (fin.is_open())
		{
			while (fin >> str)
			{
				vector<string> data(SIZE);

				data[SURNAME] = str;

				fin >> str;
				str.pop_back(); // delete ':'
				data[FIRSTNAME] = str;

				fin >> str;
				data[NUMBER] = str;

				phoneBook.push_back(data);
			}

			cout << "File \"" << INPUT_FILE << "\" successfully uploaded!" << endl;
			fin.close();
		}
		else
		{
			cout << "File \"" << INPUT_FILE << "\" not found!" << endl;
		}
	}

	void sort(int type)
	{
		sortType = type;

		string strLeft, strRight;

		std::sort(phoneBook.begin(), phoneBook.end(), [&](vector<string> vecLeft, vector<string> vecRight)
		{
			strLeft = vecLeft[sortType];
			strRight = vecRight[sortType];

			if (sortType == NUMBER)
			{
				return stoi(strLeft) < stoi(strRight);
			}

			return strLeft < strRight;
		});
	}

	void saveToFile(const string& file)
	{
		ofstream fout(OUTPUT_FILE);

		fout << "Type sort: " << reverseConvert(sortType) << endl;

		size_t size = phoneBook.size();
		for (size_t i = 0; i < size; i++)
		{
			fout << phoneBook[i][sortType];

			if (sortType == NUMBER)
			{
				fout << ":";
			}

			for (int j = 0; j < SIZE; j++)
			{
				if (sortType != j)
				{
					fout << " " << phoneBook[i][j];
				}

				if (sortType != NUMBER && j == FIRSTNAME)
				{
					fout << ":";
				}
			}
			fout << endl;
		}

		cout << "File " << OUTPUT_FILE << " completed successfully!" << endl;
		fout.close();
	}

private:
	vector<vector<string>> phoneBook;
	int sortType;
};

int main()
{
	PhoneBook book;
	book.loadFromFile(INPUT_FILE);
	book.sort(getSortTypeDialog());
	book.saveToFile(OUTPUT_FILE);

	return 0;
}