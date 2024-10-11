#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct veiculo{
    float velocidade;
    float comprimento;
    int eixos;
};


int main() {
    // Abre o arquivo em modo de leitura
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    FILE *resultado = fopen("resultado.txt", "w");
    if (resultado == NULL) {
        printf("Erro ao abrir o arquivo de resultado.\n");
        fclose(arquivo);
        return 1;
    }

    // Define um buffer para armazenar cada linha
    char linha[1024];
    const char delimitador[] = ";";
    struct veiculo veiculos[500];
    int i = 0;
    //char spac = ' ';
    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;

        char *campo = strtok(linha, delimitador);
        int coluna = 0;

        printf("\n");
        fprintf(resultado, "\n");
        while (campo != NULL){

            if(coluna == 3){
                float val = strtof(campo, NULL);
                veiculos[i].velocidade = val;
                printf("Velocidade = %.1f\n", veiculos[i].velocidade);
            }
            else if (coluna == 4){
                float val = strtof(campo, NULL);
                veiculos[i].comprimento = val;
                printf("Comprimento = %.1f\n", veiculos[i].comprimento);
            }
            else if (coluna == 6){
                int val1 = atoi(campo);
                veiculos[i].eixos = val1;
                printf("Eixos = %d\n", veiculos[i].eixos);
            }
            
            campo = strtok(NULL, delimitador);
            coluna++;    
             
        }
        fprintf(resultado, "Velocidade: %.1f\nComprimento: %.1f\nEixos: %d\n", veiculos[i].velocidade, veiculos[i].comprimento, veiculos[i].eixos);
        
        i++;  

    }

    // Fecha o arquivo
    fclose(arquivo);
    fclose(resultado);

    system("PAUSE");
    return 0;
}

