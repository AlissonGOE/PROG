#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct veiculo {
    float velocidade;
    float comprimento;
    int eixos;
};

struct deltaeixo {
    float eixovmax;
    float eixovmin;
};

struct deltacomprimento {
    float eixocmax;
    float eixocmin;
};

char linha[1024];  // Define um buffer para armazenar cada linha
const char delimitador[] = ";";
struct veiculo veiculos[500];
struct deltaeixo eixo[9];
struct deltacomprimento comprim[9];
int i = 0;  // contadores

void velo(void);
void compri(void);

int main() {
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    } else {
        printf("\nArquivo dados.txt aberto com sucesso!!\n");
    }
    FILE *resultado = fopen("resultado.txt", "w");
    if (resultado == NULL) {
        printf("Erro ao abrir o arquivo de resultado.\n");
        fclose(arquivo);
        return 1;
    } else {
        printf("Arquivo resultado.txt aberto com sucesso!!\n");
    }

    // Inicializar os valores mínimos com um valor alto
    eixo[2].eixovmin = 200.0;
    eixo[3].eixovmin = 200.0;
    eixo[5].eixovmin = 200.0;
    eixo[7].eixovmin = 200.0;
    eixo[9].eixovmin = 200.0;
    
    comprim[2].eixocmin = 200.0;
    comprim[3].eixocmin = 200.0;
    comprim[5].eixocmin = 200.0;
    comprim[7].eixocmin = 200.0;
    comprim[9].eixocmin = 200.0;


    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;
        char *campo = strtok(linha, delimitador);
        int coluna = 0;
        printf("\n");

        while (campo != NULL) {
            if (coluna == 3) {
                veiculos[i].velocidade = strtof(campo, NULL);
                printf("Velocidade = %.1f\n", veiculos[i].velocidade);
            } else if (coluna == 4) {
                veiculos[i].comprimento = strtof(campo, NULL);
                printf("Comprimento = %.1f\n", veiculos[i].comprimento);
            } else if (coluna == 6) {
                veiculos[i].eixos = atoi(campo);
                printf("Eixos = %d\n", veiculos[i].eixos);
            }
            campo = strtok(NULL, delimitador);
            coluna++;
        }

        velo();
        compri();
        i++;
    }

    fprintf(resultado, "2 EIXOS, VELOCIDADE MAX: %.1f, VELOCIDADE MIN: %.1f\n", eixo[2].eixovmax, eixo[2].eixovmin);
    fprintf(resultado, "2 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", comprim[2].eixocmax, comprim[2].eixocmin);
    fprintf(resultado, "\n3 EIXOS, VELOCIDADE MAX: %.1f, VELOCIDADE MIN: %.1f\n", eixo[3].eixovmax, eixo[3].eixovmin);
    fprintf(resultado, "3 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", comprim[3].eixocmax, comprim[3].eixocmin);
    fprintf(resultado, "\n5 EIXOS, VELOCIDADE MAX: %.1f, VELOCIDADE MIN: %.1f\n", eixo[5].eixovmax, eixo[5].eixovmin);
    fprintf(resultado, "5 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", comprim[5].eixocmax, comprim[5].eixocmin);
    fprintf(resultado, "\n7 EIXOS, VELOCIDADE MAX: %.1f, VELOCIDADE MIN: %.1f\n", eixo[7].eixovmax, eixo[7].eixovmin);
    fprintf(resultado, "7 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", comprim[7].eixocmax, comprim[7].eixocmin);
    fprintf(resultado, "\n9 EIXOS, VELOCIDADE MAX: %.1f, VELOCIDADE MIN: %.1f\n", eixo[9].eixovmax, eixo[9].eixovmin);
    fprintf(resultado, "9 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", comprim[9].eixocmax, comprim[9].eixocmin);

    fclose(arquivo);
    fclose(resultado);
    return 0;
}

void velo(void) {
    int eixos = veiculos[i].eixos;
    if (eixos == 2 || eixos == 3 || eixos == 5 || eixos == 7 || eixos == 9) {
        if (veiculos[i].velocidade >= eixo[eixos].eixovmax) {
            eixo[eixos].eixovmax = veiculos[i].velocidade;
        }
        if (veiculos[i].velocidade <= eixo[eixos].eixovmin) {
            eixo[eixos].eixovmin = veiculos[i].velocidade;
        }
    }
}

void compri(void) {
    int eixos = veiculos[i].eixos;
    if (eixos == 2 || eixos == 3 || eixos == 5 || eixos == 7 || eixos == 9) {
        if (veiculos[i].comprimento >= comprim[eixos].eixocmax) {
            comprim[eixos].eixocmax = veiculos[i].comprimento;
        }
        if (veiculos[i].comprimento <= comprim[eixos].eixocmin) {
            comprim[eixos].eixocmin = veiculos[i].comprimento;
        }
    }
}
