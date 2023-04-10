#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

#define MAX_VEICULOS 100

typedef enum
{
    CARRO = 1,
    CAMINHAO,
    ONIBUS,
    MOTO
} TipoVeiculo;

typedef enum
{
    GASOLINA = 1,
    ETANOL,
    FLEX,
    DISEL
} TipoCombustivel;

typedef struct
{
    char placa[8];
    char renavam[12];
    char chassi[17];
    char modelo[50];
    char marca[50];
    TipoVeiculo tipo;
    int km;
    float capacidade_tanque;
    char data_aquisicao[11];
    int ano_modelo;
    TipoCombustivel combustivel;
    int num_eixos;
} Veiculo;

Veiculo frota[MAX_VEICULOS];
int num_veiculos = 0;

void adicionar_veiculo();
void listar_veiculos();
void atualizar_veiculo();
void remover_veiculo();
const char *converterEnumCombustivel(TipoCombustivel num);
const char *converterEnumVeiculo(TipoVeiculo num);
bool verificarPlaca(Veiculo v);
bool validarChassi(Veiculo v);
bool separarData(Veiculo v);
bool validar_data(char *diaCarac, char *mesCarac, char *anoCarac);
bool validarAno(Veiculo v);

int main()
{

    int opcao;
    do
    {
        printf("\nSelecione uma opcao:\n");
        printf("1 - Adicionar veiculo\n");
        printf("2 - Listar veiculos\n");
        printf("3 - Atualizar veiculo\n");
        printf("4 - Remover veiculo\n");
        printf("0 - Sair\n");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Carregando...");
            Sleep(3000);
            system("cls");
            adicionar_veiculo();
            break;

        case 2:
            printf("Carregando...");
            Sleep(3000);
            system("cls");
            listar_veiculos();
            break;

        case 3:
            printf("Carregando...");
            Sleep(3000);
            system("cls");
            atualizar_veiculo();
            break;
        case 4:
            printf("Carregando...");
            Sleep(3000);
            system("cls");
            remover_veiculo();
            break;

        case 0:
            printf("Saindo...");
            Sleep(3000);
            system("cls");
            printf("Saindo...\n");
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (opcao != 0);

    return 0;
}

void adicionar_veiculo()
{

    if (num_veiculos == MAX_VEICULOS)
    {
        printf("Erro: frota cheia!\n");
        return;
    }

    Veiculo v;

    do
    {
        printf("Placa: ");
        scanf("%s", v.placa);
        strupr(v.placa);
        if (!verificarPlaca(v))
        {
            printf("Placa digitada incorretamente. Padrao AAA9A99\n");
        }
    } while (!verificarPlaca(v));

    do
    {
        printf("Renavam: ");
        fflush(stdin);
        gets(v.renavam);
        fflush(stdin);
        if (strlen(v.renavam) != 9 && strlen(v.renavam) != 11)
        {
            printf("O numero do Renavam, so pode ir ate 9 para carros ate 2013 ou 11 de 2013 a diante!!\n");
        }
    } while (strlen(v.renavam) != 9 && strlen(v.renavam) != 11);

    do
    {
        strcpy(v.chassi, "");
        printf("Chassi: ");
        gets(v.chassi);
        strupr(v.chassi);

    } while (!validarChassi(v));

    printf("Modelo: ");
    gets(v.modelo);

    printf("Marca: ");
    gets(v.marca);
    do
    {
        printf("Tipo (1-Carro, 2-Caminhao, 3-Onibus, 4-Moto): ");
        scanf("%d", &v.tipo);
        if (v.tipo < 1 || v.tipo > 4)
        {
            printf("Digite um valor valido!!\n");
        }
    } while (v.tipo < 1 || v.tipo > 4);

    printf("Kilometros rodados: ");
    scanf("%d", &v.km);

    printf("Capacidade do tanque: ");
    scanf("%f", &v.capacidade_tanque);
    do
    {
        printf("Data de aquisicao (dd/mm/aaaa): ");
        scanf("%s", v.data_aquisicao);
    } while (!separarData(v));

    do
    {
        printf("Ano do modelo: ");
        scanf("%d", &v.ano_modelo);
    } while (!validarAno(v));
    do
    {
        printf("Tipo de combustivel (1-Gasolina, 2-Etanol, 3-Flex, 4-Disel): ");
        scanf("%d", &v.combustivel);
    } while (v.combustivel < 1 || v.combustivel > 4);
    printf("Numero de eixos: ");
    scanf("%d", &v.num_eixos);

    frota[num_veiculos++] = v;

    printf("Veiculo adicionado com sucesso!\n");
}

void listar_veiculos()
{
    system("cls");
    if (num_veiculos == 0)
    {
        printf("Nenhum veiculo cadastrado.\n");
        return;
    }

    for (int i = 0; i < num_veiculos; i++)
    {

        Veiculo v = frota[i];

        printf("\n\n================VEICULO-%i================\n", i + 1);
        printf("Placa: %s\n", v.placa);
        printf("Renavam: %s\n", v.renavam);
        printf("Chassi: %s\n", v.chassi);
        printf("Modelo: %s\n", v.modelo);
        printf("Marca: %s\n", v.marca);
        printf("Tipo: %s\n", converterEnumVeiculo(v.tipo));
        printf("Km: %d\n", v.km);
        printf("Tanque(L): %.2f\n", v.capacidade_tanque);
        printf("Data: %s\n", v.data_aquisicao);
        printf("Ano: %d\n", v.ano_modelo);
        printf("Combustivel: %s\n", converterEnumCombustivel(v.combustivel));
        if (v.num_eixos != 0)
        {
            printf("Eixos: %d\n", v.num_eixos);
        }else{
            printf("Veiculo nao ha eixos.\n");
        }
        printf("==========================================");
    }

    printf("\n");
    system("pause");
    system("cls");
}

void atualizar_veiculo()
{
    char placa[8];

    printf("Digite a placa do veiculo a ser atualizado: ");
    scanf("%s", placa);
    int indice = -1;

    for (int i = 0; i < num_veiculos; i++)
    {
        if (strcmp(frota[i].placa, placa) == 0)
        {
            indice = i;
            break;
        }
    }

    if (indice == -1)
    {
        printf("Veiculo nao encontrado!\n");
        return;
    }

    Veiculo v = frota[indice];

    do
    {
        printf("Placa: ");
        scanf("%s", v.placa);
        strupr(v.placa);
        if (!verificarPlaca(v))
        {
            printf("Placa digitada incorretamente. Padrao AAA9A99\n");
        }
    } while (!verificarPlaca(v));

    do
    {
        printf("Renavam: ");
        fflush(stdin);
        gets(v.renavam);
        fflush(stdin);
        if (strlen(v.renavam) != 9 && strlen(v.renavam) != 11)
        {
            printf("O numero do Renavam, so pode ir ate 9 para carros ate 2013 ou 11 de 2013 a diante!!\n");
        }
    } while (strlen(v.renavam) != 9 && strlen(v.renavam) != 11);

    do
    {
        strcpy(v.chassi, "");
        printf("Chassi: ");
        gets(v.chassi);
        strupr(v.chassi);

    } while (!validarChassi(v));

    printf("Modelo: ");
    gets(v.modelo);

    printf("Marca: ");
    gets(v.marca);
    do
    {
        printf("Tipo (1-Carro, 2-Caminhao, 3-Onibus, 4-Moto): ");
        scanf("%d", &v.tipo);
        if (v.tipo < 1 || v.tipo > 4)
        {
            printf("Digite um valor valido!!\n");
        }
    } while (v.tipo < 1 || v.tipo > 4);

    printf("Kilometros rodados: ");
    scanf("%d", &v.km);

    printf("Capacidade do tanque: ");
    scanf("%f", &v.capacidade_tanque);
    do
    {
        printf("Data de aquisicao (dd/mm/aaaa): ");
        scanf("%s", v.data_aquisicao);
    } while (!separarData(v));

    do
    {
        printf("Ano do modelo: ");
        scanf("%d", &v.ano_modelo);
    } while (!validarAno(v));
    do
    {
        printf("Tipo de combustivel (1-Gasolina, 2-Etanol, 3-Flex, 4-Disel): ");
        scanf("%d", &v.combustivel);
    } while (v.combustivel < 1 || v.combustivel > 4);
    printf("Numero de eixos: ");
    scanf("%d", &v.num_eixos);


    frota[indice] = v;

    printf("Veiculo atualizado com sucesso!\n");
}

void remover_veiculo()
{
    char placa[8];
    printf("Digite a placa do veiculo a ser removido: ");
    scanf("%s", placa);

    int indice = -1;

    for (int i = 0; i < num_veiculos; i++)
    {
        if (strcmp(frota[i].placa, placa) == 0)
        {
            indice = i;
            break;
        }
    }

    if (indice == -1)
    {
        printf("Veiculo nao encontrado!\n");
        return;
    }

    for (int i = indice; i < num_veiculos - 1; i++)
    {
        frota[i] = frota[i + 1];
    }

    num_veiculos--;

    printf("Veiculo removido com sucesso!\n");
}

const char *converterEnumCombustivel(TipoCombustivel num)
{
    switch (num)
    {
    case 1:
        return "Gasolina";
        break;
    case 2:
        return "Etanol";
        break;
    case 3:
        return "Flex";
        break;
    case 4:
        return "Disel";
        break;
    default:
        break;
    }
}

const char *converterEnumVeiculo(TipoVeiculo num)
{
    switch (num)
    {
    case 1:
        return "Carro";
        break;
    case 2:
        return "Caminhao";
        break;
    case 3:
        return "Onibus";
        break;
    case 4:
        return "Moto";
        break;
    default:
        break;
    }
}

bool verificarPlaca(Veiculo v)
{
    char placa[9];
    strcpy(placa, v.placa);
    int placaTemp;

    for (int i = 0; i < 3; i++)
    {
        placaTemp = placa[i];
        if (placaTemp > 90 || placaTemp < 65)
        {
            return false;
        }
    }
    placaTemp = placa[3];
    if (placaTemp < 48 || placaTemp > 57)
    {
        return false;
    }
    placaTemp = placa[4];
    if (placaTemp > 90 || placaTemp < 65)
    {
        return false;
    }
    for (int i = 5; i < 7; i++)
    {
        placaTemp = placa[i];
        if (placaTemp < 48 || placaTemp > 57)
        {
            return false;
        }
    }
    return true;
}

bool validarChassi(Veiculo v)
{
    for (int i = 0; i < strlen(v.chassi); i++)
    {

        if (v.chassi[i] == ' ')
        {
            printf("Digite um chassi sem espaco!!\n");
            return false;
        }
    }

    char chassi[18];                                                    // o chassi deve ter 17 caracteres + 1 para o caractere nulo
    int pesos[] = {8, 7, 6, 5, 4, 3, 2, 10, 0, 9, 8, 7, 6, 5, 4, 3, 2}; // pesos para cada caractere
    int valores[17];                                                    // valores numéricos correspondentes a cada caractere
    int soma = 0, resto, i;

    strcpy(chassi, v.chassi);

    // converter caracteres alfanuméricos em valores numéricos correspondentes
    for (i = 0; i < 17; i++)
    {
        if (isdigit(chassi[i]))
        {
            valores[i] = chassi[i] - '0';
        }
        else if (isupper(chassi[i]))
        {
            valores[i] = chassi[i] - 'A' + 1;
        }
        else
        {
            printf("Chassi invalido!\n");
            return false;
        }
    }

    // calcular o dígito verificador
    for (i = 0; i < 16; i++)
    {
        soma += pesos[i] * valores[i];
    }
    resto = soma % 11;

    // determinar o valor do dígito verificador
    if (resto == 10)
    {
        chassi[8] = 'X';
    }
    else
    {
        chassi[8] = resto + '0';
    }

    // validar o chassi com a especificação da NHTSA
    if (chassi[9] == '0' && chassi[10] == '0')
    {
        printf("Chassi invalido!\n");
        return false;
    }

    if (chassi[10] == '9' && chassi[11] == '9')
    {
        printf("Chassi invalido!\n");
        return false;
    }

    if (chassi[10] == '1' && chassi[11] == '0')
    {
        printf("Chassi invalido!\n");
        return false;
    }

    if (chassi[11] == '0' && chassi[12] == '0')
    {
        printf("Chassi invalido!\n");
        return false;
    }

    return true;
}

bool separarData(Veiculo v)
{
    char dia[3];
    char mes[3];
    char ano[5];

    dia[2] = '\0';
    mes[2] = '\0';
    ano[4] = '\0';

    if (!(v.data_aquisicao[2] == '/' && v.data_aquisicao[5] == '/'))
    {
        printf("Formatacao invalida.\n");
        return false;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i < 2)
        {
            dia[i] = v.data_aquisicao[i];
        }
        if (i > 2 && i < 5)
        {
            mes[i - 3] = v.data_aquisicao[i];
        }
        if (i > 5)
        {
            ano[i - 6] = v.data_aquisicao[i];
        }
    }

    return validar_data(dia, mes, ano);
}

bool validar_data(char *diaCarac, char *mesCarac, char *anoCarac)
{
    int dia = atoi(diaCarac);
    int mes = atoi(mesCarac);
    int ano = atoi(anoCarac);
    // Verificar se o ano é bissexto
    bool bissexto = (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
    // Verificar se o mês é válido
    if (mes < 1 || mes > 12)
    {
        printf("Data invalida!\n");
        return false;
    }
    // Verificar se o dia é válido
    int max_dias = 31;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        max_dias = 30;
    }
    else if (mes == 2)
    {
        max_dias = bissexto ? 29 : 28;
    }
    if (dia < 1 || dia > max_dias)
    {
        printf("Data invalida!\n");
        return false;
    }
    // Verificar se o ano é válido
    if (ano < 0 || ano > 9999)
    {
        printf("Data invalida!\n");
        return false;
    }
    return true;
}

bool validarAno(Veiculo v)
{
    char ano[4];
    int anoNumero;
    int cont = 0;
    for (int i = 6; i < 10; i++)
    {
        ano[cont] = v.data_aquisicao[i];
        cont++;
    }
    ano[cont] = '\0';

    anoNumero = atoi(ano);
    
    if (anoNumero < v.ano_modelo)
    {
        printf("O ano de aquisicao e menor que o ano do modelo!\n");
        return false;
    }
    return true;
}
