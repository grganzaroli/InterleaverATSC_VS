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
public:
	void set(int N_bch, int N_ldpc, int Q_ldpc, int Rate, int Mod_size);
	void set(int N_bch, int Q_ldpc, int Rate, int Mod_size);

	void parity_interleaver(const unsigned char *lambda, unsigned char *U); // APENAS LDPC TIPO B
	void parity_deinterleaver(const unsigned char *U, unsigned char *lambda); // APENAS LDPC TIPO B

	void group_interleaver(const unsigned char *GI_in, unsigned char *GI_out, int *tabela);
	void group_deinterleaver(const unsigned char *GDI_in, unsigned char *GDI_out, int *tabela);

	void block_interleaver(const unsigned char *BI_in, unsigned char *BI_out, bool tipo);
	void block_deinterleaver(const unsigned char *BDI_in, unsigned char *BDI_out, bool tipo);

	void block_inter_tipo_A(const unsigned char *BI_in, unsigned char *BI_out, int rows_p1, int rows_p2, int col);
	void block_deinter_tipo_A(const unsigned char *BDI_in, unsigned char *BDI_out, int rows_p1, int rows_p2, int col);

	void block_inter_tipo_B(const unsigned char *BI_in, unsigned char *BI_out, int n_p1, int n_p2, int nqcb);
	void block_deinter_tipo_B(const unsigned char *BDI_in, unsigned char *BDI_out, int n_p1, int n_p2, int nqcb);
};

#endif