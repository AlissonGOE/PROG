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
struct deltaeixo eixo[9];
struct deltacomprimento comprim[9];
struct falha erro[9];
int i = 0;  // contadores

int total2 = 0,
    total3 = 0,
    total5 = 0,
    total7 = 0,
    total9 = 0;


float eixo2vmax = 19.6,
      eixo2vmin = 12.1,

      eixo3vmax = 18.9,
      eixo3vmin = 18.7,

      eixo5vmax = 11.4,
      eixo5vmin = 10.6,

      eixo7vmax = 11.4,
      eixo7vmin = 11.3,

      eixo9vmax = 11.1,
      eixo9vmin = 11.1;

void velo(void);
void compri(void);
void veloreslt(void);

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

    fprintf(resultado, "\n2 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA MAX: %d - FALHA VMIN: %d - TOTAL DE VEICULOS: %d\n", eixo[2].eixovmax, eixo[2].eixovmin, erro[2].exvmaxfalha, erro[2].exvminfalha, total2);
    fprintf(resultado, "2 EIXOS - COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA MAX: %d - FALHA VMIN: %d\n", comprim[2].eixocmax, comprim[2].eixocmin);
    fprintf(resultado, "\n3 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA MAX: %d - FALHA VMIN: %d - TOTAL DE VEICULOS: %d\n", eixo[3].eixovmax, eixo[3].eixovmin, erro[3].exvmaxfalha, erro[3].exvminfalha, total3);
    fprintf(resultado, "3 EIXOS - COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA MAX: %d - FALHA VMIN: %d\n", comprim[3].eixocmax, comprim[3].eixocmin);
    fprintf(resultado, "\n5 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA MAX: %d - FALHA VMIN: %d - TOTAL DE VEICULOS: %d\n", eixo[5].eixovmax, eixo[5].eixovmin, erro[5].exvmaxfalha, erro[5].exvminfalha, total5);
    fprintf(resultado, "5 EIXOS - COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA MAX: %d - FALHA VMIN: %d\n", comprim[5].eixocmax, comprim[5].eixocmin);
    fprintf(resultado, "\n7 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA MAX: %d - FALHA VMIN: %d - TOTAL DE VEICULOS: %d\n", eixo[7].eixovmax, eixo[7].eixovmin, erro[7].exvmaxfalha, erro[7].exvminfalha, total7);
    fprintf(resultado, "7 EIXOS - COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA MAX: %d - FALHA VMIN: %d\n", comprim[7].eixocmax, comprim[7].eixocmin);
    fprintf(resultado, "\n9 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA MAX: %d - FALHA VMIN: %d - TOTAL DE VEICULOS: %d\n", eixo[9].eixovmax, eixo[9].eixovmin, erro[9].exvmaxfalha, erro[9].exvminfalha, total9);
    fprintf(resultado, "9 EIXOS- COMPRIMENTO MAX:     %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA MAX: %d - FALHA VMIN: %d\n", comprim[9].eixocmax, comprim[9].eixocmin);

    fclose(arquivo);
    fclose(resultado);
    return 0;
}

void velo(void) {
    int eixos = veiculos[i].eixos;
    if (eixos == 2 || eixos == 3 || eixos == 5 || eixos == 7 || eixos == 9) {
        if (veiculos[i].velocidade >= eixo[eixos].eixovmax) {
            eixo[eixos].eixovmax = veiculos[i].velocidade;
            veloreslt();
        }
        if (veiculos[i].velocidade <= eixo[eixos].eixovmin) {
            eixo[eixos].eixovmin = veiculos[i].velocidade;
            veloreslt();
        }
        if(eixos == 2){
            total2++;
        }
        if(eixos == 3){
            total3++;
        }
        if(eixos == 3){
            total5++;
        }
        if(eixos == 7){
            total7++;
        }
        if(eixos == 9){
            total9++;
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

void veloreslt(void){

    int eixos = veiculos[i].eixos;
    if (eixos == 2) {
        if(eixo[eixos].eixovmax > eixo2vmax){
            erro[2].exvmaxfalha++;
        }
        if(eixo[eixos].eixovmin < eixo2vmin){
            erro[2].exvminfalha++;
        }
    }

    if (eixos == 3) {
        if(eixo[eixos].eixovmax > eixo3vmax){
            erro[3].exvmaxfalha++;
        }
        if(eixo[eixos].eixovmin < eixo3vmin){
            erro[3].exvminfalha++;
        }
    }

    if (eixos == 5) {
        if(eixo[eixos].eixovmax > eixo5vmax){
            erro[5].exvmaxfalha++;
        }
        if(eixo[eixos].eixovmin < eixo5vmin){
            erro[5].exvminfalha++;
        }
    }

    if (eixos == 7) {
        if(eixo[eixos].eixovmax > eixo7vmax){
            erro[7].exvmaxfalha++;
        }
        if(eixo[eixos].eixovmin < eixo7vmin){
            erro[7].exvminfalha++;
        }
    }

    if (eixos == 9) {
        if(eixo[eixos].eixovmax > eixo9vmax){
            erro[9].exvmaxfalha++;
        }
        if(eixo[eixos].eixovmin < eixo9vmin){
            erro[9].exvminfalha++;
        }
    }
}