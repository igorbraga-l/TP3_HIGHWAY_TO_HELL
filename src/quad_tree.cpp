#include "../include/quad_tree.hpp"
#include <stdexcept>
#include "../include/estacao.hpp"
#include "../include/max_heap.hpp"
#include <iomanip>
#include <iostream>

Quad_tree::Quad_tree(int num_estacoes) {
    this->num_estacoes = num_estacoes;
    this->nos = new No[num_estacoes];
    for (int i = 0; i < num_estacoes; i++) {
        this->nos[i] = No();
    }
    this->num_nos = 0;
    this->raiz = -1;
    this->mapa_chave_indice_estacoes = new Mapa(num_estacoes);
    
}

Quad_tree::~Quad_tree() {
    delete[] nos;
    delete mapa_chave_indice_estacoes;
}

/**
 * Insere uma estação de recarga no Quad_tree.
 * @param estacao A estação de recarga a ser inserida.
 * @param indice_no O índice do nó onde se procura o pai para inserir.
 */
void Quad_tree::inserir_estacao(Estacao_de_recarga estacao, int indice_no) {
    No& no_atual = nos[indice_no];

    mapa_chave_indice_estacoes->Inserir(estacao.get_id_endereco(), num_nos);

    if(num_nos > num_estacoes) {
        throw std::runtime_error("Número de nós excedido");
    }
    // Se o quad-tree ainda está vazio, inicialize o nó raiz
    if (this->num_nos == 0) {
        this->nos[0] = No(estacao, -1, -1, -1, -1);
        this->raiz = 0;
        this->num_nos++;
        return;
    }

    // Caso o nó não esteja ocupado, insira a estação
    if (!no_atual.esta_ocupado()) {
        no_atual.set_estacao(estacao);
    } else {
        Ponto ponto_estacao = estacao.get_ponto();
        Ponto ponto_no_atual = no_atual.get_ponto();
        inserir_em_quadrante(estacao, indice_no, ponto_estacao, ponto_no_atual);
    }
}

/**
 * Insere uma estação de recarga em um quadrante específico.
 * @param estacao A estação de recarga a ser inserida.
 * @param indice_no O índice do nó onde a estação será inserida.
 * @param ponto_estacao O ponto da estação de recarga.
 * @param ponto_no_atual O ponto do nó atual.
 */
void Quad_tree::inserir_em_quadrante(Estacao_de_recarga estacao, int indice_no, Ponto ponto_estacao, Ponto ponto_no_atual) {
    No& no_atual = nos[indice_no];
   
    // Quadrante Noroeste
    if (ponto_estacao.x < ponto_no_atual.x && ponto_estacao.y > ponto_no_atual.y) {
        if (no_atual.get_filho_noroeste() == -1) {
            no_atual.set_filho_noroeste(num_nos);
            nos[num_nos] = No();
            num_nos++;
        }
        inserir_estacao(estacao, no_atual.get_filho_noroeste());
    }
    // Quadrante Nordeste
    else if (ponto_estacao.x > ponto_no_atual.x && ponto_estacao.y > ponto_no_atual.y) {
        if (no_atual.get_filho_nordeste() == -1) {
            no_atual.set_filho_nordeste(num_nos);
            nos[num_nos] = No();
            num_nos++;
        }
        inserir_estacao(estacao, no_atual.get_filho_nordeste());
    }
    // Quadrante Sudoeste
    else if (ponto_estacao.x < ponto_no_atual.x && ponto_estacao.y < ponto_no_atual.y) {
        if (no_atual.get_filho_sudoeste() == -1) {
            no_atual.set_filho_sudoeste(num_nos);
            nos[num_nos] = No();
            num_nos++;
        }
        inserir_estacao(estacao, no_atual.get_filho_sudoeste());
    }
    // Quadrante Sudeste
    else if (ponto_estacao.x > ponto_no_atual.x && ponto_estacao.y < ponto_no_atual.y) {
        if (no_atual.get_filho_sudeste() == -1) {
            no_atual.set_filho_sudeste(num_nos);
            nos[num_nos] = No();
            num_nos++;
        }
        inserir_estacao(estacao, no_atual.get_filho_sudeste());
    } else {
        throw std::runtime_error("Erro ao inserir estação");
    }
}

/**
 * Busca os K vizinhos mais próximos (KNN) de um ponto específico.
 * @param p O ponto de referência.
 * @param indice_no O índice do nó atual.
 * @param K O número de vizinhos mais próximos a serem encontrados.
 * @param knn A estrutura Max_Heap para armazenar os vizinhos mais próximos.
 */
void Quad_tree::buscaKNN(Ponto p, long indice_no, int K, Max_Heap& knn) {
    No& no_atual = nos[indice_no];
    if (!no_atual.esta_ocupado()) return;

    double dist = distancia(no_atual.get_ponto().x, no_atual.get_ponto().y, p.x, p.y);
    Estacao_distancia est_dist{no_atual.get_estacao(), dist};

    if (no_atual.esta_ocupado() && no_atual.get_estacao().is_ativa()) {
        if (knn.getTamanho() < K) {
            knn.inserir(est_dist);
        } else if (dist < knn.getMax().distancia) {
            knn.extrairMax();
            knn.inserir(est_dist);
        }
    }
    if (no_atual.get_filho_noroeste() != -1) buscaKNN(p, no_atual.get_filho_noroeste(), K, knn);
    if (no_atual.get_filho_nordeste() != -1) buscaKNN(p, no_atual.get_filho_nordeste(), K, knn);
    if (no_atual.get_filho_sudoeste() != -1) buscaKNN(p, no_atual.get_filho_sudoeste(), K, knn);
    if (no_atual.get_filho_sudeste() != -1) buscaKNN(p, no_atual.get_filho_sudeste(), K, knn);
}

/**
 * Obtém os K vizinhos mais próximos (KNN) de um ponto específico.
 * @param k O número de vizinhos mais próximos a serem encontrados.
 * @param ponto O ponto de referência.
 * @return Um array de knn_t contendo os K vizinhos mais próximos.
 */
knn_t * Quad_tree::get_knn(int k, Ponto ponto) {
    Max_Heap knn(k);
    buscaKNN(ponto, raiz, k, knn);
    knn_t * knn_array = new knn_t[k];
    for (int i = 0; i < k; i++) {
        Estacao_distancia est_dist = knn.getMax();
        knn.extrairMax();
        knn_array[i].id = est_dist.estacao.get_id_endereco();
        knn_array[i].distancia = est_dist.distancia;
    }
    return knn_array;
}

/**
 * Imprime os K vizinhos mais próximos (KNN) de um ponto específico.
 * @param k O número de vizinhos mais próximos a serem encontrados.
 * @param ponto O ponto de referência.
 */
void Quad_tree::print_knn(int k, Ponto ponto) {
    Max_Heap knn(k);
    buscaKNN(ponto, raiz, k, knn);
    
    if (knn.getTamanho() == 0) return;
    
    Estacao_distancia Estacao_distancia_knn[k];
    for (int i = 0; i < k; i++) {
        Estacao_distancia est_dist = knn.getMax();
        Estacao_distancia_knn[k-i-1] = est_dist;
        knn.extrairMax();
    }

    for (int i = 0; i < k; i++) {
        Estacao_distancia est_dist = Estacao_distancia_knn[i];
        std::cout << std::fixed << std::setprecision(3) << est_dist.estacao.get_sigla_tipo() << " " << est_dist.estacao.get_nome_logradouro() << ", " << est_dist.estacao.get_numero_imovel()
                  << ", " << est_dist.estacao.get_nome_bairro() << ", " << est_dist.estacao.get_nome_regiao() << ", " << est_dist.estacao.get_cep() 
                  << " (" << est_dist.distancia << ")" << std::endl;
    }
}

/**
 * Obtém o número de nós no Quad_tree.
 * @return O número de nós.
 */
int Quad_tree::get_num_nos() {
    return num_nos;
}

/**
 * Obtém o array de nós no Quad_tree.
 * @return Um ponteiro para o array de nós.
 */
No * Quad_tree::get_nos() {
    return nos;
}

/**
 * Ativa uma estação de recarga com base no ID do endereço.
 * @param id_endereco O ID do endereço da estação de recarga a ser ativada.
 */
void Quad_tree::ativar_estacao(std::string id_endereco) {
    long indice_no = mapa_chave_indice_estacoes->get_item(id_endereco);
    if (indice_no == -1) throw std::runtime_error("Estação não encontrada");
    Estacao_de_recarga &estacao = nos[indice_no].get_estacao();
    if(estacao.is_ativa()) {
        std::cout << "Ponto de recarga " << id_endereco << " já estava ativo." << std::endl;
        return; 
    }
    estacao.set_ativa(true);
    std::cout << "Ponto de recarga " << id_endereco << " ativado." << std::endl;
}

/**
 * Desativa uma estação de recarga com base no ID do endereço.
 * @param id_endereco O ID do endereço da estação de recarga a ser desativada.
 */
void Quad_tree::desativar_estacao(std::string id_endereco) {
    long indice_no = mapa_chave_indice_estacoes->get_item(id_endereco);
    if (indice_no == -1) throw std::runtime_error("Estação não encontrada");
    Estacao_de_recarga &estacao = nos[indice_no].get_estacao();
    if(!estacao.is_ativa()) {
        std::cout << "Ponto de recarga " << id_endereco << " já estava desativado." << std::endl;
        return; 
    }
    estacao.set_ativa(false);
    std::cout << "Ponto de recarga " << id_endereco << " desativado." << std::endl;
}

/**
 * Obtém o mapa de chave para índice de estações.
 * @return O mapa de chave para índice de estações.
 */
Mapa Quad_tree::get_mapa_chave_indice_estacoes() const {
    return *mapa_chave_indice_estacoes;
}
