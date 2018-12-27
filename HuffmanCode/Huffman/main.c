#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)；

#include "stdio.h"
#include "Huffman.h"
#include "minheap.h"


int main() {

	FILE *infile = NULL;
	FILE *outfile = NULL;


	unsigned int i = 0;
	unsigned int data = 0,weight = 0;
	char infilename[64] = "1.txt";
	char outfilename[64] = "2.txt";
	char defilename[64] = "3.txt";

	//printf("请输入要压缩的文件名:\n");
	//scanf("%s",filename);
	//infile = fopen(infilename, "r");

	//if (infile == NULL) {
	//	fprintf(stderr,"can't open file \"%s\"\n", infilename);
	//}

	//


	//outfile = fopen(outfilename, "w+b");
	//if (outfile == NULL) {
	//	fprintf(stderr, "can't open file \"%s\\n", outfile);
	//	return (EXIT_FAILURE);
	//}

	
	HuffmanEncode(infilename, outfilename, defilename);
	
	
	system("pause");

	return 0;
}
