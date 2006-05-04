#include <stdio.h>
#include <string.h>
#include <fltk/lut.h>

/////////////////////////////////////////////////////
// Ptr DicoImplementation
/////////////////////////////////////////////////////
using namespace fltk;

// calc a key to enter a slot with possible collision modulo hasTableLen

// Static variables init
LookupTable::Node* LookupTable::slot[hashTableLen];
unsigned long LookupTable::ID =0;

void LookupTable::init() { 
    memset(slot, 0, sizeof(slot) );
}
// Node::remove() : remove node wihch value is key from the list 
LookupTable::Node* LookupTable::Node::remove(Node* &first, const Key& p) {
    if (first && p) 
	for (Node *prev=0, *n=first; n; prev=n, n=n->next) {
	    if (n->key==p) {
		if(prev) prev->next=n->next; else first = first->next; 
		return n;
	    }
    }
    return 0;
}

void LookupTable::dump () { 
    for (size_t i=0; i< (hashTableLen>1024 ? 1024: hashTableLen); i++) {
	size_t c = Node::count(slot[i]);
	fprintf(stderr, "slot %04ld : %ld elements\n",i , c);
    }
}

size_t LookupTable::count() {
    size_t c=0; 
    for (int i=0;i<hashTableLen;i++) c+=Node::count(slot[i]); 
    return c;
}
  
