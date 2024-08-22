#include <iostream>
#include <unistd.h>
#include <string>
using namespace std;

class Andar{
public:
    int valor;
    Andar *cima;
    Andar *baixo;
    int chamando;
    int destino; //-1 ou 1
    Andar(){
        this->cima = this->baixo = nullptr;
    }
    Andar(int valor_){
        this->valor = valor_;
        this->cima = this->baixo = nullptr;
    }

};

class Predio{
private:


public:
    Andar *primeiro;
    Andar *ultimo;

    Predio(){
        primeiro = nullptr;
        ultimo = nullptr;
    }

    Andar *buscar(int valor){
        Andar *aux = this->primeiro;
        while(aux&&aux->valor!=valor){
            aux=aux->cima;
        }
        return aux;
    }
    
    void inserirCima(int valor){
        if(this->buscar(valor))
            return;
        Andar *aux = new Andar(valor);
        if(!this->primeiro){
            this->primeiro = this->ultimo = aux;
        } else{
            this->ultimo->cima = aux;
            aux->baixo = this->ultimo;
            this->ultimo = aux;
        }
    }
    
    void inserirBaixo(int valor){
        if(this->buscar(valor))
            return;
        Andar *aux = new Andar(valor);
        if(!this->primeiro){
            this->primeiro = this->ultimo = aux;
        } else{
            this->primeiro->baixo = aux;
            aux->cima = this->primeiro;
            this->primeiro = aux;
        }
    }
    
    void Listar(){
        Andar *aux = this->primeiro;
        while(aux){
            cout << aux->valor << " ";
            aux = aux->cima; 
        }
    }
    
    void remover(int valor){
        Andar *aux = this->buscar(valor);
        if(!aux){
            return;
        }
        if(aux==this->primeiro&&aux==this->ultimo){
            this->primeiro = nullptr;
            this->ultimo = nullptr;
        } else{
            if(aux==this->primeiro){
                aux->cima->baixo = nullptr;
                this->primeiro = aux->cima;
            }
            if(aux==this->ultimo){
                aux->baixo->cima = nullptr;
                this->ultimo = aux->baixo;
            }
            if(aux->cima && aux->baixo){
                aux->baixo->cima = aux->cima;
                aux->cima->baixo = aux->baixo;
            }
        }
        delete aux;
        
    }
    
    void limpar(){
        Andar *aux = this->primeiro;
        while(aux->cima){
            aux = aux->cima;
            delete aux->baixo;
        }
        delete aux;
        this->primeiro = nullptr;
        this->ultimo = nullptr;
    }

};

class Elevador{
public:
    string nome;
    Predio *predio;
    Andar *andar;
    int direcao; //-1 ou 1
    Elevador(Predio *p, string n){
        this->predio = p;
        this->andar = p->primeiro;
        this->nome = n;
        this->direcao=1;
    }
    
    void Subir(){
        if(this->andar->cima==nullptr){
            this->direcao=-1;
            return;
        }
        this->direcao=1;
        this->andar = this->andar->cima;
    }

    void Descer(){
        if(this->andar->baixo==nullptr){
            this->direcao=1;
            return;
        }
        this->direcao=-1;
        this->andar = this->andar->baixo;        
    }

    void Estado(){
        cout << this->nome << " " << this->andar->valor;
        if(this->direcao==1){
            cout << "S";
        }
        if(this->direcao==-1){
            cout << "D";
        }
        printf(" Destinos: ");
        for(int i=0;i<5;i++){
            printf("%d ", i);
        }
        cout << "\n";
    }
    void printara(){
        cout << this->nome;
        cout << this->predio->primeiro->cima->valor;
    }
    void chamar(Andar *chamada, int destino){
        // if((destino==this->direcao)&&(((chamada->valor)-(this->andar->valor))*(this->direcao)>0)){
        //     // primeira prioridade
        // } talvez nao use
    }
/*
AD-AA*D
AA AD  D  
-2 -1 -1 X -1
 2  3 -1 X -1
 3 10  1 O  7
-3  5 -1 X -8
-1  3  1 O  4


*/
    void verificar(){
        this->Subir();
    }

};

int main(void){
    Predio *p1 = new Predio();
    p1->inserirCima(1);
    p1->inserirCima(2);
    p1->inserirCima(3);
    p1->inserirCima(4);
    p1->inserirCima(5);
    p1->inserirCima(6);
    p1->inserirCima(7);
    p1->inserirCima(8);
    p1->inserirCima(9);
    p1->inserirCima(10);
    Elevador *e1 = new Elevador(p1, "E1");
    while(1){
        e1->Estado();
        if(e1->direcao==1){
            e1->Subir();
        }
        if(e1->direcao==-1){
            e1->Descer();
        }
        sleep(1);
    }


    return 0;
}