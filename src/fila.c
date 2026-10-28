
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "fila.h"


// Incializa a fila. 
fila* criar_fila() {
    fila* f = (fila*) malloc(sizeof(fila));
    if (f == NULL) return NULL;
    
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

int fila_vazia(fila *f) {
    if (f == NULL) return 1;
    return f->inicio == NULL;
}

// Insere um documento no FIM da fila

// Coordena a ordem da fila. 
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
// Remove o documento do INICIO da fila e copia o nome para docRemovido

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
NoFila* buscar_proximo_por_livro(Fila* f, int id_livro) {
    if (f == NULL || fila_vazia(f)) return NULL;

    nofi *aux = f->inicio;

    while (aux != NULL) {
        if (aux->id_livro == id_livro) {
            return aux; // Encontrou o próximo da fila aguardando esse livro!
        }
        aux = aux->next;
    }

    return NULL; // Ninguém esperando por este livro
}
// Mostra uma lista da fila de reserva. 
void listar_fila(Fila* f) {
    printf("\n== FILA DE ESPERA / RESERVAS (INÍCIO -> FIM) ==\n");

    if (f == NULL || fila_vazia(f)) {
        printf("Fila de espera vazia.\n"); 
        return; 
    } 

    NoFila *current = f->inicio; 
    int count = 1; 

    while (current != NULL) {
        printf("%d. Aluno ID: %d | Livro ID: %d | Qtd Desejada: %d\n", 
               count, current->id_aluno, current->id_livro, current->qtd_dese); 
        current = current->next; 
        count++;  
    }
}
// Cancela uma reserva. 
NoFila cancelar_reserva(Fila *f) {
    NoFila copia_cancelada;
    // Inicializa com valores zerados para o caso de falha ou fila vazia
    copia_cancelada.id_aluno = 0;
    copia_cancelada.id_livro = 0;
    copia_cancelada.qtd_dese = 0;
    copia_cancelada.next = NULL;

    if (f == NULL || fila_vazia(f)) {
        printf("Aviso: Fila vazia ou inexistente. Nenhum cancelamento feito.\n");
        return copia_cancelada;
    }

    // Guarda o nó que será removido do início
    NoFila *temp = f->inicio;

    // Copia os dados antes de desalocar a memória
    copia_cancelada.id_aluno = temp->id_aluno;
    copia_cancelada.id_livro = temp->id_livro;
    copia_cancelada.qtd_dese = temp->qtd_dese;

    // Avanca o ponteiro do inicio para o proximo nó
    f->inicio = f->inicio->next;

    // Se o inicio virou NULL, a fila esvaziou por completo
    if (f->inicio == NULL) {
        f->fim = NULL;
    }

    // Libera a memória do nó que foi cancelado
    free(temp);

    return copia_cancelada;
}

// Apaga toda a fila de reserva. 
void liberar_fila(Fila *f) {
    if (f == NULL) return;

    NoFila *current = f->inicio;
    NoFila *temp;

    while (current != NULL) {
        temp = current->next;
        free(current);
        current = temp;
    }

    free(f); // Libera o ponteiro da estrutura de controle da Fila
}