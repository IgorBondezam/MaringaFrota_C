#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <locale.h>

#define MAX_FUNCIONARIOS 100
#define TAM_CPF 12   //  TAMANHO CPF (Considerando o digito verificador)
#define TAM_NOME 50  //  TAMANHO NOME
#define TAM_END 50   //  TAMANHO ENDEREÇO
#define TAM_TEL 50   //  TAMANHO TELEFONE
#define TAM_EMAIL 50 //  TAMANHO E-MAIL 
#define TAM_SENHA 21 //  TAMANHO SENHA
//#define TAM_NASC 11  //  TAMANHO DATA (dd/mm/aaaa)
//#define TAM_CARGO 21
#define ARQUIVO_FUNCIONARIOS "funcionario.txt" // PASTA FUNCIONARIOS.TXT


typedef struct {
    char cpf[TAM_CPF];
    char nome[TAM_NOME];
    char telefone[TAM_TEL];
	char email[TAM_EMAIL];
    char senha[TAM_SENHA];
    char confirmar_senha[TAM_SENHA];
	//char nascimento[TAM_NASC];
    //char cargo[TAM_CARGO];
} Funcionario;

Funcionario funcionarios[MAX_FUNCIONARIOS];

int num_funcionarios = 0;

void carregar_funcionarios() {
    FILE* arquivo = fopen(ARQUIVO_FUNCIONARIOS, "r");
    if (arquivo != NULL) {
        while (fscanf(arquivo, "%s %s", 
					  funcionarios[num_funcionarios].cpf, 
					  funcionarios[num_funcionarios].senha) == 2) {
            num_funcionarios++;
        }
        fclose(arquivo);
    }
}

void limpa_tela(){
		system("cls");
}


void salvar_funcionarios() {
    FILE* arquivo = fopen(ARQUIVO_FUNCIONARIOS, "w");
    if (arquivo != NULL) {
        for (int i = 0; i < num_funcionarios; i++) {
            fprintf(arquivo, "%s %s\n", 
				funcionarios[i].nome, 
				funcionarios[i].cpf,  
                funcionarios[i].telefone, 
                funcionarios[i].email, 
                funcionarios[i].senha);
            //    funcionarios[i].nascimento,
			//	funcionarios[i].cargo);
        }
        fclose(arquivo);
    }
}

bool cpf_valido(char cpf[]) {
    int soma = 0;
    for (int i = 0; i < 9; i++) {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int digito_verificador = 11 - (soma % 11);
    if (digito_verificador >= 10) {
        digito_verificador = 0;
    }
    return digito_verificador == (cpf[9] - '0');
}

bool cpf_existe(char cpf[]) {
    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(cpf, funcionarios[i].cpf) == 0) {
            return true;
        }
    }
    return false;
}

void cadastrar_funcionario() {
    char cpf[TAM_CPF], senha[TAM_SENHA], confirmar_senha[TAM_SENHA];
    printf("NOME: ");
    scanf("%s", funcionarios[num_funcionarios].nome);
    printf("E-MAIL: ");
    scanf("%s", funcionarios[num_funcionarios].email);
    
    bool valido = false;
    
	do{
		printf("CPF (APENAS NÚMEROS): ");
    	scanf("%s", cpf);
		if (!cpf_valido(cpf)) {
        	printf("CPF INVALIDO.\n");
        	continue;
    	}
		if (cpf_existe(cpf)) {
        	printf("JA EXISTE UM USUARIO COM ESSE CPF.\n");
        	continue;
    	}
    	valido = true;
    }while(!valido);
    
    printf("TELEFONE: ");
    scanf("%s", funcionarios[num_funcionarios].telefone);
    /*
	printf("Digite a senha do funcionario: ");
    scanf("%s", senha);
    printf("Digite a data de nascimento do funcionario (DD/MM/AAAA): ");
    scanf("%s", funcionarios[num_funcionarios].nascimento);
    printf("Digite o cargo do funcionario: ");
    scanf("%s", funcionarios[num_funcionarios].cargo);
    */
   
    do{
		
    	printf("\nSENHA: ");
    	scanf("%s", senha);
    	printf("CONFIRMAR SENHA: ");
    	scanf("%s", confirmar_senha);   
	
		if(strcmp(senha, confirmar_senha) != 0){
			usleep(500000); 
			
			printf("\n\nSENHAS NÃO COINCIDEM! \n\n");
			
		}
	}while(strcmp(senha,confirmar_senha) != 0);
	
	 
	Funcionario novo_funcionario;
    strcpy(novo_funcionario.cpf, cpf);
    strcpy(novo_funcionario.senha, senha);
    funcionarios[num_funcionarios] = novo_funcionario;
    num_funcionarios++;
    
	printf("\n \n USUÁRIO CADASTRADO COM SUCESSO! \n\n");
    usleep(500000); 
    usleep(500000);
	limpa_tela();
	
	salvar_funcionarios();   
    
}

bool fazer_login() {
    
	char cpf[TAM_CPF], senha[TAM_SENHA];
    char aux;
    
	printf("DIGITE O CPF: ");
    scanf("%s", cpf);
    printf("DIGITE A SENHA: ");
    scanf("%s", senha);
    for (int i = 0; i < num_funcionarios; i++) {
        if (strcmp(cpf, funcionarios[i].cpf) == 0 && strcmp(senha, funcionarios[i].senha) == 0) {
            printf("USUARIO ENCONTRADO, REALIZANDO LOGIN\n");
            usleep(500000); // espera meio segundo 
        	printf(".");
        	usleep(500000); 
			printf(".");
        	usleep(500000); 
			printf(".");
			usleep(500000); 
			printf("\n \n BEM VINDO!\n");
            return true;
        }
    }
    printf("CPF OU SENHA INVÁLIDA.\n\n");
//	
	do{
	
		printf("\nDESEJA VOLTAR AO MENU ANTERIOR? (S/N)\n");
		scanf("%s", &aux);
		//strlwr(aux);
		switch (aux){
			case 'n':
				printf("\n");
				limpa_tela();
				fazer_login();
				break;
			case 's':
				printf("\nVOLTANDO AO MENU ANTERIOR. \n");
				usleep(1000000); 
				return false;
				break;
			case 'N':
				printf("\n");
				limpa_tela();
				fazer_login();
				break;
			case 'S':
				printf("\nVOLTANDO AO MENU ANTERIOR. \n");
				usleep(1000000); 
				return false;
				break;
			
			default:
				printf("\nOPÇÃO INVÁLIDA!\n");
				break;
		} 
	} while (aux != 'n' && aux != 's');
    
	system("cls");
    
}

int main() {
	setlocale(LC_ALL, "Portuguese");
    carregar_funcionarios();
    while (true) {
        printf("ESCOLHA A OPÇÃO DESEJADA \n\n");
		printf("  1 - CADASTRAR FUNCIONARIO\n");
        printf("  2 - FAZER LOGIN\n");
        printf("  3 - SAIR\n");
        int opcao;
        scanf("%d", &opcao);
        limpa_tela();
        switch (opcao) {
            case 1:
            	printf("CADASTRO DE FUNCIONÀRIO \n\n");
                cadastrar_funcionario();
				break;
            case 2:
                if (fazer_login()) {
                    //-----------------------------------------------------
                    //
                    //             PRÓXIMA PAGINA DEPOIS DO LOGIN
                    //
                    //------------------------------------------------------
                    limpa_tela();
                }
                break;
            case 3:
                return 0;
            default:
                printf("OPCAO INVALIDA.\n");
				break;
        }
    }
    return 0;
}

