#include "area.hpp"
#include <vector>
#include <iostream>
#include <cmath>

#define PI 3.14159265f

#define R 0
#define Y 1
#define G 2
#define INDEFINIDO -1
#define VAZIO 4

#define XA0 30
#define YA0 -25

#define XA1 375
#define YA1 -375

#define XA2 375
#define YA2 -225

#define XA3 375
#define YA3 -174

#define XA4 375
#define YA4 -124

#define XA5 -5000
#define YA5 -5000

#define XYAErro 24



Area::Area(int id){
    this-> ordemAtualDiscos = {VAZIO, VAZIO};
    this->id = id;

    switch(id){
        case 0:
            this->ordemFINAL.push_back(VAZIO);
            this->ordemFINAL.push_back(VAZIO);
            this->carea = Coordenadas(XA0,YA0);
            this->adicionar_coordenada(carea);
            break;
        case 1:
            this->ordemFINAL.push_back(R);
            this->ordemFINAL.push_back(G);
            this->carea = Coordenadas(XA1,YA1);
            this->adicionar_coordenada(carea);
            break;
        case 2:
            this->ordemFINAL.push_back(VAZIO);
            this->ordemFINAL.push_back(VAZIO);
            this->carea = Coordenadas(XA2,YA2);
            this->adicionar_coordenada(carea);
            break;
        case 3:
            this->ordemFINAL.push_back(VAZIO);
            this->ordemFINAL.push_back(VAZIO);
            this->carea = Coordenadas(XA3,YA3);
            this->adicionar_coordenada(carea);
            break;
        case 4:
            this->ordemFINAL.push_back(VAZIO);
            this->ordemFINAL.push_back(VAZIO);
            this->carea = Coordenadas(XA4,YA4);
            this->adicionar_coordenada(carea);
            break;
        case 5:
            this->ordemFINAL.push_back(VAZIO);
            this->ordemFINAL.push_back(VAZIO);
            this->carea = Coordenadas(XA5,YA5);
            this->adicionar_coordenada(carea);
            break;
        // case 1:
        //     this->ordemFINAL.push_back(R);
        //     this->ordemFINAL.push_back(Y);
        //     break;
        // case 2:
        //     this->ordemFINAL.push_back(R);
        //     this->ordemFINAL.push_back(Y);
        //     break;
        // case 3:
        //     this->ordemFINAL.push_back(R);
        //     this->ordemFINAL.push_back(Y);
        //     break;
        // case 4:
        //     this->ordemFINAL.push_back(R);
        //     this->ordemFINAL.push_back(Y);
        //     break;
        // case 5:
        //     this->ordemFINAL.push_back(VAZIO);
        //     this->ordemFINAL.push_back(VAZIO);
        //     break;
    }
    num_elem = 0;
}

void Area::adicionar_coordenada(Coordenadas coord){
    float x_medio,y_medio;
    coordenadas.push_back(coord);
    num_elem++;
    x_medio = ponto_medio.get_x()*(num_elem-1)/num_elem + coord.get_x()/num_elem;
    y_medio = ponto_medio.get_y()*(num_elem-1)/num_elem + coord.get_y()/num_elem;
    ponto_medio = Coordenadas(x_medio, y_medio);
}

Coordenadas Area::pegar_coordenada(Coordenadas coord){
    float min = 99999,valor,orientacao;
    Coordenadas resultado;
    for (std::vector<Coordenadas>::iterator i = coordenadas.begin(); i != coordenadas.end(); ++i){
        valor = i->calcular_distancia(coord);
        //std::cout << "Valor = " << valor <<"\n";
        if(valor < min){
            //std::cout << "Menor? = " << valor <<"\n";
            min = valor;
            resultado = *i;
            //std::cout << "Ponto de origem = " << coord <<"\n";
            //std::cout << "Menor resultado = " << resultado <<"\n";
        }
    }
    orientacao = std::atan2(ponto_medio.get_y() - resultado.get_y(), ponto_medio.get_x() - resultado.get_x())*180/PI;
    resultado.set_theta(orientacao);
    return resultado;
}