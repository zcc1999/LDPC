#include "LDPC_standard.h"
LDPC_STANDARD::LDPC_STANDARD(void):variable_node(vector <vector<int> >(CHECK_BITS, vector<int>(M_ROW))),
								   check_node(vector <vector<int> >(VARIABLE_BITS, vector<int>(7)))

{
	H.resize(CHECK_BITS);
}

LDPC_STANDARD::~LDPC_STANDARD()
{
}

/**************************************************
 *function: void LDPC_STANDARD::get_variable_index(int slope, int c, int a, int& index)
 *brief: 先求出在M矩阵中的坐标，再利用这个坐标计算出在LDPC码中的对应位置，也即索引
 *input: slope 直线斜率 ，c表示截距，a是表示M矩阵的行数，index 表示返回的对应码字的索引。
 *output:
 *author: zhangcc
**************************************************/
void LDPC_STANDARD::get_variable_index(int slope, int c, int a, int& index)
{
	int b = (a * slope + c) % M_COL ;
	//第0行，有173bit置0没有索引返还
	if (a == 0)
	{
		//其中第173位0的位置为292-172，也即293-173
		if (b >= M_COL - ZEROS_BITS) index = -1;
		else index = M_COL - b - ZEROS_BITS - 1;
	}
	//从第1行至104行，一般的信息位
	else if (a <= INFO_ROW_MAX_INDEX)
	{
		index = (1+a) * M_COL - b - ZEROS_BITS - 1;
	}
	//105+6-1=110，从第105-110为有冗余的校验位
	else if (a <= CHECK_ROW_START_INDEX + CHECK_REDUNDANCY_ROW - 1)
	{
		if (b == 292) index = -1;
		else index = ((1 + a) * M_COL - b - ZEROS_BITS - 1) - (a - CHECK_ROW_START_INDEX + 1);
	}
	//第111行没有校验位
	else if (a == M_ROW_MAX_INDEX)
	{
		index = ((1 + a) * M_COL - b - ZEROS_BITS - 1) - 6;
	}
}

void LDPC_STANDARD::get_H(void)
{
	int i,c,a;
	int h_row_index = 0;
	int vari_index;
	//int check_index;
	for (i = 0; i < 6;i++)
	{
		for (c = 0; c <= M_COL_MAX_INDEX - 1;c++)  //一共有0-291，292个截距,z，最后一个截距只有一个截距经过
		{
			H[h_row_index].reset(); //先将H矩阵当前行全部置0；
			//直线截距为c,斜率为slop[i]
			for (a = 0; a <= M_ROW_MAX_INDEX; a++)
			{
				get_variable_index(slope[i], c, a, vari_index);
				if (vari_index != -1)
				{
					H[h_row_index][vari_index] = 1;
					check_node[vari_index][i] = h_row_index;
				}
				variable_node[h_row_index][a] = vari_index;
			}
			h_row_index++;
		}
	}
	for (c = 0; c <= M_COL_MAX_INDEX;c++)  //一共有0-292，293个截距
	{
		H[h_row_index].reset();
		for (a = 0; a <= M_ROW_MAX_INDEX; a++)
		{
			get_variable_index(slope[6], c, a, vari_index);
			if (vari_index != -1)
			{
				H[h_row_index][vari_index] = 1;
				check_node[vari_index][6] = h_row_index;
			}
			variable_node[h_row_index][a] = vari_index;
			
		}
		h_row_index++;
	}
	
}



void LDPC_STANDARD::get_H_tran(void)
{
	getnew(H, H_tran);
}
void   getnew(vector <bitset <VARIABLE_BITS> > mar, vector <bitset <VARIABLE_BITS> > &mar_tran)
{
	size_t row;
	row = mar.size();
	bitset <VARIABLE_BITS> temp;
	int i, j;
	mar_tran = mar;
	for (j = 0; j < row - 1; j++)  //先变成下三角矩阵
	{
		for (i = j; i < row; i++)
		{
			if (mar_tran[i][VARIABLE_BITS - row + j]) break;
		}
		if (i != j)
		{
			temp = mar_tran[i];
			mar_tran[i] = mar_tran[j];
			mar_tran[j] = temp;
		}
		for (int k = j + 1; k < row; k++)
		{
			if (mar_tran[k][VARIABLE_BITS - row + j] == 1)
			{
				mar_tran[k] = mar_tran[k] ^ mar_tran[j];
			}
		}
	}

	for (j = 0; j < row - 1; j++)
	{
		for (i = row - 1 - j - 1; i >= 0; i--)
		{
			if (mar_tran[i][VARIABLE_BITS - 1 - j])
				mar_tran[i] = mar_tran[i] ^ mar_tran[row - j - 1];
		}
	}
	
};

