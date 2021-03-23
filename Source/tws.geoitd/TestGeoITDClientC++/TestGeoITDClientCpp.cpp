// TestGeoITDClientC++.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <Windows.h>

typedef void(*PURCHASE)(IN  char* /*ip_*/,				IN  int   /*port_*/,
						IN  char* /*pos_id_*/,			IN  char* /*system_id_*/,			IN  char* /*branch_*/,
						IN  char* /*client_app_id_*/,	IN  char* /*user_id_*/,				IN  char* /*amount_*/,
						IN  int   /*installment_*/,		IN  int   /*plan_*/,				IN  char* /*currency_*/,
						IN  int   /*tax_refund_*/,		IN  char* /*taxable_amount_*/,		IN  char* /*invocie_amount_*/,
						IN  char* /*tip_amount_*/,		IN  char* /*invoice_number_*/,      IN  char* /*transaction_datetime_*/,
						OUT int*  /*response_code_*/,	OUT char* /*transaction_id_*/,		OUT char* /*res_*/);

typedef void (*QUERYSTATUS)(IN char*  /*ip_*/,					IN int   /*port_*/,
							IN char*  /*pos_id_*/,				IN char* /*system_id_*/,			IN char* /*branch_*/,
							IN char*  /*client_app_id_*/,		IN char* /*user_id_*/,				IN char* /*transaction_id_*/,
							IN bool   /*noWait_*/,              IN OUT char*  /*transaction_datetime_*/,
							OUT int*  /*response_code_*/,		OUT char* /*pos_response_code_*/,	OUT char* /*pos_response_code_ext_*/,
							OUT char* /*ticket_*/,				OUT char* /*authorization_code_*/,	OUT int*  /*issuer_*/,
							OUT char* /*card_number_*/,			OUT char* /*expiration_date_*/,		OUT char* /*res_*/);


int main()
{
    std::cout << "Hello World!\n";



    HMODULE hMod = LoadLibrary(L"TWS.RES.GeoITDClientW32.dll");
	PURCHASE purchase = (PURCHASE)GetProcAddress(hMod, "Purchase");
	QUERYSTATUS query = (QUERYSTATUS)GetProcAddress(hMod, "QueryStatus");

	int response_code_;
	char pos_response_code_[128];
	char pos_response_code_ext_[128];
	char transaction_id_[128];
	char ticket_[128];
	char authorization_code_[128];
	int issuer_;
	char card_number_[128];
	char expiration_date_[128];
	char transaction_datetime_[128];
	char res_;
	
	purchase((char*)"127.0.0.1", 7511,
        (char*)"43113460",	(char*)"F3D5877B-3C08-488C-BE97-907444042490", (char*)"TWS LOCAL 1",
        (char*)"WS 001",	(char*)"LUIS",	(char*)"12200",
        1,					0,				(char*)"858",
        0,					(char*)"10000", (char*)"12200",
        (char*)"0.00",		(char*)"", (char*)"20210319170000000",
		&response_code_,	transaction_id_,
		&res_);



	strcpy_s(transaction_datetime_, "20210319170000000");

	query((char*)"127.0.0.1", 7511,
		(char*)"43113460", (char*)"F3D5877B-3C08-488C-BE97-907444042490", (char*)"LOCAL 1",
		(char*)"WS 001", (char*)"LUIS", transaction_id_, false, transaction_datetime_,
		&response_code_, pos_response_code_, pos_response_code_ext_,
		ticket_, authorization_code_, &issuer_,
		card_number_, expiration_date_, &res_);
	 

}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
