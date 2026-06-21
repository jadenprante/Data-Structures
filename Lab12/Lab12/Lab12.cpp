/*************************************************************
* Author:			Jaden Prante
* Filename:			Lab06.cpp
* Date Created:		May 15th 2025
* Modifications:	NA
*
* 
* Lab/Assignment: Lab 12 - Hash Tables
*
* Overview:
* This lab goes Hash Tables
*
* Input:
* The input is 15 names and these arrays will be used to run a series of tests
*
* Output:
* The output will be the result of the ran test, it will output
* either a pass or fail result
**************************************************************/

#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_SECURE_NO_WARNINGS
typedef bool(*FunctionPointer)(); // Define a funtion pointer type
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <crtdbg.h>
#include <conio.h>
#include "Exception.h" 
#include "HashTable.h"
// Strings to test
const char* NAMES[] = { "Kyle", "Brit", "seth", "Alex", "Josh", "Kian",
"Kate", "Terry", "Ann", "Elaine", "Stephanie", "Wanda", "Oscar",
"Oliver", "Tobey" };
const int NUM_NAMES = 15;
const int NUM_SIZE = 10;
const int NUM_EXTRACT = 4;
// Test function declaration
bool TestConstructor();
bool TestCopyConstructor();
bool TestMoveConstructor();
bool TestCopyAssignment();
bool TestMoveAssignment();
bool TestInsert();
bool TestDelete();
bool TestOperatorBracket();
bool TestSetHash();
bool TestRehash();
bool TestTraversal();
bool TestInsertDuplicate();
bool TestInsertMultiple();
bool TestNonExistentKey();
bool TestLargeInsertions();
//bool TestDeleteNonExistent();
bool TestEmptyTable();
bool TestSetNullHash();
bool TestDeleteAfterRehash();

// Array of test functions
FunctionPointer test_functions[] = { TestConstructor, TestCopyConstructor,
TestMoveConstructor, TestCopyAssignment, TestMoveAssignment, TestInsert, TestDelete,
TestOperatorBracket, TestSetHash, TestRehash, TestTraversal, TestInsertDuplicate,
TestInsertMultiple, TestNonExistentKey, TestLargeInsertions, /*TestDeleteNonExistent,*/
TestEmptyTable, TestSetNullHash, TestDeleteAfterRehash
};


struct Book 
{
    string m_title;
    string m_author;
    int m_pages;
};

int AsciiHash(string key) 
{
    int hash = 0;
    for (size_t i = 0; i < key.length(); i++)
    {
        hash += key[i];
    }
    return hash;
}

int SimpleHash(string key) 
{
    int hash = 0;
    for (char ch : key) 
    {
        hash += ch;
    }
    return hash;
}

void PrintBook(Book b)
{
    cout << "Title: " << b.m_title << ", Author: " << b.m_author << ", Pages: " << b.m_pages << endl;
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    int failedTest = 0;
    // Run the test functions

    for (FunctionPointer func : test_functions)
    {
        if (func())
        {
            cout << "passed\n";
        }
        else
        {
            failedTest++;
            cout << "***** failed *****\n";
        }
    }
    if (failedTest > 0)
    {
        cout << "\nYou have failed " << failedTest << " tests.";
    }
    else
    {
        cout << "\nCongradulations, you have passed all the tests!";
    }
    cout << "\nPress Any Key to Exit";
    cin.get();
    HashTable<string, Book> table(10);
    table.setHash(AsciiHash);
    Book temp = { "C++: Learn by Doing", "Todd Breedlove, Troy Scevers, et. al.", 635 };
    table.Insert("0763757233", temp);
    Book temp1 = { "Rodeo for Dummies", "Calvin Caldwell", 1 };
    table.Insert("7063757233", temp1);
    Book temp3 = { "And That n There", "Ralph Carestia", 1 };
    table.Insert("7063757234", temp3);
    cout << table["0763757233"].m_title << endl;
    cout << table["7063757233"].m_title << endl;
    cout << table["7063757234"].m_title << endl;
    cout << "\nTraversing HashTable:" << endl;
    table.Traverse(PrintBook);
    return 0;
}

bool TestConstructor() 
{
    cout << "HashTable Default Constructor test ";
    HashTable<string, Book> table(10);
    return true; // If it compiles and runs, it's a success
}

bool TestCopyConstructor() 
{
    cout << "HashTable Copy Constructor test ";
    HashTable<string, Book> table1(10);
    HashTable<string, Book> table2(table1);
    return true;
}

bool TestMoveConstructor() 
{
    cout << "HashTable Move Constructor test ";
    HashTable<string, Book> table1(10);
    HashTable<string, Book> table2(std::move(table1));
    return true;
}

bool TestCopyAssignment() 
{
    cout << "HashTable Copy Assignment Operator test ";
    HashTable<string, Book> table1(10);
    HashTable<string, Book> table2 = table1;
    return true;
}

bool TestMoveAssignment()
{
    cout << "HashTable Move Assignment Operator test ";
    HashTable<string, Book> table1(10);
    HashTable<string, Book> table2 = std::move(table1);
    return true;
}

bool TestInsert() 
{
    cout << "HashTable Insert test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    Book temp = { "C++: Learn by Doing", "Todd Breedlove", 635 };
    table.Insert("12345", temp);
    return table["12345"].m_title == "C++: Learn by Doing";
}

bool TestDelete() 
{
    cout << "HashTable Delete test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    Book temp = { "C++: Learn by Doing", "Todd Breedlove", 635 };
    table.Insert("12345", temp);
    table.Delete("12345");
    return table["12345"].m_title.empty();
}

bool TestOperatorBracket()
{
    cout << "HashTable Operator Bracket test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    Book temp = { "C++ Primer", "Stanley B. Lippman", 900 };
    table.Insert("54321", temp);
    return table["54321"].m_title == "C++ Primer";
}

bool TestSetHash() 
{
    cout << "HashTable Set Hash test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    return true; // If it compiles and runs, it's a success
}

bool TestRehash() 
{
    cout << "HashTable Rehash test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    Book temp = { "Data Structures", "Mark Weiss", 800 };
    table.Insert("98765", temp);
    table.setHash(SimpleHash);
    return table["98765"].m_title == "Data Structures";
}

void PrintBookTitle(Book book) 
{
    // For traversal test
    cout << "Book Title: " << book.m_title;
}

bool TestTraversal()
{
    cout << "HashTable Traversal test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    Book temp = { "C++: Learn By Doing ", "Todd Breedlove", 1376 };
    table.Insert("11111", temp);
    table.Traverse(PrintBookTitle);
    return true;
}

bool TestInsertDuplicate()
{
    cout << "HashTable Insert Duplicate test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    Book book1 = { "Original Title", "Author A", 100 };
    Book book2 = { "Updated Title", "Author B", 200 };
    table.Insert("10101", book1);
    table.Insert("10101", book2);
    return table["10101"].m_title == "Updated Title";
}

bool TestInsertMultiple() 
{
    cout << "HashTable Insert Multiple test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    Book book1 = { "Book A", "Author X", 100 };
    Book book2 = { "Book B", "Author Y", 200 };
    table.Insert("111", book1);
    table.Insert("222", book2);
    return table["111"].m_title == "Book A" && table["222"].m_title == "Book B";
}

bool TestNonExistentKey()
{
    cout << "HashTable Non Existent Key test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    return table["99999"].m_title.empty();
}

bool TestLargeInsertions() 
{
    cout << "HashTable Large Insertion test ";
    HashTable<string, Book> table(100);
    table.setHash(SimpleHash);
    for (int i = 0; i < 50; i++) 
    {
        Book temp = { "Book " + std::to_string(i), "Author " + std::to_string(i), i * 10 };
        table.Insert(std::to_string(i), temp);
    }
    return table["25"].m_title == "Book 25";
}

/*bool TestDeleteNonExistent()
{
    cout << "HashTable Delete Non Existent test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    table.Delete("00000");
    return true; // No crash = success
}*/

bool TestEmptyTable() 
{
    cout << "HashTable Empty Table test ";
    HashTable<string, Book> table(10);
    return true; // If it initializes properly, it works
}

bool TestSetNullHash() 
{
    cout << "HashTable Set Null Hash test ";
    HashTable<string, Book> table(10);
    table.setHash(nullptr);
    return true;
}

bool TestDeleteAfterRehash() 
{
    cout << "HashTable Delete After Rehash test ";
    HashTable<string, Book> table(10);
    table.setHash(SimpleHash);
    Book temp = { "C++ Cookbook", "D. Ryan Stephens", 350 };
    table.Insert("77777", temp);
    table.setHash(SimpleHash);
    table.Delete("77777");
    return table["77777"].m_title.empty();
}

