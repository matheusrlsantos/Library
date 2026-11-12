#include <stdio.h>
#include <stdlib.h>

#include "Tree_binary.h"

// Inicializa a arvore binaria.
book* criar_arvore() {
    return NULL;
}

// Reserva um espaco para o livro.
book* criar_no_livro(int id_livro, char* titulo, int qtd_total) {
    book* novo = (book*)malloc(sizeof(book));
    if (novo == NULL) {
        return NULL;
    }

    novo->id_livro = id_livro;
    novo->qtd_total = qtd_total;
    novo->qtd_empre = 0; // Inicia sem nenhum emprestimo ativo

    // Copia o titulo caractere a caractere, sem passar de 49 (deixa 1 para o '\0')
    int i = 0;
    if (titulo != NULL) {
        while (titulo[i] != '\0' && i < 49) {
            novo->titulo[i] = titulo[i];
            i++;
        }
    }
    novo->titulo[i] = '\0';

    novo->left = NULL;
    novo->right = NULL;

    return novo;
}

// Insere os dados do livro.
book* inserir_livro(book* root, int id_livro, char* titulo, int qtd_total) {
    if (root == NULL) {
        return criar_no_livro(id_livro, titulo, qtd_total);
    }

    if (id_livro < root->id_livro) {
        root->left = inserir_livro(root->left, id_livro, titulo, qtd_total);
    } else if (id_livro > root->id_livro) {
        root->right = inserir_livro(root->right, id_livro, titulo, qtd_total);
    } else {
        // Se o ID ja existe, apenas incrementa a quantidade total cadastrada
        root->qtd_total += qtd_total;
    }

    return root;
}

// Procura por um livro cadastrado.
book* buscar_livro(book* root, int id_livro) {
    if (root == NULL || root->id_livro == id_livro) {
        return root;
    }

    if (id_livro < root->id_livro) {
        return buscar_livro(root->left, id_livro);
    }

    return buscar_livro(root->right, id_livro);
}

// Verifica se ha livro disponivel para posse.
int consultar_disponivel(book* no) {
    if (no == NULL) return 0;
    return (no->qtd_total - no->qtd_empre);
}

// Mostra todo o acervo cadastrado da biblioteca (percurso em ordem).
void listar_acervo_em_ordem(book* root) {
    if (root != NULL) {
        listar_acervo_em_ordem(root->left);

        int disponivel = consultar_disponivel(root);
        printf("ID: %d | Titulo: %-25s | Total: %d | Emprestados: %d | Disponiveis: %d\n",
               root->id_livro, root->titulo, root->qtd_total, root->qtd_empre, disponivel);

        listar_acervo_em_ordem(root->right);
    }
}

// Funcao auxiliar que nao deve ser usada fora deste arquivo.
static book* encontrar_minimo(book* root) {
    book* atual = root;
    while (atual && atual->left != NULL) {
        atual = atual->left;
    }
    return atual;
}

// Exclui um livro em especifico.
book* excluir_livro(book* root, int id_livro) {
    if (root == NULL) {
        return NULL;
    }

    if (id_livro < root->id_livro) {
        root->left = excluir_livro(root->left, id_livro);
    } else if (id_livro > root->id_livro) {
        root->right = excluir_livro(root->right, id_livro);
    } else {
        // Caso 1 e 2: No com apenas um filho ou nenhum
        if (root->left == NULL) {
            book* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            book* temp = root->left;
            free(root);
            return temp;
        }

        // Caso 3: No com dois filhos -> copia o sucessor (menor da subarvore direita)
        book* temp = encontrar_minimo(root->right);
        root->id_livro = temp->id_livro;
        root->qtd_total = temp->qtd_total;
        root->qtd_empre = temp->qtd_empre;
        for (int i = 0; i < 50; i++) {
            root->titulo[i] = temp->titulo[i];
        }

        root->right = excluir_livro(root->right, temp->id_livro);
    }
    return root;
}

// Apaga toda a arvore binaria (percurso em pos-ordem).
void liberar_arvore(book* root) {
    if (root != NULL) {
        liberar_arvore(root->left);
        liberar_arvore(root->right);
        free(root);
    }
}





