#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct veiculo {
    float velocidade;
    float comprimento;
    int eixos;
};

struct deltavelo {
    float eixovmax;
    float eixovmin;
};

struct deltacomprimento {
    float eixocmax;
    float eixocmin;
};

struct falha
{
    int exvmaxfalha;
    int exvminfalha;
    int excmaxfalha;
    int excminfalha;
};



char linha[1024];  // Define um buffer para armazenar cada linha
const char delimitador[] = ";";
struct veiculo veiculos[500];
struct deltavelo veloci[9];
struct deltacomprimento comprim[15];
struct falha erro[9];

int i = 0;  // contadores

int total2 = 0,
    total3 = 0,
    total5 = 0,
    total7 = 0,
    total9 = 0;

const float vmax[] = {0.0, 0.0, 19.6, 18.9, 0.0, 11.4, 0.0, 11.4, 0.0, 11.1};
const float vmin[] = {0.0, 0.0, 11.1, 15.7, 0.0, 10.6, 0.0, 11.3, 0.0, 11.1};

const float cmax[] = {0.0, 0.0, 1.7, 3.0, 0.0, 1.5, 0.0, 3.1, 0.0, 3.5};
const float cmin[] = {0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0};

void velo(void);
void compri(void);
void veloreslt(void);
void comprireslt(void);

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
    veloci[2].eixovmin = 200.0;
    veloci[3].eixovmin = 200.0;
    veloci[5].eixovmin = 200.0;
    veloci[7].eixovmin = 200.0;
    veloci[9].eixovmin = 200.0;
    
    comprim[2].eixocmin = 200.0;
    comprim[3].eixocmin = 200.0;
    comprim[5].eixocmin = 200.0;
    comprim[7].eixocmin = 200.0;
    comprim[9].eixocmin = 200.0;


    while (fgets(linha, sizeof(linha), arquivo)) {
    linha[strcspn(linha, "\n")] = 0;
    char *campo = strtok(linha, delimitador);
    int coluna = 0;
    //int campos_validos = 1;  // Verificador de campos válidos

        while (campo != NULL) {
            if (coluna == 3) {
                veiculos[i].velocidade = strtof(campo, NULL);
                //if (veiculos[i].velocidade < 0) campos_validos = 0;
                //printf("Velocidade = %.1f\n", veiculos[i].velocidade);

            } else if (coluna == 4) {
                veiculos[i].comprimento = strtof(campo, NULL);
                //if (veiculos[i].comprimento < 0) campos_validos = 0;
                //printf("Comprimento = %.1f\n", veiculos[i].comprimento);

            } else if (coluna == 6) {
                veiculos[i].eixos = atoi(campo);
                //if (veiculos[i].eixos <= 0) campos_validos = 0;
                //printf("Eixos = %d\n", veiculos[i].eixos);
            
            }
            campo = strtok(NULL, delimitador);
            coluna++;
        }
        velo();
        compri();
        i++;

    }

    fprintf(resultado, "\n2 EIXOS -  VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN:  %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[2].eixovmax, veloci[2].eixovmin, erro[2].exvmaxfalha, erro[2].exvminfalha, total2);
    fprintf(resultado, "2 EIXOS -  COMPRIMENTO MAX:  %.1f m   - COMPRIMENTO MIN:     %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[2].eixocmax, comprim[2].eixocmin, erro[2].excmaxfalha, erro[2].excminfalha);
    fprintf(resultado, "\n3 EIXOS -  VELOCIDADE MAX:  %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[3].eixovmax, veloci[3].eixovmin, erro[3].exvmaxfalha, erro[3].exvminfalha, total3);
    fprintf(resultado, "3 EIXOS -  COMPRIMENTO MAX:  %.1f m   - COMPRIMENTO MIN:   %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[3].eixocmax, comprim[3].eixocmin, erro[3].excmaxfalha, erro[3].excminfalha);
    fprintf(resultado, "\n5 EIXOS -  VELOCIDADE MAX:  %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[5].eixovmax, veloci[5].eixovmin, erro[5].exvmaxfalha, erro[5].exvminfalha, total5);
    fprintf(resultado, "5 EIXOS -  COMPRIMENTO MAX:  %.1f m   - COMPRIMENTO MIN:   %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[5].eixocmax, comprim[5].eixocmin, erro[5].excmaxfalha, erro[5].excminfalha);
    fprintf(resultado, "\n7 EIXOS -  VELOCIDADE MAX:  %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[7].eixovmax, veloci[7].eixovmin, erro[7].exvmaxfalha, erro[7].exvminfalha, total7);
    fprintf(resultado, "7 EIXOS -  COMPRIMENTO MAX:  %.1f m   - COMPRIMENTO MIN:   %.1f m - FALHA V-MAX: %d - FALHA C-MIN: %d\n", comprim[7].eixocmax, comprim[7].eixocmin, erro[7].excmaxfalha, erro[7].excminfalha);
    fprintf(resultado, "\n9 EIXOS -  VELOCIDADE MAX:  %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[9].eixovmax, veloci[9].eixovmin, erro[9].exvmaxfalha, erro[9].exvminfalha, total9);
    fprintf(resultado, "9 EIXOS -  COMPRIMENTO MAX:  %.1f m   - COMPRIMENTO MIN:   %.1f m - FALHA V-MAX: %d - FALHA C-MIN: %d\n", comprim[9].eixocmax, comprim[9].eixocmin, erro[9].excmaxfalha, erro[9].excminfalha);

    fclose(arquivo);
    fclose(resultado);
    return 0;
}

void velo(void) {
    int eixos1 = veiculos[i].eixos;
    if (eixos1 == 2 || eixos1 == 3 || eixos1 == 5 || eixos1 == 7 || eixos1 == 9) {
        if (veiculos[i].velocidade >= veloci[eixos1].eixovmax) {
            veloci[eixos1].eixovmax = veiculos[i].velocidade;
            if(veloci[eixos1].eixovmax > vmax[eixos1]){
                erro[eixos1].exvmaxfalha++;
            }            
        }
        if (veiculos[i].velocidade <= veloci[eixos1].eixovmin) {
            veloci[eixos1].eixovmin = veiculos[i].velocidade;
            if(veloci[eixos1].eixovmin < vmin[eixos1]){
                erro[eixos1].exvminfalha++;
            }
        }

        if(eixos1 == 2){
            total2++;
        }
        if(eixos1 == 3){
            total3++;
        }
        if(eixos1 == 5){
            total5++;
        }
        if(eixos1 == 7){
            total7++;
        }
        if(eixos1 == 9){
            total9++;
        }
    }
}

void compri(void) {
    int eixos2 = veiculos[i].eixos;
    if (eixos2 == 2 || eixos2 == 3 || eixos2 == 5 || eixos2 == 7 || eixos2 == 9) {
        if (veiculos[i].comprimento >= comprim[eixos2].eixocmax) {
            comprim[eixos2].eixocmax = veiculos[i].comprimento;
        }
        if (veiculos[i].comprimento <= comprim[eixos2].eixocmin) {
            comprim[eixos2].eixocmin = veiculos[i].comprimento;
        }
    }
}

void comprireslt(void) {
    int eixos4 = veiculos[i].eixos;
    if (eixos4 >= 2 && eixos4 <= 9 && (eixos4 % 2 == 1 || eixos4 == 2)) {
        if (comprim[eixos4].eixocmax > cmax[eixos4]) {
            erro[eixos4].excmaxfalha++;
        }
        if (comprim[eixos4].eixocmin < cmin[eixos4]) {
            erro[eixos4].excminfalha++;
        }
    }
}