#ifndef _Huffman_H_
#define _Huffman_H_

#include "binarytree.h"
#include "def.h"


#define HUFFMAN_DEBUG


typedef struct {
	unsigned char symbol[256];
	unsigned int  frequence[256];
	unsigned int totalnum;
}SymbolTable;

#define HuffmanNode struct huffmannode

typedef struct huffmannode{
	unsigned int *data;
	unsigned int *weight;

	HuffmanNode *parent;
	HuffmanNode *leftchild;
	HuffmanNode *rightchild;
};


typedef struct {
	HuffmanNode *root;
	HuffmanNode *node_array;
	unsigned int symbolnum;    //∑˚∫≈÷÷¿‡ ˝
}HuffmanTree;

typedef struct {
	unsigned char *symbol;
	unsigned int size;
	unsigned char *word;
}CodeWord;

typedef struct {
	CodeWord *codeword;
	unsigned int cur_word;
}CodeWordBuf;


SymbolTable *CountSymbols(FILE *infile);
HuffmanTree *HuffmanTreeCreate(SymbolTable *symboltable);
void HuffmanTreeExplore(HuffmanNode *node, unsigned int depth, CodeWordBuf *codeword_buf);
void HuffmanEncode(char *infilename, char *outfilename, char *decompressfile);
#endif