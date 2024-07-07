#include <stdio.h>
#include <stdlib.h>

struct Candidatos{
int ID;
char nome[20];
int idade;
char linguagem[15];
char vaga[20];
};




void Create(const char *bdCandidato, struct Candidatos Candidato){

FILE *bd = fopen(bdCandidato, "a");
if(bd == NULL){
    printf("Arquivo inexistente \n");
}
fwrite(&Candidato, sizeof(struct Candidatos), 1,bd);
fclose(bd);
}

void Read(const char *bdCandidato){
struct Candidatos Candidato;

FILE *bd = fopen(bdCandidato, "rb");
if(bd == NULL){
    printf("Erro \n");
    return;
}

while(fread(&Candidato, sizeof(struct Candidatos), 1, bd)){
printf("ID: %d \n", Candidato.ID);
printf("Nome: %s \n", Candidato.nome);
printf("Idade: %d \n", Candidato.idade);
printf("Linguagem: %s \n", Candidato.linguagem);
printf("Vaga: %s \n", Candidato.vaga);

}
fclose(bd);
}
void Update(const char *bdCandidato, int IDBusca){

    FILE *bd = fopen(bdCandidato, "r+b");
    if(bd == NULL){
    printf("Não encontrado");
    }


    struct Candidatos candidatoAtual;
    int encontrado = 0;
    long posicao;

    while(fread(&candidatoAtual,sizeof(struct Candidatos), 1, bd)){
        if(candidatoAtual.ID == IDBusca){
            encontrado = 1;
            posicao = ftell(bd) - sizeof(struct Candidatos);
            fseek(bd,posicao, SEEK_SET);

            printf("Digite o novo nome: ");
            scanf("%s", candidatoAtual.nome);
            printf("Digite a nova idade: ");
            scanf("%d",&candidatoAtual.idade);
            printf("Digite a nova linguagem: ");
            scanf("%s", candidatoAtual.linguagem);
            printf("Digite a nova vaga: ");
            scanf("%s", candidatoAtual.vaga);

            fwrite(&candidatoAtual, sizeof(struct Candidatos), 1, bd);
            break;
        }
        }
        if(!encontrado){
        printf("ID não encontrado \n");
        }
        fclose(bd);
}

    void deleteCandidato(const char *bdCandidato, const char *tempBdCandidato){

        FILE *bd = fopen(bdCandidato, "rb");
        if(bd == NULL){
            printf("Nao encontrado");
            return;
        }
        FILE *bdTemp = fopen(tempBdCandidato, "wb");
        if(bdTemp == NULL){
            printf("Nao encontrado");
            fclose(bd);
            return;
        }

        struct Candidatos Candidato;
        int deletado;

        printf("Digite o ID a ser deletado: ");
        scanf("%d", &deletado);

        while(fread(&Candidato, sizeof(struct Candidatos), 1, bd)){
            if(Candidato.ID != deletado){
                fwrite(&Candidato, sizeof(struct Candidatos), 1, bdTemp);
        }
        }
         fclose(bd);
        fclose(bdTemp);

        if(remove(bdCandidato)!= 0){
        printf("Erro ao remover \n");
        return;
        }
        if(rename(tempBdCandidato, bdCandidato)!= 0){
        printf("Erro ao renomear \n");
        return;
        }
        printf("Removido com sucesso!\n");


        }



int main(){

int op, IDBusca;

const char *bdCandidato = "BdCandidato.bin";
const char *tempBdCandidato = "tempBdCandidato.bin";

struct Candidatos Candidato;

do{
printf("[1] - Create \n");
printf("[2] - Read \n");
printf("[3] - Update\n");
printf("[4] - Delete\n");
printf("[5] - Sair\n");
scanf("%d", &op);


switch(op){
    case 1:
        printf("Digite o ID da pessoa: ");
        scanf("%d",&Candidato.ID);
        printf("Digite o nome da pessoa: ");
        scanf("%s", Candidato.nome);
        printf("Digite a idade: ");
        scanf("%d", &Candidato.idade);
        printf("Digite a linguagem: ");
        scanf("%s", Candidato.linguagem);
        printf("Digite a vaga: ");
        scanf("%s", Candidato.vaga);

    Create(bdCandidato, Candidato);
    break;

    case 2:

        Read(bdCandidato);
        break;

    case 3:

        printf("Digite o Id a ser alterado: ");
        scanf("%d", &IDBusca);
        Update(bdCandidato, IDBusca);
        break;

    case 4:

        deleteCandidato(bdCandidato, tempBdCandidato);
        Read(bdCandidato);
        break;

        }
        }
        while(op!=5);
        return 0;

}
