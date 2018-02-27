#include "stdafx.h"
#include "atsc_interleaver.h"

void atsc_interleaver::set(int N_bch, int n_ldpc, int Q_ldpc, int Rate, int Mod_size)
{
	n_bch = N_bch;
	n_ldpc = n_ldpc;
	rate = Rate;
	q_ldpc = Q_ldpc;
	mod_size = Mod_size;
}

void atsc_interleaver::set(int N_bch, int Q_ldpc, int Rate, int Mod_size)
{
	n_bch = N_bch;
	n_ldpc = n_bch*15/Rate;
	q_ldpc = Q_ldpc;
	mod_size = Mod_size;
}

void atsc_interleaver::parity_interleaver(const unsigned char *lambda, unsigned char *U)
{
	for (int i = 0; i < n_bch; i++)
		U[i] = lambda[i];

	for (int s = 0; s < 360; s++)
		for (int t = 0; t < q_ldpc; t++)
			U[n_bch+360*t+s] = lambda[n_bch+q_ldpc*s+t];
}

void atsc_interleaver::parity_deinterleaver(const unsigned char *U, unsigned char *lambda)
{
	for (int i = 0; i < n_bch; i++)
		lambda[i] = U[i];

	for (int s = 0; s < 360; s++)
		for (int t = 0; t < q_ldpc; t++)
			lambda[n_bch+q_ldpc*s+t] = U[n_bch+360*t+s];
}

void atsc_interleaver::group_interleaver(const unsigned char *GI_in, unsigned char *GI_out, int *tabela)
{
	int tab_size;
	if(n_ldpc == 16200)
		tab_size = 45;
	else if(n_ldpc == 64800)
		tab_size = 180;

	for(int i = 0; i < tab_size; i++)
	{
		for(int j = 0; j < 360; j++)
		{
			GI_out[j+360*i] = GI_in[j+360*tabela[i]];
		}
	}
}

void atsc_interleaver::group_deinterleaver(const unsigned char *GDI_in, unsigned char *GDI_out, int *tabela)
{
	int tab_size;
	if(n_ldpc == 16200)
		tab_size = 45;
	else if(n_ldpc == 64800)
		tab_size = 180;

	for(int i = 0; i < tab_size; i++)
	{
		for(int j = 0; j < 360; j++)
		{
			GDI_out[j+360*tabela[i]] = GDI_in[j+360*i];
		}
	}

}

void atsc_interleaver::block_interleaver(const unsigned char *BI_in, unsigned char *BI_out, bool tipo)
{
	if(!tipo) //tipo A
	{
		int rows_pt1, rows_pt2, colu;
		if(n_ldpc == 16200)
		{
			switch(mod_size)
			{
			case 4:
				rows_pt1 = 7920;
				rows_pt2 = 180;
				colu = 2;
				break;
			case 16:
				rows_pt1 = 3960;
				rows_pt2 = 90;
				colu = 4;
				break;
			case 64:
				rows_pt1 = 2520;
				rows_pt2 = 180;
				colu = 6;
				break;
			case 256:
				rows_pt1 = 1800;
				rows_pt2 = 225;
				colu = 8;
				break;
			default: //64qam
				rows_pt1 = 2520;
				rows_pt2 = 180;
				colu = 6;
				break;
			}
		}
		else if(n_ldpc == 64800)
		{
			switch(mod_size)
			{
			case 4:
				rows_pt1 = 32400;
				rows_pt2 = 0;
				colu = 2;
				break;
			case 16:
				rows_pt1 = 16200;
				rows_pt2 = 0;
				colu = 4;
				break;
			case 64:
				rows_pt1 = 10800;
				rows_pt2 = 0;
				colu = 6;
				break;
			case 256:
				rows_pt1 = 7920;
				rows_pt2 = 180;
				colu = 8;
				break;
			case 1024:
				rows_pt1 = 6480;
				rows_pt2 = 0;
				colu = 10;
				break;
			case 4096:
				rows_pt1 = 5400;
				rows_pt2 = 0;
				colu = 12;
				break;
			default: //64qam
				rows_pt1 = 10800;
				rows_pt2 = 0;
				colu = 6;
				break;
			}
		}

		block_inter_tipo_A(BI_in, BI_out, rows_pt1, rows_pt2, colu);
	}
	else //tipo B
	{
		int n_pt1, n_pt2, nqcb;
		if(n_ldpc == 16200)
		{
			switch(mod_size)
			{
			case 4:
				n_pt1 = 15840;
				n_pt2 = 360;
				nqcb = 2;
				break;
			case 16:
				n_pt1 = 15840;
				n_pt2 = 360;
				nqcb = 4;
				break;
			case 64:
				n_pt1 = 15120;
				n_pt2 = 1080;
				nqcb = 6;
				break;
			case 256:
				n_pt1 = 14400;
				n_pt2 = 1800;
				nqcb = 8;
				break;
			default: //64qam
				n_pt1 = 15120;
				n_pt2 = 1080;
				nqcb = 6;
				break;
			}
		}
		else if(n_ldpc == 64800)
		{
			switch(mod_size)
			{
			case 4:
				n_pt1 = 64800;
				n_pt2 = 0;
				nqcb = 2;
				break;
			case 16:
				n_pt1 = 64800;
				n_pt2 = 0;
				nqcb = 4;
				break;
			case 64:
				n_pt1 = 64800;
				n_pt2 = 0;
				nqcb = 6;
				break;
			case 256:
				n_pt1 = 63360;
				n_pt2 = 1440;
				nqcb = 8;
				break;
			case 1024:
				n_pt1 = 64800;
				n_pt2 = 0;
				nqcb = 10;
				break;
			case 4096:
				n_pt1 = 64800;
				n_pt2 = 0;
				nqcb = 12;
				break;
			default: //64qam
				n_pt1 = 64800;
				n_pt2 = 0;
				nqcb = 6;
				break;
			}
		}

		block_inter_tipo_B(BI_in, BI_out, n_pt1, n_pt2, nqcb);
	}

}

void atsc_interleaver::block_deinterleaver(const unsigned char *BDI_in, unsigned char *BDI_out, bool tipo)
{if(!tipo) //tipo A
{
	int rows_pt1, rows_pt2, colu;
	if(n_ldpc == 16200)
	{
		switch(mod_size)
		{
		case 4:
			rows_pt1 = 7920;
			rows_pt2 = 180;
			colu = 2;
			break;
		case 16:
			rows_pt1 = 3960;
			rows_pt2 = 90;
			colu = 4;
			break;
		case 64:
			rows_pt1 = 2520;
			rows_pt2 = 180;
			colu = 6;
			break;
		case 256:
			rows_pt1 = 1800;
			rows_pt2 = 225;
			colu = 8;
			break;
		default: //64qam
			rows_pt1 = 2520;
			rows_pt2 = 180;
			colu = 6;
			break;
		}
	}
	else if(n_ldpc == 64800)
	{
		switch(mod_size)
		{
		case 4:
			rows_pt1 = 32400;
			rows_pt2 = 0;
			colu = 2;
			break;
		case 16:
			rows_pt1 = 16200;
			rows_pt2 = 0;
			colu = 4;
			break;
		case 64:
			rows_pt1 = 10800;
			rows_pt2 = 0;
			colu = 6;
			break;
		case 256:
			rows_pt1 = 7920;
			rows_pt2 = 180;
			colu = 8;
			break;
		case 1024:
			rows_pt1 = 6480;
			rows_pt2 = 0;
			colu = 10;
			break;
		case 4096:
			rows_pt1 = 5400;
			rows_pt2 = 0;
			colu = 12;
			break;
		default: //64qam
			rows_pt1 = 10800;
			rows_pt2 = 0;
			colu = 6;
			break;
		}
	}

	block_deinter_tipo_A(BDI_in, BDI_out, rows_pt1, rows_pt2, colu);
}
else //tipo B
{
	int n_pt1, n_pt2, nqcb;
	if(n_ldpc == 16200)
	{
		switch(mod_size)
		{
		case 4:
			n_pt1 = 15840;
			n_pt2 = 360;
			nqcb = 2;
			break;
		case 16:
			n_pt1 = 15840;
			n_pt2 = 360;
			nqcb = 4;
			break;
		case 64:
			n_pt1 = 15120;
			n_pt2 = 1080;
			nqcb = 6;
			break;
		case 256:
			n_pt1 = 14400;
			n_pt2 = 1800;
			nqcb = 8;
			break;
		default: //64qam
			n_pt1 = 15120;
			n_pt2 = 1080;
			nqcb = 6;
			break;
		}
	}
	else if(n_ldpc == 64800)
	{
		switch(mod_size)
		{
		case 4:
			n_pt1 = 64800;
			n_pt2 = 0;
			nqcb = 2;
			break;
		case 16:
			n_pt1 = 64800;
			n_pt2 = 0;
			nqcb = 4;
			break;
		case 64:
			n_pt1 = 64800;
			n_pt2 = 0;
			nqcb = 6;
			break;
		case 256:
			n_pt1 = 63360;
			n_pt2 = 1440;
			nqcb = 8;
			break;
		case 1024:
			n_pt1 = 64800;
			n_pt2 = 0;
			nqcb = 10;
			break;
		case 4096:
			n_pt1 = 64800;
			n_pt2 = 0;
			nqcb = 12;
			break;
		default: //64qam
			n_pt1 = 64800;
			n_pt2 = 0;
			nqcb = 6;
			break;
		}
	}

	block_deinter_tipo_B(BDI_in, BDI_out, n_pt1, n_pt2, nqcb);
}
}

void atsc_interleaver::block_inter_tipo_A(const unsigned char *BI_in, unsigned char *BI_out, int rows_p1, int rows_p2, int col)
{
	unsigned char **bl_intera = new unsigned char*[col];
	for(int i = 0; i < col; i++)
		bl_intera[i] = new unsigned char[rows_p1+rows_p2];

	//write
	for(int i = 0; i < col; i++)
	{
		//pt1
		for(int j = 0; j < rows_p1; j++)
		{
			bl_intera[i][j] = BI_in[j+rows_p1*i];
		}
		//pt2
		for(int j = 0; j < rows_p2; j++)
		{
			bl_intera[i][j+rows_p1] = BI_in[j+rows_p2*i+col*rows_p1];
		}
	}

	//read
	//pt1
	for(int i = 0; i < rows_p1; i++)
	{

		for(int j = 0; j < col; j++)
		{
			BI_out[j+col*i] = bl_intera[j][i];
		}
	}
	//pt2
	for(int i = 0; i < rows_p2; i++)
	{
		for(int j = 0; j < col; j++)
		{
			BI_out[j+col*i+col*rows_p1] = bl_intera[j][i+rows_p1];
		}
	}

	for (int i = 0; i < col; ++i)
		delete [] bl_intera[i];
	delete [] bl_intera;

}

void atsc_interleaver::block_deinter_tipo_A(const unsigned char *BDI_in, unsigned char *BDI_out, int rows_p1, int rows_p2, int col)
{
	unsigned char **bl_deintera = new unsigned char*[col];
	for(int i = 0; i < col; i++)
		bl_deintera[i] = new unsigned char[rows_p1+rows_p2];

	//write
	//pt1
	for(int i = 0; i < rows_p1; i++)
	{

		for(int j = 0; j < col; j++)
		{
			bl_deintera[j][i] = BDI_in[j+col*i];
		}
	}
	//pt2
	for(int i = 0; i < rows_p2; i++)
	{
		for(int j = 0; j < col; j++)
		{
			bl_deintera[j][i+rows_p1] = BDI_in[j+col*i+col*rows_p1];
		}
	}

	//read
	for(int i = 0; i < col; i++)
	{
		//pt1
		for(int j = 0; j < rows_p1; j++)
		{
			BDI_out[j+rows_p1*i] = bl_deintera[i][j];
		}
		//pt2
		for(int j = 0; j < rows_p2; j++)
		{
			BDI_out[j+rows_p2*i+col*rows_p1] = bl_deintera[i][j+rows_p1];
		}
	}

	printf("");

	for (int i = 0; i < col; ++i)
		delete [] bl_deintera[i];
	delete [] bl_deintera;

}

void atsc_interleaver::block_inter_tipo_B(const unsigned char *BI_in, unsigned char *BI_out, int n_p1, int n_p2, int nqcb)
{
	unsigned char **bl_interb = new unsigned char*[360];
	for(int i = 0; i < 360; i++)
		bl_interb[i] = new unsigned char[nqcb];

	for(int k = 0; k < n_p1; k+=(nqcb*360))
	{
		//write
		for(int i = 0; i < nqcb; i++)
		{
			//pt1
			for(int j = 0; j < 360; j++)
			{
				bl_interb[j][i] = BI_in[j+360*i+k];
			}
		}
		//pt2 não é entrelaçado

		//read
		//pt1
		for(int i = 0; i < 360; i++)
		{
			for(int j = 0; j < nqcb; j++)
			{
				BI_out[j+nqcb*i+k] = bl_interb[i][j];
			}
		}
		//pt2 não é entrelaçado
	}

	//pt2
	for(int i = 0; i < n_p2; i++)
	{
		BI_out[i+n_p1] = BI_in[i+n_p1];
	}

	for (int i = 0; i < 360; ++i)
		delete [] bl_interb[i];
	delete [] bl_interb;
}

void atsc_interleaver::block_deinter_tipo_B(const unsigned char *BDI_in, unsigned char *BDI_out, int n_p1, int n_p2, int nqcb)
{
	unsigned char **bl_deinterb = new unsigned char*[360];
	for(int i = 0; i < 360; i++)
		bl_deinterb[i] = new unsigned char[nqcb];
	
	for(int k = 0; k < n_p1; k+=(nqcb*360))
	{
		//write
		//pt1
		for(int i = 0; i < 360; i++)
		{
			for(int j = 0; j < nqcb; j++)
			{
				bl_deinterb[i][j] = BDI_in[j+nqcb*i+k];
			}
		}
		//pt2 não é entrelaçado

		//read
		for(int i = 0; i < nqcb; i++)
		{
			//pt1
			for(int j = 0; j < 360; j++)
			{
				BDI_out[j+360*i+k] = bl_deinterb[j][i];
			}
		}
		//pt2 não é entrelaçado

	}

	//pt2
	for(int i = 0; i < n_p2; i++)
	{
		BDI_out[i+n_p1] = BDI_in[i+n_p1];
	}

	for (int i = 0; i < 360; ++i)
		delete [] bl_deinterb[i];
	delete [] bl_deinterb;
}