#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <iomanip>
using namespace std;
vector<string> tokenize(const string& text) {
    vector<string> words;
    stringstream ss(text);
    string rawWord;
    while (ss >> rawWord) {
        string cleanWord = "";
        for (size_t i = 0; i < rawWord.length(); i++) {
            if (isalnum(rawWord[i])) {cleanWord += tolower(rawWord[i]);}
        }
        if (!cleanWord.empty()) {words.push_back(cleanWord);}
    }
    return words;
}
int main() {
    cout << "Nhap so luong van ban: ";
    int N;
    if (!(cin >> N) || N <= 0) return 0;
    cin.ignore();
    vector<vector<string> > docs(N);
    set<string> vocabulary;
    for (int i = 0; i < N; i++) {
        cout << "Nhap van ban " << i + 1 << ": ";
        string line;
        getline(cin, line);
        docs[i] = tokenize(line);
        for (size_t j = 0; j < docs[i].size(); j++) {vocabulary.insert(docs[i][j]);}
    }
    if (vocabulary.empty()) {
        cout << "\nKhong co tu nao duoc tim thay!" << endl;
        return 0;
    }
    map<string, double> idf_map;
    for (set<string>::iterator it = vocabulary.begin(); it != vocabulary.end(); ++it) {
        string term = *it;
        int docCountWithTerm = 0;
        for (int i = 0; i < N; i++) {
            for (size_t j = 0; j < docs[i].size(); j++) {
                if (docs[i][j] == term) {
                    docCountWithTerm++;
                    break;
                }
            }
        }
        idf_map[term] = log10((double)N / docCountWithTerm);
    }
    cout << "\n================ KET QUA BANG TF-IDF ================\n";
    cout << fixed << setprecision(4);
    for (int i = 0; i < N; i++) {
        cout << "\n--- Van ban " << i + 1 << " ---" << endl;
        int totalWordsInDoc = docs[i].size();
        if (totalWordsInDoc == 0) {
            cout << "(Van ban rong)" << endl;
            continue;
        }
        map<string, int> termFrequency;
        for (size_t j = 0; j < docs[i].size(); j++) {
            termFrequency[docs[i][j]]++;
        }
        cout << left 
             << setw(15) << "Tu (Term)" 
             << setw(12) << "TF" 
             << setw(12) << "IDF" 
             << setw(12) << "TF-IDF" << endl;
        cout << string(51, '-') << endl;
        for (map<string, int>::iterator it = termFrequency.begin(); it != termFrequency.end(); ++it) {
            string term = it->first;
            int count = it->second;
            double tf = (double)count / totalWordsInDoc;
            double idf = idf_map[term];
            double tfidf = tf * idf;
            cout << left 
                 << setw(15) << term 
                 << setw(12) << tf 
                 << setw(12) << idf 
                 << setw(12) << tfidf << endl;
        }
    }
    return 0;
}
