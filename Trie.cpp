#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY names as parameter.
 */

typedef vector<string> S_vec;
typedef map<string, int> S_map;

// void process_error(const string, const int);
#define _R1(x) x.begin(), x.end()
#define _RR(x) x.rbegin(), x.rend()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define PRN(x) cout << x << endl

const int ALPHABET_SIZE = 26;

struct TNode { struct TNode *children[ALPHABET_SIZE]; bool isEndOfWord; int occurencies; };
struct TResult { size_t length; int occurencies; };


class MyTrie
{
public:
    MyTrie();
    ~MyTrie();
    void insert(const string&);
    TResult search(const string&);

private:
    TNode * makeNode();
    void deleteNode(TNode*);
    TNode* _root;
};

MyTrie::MyTrie()
{
    _root = makeNode();
}

MyTrie::~MyTrie()
{
    deleteNode(_root);
}

// make a new node
TNode* MyTrie::makeNode()
{
    TNode *pNode = new TNode();

    pNode->isEndOfWord = false;
    pNode->occurencies = -1;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// insert or mark last node as leaf
void MyTrie::insert(const string& key)
{
    TNode *pCrawl = _root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = makeNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf 
    if (!pCrawl->isEndOfWord)
    {
        pCrawl->isEndOfWord = true;
        pCrawl->occurencies = 1;
    }
    else
        pCrawl->occurencies += 1;

}

TResult MyTrie::search(const string& key)
{
    TResult answer{ 0, -1 };
    TNode *pCrawl = _root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]) return answer;

        answer.length++;
        pCrawl = pCrawl->children[index];
    }

    if (pCrawl->isEndOfWord)
        answer.occurencies = pCrawl->occurencies;

    return answer;
}

void MyTrie::deleteNode(TNode* top)
{
    if (top == NULL) return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        deleteNode(top->children[i]);

    delete top;
}


S_vec solve(S_vec names)
{
    MyTrie tt;
    S_vec answer;

    for (_R2(names))
    {

        TResult found = tt.search(*iter);

        if (found.occurencies == -1)
        {
            answer.push_back(iter->substr(0, found.length + 1));
        }
        else
        {
            string temp = *iter + " " + std::to_string(found.occurencies + 1);
            answer.push_back(temp);
        }

        tt.insert(*iter);
    }

    return answer;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string n_temp;
    getline(cin, n_temp);

    int n = stoi(ltrim(rtrim(n_temp)));

    vector<string> names(n);

    for (int i = 0; i < n; i++) {
        string names_item;
        getline(cin, names_item);

        names[i] = names_item;
    }

    vector<string> res = solve(names);

    for (int i = 0; i < res.size(); i++) {
        fout << res[i];

        if (i != res.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}
