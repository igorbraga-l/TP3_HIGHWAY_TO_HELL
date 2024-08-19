
#include <string>
#include "../include/utils.hpp"
#include "../include/quad_tree.hpp"
#include "../include/mapa.hpp"
#include <iostream>


int main(int argc, char *argv[]) {
    std::string nome_arquivo_base;
    std::string nome_arquivo_eventos;

    parse_arguments(argc, argv, nome_arquivo_base, nome_arquivo_eventos);
  
    Quad_tree* quad_tree = inicializar_quad_tree(nome_arquivo_base);
    // Mapa mapa = quad_tree->get_mapa_chave_indice_estacoes();
    // No * nos = quad_tree->get_nos();
    // std::cout << nos[2].get_filho_noroeste() << std::endl;
    // std::string id_endereco = "01865205247";
    // int indice= mapa.get_item(id_endereco);
    // mapa.Imprimir();
    // std::cout << indice << std::endl;

    processar_arquivo(nome_arquivo_eventos, *quad_tree);
    
    // delete quad_tree;
    return 0;
}