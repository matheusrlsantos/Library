#include <stdio.h>
#include <stdlib.h>

#include "fila.h"

// Incializa a fila.
fila* criar_fila() {
    fila* f = (fila*) malloc(sizeof(fila));
    if (f == NULL) return NULL;

    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

// Verifica se a fila está vazia.
int fila_vazia(fila *f) {
    if (f == NULL) return 1;
    return f->inicio == NULL;
}

// Coordena a ordem da fila: insere no FIM.
void enfileirar_desejo(fila* f, int id_aluno, int id_livro, int qtd) {
    if (f == NULL) return;

    nofi *novo = (nofi*) malloc(sizeof(nofi));
    if (novo == NULL) {
        printf("Erro: sem memoria disponivel para reserva.\n");
        return;
    }

    novo->id_aluno = id_aluno;
    novo->id_livro = id_livro;
    novo->qtd_dese = qtd;
    novo->next = NULL;

    // Se a fila estiver vazia, novo nó é início e fim
    if (f->fim == NULL) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->next = novo;
        f->fim = novo;
    }
}

// Remove a reserva do INICIO da fila.
void desenfileirar_desejo(fila* f) {
    if (f == NULL || fila_vazia(f)) {
        return;
    }

    nofi* removido = f->inicio;
    f->inicio = f->inicio->next;

    if (f->inicio == NULL) {
        f->fim = NULL; // Se esvaziou a fila, o fim também vira NULL
    }

    free(removido);
}

// Encontra o próximo da fila de reserva por um livro.
nofi* buscar_proximo_por_livro(fila* f, int id_livro) {
    if (f == NULL || fila_vazia(f)) return NULL;

    nofi *aux = f->inicio;

    while (aux != NULL) {
        if (aux->id_livro == id_livro) {
            return aux; // Primeiro da fila aguardando esse livro
        }
        aux = aux->next;
    }

    return NULL; // Ninguém esperando por este livro
}

// Mostra uma lista da fila de reserva.
void listar_fila(fila* f) {
    printf("\n== FILA DE ESPERA / RESERVAS (INICIO -> FIM) ==\n");

    if (f == NULL || fila_vazia(f)) {
        printf("Fila de espera vazia.\n");
        return;
    }

    nofi *current = f->inicio;
    int count = 1;

    while (current != NULL) {
        printf("%d. Aluno ID: %d | Livro ID: %d | Qtd Desejada: %d\n",
               count, current->id_aluno, current->id_livro, current->qtd_dese);
        current = current->next;
        count++;
    }
}

// Cancela a reserva de um aluno por um livro (pode estar em qualquer posição).
int cancelar_reserva(fila *f, int id_aluno, int id_livro) {
    if (f == NULL || fila_vazia(f)) {
        return 0;
    }

    nofi *atual = f->inicio;
    nofi *anterior = NULL;

    // Procura o nó guardando sempre o anterior (igual à remoção da lista encadeada)
    while (atual != NULL && !(atual->id_aluno == id_aluno && atual->id_livro == id_livro)) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        return 0; // Reserva não encontrada
    }

    if (anterior == NULL) {
        f->inicio = atual->next; // Removendo o primeiro da fila
    } else {
        anterior->next = atual->next; // "Pula" o nó removido
    }

    // Se removemos o último, o fim precisa ser atualizado
    if (atual == f->fim) {
        f->fim = anterior; // Se anterior for NULL, a fila ficou vazia
    }

    free(atual);
    return 1;
}

// Apaga toda a fila de reserva.
void liberar_fila(fila *f) {
    if (f == NULL) return;

    nofi *current = f->inicio;
    nofi *temp;

    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }

    free(f); // Libera a struct de controle da fila
}
