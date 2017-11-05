#include "mapa.hpp"
#include <string>
#include <iostream>
#include <map>
#include <cmath>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#define PI 3.14159265359

using namespace std;

// Insira a altura e largura do objeto em metros, se quiser escolhe a granulacao
Mapa::Mapa(float altura, float largura, float granulacao){
	int n = (int) (altura/granulacao  + 1);
	int m = (int) (largura/granulacao + 1);
	mapa = new int [m*n];
	img_mapa =  Mat::zeros(m, n, CV_8UC3);//CV_8UC3 tipo matriz com 8 char - 3 canais
	coordenadas_do_mapa = new Coordenadas [m*n];
	definir_cores();
	this->m = m;
	this->n = n;
	this->altura = altura;
	this->largura = largura;
	this->granulacao = granulacao;
	for (int i = 0; i < m*n; ++i){
		mapa[i] = 0;
		coordenadas_do_mapa[i] = Coordenadas((int)(i/m)*granulacao,(int)(i%m)*granulacao);//========<<<<<<
	}
	construir_representacao();
}

Mapa::~Mapa(){
	//delete[] mapa;
	//delete[] coordenadas_do_mapa;
}


void Mapa::definir_cores(){ //<<<<<<<<<<
	cores[0] = Scalar(0,255,255);//(BGR)YELLOW
	cores[1] = Scalar(255,255,255);//WHITE
	cores[2] = Scalar(255,0,0);//BLUE
	cores[3] = Scalar(0,255,0);//GREEN
	cores[4] = Scalar(0,140,127);
	cores[5] = Scalar(255,255,0);
	cores[6] = Scalar(0,255,170);
	cores[7] = Scalar(52,135,0);
	cores[8] = Scalar(120,40,0);
	cores[9] = Scalar(20,200,180);
}

void Mapa::inserir_maquina(Coordenadas centro, int tam, int ang, int cor, string discoCor){
	int posy=-centro.get_y();
	int posx=centro.get_x();
	bool cond = (((posy+((1.4142135*tam/2)*cos((PI/4)-(PI*(ang%90)/180))))/granulacao>=m)||((posx+((1.4142135*tam/2)*cos((PI/4)-(PI*(ang%90)/180))))/granulacao>=n)||((posx-((1.4142135*tam/2)*cos((PI/4)-(PI*(ang%90)/180))))/granulacao<=0)||((posy-((1.4142135*tam/2)*cos((PI/4)-(PI*(ang%90)/180))))/granulacao<=0));
	if(cond){
		return;
	}
	Point retanguloFill[1][4];			//So pq a funcao de desenhar poligono ta pedindo
	Point pontos[4];
	pontos[0] = Point((posy+((1.4142135*tam/2)*cos((PI/4)-(PI*ang/180))))/granulacao , (posx-((1.4142135*tam/2)*sin((PI/4)-(PI*ang/180))))/granulacao);
	pontos[1] = Point((posy+((1.4142135*tam/2)*cos((3*PI/4)-(PI*ang/180))))/granulacao , (posx-((1.4142135*tam/2)*sin((3*PI/4)-(PI*ang/180))))/granulacao);
	pontos[2] = Point((posy+((1.4142135*tam/2)*cos((5*PI/4)-(PI*ang/180))))/granulacao , (posx-((1.4142135*tam/2)*sin((5*PI/4)-(PI*ang/180))))/granulacao);
	pontos[3] = Point((posy+((1.4142135*tam/2)*cos((7*PI/4)-(PI*ang/180))))/granulacao , (posx-((1.4142135*tam/2)*sin((7*PI/4)-(PI*ang/180))))/granulacao);

	tam=tam*0.85;

	//Mandando a mesma logica dos pontos (ctrl c ctrl v mesmo), mas com tamanho menor
	retanguloFill[0][0] = Point((posy+((1.4142135*tam/2)*cos((PI/4)-(PI*ang/180))))/granulacao , (posx-((1.4142135*tam/2)*sin((PI/4)-(PI*ang/180))))/granulacao);
	retanguloFill[0][1] = Point((posy+((1.4142135*tam/2)*cos((3*PI/4)-(PI*ang/180))))/granulacao , (posx-((1.4142135*tam/2)*sin((3*PI/4)-(PI*ang/180))))/granulacao);
	retanguloFill[0][2] = Point((posy+((1.4142135*tam/2)*cos((5*PI/4)-(PI*ang/180))))/granulacao , (posx-((1.4142135*tam/2)*sin((5*PI/4)-(PI*ang/180))))/granulacao);
	retanguloFill[0][3] = Point((posy+((1.4142135*tam/2)*cos((7*PI/4)-(PI*ang/180))))/granulacao , (posx-((1.4142135*tam/2)*sin((7*PI/4)-(PI*ang/180))))/granulacao);

  	const Point* ppt[1] = { retanguloFill[0] };		//copiei de um exemplo so pra garantir que funciona
  	int npt[] = { 4 };				//isso aqui tambem

	line(img_mapa,  pontos[0]   ,  pontos[1]  ,  cores[cor] );
	line(img_mapa,  pontos[1]   ,  pontos[2]  ,  cores[cor] );
	Scalar preenchimento;
	if( (discoCor=="amarelo") || (discoCor=="azul") || (discoCor=="vermelho") ){
		if(discoCor=="amarelo"){
			preenchimento = cores[0];
		}
		else if(discoCor=="azul"){
			preenchimento = cores[2];
		}
		else if(discoCor=="vermelho"){
			preenchimento = Scalar(0,0,255);
		}
		fillPoly(img_mapa, ppt, npt, 1 , preenchimento);
	}
	/**/

}

string Mapa::representacao() const{
	return repr;
}

void Mapa::inserir_parede(Coordenadas coord){ /// UTILIZAR INSERIR RETANGULO, BUZZ FALOU ALGUMA COISA SOBRE ESSA FUNÇAO
	int m = coord.get_y()/granulacao;
	int n = coord.get_x()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0)//condição dentro mapa
		return;
	mapa[m*this->n+n] = 1;
	repr.replace(4*(n*this->m+m)+2,1,"\u25A0",2,2);
}

void Mapa::inserir_retangulo(Coordenadas coord1, Coordenadas coord2, int tipo){
	int m_inicial = coord1.get_y()/granulacao;
	int n_inicial = coord1.get_x()/granulacao;
	int m_final = coord2.get_y()/granulacao;
	int n_final = coord2.get_x()/granulacao;
	bool cond1 = (m_inicial >= m || n_inicial >= n || m < 0 || n < 0);
	bool cond2 = (m_final >= m || n_final >= n);
	bool cond3 = (m_inicial > m_final || n_inicial > n_final);
	if(cond1 || cond2 || cond3)
		return;
	if(tipo != LINHA && tipo != PAREDE){
		if(areas_armazenadas.count(tipo))
			return;
		else
			areas_armazenadas[tipo] = Area(tipo);
	}

	rectangle(img_mapa,Point(n_inicial,m_inicial),Point(n_final,m_final), cores[tipo],-1);
	for (int j = m_inicial; j <= m_final; ++j){
		for (int i = n_inicial; i <= n_final; ++i){
			if(tipo == LINHA){
				inserir_linha(Coordenadas(i*granulacao,j*granulacao));
			}else if(tipo == PAREDE){
				inserir_parede(Coordenadas(i*granulacao,j*granulacao));
			}else{
				areas_armazenadas[tipo].adicionar_coordenada(coordenadas_do_mapa[i*this->m+j]);
				inserir_marcador(Coordenadas(i*granulacao,j*granulacao),tipo);
			}
		}
	}
}


Coordenadas Mapa::coordenada_area(int id, Coordenadas p){
	if(!areas_armazenadas.count(id) || id == LINHA || id == PAREDE)
		return Coordenadas(0,0);
	return areas_armazenadas[id].pegar_coordenada(p);
}

Coordenadas Mapa::coordenada_area(int id){
	if(!areas_armazenadas.count(id) || id == LINHA || id == PAREDE)
		return Coordenadas(0,0);
	return areas_armazenadas[id].pegar_meio();
}

void Mapa::inserir_linha(Coordenadas coord){
	int m = coord.get_y()/granulacao;
	int n = coord.get_x()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0)
		return;
	mapa[n*this->m+m] = 2;
	repr.replace(4*(n*this->m+m)+2,1,"\u25A4",2,2);
}

void Mapa::inserir_marcador(Coordenadas coord, int tipo){
	int m = coord.get_y()/granulacao;
	int n = coord.get_x()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0 || tipo == LINHA || tipo == PAREDE)
		return;
	mapa[n*this->m+m] = tipo;
	repr.replace(4*(n*this->m+m)+2,1,"\u25B2",2,2);
}

bool Mapa::checar_se_na_area(Coordenadas p, int area){
	int m = p.get_y()/granulacao;
	int n = p.get_x()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0)
		return false;
	return mapa[n*this->m+m]==area;
}

int Mapa::qual_area(Coordenadas p){
	int m = p.get_y()/granulacao;
	int n = p.get_x()/granulacao;
	if(m >= this->m || n >= this->n || m < 0 || n < 0)
		return false;
	return mapa[n*this->m+m];
}

/*void Mapa::inserir_objeto(Objeto * obj){
	if ( objs.find(obj->get_id()) == objs.end() ) {
	  objs.insert(pair<string, Objeto*>(obj->get_id(),obj));
	}
}

void Mapa::atualizar_mapa(){
	int x,y;
	for (map<string, Objeto*>::iterator it=objs.begin(); it!=objs.end(); ++it){
   		Objeto* obj = it->second;
   		remover_objeto(obj->get_x(),obj->get_y());
   		obj->atualizar(x,y);
   		desenhar_objeto(obj,x,y);
	}
}*/

void Mapa::construir_representacao(){
	repr = string();
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m; ++j){
			if(mapa[i*m+j]==0){
				repr += "\u25A1";
			}else if(mapa[i*m+j]==1){
				repr += "\u25A0";
			}else if(mapa[i*m+j]==2){
				repr += "\u25A4";
			}else{
				repr += "\u25EB";
			}
			if(j<m-1)
				repr+=" ";
		}
		repr+='\n';
	}
}

void Mapa::mostrar_mapa(){
	imshow("Mapa",img_mapa);
}

void Mapa::mostrar_mapa_com_robo(Coordenadas p){
	Mat pos_robo;
	img_mapa.copyTo(pos_robo);
	int m = p.get_y()/granulacao;
	int n  = p.get_x()/granulacao;
	circle(pos_robo,Point(n,m),20/granulacao,Scalar(0,0,255),-1);
	line(pos_robo,Point(n,m),Point(n+20*cos(p.get_theta()*PI/180)/granulacao,m+20*sin(p.get_theta()*PI/180)/granulacao),Scalar(255,255,255),2);
	imshow("Mapa",pos_robo);
}

/*void Mapa::desenhar_objeto(Objeto* obj, int x, int y){
	if(x >= m || y >= n || x < 0 || y < 0)
		return;
	mapa[y*m+x] = 3;
	repr.replace(4*(y*m+x)+2,1,obj->get_simbolo(),2,2);
}

void Mapa::remover_objeto(int x, int y){
	if(x >= m || y >= n || x < 0 || y < 0)
		return;
	mapa[y*m+x] = 3;
	repr.replace(4*(y*m+x)+2,1,"\u25A1",2,2);
}*/

std::ostream &operator<<(std::ostream &os, Mapa const &m) {
    return os << m.representacao();
}