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

TWSRESGEOITDCLIENT_API void PurchaseVoid(IN  char* ip_,             IN  int   port_,
										 IN  char* pos_id_,         IN  char* system_id_,         IN  char* branch_,
										 IN  char* client_app_id_,  IN  char* user_id_,           IN  char* original_ticket_,
										 OUT int*  response_code_,  OUT char* transaction_id_,    OUT char* res_);

typedef void(*PURCHASEVOID)(IN  char* /*ip_*/,             IN  int   /*port_*/,
							IN  char* /*pos_id_*/,         IN  char* /*system_id_*/,         IN  char* /*branch_*/,
							IN  char* /*client_app_id_*/,  IN  char* /*user_id_*/,           IN  char* /*original_ticket_*/,
							OUT int*  /*response_code_*/,  OUT char* /*transaction_id_*/,    OUT char* /*res_*/);

TWSRESGEOITDCLIENT_API void PurchaseRefund(IN  char* ip_,                 IN  int   port_,
 										   IN  char* pos_id_,             IN  char* system_id_,         IN  char* branch_,
										   IN  char* client_app_id_,      IN  char* user_id_,           IN  char* amount_,
										   IN  int   installment_,        IN  int   plan_,              IN  char* currency_, 
										   IN  int   tax_refund_,         IN  char* taxable_amount_,    IN  char* invocie_amount_,
										   IN  char* invoice_number_,     IN  char* original_ticket_,   IN  char* original_transaction_date_,
										   OUT int*  response_code_,      OUT char* transaction_id_,    OUT char* res_);

typedef void(*PURCHASEREFUND)(	IN  char* /*ip_,                 IN  int   /*port_*/,
 								IN  char* /*pos_id_,             IN  char* /*system_id_*/,         IN  char* /*branch_*/,
								IN  char* /*client_app_id_,      IN  char* /*user_id_*/,           IN  char* /*amount_*/,
								IN  int   /*installment_,        IN  int   /*plan_*/,              IN  char* /*currency_*/, 
								IN  int   /*tax_refund_,         IN  char* /*taxable_amount_*/,    IN  char* /*invocie_amount_*/,
								IN  char* /*invoice_number_,     IN  char* /*original_ticket_*/,   IN  char* /*original_transaction_date_*/,
								OUT int*  /*response_code_,      OUT char* /*transaction_id_*/,    OUT char* /*res_*/);

TWSRESGEOITDCLIENT_API void QueryStatus(IN char* ip_,					IN int   port_,
										IN char* pos_id_,				IN char* system_id_,				IN char* branch_,
										IN char* client_app_id_,		IN char* user_id_,					IN char* transaction_id_,
										IN bool  noWait_,				IN char* transaction_datetime_,		IN int   queryResponseSize_,
										OUT int* response_code_,		OUT char* pos_response_code_,		OUT char* pos_response_code_ext_,
										OUT char* purchaseQueryResponse_,
										OUT char* res_);

typedef void (*QUERYSTATUS)(IN  char* /*ip_*/,                	IN  int   /*port_*/,
							IN  char* /*pos_id_*/,            	IN  char* /*system_id_*/,				IN  char* /*branch_*/,
							IN  char* /*client_app_id_*/,     	IN  char* /*user_id_*/,					IN  char* /*transaction_id_*/,
							IN  bool  /*noWait_*/,				IN  char* /*transaction_datetime_*/,	IN  int   /*queryResponseSize_*/,
							OUT int*  /*response_code_*/,		OUT char* /*pos_response_code_*/,		OUT char* /*pos_response_code_ext_*/,
							OUT char* /*purchaseQueryResponse_*/,
							OUT char* /*res_*/);

#endif