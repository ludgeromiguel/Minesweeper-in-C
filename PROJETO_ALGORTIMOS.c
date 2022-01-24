#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void ordenar_pontuacoes();

void ler_dimensoes(int *x, int *y){
	printf("Digite as dimensoes do campo:\n");
	scanf("%d %d",x,y);
	if((*y > 20) || (*x > 20)){
		printf("Nao pode ultrapassar o limite de (%d) linhas ou colunas!\n",20);
		ler_dimensoes(x,y);
	}
	else if((*y < 0) || (*x < 0)){
		printf("O valor de linhas e colunas precisa ser positivo!\n");
		ler_dimensoes(x,y);
	}
}

void ler_nivel(int *x,int *y, int *n){
	int res_menu;
	printf("\n\nDigite o nivel pretendido: \n\n Facil(opcao 1) \n Medio(opcao 2) \n Dificil(opcao 3)\n\n  - ");
	scanf("%d", &res_menu);
	while(res_menu != 1 && res_menu != 2 && res_menu != 3)
	{
		printf("Opção inválida. Por favor digite 1 ou 2 ou 3 consoante o que pretende. ");
		scanf("%d", &res_menu);
	}
	if(res_menu==1){
		*x = 5;
		*y = 5;
		*n = 2;
	}else if(res_menu==2){
		*x = 10;
		*y = 10;
		*n = 4;
	}else{
		*x = 20;
		*y = 20;
		*n = 10;
	}
}

void ler_minas(int *n, int x, int y){
	printf("Digite a quantidade de minas:\n");
	scanf("%d",n);
	if(*n > ((x*y)/2)){
		printf("Muitas minas para o campo desejado.\n");
		ler_minas(n,x,y);
	}
	else if(*n < 0){
		printf("A quantidade de minas precisa ser positiva.\n");
		ler_minas(n,x,y);
	}
}

void sortear_mina(char campo[20][20], int x, int y){
	int x_m = rand() % x, y_m = rand() % y;
	if(campo[x_m][y_m] == 'm')
		sortear_mina(campo,x,y);
	else
		campo[x_m][y_m] = 'm';
}

void preencher_minas(char campo[20][20], int n, int x, int y){
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			campo[i][j] = ' ';

	for(i=0;i<n;i++)
		sortear_mina(campo,x,y);
}

void exibir_campo(char campo[][20], int x, int y, int minas){     
	int i,j;
	char lin = 'A',col = 'A';

	printf("Display do campo:    ( %d minas)\n ", minas);
	for(i=0;i<y;i++,col++)
	{
		printf(" %c",col);
	}
	printf("\n");
	
	for(i=0;i<x;i++,lin++){   //vai printar no começo o A na esquerda dps quando o i for e percorrer tudo o B etc   
		printf("%c ",lin);
		for(j=0;j<y;j++)      // vai meter os espaços em branco entre os A's ou B's na linha
		{
			printf("%c ",campo[i][j]);  
		}
		printf("%c ",lin);   //printa agora o A do lado direito ao percorrer a linha
		printf("\n");        // dá um new line e passa para o B
	}
	printf(" ");
	for(i=0,col='A';i<y;i++,col++)  //printa as colunas da parte inferior do campo.
		printf(" %c",col);
	printf("\n");
	
}

void contar_vizinhos(char campo[][20], int x, int y){
	int i,j;
	char n;
	for(i=0;i<x;i++)
		for(j=0;j<y;j++){
			n = '0';
			if(campo[i][j]!='m'){
				if(j-1>=0 && campo[i][j-1]=='m')
					n++;
				if(j+1<y && campo[i][j+1]=='m')
					n++;
				if(i+1<x && j-1>=0 &&campo[i+1][j-1]=='m')
					n++;
				if(i+1<x && j+1<y && campo[i+1][j+1]=='m')
					n++;
				if(i-1>=0 && j-1>=0 &&campo[i-1][j-1]=='m')
					n++;
				if(j+1<y && i-1>=0 && campo[i-1][j+1]=='m')
					n++;
				if(i+1<x && campo[i+1][j]=='m')
					n++;
				if(i-1>=0 && campo[i-1][j]=='m')
					n++;
				if(n!='0')
					campo[i][j]=n;
			}
		}
}	

void preencher_jogo(char jogo[][20], int x, int y){
	int i,j;
	for(i=0;i<x;i++)
		for(j=0;j<y;j++)
			jogo[i][j] = '_';
}

void escolher_coordenada(char * cx, char * cy, int x, int y){
	int xmax=(int)'A'+x-1, ymax=(int)'A'+y-1;
	printf("Escolha a coordenada (linha e coluna):\n");
	scanf(" %c %c",cx,cy);
	if((*cx<'A')||((int)*cx>xmax)||(*cy<'A')||((int)*cy>ymax)){
		printf("Coordenadas invalidas! Escolha de novo.\n");
		escolher_coordenada(cx,cy,x,y);
	}
}

void abrir_ou_marcar(char * c){
	printf("Abrir ou marcar mina? A = abrir, M = marcar.\n");
	scanf(" %c",c);
	if((*c!='A')&&(*c!='M')){
		printf("Escolha invalida!\n",*c);
		abrir_ou_marcar(c);
	}
}

void abrir_brancos(char jogo[][20], char campo[][20], int x, int y, int cx, int cy){
	/*coord*/
	jogo[cx][cy]=' ';
	/*esquerda*/
	if(cy-1>=0)
		if(campo[cx][cy-1]==' ' && jogo[cx][cy-1]=='_')  // se no campo estiver aberto e no jogo estiver disponivel pra jgr
			abrir_brancos(jogo,campo,x,y,cx,cy-1);
		else
			jogo[cx][cy-1] = campo[cx][cy-1];   //PRINT DO NUMERO de minas adjacentes
	/*direita*/
	if(cy+1<y) 
		if(campo[cx][cy+1]==' ' && jogo[cx][cy+1]=='_')
			abrir_brancos(jogo,campo,x,y,cx,cy+1);
		else
			jogo[cx][cy+1] = campo[cx][cy+1];
	/*embaixo*/
	if(cx+1<x)
		if(campo[cx+1][cy]==' ' && jogo[cx+1][cy]=='_')
			abrir_brancos(jogo,campo,x,y,cx+1,cy);
		else
			jogo[cx+1][cy] = campo[cx+1][cy];
	/*em cima*/
	if(cx-1>=0)
		if(campo[cx-1][cy]==' ' && jogo[cx-1][cy]=='_')
			abrir_brancos(jogo,campo,x,y,cx-1,cy);
		else
			jogo[cx-1][cy] = campo[cx-1][cy];
	//sudoeste 
	if(cx+1<x && cy-1>=0 && campo[cx+1][cy-1]==' ' && jogo[cx+1][cy-1]=='_' && (campo[cx+1][cy]==' ' || campo[cx][cy-1]==' '))
		abrir_brancos(jogo,campo,x,y,cx+1,cy-1);
	//sudeste
	if(cy+1<y && cx+1<x && campo[cx+1][cy+1]==' ' && jogo[cx+1][cy+1]=='_' && (campo[cx+1][cy]==' ' || campo[cx][cy+1]==' '))
		abrir_brancos(jogo,campo,x,y,cx+1,cy+1);
	//noroeste
	if(cy-1>=0 && cx-1>=0 && campo[cx-1][cy-1]==' ' && jogo[cx-1][cy-1]=='_' && (campo[cx-1][cy]==' ' || campo[cx][cy-1]==' '))
		abrir_brancos(jogo,campo,x,y,cx-1,cy-1);
	//nordeste
	if(cy+1<y && cx-1>=0 && campo[cx-1][cy+1]==' ' && jogo[cx-1][cy+1]=='_' && (campo[cx-1][cy]==' ' || campo[cx][cy+1]==' '))
		abrir_brancos(jogo,campo,x,y,cx-1,cy+1);
}

void guarda_pontuacoes(int tdiferenca, int n)
{
	int i;
	float pontuacao;
	char nome[100] ;
	char buffer[100];
	FILE *fp;
	if(tdiferenca == 0)
	{
		pontuacao = n * 10;  // Máximo 10 minas campo 20x20 ou seja 10x10 = 100 max se perder
	}else
	{
		pontuacao = (n * 10) + (5000/tdiferenca);
	}
	printf("\nPontuacao final: %.2f", pontuacao);
	printf("\nDigite o seu nome para registar a pontuacao:  ");
	scanf("%s", nome);
	fp  = fopen ("data.txt", "a+");
	sprintf(buffer, "%.2f", pontuacao);
	strcat(nome," - ");
	fputs(nome, fp);
	fputs(buffer,fp);
	fputs("\n", fp);
	fclose(fp);
	ordenar_pontuacoes(); 
}

void jogar(char campo[][20], char jogo[][20], int x, int y, int tinicio,int minas){
	char cx, cy, ca;
	int k,v,contador_flags = 0;
	int i,j,count=0,tfim, tdiferenca,conta_bandeiras=0;
	system("cls");
	exibir_campo(jogo,x,y,minas);
	escolher_coordenada(&cx,&cy,x,y);
	abrir_ou_marcar(&ca);
	if(ca=='A'){
		if(campo[cx-65][cy-65]=='m'){
			
			for(k=0;k<x;k++)
				for(v=0;v<y;v++)
					if(campo[k][v] == 'm' && jogo[k][v] == '?')
					{
						contador_flags++;
					}
			
			system("cls");
			exibir_campo(campo,x,y,minas);
			printf("Abriste uma mina! Game Over!\n");
			guarda_pontuacoes(0,contador_flags);
			return;
		}
		else if(campo[cx-65][cy-65]!=' '){
			jogo[cx-65][cy-65]=campo[cx-65][cy-65];
		}
		else{
			abrir_brancos(jogo,campo,x,y,cx-65,cy-65);
		}
		//se houver campos abertos além das minas
		for(i=0;i<x;i++)
			for(j=0;j<y;j++)
				if((campo[i][j]!='m') && (jogo[i][j]=='_'))
					count++;
		if(count==0){
			system("cls");
			exibir_campo(campo,x,y,minas);
			tfim=clock();
			tdiferenca = (tfim - tinicio) / 1000;
			printf("Todas os campos foram abertos. Ganhaste o jogo em %d segundos! Parabens!\n",(tfim-tinicio)/1000);
			guarda_pontuacoes(tdiferenca,minas);
			return;
		}
	}
	else{
		if(jogo[(int)cx-65][(int)cy-65]=='?')
		{
			jogo[(int)cx-65][(int)cy-65]='_';
		}else{
			jogo[(int)cx-65][(int)cy-65]='?';
		}
			//Verificar se existem minas não marcadas
			for(i=0;i<x;i++){
				for(j=0;j<y;j++) {
					if((campo[i][j]=='m') && (jogo[i][j]=='_'))
						count++;
					if(jogo[i][j]=='?')
						conta_bandeiras++;
				}
			}
			if(count==0 && conta_bandeiras <= minas){
				system("cls");
				exibir_campo(campo,x,y,minas);
				tfim=clock();
				tdiferenca = (tfim-tinicio) / 1000;
				printf("Todas as minas foram marcadas. Ganhaste o jogo em %d segundos! Parabens!\n",(tfim-tinicio)/1000);
				guarda_pontuacoes(tdiferenca,minas);
				return;
			}else if(conta_bandeiras > minas)
			{
				printf("Tens mais marcacoes que bandeiras.\n");
				sleep(1);
			}	
	}
	jogar(campo,jogo,x,y,tinicio,minas);

}

void ordenar_pontuacoes() {
	
	FILE* filePointer,*fp;
	int bufferLength = 255,i = 0,j,k=0,get_number,tot;
	char buffer[15][bufferLength], swap[bufferLength];
	char pontuacao_linha[10][10];
	char** token = malloc(30 * sizeof(char*));
	float pontuacoes_por_linha[11];
	float pontuacoes_ordenadas[10];//, swap;
	char pontuacoes_string[11][100];
	char each_line[11][100];
	float int_swap;

	filePointer = fopen("data.txt", "r");

	while(fgets(buffer[i], bufferLength, filePointer)) {
		buffer[i][strlen(buffer[i]) - 1] = '\0';
	    i++;
	}
	tot = i;
	
	for(i=0;i<tot;i++)
	{
		strcpy(each_line[i],buffer[i]);
	}
	for(i=0;i<tot;i++)
	{
		j=0;
		token[i] = strtok(buffer[i], "- ");
		while(token[i]!=NULL) {   
			strcpy(pontuacoes_string[i],token[i]);
			token[i] = strtok(NULL, "- ");
		}
	}
	for(i=0;i<tot;i++)
	{
		pontuacoes_por_linha[i] = strtod((pontuacoes_string[i]),NULL);
	}
	
	//bublesort
	for(i=tot;i>=1;i--)
	{
		for(j=0;j<i;j++)
		{
			if(pontuacoes_por_linha[j] < pontuacoes_por_linha[j+1])
			{
				strcpy(swap,each_line[j]);
				strcpy(each_line[j],each_line[j+1]);
				strcpy(each_line[j+1], swap);
				int_swap = pontuacoes_por_linha[j];
				pontuacoes_por_linha[j] = pontuacoes_por_linha[j+1];
				pontuacoes_por_linha[j+1] = int_swap;
			}
		}
	}
	
	fp  = fopen ("data.txt", "w+");
	if(tot>10)
	{
		for(i=0;i<10;i++)
		{
			fputs(each_line[i],fp);
			fputs("\n", fp);
		}
	}else{
		for(i=0;i<tot;i++)
		{
			fputs(each_line[i],fp);
			fputs("\n", fp);
		}
	}
	fclose(fp);
	fclose(filePointer);
}


void ver_pontuacoes()
{
	FILE* filePointer;
	int bufferLength = 255;
	char buffer[bufferLength];
	
	filePointer = fopen("data.txt", "r");
	
	printf("\n");
	while(fgets(buffer, bufferLength, filePointer)) {
	    printf("%s", buffer);	
	}
	fclose(filePointer);
}

int main()
{
	int x,y,minas,tinicio;
	char campo[20][20],j;
	char jogo[20][20];
	char resposta;
	int res_menu, opcao;
	
	do {
	    printf("\nOpcoes do menu:\n");
		printf("Opcao 1: Jogar\n"); 
		printf("Opcao 2: Ver pontuacao\n");  
		printf("Opcao 0: Sair\n");
		printf("Escolha uma opcao: ");
		scanf("%d", &opcao);
		switch (opcao) {
			case 1:
				srand(time(NULL));
				while(1){
					system("cls");
					printf("\nEscolher um dos 3 niveis predefenidos: facil, medio ou dificil (escreva 1)\nEscolher detalhadamente o tamanho do campo e a quantidade das minas (escreva 2)\nVoltar (escreva 0)\n\n - ");
					scanf("%d", &res_menu);
					fflush(stdin);
					if(res_menu == 0)
					{
						system("cls");
						break;
					}
					while(res_menu != 1 && res_menu != 2)
					{
						printf("Opção inválida. Por favor digite 1 ou 2 consoante o que pretende.");
						scanf("%d", &res_menu);
					}
					if(res_menu == 2){
						ler_dimensoes(&x,&y);
						ler_minas(&minas,x,y);	
					}else{
						ler_nivel(&x,&y,&minas);
					}
	
					// escrever no ficheiro tb
					preencher_minas(campo,minas,x,y);
					contar_vizinhos(campo,x,y);

					/*Mostra a resposta!
					exibir_campo(campo,x,y);*/
					preencher_jogo(jogo,x,y);
					tinicio = clock();
					jogar(campo,jogo,x,y,tinicio,minas);
					printf("\nDeseja jogar novamente? S=sim, N=nao.\n");
					scanf(" %c",&j);
					if(j=='S' || j=='s')
						system("cls");
					else
						break;
					}
				//system("pause");
				break;
			case 2:
				system("cls");
				ver_pontuacoes();
				break;
			case 0:
				printf("A sair...");
				break;
				//return 0;
			default:
				printf("Opcao invalida, tenta novamente.");
				break;
		}
	} while(opcao != 0);
	return 0;
}
