#include "mapa.hpp"
#include "fabricademapas.hpp"
#include <iostream>
#include <cmath>

#define PI 3.14159265f

bool FabricaDeMapas::criarMapa(string nome, Mapa& mapa){
    if(nome == "Modulo1Teste"){

        mapaModulo1Teste(mapa);
        return true;

    }else if(nome == "Modulo11Teste"){

        mapaModulo11Teste(mapa);
        return true;

    }else if(nome == "Modulo2Teste"){

        mapaModulo2Teste(mapa);
        return true;

    }else if(nome == "Modulo3Teste"){

        mapaModulo3Teste(mapa);
        return true;

    }else if(nome == "Modulo1"){

        mapaModulo1(mapa);
        return true;

    }else if(nome == "Modulo2"){

        mapaModulo2(mapa);
        return true;

    }else if (nome == "Modulo3"){

        mapaModulo3(mapa);
        return true;

    }else{

        return false;

    }
}

void FabricaDeMapas::mapaModulo1Teste(Mapa & mapa){
	cout << "XABRAU";
   mapa = Mapa(400, 400, 0.5);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(400,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,400),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,398.5), Coordenadas(400,400),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(398.5,0), Coordenadas(400,400),mapa.PAREDE);

    // Area de inicio
    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(48.5,48.5),2);

    mapa.inserir_retangulo(Coordenadas(0, 400),Coordenadas(50, 350), mapa.LINHA);

    mapa.inserir_retangulo(Coordenadas(350, 80),Coordenadas(400, 130), mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(350, 131),Coordenadas(400, 180), mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(350, 181),Coordenadas(400, 230), mapa.LINHA);

    mapa.inserir_retangulo(Coordenadas(350, 0),Coordenadas(400, 50), mapa.LINHA);
    //PAREDES
    /*mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(400,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,400),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,398.5), Coordenadas(400,400),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(398.5,0), Coordenadas(400,400),mapa.PAREDE);

    //Area inicio
    mapa.inserir_retangulo(Coordenadas(348,2),Coordenadas(398,50),2);
    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(348.5,2),Coordenadas(350.5,51.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(348,49.5),Coordenadas(398.5,51.5),mapa.LINHA);


    // Area de deposito
    mapa.inserir_retangulo(Coordenadas(0,0),Coordenadas(40,398),3);

    // Linhas da area de deposito
    mapa.inserir_retangulo(Coordenadas(0,65.5),Coordenadas(40,66.5),mapa.LINHA);//area1
    mapa.inserir_retangulo(Coordenadas(0,132.5),Coordenadas(40,133.5),mapa.LINHA);//area2
    mapa.inserir_retangulo(Coordenadas(0,199.5),Coordenadas(40,200.5),mapa.LINHA);//area3
    mapa.inserir_retangulo(Coordenadas(0,265.5),Coordenadas(40,266.5),mapa.LINHA);//area1
    mapa.inserir_retangulo(Coordenadas(0,332.5),Coordenadas(40,333.5),mapa.LINHA);//area2
    mapa.inserir_retangulo(Coordenadas(0,399.5),Coordenadas(40,300.5),mapa.LINHA);//area3
/*/
}

void FabricaDeMapas::mapaModulo11Teste(Mapa & mapa){

    mapa = Mapa(186, 373, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(186,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,373),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,371.5), Coordenadas(186,373),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(184.5,0), Coordenadas(186,373),mapa.PAREDE);

    // Area de inicio
    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(59,59),2);

    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(59.5,2),Coordenadas(61.5,61.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,59.5),Coordenadas(61.5,61.5),mapa.LINHA);

    // Area de deposito
    mapa.inserir_retangulo(Coordenadas(128.5,313),Coordenadas(184.5,371.5),3);

    // Linhas da area de deposito
    mapa.inserir_retangulo(Coordenadas(126,311.5),Coordenadas(128,371.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(126,311.5),Coordenadas(184.5,313.5),mapa.LINHA);

    // Area central
    mapa.inserir_retangulo(Coordenadas(48,89),Coordenadas(139,284),4);

    // Linhas da area central
    mapa.inserir_retangulo(Coordenadas(45.5,86.5),Coordenadas(141.5,88.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(45.5,86.5),Coordenadas(47.5,286.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(139.5,86.5),Coordenadas(141.5,286.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(45.5,284.5),Coordenadas(141.5,286.5),mapa.LINHA);
}


void FabricaDeMapas::mapaModulo2Teste(Mapa & mapa){
    mapa = Mapa(200, 200, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(200,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,198.5), Coordenadas(200,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(198.5,0), Coordenadas(200,200),mapa.PAREDE);

    // Area de inicio
    mapa.inserir_retangulo(Coordenadas(151,151),Coordenadas(198,198),2);

    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(150.5,198),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(198,150.5),mapa.LINHA);

    // Area de deposito 1
    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(41.5,66.5),3);

    // Linhas da area de deposito 1
    mapa.inserir_retangulo(Coordenadas(42,2),Coordenadas(44,198),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,67),Coordenadas(41.5,69),mapa.LINHA);

    // Area de deposito 2
    mapa.inserir_retangulo(Coordenadas(2,69.5),Coordenadas(41.5,132),4);

    // Linhas da area de deposito 2
    mapa.inserir_retangulo(Coordenadas(2,132.5),Coordenadas(41.5,134.5),mapa.LINHA);

    // Area de deposito 3
    mapa.inserir_retangulo(Coordenadas(2,135),Coordenadas(41.5,198),5);

    // Area de retirada 1
    mapa.inserir_retangulo(Coordenadas(159,2),Coordenadas(198,41.5),6);

    // Linhas da area de retirada 1
    mapa.inserir_retangulo(Coordenadas(156.5,2),Coordenadas(158.5,41.5),mapa.LINHA);

    // Area de retirada 2
    mapa.inserir_retangulo(Coordenadas(117.5,2),Coordenadas(156,41.5),7);

    // Linhas da area de retirada 2
    mapa.inserir_retangulo(Coordenadas(115,2),Coordenadas(117.5,41.5),mapa.LINHA);

    // Area de retirada 3
    mapa.inserir_retangulo(Coordenadas(75.5,2),Coordenadas(114.5,41.5),8);

    // Linhas da area de retirada 3
    mapa.inserir_retangulo(Coordenadas(73,2),Coordenadas(75,41.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(73,42),Coordenadas(198,44),mapa.LINHA);

}

void FabricaDeMapas::mapaModulo3Teste(Mapa & mapa){

    mapa = Mapa(200, 200, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(200,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,198.5), Coordenadas(200,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(198.5,0), Coordenadas(200,200),mapa.PAREDE);

    // Area de inicio
     mapa.inserir_retangulo(Coordenadas(151,77.5),Coordenadas(198,122.5),2);

    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(148.5,75),Coordenadas(198,77),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(148.5,75),Coordenadas(150.5,125),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(148.5,123),Coordenadas(198,125),mapa.LINHA);

    // Area de deposito 1
    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(41.5,66.5),3);

    // Linhas da area de deposito 1
    mapa.inserir_retangulo(Coordenadas(42,2),Coordenadas(44,198),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,67),Coordenadas(41.5,69),mapa.LINHA);

    // Area de deposito 2
    mapa.inserir_retangulo(Coordenadas(2,69.5),Coordenadas(41.5,132),4);

    // Linhas da area de deposito 2
    mapa.inserir_retangulo(Coordenadas(2,132.5),Coordenadas(41.5,134.5),mapa.LINHA);

    // Area de deposito 3
    mapa.inserir_retangulo(Coordenadas(2,135),Coordenadas(41.5,198),5);

     // Area intermediaria 1
     mapa.inserir_retangulo(Coordenadas(151,2),Coordenadas(198,49),6);

    // Linhas da area intermediaria 1
    mapa.inserir_retangulo(Coordenadas(148.5,2),Coordenadas(150.5,51.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(148.5,49.5),Coordenadas(198,51.5),mapa.LINHA);

    // Area intermediaria 2
    mapa.inserir_retangulo(Coordenadas(151,151),Coordenadas(198,198),7);

    // Linhas da area intermediaria 2
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(150.5,198),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(198,150.5),mapa.LINHA);



}

void FabricaDeMapas::mapaModulo1(Mapa & mapa){

    // Modulo 1 A ----------------------------------------------------------------------------------------------------------------------

    mapa = Mapa(200, 403, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(200,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,401.5), Coordenadas(200,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(198.5,0), Coordenadas(200,403),mapa.PAREDE);

    // Area central
    mapa.inserir_retangulo(Coordenadas(56.5,109.5),Coordenadas(145.5,295.5),2);

    // Linhas da area intermediaria 2
    mapa.inserir_retangulo(Coordenadas(50.5,103.5),Coordenadas(151.5,109),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(50.5,103.5),Coordenadas(56,301.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(146,103.5),Coordenadas(151.5,301.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(50.5,296),Coordenadas(151.5,301.5),mapa.LINHA);

    // Area inicial
    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(51,49.5),3);

    // Linhas da area intermediaria 2
    mapa.inserir_retangulo(Coordenadas(51.5,2),Coordenadas(56.5,49.5),mapa.LINHA);

    // Area despejo
    mapa.inserir_retangulo(Coordenadas(147,351.5),Coordenadas(198,401.5),4);

    // Linhas da area intermediaria 2
    mapa.inserir_retangulo(Coordenadas(141.5,351.5),Coordenadas(146.5,401.5),mapa.LINHA);

     // Modulo 1 B ----------------------------------------------------------------------------------------------------------------------
    /*
    mapa = Mapa(203, 403, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(203,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,401.5), Coordenadas(203,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(201.5,0), Coordenadas(203,403),mapa.PAREDE);
    */


}

void FabricaDeMapas::mapaModulo2(Mapa & mapa){

 // Modulo 2 A ----------------------------------------------------------------------------------------------------------------------

    mapa = Mapa(200, 403, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(200,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,401.5), Coordenadas(200,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(198.5,0), Coordenadas(200,403),mapa.PAREDE);

    // Area de inicio
    mapa.inserir_retangulo(Coordenadas(2,177),Coordenadas(51.5,226.5),2);

    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(2,171.5),Coordenadas(51.5,176.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,227),Coordenadas(51.5,232),mapa.LINHA);

    //Area de deposito 1
    mapa.inserir_retangulo(Coordenadas(119,2),Coordenadas(151.5,34.5),3);

    // Linhas da area de deposito 1
    mapa.inserir_retangulo(Coordenadas(36,35),Coordenadas(157,40),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(152,2),Coordenadas(157,40),mapa.LINHA);

    //Area de deposito 2
    mapa.inserir_retangulo(Coordenadas(80,2),Coordenadas(113,34.5),4);

    // Linhas da area de deposito 2
    mapa.inserir_retangulo(Coordenadas(113.5,2),Coordenadas(118.5,40),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(74.5,2),Coordenadas(79.5,40),mapa.LINHA);

    //Area de deposito 3
    mapa.inserir_retangulo(Coordenadas(41.5,2),Coordenadas(74,34.5),5);

    // Linhas da area de deposito 3
    mapa.inserir_retangulo(Coordenadas(35.5,2),Coordenadas(41,40),mapa.LINHA);

    // Area de retirada 1
    mapa.inserir_retangulo(Coordenadas(151.5,241.5),Coordenadas(198,290.5),6);

    // Linhas da area de retirada 1
   mapa.inserir_retangulo(Coordenadas(151.5,236),Coordenadas(198,241),mapa.LINHA);
   mapa.inserir_retangulo(Coordenadas(151.5,291),Coordenadas(198,296),mapa.LINHA);

    // Area de retirada 2
    mapa.inserir_retangulo(Coordenadas(151.5,296.5),Coordenadas(198,340.5),7);

    // Linhas da area de retirada 2
    mapa.inserir_retangulo(Coordenadas(151.5,341),Coordenadas(198,346),mapa.LINHA);

    // Area de retirada 3
    mapa.inserir_retangulo(Coordenadas(100.5,346.5),Coordenadas(150.5,401.5),8);

    // Linhas da area de retirada 3
    mapa.inserir_retangulo(Coordenadas(95,346.5),Coordenadas(100,401.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(151,346.5),Coordenadas(156,401.5),mapa.LINHA);



     // Modulo 2 B ----------------------------------------------------------------------------------------------------------------------
    /*
    mapa = Mapa(203, 403, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(203,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,401.5), Coordenadas(203,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(201.5,0), Coordenadas(203,403),mapa.PAREDE);
    */

}

void FabricaDeMapas::mapaModulo3(Mapa & mapa){

    mapa = Mapa(200, 403, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(200,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,401.5), Coordenadas(200,403),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(198.5,0), Coordenadas(200,403),mapa.PAREDE);

    // Area de inicio
     mapa.inserir_retangulo(Coordenadas(150.5,173.5),Coordenadas(198,222.5),2);

    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(150.5,168),Coordenadas(198,173),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(150.5,223),Coordenadas(198,228),mapa.LINHA);


      // Area de deposito 1
    mapa.inserir_retangulo(Coordenadas(2,56),Coordenadas(51,105.5),3);

    // Linhas da area de deposito 1
    mapa.inserir_retangulo(Coordenadas(51.5,50.5),Coordenadas(55.5,386),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,50.5),Coordenadas(51.5,55.5),mapa.LINHA);

    // Area de deposito 2
    mapa.inserir_retangulo(Coordenadas(2,111.5),Coordenadas(51,160.5),4);

    // Linhas da area de deposito 2
    mapa.inserir_retangulo(Coordenadas(2,106),Coordenadas(51.5,111),mapa.LINHA);

    // Area de deposito 3
    mapa.inserir_retangulo(Coordenadas(2,166.5),Coordenadas(51,215.5),5);

    // Linhas da area de deposito 3
    mapa.inserir_retangulo(Coordenadas(2,161),Coordenadas(51.5,166),mapa.LINHA);

        // Area de deposito 4
    mapa.inserir_retangulo(Coordenadas(2,221.5),Coordenadas(51,270.5),6);

    // Linhas da area de deposito 4
    mapa.inserir_retangulo(Coordenadas(2,216),Coordenadas(51.5,221),mapa.LINHA);

        // Area de deposito 5
    mapa.inserir_retangulo(Coordenadas(2,276.5),Coordenadas(51,325.5),7);

    // Linhas da area de deposito 5
    mapa.inserir_retangulo(Coordenadas(2,271),Coordenadas(51.5,276),mapa.LINHA);

        // Area de deposito 6
    mapa.inserir_retangulo(Coordenadas(2,331.5),Coordenadas(51,380.5),8);

     // Linhas da area de deposito 6
    mapa.inserir_retangulo(Coordenadas(2,326),Coordenadas(51.5,331),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,381),Coordenadas(51.5,386),mapa.LINHA);

    // Area Intermediaria
    mapa.inserir_retangulo(Coordenadas(87,2),Coordenadas(159,34),9);

    // Linhas da area de deposito 5
    mapa.inserir_retangulo(Coordenadas(81.5,2),Coordenadas(86.5,39.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(81.5, 34.5),Coordenadas(164.5,39.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(159.5,2),Coordenadas(164.5,39.5),mapa.LINHA);


}

/*void FabricaDeMapas::mapaModulo1BB(Mapa & mapa){
	//cout << "XABRAU";
    mapa = Mapa(200, 403, 0.5);
    // Paredes da arena
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(200,1.5),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,0), Coordenadas(1.5,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(0,198.5), Coordenadas(200,200),mapa.PAREDE);
    mapa.inserir_retangulo(Coordenadas(198.5,0), Coordenadas(200,200),mapa.PAREDE);

    // Area de inicio
    mapa.inserir_retangulo(Coordenadas(2,2),Coordenadas(48.5,48.5),2);

    // Linhas da area de inicio
    mapa.inserir_retangulo(Coordenadas(49.5,2),Coordenadas(51.5,51.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(2,49.5),Coordenadas(51.5,51.5),mapa.LINHA);

    // Area de deposito
    mapa.inserir_retangulo(Coordenadas(151,151),Coordenadas(198,198),3);

    // Linhas da area de deposito
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(150.5,198),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(148.5,148.5),Coordenadas(198,150.5),mapa.LINHA);

    // Area central
    mapa.inserir_retangulo(Coordenadas(79,69),Coordenadas(122.5,132.5),4);

    // Linhas da area central
    mapa.inserir_retangulo(Coordenadas(76.5,66.5),Coordenadas(125,68.5),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(123,66.5),Coordenadas(125,135),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(76.5,66.5),Coordenadas(78.5,135),mapa.LINHA);
    mapa.inserir_retangulo(Coordenadas(76.5,133),Coordenadas(125,135),mapa.LINHA);
}*/
