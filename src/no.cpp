#include "../include/no.hpp"
#include "../include/estacao.hpp"
#include <iostream>
//infinto
#include <limits>
No::No(Estacao_de_recarga estacao, long filho_noroeste, long filho_nordeste, long filho_sudoeste, long filho_sudeste){
    this->estacao = estacao;

    this->filho_noroeste = filho_noroeste;
    this->filho_nordeste = filho_nordeste;
    this->filho_sudoeste = filho_sudoeste;
    this->filho_sudeste = filho_sudeste;
    this->pai = -1;
    this->ocupado = true;
    this->limite_direito_superior = Ponto(0,0);
    this->limite_esquerdo_inferior = Ponto(0,0);
};

No::No(){
    
    this->filho_noroeste = -1;
    this->filho_nordeste = -1;
    this->filho_sudoeste = -1;
    this->filho_sudeste = -1;
    this->ocupado = false;  
    this->estacao = Estacao_de_recarga();
    this->pai = -1;
    this->limite_direito_superior = Ponto(0,0);
    this->limite_esquerdo_inferior = Ponto(0,0);

}



No::~No(){
}

long No::get_filho_noroeste(){
    return this->filho_noroeste;
}

long No::get_filho_nordeste(){
    return this->filho_nordeste;
}

long No::get_filho_sudoeste(){
    return this->filho_sudoeste;
}

long No::get_filho_sudeste(){
    return this->filho_sudeste;
}

long No::get_pai(){
    return this->pai;
}


Estacao_de_recarga& No::get_estacao() {
    return estacao; // Assuming estacao is a member of No
}

void No::set_filho_noroeste(long filho_noroeste){
    this->filho_noroeste = filho_noroeste;
}

void No::set_filho_nordeste(long filho_nordeste){
    this->filho_nordeste = filho_nordeste;
}

void No::set_filho_sudoeste(long filho_sudoeste){
    this->filho_sudoeste = filho_sudoeste;
}

void No::set_filho_sudeste(long filho_sudeste){
    this->filho_sudeste = filho_sudeste;
}

void No::set_estacao(Estacao_de_recarga estacao){
    this->estacao = estacao;
    this->ocupado = true;
    

}

void No::set_pai(long pai){
    this->pai = pai;
}
void No::print(){
    std::cout << "Estacao: " << this->estacao.get_id_endereco()<< std::endl;
    std::cout << "Filho noroeste: " << this->filho_noroeste << std::endl;
    std::cout << "Filho nordeste: " << this->filho_nordeste << std::endl;
    std::cout << "Filho sudoeste: " << this->filho_sudoeste << std::endl;
    std::cout << "Filho sudeste: " << this->filho_sudeste << std::endl;
}

bool No::tem_estacao(){
    return this->estacao.is_valida();
}
Ponto No::get_ponto(){
    return this->estacao.get_ponto();
}

bool No::esta_ocupado(){
    return this->ocupado;
}   

