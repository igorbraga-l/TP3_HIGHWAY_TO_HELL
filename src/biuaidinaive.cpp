#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/biuaidinaive.hpp"
#include "../include/estacao.hpp"
#include <iomanip> 

Naive::Naive(int num_estacoes){
    this->num_estacoes = num_estacoes;
    this->estacoes = new Estacao_de_recarga[num_estacoes];
    this->quantidades_estacoes_inseridas = 0;
    this->quantidade_estacoes_ativas = 0;
}

Naive::~Naive(){
    delete[] estacoes;
}

void Naive::inserir_estacao(Estacao_de_recarga estacao){
    if(quantidades_estacoes_inseridas < num_estacoes){
        estacoes[quantidades_estacoes_inseridas] = estacao;
        quantidades_estacoes_inseridas++;
        quantidade_estacoes_ativas++;
    }
    else{
        std::cout << "Numero maximo de estacoes atingido" << std::endl;
    }
}

void Naive::ativar_estacao(std::string id){
    for(int i = 0; i < num_estacoes; i++){
        if(estacoes[i].get_id_endereco() == id) {
            if(!estacoes[i].is_ativa()){
                estacoes[i].set_ativa(true);
                quantidade_estacoes_ativas++;
                std::cout << "Ponto de recarga " << estacoes[i].get_id_endereco() << " ativado." << std::endl;
            } else {
                std::cout << "Ponto de recarga " << estacoes[i].get_id_endereco() << " já estava ativo." << std::endl;
            }
            return;
        }
    }
    std::cout << "Estação com ID " << id << " não encontrada." << std::endl;
}

void Naive::desativar_estacao(std::string id){
    for(int i = 0; i < num_estacoes; i++){
        if(estacoes[i].get_id_endereco() == id) {
            if(estacoes[i].is_ativa()){
                estacoes[i].set_ativa(false);
                quantidade_estacoes_ativas--;
                std::cout << "Ponto de recarga " << estacoes[i].get_id_endereco() << " desativado." << std::endl;
            } else {
                std::cout << "Ponto de recarga " << estacoes[i].get_id_endereco() << " já estava desativado." << std::endl;
            }
            return;
        }
    }
    std::cout << "Estação com ID " << id << " não encontrada." << std::endl;
}


knn_t * Naive::get_knn(int k, Ponto ponto) {
    // Distances
    knn_t * knn_todos_K = new knn_t[quantidade_estacoes_ativas];
    knn_t * knn = new knn_t[k];
    int j = 0;
    
    // Calculo das distancias
    for (int i = 0; i < quantidade_estacoes_ativas; i++) {
        if (!estacoes[i].is_ativa()) continue;

        knn_todos_K[j].distancia = distancia(ponto.x, ponto.y, estacoes[i].get_ponto().x, estacoes[i].get_ponto().y);
        knn_todos_K[j].id = estacoes[i].get_id_endereco();
        j++;
    }

    // ordena distancias
    for (int i = 0; i < j - 1; i++) {
        for (int m = i + 1; m < j; m++) {
            if (knn_todos_K[i].distancia > knn_todos_K[m].distancia) {
                knn_t aux = knn_todos_K[i];
                knn_todos_K[i] = knn_todos_K[m];
                knn_todos_K[m] = aux;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        knn[i] = knn_todos_K[i];
    }

    delete[] knn_todos_K;  
    return knn;
}

void Naive::print_knn(int k, Ponto ponto) {
    knn_t* knn = get_knn(k, ponto);
    Estacao_de_recarga estacao_k;
    for (int i = 0; i < k; i++) {
        estacao_k = *get_estacao(knn[i].id);
        if (estacao_k.is_ativa()) {
            print_estacao(knn[i]);
        }
    }
    delete[] knn; // Move this line outside the for loop
}

void Naive::print_estacao(knn knn) {
    std::string id = knn.id;
    double distancia = knn.distancia;
    for (int i = 0; i < num_estacoes; i++) {
        if (estacoes[i].get_id_endereco() == id) {
            std::cout << std::fixed << std::setprecision(3) 
             << estacoes[i].get_sigla_tipo() << " " << estacoes[i].get_nome_logradouro() << ", " << estacoes[i].get_numero_imovel()
                      << ", " << estacoes[i].get_nome_bairro() << ", " << estacoes[i].get_nome_regiao() << ", " << estacoes[i].get_cep() 
                      << " (" << distancia << ")" <<std::endl;
            return;
        }
    }
    std::cout << "Estação com ID " << id << " não encontrada." << std::endl;
}

void Naive::printmap() {
    FILE* gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set size ratio -1\n");
    fprintf(gp, "plot '-' with points pointtype 7 pointsize 1.5 title 'Estacoes de recarga'\n");
    for (int i = 0; i < num_estacoes; i++) {
        fprintf(gp, "%f %f\n", estacoes[i].get_ponto().x, estacoes[i].get_ponto().y);
    }
    fprintf(gp, "e\n");
    fflush(gp);
    pclose(gp);
}

Estacao_de_recarga* Naive::get_estacao(std::string id) {
    for (int i = 0; i < num_estacoes; i++) {
        if (estacoes[i].get_id_endereco() == id) {
            return &estacoes[i];
        }
    }
    return nullptr;
}
