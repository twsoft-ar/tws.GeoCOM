#ifndef __TWS_RES_MPQMCLIENT_H
#define __TWS_RES_MPQMCLIENT_H


#if defined(TWSRESGEOITDCLIENT_EXPORTS)
#define TWSRESGEOITDCLIENT_API __declspec(dllexport)
#elif defined(TWSRESGEOITDCLIENT_IMPORT)
#define TWSRESGEOITDCLIENT_API __declspec(dllimport)
#else
#define TWSRESGEOITDCLIENT_API
#endif

#define IN
#define OUT
#define INOUT


// Define here all exportable functions to be called by micros SIM script
/*TWSRESGEOITDCLIENT_API void Purchase(IN  char* ip_,     IN  int   port_,
 									 IN  char* pos_id_,               IN  char* system_id_,         IN  char* branch_,
 									 IN  char* client_app_id_,        IN  char* user_id_,           IN  char* amount_,
 									 IN  int   installment_,          IN  int   plan_,              IN  char* currency_,
									 IN  int   tax_refund_,           IN  char* taxable_amount_,    IN  char* invocie_amount_,
									 IN  char* tip_amount_,           IN  char* invoice_number_,
									 OUT int*  response_code_,        OUT char* pos_response_code_, OUT char* pos_response_code_ext_,
									 OUT char* transaction_id_,       OUT char* ticket_,            OUT char* authorization_code_,
									 OUT int*  issuer_,               OUT char* card_number_,       OUT char* expiration_date_,
									 OUT char* transaction_datetime_,
									 OUT char* res_);
*/

TWSRESGEOITDCLIENT_API void Purchase(IN  char* ip_,                 IN  int   port_,            
									 IN  char* pos_id_,             IN  char* system_id_,         IN  char* branch_,
									 IN  char* client_app_id_,      IN  char* user_id_,           IN  char* amount_,
									 IN  int   installment_,        IN  int   plan_,              IN  char* currency_, 
									 IN  int   tax_refund_,         IN  char* taxable_amount_,    IN  char* invocie_amount_,
									 IN  char* tip_amount_,         IN  char* invoice_number_,    IN  char* transaction_datetime_,
									 OUT int*  response_code_,      OUT char* transaction_id_,    OUT char* res_);

typedef void(*PURCHASE)(IN  char* /*ip_*/,				IN  int   /*port_*/,
						IN  char* /*pos_id_*/,			IN  char* /*system_id_*/,		IN  char* /*branch_*/,
						IN  char* /*client_app_id_*/,	IN  char* /*user_id_*/,			IN  char* /*amount_*/,
						IN  int   /*installment_*/,		IN  int   /*plan_*/,			IN  char* /*currency_*/,
						IN  int   /*tax_refund_*/,		IN  char* /*taxable_amount_*/,	IN  char* /*invocie_amount_*/,
						IN  char* /*tip_amount_*/,		IN  char* /*invoice_number_*/,  IN  char* /*transaction_datetime_*/,
						OUT int*  /*response_code_*/,	OUT char* /*transaction_id_*/,	OUT char* /*res_*/);

TWSRESGEOITDCLIENT_API void QueryStatus(IN char* ip_,					IN int   port_,
										IN char* pos_id_,				IN char* system_id_,				IN char* branch_,
										IN char* client_app_id_,		IN char* user_id_,					IN char* transaction_id_,
										IN bool  noWait_,				IN char* transaction_datetime_,		IN int   queryResponseSize_,
										OUT int* response_code_,		OUT char* pos_response_code_,		OUT char* pos_response_code_ext_,
										OUT char* purchaseQueryResponse_,
										OUT char* res_);

/*
										IN OUT char* transaction_datetime_,
										OUT int* response_code_,		OUT char* pos_response_code_,		OUT char* pos_response_code_ext_,
										OUT char* ticket_,				OUT char* authorization_code_,		OUT int*  issuer_, 
										OUT char* card_number_,			OUT char* expiration_date_,			OUT int*  origin_card_type_,
										OUT char* transaction_type_,	OUT char* batch_,					OUT int*  acquirer_,
										OUT char* EMV_application_id_,	OUT char* EMV_application_name_,	OUT char* res_);
*/

typedef void (*QUERYSTATUS)(IN  char* /*ip_*/,                	IN  int   /*port_*/,
							IN  char* /*pos_id_*/,            	IN  char* /*system_id_*/,				IN  char* /*branch_*/,
							IN  char* /*client_app_id_*/,     	IN  char* /*user_id_*/,					IN  char* /*transaction_id_*/,
							IN  bool  /*noWait_*/,				IN  char* /*transaction_datetime_*/,	IN  int   /*queryResponseSize_*/,
							OUT int*  /*response_code_*/,		OUT char* /*pos_response_code_*/,		OUT char* /*pos_response_code_ext_*/,
							OUT char* /*purchaseQueryResponse_*/,
							OUT char* /*res_*/);

//							IN OUT char* /*transaction_datetime_*/, 
//							OUT int*  /*response_code_*/,     	OUT char* /*pos_response_code_*/,		OUT char* /*pos_response_code_ext_*/,
//							OUT char* /*ticket_*/,            	OUT char* /*authorization_code_*/,		OUT int*  /*issuer_*/, 
//							OUT char* /*card_number_*/,       	OUT char* /*expiration_date_*/,			OUT int*  /*origin_card_type_*/,
//							OUT char* /*transaction_type_*/,  	OUT char* /*batch_*/,					OUT int*  /*acquirer_*/,
//							OUT char* /*EMV_application_id_*/,	OUT char* /*EMV_application_name_*/, 	OUT char* /*res_*/);
#endif