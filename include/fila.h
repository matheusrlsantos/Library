#ifndef FILA_H
#define FILA_H

typedef struct fila_de_reserva{
    int id_aluno; 
    int id_livro; 
    int qtd_dese; 
    struct fila_de_reserva* next; 
}nofi; 


typedef struct {
    nofi* inicio;
    nofi* fim;
}fila;

fila* criar_fila();

void enfileirar_desejo(fila* f, int id_aluno, int id_livro, int qtd); 

void* desenfileirar_desejo(fila* f); 

nofi* buscar_proximo_por_livro(fila* f, int id_livro); 

void listar_fila(fila* f); 

nofi* cancelar_reserva(fila *f); 





#endif 