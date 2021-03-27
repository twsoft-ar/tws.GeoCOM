// *************************************************************************
//		          MICROS RES3700 GEOCOM GeoITD
//						Current Version: 1.0.0
// *************************************************************************
// *************************************************************************
//
//
// *************************************************************************
// *   EDITOR SETTINGS                                                     *
// *   ====== ========                                                     *
// *                                                                       *
// *   Set tabulation to 4 chars long to visualize a correct indentation   *
// *                                                                       *
// *************************************************************************
//
// =========================================================================
// History
// =========================================================================
//
//
// 10/03/2021- v1.0.0 * Luis Vaccaro * 
//
//
// =========================================================================
// TO DO
//
// =========================================================================
//
// =========================================================================

// ------------------------------------------------------------- //
///////////////////////////////////////////////////////////////////
//			The Following code is not to be modified!			 //
///////////////////////////////////////////////////////////////////
// ------------------------------------------------------------- //

// SIM OPTIONS
RetainGlobalVar
SetSignOnLeft 

// --------------------------------------------------------- //
///////////////////////// Constants ///////////////////////////
// --------------------------------------------------------- //

Var IFC_VERSION									:A16 = "1.0.5"
                        						
//CONSTANTS        
Var TRUE										:N1 = 1
Var FALSE										:N1 = 0
                                       			
Var PCWS_TYPE									:N1 = 1	// Type number for PCWS
Var PPC55A_TYPE 					 			:N1 = 2 // Type number for Workstation mTablet
Var WS4_TYPE									:N1 = 3	// Type number for Workstation 4
Var WS5_TYPE									:N1 = 3	// Type number for Workstation 5
                            					
 
// Check detail types [@dtl_type]

Var DT_CHECK_INFO     							:A1 = "I"
Var DT_MENU_ITEM		     					:A1 = "M"
Var DT_DISCOUNT       							:A1 = "D"
Var DT_SERVICE_CHARGE 							:A1 = "S"
Var DT_TENDER				 					:A1 = "T"
Var DT_REFERENCE      							:A1 = "R"
Var DT_CA_DETAIL      							:A1 = "C"


//Detail status flag definitions
// 1ST DIGIT
Var DTL_PREV_RND								:N1 = 1
Var DTL_RETURN									:N1 = 4
// 2ND DIGIT                			
Var DTL_VOID									:N1 = 5
// 3RD DIGIT                			
Var DTL_PRV_RND_VOID							:N2 = 10
Var DTL_ERROR_CORRECT							:N2 = 12
// 4TH DIGIT                			
Var DTL_ITEM_SHARED								:N2 = 14
Var DTL_VOID_EDIT								:N2 = 15
// 8TH DIGIT					    			
Var DTL_SKU_ENTRY								:N2 = 30
                            			
// Detail TypeDef bits      			
Var DTL_ITEM_PRICE_PRESET						:N2 = 1
Var DTL_ITEM_IS_WEIGHED							:N2 = 28 
// ** Protocol ENUMS **
 
 
//Key Types
Var KEY_TYPE_TENDER_OBJNUM 						:N1 = 9
  
////////////////////////// IFC Global vars /////////////////////////////
Var MAX_TENDER_MAP 								:N9 = 64

Var gbliSelectedPrinterIndex 					:N9
Var SELECTED_PRINTER[4] 						:N9
	SELECTED_PRINTER[1] = @RCPT
	SELECTED_PRINTER[2] = @CHK
	SELECTED_PRINTER[3] = @JNL
	SELECTED_PRINTER[4] = @VALD

Var gblsGeocomCreditIssuerCode[MAX_TENDER_MAP] 			:N9
Var gbliGeocomCreditMappedTndrObjNum[MAX_TENDER_MAP]	:N9
Var gbliGeocomCreditMappedName[MAX_TENDER_MAP]			:A64
Var gblsGeocomDebitIssuerCode[MAX_TENDER_MAP] 			:N9
Var gbliGeocomDebitMappedTndrObjNum[MAX_TENDER_MAP]		:N9
Var gbliGeocomDebitMappedName[MAX_TENDER_MAP]			:A64

Var gblsGeocomAcquirerName[MAX_TENDER_MAP] 		:A64
Var gblsGeocomAcquirerCode[MAX_TENDER_MAP] 		:N9 		

Var gbliWSType				 					:N1		// To store the current Workstation type  
Var gbliRESMajVer								:N2		// To store the current RES major version 
Var gbliRESMinVer								:N2		// To store the current RES minor version
     
// filenames                    	
Var PATH_TO_GEOITD_DRIVER						:A100
Var ERROR_LOG_FILE_NAME							:A100
Var CONFIGURATION_FILE_NAME						:A100
Var CONFIGURATION_FILE_NAME_PWS					:A100
                                				                             				
// Driver handles (DLLs)        				
Var gblPaymentDrv 								:N12

// IFC Specific
Var CREDIT_CARD 								:A8 = "CREDITO"
Var DEBIT_CARD 									:A8 = "DEBITO"
Var RESPONSE_OK 								:N9 = 0
Var RESPONSE_WAITING_CARD 						:N9 = 10
Var RESPONSE_WAITING_RESPONSE 					:N9 = 12

Var STATUS_WAITING_FOR_CARD 					:N9 = 0
Var STATUS_WAITING_FOR_RESPONSE 				:N9 = 1
Var STATUS_APPROVED 							:N9 = 2
Var STATUS_ERROR 								:N9 = -1

Var gbliTaxIsInclusive		 					:N1		// To specify if current tax is "inclusive" or not
Var gblsServerIP 								:A16 	// Micros ReqServer IP (micros res server ip)
Var gbliServerPort 								:N9 	// Micros ReqServer PORT
Var gblsPinpadID 								:A32
Var gblsSystemID 								:A200
Var gblsBranchID 								:A100
Var gbliTaxRefund 								:N9

Var gblcPaymentAmount 							:$12
Var gblcTaxableAmount 							:$12
Var gblcInvocieBaseAmount 						:$12
Var gblcInvoiceTaxAmount 						:$12
Var gbliIsConsumidorFinal		 				:N1

Var gblsRefDataTime 							:A64
Var gbliCCTenderPresent 						:N1

Var gblsCurrency 								:A16
Var gbliMPTenderObjNum 							:N9
Var gblsCollectorID 							:A64
Var gblsSaleDescription 						:A1024
Var gbliTimeout 								:N9
Var gblsReference 								:A64
Var gbliTenderRefReq 							:N1

//Query Response Fields
Var gblsTransDate 								:A32
Var gblsTransTime 								:A32
Var gbliResponseCode							:N9
Var gblsPosResponseCode 						:A16
Var gblsPosResponseCodeExt 						:A16
Var gblsTicketNumber 							:A16
Var gblsOriginalTicketNumber 					:A16
Var gblsOriginalTicketDate 						:A32
Var gblsAuthorizationCode 						:A32
Var gbliIssuer 									:N9
Var gblsCardNumber 								:A32
Var gblsExpirationDate 							:A32
Var gbliOriginCardType 							:N9
Var gblsTransactionType 						:A16
Var gblsBatch									:A16
Var gbliAcquirer 								:N9
Var gblsEMVAppId 								:A32
Var gblsEMVAppName 								:A32
Var gblsMerchant  								:A32
Var gblsInputMode 								:A40
Var gblsCardOwnerName 							:A40
Var gblsStoreName 								:A40
Var gblsStoreRUT 								:A40
Var gblsStoreAddress 							:A40

//Client Req Error codes
Var EXECUTION_OK 								:N9 = 1
Var EXECUTION_ERROR								:N9 = 156 //-100 
Var CONNECTION_ERROR							:N9 = 155 //-101	
Var PARAM_ERROR 								:N9 = 154 //-102
Var TIMEOUT_ERROR								:N9 = 153 //-103
Var CHECKSUM_ERROR		 						:N9 = 152 //-104



////////////////////////////////////////////////////////////////
//							EVENTS							  //
////////////////////////////////////////////////////////////////

// ****************************************************************************************
// * NOTE: if this isl is executed as stand alone, uncomment this events and define every *
// *       single on of it; otherwise, assure that caller isl has this events defined and *
// *       calls every function as they are called here.                                  *
// ****************************************************************************************

Event Init

	gbliIsConsumidorFinal = TRUE
	
	// get client platform
	Call setWorkstationType()

	// set file paths for this client
	Call setFilePaths()

	// Load Custom Settings from .cfg file
	Call LoadCustomSettings()
		
EndEvent

Event Final_Tender	
	
	If(Not gbliCCTenderPresent And gblsReference <> "")
		//Call CancelMPQROrder()
	EndIf
	
	Call ClearGobalVars()
	
EndEvent

Event Trans_Cncl
	
	If(gblsReference <> "")
		//Call CancelMPQROrder()
	EndIf
	
	Call ClearGobalVars()
	
EndEvent

Event Tndr
	Call ClearGobalVars()
EndEvent
	
////////////////////////////////////////////////////////////////
//						INQ EVENTS							  //
////////////////////////////////////////////////////////////////

Event Inq : 01 //Place Sale Order
		
	If(gblsReference = "")
		Call DoPaymentOrder()
	Else
		Call ValidatePayment(gblsReference, gblsRefDataTime)
	EndIf
	
EndEvent

Event Inq : 02 //Validate Last Payment (if any)
	
	Call ValidatePayment(gblsReference, gblsRefDataTime)

EndEvent

Event Inq : 03 //Cancel Order (if any)
	
	Call DoRefundOrder()
	
EndEvent
 

Event Inq : 10 //Empresa / Consumidor Final
	
	gbliIsConsumidorFinal = Not gbliIsConsumidorFinal
	
	If(Not gbliIsConsumidorFinal)
		InfoMessage "Cliente tipo EMPRESA"
	Else
		InfoMessage "Cliente tipo CONSUMIDOR FINAL"
	EndIf

EndEvent

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                       //
//=========================================== IFC FUNCTIONS =============================================//
//                                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

//******************************************************************
// Procedure: ValidatePayment()
//******************************************************************
Sub ValidatePayment(Ref transactionId_, Ref transactionDateTime_)
	
	Var bOK 			:N1
	Var keepTrying 		:N1 = TRUE
	Var elapsedTime 	:N9 = 0
	Var initTime 		:N9
	Var timeOut 		:N1 = FALSE
	Var paymentId 		:A32
	Var strAux 			:A64
	Var paymentStatus 	:N9
	Var issuer 			:N9
	Var firstTime 		:N1 = TRUE	
	
	//Debug
	//ErrorMessage "Enter to ValidatePayment [", transactionId_, "]"
	//ErrorMessage "transactionId_=", transactionId_
	//Debug

	If(transactionId_ = "")
		ErrorMessage "No hay transaccion pendiente"
		Return 
	EndIf

	initTime = @MINUTE * 60 + @SECOND		
	While(keepTrying)
						
		//Preguntar por Estado de Pago
		Prompt ""
		//Call GetPaymentStatus(transactionId_, transactionDateTime_, issuer, paymentStatus, bOK)
		Call GetPaymentStatus(transactionId_, transactionDateTime_, paymentStatus, bOK)
		
		//Debug
		//ErrorMessage "paymentStatus=", paymentStatus, " bOK=", bOK
		//Debug
			
		If(paymentStatus = STATUS_APPROVED)

			InfoMessage "Pago Aprobado !!"
			
			Var lawDiscountAmount 	:A16 = "0"
			Var plan             	:A16 = "0"
			Var installment       	:A16 = "1"
			Var lawDisountText    	:A32 = ""
			Var lawNumber         	:A16 = ""
			Var inputMode 			:A16 = ""
			Var objNum 				:N9
			Var cardType 			:A8
			Var cardName 			:A64
			Var tipAmount 			:$12 = @CHGTIP
			Var invoiceNumber 		:A16 = @CKNUM
			
			Call GetTenderObjNumber(gbliIssuer, objNum, cardName, cardType)
												
			If(gblsInputMode = "B")
				inputMode = "BANDA"
			ElseIf(gblsInputMode = "M")
				inputMode = "MANUAL"
			ElseIf(gblsInputMode = "C")
				inputMode = "CHIP"
			ElseIf(gblsInputMode = "L")
				inputMode = "CONTACTLESS"
			EndIf
																	
			Call PrintVoucher(	gblsTransDate, 				gblsTransTime, 			cardType,				cardName, 			\
								gblsStoreName, 				gblsMerchant, 			gblsStoreAddress, 		gblsStoreRUT, 		\
								gblsPinpadID, 				gblsBatch, 				gblsTicketNumber, 		gblsCardNumber,		\
								gblsExpirationDate, 		inputMode, 				gblsEMVAppName, 		gblsEMVAppId,		\								
								gblsOriginalTicketNumber,	gblsOriginalTicketDate,	gblcPaymentAmount, 		lawDiscountAmount, 	\
								tipAmount,					plan, 			 		installment,			lawDisountText, 	\
								invoiceNumber,				lawNumber, 				gblcPaymentAmount, 		gblcTaxableAmount, 	\
								gblsCardOwnerName, 			gblsAuthorizationCode, 												\
				                FALSE)												
																			
			If(gbliTenderRefReq)
				LoadKybdMacro MakeKeys(gblcPaymentAmount), Key(KEY_TYPE_TENDER_OBJNUM, objNum), MakeKeys(transactionId_), @KEY_ENTER
			Else
				LoadKybdMacro MakeKeys(gblcPaymentAmount), Key(KEY_TYPE_TENDER_OBJNUM, objNum), @KEY_ENTER
			EndIf
			gbliCCTenderPresent = TRUE
			
			Return
			
		ElseIf(paymentStatus = STATUS_WAITING_FOR_CARD)
			If(firstTime)
				InfoMessage "INSERTE TARJETA EN EL POS"
				firstTime = FALSE
			EndIf
			Prompt "INSERTE TARJETA EN EL POS"
		ElseIf(paymentStatus = STATUS_WAITING_FOR_RESPONSE)
			Prompt "ESPERANDO RESPUESTA DEL POS..."
		Else
			gblsReference = ""
			ErrorMessage "Error, pago no procesado"
			ExitCancel
		EndIf
					
		If(elapsedTime > gbliTimeout)

			timeOut = TRUE
			Call PromptYesOrNo(bOK, "Desea esperar mas tiempo?")
			
			If(bOK)
				initTime = @MINUTE * 60 + @SECOND
				elapsedTime = 0
				timeOut = FALSE
			EndIf
								
		EndIf
		
		keepTrying = (bOK) And (Not timeOut) 
	
		MSleep(1000)  
		elapsedTime = (@MINUTE * 60 + @SECOND) - initTime 
		
	EndWhile
	
EndSub

//******************************************************************
// Procedure: 	PrintVoucher()
//******************************************************************
Sub PrintVoucher(	Ref date_, 				Ref time_, 				Ref cardType_, 			Ref	cardName_,			\
					Ref storeName_, 		Ref storeID_,			Ref storeAddress_, 		Ref storeRUT_, 			\
					Ref terminal_, 			Ref batch_, 			Ref ticketNumber_, 		Ref cardNumber_,		\
					Ref cardExpDate_, 		Ref inputMode_, 		Ref emvAppName_, 		Ref emvAppId_,			\
					Ref originalTkt_,		Ref originalTktDate_, 	Ref invoiceAmount_, 	Ref lawDiscountAmount_, \
					Ref tipAmount_,			Ref plan_, 				Ref installment_,		Ref lawDisountText_, 	\
					Ref invoiceNumber_,		Ref lawNumber_, 		Ref totalAmount_, 		Ref burdenAmount_, 		\
					Ref cardHolder_, 		Ref authorizationCode_, 												\
	                Var copy_ :N1)

	Var prtLine 	:A256
	Var fieldLeft 	:A256
	Var fieldRight 	:A256
	
	StartPrint SELECTED_PRINTER[gbliSelectedPrinterIndex]
		                //"0        1         2         3         4"
		                //"1234567890123456789012345678901234567890"

		Format fieldLeft  As date_
		Format fieldRight As time_
		Format prtLine As fieldLeft{<20}, fieldRight {>20} 
		PrintLine prtLine 
		
		Format fieldLeft As cardName_ 
		Format prtLine As fieldLeft{=40} 
		PrintLine prtLine 

		Format fieldLeft As cardType_, " ONLINE" 
		Format prtLine As fieldLeft{=40} 
		PrintLine prtLine 
		
		Format prtLine As storeName_{=40}
		PrintLine prtLine 
		
		Format prtLine As storeAddress_{=40}
		PrintLine prtLine 

		Format fieldLeft As "RUT ", storeRUT_
		Format prtLine As fieldLeft{=40} 
		PrintLine prtLine 
		
		Format fieldLeft As "COMERCIO: ", storeID_
		Format fieldRight As "TERM: ", terminal_
		Format prtLine As fieldLeft{<26}, fieldRight {>14} 
		PrintLine prtLine 
		
		Format fieldLeft As "LOTE: ", batch_
		Format fieldRight As "TICKET: ", ticketNumber_
		Format prtLine As fieldLeft{<28}, fieldRight {>12} 
		PrintLine prtLine 

		Format fieldLeft As "Tarjeta: ", cardNumber_
		Format fieldRight As "Vto.", cardExpDate_, " ", inputMode_
		Format prtLine As fieldLeft{<25}, fieldRight {>15} 
		PrintLine prtLine 
		
		Format fieldLeft As emvAppName_
		Format fieldRight As emvAppId_
		Format prtLine As fieldLeft{<25}, fieldRight {>15} 
		PrintLine prtLine 
	
		If(originalTkt_ <> "")
			Format fieldLeft As "TKT ORIG:", originalTkt_
			Format fieldRight As "FECHA ORIG:", originalTktDate_
			Format prtLine As fieldLeft{<20}, fieldRight {>20} 
			PrintLine prtLine 		
		EndIf
		
		If(invoiceAmount_ <> gblcPaymentAmount)
			Format fieldLeft As "IMPORTE"
			Format fieldRight As invoiceAmount_ 
			Format prtLine As fieldLeft{<28}, fieldRight {>12} 
			PrintLine prtLine 
		EndIf 
	
		If(lawDiscountAmount_ <> 0.00)
			Format fieldLeft As "Decuento Ley ", lawNumber_
			Format fieldRight As lawDiscountAmount_ 
			Format prtLine As fieldLeft{<28}, fieldRight {>12} 
			PrintLine prtLine 
		EndIf
		
		If(tipAmount_ <> 0.00)
			Format fieldLeft As "Propina/Adelanto"
			Format fieldRight As tipAmount_ 
			Format prtLine As fieldLeft{<28}, fieldRight {>12} 
			PrintLine prtLine 
		EndIf

		Format fieldLeft As "TOTAL"
		Format fieldRight As gblcPaymentAmount - lawDiscountAmount_ + tipAmount_ 
		Format prtLine As fieldLeft{<28}, fieldRight {>12} 
		PrintLine prtLine 

		Format fieldLeft As "PLAN: ", plan_
		Format fieldRight As "CUOTAS: ", installment_ 
		Format prtLine As fieldLeft{<20}, fieldRight {>20} 
		PrintLine prtLine 

		Format fieldLeft As "AUTORIZACION: ", authorizationCode_
		Format fieldRight As "Nro. Fact: ", invoiceNumber_ 
		Format prtLine As fieldLeft{<20}, fieldRight {>20} 
		PrintLine prtLine 
		
		PrintLine ""
		PrintLine ""
				
		If(Not copy_)
			Format prtLine As "DOCUMENTO_______________________________"
			PrintLine prtLine 
			PrintLine ""
			Format prtLine As "FIRMA___________________________________"
			PrintLine prtLine 

			Format prtLine As cardHolder_{=40}
			PrintLine prtLine 		
		Else

			Format prtLine As cardHolder_{=40}
			PrintLine prtLine 		

			Format prtLine As "MUCHAS GRACIAS"{=40}
			PrintLine prtLine 		

			Format prtLine As "** COPIA CLIENTE **"{=40}
			PrintLine prtLine 		
		EndIf

	EndPrint	
		
EndSub

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                       //
//======================================== GEOITD API FUNCTIONS =========================================//
//                                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////////////////////


//******************************************************************
// Procedure: DoPaymentOrder()
//******************************************************************
Sub DoPaymentOrder()

	Var posId 			:A64
	Var WSIDStr 		:A16 = @WSID
	Var userId 			:A32 = @TREMP
	Var paymentAmount 	:A32
	Var amount 			:$12 = 0
	Var intallment 		:N9 = 1
	Var plan 			:N9 = 0
	Var currency  		:A8 = "858"
	Var invoiceTotal 	:$12 = (@TTLDUE + @PREVPAY)
	Var taxRefund 		:N9 = 0
	Var taxableAmount 	:$12
	Var taxTtlDummy 	:$12
	Var tipAmount 		:$12 = @CHGTIP
	Var invoiceNumber 	:A16 = @CKNUM
	Var invoiceDT 		:A64 = ""
	Var transactionID 	:A32
	Var responseCode 	:N9
	Var errorCode       :N9
	Var geoITDError 	:A1024
	Var strAux 			:A1024 			
	Var intAmount100 	:N9
	Var intInvTotal100 	:N9
	Var intTaxable100 	:N9
	Var intTipAmount100 :N9
	Var strAmount   	:A16
	Var strInvTotal100 	:A16
	Var strTaxable100 	:A16
	Var strTipAmount100 :A16
	

	Call LoadPaymentDrv()
		
	If(gblPaymentDrv <> 0)
						
		Call LogInfo(ERROR_LOG_FILE_NAME, "Before calling SaleOrder", TRUE, TRUE)	
		
		Input paymentAmount, "Ingrese Monto a Pagar"
		
		amount = paymentAmount
		
		//Debug
		//ErrorMessage "amount = ", amount, " TOTALDUE = ", @TTLDUE 
		//Debug 
		
		If(@INPUTSTATUS = 0 Or amount = 0)
			InfoMessage "Operacion cancelada"
			Return
		Else
			If(amount > @TTLDUE)
				amount = @TTLDUE
			EndIf
		EndIf

		gblcPaymentAmount = amount

		If(gbliIsConsumidorFinal)
			taxRefund = gbliTaxRefund
		EndIf
		
		Call GetTaxAndBase(taxTtlDummy, taxableAmount)		
	
		gblcTaxableAmount = taxableAmount * amount / invoiceTotal
	
		intAmount100    = amount * 100
		intInvTotal100  = invoiceTotal * 100
		intTaxable100   = gblcTaxableAmount * 100
		intTipAmount100 = tipAmount * 100
		
		Format strAmount   		As intAmount100
		Format strInvTotal100 	As intInvTotal100
		Format strTaxable100 	As intTaxable100
		Format strTipAmount100 	As intTipAmount100 
			
		Format invoiceDT As (@YEAR + 2000){04}, @MONTH{02}, @DAY{02}, @HOUR{02}, @MINUTE{02}, @SECOND{02}, "000"
		
	
		//Debug
//		gblsPinpadID = "43113460"
//		gblsSystemID = "F3D5877B-3C08-488C-BE97-907444042490"
//		gblsBranchID = "TWS LOCAL 1"
//		WSIDStr = "WS 001"
//		userId = "LUIS"
//		strAmount = "12200"
//		intallment = 1
//		plan = 0
//		currency = "858"
//		taxRefund = 0
//		strTaxable100 = "10000"
//		strInvTotal100 = "12200"
//		tipAmount = "0"
//		invoiceDT = "20210319170000000"
		//Debug
	
		DLLCall_CDecl gblPaymentDrv, Purchase(	gblsServerIP, 		gbliServerPort, 					\		
												gblsPinpadID,		gblsSystemID,		gblsBranchID,	\
												WSIDStr, 			userId, 			strAmount, 		\ 			
												intallment,			plan, 				currency, 		\
												taxRefund, 			strTaxable100, 		strInvTotal100, \
												strTipAmount100, 	invoiceNumber, 		invoiceDT, 		\
												Ref responseCode, 	Ref transactionID, 	Ref errorCode) 
		
		//Debug
		//ErrorMessage "respCode:", responseCode, " errCode:", errorCode, " tranID:", transactionID
		//Debug
		
		Call LogInfo(ERROR_LOG_FILE_NAME, "After calling Purchase", TRUE, TRUE)	
		If(errorCode = EXECUTION_OK)

			//look for Error 
			If(responseCode <> 0 Or errorCode <> EXECUTION_OK)
				
				ErrorMessage "No se puede procesar el pago."
				
				Call LogInfo(ERROR_LOG_FILE_NAME, "Call to Purchase() returned GEOITD Error:", TRUE, TRUE)
				Call LogInfo(ERROR_LOG_FILE_NAME, clientDataRes, TRUE, TRUE)
				Return
			EndIf
					
			//Success								
			Prompt "Solicitud de pago enviada."

			gblsReference = transactionID
			gblsRefDataTime = invoiceDT
			//debug
			//ErrorMessage "transactionID:", transactionID
			//debug
			Call ValidatePayment(gblsReference, gblsRefDataTime)
			
		Else		
			Call ShowErrorMessage(errorCode, "", "")
		EndIf

		Call FreePaymentDrv()
												 		
	EndIf
		
EndSub

//******************************************************************
// Procedure: DoRefundOrder()
//******************************************************************
Sub DoRefundOrder()

	Var posId 			:A64
	Var WSIDStr 		:A16 = @WSID
	Var userId 			:A32 = @TREMP
	Var paymentAmount 	:A32
	Var amount 			:$12 = 0
	Var intallment 		:N9 = 1
	Var plan 			:N9 = 0
	Var currency  		:A8 = "858"
	Var invoiceTotal 	:$12 = (@TTLDUE + @PREVPAY)
	Var taxRefund 		:N9 = 0
	Var taxableAmount 	:$12
	Var taxTtlDummy 	:$12
	Var tipAmount 		:$12 = @CHGTIP
	Var invoiceNumber 	:A16 = @CKNUM
	Var invoiceDT 		:A64 = ""
	Var transactionID 	:A32
	Var responseCode 	:N9
	Var errorCode       :N9
	Var geoITDError 	:A1024
	Var strAux 			:A1024 			
	Var intAmount100 	:N9
	Var intInvTotal100 	:N9
	Var intTaxable100 	:N9
	Var intTipAmount100 :N9
	Var strAmount   	:A16
	Var strInvTotal100 	:A16
	Var strTaxable100 	:A16
	Var strTipAmount100 :A16
	Var originalDT 		:A64 = ""

	Call LoadPaymentDrv()
		
	If(gblPaymentDrv <> 0)
						
		Call LogInfo(ERROR_LOG_FILE_NAME, "Before calling SaleOrder", TRUE, TRUE)	
		
		Input originalDT, "Ingrese Nro. Ticket trans. original"
		Input originalDT, "Ingrese Fecha de trans. orig. (ddmmyy)"
		Input paymentAmount, "Ingrese Monto a Devolver"
		
		amount = paymentAmount
		
		If(@INPUTSTATUS = 0 Or amount = 0)
			InfoMessage "Operacion cancelada"
			Return
		Else
			If(amount > @TTLDUE)
				amount = @TTLDUE
			EndIf
		EndIf

		gblcPaymentAmount = Abs(amount)

		If(gbliIsConsumidorFinal)
			taxRefund = gbliTaxRefund
		EndIf
		
		Call GetTaxAndBase(taxTtlDummy, taxableAmount)		
	
		gblcTaxableAmount = Abs(taxableAmount * amount / invoiceTotal)
	
		intAmount100    = Abs(amount * 100)
		intInvTotal100  = Abs(invoiceTotal * 100)
		intTaxable100   = Abs(gblcTaxableAmount * 100)
		intTipAmount100 = Abs(tipAmount * 100)
		
		Format strAmount   		As intAmount100
		Format strInvTotal100 	As intInvTotal100
		Format strTaxable100 	As intTaxable100
		Format strTipAmount100 	As intTipAmount100 
			
		Format invoiceDT As (@YEAR + 2000){04}, @MONTH{02}, @DAY{02}, @HOUR{02}, @MINUTE{02}, @SECOND{02}, "000"
		
	
		//Debug
//		gblsPinpadID = "43113460"
//		gblsSystemID = "F3D5877B-3C08-488C-BE97-907444042490"
//		gblsBranchID = "TWS LOCAL 1"
//		WSIDStr = "WS 001"
//		userId = "LUIS"
//		strAmount = "12200"
//		intallment = 1
//		plan = 0
//		currency = "858"
//		taxRefund = 0
//		strTaxable100 = "10000"
//		strInvTotal100 = "12200"
//		tipAmount = "0"
//		invoiceDT = "20210319170000000"
		//Debug
	
		DLLCall_CDecl gblPaymentDrv, PurchaseRefund(gblsServerIP, 		gbliServerPort, 					\		
													gblsPinpadID,		gblsSystemID,		gblsBranchID,	\
													WSIDStr, 			userId, 			strAmount, 		\ 			
													intallment,			plan, 				currency, 		\
													taxRefund, 			strTaxable100, 		strInvTotal100, \
													invoiceNumber, 		invoiceDT, 		\
													Ref responseCode, 	Ref transactionID, 	Ref errorCode) 
		
		//Debug
		//ErrorMessage "respCode:", responseCode, " errCode:", errorCode, " tranID:", transactionID
		//Debug
		
		Call LogInfo(ERROR_LOG_FILE_NAME, "After calling Purchase", TRUE, TRUE)	
		If(errorCode = EXECUTION_OK)

			//look for Error 
			If(responseCode <> 0 Or errorCode <> EXECUTION_OK)
				
				ErrorMessage "No se puede procesar el pago."
				
				Call LogInfo(ERROR_LOG_FILE_NAME, "Call to Purchase() returned GEOITD Error:", TRUE, TRUE)
				Call LogInfo(ERROR_LOG_FILE_NAME, clientDataRes, TRUE, TRUE)
				Return
			EndIf
					
			//Success								
			Prompt "Solicitud de pago enviada."

			gblsReference = transactionID
			gblsRefDataTime = invoiceDT
			//debug
			//ErrorMessage "transactionID:", transactionID
			//debug
			Call ValidatePayment(gblsReference, gblsRefDataTime)
			
		Else		
			Call ShowErrorMessage(errorCode, "", "")
		EndIf

		Call FreePaymentDrv()
												 		
	EndIf
		
EndSub

//******************************************************************
// Procedure: GetPaymentStatus()
//******************************************************************
Sub GetPaymentStatus(Ref transactionId_, Ref transDateTime_, Ref status_, Ref retVal_)
	
	Var WSIDStr 			:A16 = @WSID
	Var userId 				:A32 = @TREMP
	Var ticket 				:A16 	
	Var authorizationCode 	:A16 	
	Var cardNumber 			:A50
	Var expirationDate 		:A20
	Var errorCode       	:N9
	Var noWait 			 	:N1 = TRUE
	Var queryResponse 		:A1024

	Call LoadPaymentDrv()

	If(gblPaymentDrv <> 0)

		retVal_ = FALSE
		Call LogInfo(ERROR_LOG_FILE_NAME, "Before calling QueryStatus", TRUE, TRUE)			

//TWSRESGEOITDCLIENT_API void QueryStatus(IN char* ip_,					IN int   port_,
//										IN char* pos_id_,				IN char* system_id_,				IN char* branch_,
//										IN char* client_app_id_,		IN char* user_id_,					IN char* transaction_id_,
//										IN bool  noWait_,				IN char* transaction_datetime_,		IN int   queryResponseSize_,
//										OUT int* response_code_,		OUT char* pos_response_code_,		OUT char* pos_response_code_ext_,
//										OUT char* purchaseQueryResponse_,
//										OUT char* res_)

		DLLCall_CDecl gblPaymentDrv, QueryStatus( 																					\
												gblsServerIP, 				gbliServerPort, 										\		
												gblsPinpadID,				gblsSystemID,				gblsBranchID,				\
												WSIDStr, 					userId,						transactionId_, 			\
												noWait,						transDateTime_, 			1024, 						\ 												
												Ref gbliResponseCode, 		Ref gblsPosResponseCode, 	Ref gblsPosResponseCodeExt, \
												Ref queryResponse, 			Ref errorCode)
																																				
		Call LogInfo(ERROR_LOG_FILE_NAME, "After calling QueryStatus", TRUE, TRUE)																	
		
		//Debug
		Call LogInfo(ERROR_LOG_FILE_NAME, queryResponse, TRUE, TRUE)																	
		//Debug
													
		If(errorCode = EXECUTION_OK)
			If(gbliResponseCode = RESPONSE_WAITING_CARD)
				status_ = STATUS_WAITING_FOR_CARD
			ElseIf(gbliResponseCode = RESPONSE_WAITING_RESPONSE)
				status_ = STATUS_WAITING_FOR_RESPONSE					
			ElseIf(gbliResponseCode = RESPONSE_OK And (	gblsPosResponseCode = "00" Or \ 
														gblsPosResponseCode = "08" Or \
														gblsPosResponseCode = "10" Or \
														gblsPosResponseCode = "11" Or \
														gblsPosResponseCode = "85" Or \
														gblsPosResponseCode = "OF" Or \
														gblsPosResponseCode = "Y1" Or \
														gblsPosResponseCode = "Y3"))
				status_ = STATUS_APPROVED
			Else
				Call LogInfo(ERROR_LOG_FILE_NAME, "PAYMENT FAILED", TRUE, TRUE)																	
				Call LogInfo(ERROR_LOG_FILE_NAME, gblsPosResponseCode, TRUE, TRUE)																	
				Call LogInfo(ERROR_LOG_FILE_NAME, gblsPosResponseCodeExt, TRUE, TRUE)																	
				status_ = STATUS_ERROR
			EndIf			
				
			Split @VERSION, ".", gbliRESMajVer, gbliRESMinVer

            Split queryResponse, "|", 	gblsTicketNumber, 		\
										gblsAuthorizationCode,	\
            							gbliIssuer, 			\
            							gblsCardNumber, 		\
            							gblsExpirationDate, 	\                             
            							gblsTransDate, 			\
            							gblsTransTime, 			\
            							gblsEMVAppId, 			\
            							gblsEMVAppName, 		\
            							gblsTransactionType, 	\
            							gbliOriginCardType, 	\
            							gblsBatch, 				\
            							gbliAcquirer, 			\
            							gblsMerchant, 			\
            							gblsInputMode, 			\
            							gblsCardOwnerName
            							 
			retVal_ = (status_ <> STATUS_ERROR)
		Else		
			status_ = STATUS_ERROR
			Call ShowErrorMessage(errorCode, gblsPosResponseCode, gblsPosResponseCodeExt)
		EndIf
												 		
	EndIf
	
EndSub

//******************************************************************
// Procedure: CancelSaleOrder()
//******************************************************************
Sub CancelSaleOrder(Ref retVal_)
	
	Var clientDataRes 	:A3072
	Var errorCode       :N9
	Var strAux 			:A1024 			
	Var posId 			:A64

	Call LoadPaymentDrv()

	If(gblPaymentDrv <> 0)

		retVal_ = FALSE
		Format posId As gblsStoreID, "POS", @WSID{04} 
	
		Call LogInfo(ERROR_LOG_FILE_NAME, "Before calling CancelOrder", TRUE, TRUE)			

		DLLCall_CDecl gblPaymentDrv, CancelOrder(gblsServerIP, 		gbliServerPort, \ 
											gblsCollectorID,	posId,			\
											Ref clientDataRes, 	2048, 			\ 
                                            Ref errorCode) 	

		Call LogInfo(ERROR_LOG_FILE_NAME, "After calling CancelOrder", TRUE, TRUE)			
													
		If(errorCode = EXECUTION_OK)
			
			Format strAux As "Call to CancelSaleOrder() returned MP Error:", "Call to CancelSaleOrder() returned MP Error:" 
			//parse response
			Call LogInfo(ERROR_LOG_FILE_NAME, strAux, TRUE, TRUE)
							
			//call to API was a success, but payment could fail									
			retVal_ = TRUE
		Else		
			Call ShowErrorMessage(errorCode, "", "")
		EndIf
												 		
	EndIf
	
EndSub

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                       //
//========================================= AUXILIARY FUNCTIONS =========================================//
//                                                                                                       //
///////////////////////////////////////////////////////////////////////////////////////////////////////////


Sub ClearGobalVars()
	
	gblsReference            	= ""
	gblsRefDataTime         	= ""
	gbliIsConsumidorFinal    	= TRUE
	gblcPaymentAmount			= 0
	gblcTaxableAmount 			= 0
	gblsTransDate	        	= ""
	gblsTransTime        		= ""
	gbliResponseCode         	= 0					
	gblsPosResponseCode      	= ""					
	gblsPosResponseCodeExt   	= ""					
	gblsTicketNumber         	= ""					
	gblsOriginalTicketNumber 	= "" 					
	gblsOriginalTicketDate 		= "" 					
	gblsAuthorizationCode    	= ""					
	gbliIssuer               	= 0					
	gblsCardNumber           	= ""					
	gblsExpirationDate       	= ""					
	gbliOriginCardType       	= 0					
	gblsTransactionType      	= ""					
	gblsBatch                	= ""					
	gbliAcquirer             	= 0					
	gblsEMVAppId             	= ""					
	gblsEMVAppName           	= ""				
	gblsMerchant 				= ""
	gblsInputMode 				= ""
    gblsCardOwnerName 			= ""
		
EndSub

//******************************************************************
// Procedure: GetTenderObjNumber()
//******************************************************************
Sub GetTenderObjNumber(Var issuerID_ :N9, Ref tenderObjNum_, Ref name_, Ref cardType_)

	Var index 			:N9
	
	tenderObjNum_ = 0
	cardType_ = ""
	name_ = ""
	
	For index = 1 To MAX_TENDER_MAP
					
		If(gblsGeocomCreditIssuerCode[index] = issuerID_)	
			
			tenderObjNum_ = gbliGeocomCreditMappedTndrObjNum[index]
			cardType_ = CREDIT_CARD
			name_ = Trim(gbliGeocomCreditMappedName[index])
			Return			

		ElseIf(gblsGeocomDebitIssuerCode[index] = issuerID_)
			
			tenderObjNum_ = gbliGeocomDebitMappedTndrObjNum[index]
			cardType_ = DEBIT_CARD
			name_ = Trim(gbliGeocomDebitMappedName[index])
			Return			

		ElseIf(gblsGeocomCreditIssuerCode[index] = 0 And gblsGeocomDebitIssuerCode[index] = 0)
			
			Return

		EndIf
		
	EndFor
	
EndSub

//******************************************************************
// Procedure: 	GetTaxAndBase()
//******************************************************************
Sub GetTaxAndBase(Ref taxTtl_, Ref taxBase_)

	Var cTaxAcum	: $12
	Var cBaseAccum 	: $12 = 0.00
	Var i			: N2	// for looping

	// Accumulate the total values from all taxes.

	For i = 1 To 8
		cTaxAcum = cTaxAcum + @TAX[i]
		
		If(@TAXRATE[i] <> 0.00)
			cBaseAccum = cBaseAccum + ((@TAX[i] * 100) / @TAXRATE[i])
		EndIf
	EndFor

	// return Taxes subtotal
	taxTtl_ = cTaxAcum
	taxBase_ = cBaseAccum
	
EndSub

//******************************************************************
// Procedure: 	SetFilePaths()
//******************************************************************
Sub SetFilePaths()
		
	// general paths
	If gbliWSType = PCWS_TYPE
		// This is a Win32 client
		Format PATH_TO_GEOITD_DRIVER 		As "..\bin\TWS.RES.GeoITDClientW32.dll"		
		Format ERROR_LOG_FILE_NAME 			As "GEOITDLog.log"
		Format CONFIGURATION_FILE_NAME 		As "GEOITD.cfg"
		Format CONFIGURATION_FILE_NAME_PWS 	As "GEOITD", @WSID, ".cfg"

		// This is a WinCE 5.0/6.0 client		
	ElseIf gbliWSType = WS5_TYPE		
		Format PATH_TO_GEOITD_DRIVER 		As "CF\micros\bin\TWS.RES.GeoITDClientWCE.dll"
		Format ERROR_LOG_FILE_NAME 			As "CF\micros\etc\GEOITDLog.txt"
		Format CONFIGURATION_FILE_NAME 		As "CF\micros\etc\GEOITD.cfg"
		Format CONFIGURATION_FILE_NAME_PWS 	As "CF\micros\etc\GEOITD", @WSID, ".cfg"
	Else

		// This is a WS4 client	WinCE 4.2	
		Format PATH_TO_GEOITD_DRIVER 		As "CF\micros\bin\TWS.RES.GeoITDClientWCE.dll"		
		Format ERROR_LOG_FILE_NAME 			As "CF\micros\etc\GEOITDLog.txt"
		Format CONFIGURATION_FILE_NAME 		As "CF\micros\etc\GEOITD.cfg"
		Format CONFIGURATION_FILE_NAME_PWS 	As "CF\micros\etc\GEOITD", @WSID, ".cfg"
	EndIf
		
EndSub

//******************************************************************
// Procedure: setWorkstationType()
//******************************************************************
Sub setWorkstationType()
	
	// get RES major & minor version
	Split @VERSION, ".", gbliRESMajVer, gbliRESMinVer

	// set workstation type

	If gbliRESMinVer >= 2 or gbliRESMajVer >= 3
		gbliWSType = @WSTYPE
	Else
		// older versions don't support the
		// "@WSTYPE" system variable
		gbliWSType = 1  // PCWS as default
	EndIf
	
EndSub

//******************************************************************
// Procedure: LoadPaymentDrv()
//******************************************************************
Sub LoadPaymentDrv()

	Var retMessage :A512
	
	If (gblPaymentDrv = 0)
		Call LogInfo(ERROR_LOG_FILE_NAME, "Loading PAYMENT Driver", TRUE, TRUE)
		DLLLoad gblPaymentDrv, PATH_TO_GEOITD_DRIVER
    EndIf

	If gblPaymentDrv = 0
		Call LogInfo(ERROR_LOG_FILE_NAME, "FAILED to load PAYMENT driver!", TRUE, TRUE)
		ErrorMessage "Failed to load PAYMENT driver!"
		Return 
    EndIf
					
EndSub

//******************************************************************
// Procedure: FreePaymentDrv()
//******************************************************************
Sub FreePaymentDrv()

	If gblPaymentDrv <> 0
		Call LogInfo(ERROR_LOG_FILE_NAME, "Unloading PAYMENT Driver", TRUE, TRUE)	
		DLLFree gblPaymentDrv
		Call LogInfo(ERROR_LOG_FILE_NAME, "Unloading PAYMENT Driver", TRUE, TRUE)	
		gblPaymentDrv = 0	
	EndIf

EndSub

//******************************************************************
// Procedure: 	SetCustomSetting()
// Author: 		Luis Vaccaro
// Purpose: processes the information passed by parameter,
//			classifying the type of custom setting read and 
//		    setting its value into the corresponding variable
// Parameters:
//	- sInfo_ = information string to be processed
//  - fn_	 = pointer to currently open configuration file	
//	- sFileName_ = Filename of read configuration file
//******************************************************************
Sub SetCustomSetting(Ref sInfo_, Ref fn_, Var sFileName_ : A100 )

	Var sTmp :A1000 = Trim(sInfo_)
	Var i	 :N3	// for looping

	If (Mid(sTmp,1,1) = "*")
		
		// Current line is a comment. Ignore it.
			
	ElseIf	sTmp = "REQSERVER_SERVER_IP"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""			
			gblsServerIP = sTmp			
		Else
			Call LogInfo(ERROR_LOG_FILE_NAME, "REQSERVER_SERVER_IP not specified", TRUE, TRUE)
			ErrorMessage "REQSERVER_SERVER_IP no especificado en ", sFileName_
		EndIf

	ElseIf	sTmp = "REQSERVER_SERVER_PORT"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""					
			gbliServerPort = sTmp			
		Else
			Call logInfo(ERROR_LOG_FILE_NAME, "REQSERVER_SERVER_PORT not specified", TRUE, TRUE)
			ErrorMessage "REQSERVER_SERVER_PORT no especificado en ", sFileName_
		EndIf

	ElseIf	sTmp = "GEOCOM_PINPAD_ID"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""					
			gblsPinpadID = sTmp			
		Else
			Call logInfo(ERROR_LOG_FILE_NAME, "GEOCOM_PINPAD_ID not specified", TRUE, TRUE)
			ErrorMessage "GEOCOM_PINPAD_ID no especificado en ", sFileName_
		EndIf

	ElseIf	sTmp = "GEOCOM_SYSTEM_ID"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""					
			gblsSystemID = sTmp			
		Else
			Call logInfo(ERROR_LOG_FILE_NAME, "GEOCOM_SYSTEM_ID not specified", TRUE, TRUE)
			ErrorMessage "GEOCOM_SYSTEM_ID no especificado en ", sFileName_
		EndIf

	ElseIf	sTmp = "GEOCOM_BRANCH_ID"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""					
			gblsBranchID = sTmp			
		Else
			Call logInfo(ERROR_LOG_FILE_NAME, "GEOCOM_BRANCH_ID not specified", TRUE, TRUE)
			ErrorMessage "GEOCOM_BRANCH_ID no especificado en ", sFileName_
		EndIf

	ElseIf	sTmp = "STORE_NAME"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""					
			gblsStoreName = sTmp			
		Else
			Call logInfo(ERROR_LOG_FILE_NAME, "STORE_NAME not specified", TRUE, TRUE)
			ErrorMessage "STORE_NAME no especificado en ", sFileName_
		EndIf

	ElseIf	sTmp = "STORE_RUT"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""					
			gblsStoreRUT = sTmp			
		Else
			Call logInfo(ERROR_LOG_FILE_NAME, "STORE_RUT not specified", TRUE, TRUE)
			ErrorMessage "STORE_RUT no especificado en ", sFileName_
		EndIf

	ElseIf	sTmp = "STORE_ADDRESS"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""					
			gblsStoreAddress = sTmp			
		Else
			Call logInfo(ERROR_LOG_FILE_NAME, "STORE_ADDRESS not specified", TRUE, TRUE)
			ErrorMessage "STORE_ADDRESS no especificado en ", sFileName_
		EndIf

	ElseIf	sTmp = "GEOCOM_TENDER_CREDIT_MAP"

		Var objNum 		:N9
		Var issuerCode 	:N9
		Var name 		:A64
		Var count 		:N9 = 0
		
		For i = 1 To MAX_TENDER_MAP			
			// get value (should always be found below the key)
			FReadLn fn_, sTmp

			If Trim(sTmp) = "END_GEOCOM_TENDER_CREDIT_MAP"
				Break
			EndIf
			
			Split sTmp, ":", issuerCode, objNum, name
			
			If(objNum <> 0)		
				count = count + 1	
				
				gblsGeocomCreditIssuerCode[count] = issuerCode
				gbliGeocomCreditMappedTndrObjNum[count] = objNum 
				Format gbliGeocomCreditMappedName[count] As name			
			EndIf
			
		EndFor

	ElseIf	sTmp = "GEOCOM_TENDER_DEBIT_MAP"

		Var objNum 		:N9
		Var issuerCode 	:N9
		Var name 		:A64
		Var count 		:N9 = 0

		For i = 1 To MAX_TENDER_MAP
			// get value (should always be found below the key)
			FReadLn fn_, sTmp

			If Trim(sTmp) = "END_GEOCOM_TENDER_DEBIT_MAP"
				Break
			EndIf

			Split sTmp, ":", issuerCode, objNum, name
			
			If(objNum <> 0)		
				count = count + 1	
				
				gblsGeocomDebitIssuerCode[count] = issuerCode
				gbliGeocomDebitMappedTndrObjNum[count] = objNum 
				Format gbliGeocomDebitMappedName[count] As name			
			EndIf

		EndFor

	ElseIf	sTmp = "GEOCOM_ACQUIRER_MAP"

		For i = 1 To MAX_TENDER_MAP			
			// get value (should always be found below the key)
			FReadLn fn_, sTmp

			If Trim(sTmp) = "END_GEOCOM_ACQUIRER_MAP"
				Break
			EndIf
	
			Split sTmp, ":", gblsGeocomAcquirerName[i], gblsGeocomAcquirerCode[i]
			Format gblsGeocomAcquirerName[i] As Trim(gblsGeocomAcquirerName[i])
			
		EndFor

	ElseIf	sTmp = "CURRENCY"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""
			
			gblsCurrency = sTmp
			
		Else
			Call LogInfo(ERROR_LOG_FILE_NAME, "CURRENCY not specified", TRUE, TRUE)
			ErrorMessage "CURRENCY no especificado en ", sFileName_
		EndIf
				
	ElseIf	sTmp = "TIMEOUT"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""
			
			gbliTimeout = sTmp
			
		Else
			Call LogInfo(ERROR_LOG_FILE_NAME, "TIMEOUT not specified", TRUE, TRUE)
			ErrorMessage "TIMEOUT no especificado en ", sFileName_
		EndIf
				
	ElseIf	sTmp = "VOUCHER_PRINTER"

		// get value (should always be found below the key)
		FReadLn fn_, sTmp
		
		// check its validity
		If Trim(sTmp) <> ""
			
			// Turn on or off Unit price flag
			gbliSelectedPrinterIndex = sTmp
			
		Else
			Call logInfo(ERROR_LOG_FILE_NAME,"VOUCHER_PRINTER not specified",TRUE,TRUE)
			ErrorMessage "VOUCHER_PRINTER not specified in ", sFileName_
		EndIf

	EndIf

EndSub

//******************************************************************
// Procedure: 	ShowErrorMessage()
// Author: 		Luis Vaccaro
//******************************************************************
Sub ShowErrorMessage(Var errorCode_ :N9,  Var posErrorCode_ :A16, Var posErrorCodeExt_ :A16)
     
    Var iVisitFreq 	:N9
    Var rows 		:N9
    Var row 		:N9
    Var sTmp 		:A80
    Var iAvailPts 	:N9
    Var iExpiredPts :N9
    	
	If(errorCode_ = CONNECTION_ERROR)
		ErrorMessage "Error de conexion con REQ SERVER" 
	EndIf
    		
	If(errorCode_ = PARAM_ERROR)
		ErrorMessage "Error de parametros en comando a REQ SERVER" 
	EndIf

	If(errorCode_ = TIMEOUT_ERROR)
		ErrorMessage "Error de tiempo de espera de respuesta desde REQ SERVER" 
	EndIf

	If(errorCode_ = CHECKSUM_ERROR)
		ErrorMessage "Error de checksum en mensaje desde REQ SERVER" 
	EndIf
	
	If(errorCode_ <> EXECUTION_OK)
		Format sTmp As "Error Code = ", errorCode_
		Call LogInfo(ERROR_LOG_FILE_NAME, sTmp, TRUE, TRUE)	
	EndIf
		
	If(posErrorCode_ <> "" And posErrorCode_ <> "00")
		Format sTmp As "POS Error Code = ", posErrorCode_, " EXT = ", posErrorCodeExt_ 
		ErrorMessage sTmp 
		Call LogInfo(ERROR_LOG_FILE_NAME, sTmp, TRUE, TRUE)		
	EndIf	 

EndSub

//******************************************************************
// Procedure: logInfo()
//******************************************************************
Sub LogInfo(Var sFileName_ :A100, Var sInfo_ :A3000, Var iAppend_ :N1, Var iAddTimeStamp_ :N1)

	Var fn			: N5  // file handle
	Var sTmpInfo	: A3100

	
	If iAppend_
		// append info to log file
		FOpen fn, sFileName_, append
	Else
		// overwrite existing info
		FOpen fn, sFileName_, write
	EndIf

	If fn <> 0
		
		If iAddTimeStamp_
			// add a time stamp to the record
			Format sTmpInfo As @MONTH{02}, "/", @DAY{02}, "/", (@YEAR + 2000){04}, 			\
							   " - ", @HOUR{02}, ":", @MINUTE{02}, ":", @SECOND{02}, 		\
								" | VER: ", IFC_VERSION, " | WSID: ", @WSID, " | Emp: ", 	\
							   @CKEMP, " | Chk: ", @CKNUM, " -> ", Trim(Mid(sInfo_, 1, 3000))

		Else
			// only log passed info
			Format sTmpInfo As "WSID: ", @WSID, " -> ", Trim(Mid(sInfo_, 1, 3000))

		EndIf

		// write info to log file
		FWrite fn, Trim(Mid(sTmpInfo, 1, 2048))
		
		If(Len(sTmpInfo) > 2048)
			FWrite fn, Trim(Mid(sTmpInfo, 2049, 3000))
		EndIf

		// close handle to file
		FClose fn
	Else
		// error! Warn user
		ErrorMessage "Could not log information in ", sFileName_

	EndIf

EndSub

//******************************************************************
// Procedure to PromptYesOrNo
//******************************************************************
Sub PromptYesOrNo(Ref intReturnvalue, Var strprompt : A50)
	
	Var keypress	: Key
	Var data		: A2

	ErrorBeep
	ClearIslTs
		SetIslTsKeyX  1,  1, 12, 15, 7, @KEY_ENTER, 10059, "L", 4, "Si"
		SetIslTsKeyX  1, 16, 12, 15, 7, @KEY_CLEAR, 10058, "L", 2, "No"
	DisplayIslTs

	Inputkey keypress, data, strprompt
	ClearIslTs //clear the touchscreen
	intReturnValue = keypress = @KEY_ENTER
	
EndSub

//******************************************************************
// Procedure: LoadCustomSettings()
//******************************************************************
Sub LoadCustomSettings()

	Var fn			: N5
	Var sLineInfo	: A1024
	Var sFileName	: A100
			
	// Check for WS configuration file. If it doesn't exist,
	// use "master" configuration file
	FOpen fn, CONFIGURATION_FILE_NAME_PWS, read
	If fn = 0
		FOpen fn, CONFIGURATION_FILE_NAME, Read
		Format sFileName As CONFIGURATION_FILE_NAME
	Else
		Format sFileName As CONFIGURATION_FILE_NAME_PWS
	EndIf
		
	If fn <> 0 
		While Not Feof(fn)
			FReadLn fn, sLineInfo

			// process currently read information
			Call setCustomSetting(sLineInfo,fn,sFileName)
		EndWhile

		FClose fn
	Else
		// Couldn't open configuration file!
		Call LogInfo(ERROR_LOG_FILE_NAME, "Configuration file not found", TRUE, TRUE)
		ErrorMessage "Archivo de configuracion no encontrado!"
	EndIf

EndSub
