#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class String_dyn
{
private:
	char* str;
	size_t len;
public:
	String_dyn();
	String_dyn(const char* init);
	String_dyn(const String_dyn& obj);
	~String_dyn();
	friend ostream& operator<<(ostream&, String_dyn&);
	friend istream& operator>>(istream&, String_dyn&);
	String_dyn(String_dyn&& obj);
	const int Size();
	String_dyn& operator = (const String_dyn& src_str)
	{
		if (this == &src_str)
			return *this;
		if (len != src_str.len || len == 0)
		{
			delete[] str;
			len = src_str.len;
			str = new char[len + 1];
		}
		strcpy_s(str, len, src_str.str);
		return *this;
	}
	char operator[](const int i)
	{
		return this->str[i];
	}
	String_dyn operator+(const String_dyn& right_str)
	{
		String_dyn temp_str;
		temp_str.len = this->len + right_str.len + 1;
		temp_str.str = new char[temp_str.len];
		strcpy_s(temp_str.str, this->len, this->str);
		strcat_s(temp_str.str, temp_str.len, right_str.str);
		return temp_str;
	}



};

const int String_dyn::Size()
{
	return len;
}
ostream& operator<<(ostream& stream, String_dyn& obj) {
	stream << obj.str;
	return stream;
};
istream& operator>>(istream& stream, String_dyn& obj) {
	obj.str = new char[BUFSIZ];
	stream >> obj.str;
	obj.len = strlen(obj.str) + 1;
	return stream;
};

String_dyn::String_dyn()
{
	len = 0;
	str = nullptr;
}

String_dyn::String_dyn(const char* init)
{
	len = strlen(init) + 1;
	str = new char[len + 1];
	for (uint32_t i = 0; i < len; i++)
	{
		str[i] = init[i];
	}
}
String_dyn::String_dyn(const String_dyn& obj)
{
	len = obj.len;
	str = new char[len + 1];
	memcpy(str, obj.str, len);
}

String_dyn::String_dyn(String_dyn&& obj)
{
	str = obj.str;
	len = obj.len;
	obj.str = nullptr;
	obj.len = 0;
}

String_dyn::~String_dyn()
{
	delete[] str;
	len = 0;
}

int main()
{
	size_t str_num;
	String_dyn curr_str;

	//========= My string example ========
	String_dyn s = "string";
	String_dyn s1 = "array";
	String_dyn s2(s1);
	String_dyn s3 = s + " " + s1 + " " + s;
	cout << s2 << endl;
	cout << s3 << endl;

	//======= Standart string example =======
	string str1 = "example";
	string str2(str1);
	string str3 = str1 + " " + str2 + " standart";
	cout << str3 << endl;
	cout << str2 << endl;

	//========= Print sorted strings ========
	cout << "Enter str number" << endl;
	cin >> str_num;
	cin.clear();
	vector<String_dyn> v;
	v.reserve(str_num);
	for (size_t i = 0; i < str_num; i++)
	{
		if (i == 0)
			cout << "Enter string" << endl;
		else
			cout << "Enter one's more string" << endl;
		cin >> curr_str;
		v.push_back(curr_str);
	}
	cout << "Usorted string" << endl;
	for (auto& s : v) {
		cout << s << ' ';
	};
	cout << endl;
	int sz = s.Size();
	sort(v.begin(), v.end(), [](String_dyn& a, String_dyn& b) {

		for (int i = 0; i < min(a.Size(), b.Size()); i++) {
			const auto a_char = tolower(a[i]);
			const auto b_char = tolower(b[i]);
			if (a_char != b_char) {
				return a_char > b_char;
			}
		}
		return a.Size() > b.Size();
		});
	cout << "Sorted string" << endl;
	for (auto& s : v) {
		cout << s << ' ';
	};
	cout << endl;
	return 0;
}