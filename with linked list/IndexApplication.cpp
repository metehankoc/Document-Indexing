// Metehan KOC

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <chrono>

using namespace std;

class FileNameNode {
public:
	string fileName;
	FileNameNode *next;
	FileNameNode(const string fname) :fileName(fname), next(NULL) {}
};

class WordTypeNode {
public:
	string word;
	int wordFreq;
	FileNameNode *fileListHead, *FileListLast;
	WordTypeNode *next;
	WordTypeNode(const string w) :word(w), next(NULL) {}
};

class IndexLinkedList {
private:
	WordTypeNode *head, *last;
public:
	IndexLinkedList() :head(NULL) , last(NULL){}
	void addWord(const string &word, const string &fileName) {
		WordTypeNode* walk = head;
		while (walk != NULL) {
			if (walk->word == word) {
				if (walk->FileListLast->fileName == fileName) {
					walk->wordFreq += 1;
					return;
				}

				FileNameNode* newNode = new FileNameNode(fileName);
				walk->FileListLast->next = newNode;
				walk->FileListLast = walk->FileListLast->next;
				walk->wordFreq += 1;
				return;
			}
			walk = walk->next;
		}
		WordTypeNode* node = new WordTypeNode(word);
		FileNameNode* newNode = new FileNameNode(fileName);
		if (head == NULL) {
			head = last = node;
			head->fileListHead = head->FileListLast = newNode;
			head->wordFreq = 1;
		}
		else {
			last->next = node;
			last = last->next;
			node->fileListHead = node->FileListLast = newNode;
			node->wordFreq = 1;
		}
	}
	
	bool printListOfFiles(const string &singleWordQuery)const {
		WordTypeNode* walk = head;
		while (walk != NULL) {
			if (walk->word == singleWordQuery) {
				FileNameNode* curr=walk->fileListHead;
				cout << "File Names: ";
				while (curr != NULL) {
					cout << curr->fileName << ",  ";
					curr = curr->next;
				}
				cout << endl << endl;
				return true;
			}
			walk = walk->next;
		}
		return false;
	}
	
	void printMostFrequentWords(int topWhat) {
		int** a = new int* [2];
		WordTypeNode* walk = head;
		int count=1;
		cout << "The top " << topWhat << " words that appeared most frequently:" << endl;
		for (int i = 0; i < 2; i++){
			a[i] = new int[topWhat];
		}
		for (int j = 0; j < topWhat; j++){
			a[0][j] = 0;
			a[1][j] = 0;
		}
		while (walk != NULL) {
			for (int k = 0;k < topWhat;k++) {
				if (a[0][k] < walk->wordFreq || a[0][k] == walk->wordFreq) {
					for (int m = k+topWhat;m < topWhat - 1;m++) { 
						a[0][m + 1] = a[0][m];
						a[1][m + 1] = a[0][m];
					}
					a[0][k] = walk->wordFreq;
					a[1][k] = count;
					break;
				}
			}
			walk = walk->next;
			count++;
		}
		walk = head;
		count = 1;
		while (walk != NULL) {
			for (int n = 0;n < topWhat;n++) {
				if (count == a[1][n]) 
					cout << walk->word << ": " << walk->wordFreq <<" ,  ";
					
			}
			count++;
			walk = walk->next;
		}
	}
	
	void printLeastFrequentWords(int topWhat) {
		WordTypeNode* walk = head;
		int c = 0;
		cout << "The top " << topWhat << " words that appeared least frequently:" << endl;
		while (walk != NULL) {
			if (walk->wordFreq == 1) {
				cout << walk->word << ", ";
				c++;
			}
			if (c == topWhat)
				return;
			walk = walk->next;
		}
	}
	
	/*void toBack(int n) {
		WordTypeNode* walk = head, * prev = NULL;
		for (int i = 0;i < n * 2;i++) {
			if (walk->wordFreq == 1) {
				WordTypeNode* node;
				node = walk;
				prev->next = walk->next;
				node->next = NULL;
				last->next = node;
				last = node;
			}
			prev = walk;
			walk = walk->next;
		}
	}*/
	
	void print() {
		WordTypeNode* walk = head;
		while (walk != NULL) {
			FileNameNode* curr = walk->fileListHead;
			cout << walk->word << ":" << endl;
			while (curr != NULL) {
				cout << curr->fileName << ",  ";
				curr = curr->next;
			}
			walk = walk->next;
		}
	}
	
	void printCount() {
		WordTypeNode* walk = head;
		int count = 0;
		while (walk != NULL) {
			count++;
			walk = walk->next;
		}
		cout << "Word count: " << count << endl;
	}
	
	void printWordFreq() {
		WordTypeNode* walk = head;
		int count = 1;
		while (walk != NULL) {
			cout << count <<".  "<< walk->word << ": " << walk->wordFreq << endl;
			walk = walk->next;
			count++;
		}
	}
	
	void printTotalWord() {
		WordTypeNode* walk = head;
		int total = 0;
		while (walk != NULL) {
			total += walk->wordFreq;
			walk = walk->next;
		}
		cout << "Total word count: " << total << endl;
	}
};

/*bool isAlphabethic(char x)
{
	return (x >= 'a' && x <= 'z') ||
		(x >= 'A' && x <= 'Z');
}*/

void getValidOption(int &option) {
	do {
		cin >> option;
	} while (!(option < 5 && option>0));
}

int  printDecoratedMenu(const string &indexCreationDuration) {
	cout << setfill(' ') << setw(82) << "\n";
	cout << setfill('_') << setw(82) << "\n";
	cout << "|" << setfill(' ') << setw(56) << "Simple Document Retrieval System" << setw(24) << "|" << endl;
	cout << "|" << setw(36) << "(" << indexCreationDuration << "Minutes)" << setw(35) << "|" << endl;
	cout << setfill('_') << setw(82) << "\n";
	cout << "|" << setfill(' ') << setw(66) << "1.	Enter a single keyword to list the document(s)(file names)" << setw(7) << "|" << endl;
	cout << "|" << setw(60) << "2.	Print the top 10 words that appeared most frequently" << setw(13) << "|" << endl;
	cout << "|" << setw(61) << "3.	Print the top 10 words that appeared least frequently" << setw(12) << "|" << endl;
	cout << "|" << setw(12) << "4.	Exit" << setw(61) << "|" << endl;
	cout << setfill('_') << setw(82) << "\n";
	cout << "Option:";
	int option;
	getValidOption(option);
	return option;
}

void createIndex(IndexLinkedList &index, const string directoryOfFiles) {
	string all, line, word;
	for (int i = 1;i <= 10000;i++) {
		ifstream in(directoryOfFiles + "\\" + to_string(i) + ".txt");
		while (in >> all) {
			for (int j = 0;j < all.size();j++) {
				if (isalpha(all[j])) {
					word.push_back(tolower(all[j]));
				}
			}
			if (!word.empty()) {
				index.addWord(word, to_string(i) + ".txt");
				word.clear();
			}
		}
		in.close();
	}
	//index.print();
	//index.printCount();
	//index.printWordFreq();
	//index.printTotalWord();
}

void main() {
	string dirName = "AllDocs";
	IndexLinkedList index;
	string idxCreationTime;
	auto start = chrono::steady_clock::now();
	createIndex(index, dirName);
	auto end = chrono::steady_clock::now();
	idxCreationTime = to_string(chrono::duration_cast<chrono::minutes>(end - start).count());
	int opt;
	
	do {
		opt=printDecoratedMenu(idxCreationTime);
		switch(opt) {
		case 1: {
			string queryWord, temp;
			bool t;
			cout << "Enter a single keyword: ";
			cin >> temp;
			for (int i = 0;i < temp.size();i++) {
				queryWord.push_back(tolower(temp[i]));
			}
			t=index.printListOfFiles(queryWord);
			if (!t) {
				cout << "This word is not found." << endl << endl;
			}
			break;
		}
		case 2: index.printMostFrequentWords(10); break;
		case 3: index.printLeastFrequentWords(10); break;
		}
	} while (opt != 4);
	if (opt == 4)
		cout << "Bye!" << endl;
}
