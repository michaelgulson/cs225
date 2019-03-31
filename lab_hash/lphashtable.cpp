/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"
#include <list>

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{
    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */

    /*schashtable insert
   double newLoadFactor;
    newLoadFactor = (elems + 1) / size;

    if(newLoadFactor >= .7){
        resizeTable();
    }

    unsigned hashIndex;
    std::pair<K,V> hashInsert = std::make_pair(key,value);

    hashIndex = hashes::hash(key, size);

    //you don't need to concern yourself with duplicate keys
    //if (keyExists(key)){           //No
    //    return; //key already exists in hashtable?
    //}

    //typename std::list<std::pair<K, V>>::iterator bucket_iterator;
    typename std::list<std::pair<K, V>>::iterator it = table[hashIndex].begin();

    //insert element into linked list
    table[hashIndex].insert(it, hashInsert);

    //increase elems private member
    elems++;

    */
    double newLoadFactor;
    newLoadFactor = (elems + 1) / size;

    if (newLoadFactor >= .7)
    {
        resizeTable();
    }

    unsigned hashIndex;
    //hashInsert = new
    std::pair<K, V> * hashInsert;
    //hashInsert = new std::pair<K, V>::make_pair(key, value);
    //hashInsert = new std::pair<K, V>::pair(key, value);
    hashInsert = new std::pair<K, V>(key, value);

    //find available space through linear probing Hash Table
    hashIndex = hashes::hash(key, size);

    //??? Is this how we should use should_probe?
    while(should_probe[hashIndex]){
        hashIndex++;
        hashIndex %= size;
    }

    //typename std::pair<K, V>>::iterator it;

    //insert element into linked list
    table[hashIndex] = hashInsert;

    //increase elems private member
    elems++;

    //(void) key;   // prevent warnings... When you implement this function, remove this line.
    //(void) value; // prevent warnings... When you implement this function, remove this line.
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */

    /*
    REMOVE FOR SCHASHTABLE
    for (size_t i = 0; i < size; i++)
    {
        typename std::list<std::pair<K, V>>::iterator it = table[i].begin();

        //??there's a compiler error on this line
        for (it = table[i].begin(); it != table[i].end(); it++)
        {
            if ((*(it)).first == key)
            {
                table[i].erase(it);
                return;
            }
        }
        //while (it != end()){ //
            //std::pair<K, V> &operator*
            
        //    it++;
        //}
    }
    elems--;
    */
    //for (size_t i = 0; i < size; i++)
    //{
        //typename std::list<std::pair<K, V>>::iterator it = table[i].begin();

        //??there's a compiler error on this line
        //for (it = table[i].begin(); it != table[i].end(); it++)
        //{
    /*    if(size==0){
            return;
        }
        for (int i=0; i< size; i+)
        {    
            if (table[i].first == key)
            {
                //???is this right?
                table[i].first = K();
                tabl
                return;
            }
        }
        //while (it != end()){ //
        //std::pair<K, V> &operator*

        //    it++;
        //}
    }
    elems--;
    */
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    for (size_t i = 0; i < size; i ++)
    {
        if (table[i]->first == key)
        {
            //???is this right?
            return i;
        }
    }

    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
    /*      //schashtable resizeTable()
  
    size_t newTableSizePrime;
    //table_size = tableSize();
    newTableSizePrime = findPrime(size * 2);
    //table->resize(newTableSizePrime);
    //CA says make a new table?
    std::list<std::pair<K, V>> *copyTable = new std::list<std::pair<K, V>>[size];

    copyTable = table;
    //mallocate() memory for table
    table = new std::list<std::pair<K, V>>[newTableSizePrime];

    //rehash key values
    unsigned hashIndex;

    //hashIndex = hashes::hash(key, size);

    for (size_t i = 0; i < size; i++)
    {
        typename std::list<std::pair<K, V>>::iterator it;
        //??there's a compiler error on this line
        for (it = table[i].begin(); it != table[i].end(); it++)
        {
            hashIndex = hashes::hash((*it).first, newTableSizePrime);
            table[hashIndex].insert(table[hashIndex].begin(), *it);
        }
    }

    //hash(key);
    //delete and replace old table
    delete[] copyTable;

    size = newTableSizePrime;
    //??? how does this look ^
    */

    size_t newTableSizePrime;
    //table_size = tableSize();
    newTableSizePrime = findPrime(size * 2);
    
    //create copy table
    std::pair<K, V> ** copyTable = new std::pair<K, V> *[size];

    copyTable = table;
    //mallocate() memory for table
    table = new std::pair<K, V> *[newTableSizePrime];

    //rehash key values
    unsigned hashIndex;

    for (size_t i = 0; i < size; i++)
    {
        hashIndex = hashes::hash((*copyTable[i]).first, newTableSizePrime);
        *table[hashIndex] = *copyTable[i];
    }

    delete[] copyTable;
    size = newTableSizePrime;
}
