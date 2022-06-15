//  Metehan KOC

#include <iostream>
#include <string>
#include <iomanip>
#include <chrono>
#include <fstream> 

using namespace std;

class FileNameNode {
public:
	string fileName;
	FileNameNode* next;
	FileNameNode(const string fname) :fileName(fname), next(NULL) {}
};

class WordTypeBinaryTreeNode {
public:
	string word;
	int wordFreq;
	FileNameNode* fileListHead, * fileListLast;
	WordTypeBinaryTreeNode* left;
	WordTypeBinaryTreeNode* right;
	WordTypeBinaryTreeNode() :left(NULL), right(NULL), wordFreq(0), fileListHead(NULL), fileListLast(NULL) {}
	WordTypeBinaryTreeNode(string wrd) : word(wrd) ,left(NULL), right(NULL), wordFreq(1), fileListHead(NULL), fileListLast(NULL) {}
};

class IndexBinaryTreeList {
private:
	WordTypeBinaryTreeNode* root;
	string* maxWord, * minWord;
	int* max, * min;
public:
	IndexBinaryTreeList() :root(NULL), maxWord(NULL), minWord(NULL), max(NULL), min(NULL) {}
	bool addWord(WordTypeBinaryTreeNode* wRoot, const string& word, const string& fileName) {
		if (wRoot == NULL) {
			WordTypeBinaryTreeNode* tnode= new WordTypeBinaryTreeNode(word);
			root = tnode;
			FileNameNode* node = new FileNameNode(fileName);
			root->fileListHead = node;
			root->fileListLast = node;
			return true;
		}
		if (word < wRoot->word && wRoot->left == NULL) {
			WordTypeBinaryTreeNode* tnode = new WordTypeBinaryTreeNode(word);
			wRoot->left = tnode;
			FileNameNode* node = new FileNameNode(fileName);
			tnode->fileListHead = node;
			tnode->fileListLast = node;
			return true;
		}
		if (word > wRoot->word && wRoot->right == NULL) {
			WordTypeBinaryTreeNode* tnode = new WordTypeBinaryTreeNode(word);
			wRoot->right = tnode;
			FileNameNode* node = new FileNameNode(fileName);
			tnode->fileListHead = node;
			tnode->fileListLast = node;
			return true;
		}
		if (word < wRoot->word) 
			return addWord(wRoot->left, word, fileName);

		if (word > wRoot->word) 
			return addWord(wRoot->right, word, fileName);

		if (word == wRoot->word) {
			if (wRoot->fileListLast->fileName == fileName) {
				wRoot->wordFreq += 1;
				return true;
			}
			else {
				FileNameNode* newNode = new FileNameNode(fileName);
				wRoot->fileListLast->next = newNode;
				wRoot->fileListLast = wRoot->fileListLast->next;
				wRoot->wordFreq += 1;
				return true;
			}
		}
	}

	bool printListOfFiles(WordTypeBinaryTreeNode* wRoot, const string& singleWordQuery)const {
		if (wRoot == NULL)
			return false;
		if (wRoot->word == singleWordQuery) {
			FileNameNode* walk = wRoot->fileListHead;
			cout << "List of File Names:" << endl;
			while (walk != NULL) {
				cout << walk->fileName << ",  ";
				walk = walk->next;
			}
			cout << endl;
			return true;
		}
		if (wRoot->word < singleWordQuery)
			return printListOfFiles(wRoot->right, singleWordQuery);
		else
			return printListOfFiles(wRoot->left, singleWordQuery);
	}

	void printMostFrequentWords(int topWhat) {
		max = new int[topWhat];
		maxWord = new string[topWhat];
		findMax(root, topWhat);
		cout << "The top " << topWhat << " words that appeared most frequently:" << endl;
		for (int i = 0;i < topWhat;i++) {
			cout << maxWord[i] << ": " << max[i] << " ,   ";
		}
	}

	void printLeastFrequentWords(int topWhat) {
		WordTypeBinaryTreeNode* walk=root;
		minWord = new string[topWhat];	
		findLeast(walk, topWhat - 1);
		cout << "The top " << topWhat << " words that appeared least frequently:" << endl;
		for (int i = 0;i < topWhat;i++) {
			cout << minWord[i] << ",  ";
		}
	}

	WordTypeBinaryTreeNode* getRoot() { return(root); }
	/*
	void printPreorder(WordTypeBinaryTreeNode* wRoot)
	{
		if (wRoot == NULL)
			return;
		cout << wRoot->word << ",  ";
		printPreorder(wRoot->left);
		printPreorder(wRoot->right);
	}
	*/
	void findLeast(WordTypeBinaryTreeNode* wRoot, int top) {
		static int i = 0;
		if (wRoot == NULL || i == top + 1)
			return;
		if (wRoot->wordFreq == 1) {
			minWord[i] = wRoot->word;
			i++;
			findLeast(wRoot->left, top);
			findLeast(wRoot->right, top);
		}
		else {
			findLeast(wRoot->left, top);
			findLeast(wRoot->right, top);
		}
	}

	void findMax(WordTypeBinaryTreeNode* wRoot, int top) {
		if (wRoot == NULL)
			return;
		if (max[top - 1] < wRoot->wordFreq) {
			for (int k = 0;k < top;k++) {
				if (max[k] < wRoot->wordFreq || max[k] == wRoot->wordFreq) {
					for (int m = top - 1;k < m;m--) {
						max[m] = max[m - 1];
						maxWord[m] = maxWord[m - 1];
					}
					max[k] = wRoot->wordFreq;
					maxWord[k] = wRoot->word;
					break;
				}
			}
		}
		findMax(wRoot->left, top);
		findMax(wRoot->right, top);
	}

};

void getValidOption(int& option) {
	do {
		cin >> option;
	} while (option > 5 && option < 0);
}

int  printDecoratedMenu(const string& indexCreationDuration) {
	cout << setfill(' ') << setw(82) << "\n";
	cout << setfill('_') << setw(82) << "\n";
	cout << "|" << setfill(' ') << setw(56) << "Simple Document Retrieval System" << setw(24) << "|" << endl;
	cout << "|" << setw(35) << "(" << indexCreationDuration << "Seconds)" << setw(35) << "|" << endl;
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

void createIndex(IndexBinaryTreeList& index, const string directoryOfFiles) {
	string all, line, word;
	for (int i = 1;i <= 9599;i++) {
		ifstream in(directoryOfFiles + "\\" + to_string(i) + ".txt");
		while (in >> all) {
			for (int j = 0;j < all.size();j++) {
				if (isalpha(all[j])) {
					word.push_back(tolower(all[j]));
				}
			}
			if (!word.empty()) {
				index.addWord(index.getRoot(),word, to_string(i) + ".txt");
				word.clear();
			}
		}
		in.close();
	}
	//index.printPreorder(index.getRoot());
	//index.printC();
}

void main() {
	string dirName = "allDocs";
	IndexBinaryTreeList index;
	string idxCreationTime;
	auto start = chrono::steady_clock::now();
	createIndex(index, dirName);
	auto end = chrono::steady_clock::now();
	idxCreationTime = to_string(chrono::duration_cast<chrono::seconds>(end - start).count());
	int opt;
	do {
		opt = printDecoratedMenu(idxCreationTime);
		switch (opt) {
		case 1: {
			string queryWord, temp;
			bool t;
			cout << "Enter a single keyword: ";
			cin >> temp;
			for (int i = 0;i < temp.size();i++) {
				queryWord.push_back(tolower(temp[i]));
			}
			t = index.printListOfFiles(index.getRoot(), queryWord);
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
