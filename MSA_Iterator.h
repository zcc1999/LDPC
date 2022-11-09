#ifndef MSA_ITERATOR_H
#define MSA_ITERATOR_H

#include <vector>
#include "SPA_Iterator.h"
#include "LDPC_standard.h"

class MSA : public SPA
{
public:
	MSA(vector <bitset<VARIABLE_BITS>> h,  vector <vector<int> > variable_node, vector <vector<int> > check_node);
	~MSA();
	void get_R(void);
};

#endif 

