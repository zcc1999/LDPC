#include "MSA_FixedPoint_Iterator.h"
MSA_FP::MSA_FP(vector <bitset<VARIABLE_BITS>> h, vector <vector<int> > variable_node, vector <vector<int> > check_node) : SPA(h, variable_node, check_node)
{
	q0.resize(VARIABLE_BITS);
	q.resize(VARIABLE_BITS);
	Q.resize(CHECK_BITS);
	R.resize(CHECK_BITS);
	for (int i = 0; i < CHECK_BITS; i++)
	{
		Q[i].resize(VARIABLE_BITS);
		R[i].resize(VARIABLE_BITS);
	}
}

MSA_FP::~MSA_FP()
{
}

/**************************************************
 *function:  void SPA::get_q0(std::vector <float>& p)
 *brief:对输入的进行llr
 *input:
 *output:
 *author: zhangcc
**************************************************/
void MSA_FP::get_q0(std::vector <float>& p, float sigma)
{
	for (int i = 0;i < p.size();i++)
	{
		q0[i] = (int)((p.at(i) * 2 * DECIMAL) / (sigma * sigma));
		//q0[i] = 0;
		//q0[i] = (p.at(i) * DECIMAL);
		//std::cout << q0[i] << "  ";
		//std::cout << q0[i]<< "  ";
	
		if (q0[i] >= WIDTH - 1) q0[i] = WIDTH - 1;
		if (q0[i] < -WIDTH ) q0[i] = -WIDTH;


		//if (q0[i] >= 0) q0[i] =1.0;
		//if (q0[i] < 0 ) q0[i] = -1.0;
		q[i] = q0[i];

	}
	for (int j = 0; j < CHECK_BITS;j++)
	{
		for (int i = 0;i < q0.size();i++)
		{
			Q[j][i] = H[j][i] * q0[i];
		}
	}
}


void MSA_FP::get_Q(void)
{


	for (int j = 0; j < VARIABLE_BITS;j++)
	{
		float sum = q0[j];
		for (int i = 0;i < 7;i++)
		{
			sum += R.at(check_node[j][i]).at(j);
			if (sum>(WIDTH - 1)) sum = WIDTH - 1;
			if (sum < -WIDTH ) sum = -WIDTH;
		}
		for (int i = 0;i < 7;i++)
		{
			Q[check_node[j][i]][j] = sum - R.at(check_node[j][i]).at(j);
			if (Q[check_node[j][i]][j] >(WIDTH -1)) Q[check_node[j][i]][j] = WIDTH -1;
			if (Q[check_node[j][i]][j] < (-WIDTH )) Q[check_node[j][i]][j] = -WIDTH ;
		}
	}
}

void MSA_FP::get_R(void)
{



	for (int j = 0; j < CHECK_BITS;j++)
	{
		float f = 1.0;
		//int a = 1; //计算sgn的累乘
		bool a = true;
		float absmin = FLT_MAX;
		float sub_absmin = FLT_MAX;
		for (int i = 0;i < M_ROW;i++)
		{
			if (variable_node[j][i] != -1)
			{
				if (Q[j][variable_node[j][i]] < 0) a = !a;
				if (abs(Q[j][variable_node[j][i]]) < absmin)
				{
					sub_absmin = absmin;
					absmin = abs(Q[j][variable_node[j][i]]);
				}
				else if (abs(Q[j][variable_node[j][i]]) < sub_absmin)
				{
					sub_absmin = abs(Q[j][variable_node[j][i]]);
				}
			}
		}
		//absmin *= 0.5;
		//sub_absmin *= 0.5;

		for (int i = 0;i < M_ROW;i++)
		{
			if (variable_node[j][i] != -1)
			{
				if (abs(Q[j][variable_node[j][i]]) == absmin)
				{
					R[j][variable_node[j][i]] = ((Q[j][variable_node[j][i]] < 0) ^a)?  sub_absmin : -sub_absmin;
				}
				else
				{
					R[j][variable_node[j][i]] = ((Q[j][variable_node[j][i]] < 0) ^ a) ? absmin : -absmin;
				}
				//if (R[j][variable_node[j][i]] > (8 - 1)) R[j][variable_node[j][i]]=7;
				//if (R[j][variable_node[j][i]] < (-8))    R[j][variable_node[j][i]]=-8;
				R[j][variable_node[j][i]] = R[j][variable_node[j][i]]>>1;
			}
			//std::cout << R[j][variable_node[j][i]] << "   ";
		}

	}

}

void MSA_FP::get_q(void)
{
	for (int i = 0;i < VARIABLE_BITS;i++)
	{

		q[i] = q0[i];
		for (int k = 0; k < 7; k++)
		{
			q[i] += R[check_node[i][k]][i];
			if (q[i] > WIDTH - 1)
			{
				q[i] = WIDTH -1;
			}
			if (q[i] < -WIDTH)
			{
				q[i] = -WIDTH ;
			}
		}
	}
}



/**************************************************
 *function:void SPA::hard_decide(void)
 *brief:硬决策，并会生成码字c;
 *input:
 *output:
 *author: zhangcc
**************************************************/
void MSA_FP::hard_decide(void)
{
	for (int i = 0;i < VARIABLE_BITS;i++)
	{
		c[i] = q[i] <= 0 ? 1 : 0;
	}
}

/**************************************************
 *function:bool SPA::check(void)
 *brief:生成校验向量s,并进行校验
 *input:
 *output:
 *author: zhangcc
**************************************************/
bool MSA_FP::check(void)
{
	for (int i = 0;i < CHECK_BITS;i++)
	{
		s[i] = 0;
		for (int j = 0;j < M_ROW;j++)
		{
			if (variable_node[i][j] != -1)
				s[i] ^= c[variable_node[i][j]];
			//				s[i] = 1;
		}
		//std::cout << Q[1][variable_node[1][1]]<< "  ";
		if (s[i] == 1) return false;
	}
	return true;
}