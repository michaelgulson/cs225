/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"
 
template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{
    /**
     * @todo Implement this function.
     *
     */
    //???null check do we need this???
    if(key == K() && value ==V()){
        return;
    }
    // double newLoadFactor;
    // newLoadFactor = (elems + 1) / size;
    elems++;
    if(shouldResize()){
        resizeTable();
    }

    unsigned hashIndex;
    std::pair<K,V> hashInsert = std::make_pair(key,value);

    hashIndex = hashes::hash(key, size);

    //you don't need to concern yourself with duplicate keys
    /*if (keyExists(key)){           //No
        return; //key already exists in hashtable?
    }*/

    //typename std::list<std::pair<K, V>>::iterator bucket_iterator;
    typename std::list<std::pair<K, V>>::iterator it = table[hashIndex].begin();



    //insert element into linked list
    table[hashIndex].insert(it, hashInsert);


    //increase elems private member
    //elems++;

    /*while (it != end())
        { //
            //std::pair<K, V> &operator*
            if ((*(curr).K == K()) && (*(curr).V == V()))
            {
                *(curr).K = key;
                *(curr).V = value;
                break; //insert into empty location???
            }
            curr++
        }
    }*/

    //is this preferable ^ to below
    //HashTable<K, V>::iterator curr;

    //curr = begin();
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    //size_t table_size;
    //typename std::list<std::pair<K, V>>::iterator it;
    //??? should we be using this ^
    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */
    //for typename list< pair<K,V> >::iterator it = table[i].begin(); <- this class
    //does it++ iterate through the different list entries and pairs in each list and abstact that
    //or do we need to do that

    //do we need multiple list iterators
    //table_size = tableSize();
    for (size_t i = 0; i < size; i++)
    {
        typename std::list<std::pair<K, V>>::iterator it;
    
        //??there's a compiler error on this line
        for (it = table[i].begin(); it != table[i].end(); it++){
            if ((*(it)).first == key) {
                table[i].erase(it);
                elems--;
                return;
            }
        }
        /*while (it != end()){ //
            //std::pair<K, V> &operator*
            
            it++;
        }*/
    }
    //(void) key; // prevent warnings... When you implement this function, remove this line.
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{
    //typename std::list<std::pair<K, V>>::iterator it;
    //??? is this necessary ^

    //size_t table_size;

    /**
     * @todo: Implement this function.
     */
    //table_size = tableSize();
    for (size_t i = 0; i < size; i++)
    {
        //typename std::list<std::pair<K, V>>::iterator it = table[i].begin();
        typename std::list<std::pair<K, V>>::iterator it;
        // = table[i].begin();

        //??there's a compiler error on this line
        for (it = table[i].begin(); it != table[i].end(); it++)
        {
            if ((*(it)).first == key)
            {
                return (*it).second;
            }
        }
        /*while (it != end()){ //
            //std::pair<K, V> &operator*
            
            it++;
        }*/
    }

    /*while (it != end()){ //
        //std::pair<K, V> &operator*
        if ((*(it).K == key))
        {
            (*(it).K) = K();
            return *(it).V;
        }
        it++
    }
    */

    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename std::list<std::pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */

    size_t newTableSizePrime;
    //table_size = tableSize();
    newTableSizePrime = findPrime(size * 2);
    //table->resize(newTableSizePrime);
    //CA says make a new table?
    std::list<std::pair<K, V>> * copyTable = new std::list<std::pair<K, V>>[size];

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
        for (it = copyTable[i].begin(); it != copyTable[i].end(); it++)
        {
            /*if ((*(it)).first == key)
            {
                table[i].erase(it);
                elems--;
                return;
            }*/
            hashIndex = hashes::hash((*it).first, newTableSizePrime);

            table[hashIndex].insert(table[hashIndex].begin(), *it);
            //???does this insert an element to front of linked list 
        }
    }

    //hash(key);
    //delete and replace old table
    delete [] copyTable;

    size =newTableSizePrime;
    //??? how does this look ^
}
