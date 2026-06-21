/*************************************************
* Author:          Jaden Prante
* File Name:       HashTable.h
* Date Created:    May 15th 2025
* Modifications:   Currenrly same date
*
* Class: HashTabvle
*
* Purpose: This class creates a hash table
*          
*
* Manager Functions:
*       HashTable() - Default Constructor
*       HashTable(const HashTable& other) - Copy Constructor
*       HashTable(HashTable&& other) noexcept - Move Constructor
*       HashTable& operator=(const HashTable& other) - Copy Assignment Operator
*       HashTable& operator=(HashTable&& other) noexcept - Move Assignment Operator
*       ~HashTable() - Deconstructor
*
* Methods:
*       void Insert(K key, V value);
*	    void setHash(int (*hash)(K key)); 
*	    V operator [] (K key);
*	    void Delete(K key);
*	    void Traverse(void (*visit)(V value));
*       void Rehash(int (*hash)(K key));
*
**************************************************/

#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "Exception.h"

using std::vector;
using std::list;
using std::pair;
using std::string;
using std::cout;
using std::endl;

template <typename K, typename V>
class HashTable
{
public:
	HashTable();
    HashTable(size_t size = 10);
	HashTable(const HashTable& other);
	HashTable(HashTable&& other) noexcept;
	HashTable& operator= (const HashTable& other);
	HashTable& operator= (HashTable&& other) noexcept;
	~HashTable();
    void SetBuckets(size_t size);     // replaces constructor with size
	void Insert(K key, V value);
	void setHash(int (*hash)(K key)); // store the function ptr in data member
	V operator [] (K key);
	void Delete(K key);
	void Traverse(void (*visit)(V value));
private:
    vector<list<pair<K, V>>> m_table;
    int (*m_hashFunc)(K key);
    size_t m_size;
    void Rehash(int (*hash)(K key));
};

// Constructor
/*************************************************
* Purpose: is construtor for hash table
*
* Precondtions: NA
*
* Postconditions: NA
*
**************************************************/
template<typename K, typename V>
inline HashTable<K, V>::HashTable()
{}

// Constructor with paramethers
/*************************************************
* Purpose: is construtor for hash table
*
* Precondtions: NA
*
* Postconditions: m_table is resized
*
**************************************************/
template<typename K, typename V>
inline HashTable<K, V>::HashTable(size_t size) : m_size(size), m_hashFunc(nullptr) 
{
    m_table.resize(size);
}

// Copy Constructor
/*************************************************
* Purpose: copies data
*
* Precondtions: hash data
*
* Postconditions: data is copied
*
**************************************************/
template<typename K, typename V>
inline HashTable<K, V>::HashTable(const HashTable& other) 
{
    m_size = other.m_size;
    m_hashFunc = other.m_hashFunc;
    m_table = other.m_table;
}

// Move Constructor
/*************************************************
* Purpose: moves data
*
* Precondtions: hash data 
*
* Postconditions: data is moved
*
**************************************************/
template<typename K, typename V>
inline HashTable<K, V>::HashTable(HashTable&& other) noexcept 
{
    m_size = other.m_size;
    m_hashFunc = other.m_hashFunc;
    m_table = std::move(other.m_table);
    other.m_hashFunc = nullptr;
    other.m_size = 0;
}

// Copy Assignment Operator
/*************************************************
* Purpose: makes a deep copy of hash data
*
* Precondtions: hash data
*
* Postconditions: hash data is deep copied
*
**************************************************/
template<typename K, typename V>
inline HashTable<K, V>& HashTable<K, V>::operator=(const HashTable& other) 
{
    if (this != &other)
    {
        m_size = other.m_size;
        m_hashFunc = other.m_hashFunc;
        m_table = other.m_table;
    }
    return *this;
}

// Move Assignment Operator
/*************************************************
* Purpose: makes deep copy of move data 
*
* Precondtions: hash data
*
* Postconditions: hash data is deep moved on right 
*                 hand side
*
**************************************************/
template<typename K, typename V>
inline HashTable<K, V>& HashTable<K, V>::operator=(HashTable&& other) noexcept 
{
    if (this != &other) 
    {
        m_size = other.m_size;
        m_hashFunc = other.m_hashFunc;
        m_table = std::move(other.m_table);
        other.m_hashFunc = nullptr;
        other.m_size = 0;
    }
    return *this;
}

// Destructor
/*************************************************
* Purpose: destroys hash data
*
* Precondtions: hash data
*
* Postconditions: data is deleted
*
**************************************************/
template<typename K, typename V>
inline HashTable<K, V>::~HashTable()
{
    m_table.clear();
}

template<typename K, typename V>
inline void HashTable<K, V>::SetBuckets(size_t size)
{
    m_size = size;
}

// Insert Function
/*************************************************
* Purpose: inserts data into hash table
*
* Precondtions: hash data
*
* Postconditions: data is inserted
*
**************************************************/
template<typename K, typename V>
inline void HashTable<K, V>::Insert(K key, V value)
{
    if (m_hashFunc == nullptr)
    {
        throw Exception("Error: Hash function not set!"); 
    }
    int index = m_hashFunc(key) % m_size;
    list<pair<K, V>>& bucket = m_table[index];
    typename list<pair<K, V>>::iterator it;
    for (it = bucket.begin(); it != bucket.end(); it++) 
    {
        if (it->first == key) 
        {
            it->second = value; // Update existing key
        }
    }
    bucket.push_back(pair<K, V>(key, value));
}

// Set Hash Function
/*************************************************
* Purpose: sets hash function data
*
* Precondtions: hash data
*
* Postconditions: hash data is set
*
**************************************************/
template<typename K, typename V>
inline void HashTable<K, V>::setHash(int (*hash)(K key))
{

    if (m_table.empty() != true)
    {
        vector<list<pair<K, V>>> newTable(m_size);
        typename vector<list<pair<K, V>>>::iterator i;
        for (i = m_table.begin(); i != m_table.end(); i++)
        {
            typename list<pair<K, V>>::iterator it;
            list<pair<K, V>> bucket(*i);
            for (it = bucket.begin(); it != bucket.end(); it++)
            {
                pair<K, V> tempPair(*it);
                int index = hash(tempPair.first) % m_size;
                newTable[index].push_back(tempPair);
            }
        }
        m_table = newTable;
    }
    m_hashFunc = hash;
}

// Retrieve Value using Operator[]
/*************************************************
* Purpose: gets data with subscript operator
*
* Precondtions: hash data
*
* Postconditions: gets value
*
**************************************************/
template<typename K, typename V>
inline V HashTable<K, V>::operator[](K key)
{
    V value = V();
    if (m_hashFunc == nullptr)
    {
        throw Exception("Error: Hash function not set!"); 
    }
    int index = m_hashFunc(key) % m_size;
    list<pair<K, V>>& bucket = m_table[index];
    typename list<pair<K, V>>::iterator it;
    for (it = bucket.begin(); it != bucket.end(); it++) 
    {
        if (it->first == key)
        {
            value = it->second;
        }
    }
    return value;
}

// Delete Function
/*************************************************
* Purpose: deletes hash table data
*
* Precondtions: hash data
*
* Postconditions: hash data is deletes
*
**************************************************/
template<typename K, typename V>
void HashTable<K, V>::Delete(K key) 
{
    if (m_hashFunc == nullptr) 
    {
        throw Exception("Hash function not set.");
    }
    int index = m_hashFunc(key) % m_size;
    list<pair<K, V>>& bucket = m_table[index];
    bool deleted = false;
    typename list<pair<K, V>>::iterator it = bucket.begin();
    typename list<pair<K, V>>::iterator end = bucket.end();
    while (it != end) 
    {
        if (it->first == key) 
        {
            bucket.erase(it);
            deleted = true;
            it = end; // force loop exit
        }
        else 
        {
            ++it;
        }
    }
    if (!deleted) 
        throw Exception("Key not found for deletion.");
}


// Traverse Function
/*************************************************
* Purpose: traverses through hash table
*
* Precondtions: hash data
*
* Postconditions: gets hash table data
*
**************************************************/
template<typename K, typename V>
inline void HashTable<K, V>::Traverse(void (*visit)(V value)) 
{
    if (visit == nullptr) 
    {
        throw Exception("Traversal function is null.");
    }
    bool isEmpty = true;
    for (size_t i = 0; i < m_size; ++i) 
    {
        list<pair<K, V>>& bucket = m_table[i];
        for (typename list<pair<K, V>>::iterator it = bucket.begin(); it != bucket.end(); ++it)
        {
            visit(it->second);
            isEmpty = false;
        }
    }
    if (isEmpty)
    {
        throw Exception("Hash table is empty.");
    }
}

// Rehashing Function
/*************************************************
* Purpose: Rehashes data in hash table
*
* Precondtions: hash data
*
* Postconditions: data is rehashed
*
**************************************************/
template<typename K, typename V>
void HashTable<K, V>::Rehash(int (*hash)(K key)) 
{
    vector<list<pair<K, V>>> newTable(m_size);
    for (size_t i = 0; i < m_size; ++i) 
    {
        list<pair<K, V>>& bucket = m_table[i];
        for (typename list<pair<K, V>>::iterator it = bucket.begin(); it != bucket.end(); ++it) 
        {
            int newIndex = hash(it->first) % m_size;
            newTable[newIndex].push_back(*it);
        }
    }
    m_table = std::move(newTable);
    m_hashFunc = hash;
}
