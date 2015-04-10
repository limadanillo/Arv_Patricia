/*
 * paty.c
 *
 *  Created on: 23/03/2015
 *      Author: Danillo
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>


struct nodo {
	char *prefixo, *flag;
	struct nodo *p[26];
};

struct nodo *root = NULL;

/*
 *
 */

inserir(char *palavra, struct nodo **p) {
	int i, j;

	if (*p == NULL) {
		(*p) = calloc(1, sizeof(struct nodo));
		(*p)->prefixo = strdup(palavra);
		(*p)->flag = calloc(strlen(palavra) + 1, sizeof(char));
		(*p)->flag[strlen(palavra)] = 1;
	}

	for (i = 0; i < strlen((*p)->prefixo); i++)
		if (palavra[i] != (*p)->prefixo[i])
			break;

	if (i < strlen((*p)->prefixo)) {
		if (palavra[i] == '\0')
			(*p)->flag[i] = 1;
		else {
			struct nodo *pai = calloc(1, sizeof(struct nodo));
			pai->prefixo = strndup((*p)->prefixo, i);
			pai->flag = calloc(i + 1, sizeof(char));

			for (j = 0; j <= i; j++)
				pai->flag[j] = (*p)->flag[j];

			inserir(palavra + i + 1, &pai->p[palavra[i] - 'a']);
			pai->p[(*p)->prefixo[i] - 'a'] = *p;
			j = (strlen((*p)->prefixo) - i) * sizeof(char); // ver se é +1 ou +i

			memmove((*p)->prefixo, (*p)->prefixo + i + 1, j);
			(*p)->prefixo = realloc((*p)->prefixo, j);

			memmove((*p)->flag, (*p)->flag + i + 1, j);
			(*p)->flag = realloc((*p)->flag, j);

			*p = pai; //seta o root como pai

		}
	} else if (palavra[i] == '\0') {
		(*p)->flag[i] = 1;
	} else {
		for (j = 0; j < 26; j++)
			if ((*p)->p[j] != NULL)
				break;
		if (j < 26)
			inserir(palavra + i + 1, &(*p)->p[palavra[i] - 'a']);
		else { //aumenta o prefixo
			(*p)->flag = realloc((*p)->flag, strlen(palavra) + 1);
			for (j = strlen((*p)->prefixo) + 1; j < strlen(palavra); j++)
				(*p)->flag[j] = 0;
			(*p)->flag[j] = 1;
			free((*p)->prefixo);

			(*p)->prefixo = strdup(palavra);
		}
	}
}

void Imprimir(struct nodo **p,int m) {
    int i, count =0;
    char temp;

    //caso de arvore vazia
    if (p == NULL) {
        printf("[]");
        return;
    }
    int tam_prefixo = strlen((*p)->prefixo);
    if (m == 1)printf("[");
    for (i = 0; i < tam_prefixo; ++i) {
        if ((*p)->flag[i + 1] != 1)
            printf("%c", ((*p)->prefixo[i]));
        else {
            temp = toupper((*p)->prefixo[i]);
            printf("%c", temp);
        }
    }
    for (i = 0; i < 26; i++) {
        if ((*p)->p[i] != NULL) {
            printf("[");
            //primeiro caso
            if ((*p)->p[i]->flag[0] == 1) {

                printf("%c", i + 65); //maiusculas
            } else if((strlen((*p)->p[i]->prefixo) == 0 && (*p)->p[i]->flag[0] == 1)) {
                printf("%c", i + 97); //minuscula
            }
		else {
                printf("%c", i + 97); //minuscula
            }
             
            Imprimir(&((*p)->p[i]),0);
        }
    }
    printf("]");
}
int main(int argc , char *argv[]) {
	struct nodo *p = NULL;
	char str[255];
	
	
	while( scanf("%s", &str) != EOF ){
	 
	 	inserir(str,&p);
		
		
	}
	Imprimir(&p, 1);
	printf("\n");
	
	return 0;
}


