// my_predictor.h
// This file contains a sample my_predictor class.
// It is a simple 32,768-entry gshare with a history length of 15.
// Note that this predictor doesn't use the whole 32 kilobytes available
// for the CBP-2 contest; it is just an example.

class my_update : public branch_update {
public:
	unsigned int index1;
	unsigned int index2;
	unsigned int index3;
};

class my_predictor : public branch_predictor {
public:
#define HISTORY_LENGTH	17
#define TABLE_BITS	30
	my_update u;
	branch_info bi;
	unsigned int history;
	unsigned char tab1[1<<TABLE_BITS];
	unsigned char tab2[1<<TABLE_BITS];
	unsigned char tab3[1<<TABLE_BITS];

	my_predictor (void) : history(0) { 
		memset (tab1, 0, sizeof (tab1));
		memset (tab2, 0, sizeof (tab2));
		memset (tab3, 0, sizeof (tab3));
	}

	branch_update *predict (branch_info & b) {
		bi = b;
		if (b.br_flags & BR_CONDITIONAL) {
			u.index1 = 
				  (history << (TABLE_BITS - HISTORY_LENGTH)) 
				^ (b.address & ((1<<10)-1));
			u.index2 = 
				  (history << (TABLE_BITS - HISTORY_LENGTH)) 
				^ ((b.address>>10) & ((1<<10)-1));
			u.index3 = 
				  (history << (TABLE_BITS - HISTORY_LENGTH)) 
				^ ((b.address>>20) & ((1<<10)-1));
			int FinalIndex = ((tab1[u.index1] >> 1) + (tab2[u.index2] >> 1) +(tab3[u.index3] >> 1));
			u.direction_prediction ((FinalIndex > 1) ? 1 : 0);
		} else {
			u.direction_prediction (true);
		}
		u.target_prediction (0);
		return &u;
	}

	void update (branch_update *u, bool taken, unsigned int target) {
		if (bi.br_flags & BR_CONDITIONAL) {
			unsigned char *c1 = &tab1[((my_update*)u)->index1];
			unsigned char *c2 = &tab2[((my_update*)u)->index2];
			unsigned char *c3 = &tab3[((my_update*)u)->index3];
			if (taken) {
				if (*c1 < 3) (*c1)++;
				if (*c2 < 3) (*c2)++;
				if (*c3 < 3) (*c3)++;
			} else {
				if (*c1 > 0) (*c1)--;
				if (*c2 > 0) (*c2)--;
				if (*c3 > 0) (*c3)--;
			}
			history <<= 1;
			history |= taken;
			history &= (1<<HISTORY_LENGTH)-1;
		}
	}
};
