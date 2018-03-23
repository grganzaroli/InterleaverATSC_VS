#ifndef ATSC_INTERLEAVER_H
#define ATSC_INTERLEAVER_H

class atsc_interleaver
{
private:
	int rate; //taxa de codificação LDPC
	int n_bch; //N_bch
	int n_ldpc; //N_ldpc
	int q_ldpc; //Q_ldpc
	int mod_size; //modulação
	bool interleaver_type; // false = Tipo A, true = Tipo B
	int tab_size; //tamanho da tabela
	const int *tab; //tabela de permutação group-deinterleaver
	int tabela[180];

public:
	void set(int N_ldpc, int Rate, int Mod_size);

	void parity_inter(const unsigned char *lambda, unsigned char *U); // APENAS LDPC TIPO B
	void parity_deinter(const float *U, float *lambda); // APENAS LDPC TIPO B

	void group_inter(const unsigned char *GI_in, unsigned char *GI_out);
	void group_deinter(const float *GDI_in, float *GDI_out);

	void block_inter(const unsigned char *BI_in, unsigned char *BI_out);
	void block_deinter(const float *BDI_in, float *BDI_out);

	void block_inter_tipo_A(const unsigned char *BI_in, unsigned char *BI_out, int rows_p1, int rows_p2, int col);
	void block_deinter_tipo_A(const float *BDI_in, float *BDI_out, int rows_p1, int rows_p2, int col);

	void block_inter_tipo_B(const unsigned char *BI_in, unsigned char *BI_out, int n_p1, int n_p2, int nqcb);
	void block_deinter_tipo_B(const float *BDI_in, float *BDI_out, int n_p1, int n_p2, int nqcb);
};

#endif