#ifndef MSA_FIX_POINT_ITERATOR_H
#define MSA_FIX_POINT_ITERATOR_H

#include <vector>
#include "SPA_Iterator.h"
#include "LDPC_standard.h"

#define  DECIMAL pow(2,2)
#define  WIDTH   pow(2,5)

class MSA_FP : public SPA
{
public:
	MSA_FP(vector <bitset<VARIABLE_BITS>> h, vector <vector<int> > variable_node, vector <vector<int> > check_node);
	~MSA_FP();
	//修改为int型变量
	std::vector <int> q0;
	//float Q[CHECK_BITS][VARIABLE_BITS];
	//float R[CHECK_BITS][VARIABLE_BITS];
	vector<vector<int> > Q;
	vector<vector<int> > R;

	std::vector <int> q;
	void get_q0(std::vector <float>& p, float sigma);
	void get_Q(void);
	void get_R(void);
	void get_q(void);
	void hard_decide(void);
	bool check(void);
};

#endif 
