//============================================================================
// Name        : White_Project.cpp
// Author      : grec88
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <exception>
#include <iomanip>
#include <sstream>
using namespace std;

void Ensure_Date(stringstream &ss) {
	if (ss.fail() || ss.peek() != EOF) {
		throw runtime_error("Wrong date format: " + ss.str());
	}
}

void Ensure_Month(const int &value) {
	if (value <= 0 || value > 12) {
		throw runtime_error("Month value is invalid: " + to_string(value));
	}
}

void Ensure_Day(const int &value) {
	if (value <= 0 || value > 31) {
		throw runtime_error("Day value is invalid: " + to_string(value));
	}
}

void Ensure_Operation(const string &opera) {
	if (!(opera == "Add" || opera == "Del" || opera == "Find"
			|| opera == "Print" || opera == "")) {
		throw runtime_error("Unknown command: " + opera);
	}
}


struct Year {
	int year;

	explicit Year(const int &year) {
		this->year = year;
	}
};

struct Month {
	int month;

	explicit Month(const int &month) {
		this->month = month;
	}
};

struct Day {
	int day;

	explicit Day(const int &day) {
		this->day = day;
	}
};

class Date {
public:

	Date() {
		year = 1;
		month = 1;
		day = 1;
	}

	Date(const Year &new_year, const Month &new_month, const Day &new_day) {
		this->year = new_year.year;
		this->month = new_month.month;
		this->day = new_day.day;
	}

	int GetYear() const {
		return year;
	}

	int GetMonth() const {
		return month;
	}

	int GetDay() const {
		return day;
	}

private:
	int year;
	int month;
	int day;
};

void PrintSet(const set<string> &set) {
	for (const auto &c : set) {
		if (find(begin(set), end(set), c) == --end(set)) {
			cout << c << "\n";
		} else {
			cout << c << "\n";
		}
	}
}

bool operator<(const Date &lhs, const Date &rhs) {
	if (lhs.GetYear() < rhs.GetYear()
			|| (lhs.GetYear() == rhs.GetYear()
					&& lhs.GetMonth() < rhs.GetMonth())
			|| (lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() < rhs.GetDay())) {
		return true;
	} else {
		return false;
	}
}

istream& operator>>(istream &stream, Date &date) {
	int year, month, day;
	char a, b;
	string input;
	stream >> input;
	stringstream ss(input);
	if (ss) {
		ss >> year >> a >> month >> b >> day;
		if (ss) {
			if (a == '-' && b == '-') {
				date = Date(Year { year }, Month { month }, Day { day });
				Ensure_Month(month);
				Ensure_Day(day);
			} else {
				ss.setstate(ios_base::failbit);
			}
		}
	}
	Ensure_Date(ss);
	return stream;
}

ostream& operator<<(ostream &stream, const Date &date) {
	stream << setw(4) << setfill('0') << date.GetYear() << '-' << setw(2)
			<< date.GetMonth() << '-' << setw(2) << date.GetDay();
	return stream;
}

class Database {
public:
	void AddEvent(const Date &date, const string &event) {
		base[date].insert(event);
	}
	bool DeleteEvent(const Date &date, const string &event) {
		if (find(begin(base[date]), end(base[date]), event)
				!= end(base[date])) {
			if (base[date].size() == 1) {
				base.erase(date);
				return true;
			} else {
				base[date].erase(
						find(begin(base[date]), end(base[date]), event));
				return true;
			}
		} else {
			return false;
		}
	}
	int DeleteDate(const Date &date) {
		int quant = base[date].size();
		base.erase(date);
		return quant;
	}

	void Find(const Date &date) const {
		if(base.count(date) != 0){
		PrintSet(base.at(date));
		}
	}

	void Print() const {
		if (!base.empty()) {
			for (const auto& [key, value] : base) {
				for (const auto &c : value) {
					cout << key << " ";
					if (find(begin(value), end(value), c) == --end(value)) {
						cout << c << "\n";
					} else {
						cout << c << "\n";
					}
				}
			}
		}
	}

private:
	map<Date, set<string>> base;
};

int main() {
	Database db;
	string command;
	try {
		while (getline(cin, command)) {
			stringstream ss(command);
			string operation;
			ss >> operation;
			Ensure_Operation(operation);
			if (operation != "Print" && operation != "") {
				Date date;
				string event;
				ss >> date >> event;
				if (operation == "Add") {
					db.AddEvent(date, event);
				}
				if (operation == "Del") {
					if (event.empty()) {
						cout << "Deleted " << db.DeleteDate(date)
								<< " events\n";
					} else {
						if (db.DeleteEvent(date, event)) {
							cout << "Deleted successfully\n";
						} else {
							cout << "Event not found\n";
						}
					}
				}
				if (operation == "Find") {
					db.Find(date);
				}
			} else if (operation == "Print" && operation != "") {
				db.Print();
			}
		}
	} catch (exception &ex) {
		cout << ex.what();
	}
	return 0;
}

/*#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Date {
public:
  // конструктор выбрасывает исключение, если его аргументы некорректны
  Date(int new_year, int new_month, int new_day) {
    year = new_year;
    if (new_month > 12 || new_month < 1) {
      throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
      throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
  }

  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }

private:
  int year;
  int month;
  int day;
};

// определить сравнение для дат необходимо для использования их в качестве ключей словаря
bool operator<(const Date& lhs, const Date& rhs) {
  // воспользуемся тем фактом, что векторы уже можно сравнивать на <:
  // создадим вектор из года, месяца и дня для каждой даты и сравним их
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

// даты будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const Date& date) {
  stream << setw(4) << setfill('0') << date.GetYear() <<
      "-" << setw(2) << setfill('0') << date.GetMonth() <<
      "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    storage[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event) {
    if (storage.count(date) > 0 && storage[date].count(event) > 0) {
      storage[date].erase(event);
      return true;
    }
    return false;
  }

  int DeleteDate(const Date& date) {
    if (storage.count(date) == 0) {
      return 0;
    } else {
      const int event_count = storage[date].size();
      storage.erase(date);
      return event_count;
    }
  }

  set<string> Find(const Date& date) const {
    if (storage.count(date) > 0) {
      return storage.at(date);
    } else {
      return {};
    }
  }

  void Print() const {
    for (const auto& item : storage) {
      for (const string& event : item.second) {
        cout << item.first << " " << event << endl;
      }
    }
  }

private:
  map<Date, set<string>> storage;
};

Date ParseDate(const string& date) {
  istringstream date_stream(date);
  bool ok = true;

  int year;
  ok = ok && (date_stream >> year);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int month;
  ok = ok && (date_stream >> month);
  ok = ok && (date_stream.peek() == '-');
  date_stream.ignore(1);

  int day;
  ok = ok && (date_stream >> day);
  ok = ok && date_stream.eof();

  if (!ok) {
    throw logic_error("Wrong date format: " + date);
  }
  return Date(year, month, day);
}

int main() {
  try {
    Database db;

    string command_line;
    while (getline(cin, command_line)) {
      stringstream ss(command_line);

      string command;
      ss >> command;

      if (command == "Add") {

        string date_str, event;
        ss >> date_str >> event;
        const Date date = ParseDate(date_str);
        db.AddEvent(date, event);

      } else if (command == "Del") {

        string date_str;
        ss >> date_str;
        string event;
        if (!ss.eof()) {
          ss >> event;
        }
        const Date date = ParseDate(date_str);
        if (event.empty()) {
          const int count = db.DeleteDate(date);
          cout << "Deleted " << count << " events" << endl;
        } else {
          if (db.DeleteEvent(date, event)) {
            cout << "Deleted successfully" << endl;
          } else {
            cout << "Event not found" << endl;
          }
        }

      } else if (command == "Find") {

        string date_str;
        ss >> date_str;
        const Date date = ParseDate(date_str);
        for (const string& event : db.Find(date)) {
          cout << event << endl;
        }

      } else if (command == "Print") {

        db.Print();

      } else if (!command.empty()) {

        throw logic_error("Unknown command: " + command);

      }
    }
  } catch (const exception& e) {
    cout << e.what() << endl;
  }

  return 0;
}*/
