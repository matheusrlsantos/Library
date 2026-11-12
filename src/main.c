/*
 * TRABALHO FINAL - ESTRUTURA DE DADOS - 2026/2
 *
 * Integrantes (nome completo e RA):
 *   - NOME COMPLETO 1 - RA: 000000
 *   - CARLOS EDUARDO MAXIMO SANDRIM - RA: 202616400004
 *
 * Tema: Sistema de Biblioteca
 *   ABB (acervo de livros por codigo), lista encadeada (emprestimos ativos)
 *   e fila (reservas).
 */

#include <stdio.h>
#include <stdlib.h>
#include "Tree_binary.h"
#include "Linked_list.h"
#include "fila.h"

/* Procura o emprestimo ativo de um livro pelo codigo (sem precisar do leitor). */
static empre* buscarEmprestimoPorLivro(empre *lista, int id_livro) {
    empre *atual = lista;
    while (atual != NULL) {
        if (atual->id_livro == id_livro) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

/* Carga de dados de exemplo: 10 livros, 3 emprestimos e 3 reservas. */
static book* carregarDadosExemplo(book *acervo, empre **posses, fila *reservas) {
    acervo = inserir_livro(acervo, 105, "Dom_Casmurro", 1);
    acervo = inserir_livro(acervo, 102, "O_Cortico", 1);
    acervo = inserir_livro(acervo, 108, "Capitaes_da_Areia", 1);
    acervo = inserir_livro(acervo, 101, "Memorias_Postumas", 1);
    acervo = inserir_livro(acervo, 103, "Vidas_Secas", 1);
    acervo = inserir_livro(acervo, 107, "Grande_Sertao", 1);
    acervo = inserir_livro(acervo, 110, "O_Alienista", 1);
    acervo = inserir_livro(acervo, 104, "Iracema", 1);
    acervo = inserir_livro(acervo, 106, "O_Guarani", 1);
    acervo = inserir_livro(acervo, 109, "Senhora", 1);

    /* Emprestimos ativos: o livro fica indisponivel (qtd_empre = 1) */
    buscar_livro(acervo, 102)->qtd_empre = 1;
    *posses = registrar_posse(*posses, 1, 102, 1);
    buscar_livro(acervo, 105)->qtd_empre = 1;
    *posses = registrar_posse(*posses, 2, 105, 1);
    buscar_livro(acervo, 107)->qtd_empre = 1;
    *posses = registrar_posse(*posses, 3, 107, 1);

    /* Reservas na fila (todos os livros reservados estao emprestados) */
    enfileirar_desejo(reservas, 4, 102, 1);
    enfileirar_desejo(reservas, 5, 102, 1);
    enfileirar_desejo(reservas, 6, 105, 1);

    return acervo;
}

int main() {
    book *acervo = criar_arvore();   /* ABB de livros */
    empre *posses = NULL;            /* lista de emprestimos ativos */
    fila *reservas = criar_fila();   /* fila unica de reservas */

    if (reservas == NULL) {
        printf("Erro: sem memoria disponivel.\n");
        return 1;
    }

    acervo = carregarDadosExemplo(acervo, &posses, reservas);
    printf("Dados de exemplo carregados (10 livros, 3 emprestimos, 3 reservas).\n");

    int menuPrincipal, sub;
    int codigo, leitor;
    char titulo[50];
    char resposta;
    book *livro;
    empre *emp;

    do {
        printf("\n===== BIBLIOTECA - MENU PRINCIPAL =====\n");
        printf("1 - Acervo (ABB)\n");
        printf("2 - Emprestimos (lista encadeada)\n");
        printf("3 - Reservas (fila)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &menuPrincipal);

        switch (menuPrincipal) {

        /* ---------------- ACERVO (ABB) ---------------- */
        case 1:
            do {
                printf("\n--- ACERVO ---\n");
                printf("1 - Cadastrar livro\n");
                printf("2 - Buscar livro\n");
                printf("3 - Remover livro\n");
                printf("4 - Listar acervo em ordem\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &sub);

                switch (sub) {
                case 1:
                    printf("Codigo do livro: ");
                    scanf("%d", &codigo);
                    if (buscar_livro(acervo, codigo) != NULL) {
                        printf("Erro: ja existe um livro com o codigo %d.\n", codigo);
                    } else {
                        printf("Titulo (uma palavra, use _ no lugar de espacos): ");
                        scanf("%s", titulo);
                        acervo = inserir_livro(acervo, codigo, titulo, 1);
                        printf("Livro cadastrado (disponivel).\n");
                    }
                    break;

                case 2:
                    printf("Codigo do livro: ");
                    scanf("%d", &codigo);
                    livro = buscar_livro(acervo, codigo);
                    if (livro == NULL) {
                        printf("Livro nao encontrado.\n");
                    } else {
                        printf("Codigo: %d | Titulo: %s | Disponivel: %d\n",
                               livro->id_livro, livro->titulo,
                               consultar_disponivel(livro));
                    }
                    break;

                case 3:
                    printf("Codigo do livro: ");
                    scanf("%d", &codigo);
                    if (buscar_livro(acervo, codigo) == NULL) {
                        printf("Livro nao encontrado.\n");
                    } else {
                        acervo = excluir_livro(acervo, codigo);
                        printf("Livro removido do acervo (o historico de emprestimos e mantido).\n");
                    }
                    break;

                case 4:
                    if (acervo == NULL) {
                        printf("Acervo vazio.\n");
                    } else {
                        listar_acervo_em_ordem(acervo);
                    }
                    break;

                case 0:
                    break;

                default:
                    printf("Opcao invalida.\n");
                }
            } while (sub != 0);
            break;

        /* ---------------- EMPRESTIMOS (LISTA) ---------------- */
        case 2:
            do {
                printf("\n--- EMPRESTIMOS ---\n");
                printf("1 - Emprestar livro\n");
                printf("2 - Devolver livro\n");
                printf("3 - Buscar emprestimo por codigo do livro\n");
                printf("4 - Listar emprestimos ativos\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &sub);

                switch (sub) {
                case 1:
                    printf("Codigo do livro: ");
                    scanf("%d", &codigo);
                    livro = buscar_livro(acervo, codigo);
                    if (livro == NULL) {
                        printf("Livro nao encontrado no acervo.\n");
                        break;
                    }
                    printf("ID do leitor: ");
                    scanf("%d", &leitor);

                    if (consultar_disponivel(livro) >= 1) {
                        livro->qtd_empre++;                       /* disponivel = 0 */
                        posses = registrar_posse(posses, leitor, codigo, 1);
                        printf("Emprestimo realizado.\n");
                    } else {
                        printf("Livro indisponivel. Deseja entrar na fila de reservas? (s/n): ");
                        scanf(" %c", &resposta);
                        if (resposta == 's' || resposta == 'S') {
                            enfileirar_desejo(reservas, leitor, codigo, 1);
                            printf("Leitor %d entrou na fila de reservas.\n", leitor);
                        }
                    }
                    break;

                case 2:
                    printf("Codigo do livro: ");
                    scanf("%d", &codigo);
                    emp = buscarEmprestimoPorLivro(posses, codigo);
                    if (emp == NULL) {
                        printf("Nao ha emprestimo ativo para esse livro.\n");
                    } else {
                        leitor = emp->id_aluno;
                        posses = remover_posse(posses, leitor, codigo, 1);
                        livro = buscar_livro(acervo, codigo);
                        if (livro != NULL) {
                            livro->qtd_empre--;                   /* disponivel = 1 */
                            printf("Devolucao registrada. Livro disponivel novamente.\n");
                        } else {
                            printf("Devolucao registrada (o livro ja nao esta no acervo).\n");
                        }
                    }
                    break;

                case 3:
                    printf("Codigo do livro: ");
                    scanf("%d", &codigo);
                    emp = buscarEmprestimoPorLivro(posses, codigo);
                    if (emp == NULL) {
                        printf("Nao ha emprestimo ativo para esse livro.\n");
                    } else {
                        printf("Livro %d esta emprestado ao leitor %d.\n",
                               emp->id_livro, emp->id_aluno);
                    }
                    break;

                case 4:
                    listar_posses(posses);
                    break;

                case 0:
                    break;

                default:
                    printf("Opcao invalida.\n");
                }
            } while (sub != 0);
            break;

        /* ---------------- RESERVAS (FILA) ---------------- */
        case 3:
            do {
                printf("\n--- RESERVAS ---\n");
                printf("1 - Atender proxima reserva\n");
                printf("2 - Consultar frente da fila\n");
                printf("3 - Listar fila de reservas\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &sub);

                switch (sub) {
                case 1:
                    if (fila_vazia(reservas)) {
                        printf("Fila de reservas vazia.\n");
                    } else {
                        /* copia os dados ANTES de desenfileirar (o no sera liberado) */
                        leitor = reservas->inicio->id_aluno;
                        codigo = reservas->inicio->id_livro;
                        desenfileirar_desejo(reservas);

                        livro = buscar_livro(acervo, codigo);
                        if (livro == NULL) {
                            printf("Reserva removida da fila, mas o livro %d nao existe mais no acervo.\n", codigo);
                        } else if (consultar_disponivel(livro) >= 1) {
                            livro->qtd_empre++;
                            posses = registrar_posse(posses, leitor, codigo, 1);
                            printf("Reserva atendida: livro %d emprestado ao leitor %d.\n", codigo, leitor);
                        } else {
                            printf("Livro %d ainda esta indisponivel. Reserva do leitor %d removida da fila.\n",
                                   codigo, leitor);
                        }
                    }
                    break;

                case 2:
                    if (fila_vazia(reservas)) {
                        printf("Fila de reservas vazia.\n");
                    } else {
                        printf("Frente da fila: leitor %d aguardando o livro %d.\n",
                               reservas->inicio->id_aluno, reservas->inicio->id_livro);
                    }
                    break;

                case 3:
                    listar_fila(reservas);
                    break;

                case 0:
                    break;

                default:
                    printf("Opcao invalida.\n");
                }
            } while (sub != 0);
            break;

        case 0:
            printf("Encerrando...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while (menuPrincipal != 0);

    /* Libera toda a memoria alocada com malloc */
    liberar_arvore(acervo);
    posses = liberar_lista(posses);
    liberar_fila(reservas);

    return 0;
}
