#ifndef SPA_ITERATOR_H
#define SPA_ITERATOR_H

#include <vector>
#include "LDPC_standard.h"


class SPA
{
public:
	SPA(vector <bitset<VARIABLE_BITS>> h, vector <vector<int> > variable_node, vector <vector<int> > check_node);
	vector <vector<int> > variable_node;
	vector <vector<int> > check_node;
	~SPA();
	std::vector <float> q0;
	//float Q[CHECK_BITS][VARIABLE_BITS];
	//float R[CHECK_BITS][VARIABLE_BITS];
	vector<vector<float> > Q;
	vector<vector<float> > R;
	
	std::vector <float> q;
	std::vector <int> c;
	std::vector <int> s;

	void get_q0(std::vector <float>& p,  float sigma);
	void get_R(void);
	void get_Q(void);
	void get_q(void);
	void hard_decide(void);
	bool check(void);

	void output(void);
//protected:
	//static const int b = 0;
	vector <bitset<VARIABLE_BITS>> H;
};

#endif 
