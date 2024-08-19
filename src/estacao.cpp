#include "../include/estacao.hpp"   

#include <math.h>
// calculates Euclidean distance between (x1,y1) and (x2,y2)
double distancia(double x1, double y1, double x2, double y2){
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0); 
}
Estacao_de_recarga::Estacao_de_recarga(){
    this->id_endereco = "";
    this->id_logradouro = -1;
    this->sigla_tipo = "";
    this->nome_logradouro = "";
    this->numero_imovel = -1;
    this->nome_bairro = "";
    this->nome_regiao = "";
    this->cep = -1;
    this->ponto = Ponto();
    this->ativa = false;
    this->valida = false;
}

Estacao_de_recarga::Estacao_de_recarga(std::string& id_endereco, long id_logradouro, std::string& sigla_tipo, std::string& nome_logradouro, int numero_imovel, std::string& nome_bairro, std::string& nome_regiao, int cep, Ponto& ponto){
    this->id_endereco = id_endereco;
    this->id_logradouro = id_logradouro;
    this->sigla_tipo = sigla_tipo;
    this->nome_logradouro = nome_logradouro;
    this->numero_imovel = numero_imovel;
    this->nome_bairro = nome_bairro;
    this->nome_regiao = nome_regiao;
    this->cep = cep;
    this->ponto = ponto;
    this->ativa = true;
    this->valida = true ;
}

std::string Estacao_de_recarga::get_id_endereco(){
    return this->id_endereco;
}

long Estacao_de_recarga::get_id_logradouro(){
    return this->id_logradouro;
}

std::string Estacao_de_recarga::get_sigla_tipo(){
    return this->sigla_tipo;
}

std::string Estacao_de_recarga::get_nome_logradouro(){
    return this->nome_logradouro;
}


int Estacao_de_recarga::get_numero_imovel(){
    return this->numero_imovel;
}

std::string Estacao_de_recarga::get_nome_bairro(){
    return this->nome_bairro;
}

std::string Estacao_de_recarga::get_nome_regiao(){
    return this->nome_regiao;
}


int Estacao_de_recarga::get_cep(){
    return this->cep;
}

Ponto Estacao_de_recarga::get_ponto(){
    return this->ponto;
}

bool Estacao_de_recarga::is_ativa(){
    return this->ativa;
}

bool Estacao_de_recarga::is_valida(){
    return this->valida;
}

void Estacao_de_recarga::set_id_endereco(std::string& id_endereco){
    this->id_endereco = id_endereco;
}

void Estacao_de_recarga::set_id_logradouro(long id_logradouro){
    this->id_logradouro = id_logradouro;
}

void Estacao_de_recarga::set_sigla_tipo(std::string& sigla_tipo){
    this->sigla_tipo = sigla_tipo;
}

void Estacao_de_recarga::set_nome_logradouro(std::string& nome_logradouro){
    this->nome_logradouro = nome_logradouro;
}


void Estacao_de_recarga::set_numero_imovel(int numero_imovel){
    this->numero_imovel = numero_imovel;
}

void Estacao_de_recarga::set_nome_bairro(std::string& nome_bairro){
    this->nome_bairro = nome_bairro;
}

void Estacao_de_recarga::set_nome_regiao(std::string& nome_regiao){
    this->nome_regiao = nome_regiao;
}

void Estacao_de_recarga::set_cep(int cep){
    this->cep = cep;
}

void Estacao_de_recarga::set_ponto(Ponto& ponto){
    this->ponto = ponto;
}

void Estacao_de_recarga::set_ativa(bool ativa){
    this->ativa = ativa;
}

void Estacao_de_recarga::set_valida(bool valida){
    this->valida = valida;
}

Ponto::Ponto(double x, double y){
    this->x = x;
    this->y = y;
} 

Ponto::Ponto(){
    this->x = 0;
    this->y = 0;
}


