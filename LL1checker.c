#include<stdio.h>
#include<string.h>
#define TSIZE 128

// table[i][j] stores
// the index of production that must be applied on
// ith varible if the input is
// jth nonterminal
int table[100][TSIZE];

// stores all list of terminals
// the ASCII value if use to index terminals
// terminal[i] = 1 means the character with
// ASCII value is a terminal
char terminal[TSIZE];

// stores all list of terminals
// only Upper case letters from 'A' to 'Z'
// can be nonterminals
// nonterminal[i] means ith alphabet is present as
// nonterminal is the grammar
char nonterminal[26];

// structure to hold each production
// str[] stores the production
// len is the length of production
struct product {
	char str[100];
	int len;
}pro[20];

// no of productions in form A->ß
int no_pro;


char first[26][TSIZE];
char follow[26][TSIZE];

// stores first of each production in form A->ß
char first_rhs[100][TSIZE];

// check if the symbol is nonterminal
int isNT(char c) {
	return c >= 'A' && c <= 'Z';
}

// reading data from the file
void readFromFile() {

	FILE* fptr;
	fptr = fopen("text.txt", "r");
	char buffer[255];
	int i;
	int j;
	while (fgets(buffer, sizeof(buffer), fptr)) {
		printf("%s", buffer);
		j = 0;
		nonterminal[buffer[0] - 'A'] = 1;
		for (i = 0; i < strlen(buffer) - 1; ++i) {
			if (buffer[i] == '|') {
				++no_pro;
				pro[no_pro - 1].str[j] = '\0';
				pro[no_pro - 1].len = j;
				pro[no_pro].str[0] = pro[no_pro - 1].str[0];
				pro[no_pro].str[1] = pro[no_pro - 1].str[1];
				pro[no_pro].str[2] = pro[no_pro - 1].str[2];
				j = 3;
			}
			else {
				pro[no_pro].str[j] = buffer[i];
				++j;
				if (!isNT(buffer[i]) && buffer[i] != '-' && buffer[i] != '>') {
					terminal[buffer[i]] = 1;
				}
			}
		}
		pro[no_pro].len = j;
		++no_pro;
	}

}

void add_FIRST_A_to_FOLLOW_B(char A, char B) {
	int i;
	for (i = 0; i < TSIZE; ++i) {
		if (i != '^')
			follow[B - 'A'][i] = follow[B - 'A'][i] || first[A - 'A'][i];
	}
}

void add_FOLLOW_A_to_FOLLOW_B(char A, char B) {
	int i;
	for (i = 0; i < TSIZE; ++i) {
		if (i != '^')
			follow[B - 'A'][i] = follow[B - 'A'][i] || follow[A - 'A'][i];
	}
}

void FOLLOW() {

	int t = 0;
	int i, j, k, x;
	while (t++ < no_pro) {
		for (k = 0; k < 26; ++k) {
			if (!nonterminal[k])	continue;
			char nt = k + 'A';
			for (i = 0; i < no_pro; ++i) {
				for (j = 3; j < pro[i].len; ++j) {
					if (nt == pro[i].str[j]) {
						for (x = j + 1; x < pro[i].len; ++x) {
							char sc = pro[i].str[x];
							if (isNT(sc)) {
								add_FIRST_A_to_FOLLOW_B(sc, nt);
								if (first[sc - 'A']['^'])
									continue;
							}
							else {
								follow[nt - 'A'][sc] = 1;
							}
							break;
						}
						if (x == pro[i].len)
							add_FOLLOW_A_to_FOLLOW_B(pro[i].str[0], nt);
					}
				}
			}
		}
	}
}

void add_FIRST_A_to_FIRST_B(char A, char B) {
	int i;
	for (i = 0; i < TSIZE; ++i) {
		if (i != '^') {
			first[B - 'A'][i] = first[A - 'A'][i] || first[B - 'A'][i];
		}
	}
}

void FIRST() {
	int i, j;
	int t = 0;
	while (t < no_pro) {
		for (i = 0; i < no_pro; ++i) {
			for (j = 3; j < pro[i].len; ++j) {
				char sc = pro[i].str[j];
				if (isNT(sc)) {
					add_FIRST_A_to_FIRST_B(sc, pro[i].str[0]);
					if (first[sc - 'A']['^'])
						continue;
				}
				else {
					first[pro[i].str[0] - 'A'][sc] = 1;
				}
				break;
			}
			if (j == pro[i].len)
				first[pro[i].str[0] - 'A']['^'] = 1;
		}
		++t;
	}

}

void add_FIRST_A_to_FIRST_RHS__B(char A, int B) {
	int i;
	for (i = 0; i < TSIZE; ++i) {
		if (i != '^')
			first_rhs[B][i] = first[A - 'A'][i] || first_rhs[B][i];
	}
}

// Calculates FIRST(ß) for each A->ß
void FIRST_RHS() {
	int i, j;
	int t = 0;
	while (t < no_pro) {
		for (i = 0; i < no_pro; ++i) {
			for (j = 3; j < pro[i].len; ++j) {
				char sc = pro[i].str[j];
				if (isNT(sc)) {
					add_FIRST_A_to_FIRST_RHS__B(sc, i);
					if (first[sc - 'A']['^'])
						continue;
				}
				else {
					first_rhs[i][sc] = 1;
				}
				break;
			}
			if (j == pro[i].len)
				first_rhs[i]['^'] = 1;
		}
		++t;
	}

}

// function to check if grammar is LL(1)
void checkLL1Grammar(){
	int flag = 0;
	int i,j,k;
	int firstCnt[TSIZE];
	int p;
	i = 0;
	while(i<no_pro){
		// p is used to store index
		// of production that derives '^'
		p = -1;
		flag = 0;
		memset(firstCnt,0,sizeof(firstCnt));
		
		// applying rule 1 and 2
		// check if there exist productions A->a|b
		// such that a and b have common 
		// terminals in FIRST
		for(j=0;j<TSIZE;++j){
			for(k=i;k<no_pro;++k){
				if(pro[k].str[0]==pro[i].str[0]){
					firstCnt[j] += first_rhs[k][j];
					if(first_rhs[k]['^'])
						p = k;
				}
				else{
					break;
				}
			}
			if(firstCnt[j]>1){
				flag = 1;
				break;
			}
		}
		
		// applying rule 3
		// flag==0 means rule 1 and 2 are satisfied
		// p != -1 means there is a production
		// A->a for variable A such that FIRST(a) contains '^'
		if(flag==0&&p!=-1){
			for(j=0;j<TSIZE;++j){
				firstCnt[j] -= first_rhs[p][j];
				firstCnt[j] += follow[pro[i].str[0]-'A'][j];
				if(firstCnt[j]>1){
					flag = 1;
					break;
				}
			}
		}
		
		if(flag==1){
			break;
		}
		
		i = k;
	}
	
	if(flag==0)
		printf("\nGiven Grammar is LL(1)\n");
	else
		printf("\nGiven Grammar is not LL(1)\n");
}

int main() {
	readFromFile();

	follow[pro[0].str[0] - 'A']['$'] = 1;

	FIRST();
	FOLLOW();
	FIRST_RHS();
	int i, j, k;
	
	// display first of each variable
	printf("\n");
	for (i = 0; i < no_pro; ++i) {
		if (i == 0 || (pro[i - 1].str[0] != pro[i].str[0])) {
			char c = pro[i].str[0];
			printf("FIRST OF %c: ", c);
			for (j = 0; j < TSIZE; ++j) {
				if (first[c - 'A'][j]) {
					printf("%c ", j);
				}
			}
			printf("\n");
		}
	}
	
	// display follow of each variable
	printf("\n");
	for (i = 0; i < no_pro; ++i) {
		if (i == 0 || (pro[i - 1].str[0] != pro[i].str[0])) {
			char c = pro[i].str[0];
			printf("FOLLOW OF %c: ", c);
			for (j = 0; j < TSIZE; ++j) {
				if (follow[c - 'A'][j]) {
					printf("%c ", j);
				}
			}
			printf("\n");
		}
	}

	// display first of each variable ß
	// in form A->ß
	printf("\n");
	for (i = 0; i < no_pro; ++i) {
		printf("FIRST OF %s: ", pro[i].str);
		for (j = 0; j < TSIZE; ++j) {
			if (first_rhs[i][j]) {
				printf("%c ", j);
			}
		}
		printf("\n");
	}
	
	checkLL1Grammar();

}