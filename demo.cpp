#include"demo.h"
void strScene(string str, vector<string>* mathList) {
	size_t index = 0;
	string temp;
	string temp1;
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == '[') {
			index = i + 1;
			continue;
		}
		if (str[i] == ',') {
			temp = str.substr(index, i - index);
			temp1 = temp;
			temp = "";
			mathList->push_back(temp1);
			index = i + 1;
			continue;
		}
		if (str[i] == ']') {
			temp = str.substr(index, i - index);
			temp1 = temp;
			mathList->push_back(temp1);
			return;
		}
	}
}
size_t min(size_t a, size_t b) {
	if (a > b) {
		return b;
	}
	return a;
}
size_t max(size_t a, size_t b) {
	if (a > b) {
		return a;
	}
	return b;
}
size_t delFloat(string* str) {
	size_t temp = str->size();
	for (int i = 0; i < str->size(); i++) {
		if ((*str)[i] == '.') {
			*str = str->substr(0, i) + str->substr(i+1, str->size());
			return temp - i - 1;
		}
	}
	return 0;
}
size_t strCompletion(string* str1, string* str2 ,bool tf) {//对string进行改造，使其表示为整数，并返回结果小数位数
	size_t floatSize1 = delFloat(str1);
	size_t floatSize2 = delFloat(str2);
	if (floatSize1 > floatSize2) {
		size_t disparity = floatSize1 - floatSize2;
		for (size_t i = 0; i < disparity; i++) {
			str2->push_back('0');
		}
	}
	else if (floatSize2 > floatSize1) {
		size_t disparity = floatSize2 - floatSize1;
		for (size_t i = 0; i < disparity; i++) {
			str1->push_back('0');
		}
	}
	if (str1->size() == str2->size()) {
		if (tf) {
			size_t a = max(floatSize1, floatSize2) * 2;
			return a;
		}
		return max(floatSize1, floatSize2);
	}
	else if (str1->size() > str2->size()) {
		size_t disparity = str1->size() - str2->size();
		for (size_t i = 0; i < disparity; i++) {
			*str2 = "0" + (*str2);
		}
	}
	size_t disparity = str2->size() - str1->size();
	for (size_t i = 0; i < disparity; i++) {
		*str1 = "0" + (*str1);
	}
	if (tf) {
		return max(floatSize1, floatSize2) * 2;
	}
	return max(floatSize1, floatSize2);
}
int strCompare(string* str1, string* str2) {
	string temp1 = *str1;
	string temp2 = *str2;
	strCompletion(&temp1, &temp2, false);
	if (temp1 > temp2) {
		return 1;
	}
	else if (temp1 < temp2) {
		return -1;
	}
	return 0;
}
string deInvalid(string* str) {
	string temp = (*str);
	bool tf = false;
	if (temp[0] == '.') {
		temp = "0" + temp;
	}
	for (size_t i = 0; i < temp.size() - 1; i++) {
		if (temp[0] == '0' && temp[1] != '.') {
			temp = temp.substr(1, temp.size());
		}
	}
	if (temp[temp.size() - 1] == '.') {
		temp.pop_back();
	}
	for (size_t i = 0; i < temp.size(); i++) {
		if (temp[i] == '.') {
			tf = true;
			break;
		}
	}
	if (tf) {
		while (1) {
			if (temp[temp.size() - 1] == '0') {
				temp.pop_back();
			}
			else {
				break;
			}
		}
	}
	if (temp[temp.size() - 1] == '.') {
		temp.pop_back();
	}
	return temp;
}
string subtraction(string* str1, string* str2) {
	string temp1 = *str1;
	string temp2 = *str2;
	size_t floatSize = strCompletion(str1, str2,false);
	string temp;
	for (size_t i = 0; i < str1->size(); i++) {
		(*str1)[i] -= '0';
		(*str2)[i] -= '0';
		temp.push_back((*str1)[i] - (*str2)[i]);
	}
	for (size_t i = temp.size(); i > 0; i--) {
		if (temp[i] < 0) {
			temp[i] += 10;
			temp[i - 1] -= 1;
		}
	}
	for (size_t i = 0; i < temp.size(); i++) {
		temp[i] += '0';
	}
	if (floatSize > 0) {
		temp = temp.substr(0, temp.size()-floatSize) + "." + temp.substr(temp.size() - floatSize, temp.size());
	}
	temp = deInvalid(&temp);
	*str1 = deInvalid(&temp1);
	*str2 = deInvalid(&temp2);
	return temp;
}
string addition(string* str1, string* str2) {
	string temp1 = *str1;
	string temp2 = *str2;
	size_t floatSize = strCompletion(str1, str2, false);
	string temp;
	for (size_t i = 0; i < str1->size(); i++) {
		(*str1)[i] -= '0';
		(*str2)[i] -= '0';
		temp.push_back((*str1)[i] + (*str2)[i]);
	}
	for (size_t i = temp.size(); i > 0; i--) {
		if (temp[i] >= 10) {
			temp[i] -= 10;
			temp[i - 1] += 1;
		}
		if (temp[0] > 10) {
			temp[0] -= 10;
			temp = "1" + temp;
			temp[0] -= '0';
		}
	}
	for (size_t i = 0; i < temp.size(); i++) {
		temp[i] += '0';
	}
	if (floatSize > 0) {
		temp = temp.substr(0, temp.size() - floatSize) + "." + temp.substr(temp.size() - floatSize, temp.size());
	}
	*str1 = deInvalid(&temp1);
	*str2 = deInvalid(&temp2);
	temp = deInvalid(&temp);
	return temp;
}

string multiplication(string* str1, string* str2) {
	string temp1 = *str1;
	string temp2 = *str2;
	string bits;
	string earry;
	string tempEb;
	string tempAd("0");
	vector<string> addList;
	string temp("0");
	size_t floatSize = strCompletion(&temp1, &temp2, true);//数字补齐，将小数点去掉并返回小数位数，true表示是乘法，返回双倍数量
	for (size_t i = 0; i < temp1.size(); i++) {//字符转数字
		temp1[i] -= '0';
		temp2[i] -= '0';
	}
	reverse(temp1.begin(), temp1.end());//反转字符串
	reverse(temp2.begin(), temp2.end());
	for (size_t i = 0; i < temp1.size(); i++) {
		for (size_t j = 0; j < temp2.size(); j++) {
			tempEb.push_back(temp1[i] * temp2[j]);
		}
		for (size_t p = 0; p < temp2.size(); p++) {
			bits.push_back(tempEb[p] % 10);
			bits[bits.size() - 1] += '0';
			earry.push_back(tempEb[p] / 10);
			earry[earry.size() - 1] += '0';
		}
		reverse(bits.begin(), bits.end());
		reverse(earry.begin(), earry.end());
		earry += "0";
		string addPend(i, '0');
		tempAd = addition(&earry, &bits);
		tempAd += addPend;
		addList.push_back(tempAd);
		tempEb = "";
		earry = "";
		bits = "";
	}
	for (size_t i = 0; i < addList.size(); i++) {
		temp = addition(&(addList[i]), &temp);
	}
	temp = temp.substr(0, temp.size() - floatSize) + "." + temp.substr(temp.size() - floatSize, temp.size());
	temp = deInvalid(&temp);
	return temp;
}
string divStage(string* str1, string str2) {
	string temp1;
	string temp;
	for (size_t i = 1; i <= 10; i++) {
		temp1.push_back(i + '0');
		temp = multiplication(&temp1, &str2);
		temp1.pop_back();
		if (strCompare(&temp, str1) == 0) {
			*str1 = "0";
			temp1.push_back(i + '0');
			return temp1;
		}
		else if (strCompare(&temp, str1) == 1) {
			temp1.push_back((i - 1) + '0');
			temp = multiplication(&temp1, &str2);
			*str1 = subtraction(str1, &temp);
			return temp1;
		}
	}
	return "error";//正常情况下不会击中，除非输入错误字符
}
string div(string* str1, string* str2, int se) {
	size_t floatSize = strCompletion(str1, str2, true);
	*str1 = deInvalid(str1);
	*str2 = deInvalid(str2);
	string divMain = *str1;
	string divSun;
	string temp;
	size_t i = 0;
	string comp("00");
	divSun.push_back(divMain[i]);
	while (1) {
		i++;
		if (strCompare(&divSun, str2) >= 0) {
			temp += divStage(&divSun, *str2);
		}
		if (i < divMain.size()) {
			divSun.push_back(divMain[i]);
			if (strCompare(&divSun, str2) >= 0) {
				temp += divStage(&divSun, *str2);
			}
			else {
				temp.push_back('0');
				continue;
			}
		}
		else if (divSun == "0" || divSun == "00") {
			return temp;
		}
		else {
			temp.push_back('.');
			int c = se;
			while (c--) {
				divSun.push_back('0');
				if (strCompare(&divSun, str2) == -1) {
					temp.push_back('0');
					divSun.push_back('0');
				}
				if (strCompare(&divSun, str2) >= 0) {
					temp += divStage(&divSun, *str2);
				}
			}
			temp = deInvalid(&temp);
			return temp;
		}
	}
	return "";
}
string comp(string* str1, string* str2, string str3) {
	string* temp1;
	string* temp2;
	bool tf = false;
	if (strCompare(str1, str2) == -1) {
		temp1 = str2;
		temp2 = str1;
		tf = true;
	}
	else {
		temp1 = str1;
		temp2 = str2;
	}
	if (str3 == "+") {
		return addition(temp1, temp2);
	}
	else {
		string temp = subtraction(temp1, temp2);
		if (tf) {
			temp = "-" + temp;
			return temp;
		}
		else {
			return temp;
		}
	}
}
int main(void) {
	//求平均值
	int se = 20;
	vector<string> mathList;
	string e1("0.3");
	string e2("0");
	string e3("0");
	string str1; 
	while (1) {
		while (1) {
			cout << "请输入数字列表" << endl;
			cin >> str1;
			strScene(str1, &mathList);
			if (str1 == "exit") {
				return 0;
			}
			if (str1 == "set") {
				system("cls");
				cout << "请输入除法位数";
				int d = 0;
				cin >> d;
				se = d;
				continue;
			}
			if (str1.size() > 0) {
				if (str1[0] != '[') {
					continue;
				}
			}
			string _1("1");
			for (int i = 0; i < mathList.size(); i++) {
				e3 = addition(&e3, &(mathList[i]));
				e2 = addition(&e2, &_1);
			}
			for (int i = 0; i < mathList.size(); i++) {
				cout << mathList[i];
				cout << " ";

			}
			cout << "\n";
			string p;
			p = div(&e3, &e2, se);
			if (p.size() > 1) {
				for (; p[0] == '0' && p[1] == '0';) {
					p = p.substr(1, p.size());
				}
			}
			cout << "ps::  " << endl;
			cout << p;
			cout << "\n";
			mathList.clear();
			e1 = "0";
			e3 = "0";
			e2 = "0";
			cout << "\n";
			str1 = "";
		}
	}
	//while (1) {
	//	cout << "请输入第一个数" << endl;
	//	cin >> e1;
	//	cout << "请输入第二个数" << endl;
	//	cin >> e2;
	//	cout << "请输入运算符" << endl;
	//	cin >> e3;
	//	if (e3 == "+") {
	//		cout << addition(&e1, &e2) << endl;
	//	}
	//	else if (e3 == "-") {
	//		cout << comp(&e1, &e2, e3) << endl;
	//	}
	//	else if (e3 == "*") {
	//		cout << multiplication(&e1, &e2) << endl;
	//	}
	//	else {
	//		cout << div(&e1, &e2) << endl;
	//	}
	//	system("pause");
	//	system("cls");
	//}
	return 0;
}