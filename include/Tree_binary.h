#ifndef TREE_H
#define TREE_H

// Nessa estrutura, é trabalhado os dados dos livros. 
typedef struct dados_dos_livros{
    int id_livro; 
    int qtd_empre; 
    int qtd_total; 
    char* titulo;
    struct dados_dos_livros* right; 
    struct dados_dos_livros* left; 

}book; 

//Incializa a arvore binária. 
book* criar_arvore(); 

// Reserva um espaço para o livro. 
book* criar_no_livro(int id_livro, char* titulo, int qtd_total); 

// Isere os dados do livro.  
book* inserir_livro(book* root, int id_livro, char* titulo, int qtd_total); 

// Procura por um livro cadastrado. 
book* buscar_livro(book* root, int id_livro); 

// Verifica se há livro disponível para posse. 
int consultar_disponivel(book* no); 

// Mostra todo o acervo cadastrado da biblioteca. 
void listar_acervo_em_ordem(book* root); 

// Apaga toda a arvore binária. 
void liberar_arvore(book* root); 

// Exclui um livro em específico.
book* excluir_livro(book* root, int id_livro); 




#endif 