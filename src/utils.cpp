#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <cstdlib> 
#include <cstring> 
#include "../include/biuaidinaive.hpp"
#include "../include/quad_tree.hpp"

#define BUFFER_SIZE 1024  // Tamanho do buffer para leitura das linhas

// Função para parsing dos argumentos
void parse_arguments(int argc, char *argv[], std::string &nome_arquivo_base, std::string &nome_arquivo_eventos) {
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "-b" && i + 1 < argc) {
            nome_arquivo_base = argv[i + 1];
            ++i;
        } else if (std::string(argv[i]) == "-e" && i + 1 < argc) {
            nome_arquivo_eventos = argv[i + 1];
            ++i;
        }
    }
    if (nome_arquivo_base.empty() || nome_arquivo_eventos.empty()) {
        throw std::invalid_argument("Argumentos inválidos");
    }
}

// Função para ler o arquivo e inicializar o objeto Naive
Naive* inicializar_naive(const std::string &nome_arquivo_base) {
    FILE* arquivo_base = fopen(nome_arquivo_base.c_str(), "r");
    if (!arquivo_base) {
        std::cerr << "Erro ao abrir o arquivo: " << nome_arquivo_base << std::endl;
        throw std::runtime_error("Falha ao abrir arquivo base.");
    }

    char linha[BUFFER_SIZE];
    fgets(linha, sizeof(linha), arquivo_base);
    int num_estacoes = std::stoi(linha);

    Naive* naive = new Naive(num_estacoes);

    while (fgets(linha, sizeof(linha), arquivo_base)) {
        Estacao_de_recarga estacao;
        char* token;

        // Tokenize each field, using ';' as the delimiter
        token = strtok(linha, ";");
        std::string id_endereco(token);

        token = strtok(nullptr, ";");
        long id_logradouro = std::strtol(token, nullptr, 10);

        token = strtok(nullptr, ";");
        std::string sigla_tipo(token);

        token = strtok(nullptr, ";");
        std::string nome_logradouro(token);

        token = strtok(nullptr, ";");
        int numero_imovel = std::stoi(token);

        token = strtok(nullptr, ";");
        std::string nome_bairro(token);

        token = strtok(nullptr, ";");
        std::string nome_regiao(token);

        token = strtok(nullptr, ";");
        int cep = std::stoi(token);

        token = strtok(nullptr, ";");
        double x = std::strtod(token, nullptr);

        token = strtok(nullptr, ";");
        double y = std::strtod(token, nullptr);

        Ponto ponto(x, y);

        // Configurando os valores na estação
        estacao.set_id_endereco(id_endereco);
        estacao.set_id_logradouro(id_logradouro);
        estacao.set_sigla_tipo(sigla_tipo);
        estacao.set_nome_logradouro(nome_logradouro);
        estacao.set_numero_imovel(numero_imovel);
        estacao.set_nome_bairro(nome_bairro);
        estacao.set_nome_regiao(nome_regiao);
        estacao.set_cep(cep);
        estacao.set_ponto(ponto);
        estacao.set_ativa(true);  // Valor padrão para 'ativa'
        estacao.set_valida(true);  // Valor padrão para 'valida'
        
        naive->inserir_estacao(estacao);
    }

    fclose(arquivo_base);
    return naive;
}

Quad_tree* inicializar_quad_tree(const std::string &nome_arquivo_base) {
    FILE* arquivo_base = fopen(nome_arquivo_base.c_str(), "r");
    if (!arquivo_base) {
        std::cerr << "Erro ao abrir o arquivo: " << nome_arquivo_base << std::endl;
        throw std::runtime_error("Falha ao abrir arquivo base.");
    }

    char linha[BUFFER_SIZE];
    fgets(linha, sizeof(linha), arquivo_base);
    int num_estacoes = std::stoi(linha);

    Quad_tree* quad_tree = new Quad_tree(num_estacoes);

    for (int i = 0; i < num_estacoes; i++) {
        fgets(linha, sizeof(linha), arquivo_base);
        Estacao_de_recarga estacao= Estacao_de_recarga();
        char* token;

        // Tokenize each field, using ';' as the delimiter
        token = strtok(linha, ";");
        std::string id_endereco(token);

        token = strtok(nullptr, ";");
        long id_logradouro = std::strtol(token, nullptr, 10);

        token = strtok(nullptr, ";");
        std::string sigla_tipo(token);

        token = strtok(nullptr, ";");
        std::string nome_logradouro(token);

        token = strtok(nullptr, ";");
        int numero_imovel = std::stoi(token);

        token = strtok(nullptr, ";");
        std::string nome_bairro(token);

        token = strtok(nullptr, ";");
        std::string nome_regiao(token);

        token = strtok(nullptr, ";");
        int cep = std::stoi(token);

        token = strtok(nullptr, ";");
        double x = std::strtod(token, nullptr);

        token = strtok(nullptr, ";");
        double y = std::strtod(token, nullptr);

        Ponto ponto(x, y);

        // Configurando os valores na estação
        estacao.set_id_endereco(id_endereco);
        estacao.set_id_logradouro(id_logradouro);
        estacao.set_sigla_tipo(sigla_tipo);
        estacao.set_nome_logradouro(nome_logradouro);
        estacao.set_numero_imovel(numero_imovel);
        estacao.set_nome_bairro(nome_bairro);
        estacao.set_nome_regiao(nome_regiao);
        estacao.set_cep(cep);
        estacao.set_ponto(ponto);
        estacao.set_ativa(true);  // Valor padrão para 'ativa'
        estacao.set_valida(true);  // Valor padrão para 'valida'

        quad_tree->inserir_estacao(estacao, 0);
    }

    fclose(arquivo_base);
    return quad_tree;
}



void processar_arquivo( std::string& nome_arquivo_base, Quad_tree &quad_tree ) {
    FILE* arquivo_base = fopen(nome_arquivo_base.c_str(), "r");
    if (!arquivo_base) {
        std::cerr << "Erro ao abrir o arquivo: " << nome_arquivo_base << std::endl;
        throw std::runtime_error("Falha ao abrir arquivo base.");
    }

    char linha[BUFFER_SIZE];
    fgets(linha, sizeof(linha), arquivo_base);
    


    while (fgets(linha, sizeof(linha), arquivo_base)) {
        std::string operacao;
        double x = 0.0, y = 0.0;
        int k;
        std::string id_endereco;
        char comando;
        char temp_id_endereco[100]; // Buffer temporário para leitura de strings
 

        sscanf(linha, "%c", &comando);
        if (comando == 'C') {
            sscanf(linha, "%c %lf %lf %d", &comando, &x, &y, &k);
            std::cout <<linha ;
            quad_tree.print_knn(k, Ponto(x, y));
        } 

        else if (comando == 'A') {
            sscanf(linha, "%c %s", &comando, temp_id_endereco);
            id_endereco = temp_id_endereco; // Atribui o valor lido à std::string
            std::cout <<linha ;
            quad_tree.ativar_estacao(id_endereco);
        } 

        else if (comando == 'D') {
            sscanf(linha, "%c %s", &comando, temp_id_endereco);
            id_endereco = temp_id_endereco; // Atribui o valor lido à std::string
            std::cout <<linha ;
            quad_tree.desativar_estacao(id_endereco);
        } 

        else {
            std::cerr << "Erro ao processar a linha: " << linha << std::endl;
        }


    }



    fclose(arquivo_base);
}

