//EECS 348 Lab 10
//Add strings by scratch, without an operator or converion
//Inputs: File of strings
//Outputs: Added strings
//Myself, ChatGPT
//Joey Ippolito, 3114450
// 4/18/2025
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

vector<string> readnumsfile(const string& filename) {   //function to read strings from file
    vector<string> lines;   //vector to hold strings
    ifstream file(filename);    //open file
    if (!file) {
        cerr << "Error opening file: " << filename << endl; //error message for file doesn't exist
        return lines; // Return empty vector on error
    }
    string line;    //string to hold each line
    while (getline(file, line)) {   //read each line
        lines.push_back(line);  //add line to vector
    }
    return lines;   //return vector of strings
}

bool isValidDouble(const string& str) { //function to check if string is a valid double
    if (str.empty()) return false;  //check if string is empty
    size_t i = 0, n = str.size();   //gets string size
    if (str[i] == '-' || str[i] == '+'){    //checks for sign of string
        i++;    //iterates to next character if sign is there
        if (i == n) return false;   //if sign is last character, return false
    }
    if (i >= n || !isdigit(str[i])) return false;   //if first character is not a digit, return false
    while (i < n && isdigit(str[i])) i++;   //iterates through string until a non-digit is found

    if (i < n && str[i] == '.'){    //checks for decimal point
        i++;    //iterates to next character
    if (i < n && !isdigit(str[i])) return false;    //if next character is not a digit, return false
    while (i < n && isdigit(str[i])) i++;   //iterates through string until a non-digit is found
    }   
    return i == n;  //returns true if all characters are digits or decimal point
}

//used chatgpt for this function
bool isGreater(string str1, string str2) {
    auto split = [&](string& strA, string& strB) {  //function to split strings into integer and decimal parts
        size_t da = strA.find('.'), db = strB.find('.');    //finds decimal point in string a and string b
        string Ai = (da == string::npos? strA : strA.substr(0, da));    //if no decimal point, set to string a or b
        string Bi = (db == string::npos? strB : strB.substr(0, db));    //if no decimal point, set to string a or b
        string Af = (da == string::npos? "" : strA.substr(da + 1));     //sets string a and b to the decimal part of the string
        string Bf = (db == string::npos? "" : strB.substr(db + 1));   //sets string a and b to the decimal part of the string
        size_t maxInt = max(Ai.size(), Bi.size());   //gets the max size of the integer part of the string
        Af.append(maxInt - Ai.size(), '0');   //appends zeros to the end of the string to make them the same size
        Bf.append(maxInt - Bi.size(), '0');  //appends zeros to the end of the string to make them the same size
        size_t ni = max(Af.size(), Bf.size());  //gets the max size of the decimal part of the string
        Ai = string(ni - Ai.size(), '0') + Ai;  //appends zeros to the front of the string to make them the same size
        Bi = string(ni - Bi.size(), '0') + Bi;  //appends zeros to the front of the string to make them the same size
        strA = Ai + "." + Af;   //sets string a to the integer and decimal part of the string
        strB = Bi + "." + Bf;   //sets string b to the integer and decimal part of the string
    };
    split(str1, str2);  
    return str1 >= str2;    //returns true if string a is greater than or equal to string b
}
//first part of the function follows the same format as the isGreater function. Splits the strings into integer and decimal parts, then adds them together.
string addPositive(string A, string B) {
    auto split = [&](string& strA, string& strB) {
        size_t da = strA.find('.'), db = strB.find('.');
        string Ai = (da == string::npos? strA : strA.substr(0, da));
        string Bi = (db == string::npos? strB : strB.substr(0, db));
        string Af = (da == string::npos? "" : strA.substr(da + 1));
        string Bf = (db == string::npos? "" : strB.substr(db + 1));
        size_t maxInt = max(Ai.size(), Bi.size());
        Af.append(maxInt - Ai.size(), '0');
        Bf.append(maxInt - Bi.size(), '0');
        size_t ni = max(Af.size(), Bf.size());
        Ai = string(ni - Ai.size(), '0') + Ai;
        Bi = string(ni - Bi.size(), '0') + Bi;
        strA = Ai + "." + Af;
        strB = Bi + "." + Bf;
    };
    split(A, B);
    int carry = 0;
    string result;  
    for (int i = A.size() - 1; i >= 0; --i) {   //iterates through the string backwards
        if (A[i] == '.') {  //if decimal point is found, add it to the result
            result += '.';  
            continue;
        }
        int sum = (A[i] - '0') + (B[i] - '0') + carry;  //adds digits
        carry = sum / 10;   //sets carry to 1 if sum is greater than 10
        result += (sum % 10) + '0'; //adds the sum to the result
    }
    reverse(result.begin(), result.end());  //reverses the string to get the correct order
    if (carry > 0) result.insert(result.begin(), carry + '0');  //if carry is greater than 0, add it to the front of the string
    return result;
}
//once again follows the same format as the isGreater function. Splits the strings into integer and decimal parts, then subtracts them.
string subtractPositive(string A, string B) {
    auto split = [&](string& strA, string& strB) {
        size_t da = strA.find('.'), db = strB.find('.');
        string Ai = (da == string::npos? strA : strA.substr(0, da));
        string Bi = (db == string::npos? strB : strB.substr(0, db));
        string Af = (da == string::npos? "" : strA.substr(da + 1));
        string Bf = (db == string::npos? "" : strB.substr(db + 1));
        size_t maxInt = max(Ai.size(), Bi.size());
        Af.append(maxInt - Ai.size(), '0');
        Bf.append(maxInt - Bi.size(), '0');
        size_t ni = max(Af.size(), Bf.size());
        Ai = string(ni - Ai.size(), '0') + Ai;
        Bi = string(ni - Bi.size(), '0') + Bi;
        strA = Ai + "." + Af;
        strB = Bi + "." + Bf;
    };
    split(A, B);
    int temp = 0; //temp variable to hold the carry
    string result;
    for (int i = A.size() - 1; i >= 0; --i) {   //iterates through the string backwards
        if (A[i] == '.') {  //if decimal point is found, add it to the result
            result += '.';
            continue;
        }
        int diff = (A[i] - '0') - (B[i] - '0') - temp;  //subtracts digits
        if (diff < 0) {     //checks if difference is negative
            diff += 10;     //if so, add 10 to the difference
            temp = 1;
        } else {
            temp = 0;
        }
        result += diff + '0';   //adds the difference to the result
    }
    reverse(result.begin(), result.end());  //reverses the string to get the correct order
    return result.erase(0, min(result.find_first_not_of('0'), result.size() - 1)); // Removes leading zeros
}

string addnums(const string& str1, const string& str2) {    //function to add strings
    bool neg1 = (str1[0] == '-');   //checks if string is negative
    bool neg2 = (str2[0] == '-');   //checks if string is negative
    string num1 = (neg1 || str1[0] == '+') ? str1.substr(1) : str1; //set to string a or b regardless of sign
    string num2 = (neg2 || str2[0] == '+') ? str2.substr(1) : str2; 
    string result;  //string to hold result
    bool negative = false;
    if (neg1 == neg2) { //if both strings are negative or positive
        result = addPositive(num1, num2);   //adds the strings together
        if (neg1) negative = true;  //if both strings are negative, set negative to true
    } else {
        if (num1 == num2) { //if both strings are equal, return 0
            return "0";
        } else if (isGreater(num1, num2)) { //if string a is greater than string b
            result = subtractPositive(num1, num2);  //subtracts the strings
            if (neg1) negative = true;  //if string a is negative, set negative to true
        } else {
            result = subtractPositive(num2, num1);  //subtracts the strings
            negative = neg2;    //if string b is negative, set negative to true
        }
    }
    return (negative ? "-" : "") + result;  //returns the result with the sign
}

int main() {
    cout << "Enter the name of the file: "; //recieves file from user
    string filename;
    cin >> filename;

    vector<string> lines = readnumsfile(filename);  //calls on readfile function to read file
    if (lines.empty()) {
        cout << "No valid numbers found in the file." << endl;  //error message
        return 1;
    }
    string constant = "-123.456";   //constant to add to the strings

    for (const string& line : lines) {
        if (isValidDouble(line)) {  //checks if string is a valid double
            string result = addnums(constant, line);    //calls on addnums function to add the strings together
            cout << "Result: " << constant << " + " << line << " = " << result << endl;
        } else {
            cout << "Invalid number: " << line << endl;
        }
    }
        
}
