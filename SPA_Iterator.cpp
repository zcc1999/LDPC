#include "SPA_Iterator.h"
#include <iostream>
#include "LDPC_standard.h"
#include <math.h>
SPA::SPA(vector <bitset<VARIABLE_BITS>> h, vector <vector<int> > variable_node, vector <vector<int> > check_node)
{
	q0.resize(VARIABLE_BITS);
	q.resize(VARIABLE_BITS);
	c.resize(VARIABLE_BITS);
	s.resize(CHECK_BITS);
	//H.resize(VARIABLE_BITS);
	H = h;
	this->check_node = check_node;
	this->variable_node = variable_node;

	Q.resize(CHECK_BITS);
	R.resize(CHECK_BITS);
	for (int i = 0; i < CHECK_BITS; i++)
	{
		Q[i].resize(VARIABLE_BITS);
		R[i].resize(VARIABLE_BITS);
	}
	
}

SPA::~SPA()
{

}

/**************************************************
 *function:  void SPA::get_q0(std::vector <float>& p)
 *brief:对输入的进行llr
 *input:
 *output:
 *author: zhangcc
**************************************************/
void SPA::get_q0(std::vector <float>& p,float sigma)
{
	for (int i = 0;i < p.size();i++)
	{
		q0[i] = (p.at(i)*2)/(sigma*sigma);
		//q0[i] = (p.at(i) * DECIMAL);
		//std::cout << q0[i] << "  ";
		
	  // if (q0[i] >= WIDTH - 1) q0[i] = WIDTH - 1;
	  // if (q0[i] < -WIDTH ) q0[i] = -WIDTH;
		

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


/**************************************************
 *function: void SPA::get_R(void)
 *brief:更新R矩阵，更新校验点
 *input:
 *output:
 *author: zhangcc
**************************************************/
void SPA::get_R(void)
{
	for (int j = 0; j < CHECK_BITS;j++)
	{
		float f = 1.0;
		for (int i = 0;i < M_ROW;i++)
		{	
			if (variable_node[j][i] != -1) 
				f *= tanhf(Q[j][variable_node[j][i]] / 2);
		}
		for (int i = 0;i < M_ROW;i++)
		{
			if (variable_node[j][i] != -1)
				R[j][variable_node[j][i]] = 2.0 * atanhf(f/ tanhf(Q[j][variable_node[j][i]] / 2));
		}
	}
}

/**************************************************
 *function: void SPA::get_Q(void)
 *brief:更新Q矩阵，更新变量节点
 *input:
 *output:
 *author: zhangcc
**************************************************/
void SPA::get_Q(void)
{
	

	for (int j = 0; j < VARIABLE_BITS;j++)
	{
		float sum = q0[j];
		for (int i = 0;i < 7 ;i++)
		{
			sum +=  R.at(check_node[j][i]).at(j);
			//if (sum>(WIDTH - 1)) sum = WIDTH - 1;
			//if (sum < -WIDTH ) sum = -WIDTH;
		}
		for (int i = 0;i < 7;i++)
		{
			Q[check_node[j][i]][j] = sum- R.at(check_node[j][i]).at(j);
			//if (Q[check_node[j][i]][j] >(WIDTH -1)) Q[check_node[j][i]][j] = WIDTH -1;
			//if (Q[check_node[j][i]][j] < (-WIDTH )) Q[check_node[j][i]][j] = -WIDTH ;
		}
	}
}
void SPA::get_q(void)
{
	for (int i = 0;i < VARIABLE_BITS;i++)
	{

		q[i] = q0[i];
		for (int k = 0; k < 7; k++)
		{
				q[i] += R[check_node[i][k]][i];

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
void SPA::hard_decide(void)
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
bool SPA::check(void)
{
	for (int i = 0;i < CHECK_BITS;i++)
	{
		s[i] = 0;
		for (int j = 0;j < M_ROW;j++)
		{
			if (variable_node[i][j] != -1)
				s[i] ^=  c[variable_node[i][j]];
//				s[i] = 1;
		}
		//std::cout << Q[1][variable_node[1][1]]<< "  ";
		if (s[i] == 1) return false;
	}
	return true;
}


/**************************************************
 *function: bool SPA::output(void)
 *brief:打印输出
 *input:
 *output:
 *author: zhangcc
**************************************************/
void SPA::output(void)
{
	for (int i = 0;i < q0.size();i++)
		std::cout << q0[i] << " ";
	std::cout << std::endl;

	std::cout << "R矩阵如下：" << std::endl;
	for (int j = 0;j < CHECK_BITS;j++)
	{
		for (int i = 0;i < VARIABLE_BITS;i++)
		{
			std::cout.setf(std::ios::right);
			std::cout.width(12);
			std::cout << R[j][i];
		}
		std::cout << std::endl;
	}

	std::cout << "Q矩阵如下：" << std::endl;
	for (int j = 0;j < CHECK_BITS;j++)
	{
		for (int i = 0;i < VARIABLE_BITS;i++)
		{
			std::cout.setf(std::ios::right);
			std::cout.width(12);
			std::cout << Q[j][i];
		}
		std::cout << std::endl;
	}

	std::cout << "q如下：" << std::endl;
	for (int i = 0;i < q.size();i++)
		std::cout << q[i] << " ";
	std::cout << std::endl;

	std::cout << "硬决策,c，s如下：" << std::endl;
	for (int i = 0;i < c.size();i++)
		std::cout << c[i] << " ";
	std::cout << std::endl;
	for (int i = 0;i < s.size();i++)
		std::cout << s[i] << " ";
	std::cout << std::endl;
}