#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
using namespace std;

enum Color {
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue = 9, LightGreen,
	LightCyan, LightRed, LightMagenta, Yellow, White
};
enum Direction {
	Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27, A = 97, D = 100
};
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
void setColor(Color text, Color background = Black)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
void setCursor(int x, int y) {
	COORD coordination = { x,y };
	SetConsoleCursorPosition(hStdOut, coordination);
}
void showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void build()
{
	CreateDirectoryA("Data", NULL);
	ofstream in;
	in.open("Users.txt", ios_base::app);
	in.close();
}
Color getImportance(string Priority)
{
	if (Priority == "Important")
	{
		return Red;
	}
	else if (Priority == "Medium")
	{
		return Yellow;
	}
	return White;
}

string month[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
int days[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
int first_day[12] = { 3,6,7,3,5,1,3,6,2,4,7,2 };
string day[7] = { "Mon","Tue","Wed","Thu","Fri","Sat","Sun" };

string toStr(int value)
{
	char str[5];
	_itoa(value, str, 10);
	return (string)str;
}

struct Data
{
	int Month;
	int Day;
};
struct Time
{
	int hours = 0;
	int mins = 0;
};

void SetFontSize(int x, int y)
{
	HANDLE Hout = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD fsize = { x,y };
	CONSOLE_FONT_INFOEX Font = { sizeof(Font) };
	::GetCurrentConsoleFontEx(Hout, FALSE, &Font);

	Font.dwFontSize = fsize;
	SetCurrentConsoleFontEx(Hout, 0, &Font);
}
int LogMenu()
{

	string LogStr[2] = { "Log In", "Check In" };
	int poz = 0;
	int input;
	do
	{
		system("cls");
		int y = 10;
		for (size_t i = 0; i < 2; i++)
		{

			setCursor(35, y);
			if (poz == i)
			{
				setColor(Black, White);
			}
			cout << LogStr[i] << endl;
			setColor(White, Black);
			y++;
		}
		input = _getch();
		switch (input)
		{
		case Up:
			if (poz == 0)
			{
				poz = 1;
			}
			poz--;
			break;
		case Down:
			if (poz == 1)
			{
				poz = 0;
			}
			poz++;
			break;
		case Enter:
			showConsoleCursor(true);
			return poz;
			break;
		case Esc:
			break;
		default:
			break;
		}
	} while (input != Enter);

}
int DayMenu()
{
	string Choose[4] = { "Add Event", "Delete Event", "Edit Event","Back" };
	int poz = 0;
	int input;
	do
	{
		int y = 10;
		for (size_t i = 0; i < 4; i++)
		{
			setCursor(55, y);
			if (poz == i)
			{
				setColor(Black, White);
			}
			cout << Choose[i] << endl;
			setColor(White, Black);
			y++;
		}
		input = _getch();
		switch (input)
		{
		case Up:
			if (poz == 0)
			{
				poz = 3;
			}
			else
			{
				poz--;
			}
			break;
		case Down:
			if (poz == 3)
			{
				poz = 0;
			}
			else
			{
				poz++;
			}
			break;
		case Enter:
			return poz;
			break;
		case Esc:
			break;
		default:
			break;
		}
	} while (input != Enter);
}
Time TimeGeneration()
{
	string b;
	int input;
	Time hour;
	int time[2] = { 0,0 };
	int Element = 0;
	do
	{
		system("cls");
		setCursor(35, 10);
		cout << "Choose time: ";
		if (time[1] < 10)
		{
			b = "0";
		}
		if (Element == 0)
		{
			setColor(Black, White);
		}
		cout << time[0];
		setColor(White, Black);
		cout << ":";
		if (Element == 1)
		{
			setColor(Black, White);
		}
		cout << b << time[1] << endl;
		setColor(White, Black);
		b = "";
		input = _getch();
		switch (input)
		{
		case Up:
			if (time[0] == time[Element] && time[0] == 23)
			{
				time[0] = 0;
			}
			else if (time[1] == time[Element] && time[1] == 59)
			{
				time[1] = 0;
			}
			else
			{
				time[Element]++;
			}
			break;
		case Down:
			if (time[0] == time[Element] && time[0] == 0)
			{
				time[0] = 23;
			}
			else if (time[1] == time[Element] && time[1] == 0)
			{
				time[1] = 59;
			}
			else
			{
				time[Element]--;
			}
			break;
		case Left:
			Element = 0;
			break;
		case Right:
			Element = 1;
			break;
		case Enter:
			break;
		case Esc:
			break;
		default:
			break;
		}
	} while (input != Enter);
	hour.hours = time[0];
	hour.mins = time[1];
	return hour;
}
string PriorityGeneration()
{
	string importance[3] = { "Important", "Medium", "Usuall" };
	int input;
	int Element = 0;
	do
	{
		setCursor(50, 13);
		cout << "              ";
		setCursor(50, 13);
		setColor(Black, White);
		cout << importance[Element];
		input = _getch();
		setColor(White, Black);
		cout << "             ";
		switch (input)
		{
		case Up:
			if (Element == 0)
			{
				Element = 2;
			}
			else
			{
				Element--;
			}
			break;
		case Down:
			if (Element == 2)
			{
				Element = 0;
			}
			else
			{
				Element++;
			}
			break;
		case Enter:
			return importance[Element];
			break;
		case Esc:
			break;
		default:
			break;
		}
	} while (input != Enter);
}
Time ReturnCurrentTime()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	Time time = { ltm->tm_hour,ltm->tm_min };
	return time;
}
Data ReturnCurrentDate()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	Data Date = { ltm->tm_mon,ltm->tm_mday };
	return Date;
}
bool GreenColor(Time t, Data d)
{
	Data currentDate = ReturnCurrentDate();
	Time currentTime = ReturnCurrentTime();
	if ((currentDate.Month > d.Month) || (currentDate.Month == d.Month && currentDate.Day > d.Day) || (currentDate.Month == d.Month && currentDate.Day == d.Day && currentTime.hours > t.hours) || (currentDate.Month == d.Month && currentDate.Day == d.Day && currentTime.hours == t.hours && currentTime.mins >= t.mins))
	{
		setColor(Yellow, Black);
	}
	else if (currentDate.Month == d.Month)
	{
		if (currentDate.Day + 1 == d.Day)
		{
			if (currentTime.hours == t.hours && currentTime.mins >= t.mins)
			{
				setColor(Green, Black);
				return true;
			}
			else if (currentTime.hours > t.hours)
			{
				setColor(Green, Black);
				return true;
			}
		}
		else if (currentDate.Day == d.Day)
		{
			setColor(Green, Black);
			return true;
		}
	}
	else
	{
		setColor(White, Black);
	}
	return false;
}
int SelectEvent(int value)
{
	int poz = 1;
	int input;
	if (value == 1)
	{
		return poz;
	}
	do
	{
		for (size_t i = 0; i < value; i++)
		{
			setCursor(18, i + 10);
			cout << "  ";
		}
		setCursor(18, 9 + poz);
		cout << "->";
		input = _getch();
		switch (input)
		{
		case Up:
			if (poz == 1)
			{
				poz = value;
			}
			else
			{
				poz--;
			}
			break;
		case Down:
			if (poz == value)
			{
				poz = 1;
			}
			else
			{
				poz++;
			}
			break;
		case Enter:
			return poz;
			break;
		case Esc:
			break;
		default:
			break;
		}
	} while (input != Enter);
}

bool PorF(Data Date, Time time)
{
	Data currentDate = ReturnCurrentDate();
	Time current = ReturnCurrentTime();
	if ((currentDate.Month < Date.Month) || (currentDate.Month == Date.Month && currentDate.Day < Date.Day) || (currentDate.Month == Date.Month && currentDate.Day == Date.Day && current.hours < time.hours) || (currentDate.Month == Date.Month && currentDate.Day == Date.Day && current.hours == time.hours && current.mins < time.mins))
	{
		return true;
	}
	return false;
}

class Event
{
	int value;
	string Holiday;
	Data Date;
	Time tme;
	Time doing;
	string Priority;
	string Type;
	Time currentTime;
	Data currentDate;
	void Show(vector<Event> v, Data Date, bool mode)
	{
		bool green = false;
		currentTime = ReturnCurrentTime();
		currentDate = ReturnCurrentDate();
		int z = 1;
		int y = 10;
		if (!mode)
		{
			setCursor(37, 5);
			cout << month[Date.Month] << "," << Date.Day << endl;
		}
		if (mode && v.size() != 0)
		{
			setCursor(30, y);
			cout << "Today's events:";
			y++;
		}
		if (v.size() == 0 && mode)
		{
			setCursor(28, 10);
			cout << "No events for today\n";
		}
		else if (v.size() == 0 && !mode)
		{
			setCursor(15, 10);
			cout << "No events for this day\n";
		}
		for (size_t i = 0; i < v.size(); i++)
		{
			string b;
			green = GreenColor(v[i].tme, Date);
			if (v.size() != 0)
			{
				if (mode)
				{
					if (green)
					{
						setCursor(30, y);
						y++;
						if (v[i].tme.hours < 10)
						{
							b = "0";
						}
						cout << b << v[i].tme.hours << ":";
						if (v[i].tme.mins < 10)
						{
							b = "0";
						}
						cout << b << v[i].tme.mins << " ";
						setColor(getImportance(v[i].Priority), Black);
						cout << v[i].Holiday << " ";
						setColor(White, Black);
						cout << v[i].Type << endl;
						b = "";
						green = false;
						z++;
					}
				}
				else
				{
					setCursor(20, y);
					y++;
					if (v[i].tme.hours < 10)
					{
						b = "0";
					}
					if (v[i].Type != "Public")
					{
						cout << b << v[i].tme.hours << ":";
						if (v[i].tme.mins < 10)
						{
							b = "0";
						}
						cout << b << v[i].tme.mins << " ";
					}
					setColor(getImportance(v[i].Priority), Black);
					cout << v[i].Holiday << " ";
					if (v[i].Type != "Public")
					{
						setColor(White, Black);
						cout << v[i].Type << endl;
					}
					setColor(White, Black);
					b = "";
					green = false;
				}
			}
		}
		if (mode)
		{
			setCursor(30, y);
			setColor(White, Black);
			cout << "Press any button to continue";
			system("pause>>NULL");
		}
	}
	void Sort(int poz, vector<Event> v, Data Date, bool mode)
	{
		int z = 0;
		if (v.size() > 1)
		{
			do
			{
				for (size_t i = 0; i < v.size() - 1; i++)
				{
					if (v[i].tme.hours > v[i + 1].tme.hours)
					{
						swap(v[i], v[i + 1]);
					}
					else if ((v[i].tme.mins > v[i + 1].tme.mins) && v[i].tme.hours == v[i + 1].tme.hours)
					{
						swap(v[i], v[i + 1]);
					}
					z++;
				}
			} while (z < v.size());
		}
		value = v.size();
		if (poz != 0)
		{
			doing = v[poz - 1].tme;
		}

		else
		{
			Show(v, Date, mode);
		}

	}
public:
	void SetPublicHolidays(string login)
	{
		ifstream file;
		file.open("PublicHolidays.txt");
		if (file.is_open())
		{
			while (!file.eof())
			{
				getline(file, Holiday);
				file >> Date.Day;
				file >> Date.Month;
				AddEvent(Holiday, Date, login);
				getline(file, Holiday);
			}
		}
	}
	void AddEvent(string Holiday, Data Date, string login)
	{

		string path = "Data\\" + login + "\\" + month[Date.Month - 1] + "\\" + toStr(Date.Day) + ".txt";
		ofstream file;
		file.open(path.c_str());
		file << Holiday << endl << "00 00 " << "Public " << "Important " << endl;
		file.close();
	}
	void AddEvent(string Holiday, Data Date, Time time, string Priority, string Type, string login, bool buff)
	{
		string Day = toStr(Date.Day);
		string path;
		if (buff)
		{
			path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + "buff.txt";
		}
		else
		{
			path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + toStr(Date.Day) + ".txt";
		}
		ofstream file;
		file.open(path.c_str(), ios_base::app);
		file << Holiday << endl << time.hours << " " << time.mins << " " << Type << " " << Priority << endl;
		file.close();
	}
	bool DeleteEvent(Data Date, string login)
	{
		string Day = toStr(Date.Day);
		string path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + Day + ".txt";
		string buff;
		Time B;
		ifstream out;
		bool key = false;
		out.open(path.c_str());
		getline(out, Holiday);
		if (Holiday == "")
		{
			system("cls");
			setCursor(30, 10);
			cout << "No one event to delete\n";
			Sleep(1000);
		}
		else
		{
			Read(SelectEvent(value), Date, login, true);
			tme = doing;
			while (!out.eof())
			{
				out >> B.hours;
				out >> B.mins;
				out >> Type;
				out >> Priority;
				if (tme.hours == B.hours && tme.mins == B.mins)
				{
					getline(out, buff);
					getline(out, Holiday);
					key = true;
					continue;
				}
				AddEvent(Holiday, Date, B, Priority, Type, login, true);
				getline(out, buff);
				getline(out, Holiday);
			}
		}
		out.close();
		ofstream in;
		in.open(path.c_str(), ios_base::trunc);
		in.close();
		CopyEvent(Date, login);
		path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + "buff.txt";
		in.open(path.c_str(), ios_base::trunc);
		in.close();
		return key;
	}
	bool DeleteEvent(Data Date, string login, Time time)
	{
		string Day = toStr(Date.Day);
		string path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + Day + ".txt";
		string buff;
		Time B;
		ifstream out;
		bool key = false;
		out.open(path.c_str());
		getline(out, Holiday);
		if (Holiday == "")
		{
			system("cls");
			setCursor(30, 10);
			cout << "No one event to delete\n";
			Sleep(1000);
		}
		else
		{
			while (!out.eof())
			{
				out >> B.hours;
				out >> B.mins;
				out >> Type;
				out >> Priority;
				if (time.hours == B.hours && time.mins == B.mins)
				{
					getline(out, buff);
					getline(out, Holiday);
					key = true;
					continue;
				}
				AddEvent(Holiday, Date, B, Priority, Type, login, true);
				getline(out, buff);
				getline(out, Holiday);
			}
		}
		out.close();
		ofstream in;
		in.open(path.c_str(), ios_base::trunc);
		in.close();
		CopyEvent(Date, login);
		path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + "buff.txt";
		in.open(path.c_str(), ios_base::trunc);
		in.close();
		return key;
	}
	void CopyEvent(Data Date, string login)
	{
		string Day = toStr(Date.Day);
		string path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + "buff.txt";
		string buff;
		ifstream out;
		out.open(path.c_str());
		do
		{
			getline(out, Holiday);
			if (Holiday == "")
			{
				break;
			}
			out >> tme.hours;
			out >> tme.mins;
			out >> Type;
			out >> Priority;
			getline(out, buff);
			AddEvent(Holiday, Date, tme, Priority, Type, login, false);
		} while (!out.eof());
	}
	void Read(int poz, Data Date, string login, bool mode)
	{
		vector<Event>events;
		Event event;
		string Day = toStr(Date.Day);
		string path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + Day + ".txt";
		string buff;
		ifstream out;
		out.open(path.c_str());
		do
		{
			getline(out, event.Holiday);
			if (event.Holiday == "")
			{
				break;
			}
			out >> event.tme.hours;
			out >> event.tme.mins;
			out >> event.Type;
			out >> event.Priority;
			getline(out, buff);
			events.push_back(event);
		} while (!out.eof());
		Sort(poz, events, Date, mode);
	}
	void EditEvent(Data Date, string login)
	{
		bool key = true;
		int time_h, time_m;
		string buff;
		currentTime = ReturnCurrentTime();
		string path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + toStr(Date.Day) + ".txt";
		ifstream file;
		file.open(path.c_str());
		getline(file, buff);
		if (buff == "")
		{
			system("cls");
			setCursor(30, 10);
			cout << "No one event to edit\n" << buff;
			Sleep(1000);
		}
		else
		{
			Read(SelectEvent(value), Date, login, true);
			tme = TimeGeneration();
			Time tme1 = tme;
			while (!file.eof())
			{
				file >> time_h;
				file >> time_m;
				getline(file, buff);
				if (PorF(Date, tme1))
				{
					if (tme.hours == time_h && tme.hours == time_h)
					{
						key = false;
						if (doing.hours == tme.hours && doing.mins == tme.mins)
						{
							key = true;
						}
					}
				}
				else
				{
					key = false;
				}
				getline(file, buff);
			}
			if (key)
			{
				DeleteEvent(Date, login, doing);
				setCursor(35, 11);
				cout << "Edit Event: ";
				cin >> Holiday;
				setCursor(35, 12);
				cout << "Edit Type of Event: ";
				cin >> Type;
				setCursor(35, 13);
				cout << "Edit Priority: ";
				Priority = PriorityGeneration();
				AddEvent(Holiday, Date, tme1, Priority, Type, login, false);
			}
			else
			{
				setCursor(28, 10);
				cout << "You can't edit at that time\n";
				Sleep(2000);
			}
		}

	}
};

class User
{
	string login;
	string password;
	string buff;
	Event event;
	Data currentDate;
public:
	void CreateData()
	{
		string path = "Data\\" + login;
		CreateDirectoryA(path.c_str(), NULL);
		for (size_t i = 0; i < 12; i++)
		{
			path = "Data\\" + login + "\\" + month[i];
			CreateDirectoryA(path.c_str(), NULL);
		}
		event.SetPublicHolidays(login);
	}
	void Reminder()
	{
		system("cls");
		event.Read(0, ReturnCurrentDate(), login, true);
	}
	bool LogIn()
	{
		ifstream file;
		file.open("Users.txt");
		bool find = false;
		system("cls");
		setCursor(30, 10);
		cout << "Type your login: ";
		cin >> login;
		while (!file.eof())
		{
			file >> buff;
			if (buff == login)
			{
				find = !find;
				setCursor(30, 11);
				cout << "Type your password: ";
				cin >> password;
				file >> buff;
				if (buff == password)
				{
					system("cls");
					setCursor(30, 9);
					cout << "Access accepted\n";
					Reminder();
					return true;
				}
				else
				{
					system("cls");
					setCursor(30, 9);
					cout << "Incorrect password\n";
					Sleep(1000);
					return false;
				}
				getline(file, buff);
			}
			else
			{
				getline(file, buff);
			}
		}
		if (!find)
		{
			setCursor(23, 10);
			cout << "There is no one with the same login\n";
			Sleep(1000);
			return false;
		}
		file.close();
		system("cls");
	}
	bool Registration()
	{
		ifstream file;
		ofstream fout;
		file.open("Users.txt");
		bool find = false;
		system("cls");
		if (file.is_open())
		{
			setCursor(30, 10);
			cout << "Type your login: ";
			cin >> login;
			while (!file.eof())
			{
				file >> buff;
				if (buff == login)
				{
					find = true;
				}
				file >> buff;
			}
			if (find)
			{
				setCursor(25, 10);
				cout << "There is one have the same login\n";
				Sleep(1000);
				file.close();
				return false;
			}
			else
			{
				setCursor(30, 11);
				cout << "Type your password: ";
				cin >> password;
				file.close();
				if (login.find_first_of("!., ?;@|") == -1 && login != "" && password.find_first_of("!., ?;@|") == -1 && password != "")
				{
					fout.open("Users.txt", ios_base::app);
					fout << login << " " << password << endl;
					fout.close();
					CreateData();
					return true;
				}
				else
				{
					system("cls");
					setCursor(27, 10);
					cout << "Incorrect login or password\n";
					Sleep(1000);
					return false;
				}
			}
		}
		system("cls");
	}
	void AddEvent(Data Date)
	{
		string Holiday;
		Time tme;
		string Priority;
		string Type;
		bool key = true;
		Time EventTime;
		string buff;
		tme = TimeGeneration();
		if (PorF(Date, tme))
		{
			string path = "Data\\" + login + "\\" + month[Date.Month] + "\\" + toStr(Date.Day) + ".txt";
			ifstream file;
			string trash;
			file.open(path.c_str());
			while (!file.eof())
			{
				getline(file, buff);
				file >> EventTime.hours;
				file >> EventTime.mins;
				getline(file, buff);
				if (EventTime.hours <= 0)
				{
					key = true;
					break;
				}
				else if (tme.hours == EventTime.hours && tme.mins == EventTime.mins)
				{
					key = false;
					cout << "Time already reserved\n";
					break;

				}
			}
			if (key)
			{
				setCursor(35, 11);
				cout << "Input Event: ";
				cin >> Holiday;
				setCursor(35, 12);
				cout << "Input Type of Event: ";
				cin >> Type;
				setCursor(35, 13);
				cout << "Input Priority: ";
				Priority = PriorityGeneration();
				event.AddEvent(Holiday, Date, tme, Priority, Type, login, false);
			}
			else
			{
				system("cls");
				setCursor(20, 10);
				cout << "Sorry, you cannot add an event at this time.\n";
				Sleep(1000);
			}
		}
		else
		{
			system("cls");
			setCursor(20, 10);
			cout << "Sorry, you cannot add an event.\n";
			Sleep(1000);
		}
	}
	void DeleteEvent(Data Date)
	{
		event.DeleteEvent(Date, login);
	}
	void ShowEvent(Data date)
	{
		event.Read(0, date, login, false);
	}
	void EditEvent(Data Date)
	{
		event.EditEvent(Date, login);
	}
	void ShowMonth(Data d)
	{
		system("cls");
		int z = 1;
		bool key = false;
		int y = 5;
		setCursor(16, y);
		cout << month[d.Month] << endl;
		y++;
		setCursor(16, y);
		for (size_t i = 0; i < 7; i++)
		{
			cout << day[i] << "\t";
		}
		cout << endl;
		for (size_t i = 0; i < 6; i++)
		{
			y++;
			setCursor(16, y);
			for (size_t i = 0; i < 7; i++)
			{
				if (i == first_day[d.Month] - 1)
				{
					key = true;
				}
				if (key)
				{
					if (z != days[d.Month] + 1)
					{
						if (z == d.Day)
						{
							setColor(Black, White);
						}
						cout << z;
						setColor(White, Black);
						cout << "\t";
						z++;
					}
					else
					{
						break;
					}
				}
				else
				{
					cout << " \t";
				}
			}
			cout << endl;
		}
	}
	Data Move()
	{
		int input;
		Data date = ReturnCurrentDate();
		do
		{
			ShowMonth(date);
			input = _getch();
			switch (input)
			{
			case Up:
				if (date.Day - 7 > 0)
				{
					date.Day -= 7;
				}
				break;
			case Down:
				if (date.Day + 7 <= days[date.Month])
				{
					date.Day += 7;
				}
				break;
			case Left:
				if (date.Day - 1 > 0)
				{
					date.Day -= 1;
				}
				break;
			case Right:
				if (date.Day + 1 <= days[date.Month])
				{
					date.Day += 1;
				}
				break;
			case A:
				if (date.Month > 0)
				{
					date.Month -= 1;
				}
				break;
			case D:
				if (date.Month < 11)
				{
					date.Month += 1;
				}
				break;
			case Enter:

				break;
			default:
				break;
			}
		} while (input != Enter);
		return date;
	}
};

class Organizer
{
	User user;
public:
	Organizer()
	{
		bool log = false;
		do
		{
			bool(User:: * p[2])() = { &User::LogIn, &User::Registration };
			showConsoleCursor(false);
			log = (user.*p[LogMenu()])();
		} while (!log);
		showConsoleCursor(false);
		Show();
	}
	void Show()
	{
		Menu(user.Move());
	}
	void Menu(Data date)
	{
		int poz = 0;
		do
		{
			system("cls");
			user.ShowEvent(date);
			void(User:: * p[3])(Data) = { &User::AddEvent, &User::DeleteEvent, &User::EditEvent };
			poz = DayMenu();
			if (poz != 3)
			{
				(user.*p[poz])(date);
			}
		} while (poz != 3);
		Show();
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	SetFontSize(24, 24);
	build();
	Organizer obj;
}


