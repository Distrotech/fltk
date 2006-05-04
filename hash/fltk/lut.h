/*
 *  lookup.h
 *
 *  by Fabien Costantini 03/05/06
 *    Very fast lookup table mechanism for pointer (+ID or other user_data) data
 *
 *  Typically the lookup of one item in the hashtable (with ideal collision rate)
 *    is about 168 nanosecs for 250 thousands items in the table on a powermac 2.5ghz !
 *
 */
#ifndef fl_lookup_h
#define fl_lookup_h
////////////////////////////////////////////////////////////////////////////////////	
#include "FL_API.h"
#include <fltk/types.h>
#include <stddef.h>

namespace fltk {

    // Warning: Table Len must be a power of 2 for performance issues !
    const int hashTableLen = 16384; // means 64KB table on 32bit arch on init.

    inline static int hashAlgo(PointerValue p) {
#if defined(FLTK_ARCH64) // hash a 64 bits value : for 64bits pointers platforms with dword data alignement by p>>2
	return ( p>>2 ^ (p>>8) ^ (p>>16) ^ (p>>24) ^ 
	    (p>>32) ^ (p>>40) ^ (p>>48) ^ (p>>56) )  & (hashTableLen-1) ; 
#else	// hash a 32 bits value (taking with dword data alignement by p>>2)
	return ( p>>2 ^ (p>>8) ^ (p>>16) ^ (p>>24) ) &  (hashTableLen-1);
#endif
    }
    /** This static class features a very fast pointer lookup algorithm.
	  using a hashCoding algorithm adapted to pointer types
	and take in account modern ptr alignment  & platforms with 32/64bits arch
	for an ideal hashed values repartitionthough it does not use any template 
	this class is quite easy to adapt for other needs : 
	further new Key, DataType types and (if necessary) hashCode inline function
    */    
    class FL_API LookupTable {
	public:
	    struct Node;
	    typedef void * Key;	    // what we are looking for in this table
	    typedef unsigned long DataType;  // optional user data type
	    
	    //! finding a pointer in the table
	    static const DataType * find(const Key& key) {return Node::find(slot[hashAlgo((PointerValue)key)], key); }
	    //! is an object still valid ?
	    static bool is_valid(const Key& key, DataType id) {const DataType * d=find(key); return d  && *d==id;}

	    //! adding a pointer to the table of lists
	    static void add(const Key& key, DataType data) {Node::add(slot[hashAlgo((PointerValue)key)], new Node(key, data));}
	    static void add(const Key& key, Node* n) {Node::add(slot[hashAlgo((PointerValue)key)], n);}
	    //! removing a pointer if in the table
	    static Node *remove(const Key& key) {
		return Node::remove(slot[hashAlgo((PointerValue)key)], key);
	    }
	    
	    //! getting a unique (non-persistent) ID
	    static unsigned long get_uid() { return ++ID;}
	    
	    //! initialize the class internals
	    static void init();
	    //! free resources
	    static void done() {for (int i=0; i<hashTableLen; i++) Node::clear(slot[i]);}
	    
	    //! for statistics purpose count the nuumber of stored nodes in the hashTable
	    static size_t count();
	    //! dump items
	    static void dump ();
    
	    // node data structure (simple linked list is enough as very few collision are intended)
	    struct Node {
		Key	    key;
		DataType    data;
		Node*	    next;
		//! Node constructor
		Node(const Key& p, const DataType& d) {key=p; data=d;}
		virtual ~Node(){}
		//! remove all entries from the list
		static void clear(Node * first) {for(Node*p=first; p;) {first=p; p=p->next; delete first;} }
		//! add a node o the list
		static void add(Node * &first, Node * n) { n->next=first;first=n; }
		//! remove a node from its key in the list slot
		static Node *remove(Node* &first, const Key& p);
		//! find  node which value is key from the list 
		static const DataType* find(const Node* first, const Key& p) 
		    {for(; first ; first=first->next) if (first->key==p) return &first->data; return 0;}
		//! count the number of item linked
		static size_t count(const Node* first) {size_t i=0;for(; first ; first=first->next, i++);return i;}
	    }; 
	private:
	    static Node * slot[hashTableLen];
	    static unsigned long ID;
    };
}
#endif
