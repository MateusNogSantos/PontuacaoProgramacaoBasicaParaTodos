#ifndef EVENTO_H
#define EVENTO_H

#include <vector>
#include <utility>
#include <queue>
#include <stdexcept>
#include <algorithm> // Necessário para o std::max

using namespace std;

// Forward Declaration para a classe Evento poder acessar membros de Grupo
class Evento;

class Grupo {
    friend class Evento;

protected:
    int ajudas;

private:
    int pontuacao;
    vector<int> exerciciosFaceis, exerciciosMedios;

    void adicionaPontuacaoFacil(int pos);
    void adicionaPontuacaoMedio(int pos);
    void ajudou();

public:
    // Construtor
    Grupo();

    // Getters
    int getPontuacao() { return pontuacao; }
    int getExerciciosFaceis() { return exerciciosFaceis.size(); }
    int getExerciciosMedios() { return exerciciosMedios.size(); }
};

class Evento {
private:
    int qtdeEquipes;
    int posExerciciosFaceis;
    int posExerciciosMedios;
    vector<Grupo> equipe;

public:
    // Construtor
    Evento(int numeroEquipes);

    // Métodos de Logica
    void concluiuExercicioMedio(int indiceEquipe);
    void concluiuExercicioFacil(int indiceEquipe);
    void ajudou(int indiceEquipe);

    // Retorna a fila de prioridade para a tabela final
    priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> mostrarTabela();

    // Getters de estado
    int getAjudas(int i);
    int getExerciciosFaceis(int i);
    int getExerciciosMedios(int i);
};

#endif // EVENTO_H