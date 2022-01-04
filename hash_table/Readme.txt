This file is for the implementation of Hash Table in C

A Hash table is a container data structure that allows you to quickly look up a key (often a string) to find its corresponding value. 
Under the hood there are arrays that are indexed by a hash function. 

A Hash function turns a key into a random-looking number, and it must always return the same number given the same key. 

The Hash function that was utilized is 64-Bit FNV-1A. 

Whatever your Hash output is, it must be operated with a "modulo-x", here x is the number of Hash entries you have. Performing a module will allow 0 to x-1 indexes, which 
would quite comfortably allow us map x keys of the hash table with unique indexes. 

To look up a value, we simply fetch array[hash(key) % 16].

But what if two keys hash to the same value?. Depending upon the hash function and size of the array, this is fairly common. 
Traditionally, you would create a hash array of a certain size, and if there was a collision you would use a linked list to store the values that hashed to the same index.

A simpler and "faster" way of dealing with collisions is linear probing. If we are trying to insert an item but there's one already there, simply move to the next slot. 
If the next slot is full too, simply move to the next slot, until you find an empty slot, wrapping around the beginning if you hit the end of the array. 
This technique is lot faster than linked lists, because your CPU's cachehas probably fetched the next items already. 

With a good hash function, this kind of hash table requires an average of one operation per lookup, plus time to hash the key. 
 
