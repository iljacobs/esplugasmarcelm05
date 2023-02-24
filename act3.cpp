#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include <ctime> // time function for seed value
#include <chrono>
#include <thread>
using namespace std;

struct carta
{
	int numero;
	string palo;
};
struct carta mano[52], manoMaquina[52];
struct carta baraja[52];
void mostrarmano(struct carta vc[], int *puntos, int contadorAs, int *num_cartas_mano, int contadorMano);
void mirarpuntuacion(int puntos, int *repetir);
void sotacaballo(struct carta vc[], int contadorBaraja);
int main()
{
  time_t t;
  srand((unsigned) time(&t));
	int numeros[13] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
	const string palos[4] = { "Corazones", "Diamantes", "Picas", "Treboles" };
	int contador = 0; 
	for ( int i = 0; i < 13; i++){
		for ( int j = 0; j < 4; j++){
			baraja[contador].numero = numeros[i];
			baraja[contador].palo = palos[j];
			contador++;
		}
	}
  int opcion;
  bool repetir = true;  
  int boolnum = 1;
  int num_cartas_mano, carta_mano_maquina, puntos, contadorAs, puntosMaquina, turno = 0, contadorMano = 0;

  for (int contadorBaraja = 0; contadorBaraja < 2; contadorBaraja++)
  {
    mano[contadorBaraja] = baraja[rand()%52];
  }
  do {
        cout << "\033[1;31m \n\nMenu de Opciones \033[0m" << endl;
        cout << "\033[1;32m 1. Robar carta \033[0m" << endl;
        cout << "\033[1;32m 2. Mostrar mano \033[0m" << endl;
        cout << "\033[1;32m 3. Plantarse \033[0m" << endl;
        cout << "\033[1;32m 4. Ver baraja \033[0m" << endl;
        cout << "\033[1;32m 0. SALIR \033[0m" << endl;
        
        if (turno == 0)
        {
          cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
          puntos = 0;
          contadorAs = 0;
          for (int contadorMano = 0; contadorMano < 52; contadorMano++){
            mostrarmano(mano, &puntos, contadorAs, &num_cartas_mano, contadorMano);
          }
          
          mirarpuntuacion(puntos, &boolnum);
          if(boolnum == 0)
          {
            repetir = false;
            break;
          }
        } 
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        turno++;

        switch (opcion) {
            case 1:
                mano[num_cartas_mano+1] = baraja[rand()%52];                
                cout << "\033[1;32mTu carta es: \033[0m" << endl;

                contadorMano = num_cartas_mano + 1;
                mostrarmano(mano, &puntos, contadorAs, &num_cartas_mano, contadorMano);

                mirarpuntuacion(puntos, &boolnum);
                if(boolnum == 0)
                {
                  repetir = false;
                }
                break;
            case 2:
                // system("clear");               
                cout << "\033[1;31m \nTus cartas son: \033[0m" << endl;
                puntos = 0;
                contadorAs = 0;
                for (int contadorMano = 0; contadorMano < 52; contadorMano++){
                  mostrarmano(mano, &puntos, contadorAs, &num_cartas_mano, contadorMano);
                }
                cout << "\033[1;32mTienes " << puntos <<" puntos \033[0m" << endl;
                break;
            case 3:
            	// system("clear");               
                cout << "\033[1;32mHas conseguido " << puntos << " puntos \033[0m" << endl;
                cout << "\033[1;36mAhora juega la máquina\033[0m" << endl;
                while(puntosMaquina < puntos){
                  cout << "\033[1;36mLa maquina roba carta\033[0m" << endl;
                  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                  manoMaquina[carta_mano_maquina] = baraja[rand()%52];
                  sotacaballo(manoMaquina, carta_mano_maquina);
                  puntosMaquina = puntosMaquina + manoMaquina[carta_mano_maquina].numero;
                  cout << "\033[1;37m Puntos maquina: " << puntosMaquina << endl;
                  carta_mano_maquina++;
                }
                if (puntosMaquina > 21){
                  cout << "\033[1;31mLa máquina se ha pasado\033[0m" << endl;
                  cout << "\033[1;33mFELICIDADES, HAS GANADO!\033[0m" << endl;
                } else if (puntosMaquina == puntos){
                  cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
                  cout << "\033[1;33mEmpate\033[0m" << endl;
                } else {
                  cout << "\033[1;33mLa máquina se planta\033[0m" << endl;
                  cout << "\033[1;31mHas perdido...\033[0m" << endl;
                }
                cout << "\033[1;35mTu has conseguido " << puntos << " puntos y la máquina " << puntosMaquina << " puntos\033[0m" << endl;
                repetir = false;            
                break;
            case 4:
              for (int contadorBaraja = 0; contadorBaraja < 52; contadorBaraja++){
                sotacaballo(baraja, contadorBaraja);
              }
              break;
            case 0:
            	repetir = false;
            	break;
        }        
    } while (repetir);
		return 0;
}
void mostrarmano(struct carta vc[], int *puntos, int contadorAs, int *num_cartas_mano, int contadorMano)
{
      if (vc[contadorMano].palo != ""){
      if( vc[contadorMano].numero == 1){
        cout <<  "\033[1;33m A de " << vc[contadorMano].palo << "\033[0m" << endl;
        contadorAs++;
        if (contadorAs >= 1 && *puntos + 11 > 21){
          *puntos = *puntos + 1;
        } else {
          *puntos = *puntos + 11;
        }
        *num_cartas_mano = *num_cartas_mano + 1;
      } else if (vc[contadorMano].numero == 11){
        cout <<  "\033[1;33m Sota de " << vc[contadorMano].palo << "\033[0m"<< endl;
        *puntos = *puntos + 10;
        *num_cartas_mano = *num_cartas_mano + 1;
      } else if (vc[contadorMano].numero == 12){
        cout <<  "\033[1;33m Caballo de " << vc[contadorMano].palo << "\033[0m" << endl;
        *puntos = *puntos + 10;
        *num_cartas_mano = *num_cartas_mano + 1;
      } else if (vc[contadorMano].numero == 13){
        cout <<  "\033[1;33m Rey de " << vc[contadorMano].palo << "\033[0m" << endl;
        *puntos = *puntos + 10;
        *num_cartas_mano = *num_cartas_mano + 1;
      } else {
        cout << "\033[1;33m "<< vc[contadorMano].numero << " de " << vc[contadorMano].palo << "\033[0m" << endl;
        *puntos = *puntos + vc[contadorMano].numero;
        *num_cartas_mano = *num_cartas_mano + 1;
      }
    }
}
void mirarpuntuacion(int puntos, int *repetir)
{
  if (puntos > 21){
            cout << "\033[1;31mTe has pasado... puntos: " << puntos << "\033[0m" << endl;
            cout << "\033[1;31mHas perdido\033[0m" << endl;
            *repetir = 0;
          } else if (puntos == 21){ 
            cout << "\033[1;33mFELICIDADES tienes " << puntos <<  " puntos!(Blackjack)\033[0m" << endl;
            *repetir = 0;
          } else {
            cout << "\033[1;32mTienes " << puntos <<" puntos \033[0m" << endl;
          }
}
void sotacaballo(struct carta vc[], int contadorBaraja)
{
  if( vc[contadorBaraja].numero == 1){
    cout <<  "A de " << vc[contadorBaraja].palo << endl;
  } else if (vc[contadorBaraja].numero == 11){
    cout <<  "Sota de " << vc[contadorBaraja].palo << endl;
  } else if (vc[contadorBaraja].numero == 12){
    cout <<  "Caballo de " << vc[contadorBaraja].palo << endl;
  } else if (vc[contadorBaraja].numero == 13){
    cout <<  "Rey de " << vc[contadorBaraja].palo << endl;
  } else {
    cout << vc[contadorBaraja].numero << " de " << vc[contadorBaraja].palo << endl;
  }
}