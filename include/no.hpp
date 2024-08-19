#ifndef NODE_HPP
#define NODE_HPP

#include <stdlib.h>
#include <math.h>
#include "estacao.hpp"



class No{
        private:

        long filho_noroeste;
        long filho_nordeste;
        long filho_sudoeste;
        long filho_sudeste;
        long pai;
        Estacao_de_recarga estacao;
        bool ocupado;

        Ponto limite_direito_superior;
        Ponto limite_esquerdo_inferior;


        public:
        No(Estacao_de_recarga estacao, long filho_noroeste, long filho_nordeste, long filho_sudoeste, long filho_sudeste);
        No();
        ~No();
        long get_filho_noroeste();
        long get_filho_nordeste();
        long get_filho_sudoeste();
        long get_filho_sudeste();
        long get_pai();
        Ponto get_ponto();

        Estacao_de_recarga& get_estacao();
        void set_filho_noroeste(long filho_noroeste);
        void set_filho_nordeste(long filho_nordeste);
        void set_filho_sudoeste(long filho_sudoeste);
        void set_filho_sudeste(long filho_sudeste);
        void set_pai(long pai); 
        void set_estacao(Estacao_de_recarga estacao);
        void print();
        bool tem_estacao();
        bool esta_ocupado();
};

#endif
