#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************************************************************************
Aluno(a): Guilherme Ferreira Brandao
Matrícula: 231030691
Declaro que eu sou o(a) autor(a) deste trabalho e que o código não foi copiado
de outra pessoa nem repassado para alguém. Estou ciente de que poderei sofrer
penalizações na avaliação em caso de detecção de plágio.
*******************************************************************************/



// STRUCT MINIUSINA
struct miniusina {
    char cnpj[20];
    char nome[100];
    float capacidade_total;
    int id_ra;
    char status_usina[20];
    char cnpj_miniusina[20];
};

// STRUCT CONSUMIDORES
struct consumidores {
    char cnpj_cpf[20];
    char nome[100];
    int id_ra;
};


// STRUCT CONTRATOS
struct contratos {
    int id_contrato;
    char cnpj_cpf2[20];
    char cnpj_miniusina[20];
    char data_inicio_contrato[20];
    float energia_contratada; 
};



// FUNCAO PARA CARREGAR OS DADOS DE MINIUSINAS
void carregarminiusinas(struct miniusina* miniusinas, int* numminiusinas) {
    // Abrindo o arquivo de leitura
    FILE* arquivo = fopen("miniusinas.csv", "r");
    if (arquivo == NULL) {
        printf("ERROR ao abrir o arquivo de miniusinas.\n");
        return;
    }

    // LENDO A PRIMEIRA LINHA
    char linha[100];
    fgets(linha, sizeof(linha), arquivo);

    // LENDO O RESTANTE DAS LINHAS
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Utilizando a função sscanf para separar os campos da linha e atribuí-los à estrutura Miniusina correspondente
        sscanf(linha, "%[^;];%[^;];%f;%d;%s",
               miniusinas[*numminiusinas].cnpj,
               miniusinas[*numminiusinas].nome,
               &(miniusinas[*numminiusinas].capacidade_total),
               &(miniusinas[*numminiusinas].id_ra),
               miniusinas[*numminiusinas].status_usina);

        
        (*numminiusinas)++;
    }

    // Fechando o arquivo
    fclose(arquivo);
}


// FUNCAO PARA CARREGAR OS DADOS DOS CONSUMIDORES 
void carregarconsumidores(struct consumidores* consumidores, int* numconsumidores) {
    // Abrindo o arquivo de leitura
    FILE* arquivo = fopen("consumidores.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de Consumidores.\n");
        return;
    }

    // LENDO A PRIMEIRA LINHA
    char linha[100];
    fgets(linha, sizeof(linha), arquivo);

    // LENDO O RESTANTE
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Utilizando a função sscanf para separar os campos da linha e atribuí-los aos consumidores
        sscanf(linha, "%[^;];%[^;];%d;%d",
               consumidores[*numconsumidores].cnpj_cpf,
               consumidores[*numconsumidores].nome,
               &(consumidores[*numconsumidores].id_ra));

       
        (*numconsumidores)++;
    }

    // Fechando o arquivo
    fclose(arquivo);
}

// FUNCAO PARA CARREGAR OS CONTRATOS
void carregarcontratos(struct contratos* contratos, int* numcontratos) {
    
    FILE* arquivo = fopen("contratos.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de contratos.\n");
        return;
    }

    // LENDO A PRIMEIRA LINHA 
    char linha[100];
    fgets(linha, sizeof(linha), arquivo);

    // LENDO O RESTANTE 
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Utilizando a função sscanf para separar os campos da linha e atribuí-los à estrutura Contratos correspondente
        sscanf(linha, "%d;%[^;];%[^;];%[^;];%f",
               &(contratos[*numcontratos].id_contrato),
               contratos[*numcontratos].cnpj_cpf2,
               contratos[*numcontratos].cnpj_miniusina,
               contratos[*numcontratos].data_inicio_contrato,
               &(contratos[*numcontratos].energia_contratada));

       
        (*numcontratos)++;
    }

    
    fclose(arquivo);
}

// FUNCAO PARA VALIDAR CPF_CNPJ
int validardocumento(char *documentonumerico) {
    int i;

    // Verifica o tamanho do documento
    int tamanho = strlen(documentonumerico);
    if (tamanho == 11) {
        // CPF

        // CALCULO DO PRIMEIRO DIGITO
        int soma = 0;
        int peso = 10;
        for (i = 0; i < 9; i++) {
            soma += (documentonumerico[i] - '0') * peso;
            peso--;
        }
        int digito1 = (soma % 11 < 2) ? 0 : (11 - soma % 11);

        //CALCULO DO SEGUNDO DIGITO 
        soma = 0;
        peso = 11;
        for (i = 0; i < 10; i++) {
            soma += (documentonumerico[i] - '0') * peso;
            peso--;
        }
        int digito2 = (soma % 11 < 2) ? 0 : (11 - soma % 11);

        // VERIFICANDO SE OS DIGITOS VERIFICADORES SAO VALIDOS
        if ((documentonumerico[9] - '0' != digito1) || (documentonumerico[10] - '0' != digito2)) {
            return 0;
        }
    } else if (tamanho == 14) {
        // CNPJ

        // CALCULO DO PRIMEIRO DIGITO
        int soma = 0;
        int peso = 5;
        for (i = 0; i < 12; i++) {
            soma += (documentonumerico[i] - '0') * peso;
            peso = (peso == 2) ? 9 : peso - 1;
        }
        int digito1 = (soma % 11 < 2) ? 0 : (11 - soma % 11);

        // CALCULO DO SEGUNDO DIGITO 
        soma = 0;
        peso = 6;
        for (i = 0; i < 13; i++) {
            soma += (documentonumerico[i] - '0') * peso;
            peso = (peso == 2) ? 9 : peso - 1;
        }
        int digito2 = (soma % 11 < 2) ? 0 : (11 - soma % 11);

        // VERIFICANDO SE OS DIGITOS VERIFICAROES SAO VALIDOS
        if ((documentonumerico[12] - '0' != digito1) || (documentonumerico[13] - '0' != digito2)) {
            return 0;
        }
    } else {
        // CASO NAO SEJA 
        return 0;
    }

    return 1;
}



int main() {
    // DECLARANDO E CHAMANDO 
    struct miniusina miniusinas[100];
    int numminiusinas = 0;

    struct consumidores consumidores[100];
    int numconsumidores = 0;

    struct contratos contratos[100];
    int numcontratos = 0;

    carregarminiusinas(miniusinas, &numminiusinas); // Chamando função Miniusina
    carregarconsumidores(consumidores, &numconsumidores); // Chamando função Consumidores
    carregarcontratos(contratos, &numcontratos);

    // CABECALHO DO MENU 
    printf("Sistema de Informacoes sobre Geracao e Distribuicao Fotovoltaica (SINGDF)\n");
    
    while (1) {  //LOPP PARA O PROGAMA VOLTAR AQUI ATE FECHAR PELA OPCAO SAIR DO PROGAMA 
        // MENU 
        printf("Menu de opcoes:\n");
        printf("1) Consultar miniusina cadastrada\n");
        printf("2) Consultar consumidor cadastrado\n");
        printf("3) Listar as miniusinas cadastradas\n");
        printf("4) Listar as miniusinas em operacao por ordem decrescente de capacidade de geracao de energia\n");
        printf("5) Listar as RAs por ordem decrescente de quantidade de miniusinas\n");
        printf("6) Listar as RAs por ordem crescente de numero de contratos\n");
        printf("7) Listar as RAs por ordem decrescente de capacidade de geracao\n");
        printf("8) Listar as RAs por ordem decrescente de percentual de energia disponivel\n");
        printf("9) Sair do programa\n");

        // LENDO A OPCAO ESCOLHIDA 
        int opcao;
        printf("Digite uma opcao: ");
        scanf("%d", &opcao);

        // ESTRUTURA DE CADA OPCAO DO MENU 
        switch (opcao) {
            case 1: {
                printf("____________________________________________________________________________\n");
                char cnpj[20];
                printf("Digite o CNPJ da miniusina: ");
                scanf("%s", cnpj);
                int encontrada = 0; // VARIAVEL PARA INDICAR Q FOI LOCALIZADA A MINIUSINA 
                      

                 if (!validardocumento(cnpj)) {// VALIDANDO O CPF OU CNPJ
                  printf("CNPJ Valido!\n");
                } else {
                  printf("CNPJ invalido!\n");
                       }


                //LOOP PARA PROCURAR O CNPJ DIGITADO
                for (int i = 0; i < numminiusinas; i++) {
                    // Comparando o CNPJ digitado com o CNPJ de cada miniusina
                    if (strcmp(cnpj, miniusinas[i].cnpj) == 0) {
                        encontrada = 1;

                        // EXIBINDO OS DADOS 
                        printf("Miniusina encontrada:\n");
                        printf("CNPJ: %s\n", miniusinas[i].cnpj);
                        printf("Nome: %s\n", miniusinas[i].nome);
                        printf("Capacidade total: %.2f kWh\n", miniusinas[i].capacidade_total);
                        printf("RA: %d\n", miniusinas[i].id_ra);
                        printf("Status: %s\n", miniusinas[i].status_usina);
                        printf("______________________\n");

                        //LOOP PARA VERIFICAR SE TEM ALGUUM CONTRATO VINCULADO 
                        for (int j = 0; j < numcontratos; j++) {
                            // COMPARANDO COM OS CONTRATOS 
                            if (strcmp(miniusinas[i].cnpj, contratos[j].cnpj_miniusina) == 0) {
                                // Exibindo as informações do contrato vinculado à miniusina
                                printf("Contrato vinculado:\n");
                                printf("ID Contrato: %d\n", contratos[j].id_contrato);
                                printf("Data de Inicio: %s\n", contratos[j].data_inicio_contrato);
                                printf("Energia Contratada: %.2f kWh\n", contratos[j].energia_contratada);
                                printf("--------------------------------\n");
                                printf("____________________________________________________________________________\n");
                                break;
                            }
                        }
                    }
                }

                // CASO A MINIUSINA NAO SEJA ENCONTRADA 
                if (!encontrada) {
                    printf("Miniusina nao encontrada.\n");
                }

                break;
            }

            case 2: {
                printf("____________________________________________________________________________\n");
                char cnpj_cpf[20];
                printf("Digite o CPF ou CNPJ do Consumidor: ");
                scanf("%s", cnpj_cpf);
                int encontrada = 0; // VARIAVEL PARA VER SE O CONSUMIDOR FOI LOCALIZADO

                if (!validardocumento(cnpj_cpf)) {
                  printf("CNPJ ou CPF Valido!\n");
                } else {
                  printf("CNPJ ou CPF invalido!\n");
                       }



                // LOOP PARA PECORRER OS CONSUMIDORESS 
                for (int i = 0; i < numconsumidores; i++) {
                    // Comparando o CPF/CNPJ digitado com o CPF/CNPJ de cada consumidor
                    if (strcmp(cnpj_cpf, consumidores[i].cnpj_cpf) == 0) {
                        encontrada = 1;

                        // EXIBINDO INFORMACOES DO CONTRATO
                        printf("Consumidor encontrado:\n");
                        printf("CPF/CNPJ: %s\n", consumidores[i].cnpj_cpf);
                        printf("Nome: %s\n", consumidores[i].nome);
                        printf("RA: %d\n", consumidores[i].id_ra);
                        printf("______________________\n");

                        // LOOP PRA VER OS CONTRATOS VINCULADOS 
                        for (int j = 0; j < numcontratos; j++) {
                            // Comparando o CPF/CNPJ do consumidor com o CPF/CNPJ do contrato
                            if (strcmp(consumidores[i].cnpj_cpf, contratos[j].cnpj_cpf2) == 0) {
                                // Exibindo as informações do contrato do consumidor
                                printf("Contrato do Consumidor:\n");
                                printf("ID Contrato: %d\n", contratos[j].id_contrato);
                                printf("CNPJ Miniusina: %s\n", contratos[j].cnpj_miniusina);
                                printf("Data de Inicio: %s\n", contratos[j].data_inicio_contrato);
                                printf("Energia Contratada: %.2f kWh\n", contratos[j].energia_contratada);
                                printf("--------------------------------\n");
                                printf("____________________________________________________________________________\n");

                                
                                break;
                            }
                        }
                    }
                }

                // CASO NAO FOI ENCONTRADO 
                if (!encontrada) {
                    printf("Consumidor nao encontrado.\n");
                }

                break;
            }


    case 3: {
    printf("____________________________________________________________________________\n");
    printf("Miniusinas cadastradas:\n");

    if (numminiusinas == 0) {
        printf("Nenhuma miniusina cadastrada.\n");
    } else {
        for (int i = 0; i < numminiusinas; i++) { // LOOP PARA LISTA AS MINIUSINAS
            printf("Miniusina %d:\n", i + 1);
            printf("CNPJ: %s\n", miniusinas[i].cnpj);
            printf("Nome: %s\n", miniusinas[i].nome);
            printf("Capacidade total: %.2f kWh\n", miniusinas[i].capacidade_total);
            printf("RA: %d\n", miniusinas[i].id_ra);
            printf("Status: %s\n", miniusinas[i].status_usina);
            printf("\n");
            printf("____________________________________________________________________________\n");
        }
    }

    break;
}
case 4: {
    printf("____________________________________________________________________________\n");
    printf("Miniusinas em operacao (por ordem decrescente de capacidade de geracao de energia):\n");

    if (numminiusinas == 0) {
        printf("Nenhuma miniusina cadastrada.\n");
    } else {
        // FILTRAR E ORDENAR AS MINIUSINAS EM OPERACAO POR CAPACIDADE DE GERACAO
        int numminiusinasemoperacao = 0;
        struct miniusina miniusinasemoperacao[100];

        for (int i = 0; i < numminiusinas; i++) {
            if (strcmp(miniusinas[i].status_usina, "operacao") == 0) {
                miniusinasemoperacao[numminiusinasemoperacao] = miniusinas[i];
                numminiusinasemoperacao++;
            }
        }

        //ORDENAR AS MINIUSINAS EM OPERAÇÃO POR CAPACIDADE FAMOSO METODO BUBBLE SORT
        for (int i = 0; i < numminiusinasemoperacao - 1; i++) {
            for (int j = 0; j < numminiusinasemoperacao - i - 1; j++) {
                if (miniusinasemoperacao[j].capacidade_total < miniusinasemoperacao[j + 1].capacidade_total) {
                    struct miniusina temp = miniusinasemoperacao[j];
                    miniusinasemoperacao[j] = miniusinasemoperacao[j + 1];
                    miniusinasemoperacao[j + 1] = temp;
                }
            }
        }

        // EXIBINDO O RESULTADO 
        if (numminiusinasemoperacao == 0) {
            printf("Nenhuma miniusina em operacao.\n");
        } else {
            for (int i = 0; i < numminiusinasemoperacao; i++) {
                printf("Miniusina %d:\n", i + 1);
                printf("CNPJ: %s\n", miniusinasemoperacao[i].cnpj);
                printf("Nome: %s\n", miniusinasemoperacao[i].nome);
                printf("Capacidade total: %.2f kWh\n", miniusinasemoperacao[i].capacidade_total);
                printf("RA: %d\n", miniusinasemoperacao[i].id_ra);
                printf("Status: %s\n", miniusinasemoperacao[i].status_usina);
                printf("\n");
                printf("____________________________________________________________________________\n");

            }
        }
    }

    break;
}


    case 5:{ 
        // AINDA FALTA IMPLEMENTAR 


    }

    case 6:{ 
        // AINDA FALTA IMPLEMENTAR 


    }

    case 7:{ 
        // AINDA FALTA IMPLEMENTAR 


    }



    case 8:{ 
        // AINDA FALTA IMPLEMENTAR 


    }

            case 9: {
                // FECHANDO PROGRAMA 
                printf("FECHANDO PROGAMA...\n");
                return 0;
            }

            default:
                printf("ERRO. OPCAO INVALIDA .\n");
        }
    }

    return 0;
}