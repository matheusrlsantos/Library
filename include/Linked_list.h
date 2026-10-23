#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Structure to represent a node in a linked list, cotaining a pointer to the next node and a string data field. 
typedef struct lista_de_emprestimo_ativo{
    int qtd_possuida; 
    int id_livro; 
    int id_aluno; 
    struct lista_de_emprestimo_ativo *next;    
}empre; 

// Creates a new node with the given data and returns a pointer to it. 
empre* criar_no_posse(int id_aluno, int id_livro, int qtd); 

empre* buscar_posse(empre* lista, int id_aluno, int id_livro); 

// Adds a new node using the function creat_node and returns the head of the list. 
empre* registrar_posse(empre* lista, int id_aluno, int id_livro, int qtd); 

// Deletes the node with the specified data from the linked list and returns the head of the list. 
empre* remover_posse(empre *lista, int id_aluno, int id_livro, int qtd_devolvida); 

empre* listar_posses(empre* lista); 

// Destroys all nodes in the linked list and frees the associated memory. Returns NULL. 
empre* liberar_lista(empre *head); 

#endif 