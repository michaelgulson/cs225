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
    //double newLoadFactor;
    //newLoadFactor = (elems + 1) / size;
    elems++;
    if (shouldResize())
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
    hashIndex %=size;

    //??? Is this how we should use should_probe?
    for(size_t i=0; i<size; i++){
        if(!should_probe[hashIndex]){
            break;
        }
        hashIndex++;
        hashIndex %= size;
    }

    //typename std::pair<K, V>>::iterator it;

    //insert element into linked list
    table[hashIndex] = hashInsert;

    
    //change should probe value at hashIndex
    should_probe[hashIndex] = true;

    //(void) key;   // prevent warnings... When you implement this function, remove this line.
    //(void) value; // prevent warnings... When you implement this function, remove this line.
}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
    std::pair<K, V> *empty = new std::pair<K, V>(K(), V());

    for (size_t i = 0; i < size; i++)
    {
        if (should_probe[i] && table[i]!=NULL)
        {

            if (table[i]->first == key)
            {
               // table[i] = empty;
               delete table[i];
               table[i] = NULL;
                elems--;
                return;
            }
        }
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    
    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */

    //most efficient way to find key
    /*unsigned hashIndex;
    hashIndex = hashes::hash(key, size);

    for (size_t i = 0; i < size; i ++)
    {
        //segfaults here if table[i] is null
        if (should_probe[(hashIndex + i) % size])
        {
            if (table[(hashIndex+i)%size]->first == key)
            {
                //???is this right?
                return (hashIndex+i)%size;
            }
        }
    }
    */

    for (size_t i = 0; i < size; i++)
    {
        //segfaults here if table[i] is null
        if (should_probe[i] && table[i] != NULL)
        {
            if (table[i]->first == key)
            {
                //???is this right?
                return i;
            }
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

    /*Michael Gulson implimentation
    size_t newTableSizePrime;
    //table_size = tableSize();
    newTableSizePrime = findPrime(size * 2);
    
    //create copy table
    std::pair<K, V> ** originalTable = new std::pair<K, V> *[size];

    originalTable = table;
    //mallocate() memory for table
    table = new std::pair<K, V> *[newTableSizePrime];

    bool * should_probe_original = new bool[size];
    should_probe_original = should_probe;
    delete [] should_probe;
    should_probe = new bool[newTableSizePrime];

    for (size_t i = 0; i < newTableSizePrime; i++)
    {
        table[i] =NULL;
        should_probe[i] = false;
    }
    
    

    //rehash key values
    unsigned hashIndex;

    for (size_t i = 0; i < size; i++)
    {
        //no need to rehash empty bins
        if (!should_probe_original[i] || originalTable[i] == NULL)
        {
            continue;
        }
        for (size_t j = 0; j < newTableSizePrime; j++){
            //should_probe returns 1 when something occupied bin previously
            hashIndex = hashes::hash(originalTable[i]->first, newTableSizePrime);
            hashIndex %= newTableSizePrime;
            if (should_probe[i])
            {
                hashIndex++;
                hashIndex %= newTableSizePrime;
            }
            else{
                *table[hashIndex] = *originalTable[i];
                should_probe[hashIndex]=true;
                break;
            }
        }
    }

    delete[] originalTable;
    size = newTableSizePrime;
    */

    size_t newSize = findPrime(size * 2);
    std::pair<K, V> **temp = new std::pair<K, V> *[newSize];
    delete[] should_probe;
    should_probe = new bool[newSize];
    for (size_t i = 0; i < newSize; i++)
    {
        temp[i] = NULL;
        should_probe[i] = false;
    }

    for (size_t slot = 0; slot < size; slot++)
    {
        if (table[slot] != NULL)
        {
            size_t idx = hashes::hash(table[slot]->first, newSize);
       
            while (temp[idx] != NULL)
            {
                idx = (idx+1) % newSize;
            }
            temp[idx] = table[slot];
            should_probe[idx] = true;
        }
    }

    delete[] table;
    // don't delete elements since we just moved their pointers around
    table = temp;
    size = newSize;
}
