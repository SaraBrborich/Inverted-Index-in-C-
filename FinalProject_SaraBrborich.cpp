// FinalProject_SaraBrborich.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <unordered_set>
#include <set>
using namespace std;

int main() {

	// Preguntar el nombre del archivo de texto que se va a leer.
	string file_name;
	cout << "Ingrese el nombre del archivo para analizar: ";
	cin >> file_name;

	// Abrir el archivo para analizar.
	ifstream infile(file_name);

	// Si el archivo no se pudo abrir para analizar.
	if (!infile.is_open())
	{
		cout << "No se pudo abrir el archivo de nombre " << file_name << endl;
		return 1;
	}

	// Crear una lista para las palabras de excepcion.
	unordered_set<string> lista_palabras_excepcion;
	string exception_file_name;
	cout << "Ingrese el nombre del archivo de palabras de excepcion: ";
	cin >> exception_file_name;

	// Abrir el archivo de excepciones para analizar.
	ifstream exception_file(exception_file_name);

	// Si el archivo no se pudo abrir.
	if (!exception_file.is_open())
	{
		cout << "El archivo " << exception_file_name << " no se pudo abrir.";
		return 1;
	}

	// Agregar las palabras de excepcion a una lista para luego comparar ambos.	
	string palabras_excepcion;

	while (getline(exception_file, palabras_excepcion,','))
	{
		// Convertir las palabras a minusculas.
		transform(palabras_excepcion.begin(), palabras_excepcion.end(), palabras_excepcion.begin(), ::tolower);

		// Elimiar caracteres especiales.
		vector<char>caracteres_especiales_a_eliminar = { ' ',',','.',':',';','\n' };
		for (auto& c : caracteres_especiales_a_eliminar)
		{
			palabras_excepcion.erase(remove(palabras_excepcion.begin(), palabras_excepcion.end(), c), palabras_excepcion.end());
		}

		lista_palabras_excepcion.insert(palabras_excepcion);
	}


	// Leer el otro archivo a analizar linea por linea.
	string linea;
	int numero_de_linea = 0;

	// Creacion del indice invertido de palabras.
	// Cada palabra (string) es la clave, list guarda en pares la linea y posicion de la clave.
	map<string, list<pair<int, int>>> indice_invertido;

	while (getline(infile, linea))
	{
		numero_de_linea++;
		stringstream ss(linea);  // Leer el string como si fuera un stream. 

		string palabras;
		int numero_de_palabra = 0;

		while (ss >> palabras)
		{
			numero_de_palabra++;

			// Convertir palabra a minúsculas.
			transform(palabras.begin(), palabras.end(), palabras.begin(), ::tolower);

			// Elimiar caracteres especiales.
			vector<char>caracteres_especiales_a_eliminar = { ' ',',','.',':',';','"', '(', ')','*', '=', '+', '&','$', '%', '^','-', '<', '>', '[',']','/','{','}'};
			for (auto& c : caracteres_especiales_a_eliminar)
			{
				palabras.erase(remove(palabras.begin(), palabras.end(), c), palabras.end());
			}

			// Verificar si la palabra esta en la lista de excepciones.
			if (lista_palabras_excepcion.find(palabras) != lista_palabras_excepcion.end())
			{
				continue;
			}
			else
			{
				indice_invertido[palabras].push_back(make_pair(numero_de_linea, numero_de_palabra));
			}
		}
	}


	// Crear el archivo de salida del indice invertido.
	string archivo_de_salida = "Indice_Invertido_Sara_Brborich.txt";
	ofstream outfile(archivo_de_salida);
	if (!outfile.is_open())
	{
		cout << "No se pudo generar el archivo de salida con nombre " << archivo_de_salida;
		return 1;
	}

		
	// Mostrar el indice de palabras sin las palabras de excepcion.
	outfile << "Indice de palabras: " << endl;
	for (auto it = indice_invertido.begin(); it != indice_invertido.end(); it++)
	{
		outfile << it->first << ":";

		for (auto posicion = it->second.begin(); posicion != it->second.end(); posicion++)
		{
			outfile << " (" << posicion->first << "," << posicion->second << ")";
		}
		outfile << endl;
	}

	// Cerrar el archivo generado.
	outfile.close();



	// Preguntar al usuario la palabra que quiere buscar y mostrar su informacion.
	string palabra_usuario;
	cout << "\nIngrese una palabra para mostrar su informacion: ";
	cin >> palabra_usuario;

	// Eliminar posibles caracteres no deseados.
	vector<char>caracteres_especiales_a_eliminar = { ' ',',','.',':',';' };
	for (auto& c : caracteres_especiales_a_eliminar)
	{
		palabra_usuario.erase(remove(palabra_usuario.begin(), palabra_usuario.end(), c), palabra_usuario.end());
	}

	// Verificar que la palabra este en el indice.
	auto it = indice_invertido.find(palabra_usuario);
	if (it != indice_invertido.end())
	{
		cout << it->first << ":";
		for (auto& informacion : it->second)
		{
			cout << " (" << informacion.first << "," << informacion.second << ")";
		}
	}
	else
	{
		cout << "La palabra " << palabra_usuario << " no se encontro en el archivo";
	}


	// Preguntar al usuario grupos de palabras e imprimir las lineas donde se encuentran.
	string grupo_palabras_usuario;
	cout << "\n\nIngrese un grupo de palabras separadas por espacios para mostrar su informacion: ";
	cin.ignore();
	getline(cin, grupo_palabras_usuario);

	// Separar el grupo de palabras en palabras individuales.
	stringstream ss(grupo_palabras_usuario);
	string palabra_individual;

	// Lista para almacenar todas las palabras ingresadas por el usuario.
	vector<string> palabras_a_buscar;
	while (ss >> palabra_individual) 
	{
		palabras_a_buscar.push_back(palabra_individual);
	}
	
	bool todas_encontradas = false;

	// Mostrar la informacion de las palabras ingresadas.
	cout <<"\nInformacion: \n";
	for (const auto& palabra_usuario : palabras_a_buscar) 	{
		
		// Verificar que la palabra este en el indice invertido.		
		if (indice_invertido.count(palabra_usuario)!=0)
		{
			cout << "Linea(s) donde '" << palabra_usuario << "' se encuentra: ";
			// Se encontro la palabra.
			for (const auto& informacion : indice_invertido[palabra_usuario])
			{
				cout << informacion.second << " ";
			}
			cout << endl;
			todas_encontradas = true;
		}
		else 
		{
			// No se encontro la palabra.
			cout << "La palabra '" << palabra_usuario << "' no se encontro en el archivo\n";
		}

	}

	// Cerrar el archivo de texto.
	infile.close();
	exception_file.close();
	return 0;
}