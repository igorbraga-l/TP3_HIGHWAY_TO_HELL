#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include "estacao.hpp"
#include "no.hpp"
#include "mapa.hpp"
#include "max_heap.hpp"
class Quad_tree {

    private:
        No * nos;
        int num_estacoes;
        int num_nos;
        int raiz;
        Mapa * mapa_chave_indice_estacoes;
    public:
        Quad_tree(int num_estacoes);
        ~Quad_tree();
        void inserir_estacao(Estacao_de_recarga estacao, int id_no);
        void inserir_em_quadrante(Estacao_de_recarga estacao, int indice_no, Ponto ponto_estacao, Ponto ponto_no_atual);
        
        void buscaKNN(Ponto p, long indice_no, int K,Max_Heap& knn);
        knn_t * get_knn(int k, Ponto ponto);
        void print_knn(int k, Ponto ponto);
        int get_num_nos();
        No * get_nos();
        void ativar_estacao(std::string id_endereco);
        void desativar_estacao(std::string id_endereco);
        Mapa get_mapa_chave_indice_estacoes() const;

};

#endif   