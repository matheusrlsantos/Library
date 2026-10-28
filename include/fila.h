#ifndef FILA_H
#define FILA_H


// Nesta estrutura, é trabalhado os dados da fila de reserva. 
typedef struct fila_de_reserva{
    int id_aluno; 
    int id_livro; 
    int qtd_dese; 
    struct fila_de_reserva* next; 
}nofi; 

// Preparação para manipulação da fila(FIFO). 
typedef struct {
    nofi* inicio;
    nofi* fim;
}fila;


// Incializa a fila. 
fila* criar_fila();

// Coordena a ordem da fila. 
void enfileirar_desejo(fila* f, int id_aluno, int id_livro, int qtd); 

// Remove da fila a reserva. 
void* desenfileirar_desejo(fila* f); 

// Encontra o próximo da fila de reserva por um livro. 
nofi* buscar_proximo_por_livro(fila* f, int id_livro); 

// Mostra uma lista da fila de reserva. 
void listar_fila(fila* f); 

// Cancela uma reserva. 
nofi* cancelar_reserva(fila *f); 


// Apaga toda a fila de reserva. 
void liberar_fila(fila *f); 



#endif 