#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include "../include/biuaidinaive.hpp"
#include "../include/quad_tree.hpp" 
// Função para parsing dos argumentos
void parse_arguments(int argc, char *argv[], std::string &nome_arquivo_base, std::string &nome_arquivo_eventos);

// Função para ler o arquivo e inicializar o objeto Naive
Naive* inicializar_naive(const std::string &nome_arquivo_base);
Quad_tree* inicializar_quad_tree(const std::string &nome_arquivo_base);
void processar_arquivo( std::string& nome_arquivo_base, Quad_tree &quad_tree);
#endif