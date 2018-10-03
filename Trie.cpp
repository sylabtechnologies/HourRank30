// https://www.hackerrank.com/contests/hourrank-30/challenges/video-conference
// - quickly combine trie and map

#include <bits/stdc++.h>

using namespace std;

typedef vector<string> S_vec;
typedef map<string, int> S_map;

#define _R1(x) x.begin(), x.end()
#define _RR(x) x.rbegin(), x.rend()
#define _R2(x) auto iter = x.begin(); iter != x.end(); ++iter
#define PRN(x) cout << x << endl

string ltrim(const string &);
string rtrim(const string &);

const int ALPHABET_SIZE = 26;

struct TNode { struct TNode *children[ALPHABET_SIZE]; bool isEndOfWord; };

class MyTrie
{
public:
    MyTrie();
    ~MyTrie();
    TNode *getNode();
    void insert(const string&);
    size_t search(const string&);

private:
    void _delete(TNode*);
    TNode* _root;
};

MyTrie::MyTrie()
{
    _root = getNode();
}

MyTrie::~MyTrie()
{
    _delete(_root);
}

// make a new node
TNode* MyTrie::getNode()
{
    TNode *pNode = new TNode();

    pNode->isEndOfWord = false;

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
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf 
    pCrawl->isEndOfWord = true;
}

size_t MyTrie::search(const string& key)
{
    size_t answer = 0;
    TNode *pCrawl = _root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index]) break;

        answer++;
        pCrawl = pCrawl->children[index];
    }

    return answer;
    // return (pCrawl != NULL && pCrawl->isEndOfWord);
}

void MyTrie::_delete(TNode* top)
{
    if (top == NULL) return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        _delete(top->children[i]);
    
    delete top;
}


S_vec solve(S_vec names)
{
    MyTrie tt;
    S_map fullMap;
    S_vec answer;

    for (_R2(names))
    {
        auto mapIter = fullMap.find(*iter);

        // count all occurencies
        if (mapIter == fullMap.end())
        {
            fullMap[*iter] = 1;
        }
        else
        {
            fullMap[*iter] += 1;

            stringstream ss;
            ss << *iter << " " << fullMap[*iter];
            answer.push_back(ss.str());
            continue;
        }

        size_t keysFound = tt.search(*iter);

        answer.push_back(iter->substr(0, keysFound + 1));
                             
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
