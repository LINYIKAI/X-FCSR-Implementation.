#include<time.h>
#include<vector>
typedef unsigned char u8;
typedef unsigned int u32;





class X_FCSR
{
private:
	int Matrix[257][257];
	int clock_Matrix[9][10];
	std::vector<u8>keystream_storage;
	struct data_struct
	{
		u32 state[8];
		u32 carry[8];
		u32 filter[8];
	}FCSR_register;
public:
	void Matrix_init();
	void clock_Matrix_init();
	void register_Key_IV_Load(const u8  Key[16], const u8 IV[16]);
	void register_update();
	void register_clock();
	u8 keystream();
	void encrypt(int plain_text_length,std::vector<u8>plain, std::vector<u8>&ciphertext);
	void Decrypt(std::vector<u8>ciphertext, std::vector<u8>&plain);
};



void X_FCSR::Matrix_init()
{
	for (int i = 0; i < 257; i++)
	{
		for (int j = 0; j < 257; j++)
			Matrix[i][j] = 0;
	}
	Matrix[51][207] = 1;
	Matrix[55][203] = 1;
	Matrix[57][201] = 1;
	Matrix[59][199] = 1;
	Matrix[68][190] = 1;
	Matrix[73][185] = 1;
	Matrix[75][183] = 1;
	Matrix[77][181] = 1;
	Matrix[80][177] = 1;
	Matrix[82][175] = 1;
	Matrix[83][172] = 1;
	Matrix[84][173] = 1;
	Matrix[86][171] = 1;
	Matrix[91][167] = 1;
	Matrix[93][165] = 1;
	Matrix[96][161] = 1;
	Matrix[101][156] = 1;
	Matrix[103][154] = 1;
	Matrix[105][152] = 1;
	Matrix[108][149] = 1;
	Matrix[112][146] = 1;
	Matrix[114][144] = 1;
	Matrix[116][142] = 1;
	Matrix[119][139] = 1;
	Matrix[122][136] = 1;
	Matrix[124][134] = 1;
	Matrix[129][128] = 1;
	Matrix[131][125] = 1;
	Matrix[134][123] = 1;
	Matrix[136][120] = 1;
	Matrix[139][117] = 1;
	Matrix[144][113] = 1;
	Matrix[146][109] = 1;
	Matrix[149][106] = 1;
	Matrix[154][102] = 1;
	Matrix[157][100] = 1;
	Matrix[158][98] = 1;
	Matrix[162][94] = 1;
	Matrix[165][92] = 1;
	Matrix[168][87] = 1;
	Matrix[173][83] = 1;
	Matrix[178][78] = 1;
	Matrix[183][74] = 1;
	Matrix[185][71] = 1;
	Matrix[187][69] = 1;
	Matrix[191][66] = 1;
	Matrix[192][65] = 1;
	Matrix[193][63] = 1;
	Matrix[196][61] = 1;
	Matrix[199][58] = 1;
	Matrix[201][56] = 1;
	Matrix[204][53] = 1;
	Matrix[208][49] = 1;
	Matrix[211][45] = 1;
	Matrix[213][43] = 1;
	Matrix[215][41] = 1;
	Matrix[218][38] = 1;
	Matrix[220][36] = 1;
	Matrix[224][33] = 1;
	Matrix[225][32] = 1;
	Matrix[227][28] = 1;
	Matrix[230][26] = 1;
	Matrix[233][23] = 1;
	Matrix[235][22] = 1;
	Matrix[236][21] = 1;
	Matrix[238][19] = 1;
	Matrix[241][16] = 1;
	Matrix[243][13] = 1;
	Matrix[246][11] = 1;
	Matrix[248][8] = 1;
	Matrix[251][6] = 1;//ÖÐ¶Ï
	Matrix[48][208] = -1;
	Matrix[49][209] = -1;
	Matrix[50][206] = -1;
	Matrix[52][204] = -1;
	Matrix[53][205] = -1;
	Matrix[54][202] = -1;
	Matrix[56][200] = -1;
	Matrix[58][198] = -1;
	Matrix[60][196] = -1;
	Matrix[61][197] = -1;
	Matrix[62][193] = -1;
	Matrix[63][194] = -1;
	Matrix[65][191] = -1;
	Matrix[66][192] = -1;
	Matrix[67][189] = -1;
	Matrix[72][184] = -1;
	Matrix[74][182] = -1;
	Matrix[76][180] = -1;
	Matrix[79][176] = -1;
	Matrix[81][174] = -1;
	Matrix[85][170] = -1;
	Matrix[90][166] = -1;
	Matrix[92][164] = -1;
	Matrix[95][160] = -1;
	Matrix[97][158] = -1;
	Matrix[98][159] = -1;
	Matrix[100][155] = -1;
	Matrix[102][153] = -1;
	Matrix[104][151] = -1;
	Matrix[107][148] = -1;
	Matrix[111][145] = -1;
	Matrix[113][143] = -1;
	Matrix[115][141] = -1;
	Matrix[118][138] = -1;
	Matrix[121][135] = -1;
	Matrix[123][133] = -1;
	Matrix[127][129] = -1;
	Matrix[128][130] = -1;
	Matrix[132][126] = -1;
	Matrix[137][121] = -1;
	Matrix[140][118] = -1;
	Matrix[147][110] = -1;
	Matrix[150][107] = -1;
	Matrix[163][95] = -1;
	Matrix[169][88] = -1;
	Matrix[172][84] = -1;
	Matrix[179][79] = -1;
	Matrix[186][72] = -1;
	Matrix[188][70] = -1;
	Matrix[207][50] = -1;
	Matrix[219][39] = -1;
	Matrix[221][37] = -1;
	Matrix[228][29] = -1;
	Matrix[234][24] = -1;
	Matrix[244][14] = -1;
	Matrix[249][9] = -1;
	Matrix[254][2] = -1;	
}




void X_FCSR::clock_Matrix_init()
{
	for (int i = 1; i < 9; i++)
	{
		clock_Matrix[i][0] = 0;
		for (int j = 1; j < 10; j++)
		{
			clock_Matrix[i][j] = (i + 8 * (j - 1)) % 32;
			/*if (clock_Matrix[i][j] == 0)
				clock_Matrix[i][j] = 32;*/
		}
		clock_Matrix[8][4] = clock_Matrix[8][8] = 32;
	}
}



void X_FCSR::register_Key_IV_Load(const u8  key[16], const u8 IV[16])
{
	FCSR_register.state[0] = key[15] | key[14] << 8 | key[13] << 16 | key[12] << 24;
	FCSR_register.state[1] = key[11] | key[10] << 8 | key[9] << 16 | key[8] << 24;
	FCSR_register.state[2] = key[7] | key[6] << 8 | key[5] << 16 | key[4] << 24;
	FCSR_register.state[3] = key[3] | key[2] << 8 | key[1] << 16 | key[0] << 24;
	FCSR_register.state[4] = IV[15] | IV[14] << 8 | IV[13] << 16 | IV[12] << 24;
	FCSR_register.state[5] = IV[11] | IV[10] << 8 | IV[9] << 16 | IV[8] << 24;
	FCSR_register.state[6] = IV[7] | IV[6] << 8 | IV[5] << 16 | IV[4] << 24;
	FCSR_register.state[7] = IV[3] | IV[2] << 8 | IV[1] << 16 | IV[0] << 24;
	FCSR_register.carry[0] = FCSR_register.carry[1] = FCSR_register.carry[2] = FCSR_register.carry[3] = FCSR_register.carry[4] = 0;
	FCSR_register.filter[0] = FCSR_register.filter[1] = FCSR_register.filter[2] = FCSR_register.filter[3] = FCSR_register.filter[4] = 0;
	//FCSR_register.filter[0] = 1;
}







void X_FCSR::register_update()
{
	u32 E;
	u32 t_var1, t_var2;
	int location = 1, value = 0;
	
	for (int i = 1; i < 257; i++)
	{
		for (int j = 1; j < 257; j++)
		{
			if (Matrix[i][j] == 1 || Matrix[i][j] == -1)
			{
				location = j;
				value = Matrix[i][j];
				break;
			}
		}//for j

		switch (value)
		{
		case 1:
		{
			E = ((u32)(FCSR_register.state[location / 33] & (1 << ((location-1) % 32)))) >> ((location - 1) % 32); //A$1=A,$ is one kind of calculate
			break;
		}
		case -1:
		{
			E = ((u32)((FCSR_register.state[location / 33] & (1 << ((location - 1) % 32)))) >> ((location - 1) % 32)) ^ 1;//A$-1=A^1
			break;
		}
		case 0:
		{
			E = 0;		 //A$0=0
		}
		}//for switch
		t_var1 = ((u32)(FCSR_register.state[((i + 1) % 257) / 33] & (1 << (i % 32)))) >> (i % 32);//¼´M£¨i+1£©
		t_var2 = ((u32)(FCSR_register.carry[(i % 257) / 33] & (1 << ((i - 1) % 32)))) >> ((i - 1) % 32);//¼´c(i)
		if (t_var1 ^ t_var2 ^ E)
		{
			FCSR_register.state[i / 33] |= (0x01 << ((i - 1) % 32));
		}
		else
		{
			FCSR_register.state[i / 33] &= (0xFFFFFFFF ^ (0x01 << ((i - 1) % 32)));
		}
		if ((t_var1 & E) ^ (t_var1 & t_var2) ^ (E & t_var2))
		{
			FCSR_register.carry[i / 33] |= (0x01 << ((i - 1) % 32));
		}
		else
		{
			FCSR_register.carry[i / 33] &= 0xFFFFFFFF ^ (0x01 << ((i - 1) % 32));
		}
	}//for i

}








void X_FCSR::register_clock()
{
	u32 t[5];
	for (int i = 0; i < 83; i++)
	{
		register_update();
		for (int j = 1; j < 9; j++)
		{
			t[0] = (((u32)(FCSR_register.state[0] >> (clock_Matrix[j][1] - 1))) & 0x01);
			t[1] = (((u32)(FCSR_register.state[0] >> (clock_Matrix[j][2] - 1) & 0x01))) & (((u32)(FCSR_register.state[0] >> (clock_Matrix[j][3] - 1))) & 0x01);
			t[2] = (((u32)(FCSR_register.state[0] >> (clock_Matrix[j][4] - 1) & 0x01))) & (((u32)(FCSR_register.state[1] >> (clock_Matrix[j][5] - 1))) & 0x01);
			t[3] = (((u32)(FCSR_register.state[1] >> (clock_Matrix[j][6] - 1) & 0x01))) & (((u32)(FCSR_register.state[1] >> (clock_Matrix[j][7] - 1))) & 0x01);
			t[4] = (((u32)(FCSR_register.state[1] >> (clock_Matrix[j][8] - 1) & 0x01))) & (((u32)(FCSR_register.state[2] >> (clock_Matrix[j][9] - 1))) & 0x01);
			t[0] = t[0] ^ t[1] ^ t[2] ^ t[3] ^ t[4];
			if (t[0])
			{
				FCSR_register.state[0] |= (0x01 << (j - 1));
			}
			else
			{
				FCSR_register.state[0]&= (0xFFFFFFFF ^ (0x01<<(j - 1)));
			}					
		}
	}
}







u8 X_FCSR::keystream()
{
	u32 t[5];
	u8 value=0;
	for (int i = 0; i < 83; i++)
	{
		register_update();
		for (int j = 1; j < 9; j++)
		{
			t[0] = (((u32)(FCSR_register.state[0] >> (clock_Matrix[j][1] - 1))) & 0x01);
			t[1] = (((u32)(FCSR_register.state[0] >> (clock_Matrix[j][2] - 1) & 0x01))) & (((u32)(FCSR_register.state[0] >> (clock_Matrix[j][3] - 1))) & 0x01);
			t[2] = (((u32)(FCSR_register.state[0] >> (clock_Matrix[j][4] - 1) & 0x01))) & (((u32)(FCSR_register.state[1] >> (clock_Matrix[j][5] - 1))) & 0x01);
			t[3] = (((u32)(FCSR_register.state[1] >> (clock_Matrix[j][6] - 1) & 0x01))) & (((u32)(FCSR_register.state[1] >> (clock_Matrix[j][7] - 1))) & 0x01);
			t[4] = (((u32)(FCSR_register.state[1] >> (clock_Matrix[j][8] - 1) & 0x01))) & (((u32)(FCSR_register.state[2] >> (clock_Matrix[j][9] - 1))) & 0x01);
			t[0] = t[0] ^ t[1] ^ t[2] ^ t[3] ^ t[4];
			if (t[0])
			{
				value |= (0x01<<(j-1));
			}
			else
			{
				value &= (0xFFFFFFFF ^ (0x01 << (j - 1)));
			}
		}
	}
	return value;
}








void X_FCSR::encrypt(int plain_length, std::vector<u8>plain, std::vector<u8>&ciphertext)
{
	u8 T;
	for (int i = 1; i < 84; i++)
		register_update();
	for (int j = 0; j < plain.size(); j++)
	{
		ciphertext[j] = plain[j] ^ (T=keystream());
		keystream_storage.push_back(T);
	}
}




void X_FCSR::Decrypt(std::vector<u8>ciphertext, std::vector<u8>&plain)
{
	for (int i = 0; i < ciphertext.size(); i++)
		plain[i] = ciphertext[i] ^ keystream_storage[i];
}