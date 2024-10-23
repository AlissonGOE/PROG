#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"

struct veiculo {
    float velocidade;
    float comprimento;
    float peso;
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

struct deltapeso
{
    float eixopmax;
    float eixopmin;
};


struct falha
{
    int exvmaxfalha;
    int exvminfalha;
    int excmaxfalha;
    int excminfalha;
    int expmaxfalha;
    int expminfalha;
};

enum printerror{
    printof = 0,
    printon ,
};

enum transito{
    satpevr = 0,
    satpevrc,
    somentelacos,
    somentepiezos,
    satpe,
    sat,
};

// char linha[102400];  // Define um buffer para armazenar cada linha
// char linhaanterior[102400] = "";
const char delimitador[] = ";";
struct veiculo veiculos[2000];
struct deltavelo veloci[50];
struct deltacomprimento comprim[50];
struct deltapeso pes[50];
struct falha erro[50];
enum printerror set;
enum transito modotransito;

int ganho = 0;
int i = 1,  // contadores
    counterror = 0;

char fvelo = ' ';
char fcomp = ' ';
char fpeso = ' ';
char feixo = ' ';

int total2 = 0,
    total3 = 0,
    total5 = 0,
    total7 = 0,
    total9 = 0,
    totaleixoerror = 0;

float vmax[] = {0.0, 0.0, 19.6, 18.9, 0.0, 11.4, 0.0, 11.4, 0.0, 11.1}; // range da simuladora
float vmin[] = {0.0, 0.0, 11.1, 15.7, 0.0, 10.6, 0.0, 11.3, 0.0, 11.1};

float cmax[] = {0.0, 0.0, 3.5, 3.0, 0.0, 1.5, 0.0, 3.1, 0.0, 3.5};
float cmin[] = {0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0};

float pmax[] = {0.0, 0.0, 8.2, 8.6, 0.0, 8.6, 0.0, 12.1, 0.0, 14.9};
float pmin[] = {0.0, 0.0, 1.0, 4.0, 0.0, 3.0, 0.0, 5.2, 0.0, 6.5};

void velo(void);
void compri(void);
void peso(void);
void copy_wst_sat_pe(void);
FILE *abrirarquivo(const char *nomearquivo);
void init_valores_minimos(void);
void registrarErro(FILE *erros, const char *linha, const char *linhaanterior, char feixo, char fvelo, char fcomp, char fpeso, struct veiculo veiculos[], int i);
void processa_linha_arquivo(FILE *arquivo, FILE *erros, const char *delimitador);

int main() {

    system("CLS");

    printf("\n PROGRAMA PARA ANALISAR ARQUIVO DE TRANSITO SAT-PE-SB\n");
    printf(" --------------------------------------------------------------------------------04--03--02--01--\n");
    printf(" 01 - SAT-PE(Transito)                                                   DIP-SW: OFF OFF OFF OFF\n");                                           
    printf(" 02 - SAT-PE(Transito variado e repetitivo)                              DIP-SW: OFF OFF OFF \033[32mON\033[0m \n");
    printf(" 03 - SAT(Transito variado e rondomico em cada canal)                    DIP-SW: OFF OFF \033[32mON\033[0m  OFF\n");
    printf(" 04 - SAT-PE(Transito variado e repetitivo em todos os canais)           DIP-SW: OFF OFF \033[32mON\033[0m  \033[32mON\033[0m \n");
    printf(" 05 - Somente lacos(Transito unico/repetitivo)                           DIP-SW: OFF \033[32mON\033[0m  OFF OFF\n");
    printf(" 06 - Somente piezos(Transito unico/repetitivo)                          DIP-SW: OFF \033[32mON\033[0m  OFF \033[32mON\033[0m \n");
    printf(" ------------------------------------------------------------------------------------------------\n");
    printf(" Selecione o modo de transito do arquivo: ");
    scanf("%d", &modotransito);

    switch (modotransito)
    {
    case 1:
        printf("\n Modo de transito selecionado: \033[32m01 - SAT-PE(Transito)\033[0m\n"); 
        break;
    
    case 2:
        printf("\n Modo de transito selecionado: \033[32m02 - SAT-PE(Transito variado e repetitivo)\033[0m\n");
        printf(" -------------------\n");
        printf(" 01 - Ganho MAXIMO\n");
        printf(" 02 - Ganho MINIMO\n");
        printf(" -------------------\n");
        printf(" Selecione o ganho dos piezos de pesagem: ");
        scanf("%d", &ganho);
        switch (ganho)
        {
        case 1:
            printf(GREEN" Ganho maximo selecionado\n"RESET);

            vmax[2] = 19.8, vmax[3] = 19.0, vmax[5] = 11.6, vmax[7] = 11.6, vmax[9] = 11.3; 
            vmin[2] = 19.4, vmin[3] = 18.6, vmin[5] = 11.2, vmin[7] = 11.2, vmin[9] = 10.9;
            cmax[2] = 1.9, cmax[3] = 3.1, cmax[5] = 1.7, cmax[7] = 3.3, cmax[9] = 3.7;
            cmin[2] = 1.5, cmin[3] = 2.7, cmin[5] = 1.3, cmin[7] = 2.9, cmin[9] = 3.3;
            pmax[2] = 1.0, pmax[3] = 20.65, pmax[5] = 20.5, pmax[7] = 28.7, pmax[9] = 35.4; 
            pmin[2] = 1.0, pmin[3] = 18.65, pmin[5] = 18.6, pmin[7] = 26.0, pmin[9] = 32.0;
            copy_wst_sat_pe();
            break;
        
        case 2:
            printf(GREEN" Ganho minimo selecionado\n"RESET);

            vmax[2] = 19.8, vmax[3] = 19.0, vmax[5] = 11.6, vmax[7] = 11.6, vmax[9] = 11.3; 
            vmin[2] = 19.4, vmin[3] = 18.6, vmin[5] = 11.2, vmin[7] = 11.2, vmin[9] = 10.9;
            cmax[2] = 1.9, cmax[3] = 3.1, cmax[5] = 1.7, cmax[7] = 3.3, cmax[9] = 3.7;
            cmin[2] = 1.5, cmin[3] = 2.7, cmin[5] = 1.3, cmin[7] = 2.9, cmin[9] = 3.3;
            pmax[2] = 1.0, pmax[3] = 4.9, pmax[5] = 4.9, pmax[7] = 6.8, pmax[9] = 8.4; 
            pmin[2] = 1.0, pmin[3] = 4.4, pmin[5] = 4.4, pmin[7] = 6.2, pmin[9] = 7.6;
            copy_wst_sat_pe();
            break;
    
        }
        break;

    case 3:
        printf("\n Modo de transito selecionado: \033[32m03 - SAT(Transito variado e rondomico em cada canal)\033[0m\n");
        break;

    case 4:
        printf("\n Modo de transito selecionado: \033[32m04 - SAT-PE(Transito variado e repetitivo em todos os canais)\033[0m\n");
        break;

    case 5:
        printf("\n Modo de transito selecionado: \033[32m05 - Somente lacos(Transito unico/repetitivo)\033[0m\n");
        break;

    case 6:
        printf("\n Modo de transito selecionado: \033[32m06 - Somente piezos(Transito unico/repetitivo)\033[0m\n");
        break;

    default:
        printf(RED"Digite uma opcao valida!!!"RESET);
        break;
    }

    FILE *arquivo = abrirarquivo("dados.txt");
    FILE *resultado = abrirarquivo("resultado.txt");
    FILE *erros = abrirarquivo("erros.txt");
    
    init_valores_minimos();
    processa_linha_arquivo(arquivo, erros, delimitador);

    fprintf(resultado, "\n2 EIXOS -  VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN:  %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[2].eixovmax, veloci[2].eixovmin, erro[2].exvmaxfalha, erro[2].exvminfalha, total2);
    fprintf(resultado, "2 EIXOS -  COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:     %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[2].eixocmax, comprim[2].eixocmin, erro[2].excmaxfalha, erro[2].excminfalha);
    fprintf(resultado, "2 EIXOS -  PESO MAX:        %.2f PBT - PESO MIN:         %.2f PBT - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[2].eixopmax, pes[2].eixopmin, erro[2].expmaxfalha, erro[2].expminfalha);
    fprintf(resultado, "\n3 EIXOS -  VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN:  %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[3].eixovmax, veloci[3].eixovmin, erro[3].exvmaxfalha, erro[3].exvminfalha, total3);
    fprintf(resultado, "3 EIXOS -  COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:     %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[3].eixocmax, comprim[3].eixocmin, erro[3].excmaxfalha, erro[3].excminfalha);
    fprintf(resultado, "3 EIXOS -  PESO MAX:       %.2f PBT - PESO MIN:        %.2f PBT - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[3].eixopmax, pes[3].eixopmin, erro[3].expmaxfalha, erro[3].expminfalha);
    fprintf(resultado, "\n5 EIXOS -  VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN:  %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[5].eixovmax, veloci[5].eixovmin, erro[5].exvmaxfalha, erro[5].exvminfalha, total5);
    fprintf(resultado, "5 EIXOS -  COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:     %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[5].eixocmax, comprim[5].eixocmin, erro[5].excmaxfalha, erro[5].excminfalha);
    fprintf(resultado, "5 EIXOS -  PESO MAX:       %.2f PBT - PESO MIN:        %.2f PBT - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[5].eixopmax, pes[5].eixopmin, erro[5].expmaxfalha, erro[5].expminfalha);
    fprintf(resultado, "\n7 EIXOS -  VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN:  %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[7].eixovmax, veloci[7].eixovmin, erro[7].exvmaxfalha, erro[7].exvminfalha, total7);
    fprintf(resultado, "7 EIXOS -  COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:     %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[7].eixocmax, comprim[7].eixocmin, erro[7].excmaxfalha, erro[7].excminfalha);
    fprintf(resultado, "7 EIXOS -  PESO MAX:       %.2f PBT - PESO MIN:        %.2f PBT - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[7].eixopmax, pes[7].eixopmin, erro[7].expmaxfalha, erro[7].expminfalha);
    fprintf(resultado, "\n9 EIXOS -  VELOCIDADE MAX: %.1f Km/h - VELOCIDADE MIN:  %.1f Km/h - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[9].eixovmax, veloci[9].eixovmin, erro[9].exvmaxfalha, erro[9].exvminfalha, total9);
    fprintf(resultado, "9 EIXOS -  COMPRIMENTO MAX:    %.1f m - COMPRIMENTO MIN:     %.1f m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[9].eixocmax, comprim[9].eixocmin, erro[9].excmaxfalha, erro[9].excminfalha);
    fprintf(resultado, "9 EIXOS -  PESO MAX:       %.2f PBT - PESO MIN:        %.2f PBT - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[9].eixopmax, pes[9].eixopmin, erro[9].expmaxfalha, erro[9].expminfalha);
    fprintf(resultado, "\nTOTAL DE TRANSITOS COLETADOS: %d", total2 + total3 + total5 + total7 + total9 + totaleixoerror);
    fprintf(resultado, "\n TOTAL DE TRANSITOS COM ERROS: %d", counterror);

    printf("\n \033[32m2\033[0m EIXOS -  VELOCIDADE MAX: \033[32m%.1f Km/h\033[0m - VELOCIDADE MIN:  \033[32m%.1f Km/h\033[0m - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[2].eixovmax, veloci[2].eixovmin, erro[2].exvmaxfalha, erro[2].exvminfalha, total2);
    printf(" \033[32m2\033[0m EIXOS -  COMPRIMENTO MAX:    \033[32m%.1f m\033[0m - COMPRIMENTO MIN:     \033[32m%.1f m\033[0m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[2].eixocmax, comprim[2].eixocmin, erro[2].excmaxfalha, erro[2].excminfalha);
    printf(" \033[32m2\033[0m EIXOS -  PESO MAX:        \033[32m%.2f PBT\033[0m - PESO MIN:         \033[32m%.2f PBT\033[0m - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[2].eixopmax, pes[2].eixopmin, erro[2].expmaxfalha, erro[2].expminfalha);
    printf("\n \033[32m3\033[0m EIXOS -  VELOCIDADE MAX: \033[32m%.1f Km/h\033[0m - VELOCIDADE MIN:  \033[32m%.1f Km/h\033[0m - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[3].eixovmax, veloci[3].eixovmin, erro[3].exvmaxfalha, erro[3].exvminfalha, total3);
    printf(" \033[32m3\033[0m EIXOS -  COMPRIMENTO MAX:    \033[32m%.1f m\033[0m - COMPRIMENTO MIN:     \033[32m%.1f m\033[0m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[3].eixocmax, comprim[3].eixocmin, erro[3].excmaxfalha, erro[3].excminfalha);
    printf(" \033[32m3\033[0m EIXOS -  PESO MAX:       \033[32m%.2f PBT\033[0m - PESO MIN:        \033[32m%.2f PBT\033[0m - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[3].eixopmax, pes[3].eixopmin, erro[3].expmaxfalha, erro[3].expminfalha);
    printf("\n \033[32m5\033[0m EIXOS -  VELOCIDADE MAX: \033[32m%.1f Km/h\033[0m - VELOCIDADE MIN:  \033[32m%.1f Km/h\033[0m - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[5].eixovmax, veloci[5].eixovmin, erro[5].exvmaxfalha, erro[5].exvminfalha, total5);
    printf(" \033[32m5\033[0m EIXOS -  COMPRIMENTO MAX:    \033[32m%.1f m\033[0m - COMPRIMENTO MIN:     \033[32m%.1f m\033[0m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[5].eixocmax, comprim[5].eixocmin, erro[5].excmaxfalha, erro[5].excminfalha);
    printf(" \033[32m5\033[0m EIXOS -  PESO MAX:       \033[32m%.2f PBT\033[0m - PESO MIN:        \033[32m%.2f PBT\033[0m - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[5].eixopmax, pes[5].eixopmin, erro[5].expmaxfalha, erro[5].expminfalha);
    printf("\n \033[32m7\033[0m EIXOS -  VELOCIDADE MAX: \033[32m%.1f Km/h\033[0m - VELOCIDADE MIN:  \033[32m%.1f Km/h\033[0m - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[7].eixovmax, veloci[7].eixovmin, erro[7].exvmaxfalha, erro[7].exvminfalha, total7);
    printf(" \033[32m7\033[0m EIXOS -  COMPRIMENTO MAX:    \033[32m%.1f m\033[0m - COMPRIMENTO MIN:     \033[32m%.1f m\033[0m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[7].eixocmax, comprim[7].eixocmin, erro[7].excmaxfalha, erro[7].excminfalha);
    printf(" \033[32m7\033[0m EIXOS -  PESO MAX:       \033[32m%.2f PBT\033[0m - PESO MIN:        \033[32m%.2f PBT\033[0m - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[7].eixopmax, pes[7].eixopmin, erro[7].expmaxfalha, erro[7].expminfalha);
    printf("\n \033[32m9\033[0m EIXOS -  VELOCIDADE MAX: \033[32m%.1f Km/h\033[0m - VELOCIDADE MIN:  \033[32m%.1f Km/h\033[0m - FALHA V-MAX: %d - FALHA V-MIN: %d - TOTAL DE VEICULOS: %d\n", veloci[9].eixovmax, veloci[9].eixovmin, erro[9].exvmaxfalha, erro[9].exvminfalha, total9);
    printf(" \033[32m9\033[0m EIXOS -  COMPRIMENTO MAX:    \033[32m%.1f m\033[0m - COMPRIMENTO MIN:     \033[32m%.1f m\033[0m - FALHA C-MAX: %d - FALHA C-MIN: %d\n", comprim[9].eixocmax, comprim[9].eixocmin, erro[9].excmaxfalha, erro[9].excminfalha);
    printf(" \033[32m9\033[0m EIXOS -  PESO MAX:       \033[32m%.2f PBT\033[0m - PESO MIN:        \033[32m%.2f PBT\033[0m - FALHA P-MAX: %d - FALHA P-MIN: %d\n", pes[9].eixopmax, pes[9].eixopmin, erro[9].expmaxfalha, erro[9].expminfalha);
    printf("\n TOTAL DE TRANSITOS COLETADOS: %d", total2 + total3 + total5 + total7 + total9 + totaleixoerror);
    printf("\n TOTAL DE TRANSITOS COM ERRO: \033[31m%d\033[0m", counterror);


    fclose(arquivo);
    fclose(resultado);
    fclose(erros);

    printf(GREEN"\n\n Teste finalizado com sucesso!!\n\n"RESET);
    system("PAUSE");
    return 0;
}

void velo(void) {
    int eixos1 = veiculos[i].eixos;
    if (eixos1 == 2 || eixos1 == 3 || eixos1 == 5 || eixos1 == 7 || eixos1 == 9) {
        if (veiculos[i].velocidade >= veloci[eixos1].eixovmax) {
            veloci[eixos1].eixovmax = veiculos[i].velocidade;
            if(veloci[eixos1].eixovmax > vmax[eixos1]){
                erro[eixos1].exvmaxfalha++;
                set = 1;
                fvelo = 'V';

            }            
        }
        if (veiculos[i].velocidade <= veloci[eixos1].eixovmin) {
            veloci[eixos1].eixovmin = veiculos[i].velocidade;
            if(veloci[eixos1].eixovmin < vmin[eixos1]){
                erro[eixos1].exvminfalha++;
                set = 1;
                fvelo = 'V';
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
    else{
        //contagem de eixos divergente
        set = 1;
        totaleixoerror++;
        feixo = 'E';
    }
}

void compri(void) {
    int eixos2 = veiculos[i].eixos;
    if (eixos2 == 2 || eixos2 == 3 || eixos2 == 5 || eixos2 == 7 || eixos2 == 9) {
        if (veiculos[i].comprimento >= comprim[eixos2].eixocmax) {
            comprim[eixos2].eixocmax = veiculos[i].comprimento;
            if(comprim[eixos2].eixocmax > cmax[eixos2]){
                erro[eixos2].excmaxfalha++;
                set = 1;
                fcomp = 'C';
            }
        }
        if (veiculos[i].comprimento <= comprim[eixos2].eixocmin) {
            comprim[eixos2].eixocmin = veiculos[i].comprimento;
            if(comprim[eixos2].eixocmin < cmin[eixos2]){
                erro[eixos2].excminfalha++;
                set = 1;
                fcomp = 'C';
            }
        }
    }
}

void peso(void){
    int eixos3 = veiculos[i].eixos;
    if(eixos3 == 2 || eixos3 == 3 || eixos3 == 5 || eixos3 == 7 || eixos3 == 9){
        if (veiculos[i].peso >= pes[eixos3].eixopmax){
            pes[eixos3].eixopmax = veiculos[i].peso;
            if(pes[eixos3].eixopmax > pmax[eixos3]){
                erro[eixos3].expmaxfalha++;
                set = 1;
                fpeso = 'P';
            }
        }

        if (veiculos[i].peso <= pes[eixos3].eixopmin) {
            pes[eixos3].eixopmin = veiculos[i].peso;
            if(pes[eixos3].eixopmin < pmin[eixos3]){
                erro[eixos3].expminfalha++;
                set = 1;
                fpeso = 'P';
            }
        }
    }
}

void copy_wst_sat_pe(void){
    // char fliez;
    // printf(RED" COPIE OS ARQUIVOS DE LOG PARA O DIRETORIO !!!\n"RESET);
    // printf(RED"\n DESEJA ABRIR O FILEZILA ? S/N: \n"RESET);
    // scanf("%c", &fliez);
    // if ((fliez == 'S') || (fliez == 's')){
    //     printf(RED"\n ENTRE NO FILEZILA COM O IP, USUARIO E SENHA DO EQUIPAMENTO \n"RESET);
    //     system("C:\\Users\\alisson.evangelista\\Documents\\ALISSON\\PROGRAMAS\\FileZillaPortable\\FileZillaPortable.exe");
    // }
    // system("explorer \"ARQUIVOS_SAT_PE_SB\"");
    // system("PAUSE");
    // system("type nul > dados.txt");
    // system("copy \"ARQUIVOS_SAT_PE_SB\\*.wst\" dados.txt");
}

FILE *abrirarquivo(const char *nomeArquivo){
        FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
    } else {
        printf("\nArquivo %s aberto com sucesso!\n", nomeArquivo);
    }
    return arquivo;
}

void init_valores_minimos(void){
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

    pes[2].eixopmin = 200.0;
    pes[3].eixopmin = 200.0;
    pes[5].eixopmin = 200.0;
    pes[7].eixopmin = 200.0;
    pes[9].eixopmin = 200.0;
}

void registrarErro(FILE *erros, const char *linha, const char *linhaanterior, char feixo, char fvelo, char fcomp, char fpeso, struct veiculo veiculos[], int i) {
    if (erros != NULL) { // Verifica se o arquivo está aberto
        fprintf(erros, "ERROR(%c%c%c%c) - %d EIXOS - VELOCIDADE: %.1f Km/h - COMPRIMENTO: %.1f m - PESO: %.2f PBT\n", feixo, fvelo, fcomp, fpeso, veiculos[i].eixos, veiculos[i].velocidade, veiculos[i].comprimento, veiculos[i].peso);  
        fprintf(erros, "LINHA: %d - %s\n\n", linha, linhaanterior);
        set = 0;
        counterror++;
        fvelo = ' ';
        fcomp = ' ';
        fpeso = ' ';
        feixo = ' ';
    } else {
        printf("Erro: arquivo não está aberto.\n");
    }
}

void processa_linha_arquivo(FILE *arquivo, FILE *erros, const char *delimitador) {
    char linha[102400]; // Buffer para armazenar a linha lida
    char linhaanterior[102400]; // Buffer para armazenar a linha anterior
    int set = 0; // Variável para verificar se houve erro

    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0; // Remove a nova linha
        strcpy(linhaanterior, linha); // Armazena a linha anterior

        char *campo = strtok(linha, delimitador); // Divide a linha em campos
        int coluna = 0;

        while (campo != NULL) {
            if (coluna == 3) {
                veiculos[i].velocidade = strtof(campo, NULL);
            } else if (coluna == 4) {
                veiculos[i].comprimento = strtof(campo, NULL);
            } else if (coluna == 6) {
                veiculos[i].eixos = atoi(campo);
            } else if (coluna == 10) {
                veiculos[i].peso = strtof(campo, NULL);
            }
            campo = strtok(NULL, delimitador); // Passa para o próximo campo
            coluna++;
        }

        velo(); // Chamada para a função de validação de velocidade
        compri(); // Chamada para a função de validação de comprimento
        peso(); // Chamada para a função de validação de peso

        if (set == 1) { // Verifica se houve erro
            registrarErro(erros, linha, linhaanterior, feixo, fvelo, fcomp, fpeso, veiculos, i);
        }
        i++; // Incrementa o índice do veículo

    }
}