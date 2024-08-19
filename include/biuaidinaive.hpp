#ifndef NAIVE_HPP
#define NAIVE_HPP

#include <stdlib.h>
#include <math.h>
#include <string>
#include "estacao.hpp"


class Naive{
private:
    Estacao_de_recarga * estacoes;
    int num_estacoes;
    int quantidades_estacoes_inseridas;
    int quantidade_estacoes_ativas;
        
public:

    Naive(int num_estacoess);
    ~Naive();
    void inserir_estacao(Estacao_de_recarga estacao);
    void ativar_estacao(std::string id);
    void desativar_estacao(std::string id);
    void print_knn(int k, Ponto ponto);
    void print_estacao(knn knn); 
    void printmap();
    knn_t * get_knn(int k, Ponto ponto);;
    Estacao_de_recarga * get_estacao(std::string id);
    };
#endif
