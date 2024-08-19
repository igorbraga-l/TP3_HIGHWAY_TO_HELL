    #ifndef SET_HPP
    #define SET_HPP

    // #include <bits/stdc++.h>

    #include <string>
    using namespace std;

    typedef struct s_table_elem{
        
        int dado;
        bool vazio;
        bool retirada;
        string chave;

    }  Elemento_tabela;

    class Mapa{

        public:
            Mapa(int tamanho);
            ~Mapa();

            void Inserir(string chave,int valor);
            void Remover(string chave);
            bool Pertence(string chave);
            int get_item(string chave);
    

            void Imprimir();

        private:
            int tamanho_original;
            int tamanho_tabela;
            int tamanho_conjunto;
            Elemento_tabela* tabela;

            int Hash(string s);
            void Rehash(int pos);
            void Resize(size_t tamanho);
            
    };


    #endif