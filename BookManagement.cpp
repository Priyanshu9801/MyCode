#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class book
{
    int bookid;
    char title[20];
    float price;

public:
    book()
    {
        bookid = 0;
        strcpy(title, "no title");
        price = 0;
    }
    void getBookData()
    {
        cout << "Enter bookid,title and price ";
        cin >> bookid;
        cin.ignore();
        cin.getline(title, 20);
        cin >> price;
    }
    void showBookData()
    {
        cout << "\nBookid:" << bookid << "          Title:" << title << "            Price:" << price;
    }
    int storeBook();
    void viewAllBooks();
    void searchBook(const char *);
    void deleteBook(const char *);
    void updateBook(const char *);
};

int book::storeBook()
{
    if (bookid == 0 && price == 0)
    {
        cout << "\nBook data not initialised ";
        return 0;
    }
    else
    {
        ofstream fout;
        fout.open("myfile.dat", ios::app | ios::binary);
        fout.write((char *)this, sizeof(*this));
        fout.close();
        return 1;
    }
}

void book::viewAllBooks()
{
    ifstream fin;
    fin.open("myfile.dat", ios::in | ios::binary);
    if (!fin)
        cout << "\nFile not found\n";
    else
    {
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            showBookData();
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
    }
}

void book::searchBook(const char *t)
{
    ifstream fin;
    fin.open("myfile.dat", ios::in | ios::binary);
    if (!fin)
        cout << "\nFile not found\n";
    else
    {
        int counter = 0;
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (!strcmp(t, title))
            {
                showBookData();
                counter++;
            }
            fin.read((char *)this, sizeof(*this));
        }
        if (counter == 0)
            cout << "\nRecord not found\n";
        fin.close();
    }
}

void book::deleteBook(const char *t)
{
    ifstream fin;
    ofstream fout;
    fin.open("myfile.dat", ios::in | ios::binary);

    if (!fin)
        cout << "\nFile not found\n";
    else
    {
        fout.open("tempfile.dat", ios::out | ios::binary);
        fin.read((char *)this, sizeof(*this));
        while (!fin.eof())
        {
            if (strcmp(t, title))
                fout.write((char *)this, sizeof(*this));
            fin.read((char *)this, sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("myfile.dat");
        rename("tempfile.dat", "myfile.dat");
    }
}

void book::updateBook(const char *t)
{
    fstream file;
    file.open("myfile.dat", ios::ate | ios::binary | ios::in | ios::out);
    file.seekg(0);
    file.read((char *)this, sizeof(*this));
    while (!file.eof())
    {
        if (!strcmp(t, title))
        {
            getBookData();
            file.seekp(file.tellg() - (streampos)sizeof(*this));
            file.write((char *)this, sizeof(*this));
        }
        file.read((char *)this, sizeof(*this));
    }
    file.close();
}

int menu()
{
    int choice;
    cout << "Book management";
    cout << "\n1.Insert Book Record";
    cout << "\n2.View All Book Records";
    cout << "\n3.Search Book Record";
    cout << "\n4.Delete Book Record";
    cout << "\n5.Update Book Record";
    cout << "\n6.Exit";
    cout << "\nEnter your choice\t";
    cin >> choice;
    return choice;
}

int main()
{
    book b;
    char title[20];
    while (1)
    {
        system("cls");
        switch (menu())
        {
        case 1:
            b.getBookData();
            b.storeBook();
            cout << "\nThe book has been inserted, press any key to continue";
            break;
        case 2:
            b.viewAllBooks();
            cout << "\npress any key to continue";
            break;
        case 3:
            cout << "\nEnter title of the book to search\t";
            cin.ignore();
            cin.getline(title, 19);
            b.searchBook(title);
            cout << "\npress any key to continue";
            break;
        case 4:
            cout << "\nEnter title of the book to delete\t";
            cin.ignore();
            cin.getline(title, 19);
            b.deleteBook(title);
            cout << "\nThe book has been deleted, press any key to continue";
            break;
        case 5:
            cout << "\nEnter title of the book to update\t";
            cin.ignore();
            cin.getline(title, 19);
            b.updateBook(title);
            cout << "\nThe book has been updated, press any key to continue";
            break;
        case 6:
            cout << "\nThanks for using our service";
            cout << "\nPress any key to exit";
            getch();
            exit(0);
        default:
            cout << "\nInvalid response";
        }
        getch();
    }
}
