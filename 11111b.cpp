#include<iostream>
#include<stdio.h>
#include<stack>
#include<string>
using namespace std;
string cadena;

int conversor(bool positivo,int posicion)
{
	int numero=0;
	while(cadena[posicion]>47 and cadena[posicion]<58)
	{
		numero=(numero*10)+(cadena[posicion]-48);
		posicion++;
	}
	if(positivo)
		return numero;
	else
		return -1*numero;
}

void imprimir_carrito(stack <int> carrito)
{
	//cout<<"carrito"<<endl;
	while(!carrito.empty())
	{
		cout<<carrito.top()<<" ";
		carrito.pop();
	}
	cout<<endl;
}

int main()
{
	int numero;
	while(getline(cin,cadena))
	{
		//cout<<cadena<<endl;
		int n=cadena.length();
		//cout<<n<<" "<<cadena[cadena.size()-1]<<endl;
		if(cadena[cadena.size()-1]<47 or cadena[cadena.size()-1]>58)
			cadena.pop_back();
		n=cadena.length();
		
		stack <int> pila1;
   		stack <pair<int,int>> pila2;
		bool valido;
		int number;
		for(int i=0;i<n;i++)
		{
			//leemos caracter y lo convertimos a numero
			valido=true;
			if(cadena[i]=='-')
			{
				i++;
				numero=conversor(0,i);
				while(cadena[i]>47 and cadena[i]<58)
					i++;
			}
			else if(cadena[i]>47 and cadena[i]<58)
			{
				numero=conversor(1,i);
				while(cadena[i]>47 and cadena[i]<58)
					i++;
			}
			else if(cadena[i]==' ')
				valido=false;

			//ingresamos el numero a la pila correspondiente
			if(valido)
				pila1.push(numero);
		}

		
		//manipulammos pilas
//		cout<<"Negativos"<<endl; imprimir_carrito(negativos);
//		cout<<"positivos"<<endl;imprimir_carrito(positivos);
//		cout<<"Auxiliar"<<endl;imprimir_carrito(aux);
		bool hubo_cambios=true;
		int aux;
		while(hubo_cambios)
		{
	      if(!pila1.empty() and pila1.top()>0)
	      {
	         //checamos si cabe en pila 2

	         //si pila2 está vacía
	         if(pila2.empty())
	         {
	            pair<int,int>par;
	            par.first=pila1.top();
	            par.second=0;
	            pila2.push(par);
	            pila1.pop();
	         }
	         else if(pila1.top()+pila2.top().second < pila2.top().first)
	         {
	            pair<int,int>par;
	            //modificamos suma en el ultimo elementos de pila 2
	            par=pila2.top();
	            pila2.pop();
	            par.second+=pila1.top();
	            pila2.push(par);
	            //borramos al elemento en pila1 y lo agregamos a pila2
	            par.first=pila1.top();
	            par.second=0;
	            pila2.push(par);
	            pila1.pop();
	         }
	         else
	            hubo_cambios=false;
	      }
	      else if(!pila1.empty() and pila1.top()<0 and !pila2.empty() and pila1.top()*-1==pila2.top().first)
	      {
	         pila1.pop();
	         pila2.pop();
	      }
	      else
	         hubo_cambios=false;
	   }

		if(pila1.empty() and pila2.empty())
			cout<<":-) Matrioshka!"<<endl;
		else
			cout<<":-( Try again."<<endl;
	}
	return 0;
}
