#include<iostream>
#include"PreDefine.h"


int main()
{
	u8 input;
	std::vector<u8>plain;
	bool judge = false;
	std::cout << "Please input the Plaintext:";
	do
	{		
		if (std::cin.peek() == ' '&&(judge != true))
		{
			plain.push_back(0);
			judge = true;
		}
		else
		{
			std::cin >> input;
			plain.push_back(input);
			judge = false;
		}
	} while (std::cin.peek() != '\n');
	std::vector<u8>ciphertext(plain.size(),0);
	time_t start_time, end_time;
	u8 testKEY[16] = { 0x00, 0x88 , 0x63 , 0x9d, 0x6b , 0xf8 , 0x47 , 0xed , 0x59 , 0xc6 ,0xFA ,0x27 , 0x08 , 0x98 ,0xE4 ,0x13 };
	u8 testIV[16] = { 0x00 , 0x11 , 0x22 , 0x33 , 0x44 , 0x55 , 0x66 , 0x77 , 0x88 , 0x99 ,0x17 , 0xCB ,0x07 ,0x98 ,0x6c ,0x8E };
	X_FCSR FCSR;
	time(&start_time);
	FCSR.Matrix_init();
	FCSR.clock_Matrix_init();
	FCSR.register_Key_IV_Load(testKEY, testIV);
	FCSR.register_clock();
	FCSR.encrypt(plain.size(), plain,ciphertext);
	std::cout << "The cipher text is listed as follow:" << std::endl;
	for (int j = 0; j < ciphertext.size(); j++)
		printf("0x%x  ", ciphertext[j]);
	FCSR.Decrypt(ciphertext, plain);
	time(&end_time);
	std::cout << std::endl;
	std::cout << "The pain text is listed as follow:" << std::endl;
	for (int j = 0; j < plain.size(); j++)
	{
		if (plain[j]!=0x00)
		{
			std::cout << plain[j];
		}
		else
		{
			std::cout << " ";
		}
	}
	std::cout << std::endl;
	std::cout << difftime(end_time, start_time) << "s" << std::endl;
	/*time(&start_time);//²âÊÔ´úÂë
	std::cout << std::hex << ciphertext[j] << "   ";
	for(int i=0;i<100000;i++)
		FCSR.register_update();
	time(&end_time);
	std::cout << difftime(end_time,start_time);*/
	system("pause");
	return 0;
}