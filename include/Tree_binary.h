#ifndef TREE_H
#define TREE_H

typedef struct dados_dos_livros{
    int id_livro; 
    int qtd_empre; 
    int qtd_total; 
    char* titulo;
    struct dados_dos_livros* right; 
    struct dados_dos_livros* left; 

}book; 

book* criar_arvore(); 

book* criar_no_livro(int id_livro, char* titulo, int qtd_total); 

book* inserir_livro(book* root, int id_livro, char* titulo, int qtd_total); 

book* buscar_livro(book* root, int id_livro); 

int consultar_disponivel(book* no); 

void listar_acervo_em_ordem(book* root); 

void liberar_arvore(book* root); 

book* excluir_livro(book* root, int id_livro); 




#endif 