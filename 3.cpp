#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Node 
{
public:
    string title;
    vector<Node> children;

    Node(string t) : title(t) {}

    void addChild(Node child) 
    {
        children.push_back(child);
    }

    void display(int level = 0) const 
    {
        cout << string(level * 2, ' ') << title << endl;
        for (const auto& child : children)
            child.display(level + 1);
    }
};

int main() 
{
    string bookName;
    cout << "Enter book name: ";
    getline(cin, bookName);
    Node book("Book: " + bookName);

    int numChapters;
    cout << "Enter number of chapters: ";
    cin >> numChapters;
    cin.ignore();

    for (int i = 0; i < numChapters; i++) 
    {
        string chTitle;
        cout << "  Enter title for chapter " << i + 1 << " : ";
        getline(cin, chTitle);
        Node chapter("Chapter: " + chTitle);

        int numSections;
        cout << "  Enter number of sections in " << chTitle << " : ";
        cin >> numSections;
        cin.ignore();

        for (int j = 0; j < numSections; j++) 
        {
            string secTitle;
            cout << "    Enter title for section " << j + 1 << " : ";
            getline(cin, secTitle);
            Node section("Section: " + secTitle);

            int numSubsections;
            cout << "    Enter number of subsections in " << secTitle << " : ";
            cin >> numSubsections;
            cin.ignore();

            for (int k = 0; k < numSubsections; k++) 
            {
                string subTitle;
                cout << "      Enter title for subsection " << k + 1 << " : ";
                getline(cin, subTitle);
                section.addChild(Node("Subsection: " + subTitle));
            }
            chapter.addChild(section);
        }
        book.addChild(chapter);
    }

    cout << "\nBook Structure:\n";
    book.display();

    return 0;
}