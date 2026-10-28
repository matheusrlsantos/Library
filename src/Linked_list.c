#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
#include "Linked_list.h"



// Cria um novo nó para mais uma posse de livro. 
empre* criar_no_posse(int id_aluno, int id_livro, int qtd){
   
    empre* novo = (empre*)malloc(sizeof(empre)); 

    if (novo == NULL) {
        return NULL; // Falha na alocação de memória
    }

    novo->id_aluno = id_aluno;
    novo->id_livro = id_livro;
    novo->qtd_possuida = qtd;
    novo->next = NULL; 
    
    return novo; 
}

//Procura quem está em posse do livro. 
empre* buscar_posse(empre* lista, int id_aluno, int id_livro){
    empre* current = lista;

    while (current != NULL) {
        if (current->id_aluno == id_aluno && current->id_livro == id_livro) {
            return current; // Registro encontrado
        }
        current = current->next;
    }

    return NULL; // Não encontrado
} 

// Registra quem está em posse de um livro, e sua quantidade. 
empre* registrar_posse(empre* lista, int id_aluno, int id_livro, int qtd) { 
    // Check 1: Se o aluno já tem o registro desse livro, apenas incrementa a quantidade
    empre* existente = buscar_posse(lista, id_aluno, id_livro);
    if (existente != NULL) {
        existente->qtd_possuida += qtd;
        return lista;
    }

    // Check 2: Se não existe, cria um nó novo
    empre* novo = criar_no_posse(id_aluno, id_livro, qtd);
    if (novo == NULL) return lista;

    // Se a lista estiver vazia, o novo nó torna-se a cabeça da lista
    if (lista == NULL) {
        return novo; 
    }

    // Senão, insere no final da lista
    empre* current = lista; 
    while (current->next != NULL) {
        current = current->next; 
    }
    current->next = novo; 

    return lista; 
}

// Apaga a posse escolhida. 
empre* remover_posse(empre *lista, int id_aluno, int id_livro, int qtd_devolvida) {
    if (lista == NULL) {
        return NULL; 
    }

    empre* registro = buscar_posse(lista, id_aluno, id_livro);
    if (registro == NULL) {
        return lista; // O aluno nem tinha esse registro
    }

    // Caso 1: Devolução parcial (ainda sobra saldo com o aluno)
    if (registro->qtd_possuida > qtd_devolvida) {
        registro->qtd_possuida -= qtd_devolvida;
        return lista;
    }

    // Caso 2: Devolução total (precisa remover o nó da lista)
    
    // Se o nó a ser removido é a cabeça (head) da lista
    if (lista->id_aluno == id_aluno && lista->id_livro == id_livro) {
        empre* temp = lista; 
        lista = lista->next; 
        free(temp); 
        return lista; 
    }

    // Se o nó está no meio ou no fim da lista
    empre* prev = lista;
    empre* current = lista->next; 
    
    while (current != NULL) {
        if (current->id_aluno == id_aluno && current->id_livro == id_livro) { 
            prev->next = current->next; 
            free(current);
            break; 
        }
        prev = current; 
        current = current->next;
    }

    return lista; 
}

// Mostra uma lista com todas as posses ativas. 
void listar_posses(empre* head){

    if(head == NULL){ // Verifica se a cabeça não está vazia. 
        return; 
    }

    empre* current = head; 

    while(current != NULL){
        printf("O aluno com o id: %d, está em posse do livro: %d \n"); 
        current = (*current).proximo; 
    }

}




// Apaga a lista das posses. 
   empre* liberar_lista(empre *head) {
    empre* current = head; 
    empre* temp; 

    while (current != NULL) {
        temp = current->next; 
        free(current); // Removeu a chamada a free(current->data) já que não temos mais strings dinâmicas
        current = temp; 
    }
    return NULL;
}