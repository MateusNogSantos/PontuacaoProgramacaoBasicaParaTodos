#ifndef EVENTO_H
#define EVENTO_H

#include <vector>
#include <utility>
#include <queue>
#include <stdexcept>
#include <algorithm> 

using namespace std;

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
    Grupo();

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

    Evento(int numeroEquipes);

    void concluiuExercicioMedio(int indiceEquipe);
    void concluiuExercicioFacil(int indiceEquipe);
    void ajudou(int indiceEquipe);

    priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> mostrarTabela();

    int getAjudas(int i);
    int getExerciciosFaceis(int i);
    int getExerciciosMedios(int i);
};

#endif