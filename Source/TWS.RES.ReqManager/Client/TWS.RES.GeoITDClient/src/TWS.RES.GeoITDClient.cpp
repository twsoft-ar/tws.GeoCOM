#include "TWS.RES.GeoITDClient.h"
#include "TWS.RES.GeoITDDefine.h"
#include "WSReqClient.h"
#include "levstring.h"
#include "reqstruct.h"
#include "Logger.h"
#include "stdexcept"

char HexToChar(char hex_);

#if defined(UNDER_CE)
#define LOG_FILE "\\CF\\micros\\etc\\GeoITDClientLog.txt"
#else
#define LOG_FILE "GeoITDClientLog.log"
#endif

TWSRESGEOITDCLIENT_API void Purchase(IN  char* ip_,                 IN  int   port_,            
									 IN  char* pos_id_,             IN  char* system_id_,         IN  char* branch_,
									 IN  char* client_app_id_,      IN  char* user_id_,           IN  char* amount_,
									 IN  int   installment_,        IN  int   plan_,              IN  char* currency_, 
									 IN  int   tax_refund_,         IN  char* taxable_amount_,    IN  char* invocie_amount_,
									 IN  char* tip_amount_,         IN  char* invoice_number_,    IN  char* transaction_datetime_,
									 OUT int*  response_code_,      OUT char* transaction_id_,    OUT char* res_)	
{
	ReqMessage	reqMsg;
	ByteStream	msgChain;

	lev::string	strJSON;
	lev::string strResponse;

	try
	{
		Logger::LogEvent(LOG_FILE, "Enter to Purchase()", true);

		memset(transaction_id_, 0, 20);			//string 20

		strJSON << "{" << "\r\n";
		strJSON << "\"pos_id\":"				<< "\"" << pos_id_					<< "\",";
		strJSON << "\"system_id\":"				<< "\"" << system_id_				<< "\",";
		strJSON << "\"branch\":"				<< "\"" << branch_					<< "\",";
		strJSON << "\"client_app_id\":"			<< "\"" << client_app_id_			<< "\",";
		strJSON << "\"user_id\":"				<< "\"" << user_id_					<< "\",";
		strJSON << "\"transaction_date_time\":" << "\"" << transaction_datetime_	<< "\",";
		strJSON << "\"amount\":"				<< "\"" << amount_					<< "\",";
		strJSON << "\"installment\":"					<< installment_				<< ",";
		strJSON << "\"plan\":"							<< plan_					<< ",";
		strJSON << "\"currency\":"				<< "\"" << currency_				<< "\",";
		strJSON << "\"tax_refund\":"					<< tax_refund_				<< ",";
		strJSON << "\"taxable_amount\":"		<< "\"" << taxable_amount_			<< "\",";
		strJSON << "\"invocie_amount\":"		<< "\"" << invocie_amount_			<< "\",";
		strJSON << "\"tip_amount\":"			<< "\"" << tip_amount_				<< "\",";
		strJSON << "\"invoice_number\":"		<< "\"" << invoice_number_			<< "\"";
		strJSON << "}" << "\r\n";

		msgChain.Assign((Byte*)(const char*)strJSON, strJSON.Longitud());

		ReqClient reqClient(ip_, port_, ReqMessage(GEOITD_MSG::Purchase, msgChain.Length(), (Byte*)msgChain));

		if (reqClient.RequestCommand(reqMsg))
		{
			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
			lev::SafeList<lev::string> responseParts = str.Split('|');

			if (responseParts.Size() == 2)
			{
				lev::SafeList<lev::string> keyVal;

				//1. parse response_code
				keyVal = responseParts[0].Split('=');
				if (keyVal.Size() == 2)
				{
					*response_code_ = atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [response_code]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//2 .parse transaction_id
				keyVal = responseParts[1].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(transaction_id_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [transaction_id]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				*res_ = (strResponse.Trim() == "" ? RES_OK : INVALID_MSG);
			}
			else if (responseParts.Size() == 1)
			{
				strResponse = responseParts[0];
				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				*res_ = EXECUTION_ERROR;
			}
			else
			{
				strResponse = "BAD RESPONSE FORM [0]";
				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				*res_ = EXECUTION_ERROR;
			}
		}
		else
			//devuelvo codigo de error		
			*res_ = (char)reqMsg.MessageType;
	}
	catch (const std::exception ex)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), exception caught: " << ex.what();
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), unhandled exception caught";
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	Logger::LogEvent(LOG_FILE, "Exit from Purchase()", true);
}

TWSRESGEOITDCLIENT_API void PurchaseReverse(IN  char* ip_,                 IN  int   port_,
  										    IN  char* pos_id_,             IN  char* system_id_,         IN  char* branch_,
										    IN  char* client_app_id_,      IN  char* user_id_,           IN  char* original_transaction_id_,
										    OUT int*  response_code_,      OUT char* pos_response_code_, OUT char* pos_response_code_ext_,
										    OUT char* transaction_id_,     OUT char* ticket_,            OUT char* authorization_code_,
										    OUT int*  issuer_,             OUT char* card_number_,       OUT char* expiration_date_,
										    OUT char* transaction_datetime_,
										    OUT char* res_)	
{
	ReqMessage	reqMsg;
	ByteStream	msgChain;

	lev::string	strJSON;
	lev::string strResponse;

	try
	{
		Logger::LogEvent(LOG_FILE, "Enter to Purchase()", true);

		memset(pos_response_code_, 0, 10);		//string 10
		memset(pos_response_code_ext_, 0, 10);	//string 10
		memset(transaction_id_, 0, 20);			//string 20
		memset(ticket_, 0, 10);					//string 10
		memset(authorization_code_, 0, 10);		//string 10
		memset(card_number_, 0, 50);			//string 50
		memset(expiration_date_, 0, 20);		//string 20
		memset(transaction_datetime_, 0, 20);	//string 20

		strJSON << "{" << "\r\n";
		strJSON << "\"pos_id\":"					<< "\"" << pos_id_					<< "\",";
		strJSON << "\"system_id\":"					<< "\"" << system_id_				<< "\",";
		strJSON << "\"branch\":"					<< "\"" << branch_					<< "\",";
		strJSON << "\"client_app_id\":"				<< "\"" << client_app_id_			<< "\",";
		strJSON << "\"user_id\":"					<< "\"" << user_id_					<< "\",";
		strJSON << "\"original_transaction_id\":"	<< "\"" << original_transaction_id_ << "\"";
		strJSON << "}" << "\r\n";

		msgChain.Assign((Byte*)(const char*)strJSON, strJSON.Longitud());

		ReqClient reqClient(ip_, port_, ReqMessage(GEOITD_MSG::Reverse, msgChain.Length(), (Byte*)msgChain));

		if (reqClient.RequestCommand(reqMsg))
		{
			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
			lev::SafeList<lev::string> responseParts = str.Split('|');

			if (responseParts.Size() == 1)
			{
				lev::SafeList<lev::string> keyVal;

				//1. parse response_code
				keyVal = responseParts[0].Split('=');
				if (keyVal.Size() == 2)
				{
					*response_code_ = atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [response_code]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}
			}
			else
			{
				strResponse << "BAD RESPONSE FORM [0]";
				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
			}
		}
		else
			//devuelvo codigo de error		
			*res_ = (char)reqMsg.MessageType;
	}
	catch (const std::exception ex)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), exception caught: " << ex.what();
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), unhandled exception caught";
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	Logger::LogEvent(LOG_FILE, "Exit from Purchase()", true);
}

//TWSRESGEOITDCLIENT_API void PurchaseVoid(IN  char* ip_,             IN  int   port_,
//										 IN  char* pos_id_,         IN  char* system_id_,         IN  char* branch_,
//										 IN  char* client_app_id_,  IN  char* user_id_,           IN  char* original_ticket_,
//										 OUT int* response_code_,   OUT char* pos_response_code_, OUT char* pos_response_code_ext_,
//										 OUT char* transaction_id_, OUT char* ticket_,            OUT char* authorization_code_,
//										 OUT int* issuer_,          OUT char* card_number_,       OUT char* expiration_date_,
//										 OUT char* transaction_datetime_,
//										 OUT char* res_)
//{
//	ReqMessage	reqMsg;
//	ByteStream	msgChain;
//
//	lev::string	strJSON;
//	lev::string strResponse;
//
//	try
//	{
//		Logger::LogEvent(LOG_FILE, "Enter to Purchase()", true);
//
//		memset(pos_response_code_, 0, 10);		//string 10
//		memset(pos_response_code_ext_, 0, 10);	//string 10
//		memset(transaction_id_, 0, 20);			//string 20
//		memset(ticket_, 0, 10);					//string 10
//		memset(authorization_code_, 0, 10);		//string 10
//		memset(card_number_, 0, 50);			//string 50
//		memset(expiration_date_, 0, 20);		//string 20
//		memset(transaction_datetime_, 0, 20);	//string 20
//
//		strJSON << "{" << "\r\n";
//		strJSON << "\"pos_id\":" << "\"" << pos_id_ << "\",";
//		strJSON << "\"system_id\":" << "\"" << system_id_ << "\",";
//		strJSON << "\"branch\":" << "\"" << branch_ << "\",";
//		strJSON << "\"client_app_id\":" << "\"" << client_app_id_ << "\",";
//		strJSON << "\"user_id\":" << "\"" << user_id_ << "\",";
//		strJSON << "\"original_ticket\":" << "\"" << original_ticket_ << "\",";
//		strJSON << "}" << "\r\n";
//
//		msgChain.Assign((Byte*)(const char*)strJSON, strJSON.Longitud());
//
//		ReqClient reqClient(ip_, port_, ReqMessage(GEOITD_MSG::PurchaseVoid, msgChain.Length(), (Byte*)msgChain));
//
//		if (reqClient.RequestCommand(reqMsg))
//		{
//			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
//			lev::SafeList<lev::string> responseParts = str.Split('|');
//
//			if (responseParts.Size() == 10)
//			{
//				lev::SafeList<lev::string> keyVal;
//
//				//1. parse response_code
//				keyVal = responseParts[0].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					*response_code_ = atoi(keyVal[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [response_code]\r\n";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//2. parse pos_response_code 
//				keyVal = responseParts[1].Split('=');
//				if (responseParts.Size() == 2)
//				{
//					strcpy(pos_response_code_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [pos_response_code]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//3. parse pos_response_code_ext
//				keyVal = responseParts[2].Split('=');
//				if (responseParts.Size() == 2)
//				{
//					strcpy(pos_response_code_ext_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [pos_response_code_ext]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//4 .parse transaction_id
//				keyVal = responseParts[3].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(transaction_id_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [transaction_id]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//5. parse ticket
//				keyVal = responseParts[4].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(ticket_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [ticket]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//6. parse authorization_code
//				keyVal = responseParts[5].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(authorization_code_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [authorization_code]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//7. parse issuer
//				keyVal = responseParts[6].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					*issuer_ = atoi(keyVal[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [issuer]\r\n";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//8. parse card_number
//				keyVal = responseParts[7].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(card_number_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [card_number]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//9. parse expiration_date
//				keyVal = responseParts[8].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(expiration_date_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [expiration_date]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//10. parse transaction_datetime
//				keyVal = responseParts[9].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(transaction_datetime_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [transaction_datetime]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//			}
//			else if (responseParts.Size() == 1)
//			{
//				strResponse << responseParts[0] << "|";
//				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				*res_ = RES_OK;
//			}
//			else
//			{
//				strResponse << "BAD RESPONSE FORM [0]";
//				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//			}
//		}
//		else
//			//devuelvo codigo de error		
//			*res_ = (char)reqMsg.MessageType;
//	}
//	catch (const std::exception ex)
//	{
//		lev::string strErr = "";
//		strErr << "In Purchase(), exception caught: " << ex.what();
//		strResponse = strErr;
//
//		Logger::LogEvent(LOG_FILE, strErr, true);
//		*res_ = 0;
//	}
//	catch (...)
//	{
//		lev::string strErr = "";
//		strErr << "In Purchase(), unhandled exception caught";
//		strResponse = strErr;
//
//		Logger::LogEvent(LOG_FILE, strErr, true);
//		*res_ = 0;
//	}
//
//	Logger::LogEvent(LOG_FILE, "Exit from Purchase()", true);
//}

TWSRESGEOITDCLIENT_API void PurchaseVoid(IN  char* ip_,             IN  int   port_,
										 IN  char* pos_id_,         IN  char* system_id_,         IN  char* branch_,
										 IN  char* client_app_id_,  IN  char* user_id_,           IN  char* original_ticket_,
										 OUT int*  response_code_,  OUT char* transaction_id_,    OUT char* res_)
{
	ReqMessage	reqMsg;
	ByteStream	msgChain;

	lev::string	strJSON;
	lev::string strResponse;

	try
	{
		Logger::LogEvent(LOG_FILE, "Enter to PurchaseVoid()", true);

		memset(transaction_id_, 0, 20);			//string 20

		strJSON << "{" << "\r\n";
		strJSON << "\"pos_id\":"			<< "\"" << pos_id_			<< "\",";
		strJSON << "\"system_id\":"			<< "\"" << system_id_		<< "\",";
		strJSON << "\"branch\":"			<< "\"" << branch_			<< "\",";
		strJSON << "\"client_app_id\":"		<< "\"" << client_app_id_	<< "\",";
		strJSON << "\"user_id\":"			<< "\"" << user_id_			<< "\",";
		strJSON << "\"original_ticket\":"	<< "\"" << original_ticket_ << "\"";
		strJSON << "}" << "\r\n";

		msgChain.Assign((Byte*)(const char*)strJSON, strJSON.Longitud());

		ReqClient reqClient(ip_, port_, ReqMessage(GEOITD_MSG::PurchaseVoid, msgChain.Length(), (Byte*)msgChain));

		if (reqClient.RequestCommand(reqMsg))
		{
			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
			lev::SafeList<lev::string> responseParts = str.Split('|');

			if (responseParts.Size() == 2)
			{
				lev::SafeList<lev::string> keyVal;

				//1. parse response_code
				keyVal = responseParts[0].Split('=');
				if (keyVal.Size() == 2)
				{
					*response_code_ = atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [response_code]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In PurchaseVoid(): " << strResponse, true);
				}

				//2 .parse transaction_id
				keyVal = responseParts[1].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(transaction_id_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [transaction_id]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In PurchaseVoid(): " << strResponse, true);
				}

				*res_ = (strResponse.Trim() == "" ? RES_OK : INVALID_MSG);
			}
			else if (responseParts.Size() == 1)
			{
				strResponse = responseParts[0];
				Logger::LogEvent(LOG_FILE, lev::string() << "In PurchaseVoid(): " << strResponse, true);
				*res_ = EXECUTION_ERROR;
			}
			else
			{
				strResponse = "BAD RESPONSE FORM [0]";
				Logger::LogEvent(LOG_FILE, lev::string() << "In PurchaseVoid(): " << strResponse, true);
				*res_ = EXECUTION_ERROR;
			}
		}
		else
			//devuelvo codigo de error		
			*res_ = (char)reqMsg.MessageType;
	}
	catch (const std::exception ex)
	{
		lev::string strErr = "";
		strErr << "In PurchaseVoid(), exception caught: " << ex.what();
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In PurchaseVoid(), unhandled exception caught";
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	Logger::LogEvent(LOG_FILE, "Exit from PurchaseVoid()", true);
}
//TWSRESGEOITDCLIENT_API void PurchaseRefund(IN  char* ip_,                 IN  int   port_,
// 										   IN  char* pos_id_,             IN  char* system_id_,         IN  char* branch_,
//										   IN  char* client_app_id_,      IN  char* user_id_,           IN  char* amount_,
//										   IN  int   installment_,        IN  int   plan_,              IN  char* currency_, 
//										   IN  int   tax_refund_,         IN  char* taxable_amount_,    IN  char* invocie_amount_,
//										   IN  char* invoice_number_,     IN  char* original_ticket_,   IN  char* original_transaction_date_,
//										   OUT int*  response_code_,      OUT char* pos_response_code_, OUT char* pos_response_code_ext_,
//										   OUT char* transaction_id_,     OUT char* ticket_,            OUT char* authorization_code_,
//										   OUT int*  issuer_,             OUT char* card_number_,       OUT char* expiration_date_,
//										   OUT char* transaction_datetime_,
//										   OUT char* res_)
//{
//	ReqMessage	reqMsg;
//	ByteStream	msgChain;
//
//	lev::string	strJSON;
//	lev::string strResponse;
//
//	try
//	{
//		Logger::LogEvent(LOG_FILE, "Enter to Purchase()", true);
//
//		memset(pos_response_code_, 0, 10);		//string 10
//		memset(pos_response_code_ext_, 0, 10);	//string 10
//		memset(transaction_id_, 0, 20);			//string 20
//		memset(ticket_, 0, 10);					//string 10
//		memset(authorization_code_, 0, 10);		//string 10
//		memset(card_number_, 0, 50);			//string 50
//		memset(expiration_date_, 0, 20);		//string 20
//		memset(transaction_datetime_, 0, 20);	//string 20
//
//		strJSON << "{" << "\r\n";
//		strJSON << "\"pos_id\":" << "\"" << pos_id_ << "\",";
//		strJSON << "\"system_id\":" << "\"" << system_id_ << "\",";
//		strJSON << "\"branch\":" << "\"" << branch_ << "\",";
//		strJSON << "\"client_app_id\":" << "\"" << client_app_id_ << "\",";
//		strJSON << "\"user_id\":" << "\"" << user_id_ << "\",";
//		strJSON << "\"original_ticket\":" << "\"" << original_ticket_ << "\",";
//		strJSON << "\"original_transaction_date\":" << "\"" << original_transaction_date_ << "\",";
//		strJSON << "\"amount\":" << "\"" << amount_ << "\",";
//		strJSON << "\"installment\":" << "\"" << installment_ << "\",";
//		strJSON << "\"plan\":" << plan_ << ",";
//		strJSON << "\"currency\":" << "\"" << currency_ << "\",";
//		strJSON << "\"tax_refund\":" << tax_refund_ << ",";
//		strJSON << "\"taxable_amount\":" << "\"" << taxable_amount_ << "\",";
//		strJSON << "\"invocie_amount\":" << "\"" << invocie_amount_ << "\",";
//		strJSON << "\"invoice_number\":" << "\"" << invoice_number_ << "\",";
//		strJSON << "}" << "\r\n";
//
//		msgChain.Assign((Byte*)(const char*)strJSON, strJSON.Longitud());
//
//		ReqClient reqClient(ip_, port_, ReqMessage(GEOITD_MSG::PurchaseRefund, msgChain.Length(), (Byte*)msgChain));
//
//		if (reqClient.RequestCommand(reqMsg))
//		{
//			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
//			lev::SafeList<lev::string> responseParts = str.Split('|');
//
//			if (responseParts.Size() == 10)
//			{
//				lev::SafeList<lev::string> keyVal;
//
//				//1. parse response_code
//				keyVal = responseParts[0].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					*response_code_ = atoi(keyVal[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [response_code]\r\n";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//2. parse pos_response_code 
//				keyVal = responseParts[1].Split('=');
//				if (responseParts.Size() == 2)
//				{
//					strcpy(pos_response_code_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [pos_response_code]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//3. parse pos_response_code_ext
//				keyVal = responseParts[2].Split('=');
//				if (responseParts.Size() == 2)
//				{
//					strcpy(pos_response_code_ext_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [pos_response_code_ext]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//4 .parse transaction_id
//				keyVal = responseParts[3].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(transaction_id_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [transaction_id]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//5. parse ticket
//				keyVal = responseParts[4].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(ticket_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [ticket]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//6. parse authorization_code
//				keyVal = responseParts[5].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(authorization_code_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [authorization_code]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//7. parse issuer
//				keyVal = responseParts[6].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					*issuer_ = atoi(keyVal[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [issuer]\r\n";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//8. parse card_number
//				keyVal = responseParts[7].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(card_number_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [card_number]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//9. parse expiration_date
//				keyVal = responseParts[8].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(expiration_date_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [expiration_date]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//
//				//10. parse transaction_datetime
//				keyVal = responseParts[9].Split('=');
//				if (keyVal.Size() == 2)
//				{
//					strcpy(transaction_datetime_, responseParts[1]);
//				}
//				else
//				{
//					strResponse = "BAD RESPONSE FORM [transaction_datetime]";
//					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				}
//			}
//			else if (responseParts.Size() == 1)
//			{
//				strResponse << responseParts[0] << "|";
//				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//				*res_ = RES_OK;
//			}
//			else
//			{
//				strResponse << "BAD RESPONSE FORM [0]";
//				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
//			}
//		}
//		else
//			//devuelvo codigo de error		
//			*res_ = (char)reqMsg.MessageType;
//	}
//	catch (const std::exception ex)
//	{
//		lev::string strErr = "";
//		strErr << "In Purchase(), exception caught: " << ex.what();
//		strResponse = strErr;
//
//		Logger::LogEvent(LOG_FILE, strErr, true);
//		*res_ = 0;
//	}
//	catch (...)
//	{
//		lev::string strErr = "";
//		strErr << "In Purchase(), unhandled exception caught";
//		strResponse = strErr;
//
//		Logger::LogEvent(LOG_FILE, strErr, true);
//		*res_ = 0;
//	}
//
//	Logger::LogEvent(LOG_FILE, "Exit from Purchase()", true);
//}

TWSRESGEOITDCLIENT_API void PurchaseRefund(IN  char* ip_,                 IN  int   port_,
 										   IN  char* pos_id_,             IN  char* system_id_,         IN  char* branch_,
										   IN  char* client_app_id_,      IN  char* user_id_,           IN  char* amount_,
										   IN  int   installment_,        IN  int   plan_,              IN  char* currency_, 
										   IN  int   tax_refund_,         IN  char* taxable_amount_,    IN  char* invocie_amount_,
										   IN  char* invoice_number_,     IN  char* original_ticket_,   IN  char* original_transaction_date_,
										   OUT int*  response_code_,      OUT char* transaction_id_,    OUT char* res_)
{
	ReqMessage	reqMsg;
	ByteStream	msgChain;

	lev::string	strJSON;
	lev::string strResponse;

	try
	{
		Logger::LogEvent(LOG_FILE, "Enter to Purchase()", true);

		memset(transaction_id_, 0, 20);			//string 20

		strJSON << "{" << "\r\n";
		strJSON << "\"pos_id\":"					<< "\"" << pos_id_						<< "\",";
		strJSON << "\"system_id\":"					<< "\"" << system_id_					<< "\",";
		strJSON << "\"branch\":"					<< "\"" << branch_						<< "\",";
		strJSON << "\"client_app_id\":"				<< "\"" << client_app_id_				<< "\",";
		strJSON << "\"user_id\":"					<< "\"" << user_id_						<< "\",";
		strJSON << "\"original_ticket\":"			<< "\"" << original_ticket_				<< "\",";
		strJSON << "\"original_transaction_date\":" << "\"" << original_transaction_date_	<< "\",";
		strJSON << "\"amount\":"					<< "\"" << amount_						<< "\",";
		strJSON << "\"installment\":"						<< installment_					<< ",";
		strJSON << "\"plan\":"								<< plan_						<< ",";
		strJSON << "\"currency\":"					<< "\"" << currency_					<< "\",";
		strJSON << "\"tax_refund\":"						<< tax_refund_					<< ",";
		strJSON << "\"taxable_amount\":"			<< "\"" << taxable_amount_				<< "\",";
		strJSON << "\"invocie_amount\":"			<< "\"" << invocie_amount_				<< "\",";
		strJSON << "\"invoice_number\":"			<< "\"" << invoice_number_				<< "\"";
		strJSON << "}" << "\r\n";

		msgChain.Assign((Byte*)(const char*)strJSON, strJSON.Longitud());

		ReqClient reqClient(ip_, port_, ReqMessage(GEOITD_MSG::PurchaseRefund, msgChain.Length(), (Byte*)msgChain));

		if (reqClient.RequestCommand(reqMsg))
		{
			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
			lev::SafeList<lev::string> responseParts = str.Split('|');

			if (responseParts.Size() == 2)
			{
				lev::SafeList<lev::string> keyVal;

				//1. parse response_code
				keyVal = responseParts[0].Split('=');
				if (keyVal.Size() == 2)
				{
					*response_code_ = atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [response_code]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In PurchaseRefund(): " << strResponse, true);
				}

				//2 .parse transaction_id
				keyVal = responseParts[1].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(transaction_id_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [transaction_id]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In PurchaseRefund(): " << strResponse, true);
				}

				*res_ = (strResponse.Trim() == "" ? RES_OK : INVALID_MSG);
			}
			else if (responseParts.Size() == 1)
			{
				strResponse = responseParts[0];
				Logger::LogEvent(LOG_FILE, lev::string() << "In PurchaseRefund(): " << strResponse, true);
				*res_ = EXECUTION_ERROR;
			}
			else
			{
				strResponse = "BAD RESPONSE FORM [0]";
				Logger::LogEvent(LOG_FILE, lev::string() << "In PurchaseRefund(): " << strResponse, true);
				*res_ = EXECUTION_ERROR;
			}
		}
		else
			//devuelvo codigo de error		
			*res_ = (char)reqMsg.MessageType;
	}
	catch (const std::exception ex)
	{
		lev::string strErr = "";
		strErr << "In PurchaseRefund(), exception caught: " << ex.what();
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In PurchaseRefund(), unhandled exception caught";
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	Logger::LogEvent(LOG_FILE, "Exit from PurchaseRefund()", true);
}

//TWSRESGEOITDCLIENT_API void QueryStatus(IN char* ip_,					IN int   port_,
//										IN char* pos_id_,				IN char* system_id_,				IN char* branch_,
//										IN char* client_app_id_,		IN char* user_id_,					IN char* transaction_id_,
//										IN bool  noWait_,               IN OUT char* transaction_datetime_, 
//										OUT int* response_code_,		OUT char* pos_response_code_,		OUT char* pos_response_code_ext_,
//										OUT char* ticket_,				OUT char* authorization_code_,		OUT int*  issuer_, 
//										OUT char* card_number_,			OUT char* expiration_date_,			OUT int*  origin_card_type_,
//										OUT char* transaction_type_,	OUT char* batch_,					OUT int*  acquirer_,
//										OUT char* EMV_application_id_,	OUT char* EMV_application_name_,	OUT char* res_)

TWSRESGEOITDCLIENT_API void QueryStatus(IN char* ip_,					IN int   port_,
										IN char* pos_id_,				IN char* system_id_,				IN char* branch_,
										IN char* client_app_id_,		IN char* user_id_,					IN char* transaction_id_,
										IN bool  noWait_,				IN char* transaction_datetime_,		IN int   queryResponseSize_,
										OUT int* response_code_,		OUT char* pos_response_code_,		OUT char* pos_response_code_ext_,
										OUT char* purchaseQueryResponse_,
										OUT char* res_)
{
	ReqMessage	reqMsg;
	ByteStream	msgChain;

	lev::string	strJSON;
	lev::string strResponse;

	try
	{
		Logger::LogEvent(LOG_FILE, "Enter to QueryStatus()", true);

		memset(purchaseQueryResponse_, 0, queryResponseSize_);

		/*
		memset(pos_response_code_, 0, 10);		//string 10
		memset(pos_response_code_ext_, 0, 10);	//string 10
		memset(ticket_, 0, 10);					//string 10
		memset(authorization_code_, 0, 10);		//string 10
		memset(card_number_, 0, 50);			//string 50
		memset(expiration_date_, 0, 20);		//string 20
		*/
		strJSON << "{" << "\r\n";
		strJSON << "\"pos_id\":" << "\"" << pos_id_ << "\",";
		strJSON << "\"system_id\":" << "\"" << system_id_ << "\",";
		strJSON << "\"branch\":" << "\"" << branch_ << "\",";
		strJSON << "\"client_app_id\":" << "\"" << client_app_id_ << "\",";
		strJSON << "\"user_id\":" << "\"" << user_id_ << "\",";
		strJSON << "\"transaction_id\":" << transaction_id_ << ",";
		strJSON << "\"transaction_date_time\":" << "\"" << transaction_datetime_ << "\"";
		strJSON << "}" << "\r\n";

		msgChain.Assign((Byte*)(const char*)strJSON, strJSON.Longitud());

		ReqClient reqClient(ip_, port_, ReqMessage(noWait_? GEOITD_MSG::QueryStatusNoWait : GEOITD_MSG::QueryStatus, msgChain.Length(), (Byte*)msgChain));

		if (reqClient.RequestCommand(reqMsg))
		{
			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
			lev::SafeList<lev::string> responseParts = str.Split('|');
			lev::SafeList<lev::string> keyVal;
			lev::string queryResponseStr = "";

			if (responseParts.Size() >= 19)
			{
				for (int index = 0; index < responseParts.Size(); index++)
				{
					keyVal = responseParts[index].Split('=');
					if (keyVal.Size() == 2)
					{
						switch(index)
						{
						case 0:
							*response_code_ = atoi(keyVal[1]);
							break;
						case 1:
							strcpy(pos_response_code_, keyVal[1]);
							break;
						case 2:
							strcpy(pos_response_code_ext_, keyVal[1]);
							break;
						default:
							if (index > 3)
								queryResponseStr << "|";
							queryResponseStr << keyVal[1];
						}
					}
					else
					{
						strResponse << "BAD RESPONSE FORM [" << keyVal[0] << "]\r\n";
						Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
					}
				}
				
				if(strResponse.Trim() != "") 
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				
				if (queryResponseStr.Longitud() > queryResponseSize_)
				{
					strResponse << "Query Response Buffer Size is too small: [" << queryResponseSize_ << " vs. " << queryResponseStr.Longitud() << "]" << "\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}
				else
				{
					memcpy(purchaseQueryResponse_, (char*)queryResponseStr, min(queryResponseSize_, queryResponseStr.Longitud()));
				}

				*res_ = RES_OK;

				/*
				//1. parse response_code
				keyVal = responseParts[0].Split('=');
				if (keyVal.Size() == 2)
				{
					queryResponseStr << keyVal[1];
					//*response_code_ = atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [response_code]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}
				queryResponseStr << "|";

				//2. parse pos_response_code 
				keyVal = responseParts[1].Split('=');
				if (keyVal.Size() == 2)
				{
					queryResponseStr << keyVal[1];
					//strcpy(pos_response_code_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [pos_response_code]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}
				queryResponseStr << "|";

				//3. parse pos_response_code_ext
				keyVal = responseParts[2].Split('=');
				if (keyVal.Size() == 2)
				{
					queryResponseStr << keyVal[1];
					//strcpy(pos_response_code_ext_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [pos_response_code_ext]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}
				queryResponseStr << "|";

				//4. parse ticket
				keyVal = responseParts[3].Split('=');
				if (keyVal.Size() == 2)
				{
					queryResponseStr << keyVal[1];
					strcpy(ticket_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [ticket]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}
				queryResponseStr << "|";

				//5. parse authorization_code
				keyVal = responseParts[4].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(authorization_code_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [authorization_code]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//6. parse issuer
				keyVal = responseParts[5].Split('=');
				if (keyVal.Size() == 2)
				{
					*issuer_ = atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [issuer]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//7. parse card_number
				keyVal = responseParts[6].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(card_number_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [card_number]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//8. parse expiration_date
				keyVal = responseParts[7].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(expiration_date_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [expiration_date]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//9. parse transaction_datetime
				keyVal = responseParts[8].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(transaction_datetime_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [transaction_datetime]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//10. parse Application Id
				keyVal = responseParts[9].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(EMV_application_id_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [EMV_application_id]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//11. parse Application Name
				keyVal = responseParts[10].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(EMV_application_name_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [EMV_application_name_]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//12. parse transaction_type
				keyVal = responseParts[11].Split('=');
				if (keyVal.Size() == 2)
				{
					*transaction_type_= atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [transaction_type]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//13. parse origin_card_type
				keyVal = responseParts[12].Split('=');
				if (keyVal.Size() == 2)
				{
					*origin_card_type_= atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [origin_card_type]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//14. parse Batch
				keyVal = responseParts[13].Split('=');
				if (keyVal.Size() == 2)
				{
					strcpy(batch_, keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [batch_]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//15. parse acquirer
				keyVal = responseParts[14].Split('=');
				if (keyVal.Size() == 2)
				{
					*acquirer_ = atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [acquirer]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				*res_ = RES_OK;
				*/
			}
			else if (responseParts.Size() == 1)
			{
				strResponse << responseParts[0] << "|";
				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
			
				keyVal = responseParts[0].Split('=');
				if (keyVal.Size() == 2)
				{
					*response_code_ = atoi(keyVal[1]);
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [response_code]\r\n";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				*res_ = RES_OK;
			}
			else
			{
				strResponse << "BAD RESPONSE FORM [0]";
				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
			}
		}
		else
			//devuelvo codigo de error		
			*res_ = (char)reqMsg.MessageType;
	}
	catch (const std::exception ex)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), exception caught: " << ex.what();
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), unhandled exception caught";
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	Logger::LogEvent(LOG_FILE, "Exit from Purchase()", true);
}
/*
TWSRESGEOITDCLIENT_API void SaleOrder(char* ip_,				int   port_,			int   arraySize_,
									char* collector_id_,	char* pos_id_,			char* reference_,
									int   dtlQty_[],		char* dtlName_[],		char* dtlPrice_[],	
									char* currency_,		char* clientDataRes_,	int dataResSize_,
									char* res_)
{
	ReqMessage	reqMsg;
	ByteStream	msgChain;

	lev::string	strJSON;
	lev::string strResponse;

	try
	{
		Logger::LogEvent(LOG_FILE, "Enter to Purchase()", true);

		memset(clientDataRes_, 0, dataResSize_);

		strJSON << "{" << "\r\n";
		strJSON << "\"collector_id\":" << "\"" << collector_id_ << "\",";
		strJSON << "\"pos_id\":" << "\"" << pos_id_ << "\",";
		strJSON << "\"external_reference\":" << "\"" << reference_ << "\",";
		strJSON << "items:" << "[" << "\r\n";

		for (int i = 0; i < arraySize_; i++)
		{
			if (i > 0)
				strJSON << ",\r\n";

			strJSON << "{" << "\r\n";
			strJSON << "\"title\":" << "\"" << dtlName_[i] << "\"," << "\r\n";
			strJSON << "\"currency_id\":" << "\"" << currency_ << "\"," << "\r\n";
			strJSON << "\"unit_price\":" << dtlPrice_[i] << ",\r\n";
			strJSON << "\"quantity\":" << dtlQty_[i] << ",\r\n";
			strJSON << "}" << "\r\n";
		}
		strJSON << "]" << "\r\n";
		strJSON << "}" << "\r\n";

		msgChain.Assign((Byte*)(const char *)strJSON, strJSON.Longitud());

		ReqClient reqClient(ip_, port_, ReqMessage(MPQR_MSG::SaleOrder, msgChain.Length(), (Byte*)msgChain));

		if (reqClient.RequestCommand(reqMsg))
		{
			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
			lev::SafeList<lev::string> responseParts = str.Split('|');

			if (responseParts.Size() == 5)
			{
				//parse error message
				lev::SafeList<lev::string> errorCode = responseParts[0].Split('=');
				if (errorCode.Size() == 2)
				{
					strResponse << errorCode[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [1]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//parse id
				lev::SafeList<lev::string> id = responseParts[1].Split('=');
				if (id.Size() == 2)
				{
					strResponse << id[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [2]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//parse external reference
				lev::SafeList<lev::string> extRef = responseParts[2].Split('=');
				if (extRef.Size() == 2)
				{
					strResponse << extRef[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [3]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//parse total amount
				lev::SafeList<lev::string> total = responseParts[3].Split('=');
				if (total.Size() == 2)
				{
					strResponse << total[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [4]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}

				//parse MP response
				lev::SafeList<lev::string> mpResponse = responseParts[4].Split('=');
				if (mpResponse.Size() == 2)
				{
					if (strResponse.Longitud() + mpResponse[1].Longitud() < dataResSize_)
						strResponse << mpResponse[1];
					else
						strResponse << mpResponse[1].Left(dataResSize_ - strResponse.Longitud());

					*res_ = RES_OK;
				}
				else
				{				
					strResponse << "BAD RESPONSE FORM [5]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				}
			}
			else if (responseParts.Size() == 1)
			{
				strResponse << responseParts[0] << "|";
				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
				*res_ = RES_OK;
			}
			else
			{
				strResponse << "BAD RESPONSE FORM [0]";
				Logger::LogEvent(LOG_FILE, lev::string() << "In Purchase(): " << strResponse, true);
			}
		}
		else
			//devuelvo codigo de error		
			*res_ = (char)reqMsg.MessageType;
	}
	catch (const std::exception ex)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), exception caught: " << ex.what();
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), unhandled exception caught";
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	try
	{
		memcpy(clientDataRes_, (const char*)strResponse, min(dataResSize_ - 1, strResponse.Longitud()));
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), unhandled exception caught when copying response";

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	
	Logger::LogEvent(LOG_FILE, "Exit from Purchase()", true);
}

TWSRESGEOITDCLIENT_API void CancelOrder(	char* ip_,				int   port_,	
										char* collector_id_,	char* pos_id_,	
										char* clientDataRes_,   int   dataResSize_,		
										char* res_)
{
	ReqMessage	reqMsg;
	ByteStream	msgChain;

	lev::string	strJSON;
	lev::string strResponse;

	try
	{
		Logger::LogEvent(LOG_FILE, "Enter to CancelOrder()", true);

		memset(clientDataRes_, 0, dataResSize_);

		strJSON << "{" << "\r\n";
		strJSON << "\"collector_id\":" << "\"" << collector_id_ << "\",";
		strJSON << "\"pos_id\":" << "\"" << pos_id_ << "\"";
		strJSON << "}" << "\r\n";

		msgChain.Assign((Byte*)(const char *)strJSON, strJSON.Longitud());

		ReqClient reqClient(ip_, port_, ReqMessage(MPQR_MSG::CancelOrder, msgChain.Length(), (Byte*)msgChain));

		if (reqClient.RequestCommand(reqMsg))
		{
			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);

			if (str != "")
			{
				//parse error message
				lev::SafeList<lev::string> errorCode = str.Split('=');
				if (errorCode.Size() == 2)
				{
					strResponse << errorCode[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [1]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In CancelOrder(): " << strResponse, true);
				}
			}
		}
		else
			//devuelvo codigo de error		
			*res_ = (char)reqMsg.MessageType;
	}
	catch (const std::exception ex)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), exception caught: " << ex.what();
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), unhandled exception caught";
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	try
	{
		memcpy(clientDataRes_, (const char*)strResponse, min(dataResSize_ - 1, strResponse.Longitud()));
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In Purchase(), unhandled exception caught when copying response";

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	Logger::LogEvent(LOG_FILE, "Exit from Purchase()", true);
}

TWSRESGEOITDCLIENT_API void GetPaymentStatus(	char* ip_,				int port_,			char* reference_,
											char* clientDataRes_,	int dataResSize_,	char* res_)
{
	ReqMessage			reqMsg;
	ByteStream			msgChain;

	lev::string	strJSON;
	lev::string strResponse;

	try
	{
		Logger::LogEvent(LOG_FILE, "Enter to GetPaymentStatus()", true);
		memset(clientDataRes_, 0, dataResSize_);

		strJSON << "{" << "\r\n";
		strJSON << "\"external_reference\":" << "\"" << reference_ << "\",";
		strJSON << "}" << "\r\n";

		msgChain.Assign((Byte*)(const char *)strJSON, strJSON.Longitud());

		ReqClient reqClient(ip_, port_, ReqMessage(MPQR_MSG::PaymentSearch, msgChain.Length(), (Byte*)msgChain));

		if (reqClient.RequestCommand(reqMsg))
		{
			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
			lev::SafeList<lev::string> responseParts = str.Split('|');

			if (responseParts.Size() == 7)
			{
				//parse error message
				lev::SafeList<lev::string> errorCode = responseParts[0].Split('=');
				if (errorCode.Size() == 2)
				{
					strResponse << errorCode[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [1]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In GetPaymentStatus(): " << strResponse, true);
				}

				//parse id
				lev::SafeList<lev::string> id = responseParts[1].Split('=');
				if (id.Size() == 2)
				{
					strResponse << id[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [2]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In GetPaymentStatus(): " << strResponse, true);
				}

				//parse order id
				lev::SafeList<lev::string> orderId = responseParts[2].Split('=');
				if (orderId.Size() == 2)
				{
					strResponse << orderId[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [3]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In GetPaymentStatus(): " << strResponse, true);
				}

				//parse order type
				lev::SafeList<lev::string> orderType = responseParts[3].Split('=');
				if (orderType.Size() == 2)
				{
					strResponse << orderType[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [4]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In GetPaymentStatus(): " << strResponse, true);
				}

				//parse status
				lev::SafeList<lev::string> status = responseParts[4].Split('=');
				if (status.Size() == 2)
				{
					strResponse << status[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [5]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In GetPaymentStatus(): " << strResponse, true);
				}

				//parse collector id
				lev::SafeList<lev::string> collectorId = responseParts[5].Split('=');
				if (collectorId.Size() == 2)
				{
					strResponse << collectorId[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [6]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In GetPaymentStatus(): " << strResponse, true);
				}

				//parse MP response
				lev::SafeList<lev::string> mpResponse = responseParts[6].Split('=');
				if (mpResponse.Size() == 2)
				{
					if (strResponse.Longitud() + mpResponse[1].Longitud() < dataResSize_ - 1)
						strResponse << mpResponse[1];
					else
						strResponse << mpResponse[1].Left(dataResSize_ - strResponse.Longitud() - 1);

					*res_ = RES_OK;
				}
				else
				{
					strResponse << "BAD RESPONSE FORM [7]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In GetPaymentStatus(): " << strResponse, true);
				}
			}
			else
			{
				strResponse << "BAD RESPONSE FORM [0]";
				Logger::LogEvent(LOG_FILE, lev::string() << "In GetPaymentStatus(): " << strResponse, true);
			}
		}
		else
			//devuelvo codigo de error		
			*res_ = (char)reqMsg.MessageType;
	}
	catch (const std::exception ex)
	{
		lev::string strErr = "";
		strErr << "In GetPaymentStatus(), exception caught: " << ex.what();
		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In GetPaymentStatus(), unhandled exception caught";
		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	try
	{
		memcpy(clientDataRes_, (const char*)strResponse, min(dataResSize_ - 1, strResponse.Longitud()));
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In GetPaymentStatus(), unhandled exception caught when copying response";

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	Logger::LogEvent(LOG_FILE, "Exit from GetPaymentStatus()", true);
}


TWSRESGEOITDCLIENT_API void QRCustomerSaleOrder(char* ip_,             int   port_,          char* store_id_,
											  char* collector_id_,   char* pos_id_,        char* reference_, 
											  char* description_,    char* amount_,        char* customerToken_,
                                              char* clientDataRes_,  int   dataResSize_,   char* res_)
{
	ReqMessage	reqMsg;
	ByteStream	msgChain;

	lev::string	strJSON;
	lev::string strResponse;

	try
	{
		Logger::LogEvent(LOG_FILE, "Enter to QRCustomerPurchase()", true);

		memset(clientDataRes_, 0, dataResSize_);

		strJSON << "{"			<< "\r\n";
		strJSON << "\"payer\":" << "{\r\n";
		strJSON << "\"token\":"					<< "\""		<< customerToken_	<< "\"},";
		strJSON << "\"wallet_payment\":"		<< "{\r\n";
		strJSON << "\"description\":"			<< "\""		<< description_		<< "\",";
		strJSON << "\"external_reference\":"	<< "\""		<< reference_		<< "\",";
		strJSON << "\"transaction_amount\":"				<< amount_			<< "},";
		strJSON << "\"disbursements\": [{";
		strJSON << "\"collector_id\":"			<< "\""		<< collector_id_	<< "\"}],";
		strJSON << "\"external_store_id\":"		<< "\""		<< store_id_		<< "\",";
		strJSON << "\"external_pos_id\":"		<< "\""		<< pos_id_			<< "\"";
		strJSON << "}\r\n";

		msgChain.Assign((Byte*)(const char *)strJSON, strJSON.Longitud());

		ReqClient reqClient(ip_, port_, ReqMessage(MPQR_MSG::QrPayerSaleOrder, msgChain.Length(), (Byte*)msgChain));

		if (reqClient.RequestCommand(reqMsg))
		{
			lev::string str((char*)reqMsg.Body, reqMsg.BodySize);
			lev::SafeList<lev::string> responseParts = str.Split('|');

			if (responseParts.Size() == 6)
			{
				//parse error message
				lev::SafeList<lev::string> errorCode = responseParts[0].Split('=');
				if (errorCode.Size() == 2)
				{
					strResponse << errorCode[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [1]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In QRCustomerPurchase(): " << strResponse, true);
				}

				//parse status
				lev::SafeList<lev::string> status = responseParts[1].Split('=');
				if (status.Size() == 2)
				{
					strResponse << status[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [2]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In QRCustomerPurchase(): " << strResponse, true);
				}

				//parse id
				lev::SafeList<lev::string> id = responseParts[2].Split('=');
				if (id.Size() == 2)
				{
					strResponse << id[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [3]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In QRCustomerPurchase(): " << strResponse, true);
				}

				//parse external reference
				lev::SafeList<lev::string> extRef = responseParts[3].Split('=');
				if (extRef.Size() == 2)
				{
					strResponse << extRef[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [4]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In QRCustomerPurchase(): " << strResponse, true);
				}

				//parse total amount
				lev::SafeList<lev::string> total = responseParts[4].Split('=');
				if (total.Size() == 2)
				{
					strResponse << total[1] << "|";
				}
				else
				{
					strResponse = "BAD RESPONSE FORM [5]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In QRCustomerPurchase(): " << strResponse, true);
				}

				//parse MP response
				lev::SafeList<lev::string> mpResponse = responseParts[5].Split('=');
				if (mpResponse.Size() == 2)
				{
					if (strResponse.Longitud() + mpResponse[1].Longitud() < dataResSize_)
						strResponse << mpResponse[1];
					else
						strResponse << mpResponse[1].Left(dataResSize_ - strResponse.Longitud());

					*res_ = RES_OK;
				}
				else
				{
					strResponse << "BAD RESPONSE FORM [6]";
					Logger::LogEvent(LOG_FILE, lev::string() << "In QRCustomerPurchase(): " << strResponse, true);
				}
			}
			else if (responseParts.Size() == 1)
			{
				strResponse << responseParts[0] << "|";
				Logger::LogEvent(LOG_FILE, lev::string() << "In QRCustomerPurchase(): " << strResponse, true);
				*res_ = RES_OK;
			}
			else
			{
				strResponse << "BAD RESPONSE FORM [0]";
				Logger::LogEvent(LOG_FILE, lev::string() << "In QRCustomerPurchase(): " << strResponse, true);
			}
		}
		else
			//devuelvo codigo de error		
			*res_ = (char)reqMsg.MessageType;
	}
	catch (const std::exception ex)
	{
		lev::string strErr = "";
		strErr << "In QRCustomerPurchase(), exception caught: " << ex.what();
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In QRCustomerPurchase(), unhandled exception caught";
		strResponse = strErr;

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	try
	{
		memcpy(clientDataRes_, (const char*)strResponse, min(dataResSize_ - 1, strResponse.Longitud()));
	}
	catch (...)
	{
		lev::string strErr = "";
		strErr << "In QRCustomerPurchase(), unhandled exception caught when copying response";

		Logger::LogEvent(LOG_FILE, strErr, true);
		*res_ = 0;
	}

	Logger::LogEvent(LOG_FILE, "Exit from QRCustomerPurchase()", true);
}*/
