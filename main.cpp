#include "programacaoBasica.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <iostream>
#include <queue>

int numeroDeEquipes;

class MyApp : public wxApp {

    public:
    virtual bool OnInit();

};

class MainFrame : public wxFrame {

    private:

    Evento* projeto;
    wxListCtrl* Placar;
    wxTextCtrl* registroEquipe;
    wxTextCtrl* registroAtividade;
    wxStaticText* alerta;
    public:

    MainFrame() : wxFrame(NULL,wxID_ANY,"Programacao Basica Para Todos",wxDefaultPosition,wxSize(400,400)){

        wxPanel* panel = new wxPanel(this);
        wxBoxSizer* sizerVertical = new wxBoxSizer(wxVERTICAL);
        wxBoxSizer* sizerHorizontal = new wxBoxSizer(wxHORIZONTAL);
        wxStaticText* explicacao = new wxStaticText(panel,wxID_ANY,"0 -> Ajuda \n1 -> Exercicio Facil \n2 -> Exercicio Medio");
        Placar = new wxListCtrl(panel,wxID_ANY,wxDefaultPosition,wxSize(540,540),wxLC_REPORT);
        alerta = new wxStaticText(panel,wxID_ANY,"");
        alerta->SetForegroundColour(*wxRED);

        registroEquipe = new wxTextCtrl(panel,wxID_ANY,"");
        registroEquipe->SetHint("Equipe");
        registroAtividade = new wxTextCtrl(panel,wxID_ANY,"");
        registroAtividade->SetHint("Atividade");
        wxButton* botaoConfirma = new wxButton(panel,wxID_ANY,"Confirma");

        this->SetMinSize(wxSize(600,750));

        int tamanhoColunas = 90;

        botaoConfirma->SetMinSize(wxSize(100,60));
        registroAtividade->SetMinSize(wxSize(100,60));
        registroEquipe->SetMinSize(wxSize(100,60));
        Placar->InsertColumn(0,"Posicao",wxLIST_FORMAT_LEFT,tamanhoColunas);
        Placar->InsertColumn(1,"Equipes",wxLIST_FORMAT_LEFT,tamanhoColunas);
        Placar->InsertColumn(2,"N De Ajudas",wxLIST_FORMAT_LEFT,tamanhoColunas);
        Placar->InsertColumn(3,"N Ex. Facil",wxLIST_FORMAT_LEFT,tamanhoColunas);
        Placar->InsertColumn(4,"N Ex. Medios",wxLIST_FORMAT_LEFT,tamanhoColunas);
        Placar->InsertColumn(5,"Total",wxLIST_FORMAT_LEFT,tamanhoColunas);

        sizerVertical->AddStretchSpacer(10);

        sizerVertical->Add(Placar,0,wxALL | wxALIGN_CENTER,10);
        sizerVertical->Add(alerta,0,wxEXPAND | wxLEFT | wxRIGHT,30);
        sizerVertical->Add(sizerHorizontal,0,wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM , 10);
        sizerVertical->Add(explicacao,0,wxALL | wxALIGN_CENTER_HORIZONTAL,10);

        sizerHorizontal->AddStretchSpacer(10);

        sizerHorizontal->Add(registroEquipe,0,  wxALL | wxALIGN_CENTER ,10);
        sizerHorizontal->Add(registroAtividade,0, wxALL | wxALIGN_CENTER, 10);
        sizerHorizontal->Add(botaoConfirma,0, wxALL| wxALIGN_CENTER , 10);

        sizerHorizontal->AddStretchSpacer(10);

        sizerVertical->AddStretchSpacer(10);

        panel->SetSizer(sizerVertical);
        botaoConfirma->Bind(wxEVT_BUTTON,&MainFrame::OnConfirm,this);

    }

void listarTabela() {
    Placar->DeleteAllItems();

    priority_queue<pair<int,int>, vector<pair<int,int>>, less<pair<int,int>>> minHeap;

    minHeap = projeto->mostrarTabela();

    for(int i = 0; i < numeroDeEquipes; i++) {
        long index = Placar->InsertItem(i, wxString::Format("%d", i + 1)); 

        pair<int,int> equipe = minHeap.top();
        minHeap.pop();

        Placar->SetItem(index, 1, "Equipe " + to_string(equipe.second));  
        Placar->SetItem(index,2,to_string(projeto->getAjudas(equipe.second- 1)));
        Placar->SetItem(index,3,to_string(projeto->getExerciciosFaceis(equipe.second - 1)));
        Placar->SetItem(index,4,to_string(projeto->getExerciciosMedios(equipe.second - 1)));   
        Placar->SetItem(index, 5,to_string(equipe.first));                                  
    }
}

    void OnConfirm(wxCommandEvent& event){

        int comando,idEquipe;

        wxString temp;

        temp = registroEquipe->GetValue();
        temp.ToInt(&idEquipe);
        temp = registroAtividade->GetValue();
        temp.ToInt(&comando);

        if(idEquipe > 0 && idEquipe <= numeroDeEquipes){

            switch(comando){
                case 0:
                    projeto->ajudou(idEquipe);
                break;
                case 1:
                    projeto->concluiuExercicioFacil(idEquipe);
                break;
                case 2:
                    projeto->concluiuExercicioMedio(idEquipe);
                break;
                default:
                    alerta->SetLabel("Atividade nao coerente!");
                break;
            }


        }else alerta->SetLabel("Equipe nao existe!");

        listarTabela();

        this->Layout();
        alerta->Layout();
        this->Update();

    }  
    
    void constroiEvento(int n){

        projeto = new Evento(n);
    }

};

class InitFrame : public wxFrame{
    public:
    InitFrame(MainFrame* mPtFrame):wxFrame(NULL,wxID_ANY,"Programacao Basica Para Todos",wxDefaultPosition,wxSize(400,400)){

        janelaPrincipal = mPtFrame;

        wxPanel *panel = new wxPanel(this);
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        wxStaticText* leituraDeDados = new wxStaticText(panel,wxID_ANY,"Digite o numero de equipes.");
        wxButton *botaoConfirma = new wxButton(panel,wxID_ANY,"Confirmar");
        campoDeTexto = new wxTextCtrl(panel,wxID_ADD,"");

        this->SetMinSize(wxSize(270,300));

        leituraDeDados->SetForegroundColour(wxColor(*wxWHITE));
        leituraDeDados->SetFont(wxFont(12,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_MAX,wxFONTWEIGHT_BOLD));

        sizer->AddStretchSpacer(10);

        sizer->Add(leituraDeDados,0,wxALL | wxALIGN_CENTER,10);
        sizer->Add(campoDeTexto,0,wxALL | wxALIGN_CENTER,10);
        sizer->Add(botaoConfirma,0,wxALL | wxALIGN_CENTER,10);

        sizer->AddStretchSpacer(10);

        panel->SetSizer(sizer);
        sizer->Fit(this);
        this->Layout();

        botaoConfirma->Bind(wxEVT_BUTTON,&InitFrame::OnButtonConfirmClick,this);

    }

    void OnButtonConfirmClick(wxCommandEvent& event){

        this->Close();
        janelaPrincipal->Show(true);

        wxString texto = campoDeTexto->GetValue();

        texto.ToInt(&numeroDeEquipes);

        janelaPrincipal->constroiEvento(numeroDeEquipes);
        janelaPrincipal->listarTabela();
        
    }

    private:

    wxTextCtrl *campoDeTexto;

    MainFrame* janelaPrincipal;

};

bool MyApp::OnInit(){

    MainFrame* nMain = new MainFrame();
    MainFrame* ptFrame = nMain;
    InitFrame* FirstFrame = new InitFrame(ptFrame);

    FirstFrame->Show(true);

    std::cout << "Aplicação iniciada" << std::endl;

    return true;
}

wxIMPLEMENT_APP(MyApp);
