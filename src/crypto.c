#include "stdio.h"
#include "string.h"							// strlen
#include "stdlib.h"							// qsort
#define NUM_ENG_LETT 26
#define DELTA_ENG 32
#define NUM_ASCII_ZERO 48
#define NUM_ASCII_A 65
#define NUM_ASCII_a 97
#define NUM_KEY_1 1							// level -key 0
#define NUM_KEY_2 2							// level -key 1

void replacer(){
	int ch;
	int i;
	char err = 0;
	char flag;
	int mas[2][NUM_ENG_LETT] = {{0},{0}};
	
	if ((ch = getchar()) == '{') {
		i = 0;
		while ((ch = getchar()) != '}'){
			if (i >= NUM_ENG_LETT) {
				printf("\nout of index mas: i=%d\n", i);
				break;
			}
			mas[0][i] = ch;
			i++;
		}			
	} else err = 1;	
	if (err == 0){
		while ((ch = getchar()) != '\n'){		
		}
		if ((ch = getchar()) == '{') {
			i = 0;
			while ((ch = getchar()) != '}'){
				if (i >= NUM_ENG_LETT) {
					printf("\nout of index mas: i=%d\n", i);
					break;
				}
				mas[1][i] = ch;
				i++;		
			}				
		} else err = 2;
	} 
	if (err != 0) printf("\nError read data vector #%d!!! ch =%c\n", err, ch);

	if (err == 0){
		while ((ch = getchar()) != EOF){
			flag = 0;
			for (i = 0; i < NUM_ENG_LETT; i++){ 
				if ((mas[1][i] == ch) || ((mas[1][i]+DELTA_ENG) == ch)){
					putchar(mas[0][i]);
					flag = 1;
					break;
				}
			}
			if (flag == 0) 		
			putchar(ch);
		}
		printf("\n");
	}
}

void help(char *argv[]){
	printf("\n............................Help...................................\n");
	printf("-encode [a]\tEncryption by Offset. a - size of shifting, where 0<=a<=%d.\n", NUM_ENG_LETT-1);
	printf("(-e [a])\n\t\tUse structure:\n\t\t< [input_file.txt] > [output_file.txt]\n");
	printf("\n\t\tFor example:\n\t\t%s -e 5 < input_file.txt > output_file.txt\n", argv[0]);
	printf("\n\n-analysis \tStatistical text analysis by letter.\n(-a)");
	printf("\n\t\tUse structure:\n\t\t< [input_file.txt] > [output_file.txt]\n");
	printf("\n\t\tFor example:\n\t\t%s -a < input_file.txt > output_file.txt\n", argv[0]);
	printf("\n\n-replacer \tReplaces all letters in the modified file. \n");
	printf("(-r)\t\tWhere structure of modified file:\n");
	printf("\t\t{true statistic vector}\n\t\t{false statistic vector}\n\t\t......Encrypted..Data...........\n");
	printf("\n\t\tUse structure:\n\t\t< [input_file.txt] > [output_file.txt]\n");
	printf("\n\t\tFor example:\n\t\t%s -r < input_file.txt > output_file.txt\n", argv[0]);
	printf("\n\n--help    \tInformation on how to use the program.\n");
	printf("-------------------------------------------------------------------\n");	
}
//_____________________________________________________________________________________
////////  				encoder 			///////////////
int exponentiation(int a, int b){
	int i, z;
	
	z = 1;
	for (i = 0;  i < b; i++){
		z = z * a;
	}
	if (b == 0) return 1;
	return z;
}

void encoder(int argc, char *argv[]){
	int ch, ch_sh;	
	char i, j;
	int num;
	int length;

	if (argc == 3){
		length = strlen(argv[NUM_KEY_2]);		// length of string
		num = 0;
		i = 0;
		j = length - 1;
		while (i < length){				// convert char string to int number
			num = num + (argv[NUM_KEY_2][i]-NUM_ASCII_ZERO)*exponentiation(10, j);
			i++;
			j--;
		}
		if ((num < 0) || (num >= NUM_ENG_LETT)){	// not cycle shifting
			printf("Error key! %d\n", num);
			num = -1;
		}
		if (num != -1){
			while ((ch = getchar()) != EOF){	// reading, shifting and writing letter
				if (((ch >= NUM_ASCII_A) && (ch < (NUM_ASCII_A+NUM_ENG_LETT))) 
				|| ((ch >= NUM_ASCII_a) && (ch < (NUM_ASCII_a+NUM_ENG_LETT)))){
					ch_sh = ch + num;
					if (((ch_sh >= NUM_ASCII_A) && (ch_sh < (NUM_ASCII_A+NUM_ENG_LETT))) 
					|| ((ch_sh >= NUM_ASCII_a) && (ch_sh < (NUM_ASCII_a+NUM_ENG_LETT)))){
						putchar(ch_sh);
					} else putchar(ch_sh - NUM_ENG_LETT);
				} else putchar(ch);
			}
		}
	} else printf("Error key, if you need help use syntax whith key:\n%s --help\n", argv[0]);

}
//_____________________________________________________________________________________
//_____________________________________________________________________________________
////////  				analysis 			///////////////
void output_data(long long count, int mas[2][NUM_ENG_LETT], int *vect_l){
	int i;
	printf("Number letter in file: %lli \n", count);
	printf("--------------------------\n");			// head output data
	printf("Letter |   Num   |   %%   |\n");		//
	printf("--------------------------\n");			//
	for (i = 0; i < NUM_ENG_LETT; i++){			// output data
		printf("  %c+%c  | %7.1d | %5.2f |\n", mas[0][i], mas[0][i]+DELTA_ENG, mas[1][i], 
			((float)mas[1][i]/(float)count*100.0));
	}
	printf("Please insert this vector to the beginning of the encrypted file (with symbol \'{\' and \'}\'):\n");	
	putchar('{');
	for (i = 0; i < NUM_ENG_LETT; i++){
		//printf("%d ", vect_l[i]);
		putchar(vect_l[i]);
	}
	putchar('}');
	printf("\n");		
}

void read_count(long long *count, int mas[2][NUM_ENG_LETT]){	// *pointer
	int i;
	int ch;
	for (i = 0; i< NUM_ENG_LETT; i++){			// ascii initialization
		mas[0][i] = i+'A';
	}
	
	while ((ch = getchar()) != EOF){			// count letters
		for (i = 0; i< NUM_ENG_LETT; i++){
			if (((int)ch == mas[0][i]) || ((((int)ch-DELTA_ENG) == mas[0][i]))){
				mas[1][i] = mas[1][i] + 1;
				*count= *count + 1;
				break;
			}
			if (ch == '\n') break;			// delete excess iteration	
		}
	}
}

int compare(const void *a, const void *b){
	return *(int*)b - *(int*)a;			//???? wtf *(int*)??
}

void vect_stat_letter(int *vect_l,int mas[2][NUM_ENG_LETT]){

	int i,j;
	int vect_buf[NUM_ENG_LETT]={0};
	
	for (i = 0; i < NUM_ENG_LETT; i++){
		vect_buf[i] = mas[1][i];
	}

	qsort(vect_buf, NUM_ENG_LETT, sizeof(int), compare);

	for (i = 0; i < NUM_ENG_LETT; i++){
		for (j = 0; j < NUM_ENG_LETT; j++){
			if (vect_buf[i] == mas[1][j]){
				vect_l[i] = mas[0][j];			
			}
		}
	}
}

void analysis(){
	long long count = 0;
	int mas[2][NUM_ENG_LETT] = {{0},{0}};			//  initialization of zero value
	int vect_l[NUM_ENG_LETT]={0};
	
	read_count(&count, mas);				// count nuber all letters	
	vect_stat_letter(vect_l, mas);
	output_data(count, mas, vect_l);			// print formated output data
}
//_______________________________________________________________________________________

void main(int argc, char *argv[]){
	char flag = 0;	
	

	if (argc > 1){
		if (strcmp(argv[NUM_KEY_1], "--help") == 0){			// help
			help(argv);
			flag = 1;
		}
		if ((strcmp(argv[NUM_KEY_1], "-encode") == 0) || (strcmp(argv[NUM_KEY_1], "-e") == 0)){	// encoder
			encoder(argc, argv);
			flag = 1;
		}
		if ((strcmp(argv[NUM_KEY_1], "-analysis") == 0) || (strcmp(argv[NUM_KEY_1], "-a") == 0)){// analysis
			analysis();	// not work
			flag = 1;
		}
		if ((strcmp(argv[NUM_KEY_1], "-replacer") == 0) || (strcmp(argv[NUM_KEY_1], "-r") == 0)){// replacer
			replacer();
			flag = 1;
		}		
		if (flag == 0) printf("Error key, if you need help use syntax whith key:\n%s --help\n", argv[0]);
	} else printf("Error key, if you need help use syntax whith key:\n%s --help\n", argv[0]);
}

