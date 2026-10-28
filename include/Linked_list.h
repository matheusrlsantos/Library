#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Esta estrutura trabalha com os dados dos empréstimos dos livros. 
typedef struct lista_de_emprestimo_ativo{
    int qtd_possuida; 
    int id_livro; 
    int id_aluno; 
    struct lista_de_emprestimo_ativo *next;    
}empre; 

// Cria um novo nó para mais uma posse de livro. 
empre* criar_no_posse(int id_aluno, int id_livro, int qtd); 

//Procura quem está em posse do livro. 
empre* buscar_posse(empre* lista, int id_aluno, int id_livro); 

// Registra quem está em posse de um livro, e sua quantidade. 
empre* registrar_posse(empre* lista, int id_aluno, int id_livro, int qtd); 

// Apaga a posse escolhida. 
empre* remover_posse(empre *lista, int id_aluno, int id_livro, int qtd_devolvida); 

// Mostra uma lista com todas as posses ativas. 
void listar_posses(empre* lista); 

// Apaga a lista das posses. 
empre* liberar_lista(empre *head); 

#endif 