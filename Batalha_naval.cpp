#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <time.h>
#include <locale.h>

using namespace std;


//Cabeçalho de funções
void menuInicial();

void limpaTela(){
	system("CLS");
}

void iniciaTabuleiro(char tabuleiro[10][10], char mascara[10][10]){
	
	//Preenche o tabuleiro com água
	int linha, coluna;
	for(linha = 0; linha < 10; linha++){
		for(coluna = 0; coluna < 10; coluna++){
			tabuleiro[linha][coluna] = 'A';
			mascara[linha][coluna] = '*';
		}
	}
}

void exibeMapa(){
	//Mapa indicador de colunas
	int cont;
	for(cont = 0; cont < 10; cont++){
		if(cont == 0){
			cout << "     ";
		}
		cout << cont << "  ";
	}
	
	cout << "\n";
	for(cont = 0; cont < 10; cont++){
		if(cont == 0){
			cout << "   ";
		}
		cout << "|  ";
	}
	cout << "\n";
	
}


void exibeTabuleiro(char tabuleiro[10][10], char mascara[10][10], bool mostraGabarito){
	
	
	char blue[] = {0x1b, '[', '1', ';', '3', '4', 'm', 0};
	char green[] = {0x1b, '[', '1', ';', '3', '2', 'm', 0};
	char normal[] = {0x1b, '[', '1', ';', '3', '9', 'm', 0};
	
	//exibe o tabuleiro
	int linha, coluna;
	for(linha = 0; linha < 10; linha++){
		cout << linha << " - ";
		for(coluna = 0; coluna < 10; coluna++){
			
			switch(mascara[linha][coluna]){
				case 'A':
					cout << blue << " " << mascara[linha][coluna] << normal;
					break;
				case 'P':
					cout << green << " " << mascara[linha][coluna] << normal;
					break;
				default:
					cout << " " << mascara[linha][coluna];
					break;
			}
			
		}
		cout << "\n"; 
	}
	
	if(mostraGabarito == true){
		for(linha = 0; linha < 10; linha++){
			for(coluna = 0; coluna < 10; coluna++){
				cout << "  " << tabuleiro[linha][coluna];
				
			}
			cout << "\n";
		}
	}
	
	
	
}

void posicionaBarcos(char tabuleiro [10][10]){
	
	//coloca 10 barcos no tabuleiro
	int cont, quantidade = 10, quantidadePosicionada = 0;
	
	//verifica se já posicionou todos os barcos
	while(quantidadePosicionada < quantidade){
		
		int linhaAleatoria = rand() % 10; //gera número aleatório de 0 a 9
		
		int colunaAleatoria = rand() % 10; //gera número de itens na coluna aleatório de 0 a 9
		
		if(tabuleiro[linhaAleatoria][colunaAleatoria] == 'A'){
			
			//posiciona 10 barcos aleatoriamente
			tabuleiro[linhaAleatoria][colunaAleatoria] = 'P';
			
			//aumenta o contador de barcos posicionados
			quantidadePosicionada++;
		}
	}
}

void verificaTiro(char tabuleiro[10][10], int linhaJogada, int colunaJogada, int *pontos, string *mensagem){
	
	setlocale(LC_ALL, "Portuguese");
	//verifica quantos pontos adicionar
	switch(tabuleiro[linhaJogada][colunaJogada]){
		case 'P':
			*pontos = *pontos + 10;
			*mensagem = "Você acertou um barco pequeno! (10 pontos)";
			break;
		case 'A':
			*mensagem = "Você acertou a água";
			break;
	}
}

void jogo(string nomeDoJogador){
	
	//variáveis gerais
	char tabuleiro[10][10], mascara[10][10]; //tabuleiro do jogo
	
	int linha, coluna;  // auiliares de navegação
	
	int linhaJogada, colunaJogada; // posição escolhida pelo jogador 
	
	int estadoDeJogo = 1; // 1 = inicio de jogo, 0 = fim de jogo
	
	int pontos = 0; // pontuação do jogador
	
	int tentativas = 0, maximoDeTentativas = 10; //tentativas do jogador
	
	int opcao; // opções de fim de jogo
	
	string mensagem = "Bem vindo ao jogo!"; //mensagem de inicio do jogo e feedback
	
	
	//Inicia o tabuleiro com água
	iniciaTabuleiro(tabuleiro, mascara);
	
	//posiciona barcos aleatoriamente
	posicionaBarcos(tabuleiro);
	
	while(tentativas < maximoDeTentativas){
		
		limpaTela();
		
		//exibe o mapa de indicações
		exibeMapa();
		
		//exibe tabuleiro
		exibeTabuleiro(tabuleiro, mascara, false);
		
		cout << "\nPontos: " << pontos << ", Tentativas Restantes:" << maximoDeTentativas - tentativas;
		cout << "\n" << mensagem;
		
		//verificação de dados
		linhaJogada = -1;
		colunaJogada = -1;
		
		while( (linhaJogada < 0 || colunaJogada < 0) || (linhaJogada > 9 || colunaJogada > 9)){
			
			cout << "\n" << nomeDoJogador << ", digite uma linha: ";
			cin >> linhaJogada;
			cout << "\n" << nomeDoJogador << ", digite uma coluna: ";
			cin >> colunaJogada;
			
		}
		
		//verifica o que aconteceu
		verificaTiro(tabuleiro, linhaJogada, colunaJogada, &pontos, &mensagem);
		
		//reveja o que esta no tabuleiro
		mascara[linhaJogada][colunaJogada] = tabuleiro[linhaJogada][colunaJogada];
		
		tentativas++;
		
	}
	
	setlocale(LC_ALL, "Portuguese");
	cout << "Fim de jogo, o que deseja fazer?";
	cout << "\n1-jogar novamente";
	cout << "\n2-ir para o menu";
	cout << "\n3-sair";
	cin >> opcao;
	switch(opcao){
		case 1:
			jogo(nomeDoJogador);
			break;
		case 2: 
			menuInicial();
			break;
			}
			
			
}

void menuInicial(){
	
	//opção escolhida pelo usuário
	int opcao = 0;
	
	//Nome do usuario
	string nomeDoJogador;
	
	//enquanto ojogador não digita uma opcao valida, mostra o menu novamente
	
	while(opcao < 1 || opcao >3){
		limpaTela();
		setlocale(LC_ALL, "Portuguese");
		cout << "Bem vindo ao jogo de Batalha naval";
		cout << "\n1-Jogar";
		cout << "\n2-Sobre";
		cout << "\n3-Sair";
		cout << "\nEscolha uma opção e tecle ENTER: ";
		
		//faz a leitura da opção
		
		cin >> opcao;
		
		//faz algo de acordo com a opção escolhida
		switch(opcao){
			case 1:
				//inicia o jogo
				//cout << "jogo iniciado"
				cout << "Nome do jogador:";
				cin >> nomeDoJogador;
				jogo(nomeDoJogador);
				break;
			case 2:
				//mostra informações do jogo
				cout << "Informações do jogo";
				break;
			case 3:
				cout << "ate mais";
				break;
		
		}
	}
}

int main(){
	//para gerar números realmente aleatórios
	srand((unsigned) time(NULL));
	
	menuInicial();
	return 0;
}
