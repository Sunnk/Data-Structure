#include "Huffman.h"
#include "PriorityQuery.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)；

/*
	统计文件中频次
*/
SymbolTable *CountSymbols(FILE *infile) {

	SymbolTable *operate_symboltable = NULL;
	unsigned char *temp_symbol = NULL;
	unsigned int i = 0;

	operate_symboltable = (SymbolTable *)malloc(sizeof(SymbolTable));

	for (i = 0; i < 256; i++) {
		operate_symboltable->symbol[i] = i;
		operate_symboltable->frequence[i] = 0;
	}
	operate_symboltable->totalnum = 0;

	temp_symbol = malloc(sizeof(unsigned char));

	while (fread(temp_symbol, 1, 1, infile)) {  //文件末尾没有读到EOF？
		operate_symboltable->frequence[*temp_symbol]++;	
		operate_symboltable->totalnum++;
	}

#ifdef HUFFMAN_DEBUG

	printf("  symbols  |  frequence\n");

	for (i = 0; i < 256; i++) {
		if(operate_symboltable->frequence[i] != 0)
			printf("%5c       %5d\n", operate_symboltable->symbol[i], operate_symboltable->frequence[i]);
	}

#endif 

	return operate_symboltable;
}

HuffmanTree *HuffmanTreeCreate(SymbolTable *symboltable) {
	PriorityQuery *priorityqueue = NULL;
	HuffmanTree *huffmantree = NULL;
	HuffmanNode *temp ;

	unsigned int  i = 0;
	unsigned int index = 0;
	unsigned int symbolnum = 0;
	unsigned int weight = 0;
	for (i = 0; i < 256; i++) {
		if (symboltable->frequence[i] > 0) {
			symbolnum++;
		}
	}

	huffmantree = (HuffmanTree *)malloc(sizeof(HuffmanTree));

	huffmantree->node_array = (HuffmanNode *)malloc(symbolnum * sizeof(HuffmanNode));
	huffmantree->root = (HuffmanNode *)malloc(symbolnum * sizeof(HuffmanNode));
	huffmantree->symbolnum = symbolnum;

	for (i = 0; i < symbolnum; i++) {
		huffmantree->node_array[i].data = (unsigned int *)malloc(sizeof(unsigned int));
		huffmantree->node_array[i].weight = (unsigned int *)malloc(sizeof(unsigned int));
		huffmantree->node_array[i].leftchild = NULL;//(HuffmanNode *)malloc(sizeof(HuffmanNode));
		huffmantree->node_array[i].rightchild = NULL;//(HuffmanNode *)malloc(sizeof(HuffmanNode));
		huffmantree->node_array[i].parent = NULL;//(HuffmanNode *)malloc(sizeof(HuffmanNode));
	}


	for (i = 0 , symbolnum=0; i < 256; i++) {
		if (symboltable->frequence[i] > 0) {
			temp = &huffmantree->node_array[symbolnum];
			*(temp->data) = (char)symboltable->symbol[i];
			*(temp->weight) = (unsigned int)symboltable->frequence[i];
			//printf("huffmantree->node_array[%d].weight = %d\n", symbolnum,*huffmantree->node_array[symbolnum].weight);
			//printf("weight[%d] = %d\n", i, symboltable->frequence[i]);
			symbolnum++;
		}
	}

	priorityqueue = CreatePriorityQuery();

	for (i = 0; i < symbolnum; i++) {
		//printf("weight = %d\n", *huffmantree->node_array[i].weight);
		PriorityQueryEnqueue(priorityqueue,&huffmantree->node_array[i], *huffmantree->node_array[i].weight);

	}


	index = 0;
	while (!(priorityqueue->miniumheap->symbolnum == 1)){

		HuffmanNode *newnode1 ;
		HuffmanNode *newnode2 ;
		HuffmanNode *root = (HuffmanNode *)malloc(sizeof(HuffmanNode));

		//取出两个最小的元素
		PriorityQueryDequeue(priorityqueue, &newnode1, &weight);
		PriorityQueryDequeue(priorityqueue, &newnode2, &weight);

		root->leftchild = newnode1;
		root->rightchild = newnode2;

		root->data = (unsigned int *)malloc(sizeof(unsigned int));
		root->weight = (unsigned int *)malloc(sizeof(unsigned int));
		
		newnode1->parent = root;
		newnode2->parent = root;

		//printf("newnode1.weight = %d\n",*(newnode1->weight));
		//printf("newnode2.weight = %d\n", *(newnode2->weight));


		//构造树
		*(root->weight) = *(newnode1->weight) + *(newnode2->weight);

		//入队列
		PriorityQueryEnqueue(priorityqueue,root, *(root->weight));


		index++;

	}

	PriorityQueryDequeue(priorityqueue,&huffmantree->root,&weight);

	huffmantree->root->parent = NULL;

#ifdef HUFFMAN_DEBUG

#endif // HUFFMAN_DEBUG


	return huffmantree;

}


/*
	探索霍夫曼编码树，要求CodeWordBuf已经初始化好
*/
void HuffmanTreeExplore(HuffmanNode *node, unsigned int depth,CodeWordBuf *codeword_buf) {

	if (node->leftchild != NULL) {
		HuffmanTreeExplore(node->leftchild,depth+1, codeword_buf);
	}

	if (node->rightchild != NULL) {
		HuffmanTreeExplore(node->rightchild, depth + 1, codeword_buf);
	}

	if (node->leftchild == NULL && node->rightchild == NULL) {
		
		codeword_buf->codeword[codeword_buf->cur_word].symbol = node->data;
		codeword_buf->codeword[codeword_buf->cur_word].size = depth;

		codeword_buf->codeword[codeword_buf->cur_word].word = (unsigned char *)malloc(depth * sizeof(unsigned char));

		HuffmanNode *cur_node, *parent_node;
		unsigned int i = depth - 1;

		for (cur_node = node, parent_node = node->parent; parent_node != NULL; cur_node = parent_node, parent_node = parent_node->parent) {

			if (parent_node->leftchild == cur_node)
				codeword_buf->codeword[codeword_buf->cur_word].word[i] = 1;
			else
				codeword_buf->codeword[codeword_buf->cur_word].word[i] = 0;

			i--;
		}

		codeword_buf->cur_word++;
	}

}
char GetBit(char byte, char num) {
	if (num == 0)
		return (char)(byte & 0x01);
	else if(num == 1)
		return (char)((byte & 0x02) >> 1);
	else if (num == 2)
		return (char)((byte & 0x04) >> 2);
	else if (num == 3)
		return (char)((byte & 0x08) >> 3);
	else if (num == 4)
		return (char)((byte & 0x10) >> 4);
	else if (num == 5)
		return (char)((byte & 0x20) >> 5);
	else if (num == 6)
		return (char)((byte & 0x40) >> 6);
	else if (num == 7)
		return (char)((byte & 0x80) >> 7);
}


/*
	生成码表
*/
void HuffmanEncode(char *infilename,char *outfilename,char *decompressfile) {

	FILE *infile = NULL;
	FILE *outfile = NULL;
	FILE *defile = NULL;

	HuffmanTree *operate_huffmantree = NULL;
	CodeWordBuf *operate_codewordbuf = NULL;
	SymbolTable *operate_symboltable = NULL;

	unsigned char *temp_symbol =(unsigned char *) malloc(sizeof(unsigned char));
	unsigned int index = 0;  //记录当前读取的文件中所读到的字符对应码表中的位置
	unsigned int write_index = 7;//记录待向文件中写入的字符中的几位有效
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned char code = 0;//待向文件中写入的字符

	infile = fopen(infilename, "r");

	operate_symboltable = CountSymbols(infile);

	//fclose(infile);

	operate_huffmantree = HuffmanTreeCreate(operate_symboltable);
	operate_codewordbuf = (CodeWordBuf *)malloc(sizeof(CodeWordBuf));

	operate_codewordbuf->codeword = (CodeWord *)malloc(operate_huffmantree->symbolnum * sizeof(CodeWord));
	operate_codewordbuf->cur_word = 0;

	HuffmanTreeExplore(operate_huffmantree->root,0, operate_codewordbuf);

#ifdef HUFFMAN_DEBUG
	printf("经过霍夫曼编码后结果为：\n");

	for (i = 0; i < operate_codewordbuf->cur_word; i++) {
		printf("符号为： %c   码字为：", (char)*operate_codewordbuf->codeword[i].symbol);
		
		for (j = 0; j < operate_codewordbuf->codeword[i].size; j++) {
			printf("%d", operate_codewordbuf->codeword[i].word[j]);
		}

		printf("\n");
	}
#endif
	
	//infile = fopen(infilename, "r");
	//if (infile == NULL) {
	//	fprintf(stderr, "can't open file \"%s\"\n", infilename);
	//}

	fseek(infile,0,SEEK_SET);
	
	outfile = fopen(outfilename, "w+b");

	printf("经过霍夫曼编码后的比特流为 ： \n");
	
	while (fread(temp_symbol, 1, 1, infile)) {  //文件末尾没有读到EOF？
		
		for (i = 1; *temp_symbol != *operate_codewordbuf->codeword[i-1].symbol;i++) {

		}

		index = i - 1;

		for (i = 0; i < operate_codewordbuf->codeword[index].size; i++) {
			if (write_index != 0 ) {
				unsigned int temp = operate_codewordbuf->codeword[index].word[i];
				printf("%d", operate_codewordbuf->codeword[index].word[i]);
				code = code  | (unsigned char)(temp << write_index);
				write_index--;
			}
			else if (write_index == 0) {
				unsigned int temp = operate_codewordbuf->codeword[index].word[i];
				printf("%d", operate_codewordbuf->codeword[index].word[i]);
				code = code | (unsigned char)(temp);
				write_index = 7;

				fwrite(&code,sizeof(unsigned char),1,outfile);
				code = 0;
			}
		}

	}

	if (write_index != 7) {
		fwrite(&code, sizeof(unsigned char), 1, outfile);
	}

	printf("\n\n");

	fclose(outfile);
	fclose(infile);

	outfile = fopen(outfilename, "r+b");

	defile = fopen(decompressfile, "w+b");

	unsigned char inbyte = 0;
	char inbyte_index = 7;//当前处理字节比特的位置
	unsigned int temp_byte = 0;
	HuffmanNode *curnode;

	i = 0;

	fread(&inbyte, 1, 1, outfile);


	printf("经过解码后的比特流为 ： \n");
	while (i < operate_symboltable->totalnum) {
		curnode = operate_huffmantree->root;
		
		while (1) {
			
			temp_byte = GetBit(inbyte, inbyte_index);
			inbyte_index--;
			if (inbyte_index == -1) {
				fread(&inbyte, 1, 1, outfile);
				inbyte_index = 7;
			}
				
			
			if (temp_byte)
				curnode = curnode->leftchild;
			else
				curnode = curnode->rightchild;

			//printf("%d", temp_byte);

			if (curnode->leftchild == NULL) {
				printf("%c", *curnode->data);
				fwrite(curnode->data, sizeof(unsigned char), 1, defile);
				i++;
				break;
			}


		}
	}

	printf("\n");

	fclose(outfile);
	fclose(defile);

	
	//int32_t inbyte;
	//uint8_t byte_bit_count;/**< 一个码流字节中，当前处理的比特的位置 */
	//uint8_t byte_mask;/**< 用于选择字节中的比特位 */
	//uint32_t index;
	//uint32_t byte_num = 0;
	//BTNode *current_node;

	//byte_bit_count = 8;

	//for (index = 0; index < operate_huffmantree->symbolnum; index++) {
	//	/**< 根据码流的指示，从树的根节点往下走到叶节点*/
	//	current_node = operate_huffmantree->root;
	//	for (;; ) {
	//		if (byte_bit_count == 8) {/**若已处理的比特数等于8，表示一个码流字节处理完毕*/
	//			inbyte = fgetc(infile);/**从压缩文件读入一新码流字节*/
	//			if (inbyte == EOF) {
	//				goto game_over;
	//			}
	//			byte_bit_count = 0;/**< 当前处理比特数复位到0，开始处理新码流字节*/
	//			byte_mask = 0x80;/**< 从码流字节的高位开始处理 */
	//		}

	//		/**< 测试当前比特，决定走向*/
	//		if (inbyte & byte_mask)
	//			current_node = current_node->left_child;
	//		else
	//			current_node = current_node->right_child;
	//		byte_bit_count++;
	//		byte_mask >>= 1;

	//		/**< 到达叶节点*/
	//		if (current_node->left_child == NULL) {
	//			byte_num++;
	//			/**将叶节点中的符号写入解压缩文件*/
	//			fputc(((Symbol *)(current_node->data))->ascii, outfile);

	//			break;
	//		}
	//	}
	//}


}



