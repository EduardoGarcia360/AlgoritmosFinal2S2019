#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

/***********************************************
				A G R E G A R
***********************************************/
//AGREGA UN ALUMNO AL ARCHIVO ABIERTO
void agregarAlumno (FILE * archivo) {
	system("cls");
	cout<<"***** Bienvenido a la opcion de agregar ***** "<<endl;
	char carnet[20]="", nombre[35]="", seccion[20]="";
	string otro = "s";
	while (otro == "s"){
		cout<<"ingrese el carnet"<<endl;
		cin.getline(carnet, 20);
		cout<<"ingrese el nombre"<<endl;
		cin.getline(nombre, 35);
		cout<<"ingrese la seccion"<<endl;
		cin.getline(seccion, 20);
		fprintf(archivo, " %s; %s; %s\n", carnet, nombre, seccion);
		cout<<"desea agregar otro? (s/n)"<<endl;
		cin>>otro;
		cin.ignore();
	}
}

//AGREGA UN LIBRO AL ARCHIVO ABIERTO
void agregarLibro (FILE * archivo) {
	system("cls");
	cout<<"***** Bienvenido a la opcion de agregar *****  "<<endl;
	char nombre[35]="", autor[35]="", editorial[35]="",prestado[35]="";
	string otro = "s";
	while (otro == "s"){
		cout<<"ingrese el nombre"<<endl;
		cin.getline(nombre, 35);
		cout<<"ingrese el autor"<<endl;
		cin.getline(autor, 35);
		cout<<"ingrese la editorial"<<endl;
		cin.getline(editorial, 35);
		cout<<"el libro en que estado esta(prestado o libre)?"<<endl;
		cin.getline(prestado, 35);
	
		
		fprintf(archivo, " %s; %s;  %s;  %s\n", nombre, autor, editorial,prestado);
		cout<<"desea agregar otro? (s/n)"<<endl;
		cin>>otro;
		cin.ignore();
	}
}

//DEL MENU DE GESTION SI ELIGE AGREGAR PASA A ESTE METODO
//QUE RECIBE EL NOMBRE DEL ARCHIVO FISICO Y CUAL FUE LA
//ELECCION DEL CONTROL AL QUE SE QUERIA ACCEDER.
void agregar (string nombreArchivo, string control) {
	
	//SE CREA UN ARCHIVO CON EL NOMBRE QUE VENGA EN EL PARAMETRO
	FILE * archivo = fopen(nombreArchivo.c_str(), "a+");
	
	if(archivo != NULL){
		//USANDO EL ARCHIVO CREADO PODEMOS PARTIR A AGREGAR
		//ALUMNOS O LIBROS CON ESTA VALIDACION
		if (control == "ALUMNOS"){
			agregarAlumno(archivo);
		}else{
			agregarLibro(archivo);
		}
		
		//AL FINALIZAR EL CICLO DENTRO DE LOS METODOS ANTERIORES
		//SE CIERRA EL ARCHIVO ABIERTO.
		fclose(archivo);
	}
}

/***********************************************
				M O S T R A R
***********************************************/
//MOSTRAR CONTENIDO DEL ARCHIVO SEPARANDOLO POR PARTES
void analizarLinea (char linea[], int noLinea) {
	char * token = strtok(linea, ";");
	cout<<noLinea<<".- ";
	while (token != NULL){
		cout<<token<<" ";
		token = strtok(NULL, ";");
	}
	cout<<"\n";
}

//LEE LINEA POR LINEA EL ARCHIVO
void mostrarDatos (FILE * archivo) {
	system("cls");

	
	char lineaTmp[1000]="", linea[1000]="";
	int noLinea = 1;
	cout<<"No."<<endl;
	cout<<"Linea.- Registro"<<endl;
	while(feof(archivo) == 0){
		//LECTURA DE LINEA DEL ARCHIVO AL FINAL DE LA LINEA TIENE UN "SALTO DE LINEA (\n)"
		fgets(lineaTmp, 1000, archivo);
		//SE QUITA EL "SALTO DE LINEA (\n)" PARA DEJAR SOLO LA LINEA NORMAL
		char* lineaSinSalto = strtok(lineaTmp, "\n");
		//SE PASA LA LINEA SIN SALTO AL METODO ANALIZAR LINEA PARA QUE SE MUESTRE
		strcpy(linea, lineaSinSalto);
		if(feof(archivo) == 0){
			
			analizarLinea(linea, noLinea);
			noLinea += 1;
	
		}
	}
}

//DEL MENU DE GESTION SE USA PARA MOSTRAR EL CONTENIDO DEL ARCHIVO
void mostrar (string nombreArchivo) {
	system("cls");
	cout<<"***** Bienvenido a la opcion de visualizar ***** "<<endl;
	FILE * archivo = fopen(nombreArchivo.c_str(), "a+");
	if(archivo != NULL){
	
		mostrarDatos(archivo);
		fclose(archivo);
	}
}

/***********************************************
				E L I M I N A R
***********************************************/
//CON LA LINEA A ELIMINAR ELEGIDA POR EL USUARIO SE PROCEDE
//A REMOVERLA DEL ARCHIVO ORIGEN
void procesoEliminar (int lineaEliminar, string nombreArchivoIn){
	cout<<"***** Bienvenido a la opcion de eliminar ***** "<<endl;
	
	FILE * archivoEntrada = fopen(nombreArchivoIn.c_str(), "a+");
	if(archivoEntrada == NULL){
		cout<<"No se ha podido abrir el archivo: "<<nombreArchivoIn<<endl;
		return;
	}
	string rutaArchivoTmp = "C:/Users/Samsung/Documents/GitHub/Nueva carpeta/AlgoritmosFinal2S2019/temp.txt";
	FILE * archivoTmp = fopen(rutaArchivoTmp.c_str(), "a+");
	if (archivoTmp == NULL){
		cout<<"No se ha podido abrir el archivo temporal"<<endl;
		return;
	}
	
	char lineaArchivoInTmp[1000]="", lineaArchivoIn[1000]="";
	int noLineaArchivoIn = 1;
	
	while(fgets(lineaArchivoInTmp, 1000, archivoEntrada)){
		fputs(lineaArchivoInTmp, stdout);
		//SE QUITA EL "SALTO DE LINEA (\n)" PARA DEJAR SOLO LA LINEA NORMAL
		char* lineaSinSalto = strtok(lineaArchivoInTmp, "\n");
		//SE PASA LA LINEA SIN SALTO AL METODO ANALIZAR LINEA PARA QUE SE MUESTRE
		strcpy(lineaArchivoIn, lineaSinSalto);
		
		//CON EL CONTADOR DE LINEA DEL ARCHIVO DE ENTRADA
		//SE COMPARA QUE NO SEA IGUAL A LA LINEA LEIDA
		//DEL ARCHIVO ABIERTO
		if(noLineaArchivoIn != lineaEliminar){
			fprintf(archivoTmp, "%s\n", lineaArchivoIn);
		}
		
		if(feof(archivoEntrada) == 0){
			noLineaArchivoIn += 1;
		}
	}
	fclose(archivoEntrada);
	fclose(archivoTmp);
	remove(nombreArchivoIn.c_str());
	rename("temp.txt", nombreArchivoIn.c_str());
}

//SE LE PRESENTA AL USUARIO LOS DATOS ALMACENADOS EN EL ARCHIVO
//EL USUARIO ELIGE QUE LINEA BORRAR
void eliminar (string nombreArchivo) {
	system("cls");
	cout<<"***** Bienvenido a la opcion de eliminar ***** "<<endl;
	FILE * archivo = fopen(nombreArchivo.c_str(), "a+");
	if(archivo != NULL){
		int linea;
		mostrarDatos(archivo);
		fclose(archivo);
		cout<<"elija la linea a borrar:"<<endl;
		cin>>linea;
		procesoEliminar(linea, nombreArchivo);
	}
}

/***********************************************
				B U S C A R
***********************************************/
void buscarEnLinea (char linea[], char busqueda[]) {
	char * token = strtok(linea, ";");
	while (token != NULL){
		if(strcmp(token, busqueda) == 0){
			cout<<"valor encontrado"<<endl;
		}
		token = strtok(NULL, ";");
	}
}

void buscar (string nombreArchivo) {
	system("cls");
	cout<<"***** Bienvenido a la opcion de buscar ***** "<<endl;
	char busqueda[20] = "";
	cout<<"ingrese una palabra para buscar:"<<endl;
	cin.getline(busqueda, 20);
	FILE * archivo = fopen(nombreArchivo.c_str(), "a+");
	if (archivo == NULL){
		cout<<"No se ha podido abrir el archivo: "<<nombreArchivo<<endl;
		return;
	}
	
	char linea[1000]="", lineaTmp[1000]="";
	while(feof(archivo) == 0){
		fgets(lineaTmp, 1000, archivo);
		//SE QUITA EL "SALTO DE LINEA (\n)" PARA DEJAR SOLO LA LINEA NORMAL
		char* lineaSinSalto = strtok(lineaTmp, "\n");
		//SE PASA LA LINEA SIN SALTO AL METODO ANALIZAR LINEA PARA QUE SE MUESTRE
		strcpy(linea, lineaSinSalto);
		buscarEnLinea(linea, busqueda);
	}
	cin.ignore();
	fclose(archivo);
}

/***********************************************
		M E N U S D E G E S T I O N
***********************************************/
//MENU DE GESTION PARA ALUMNOS O PARA BIBLIOTECA
void menuGestion (string control, string nombreArchivo){
	int menu=0;
	system("cls");
	
	while (menu != 6){
		cout<<"***** MENU DE CONTROL DE "<<control<<" *****"<<endl;
		cout<<"Que desea hacer?"<<endl;
		cout<<"1. Agregar\n2. Buscar\n3. Eliminar\n4. Modificar\n5. Mostrar\n6. Regresar al menu principal"<<endl;
		cin>>menu;
		cin.ignore();
		if(menu==1){
			
			agregar(nombreArchivo, control);
		}else if(menu==2){
			
			buscar(nombreArchivo);
		}else if(menu==3){
			
			eliminar(nombreArchivo);
		}else if(menu==5){
				
			mostrar(nombreArchivo);
		}
	}
}

//MENU PRINCIPAL DEL CUAL SE PUEDE ELEGIR SI ACCEDER A ALUMNOS O A BIBLIOTECA
int main () {
	int opcion = 0;
	system("cls");
	
	while (opcion != 3){
		cout<<"1. Ingresar al control de alumnos\n2. Ingresar al control biblioteca\n3. Salir"<<endl;
		cin>>opcion;
		cin.ignore();
		if(opcion == 1){
			menuGestion("ALUMNOS", "datosALUMNOS.txt");
		}else if (opcion == 2){
			menuGestion("BIBLIOTECA", "datosBIBLIOTECA.txt");
		}
	}
	cout<<"eduardo garcia"<<endl;
	cout<<"brian duarte"<<endl;
	cout<<"Marcelo Samayoa"<<endl;
}
