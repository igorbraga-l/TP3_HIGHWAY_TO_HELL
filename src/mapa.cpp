// Chave a se refere a string id da estação de recarga
// Valor a se refere ao índice da estação de recarga no array de nós da quad tree
#include "../include/mapa.hpp"
#include <iostream>
#include <string>
#include <bits/stdc++.h>

Mapa::Mapa(int tamanho){
    tamanho_original= tamanho;
    tamanho_tabela= tamanho;
    tamanho_conjunto=0;
    tabela= new Elemento_tabela[tamanho];
    for (int i=0; i<tamanho; i++){
        tabela[i].vazio= true;
        tabela[i].retirada= false;
        tabela[i].chave= "";
        tabela[i].dado= -1;
    }
}

Mapa::~Mapa(){
    if(tabela!=nullptr) delete[] tabela;
    
}

/**
 * Insere um par chave-valor na tabela hash.
 * 
 * @param chave A chave a ser inserida.
 * @param valor O valor associado à chave.
 */
void Mapa::Inserir(std::string chave, int valor){
    int pos= Hash(chave);
 
    int i=0;
    while(i< tamanho_tabela && !tabela[(pos+i)%tamanho_tabela].vazio){
        i++;    
    }
    if(Pertence(chave)) return;
    if(i==tamanho_tabela){
        Resize(tamanho_tabela*2);
        return Inserir(chave, valor);
    }

    else{
        tabela[(pos+i)%tamanho_tabela].dado= valor;
        tabela[(pos+i)%tamanho_tabela].vazio= false;
        tabela[(pos+i)%tamanho_tabela].retirada= false;
        tabela[(pos+i)%tamanho_tabela].chave= chave;
        tamanho_conjunto++;
    }
}

/**
 * Remove um par chave-valor da tabela hash.
 * 
 * @param chave A chave a ser removida.
 */
void Mapa::Remover(std::string chave){
    int pos= Hash(chave);
    int i=0;
    while(i< tamanho_tabela && tabela[(pos+i)%tamanho_tabela].chave!=chave){
        i++;    
    }

    if(i==tamanho_tabela){
        return;
    }

    else{
        tabela[(pos+i)%tamanho_tabela].vazio= true;
        tabela[(pos+i)%tamanho_tabela].retirada= true;
        tamanho_conjunto--;
    }
}

/**
 * Verifica se uma chave está presente na tabela hash.
 * 
 * @param s A chave a ser verificada.
 * @return true se a chave está presente, false caso contrário.
 */
bool Mapa::Pertence(std::string s){
    int pos= Hash(s);
    int i=0;
    while(i< tamanho_tabela && tabela[(pos+i)%tamanho_tabela].chave!=s){
        i++;    
    }

    if(i==tamanho_tabela){
        return false;
    }

    else{
        return true;
    }
}

/**
 * Imprime todos os elementos da tabela hash.
 */
void Mapa::Imprimir(){
    for(int i=0; i<tamanho_tabela; i++){
        if(!tabela[i].vazio && !tabela[i].retirada){
            std::cout<< tabela[i].chave<< " "<< tabela[i].dado<< std::endl;
        }
    }
}

/**
 * Calcula o hash de uma string.
 * 
 * @param s A string a ser hasheada.
 * @return O valor do hash.
 */
int Mapa::Hash(std::string s){
    int key=0;
    for(long unsigned int i=0; i<s.length(); i++){
        key+= s[i]*(i+1);
    }
    key= key%tamanho_tabela;
    return key;
}

void Mapa::Rehash(int pos){

}

/**
 * Redimensiona a tabela hash.
 * 
 * @param tamanho O novo tamanho da tabela.
 */
void Mapa::Resize(size_t tamanho){
    Elemento_tabela* nova_tabela = new Elemento_tabela[tamanho];
    Elemento_tabela* velha_tabela = tabela;

    for (size_t i = 0; i < tamanho; i++){
        nova_tabela[i].vazio = true;
        nova_tabela[i].retirada = false;
    }

    tabela = nova_tabela;
    
    // Copiando a tabela antiga para a nova
    for (int i = 0; i < tamanho_tabela; i++){
        if (!velha_tabela[i].vazio && !velha_tabela[i].retirada) {
            Inserir(velha_tabela[i].chave, velha_tabela[i].dado);
        }
    }
    
    delete[] velha_tabela;  

    tamanho_tabela = tamanho; 
}

/**
 * Obtém o valor associado a uma chave.
 * 
 * @param chave A chave cujo valor será obtido.
 * @return O valor associado à chave, ou -1 se a chave não estiver presente.
 */
int Mapa::get_item(std::string chave){
    int pos= Hash(chave);
    int i=0;
    while(i< tamanho_tabela && tabela[(pos+i)%tamanho_tabela].chave!=chave){
        i++;    
    }

    if(i==tamanho_tabela){
        return -1;
    }

    else{
        return tabela[(pos+i)%tamanho_tabela].dado;
    }
}