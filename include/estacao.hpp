#ifndef ESTACAO_HPP
#define ESTACAO_HPP
#include <string>
class Ponto{
  public:
  double x;
  double y;
  Ponto(double x, double y);
  Ponto();
}; 

class Estacao_de_recarga {
private:
    std::string id_endereco;
    long id_logradouro;
    std::string sigla_tipo;
    std::string nome_logradouro;
    int numero_imovel;
    std::string nome_bairro;
    std::string nome_regiao;
    int cep;
    Ponto ponto;
    bool ativa;
    bool valida;

public:
    // Default ructor
    Estacao_de_recarga();

    // Parameterized ructor
    Estacao_de_recarga( std::string& id_endereco, long id_logradouro,  std::string& sigla_tipo,
                        std::string& nome_logradouro, int numero_imovel,  std::string& nome_bairro,
                        std::string& nome_regiao, int cep,  Ponto& ponto);

    // Getters
    std::string get_id_endereco();  
    long get_id_logradouro();  
    std::string get_sigla_tipo(); 
    std::string get_nome_logradouro();
    int get_numero_imovel();
    std::string get_nome_bairro();
    std::string get_nome_regiao();
    int get_cep();
    Ponto get_ponto();
    bool is_ativa();
    bool is_valida();

    // Setters
    void set_id_endereco( std::string& id_endereco);
    void set_id_logradouro(long id_logradouro);
    void set_sigla_tipo( std::string& sigla_tipo);
    void set_nome_logradouro( std::string& nome_logradouro);
    void set_numero_imovel(int numero_imovel);
    void set_nome_bairro( std::string& nome_bairro);
    void set_nome_regiao( std::string& nome_regiao);
    void set_cep(int cep);
    void set_ponto( Ponto& ponto);
    void set_ativa(bool ativa);
    void set_valida(bool valida);
};
typedef struct knn{
        double distancia; // distance between origin location and recharging location
        std::string id;      // recharging location id
} knn_t, *ptr_knn_t;

// calculates Euclidean distance between (x1,y1) and (x2,y2)
double distancia(double x1, double y1, double x2, double y2);


#endif