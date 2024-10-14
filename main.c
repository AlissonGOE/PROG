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
    int campos_validos = 1;  // Verificador de campos válidos

    while (campo != NULL) {
        if (coluna == 3) {
            veiculos[i].velocidade = strtof(campo, NULL);
            if (veiculos[i].velocidade < 0) campos_validos = 0;
            //printf("Velocidade = %.1f\n", veiculos[i].velocidade);

        } else if (coluna == 4) {
            veiculos[i].comprimento = strtof(campo, NULL);
            if (veiculos[i].comprimento < 0) campos_validos = 0;
            //printf("Comprimento = %.1f\n", veiculos[i].comprimento);

        } else if (coluna == 6) {
            veiculos[i].eixos = atoi(campo);
            if (veiculos[i].eixos <= 0) campos_validos = 0;
            //printf("Eixos = %d\n", veiculos[i].eixos);
            
        }
        campo = strtok(NULL, delimitador);
        coluna++;
    }

    if (campos_validos) {
        velo();
        compri();
        i++;
    } else {
        printf("Dados inválidos na linha %d. Linha ignorada.\n", i + 1);
    }
}

    fprintf(resultado, "\n2 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", eixo[2].eixovmax, eixo[2].eixovmin, erro[2].exvmaxfalha, erro[2].exvminfalha, total2);
    fprintf(resultado, "2 EIXOS - COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[2].eixocmax, comprim[2].eixocmin, erro[2].excmaxfalha, erro[2].excminfalha);
    fprintf(resultado, "\n3 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", eixo[3].eixovmax, eixo[3].eixovmin, erro[3].exvmaxfalha, erro[3].exvminfalha, total3);
    fprintf(resultado, "3 EIXOS - COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[3].eixocmax, comprim[3].eixocmin, erro[3].excmaxfalha, erro[3].excminfalha);
    fprintf(resultado, "\n5 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", eixo[5].eixovmax, eixo[5].eixovmin, erro[5].exvmaxfalha, erro[5].exvminfalha, total5);
    fprintf(resultado, "5 EIXOS - COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[5].eixocmax, comprim[5].eixocmin, erro[5].excmaxfalha, erro[5].excminfalha);
    fprintf(resultado, "\n7 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", eixo[7].eixovmax, eixo[7].eixovmin, erro[7].exvmaxfalha, erro[7].exvminfalha, total7);
    fprintf(resultado, "7 EIXOS - COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA V-MAX: %d - FALHA C-MIN: %d\n", comprim[7].eixocmax, comprim[7].eixocmin, erro[7].excmaxfalha, erro[7].excminfalha);
    fprintf(resultado, "\n9 EIXOS - VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN: %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", eixo[9].eixovmax, eixo[9].eixovmin, erro[9].exvmaxfalha, erro[9].exvminfalha, total9);
    fprintf(resultado, "9 EIXOS- COMPRIMENTO MAX:     %.1f m - COMPRIMENTO MIN:    %.1f m - FALHA V-MAX: %d - FALHA C-MIN: %d\n", comprim[9].eixocmax, comprim[9].eixocmin, erro[9].excmaxfalha, erro[9].excminfalha);

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

        if(eixos == 2){
            total2++;
        }
        if(eixos == 3){
            total3++;
        }
        if(eixos == 5){
            total5++;
        }
        if(eixos == 7){
            total7++;
        }
        if(eixos == 9){
            total9++;
        }
    }
    veloreslt();

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
    comprireslt();
}

void veloreslt(void) {
    int eixos = veiculos[i].eixos;
    if (eixos >= 2 && eixos <= 9 && (eixos % 2 == 1 || eixos == 2)) {
        if (veiculos[eixos].velocidade > vmax[eixos]) {
            erro[eixos].exvmaxfalha++;
        }
        if(veiculos[eixos].velocidade < vmin[eixos]) {
            erro[eixos].exvminfalha++;
        }
    }
}

void comprireslt(void) {
    int eixos = veiculos[i].eixos;
    if (eixos >= 2 && eixos <= 9 && (eixos % 2 == 1 || eixos == 2)) {
        if (comprim[eixos].eixocmax > cmax[eixos]) {
            erro[eixos].excmaxfalha++;
        }
        if (comprim[eixos].eixocmin < cmin[eixos]) {
            erro[eixos].excminfalha++;
        }
    }
}