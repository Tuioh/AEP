#include <stdio.h>
#include <string.h>
#include <locale.h>
int decisoes() {
    setlocale(LC_ALL, "Portuguese");
    int es;
    printf("----------------COMO PODEMOS AJUDAR?----------------");
    printf("\n1 - Adicionar usuários");
    printf("\n2 - Alterar usuários");
    printf("\n3 - Excluir usuários");
    printf("\n4 - Exibir lista de usuários");
    printf("\n-----------------------------------------------------");
    printf("\nDigite sua escolha: ");
    scanf("%d", &es);
    return es;
}
int main() {
    setlocale(LC_ALL, "Portuguese");
    char usuarios[70][100];
    char senha[10][100];
    char busca[70];
    char temp;
    char linha[100];
    char senhaa[10];
    char usuarioss[70];
    int c, i, u, escolha, usu, tam, s;
    escolha = decisoes();
    while (escolha != 1 && escolha != 2 && escolha != 3 && escolha != 4) {
        printf("\nA opção esta incorreta");
        escolha = decisoes();
    }
    switch (escolha) {
        case 1:
            printf("\nQuantos usuários deseja adicionar: ");
            scanf("%d", &usu);
            getchar(); 
            for (c = 0; c < usu; c++) {
                printf("\nDigite um nome de usuário: ");
                fgets(usuarios[c], sizeof(usuarios[c]), stdin);
                usuarios[c][strcspn(usuarios[c], "\n")] = '\0';
                printf("Digite uma senha: ");
                fgets(senha[c], sizeof(senha[c]), stdin);
                senha[c][strcspn(senha[c], "\n")] = '\0';
                tam = strlen(senha[c]);
                for (i = 0; i < tam / 2; i++) {
                    temp = senha[c][i];
                    senha[c][i] = senha[c][tam - i - 1];
                    senha[c][tam - i - 1] = temp;
                }
                for (i = 0; i < strlen(senha[c]); i++) {
                    senha[c][i] = senha[c][i] + 10;
                }
                FILE *arquivo = fopen("banco.txt", "a");
                if (arquivo == NULL) {
                    printf("\nErro ao abrir o arquivo!");
                    return 1;
                }
                fprintf(arquivo, "%s,%s\n", usuarios[c], senha[c]);
                fclose(arquivo);
            }
            break;
        case 2:
            printf("\nDigite o nome do usuário que deseja alterar: ");
    getchar(); 
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';
    FILE *arquivo = fopen("banco.txt", "r+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *usuario2 = strtok(linha, ",");
        char *senha2 = strtok(NULL, "\n");
        if (usuario2 && senha2) {
            usuario2[strcspn(usuario2, "\n")] = '\0';
            senha2[strcspn(senha2, "\n")] = '\0'; 
            if (strcmp(busca, usuario2) == 0) {
                printf("\nUsuário encontrado: %s\n", usuario2);
                encontrado = 1;
                printf("\nDigite a sua senha: ");
                fgets(senhaa, sizeof(senhaa), stdin);
                senhaa[strcspn(senhaa, "\n")] = '\0';
                tam = strlen(senhaa);
                for (i = 0; i < tam / 2; i++) {
                    temp = senhaa[i];
                    senhaa[i] = senhaa[tam - i - 1];
                    senhaa[tam - i - 1] = temp;
                }
                for (i = 0; i < tam; i++) {
                    senhaa[i] = senhaa[i] + 10;
                }
                if (strcmp(senhaa, senha2) == 0) {
                    printf("\nAcesso liberado!\n");
                    printf("Digite o novo nome de usuário: ");
                    getchar();
                    fgets(usuarioss, sizeof(usuarioss), stdin);
                    usuarioss[strcspn(usuarioss, "\n")] = '\0';
                    FILE *arquivotemp = fopen("bancotemp.txt", "w");
                    if (arquivotemp == NULL) {
                        printf("Erro ao criar arquivo temporário\n");
                        fclose(arquivo);
                        return 1;
                    }
                    rewind(arquivo);
                    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                        char *usuario2 = strtok(linha, ",");
                        char *senha2 = strtok(NULL, "\n");
                        if (strcmp(busca, usuario2) == 0) {
                            fprintf(arquivotemp, "%s,%s\n", usuarioss, senha2);
                        } else {
                            fprintf(arquivotemp, "%s,%s\n", usuario2, senha2);
                        }
                    }
                    fclose(arquivo);
                    fclose(arquivotemp);
                    remove("banco.txt");
                    rename("bancotemp.txt", "banco.txt");
                    printf("\nUsuário alterado com sucesso!");
                } else {
                    printf("\nSenha esta errada");
                }
                break;
            }
        }
    }
    if (!encontrado) {
        printf("Usuário não encontrado");
    }
    fclose(arquivo);
    break;
        case 3:
            printf("\nDigite o nome do usuário que deseja excluir: ");
            getchar();
            fgets(busca, sizeof(busca), stdin);
            busca[strcspn(busca, "\n")] = '\0';
            FILE *arquivo2 = fopen("banco.txt", "r");
            if (arquivo2 == NULL) {
                printf("Erro ao abrir o arquivo");
                return 1;
            }
            int ex = 0;
            while (fgets(linha, sizeof(linha), arquivo2) != NULL) {
                char *usuario2 = strtok(linha, ",");
                char *senha2 = strtok(NULL, "\n");
                if (usuario2 && senha2) {
                    usuario2[strcspn(usuario2, "\n")] = '\0';
                    senha2[strcspn(senha2, "\n")] = '\0';
                    if (strcmp(busca, usuario2) == 0) {
                        printf("\nDigite a senha do usuário %s para confirmar a exclusão: ", usuario2);
                        fgets(senhaa, sizeof(senhaa), stdin);
                        senhaa[strcspn(senhaa, "\n")] = '\0'; 
                        tam = strlen(senhaa);
                        for (i = 0; i < tam / 2; i++) {
                            temp = senhaa[i];
                            senhaa[i] = senhaa[tam - i - 1];
                            senhaa[tam - i - 1] = temp;
                        }
                        for (i = 0; i < tam; i++) {
                            senhaa[i] = senhaa[i] + 10;
                        }
                        if (strcmp(senhaa, senha2) == 0) {
                            printf("\nAcesso liberado! O usuário será excluído");
                            FILE *arquivo3 = fopen("banco2.txt", "w");
                            if (arquivo3 == NULL) {
                                printf("Erro ao criar o arquivo temporário");
                                fclose(arquivo2);
                                return 1;
                            }
                            rewind(arquivo2);
                            while (fgets(linha, sizeof(linha), arquivo2) != NULL) {
                                char *usuario2 = strtok(linha, ",");
                                char *senha2 = strtok(NULL, "\n");
                                if (strcmp(busca, usuario2) != 0) {
                                    fprintf(arquivo3, "%s,%s\n", usuario2, senha2);
                                }
                            }
                            fclose(arquivo2);
                            fclose(arquivo3);
                            remove("banco.txt");
                            rename("banco2.txt", "banco.txt");
                            printf("\nUsuário excluído", busca);
                            ex = 1;
                        } else {
                            printf("\nSenha errada");
                        }
                    }
                }
            }
            if (!ex) {
                printf("Usuário não encontrado ou erro na senha\n");
            }
            fclose(arquivo2);
            break;
        case 4:
            printf("\nExibindo lista de usuários:\n");
            FILE *arquivo4 = fopen("banco.txt", "r");
            if (arquivo4 == NULL) {
                printf("Erro ao abrir o arquivo");
                return 1;
            }
            while (fgets(linha, sizeof(linha), arquivo4) != NULL) {
                int i = 0;
                while (linha[i] != ',' && linha[i] != '\0') {
                    printf("%c", linha[i]);
                    i++;
                }
                printf("\n");
            }
            fclose(arquivo4);
            break;
    }
    return 0;
}
