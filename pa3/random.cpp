#include <iostream>
using namespace std;


bool containAnyWords(string src, string filterWords) {
    auto strToLower = [](string& str) {
        for (char& c: str) c = tolower(c);
    };
    strToLower(src);
    strToLower(filterWords);
    size_t found = filterWords.find(' ');
    while (found != string::npos) {
        if (src.find(filterWords.substr(0, found)) != string::npos)
            return true;
        filterWords = filterWords.substr(found+1);
        found = filterWords.find(' ');
    }
    return src.find(filterWords) != string::npos;
}

int main(){
    cout << containAnyWords("","") << endl;
    return 0;
}