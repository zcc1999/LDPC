#include "MSA_Iterator.h"
MSA::MSA(vector <bitset<VARIABLE_BITS>> h, vector <vector<int> > variable_node, vector <vector<int> > check_node) : SPA(h,variable_node, check_node)
{
}

MSA::~MSA()
{
}

void MSA::get_R(void)
{



	for (int j = 0; j < CHECK_BITS;j++)
	{
		float f = 1.0;
		int a = 1; //¼ÆËãsgnµÄÀÛ³Ë
		float absmin = FLT_MAX;
		float sub_absmin = FLT_MAX;
		for (int i = 0;i < M_ROW;i++)
		{
				if (variable_node[j][i] != -1)
				{
					if (Q[j][variable_node[j][i]] < 0) a *= -1;
					if (abs(Q[j][variable_node[j][i]]) < absmin)
					{
						sub_absmin = absmin;
						absmin = abs(Q[j][variable_node[j][i]]);
					}
					else if(abs(Q[j][variable_node[j][i]]) < sub_absmin)
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
					R[j][variable_node[j][i]] = Q[j][variable_node[j][i]]>0? a*sub_absmin: -a*sub_absmin;
				}
				else
				{
					R[j][variable_node[j][i]] = Q[j][variable_node[j][i]] > 0 ? a * absmin : -a * absmin;
				}
				//if (R[j][variable_node[j][i]] > (8 - 1)) R[j][variable_node[j][i]]=7;
				//if (R[j][variable_node[j][i]] < (-8))    R[j][variable_node[j][i]]=-8;
				//R[j][variable_node[j][i]] *= 0.5;
			}
			//std::cout << R[j][variable_node[j][i]] << "   ";
		}
		
	}
	
}