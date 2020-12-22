#include <iostream>
#include <fstream>
#include <ctime>
#include <windows.h>
#include <vector>
#include <map>
#include <algorithm>

//конвертирование словаря которого я нашел по популярности
//обязательный критерий работы данного дерева - слова, упорядоченные
//по популярности/частотности, иначе подсказки могут быть кривые
//например, вводишь "прив", а он предлагает "приведение" или "привозной"
void convertDict()
{
    std::ifstream fin("dict.txt");
    std::map<double, std::string> newDict;
    while (true)
    {
        int id;
        std::string word1, word2, partOfSpeech;
        double freq;
        fin >> id >> word1 >> word2 >> partOfSpeech >> freq;
        if (fin.eof())
            break;

        newDict.insert({freq, word1});
    }
    std::ofstream fout("dict_new.txt");
    for (auto i = newDict.rbegin(); i != newDict.rend(); ++i)
        fout << i->second << std::endl;
}

class Trie
{
private:

    struct Node
    {
        char value;
        std::vector<Node*> children;

        Node()
        {
            this->value = 0;
        }

        Node(char value)
        {
            this->value = value;
        }

        virtual ~Node()
        {
            for (size_t i = 0; i < children.size(); ++i)
                delete children[i];
        }
    } *root = nullptr;

    void _insert(const std::string &word, Node *node, size_t index = 0)
    {
        if (index == word.length())
        {
            node->children.push_back(nullptr);
            return;
        }

        auto f = std::find_if(node->children.begin(), node->children.end(), [&](Node *a){if (a != nullptr) return a->value == word[index]; return false;});

        if (f == node->children.end())
        {
            node->children.push_back(new Node(word[index]));
            f = node->children.end() - 1;
        }

        _insert(word, *f, index + 1);
    }

    void _recommendWord(const std::string &word, Node *node, std::string &rec, size_t index = 0)
    {
        //выход на случай, если не получилось найти нужную букву
        if (node == nullptr)
        {
            rec = word;
            return;
        }

        if (index >= word.length())
        {
            auto f = std::find(node->children.begin(), node->children.end(), nullptr);
            if (f == node->children.end())
            {
                rec += node->children[0]->value;
                _recommendWord(word, node->children[0], rec, index + 1);
            }
            return;
        }

        auto f = std::find_if(node->children.begin(), node->children.end(), [&](Node *a){if (a != nullptr) return a->value == word[index]; return false;});

        if (f != node->children.end())
        {
            rec += word[index];
            _recommendWord(word, *f, rec, index + 1);
            return;
        }

        //INSERT CODE HERE
        //обработка случая, когда буква не найдена здесь
        //
        //то есть перебираем еще и буквы, которые
        //теоретически могут быть на ее месте
        //допустим находятся рядом на клавиатуре
        //или же просто грамматическая ошибка

        //не получилось найти нужную букву
        rec += word[index];
        _recommendWord(word, nullptr, rec, index + 1);
    }

public:

    Trie()
    {
        root = new Node;
    }
    virtual ~Trie()
    {
        delete root;
    }

    void insert(const std::string &word)
    {
        this->_insert(word, this->root);
    }

    std::string recommendWord(const std::string &word)
    {
        std::string rec;
        this->_recommendWord(word, this->root, rec);
        return rec;
    }
};

int main()
{
    std::srand(std::time(0));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    std::ifstream fin("dict.txt");
    std::string word;

    Trie trie;

    while (std::getline(fin, word))
        if (word != "")
            trie.insert(word);

    fin.close();
    std::cout << "Dictionary created" << std::endl;

    while (true)
    {
        std::cin >> word;
        std::cout << trie.recommendWord(word) << std::endl << std::endl;
    }
    return 0;
}
