#ifndef MAX_HEAP_HPP
#define MAX_HEAP_HPP
#include "estacao.hpp"
struct Estacao_distancia {
    Estacao_de_recarga estacao;
    double distancia;
};

class Max_Heap {
private:
    Estacao_distancia* heap;
    int capacidade;
    int tamanho;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Max_Heap(int capacidade);
    ~Max_Heap();

    void inserir( Estacao_distancia& novoElemento);
    Estacao_distancia getMax() const;
    int getTamanho() const;
    void extrairMax();
    bool estaVazio() const;
    void print();
};


#endif