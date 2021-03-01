#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include<conio.c>
#include<conio.h>
#include<string.h>
#include<locale.h>
// Livraria Mustafar
struct str1
{
	long int codigo;
	char nome[50];
	char genero[50];
	char autor[50];
	long int quant;
	    struct dt
         {
	          int dia;
	          int mes;
	          int  ano;
        }data;
     char excluido;   
     
}cad;
FILE*arq;
void mensagem( char *MENS, int lin )
{
	long I;
	div_t x;
	x = div( ( 80 - strlen( MENS ) ), 2 );
	gotoxy( x.quot, lin); printf("%s", MENS );
	fflush(stdin);
}

void confere(int x, int y)
{
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void Mascara(char parte[30])//Mascara para adicionar dados!
{


	setlocale(LC_ALL, "Portuguese");
	gotoxy(10,2);printf("Cadastro de Livros-%s",parte);
	gotoxy(10,5);printf("Código: ");	
	gotoxy(10,6);printf("Nome  : ");
	gotoxy(10,7);printf("Gênero: ");
	gotoxy(10,8);printf("Autor : ");
	gotoxy(10,9);printf("Quantidade de livros:");
	gotoxy(10,10);printf("Data de publicação");
	gotoxy(10,11);printf("Dia   :");
	gotoxy(10,12);printf("Mês   :");
	gotoxy(10,13);printf("Ano   :");
}
void ler_mascara()
{
	
	gotoxy(17,5);printf("%d",cad.codigo);
	fflush(stdin);	
    gotoxy(17,6);puts(cad.nome);	
	gotoxy(17,7);puts(cad.genero);
	gotoxy(17,8);puts(cad.autor);
	fflush(stdin);
	gotoxy(31,9);printf("%d",cad.quant);
	gotoxy(17,11);printf("%d",cad.data.dia);		
	gotoxy(17,12);printf("%d",cad.data.mes);
	gotoxy(17,13);printf("%d",cad.data.ano);
	

}
void ExcluINFO() //exclusao lógica
{
	int aux_codigo,F;
	long fposicao;
	char conf;
	char continua;
	do
	{	
	    gotoxy(13,6);printf("                                                               ");
	    gotoxy(13,8);printf("                                                               ");
		gotoxy(10,15); printf("Digite o codigo a ser excluido (digite zero para encerrar): ");         
	    scanf("%d", &aux_codigo );
	    Mascara("EXCLUSÃO");
	    if (aux_codigo!=0)
	    {
			F = 0;
			rewind(arq);
		    do
		    {
				fread( &cad,sizeof(cad),1,arq);
				if ( cad.codigo == aux_codigo && cad.excluido == 'n' ) 
				{
			   		F = 1;
			   		fposicao = ftell(arq); 
			   		ler_mascara(); 
				   	gotoxy(20,20); printf("Confirma exclusão ? (S/N): ");
				   	do 
				   	{
				    	gotoxy(46,20); conf = getche();
				   	}while( conf != 's' && conf != 'S' &&conf != 'n' && conf != 'N' );
				   
				   	if( conf == 's' || conf == 'S' )
				   	{
						fseek (arq,fposicao-(sizeof(cad)),SEEK_SET); 
						cad.excluido='s';
						fwrite(&cad,sizeof(cad),1,arq);
						fflush (arq);
				   	}
					fflush(stdin);
					gotoxy(8,21); printf("Digite ENTER para excluir outro arquivo ou ESPAÇO para voltar ao MENU: ");
			
					gotoxy(78,21);continua=getch();
					if(continua==13)
					{
						gotoxy(70,15);clreol(); 
						
					}
					if(continua==32)
					{
						return;
					}
					
				}
			} while((!F) &&(!feof(arq)));  	
		}
		if (F==0 && aux_codigo!=0)
		{   
			system("cls");
			gotoxy(13,6);printf(" Código nao encontrado");
			gotoxy(13,8);printf("Aperte enter para excluir outro código...");
			//Sleep(4000);
			getch();
			
		}
	}while(aux_codigo!=0);
}


void cabecalho()
{
     system("cls");

			{
     			gotoxy(15,2);printf("CONSULTA GLOBAL-TABELA");
     			gotoxy(1,4);printf("Codigo");
     			gotoxy(8,4);printf("Nome");
			     gotoxy(35,4);printf("Genero");
			     gotoxy(45,4);printf("Autor");
			     gotoxy(60,4);printf("Qtd");
			     gotoxy(65,4);printf("Dia");
			     gotoxy(69,4);printf("Mês");
				 gotoxy(73,4);printf("Ano");	// gotoxy(32,18);printf("Pressione ENTER para voltar ao MENU...");
			}	
}


int checar_chave_primaria()
{
	int aux_codigo, F;
	rewind(arq);
	do{
		F=0;
		gotoxy(18,5);scanf("%d",&aux_codigo);
	    while( ( fread( &cad,sizeof(cad),1,arq) == 1 )&& cad.codigo != aux_codigo ); 
				if(cad.codigo == aux_codigo && cad.excluido=='n')
				{
					fflush(stdin);
					gotoxy(18,15);printf("Código já  cadastrado!");
					//getch();
					gotoxy(17,5);clreol(); 
					F=1;
				}
	}while(F==1);
			return aux_codigo;
}

void CadasINFO()//Inclusão de dados!
{
	Mascara("INCLUSAO");
	cad.codigo=checar_chave_primaria();
	gotoxy(28,5);printf("Código Confirmado: %d",cad.codigo);
	if (cad.codigo==0) return; 
	fflush(stdin);	
	//gotoxy(17,5);scanf("%d",&cad.codigo);
	fflush(stdin);	
    gotoxy(17,6);gets(cad.nome);
    strlwr(cad.nome);
    fflush(stdin);	
	gotoxy(17,7);gets(cad.genero);
	gotoxy(17,8);gets(cad.autor);
	fflush(stdin);
	gotoxy(31,9);scanf("%d",&cad.quant);
	do{
		if(cad.data.dia < 0 || cad.data.dia > 31)
		{
			gotoxy(25,11);printf("Digite um dia entre 1 e 31!");
			Sleep(1000);	
			gotoxy(25,11);printf("                            ");
		}
		gotoxy(17,11);scanf("%d",&cad.data.dia);
	}while(cad.data.dia < 0 || cad.data.dia > 31);
	
	do{
		do{
			
		gotoxy(17,12);scanf("%d",&cad.data.mes);
		if(cad.data.dia == 31 && cad.data.mes == 2 || cad.data.mes == 4 || cad.data.mes == 6 || cad.data.mes == 9 || cad.data.mes == 11){
			gotoxy(25,12);printf("Mes não possui 31 dias, digite o mês correto!");
			Sleep(1000);
			gotoxy(25,12);printf("                                              ");
		}
		}while(cad.data.mes < 0 || cad.data.mes > 12);
	}while(cad.data.dia == 31 && cad.data.mes == 1 || cad.data.dia == 31 &&cad.data.mes == 4 || cad.data.dia == 31 &&cad.data.mes == 6 || cad.data.dia == 31 &&cad.data.mes == 9 || cad.data.dia == 31 &&cad.data.mes == 12);
	do{
	
		gotoxy(17,13);scanf("%d",&cad.data.ano);
		if(cad.data.ano > 2015)
		{
			gotoxy(25,13);printf("Você não pode cadastrar livros do ano futuro!");
			Sleep(1000);
			gotoxy(25,13);printf("                                             ");
	
		}
	}while(cad.data.ano > 2015);
	cad.excluido='n';
		
}
void mostra_CadasINFO()
{
	gotoxy(17,5);scanf("%d",&cad.codigo);
	fflush(stdin);	
    gotoxy(17,6);gets(cad.nome);
    fflush(stdin);	
	gotoxy(17,7);gets(cad.genero);
	gotoxy(17,8);gets(cad.autor);
	fflush(stdin);
	gotoxy(31,9);scanf("%d",&cad.quant);
	gotoxy(17,11);scanf("%d",&cad.data.dia);
	gotoxy(17,12);scanf("%d",&cad.data.mes);
	gotoxy(17,13);scanf("%d",&cad.data.ano);
}
void Salvar()
{
	char conf;
	gotoxy(30,20);printf("Deseja salvar os dados ? (S/N)");
	do
   	{
       	gotoxy(61,22); conf = getche();
   	}while( conf != 's' && conf != 'S'&& conf != 'n' && conf != 'N' );
   
	
	if( conf == 's' || conf == 'S' )
   	{
		if(fwrite(&cad, sizeof(cad), 1, arq) != 1) 
		{
		    gotoxy(18,11);printf("Erro na escrita do arquivo");
		}
		else
		{
			fflush( arq);
			system("cls");
			gotoxy(10,15);printf("Dados salvos com sucesso!");
			Sleep(2000);
			system("cls");
			gotoxy(32,18);printf("Pressione enter para voltar ao menu...");
			getche();
		}
		
		getch();	
	}
}
void ConsulGlobal()
{
	int n=6;	
	cabecalho();	
	char a;
	rewind(arq);
	do
    {
    	if(fread(&cad, sizeof(cad), 1, arq) == 1)
		   	if (cad.excluido=='n')
			{
		        gotoxy(1,n);printf("%d",cad.codigo);	
		        gotoxy(8,n);puts(cad.nome);
		        gotoxy(35,n);puts(cad.genero);
		        gotoxy(45,n);puts(cad.autor);
		        gotoxy(60,n);printf("%d",cad.quant);
		        gotoxy(65,n);printf("%d",cad.data.dia);
	            gotoxy(69,n);printf("%d",cad.data.mes);
	            gotoxy(73,n);printf("%d",cad.data.ano);
                
		        n++;
			
	  			if(n>16)
				{				  
				    gotoxy(15,20);printf("Deseja continuar(ENTER)//para sair (ESPAÇO):");
				    fflush(stdin);
					a=getch(); 
				    if(a==13)
				    {
				       n=6;
				       cabecalho();
					}
					if(a==32)
					{
						break;
					}
				}
			}    
    }while(!feof(arq));
    if(a!=32)
	{
	    gotoxy(15,21);printf("Pressione uma tecla para encerrar a consulta...");
		getch(); 
	}    
    
}

void ConsultNome()
{
		system("cls");
		char NLivro[50];
		char retorna;
		gotoxy(18,10);printf("Digite o nome do livro para consulta-lo: ");
		scanf("%s",&NLivro);
		strlwr(NLivro);
		do
        {
        	if (cad.excluido=='n')
        	{
			
        		if(fread(&cad,sizeof(cad),1,arq)== 1)  
				{	
					if(strstr(cad.nome,NLivro))
					{
					
						rewind(arq);
						system("cls");
				 		Mascara("CONSULTA NOME");
				 		ler_mascara();
				 		gotoxy(12,17);printf("Digite ENTER para voltar ao MENU:");
						retorna=getch();
	 				 	if(retorna==13)
	  						return;                  
				 		//break;
				   }
				
				}
				else
				{
					system("cls");
					gotoxy(18,11);printf("Este livro não está cadastrado em nosso sistema!");
					gotoxy(12,17);printf("Digite ENTER para voltar ao MENU:");
					retorna=getch();
	 				if(retorna==13)
	  					return;
					
				}
			}
			
			
		}while(fread(&cad,sizeof(cad), 1,arq)!=0);	
		
}
void ConsultCod()
{

		int aux_codigo;
		clrscr();
		char retorna;
		gotoxy(30,10);printf("Digite o codigo a ser pesquisado:");
		scanf("%d",&aux_codigo);
		do
        {
        	
			if(cad.codigo==aux_codigo&&cad.excluido=='n')
			{   
			    rewind(arq);
				system("cls");
				Mascara("CONSULTA");
				ler_mascara();
				gotoxy(12,17);printf("Digite ENTER para voltar ao MENU:");
				retorna=getch();
	 			if(retorna==13)
	  				return; 
				
			} 	
			else 
			{
					system("cls");
					gotoxy(18,11);printf("Código não cadastrado em nosso sistema!");
					gotoxy(12,17);printf("Digite ENTER para voltar ao MENU:");
					retorna=getch();
	 				if(retorna==13)
	  					return;
				
			}
			
		}while(fread(&cad,sizeof(cad), 1,arq)!=0);	
}
void digita_dados()
{
	char aux_dia[3],aux_mes[3],aux_ano[5],aux_quant[6];
	fflush(stdin);	
	gotoxy(17,6);gets(cad.nome);
	gotoxy(17,7);gets(cad.genero);
	gotoxy(17,8);gets(cad.autor);
	fflush(stdin);
	gotoxy(31,9);gets(aux_quant);
	cad.quant = atoi(aux_quant);
	gotoxy(17,11);gets(aux_dia);
	gotoxy(17,12);gets(aux_mes);
	gotoxy(17,13);gets(aux_ano);
	cad.data.dia = atoi(aux_dia);
	cad.data.mes = atoi(aux_mes);
	cad.data.ano = atoi(aux_ano);
		
}
void AltINFO()
{
	str1 cad_aux;
	int aux_codigo,F;
	long fposicao;
	long int aux_quant;
	char conf;
	char retorna;
	Mascara("ALTERAÇÃO");
    gotoxy(12,18); printf("Digite o código a ser alterado: ");
    scanf("%d", &aux_codigo );
    F = 0;
    do
    {
		fread( &cad,sizeof(cad),1,arq);
		if ( cad.codigo == aux_codigo && cad.excluido=='n')//SOMENTE SE NÃO FOI EXCLUIDO	
		{
	   		F = 1;
	   		fposicao = ftell(arq); 
	   		ler_mascara();
	   		cad_aux = cad;//salva os dados do registro atual numa estrutura auxiliar
	   		digita_dados();
			// ******> VERIFICA SE HOUVE ALTERACAO EM CADA UM DOS CAMPOS
			if (cad.nome[0] == '\0')//checa se cada campo está vazio
			    strcpy(cad.nome, cad_aux.nome);
			if (cad.genero[0] == '\0')
			    strcpy(cad.genero, cad_aux.genero);
			if (cad.autor[0] == '\0')
			    strcpy(cad.autor, cad_aux.autor);
			if (cad.autor[0] == 0)
			    cad.quant=cad_aux.quant;	    
			if (cad.data.dia == 0)
			    cad.data.dia = cad_aux.data.dia;
			if (cad.data.mes == 0)
			    cad.data.mes = cad_aux.data.mes;
			if (cad.data.ano == 0)
			    cad.data.ano = cad_aux.data.ano;
			
		   	gotoxy(25,22); printf("Confirma alteração ? (S/N): ");
		   	do
		   	{
		    	gotoxy(54,22); conf = getche();
		   	}while( conf != 's' && conf != 'S' &&conf != 'n' && conf != 'N' );
		   
		   	if( conf == 's' || conf == 'S' )
		   	{
		   		//posiciona o ponteiro do arquivo no registro alterado
				fseek (arq,fposicao-(sizeof(cad)),SEEK_SET);//em stdio.h
				//SEEK_SET indica o início do arquivo
				fwrite (&cad,sizeof(cad),1,arq);
				fflush (arq);
		   	}
	
		}
	}  while ((!F) && (!feof(arq))); 
	if (F==0)
	{
		gotoxy(18,15);printf("Código nao encontrado ");
		getch();
	} 	
}


void Sobre()
{
	  char retorna;
	  gotoxy(15,1);printf("Livraria Mustafar");
	  gotoxy(10,5);printf("Alunos:");
	  gotoxy(10,7);printf("  Matheus Guermandi nº22");
	  gotoxy(10,9);printf("  Suellen Stefany   nº25");
	  gotoxy(10,11);printf("  Victor Ribeiro    nº27");
	  gotoxy(40,9);printf("Turma : 71D ");
	  gotoxy(10,13);printf(" Trabalho : FPD");
	  gotoxy(10,15);printf(" Professora : Ariane Scarelli");
	  gotoxy(10,17);printf(" Curiosidade: Mustafar é um planeta vulcanico do universo Star Wars");
	  gotoxy(40,7);printf("CTI-BAURU/SP-UNESP");
	  gotoxy(12,20);printf("Digite ENTER para voltar ao MENU");
	  
	                      retorna=getch();
	  if(retorna==13)
	  	return;                    
}
void AbrirArq(char *modo)
{
	if((arq = fopen("Livraria71d.dat",modo)) == NULL)
	{
		gotoxy(18,11);printf("Erro na abertura do arquivo");
	    exit(1);
	}	
}


void menu(int a)
{
		if(a<0||a>8)
		{
			 printf("\n\n\t\tOpção incorreta");
		}
		system("cls");
    
		switch(a)
		{
			case 1:
					AbrirArq("ab+");
					CadasINFO();
    				Salvar();
    				break;
    		case 2:
    			   // fclose(arq);
    				AbrirArq("rb+");
    				ConsulGlobal();
    				break;
    		case 3:
    				AbrirArq("rb");
					ConsultNome();
    				break;
    		case 4:
    			 	 AbrirArq("rb");
					 ConsultCod();
					 break;
    		case 5:
    				AbrirArq("rb+");
					AltINFO();	
    				break;
    		case 6:
    				AbrirArq("rb+");
					ExcluINFO();
    				break;
			case 7:
					Sobre();
					break;
			case 8:
					system("cls");
	 				gotoxy(20,10);printf("Obrigado por utilizar nosso sistema!");
	 				break;
	 			
							
				
		}	
}

main()
{
     int a; 
     AbrirArq("ab+");
     do
     {
		system("cls");
		textcolor(3);
		setlocale(LC_ALL, "Portuguese");
		gotoxy(20,2);printf("MENU");
		gotoxy(5,4);printf("Bem vindo a Livraria Virtual Mustafar");
		gotoxy(10,6);printf(" (1) Cadastrar informações. ");
		gotoxy(10,7);printf(" (2) Consulta Global.       ");
		gotoxy(10,8);printf(" (3) Consulta por nome.     ");
		gotoxy(10,9);printf(" (4) Consulta por código.   ");
		gotoxy(10,10);printf(" (5) Alterar informações.   ");
		gotoxy(10,11);printf(" (6) Excluir.               ");
		gotoxy(10,12);printf(" (7) Sobre.                 ");
		gotoxy(10,13);printf(" (8) Encerrar.              ");
		gotoxy(10,14);printf("\n\n\t\tDigite sua opção:");
		scanf("%d",&a);
		menu(a);
	 }while(a!=8);
}
