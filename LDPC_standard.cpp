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
 *brief: �������M�����е����꣬�������������������LDPC���еĶ�Ӧλ�ã�Ҳ������
 *input: slope ֱ��б�� ��c��ʾ�ؾ࣬a�Ǳ�ʾM�����������index ��ʾ���صĶ�Ӧ���ֵ�������
 *output:
 *author: zhangcc
**************************************************/
void LDPC_STANDARD::get_variable_index(int slope, int c, int a, int& index)
{
	int b = (a * slope + c) % M_COL ;
	//��0�У���173bit��0û����������
	if (a == 0)
	{
		//���е�173λ0��λ��Ϊ292-172��Ҳ��293-173
		if (b >= M_COL - ZEROS_BITS) index = -1;
		else index = M_COL - b - ZEROS_BITS - 1;
	}
	//�ӵ�1����104�У�һ�����Ϣλ
	else if (a <= INFO_ROW_MAX_INDEX)
	{
		index = (1+a) * M_COL - b - ZEROS_BITS - 1;
	}
	//105+6-1=110���ӵ�105-110Ϊ�������У��λ
	else if (a <= CHECK_ROW_START_INDEX + CHECK_REDUNDANCY_ROW - 1)
	{
		if (b == 292) index = -1;
		else index = ((1 + a) * M_COL - b - ZEROS_BITS - 1) - (a - CHECK_ROW_START_INDEX + 1);
	}
	//��111��û��У��λ
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
		for (c = 0; c <= M_COL_MAX_INDEX - 1;c++)  //һ����0-291��292���ؾ�,z�����һ���ؾ�ֻ��һ���ؾྭ��
		{
			H[h_row_index].reset(); //�Ƚ�H����ǰ��ȫ����0��
			//ֱ�߽ؾ�Ϊc,б��Ϊslop[i]
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
	for (c = 0; c <= M_COL_MAX_INDEX;c++)  //һ����0-292��293���ؾ�
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
	for (j = 0; j < row - 1; j++)  //�ȱ�������Ǿ���
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

