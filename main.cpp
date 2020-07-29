#include<algorithm>
#include<cmath>
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<typeinfo>
#include<set>
#include <cctype>
#include<fstream>

using namespace std;





class Person {
private:
	map<int, string, greater<int>> first_names;
	map<int, string, greater<int>> last_names;
	int birthday;
public:

	Person(string first_name, string last_name, int year) {
		first_names[year] = first_name;
		last_names[year] = last_name;
		birthday = year;
	}

	void PrintMap() {
		for (const auto& i : first_names) {
			cout << i.first << " : " << i.second << '\n';
		}
		cout << "Next\n\n";
		for (const auto& i : last_names) {
			cout << i.first << " : " << i.second << '\n';
		}

		cout << first_names.begin()->first << " : " << endl;

		auto it = first_names.lower_bound(3853);

		if (it == first_names.end()) {
			cout << "All values less of key\n";
		}
		else cout << first_names.lower_bound(3853)->first << "\n";
	}

	void ChangeFirstName(int year, const string& first_name) {
		if (year < birthday) {
			return;
		}

		first_names[year] = first_name;
	}

	void ChangeLastName(int year, const string& last_name) {
		if (year < birthday) {
			return;
		}
		last_names[year] = last_name;
	}

	string GetFullName(int year) const  {
		if (year < birthday) {
			return "No person";
		}

		auto it_first = first_names.lower_bound(year);
		auto it_last = last_names.lower_bound(year);

		if (it_first == first_names.end() && it_last == last_names.end())
			return "Incognito";

		if (it_first == first_names.end())
			return it_last->second + " with unknown first name";

		if (it_last == last_names.end())
			return it_first->second + " with unknown last name";

		return it_first->second + " " + it_last->second;
	}

	string GetFromIterator(const map<int, string, greater<int>>& some, int year) const {

		auto it_first_names = some.lower_bound(year);
		string result = (it_first_names)->second;

		bool check = false;
		if (it_first_names == --end(some)) {
			check = true;
		}

		while (it_first_names != end(some) && !check) {
			string prew_names = it_first_names->second;
			it_first_names = some.lower_bound(it_first_names->first - 1);



			if ((it_first_names == --end(some) && it_first_names->second != prew_names)) {

				if (result.find('(') == string::npos) {
					result += " (";
				}

				result += it_first_names->second + ")";
				return result;
			}

			if ( it_first_names != end(some) && it_first_names->second != prew_names) {

				if (result.find('(') == string::npos) {
					result += " (";
				}

				result += it_first_names->second + ", ";
				prew_names = it_first_names->second;
			}
		}
		return result;
	}

	string GetFullNameWithHistory(int year) const {

		if (year < birthday) {
			return "No person";
		}

		auto it_first = first_names.lower_bound(year);
		auto it_last = last_names.lower_bound(year);

		if (it_first == first_names.end() && it_last == last_names.end())
			return "Incognito";

		if (it_first == first_names.end())
			return GetFromIterator(last_names, year) + " with unknown first name";

		if (it_last == last_names.end())
			return GetFromIterator(first_names, year) + " with unknown last name";

		return GetFromIterator(first_names, year) + " " + GetFromIterator(last_names, year);
	}
};





int main() {

	Person person("Polina", "Sergeeva", 1960);
	for (int year : {1959, 1960}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : {1965, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}
	
    return 0;
}