#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct veiculo{
    float velocidade;
    float comprimento;
    int eixos;
};

// Define um buffer para armazenar cada linha
char linha[1024];
const char delimitador[] = ";";
struct veiculo veiculos[500];
int i = 0;

float eixo2vmax = 0,
      eixo2vmin = 200.0,
      eixo3vmax = 0,
      eixo3vmin = 200.0,
      eixo5vmax = 0,
      eixo5vmin = 200.0,
      eixo7vmax = 0,
      eixo7vmin = 200.0,
      eixo9vmax = 0,
      eixo9vmin = 200.0,
      eixo2cmax = 0,
      eixo2cmin = 200.0,
      eixo3cmax = 0,
      eixo3cmin = 200.0,
      eixo5cmax = 0,
      eixo5cmin = 200.0,
      eixo7cmax = 0,
      eixo7cmin = 200.0,
      eixo9cmax = 0,
      eixo9cmin = 200.0;

void velo(void); 
void compri(void);

int main() {
    // Abre o arquivo em modo de leitura
    FILE *arquivo = fopen("dados.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    else{
        printf("\nArquivo dados.txt aberto com sucesso!!\n");
    }

    FILE *resultado = fopen("resultado.txt", "w");
    if (resultado == NULL) {
        printf("Erro ao abrir o arquivo de resultado.\n");
        fclose(arquivo);
        return 1;
    }
    else{
        printf("Arquivo resultado.txt aberto com sucesso!!\n");
    }

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = 0;

        char *campo = strtok(linha, delimitador);
        int coluna = 0;

        printf("\n");
        //fprintf(resultado, "\n");
        while (campo != NULL){

            if(coluna == 3){
                float val = strtof(campo, NULL);
                veiculos[i].velocidade = val;
                printf("Velocidade = %.1f\n", veiculos[i].velocidade);
            }
            else if (coluna == 4){
                float val1 = strtof(campo, NULL);
                veiculos[i].comprimento = val1;
                printf("Comprimento = %.1f\n", veiculos[i].comprimento);
            }
            else if (coluna == 6){
                int val2 = atoi(campo);
                veiculos[i].eixos = val2;
                printf("Eixos = %d\n", veiculos[i].eixos);
            }
            
            velo();
            compri();
            campo = strtok(NULL, delimitador);
            coluna++;    
             
        }
        //fprintf(resultado, "Velocidade: %.1f\nComprimento: %.1f\nEixos: %d\n", veiculos[i].velocidade, veiculos[i].comprimento, veiculos[i].eixos);
        
        i++;  

    }
    fprintf(resultado, "2 EIXOS, VELOCIDADE MAX: %.1f,  VELOCIDADE MIN: %.1f\n", eixo2vmax, eixo2vmin);
    fprintf(resultado, "2 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", eixo2cmax, eixo2cmin);
    fprintf(resultado, "\n3 EIXOS, VELOCIDADE MAX: %.1f,  VELOCIDADE MIN: %.1f\n", eixo3vmax, eixo3vmin);
    fprintf(resultado, "3 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", eixo3cmax, eixo3cmin);
    fprintf(resultado, "\n5 EIXOS, VELOCIDADE MAX: %.1f,  VELOCIDADE MIN: %.1f\n", eixo5vmax, eixo5vmin);
    fprintf(resultado, "5 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", eixo5cmax, eixo5cmin);
    fprintf(resultado, "\n7 EIXOS, VELOCIDADE MAX: %.1f,  VELOCIDADE MIN: %.1f\n", eixo7vmax, eixo7vmin);
    fprintf(resultado, "7 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", eixo7cmax, eixo7cmin);
    fprintf(resultado, "\n9 EIXOS, VELOCIDADE MAX: %.1f,  VELOCIDADE MIN: %.1f\n", eixo9vmax, eixo9vmin);
    fprintf(resultado, "9 EIXOS, COMPRIMENTO MAX: %.1f, COMPRIMENTO MIN: %.1f\n", eixo9cmax, eixo9cmin);


    fclose(arquivo);
    fclose(resultado);

    return 0;
}

void velo(void){
    if(veiculos[i].eixos == 2){
        if(veiculos[i].velocidade >= eixo2vmax){
            eixo2vmax = veiculos[i].velocidade;
            if(eixo2vmin == 200.0){
                eixo2vmin = veiculos[i].velocidade;
            }
        }
        else{            
            if(veiculos[i].velocidade <= eixo2vmin){
                eixo2vmin = veiculos[i].velocidade;
            }
        }
    }
    else if(veiculos[i].eixos == 3){
        if(veiculos[i].velocidade >= eixo3vmax){
            eixo3vmax = veiculos[i].velocidade;
            if(eixo3vmin == 200.0){
                eixo3vmin = veiculos[i].velocidade;
            }
        }
        else{            
            if(veiculos[i].velocidade <= eixo3vmin){
                eixo3vmin = veiculos[i].velocidade;
            }
        }
    }
    else if(veiculos[i].eixos == 5){
        if(veiculos[i].velocidade >= eixo5vmax){
            eixo5vmax = veiculos[i].velocidade;
            if(eixo5vmin == 200.0){
                eixo5vmin = veiculos[i].velocidade;
            }
        }
        else{            
            if(veiculos[i].velocidade <= eixo5vmin){
                eixo5vmin = veiculos[i].velocidade;
            }
        }
    }
    else if(veiculos[i].eixos == 7){
        if(veiculos[i].velocidade >= eixo7vmax){
            eixo7vmax = veiculos[i].velocidade;
            if(eixo7vmin == 200.0){
                eixo7vmin = veiculos[i].velocidade;
            }
        }
        else{            
            if(veiculos[i].velocidade <= eixo7vmin){
                eixo7vmin = veiculos[i].velocidade;
            }
        }
    }
    else if(veiculos[i].eixos == 9){
        if(veiculos[i].velocidade >= eixo9vmax){
            eixo9vmax = veiculos[i].velocidade;
            if(eixo9vmin == 200.0){
                eixo9vmin = veiculos[i].velocidade;
            }
        }
        else{            
            if(veiculos[i].velocidade <= eixo9vmin){
                eixo9vmin = veiculos[i].velocidade;
            }
        }
    }
}

void compri(void){
    if(veiculos[i].eixos == 2){
        if(veiculos[i].comprimento >= eixo2cmax){
            eixo2cmax = veiculos[i].comprimento;
            if(eixo2cmin == 200.0){
                eixo2cmin = veiculos[i].comprimento;
            }
        }
        else{            
            if(veiculos[i].comprimento <= eixo2cmin){
                eixo2cmin = veiculos[i].comprimento;
            }
        }
    }
    else if(veiculos[i].eixos == 3){
        if(veiculos[i].comprimento >= eixo3cmax){
            eixo3cmax = veiculos[i].comprimento;
            if(eixo3cmin == 200.0){
                eixo3cmin = veiculos[i].comprimento;
            }
        }
        else{            
            if(veiculos[i].comprimento <= eixo3cmin){
                eixo3cmin = veiculos[i].comprimento;
            }
        }
    }
    else if(veiculos[i].eixos == 5){
        if(veiculos[i].comprimento >= eixo5cmax){
            eixo5cmax = veiculos[i].comprimento;
            if(eixo5cmin == 200.0){
                eixo5cmin = veiculos[i].comprimento;
            }
        }
        else{            
            if(veiculos[i].comprimento <= eixo5cmin){
                eixo5cmin = veiculos[i].comprimento;
            }
        }
    }
    else if(veiculos[i].eixos == 7){
        if(veiculos[i].comprimento >= eixo7cmax){
            eixo7cmax = veiculos[i].comprimento;
            if(eixo7cmin == 200.0){
                eixo7cmin = veiculos[i].comprimento;
            }
        }
        else{            
            if(veiculos[i].comprimento <= eixo7cmin){
                eixo7cmin = veiculos[i].comprimento;
            }
        }
    }
    else if(veiculos[i].eixos == 9){
        if(veiculos[i].comprimento >= eixo9cmax){
            eixo9cmax = veiculos[i].comprimento;
            if(eixo9cmin == 200.0){
                eixo9cmin = veiculos[i].comprimento;
            }
        }
        else{            
            if(veiculos[i].comprimento <= eixo9cmin){
                eixo9cmin = veiculos[i].comprimento;
            }
        }
    }  
}