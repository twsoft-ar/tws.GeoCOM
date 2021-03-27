using System;
using System.Globalization;
using System.Net.Sockets;
using tws.geoitd;
using TWS.GeoCOM.Payment;
using TWS.GeoCOM.Payment.GeoITDClientSOAP;
using TWS.Marshaling;
using TWS.Networking;

namespace TWS.RES.GeoCOM
{
    public class RESGeoITDReqInstance : ReqInstance
    {
        private static readonly NLog.Logger LOG = NLog.LogManager.GetCurrentClassLogger();

        enum GEOITD_MSG { PURCHASE = 1, REVERSE = 2, PURCHASE_VOID= 3, PURCHASE_REFUND = 4, QUERY_REQUEST = 5, QUERY_REQUEST_NOWAIT = 6 };

        public RESGeoITDReqInstance(Socket socket_) : base(socket_)
        {
        }

        protected RESGeoITDReqInstance()
        {
        }

        protected override ReqMessage ProcessIncomingRequest(ReqMessage msg_)
        {
            ReqMessage retVal = new ReqMessage(null);

            switch (msg_.MessageType)
            {
                case (int)GEOITD_MSG.PURCHASE:
                    retVal = ProcessGeoITDPruchase(msg_);
                    break;

                case (int)GEOITD_MSG.REVERSE:
                    //retVal = ProcessCancelOrder(msg_);
                    break;

                case (int)GEOITD_MSG.PURCHASE_VOID:
                    retVal = ProcessGeoITDPruchaseVoid(msg_);
                    break;

                case (int)GEOITD_MSG.PURCHASE_REFUND:
                    retVal = ProcessGeoITDPruchaseRefund(msg_);
                    break;

                case (int)GEOITD_MSG.QUERY_REQUEST:
                    retVal = ProcessGeoITDQueryStatus(msg_);
                    break;

                case (int)GEOITD_MSG.QUERY_REQUEST_NOWAIT:
                    retVal = ProcessGeoITDQueryStatus(msg_, false);
                    break;

                default:
                    LOG.Info("{Message}", $"Unknown Message type -> { msg_.MessageType} ID received.");
                    break;
            }

            return retVal;
        }
        
        private ReqMessage ProcessGeoITDPruchase(ReqMessage reqMsg_)
        {
            LOG.Trace("ENTER");

            ReqMessage retVal = new ReqMessage(null);

            try
            {
                string jsonBody = ByteStream.PByteToPrimitive(reqMsg_.Body, 0, typeof(string)).ToString();

                GeoITDPurchaseRequest purchaseRequest = GeoITDPurchaseRequest.DeserializeJson(jsonBody);

                GeoITDClient geoITDClient = new GeoITDClient();

                string strAux = "";

                LOG.Info("{Message}", $"Before calling Purchase(), REQUEST:\r\n{jsonBody}");

                PurchaseResponse response;
                if (geoITDClient.Purchase(GeoITDPurchaseRequest.ToPurchaseRequest(purchaseRequest), out response))
                {
                    strAux = $"response_code={response.ResponseCode}|" +
                             $"transaction_id={response.TransactionId}";
                }
                else
                {
                    strAux = $"response_code={(response == null? -1 : response.ResponseCode)}";
                }

                retVal.MessageType = reqMsg_.MessageType;
                retVal.Body = ByteStream.ToPByte(strAux);
                retVal.BodySize = retVal.Body.Length;
                retVal.Checksum = retVal.GenerateChecksum();

                LOG.Info("{Message}", $"After calling Purchase(), RESPONSE:\r\n{strAux}");
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Trace("EXIT");
            }

            return retVal;
        }

        private ReqMessage ProcessGeoITDPruchaseVoid(ReqMessage reqMsg_)
        {
            LOG.Trace("ENTER");

            ReqMessage retVal = new ReqMessage(null);

            try
            {
                string jsonBody = ByteStream.PByteToPrimitive(reqMsg_.Body, 0, typeof(string)).ToString();

                GeoITDPurchaseRequest purchaseRequest = GeoITDPurchaseRequest.DeserializeJson(jsonBody);

                GeoITDClient geoITDClient = new GeoITDClient();
                //(ConfigMgr.Instance.MercadoPagoAPIURL, ConfigMgr.Instance.MercadoLibreAPIURL, ConfigMgr.Instance.MercadoLibreAPIAccessTOKEN);

                string strAux = "";
                long transactionId = 0;
                PurchaseQueryResponse queryResponse;

                LOG.Info("{Message}", $"Before calling Purchase(), REQUEST:\r\n{jsonBody}");

                if (geoITDClient.PurchaseVoid(GeoITDPurchaseRequest.ToPurchaseVoidRequest(purchaseRequest), out queryResponse))
                {
                    strAux = $"response_code={queryResponse.ResponseCode}|" +
                             $"pos_response_code={queryResponse.PosResponseCode}|" +
                             $"pos_response_code_ext={queryResponse.PosResponseCodeExtension}|" +
                             $"transaction_id={transactionId}|" +
                             $"ticket={queryResponse.Ticket}|" +
                             $"authorization_code={queryResponse.AuthorizationCode}|" +
                             $"issuer={queryResponse.Issuer}|" +
                             $"card_number={queryResponse.CardNumber}|" +
                             $"expiration_date={queryResponse.ExpirationDate}|" +
                             $"transaction_datetime={queryResponse.TransactionDate} {queryResponse.TransactionHour}";
                }
                else
                {
                    strAux = $"response_code={queryResponse.ResponseCode}";
                }

                retVal.MessageType = reqMsg_.MessageType;
                retVal.Body = ByteStream.ToPByte(strAux);
                retVal.BodySize = retVal.Body.Length;
                retVal.Checksum = retVal.GenerateChecksum();

                LOG.Info("{Message}", $"After calling Purchase(), RESPONSE:\r\n{strAux}");
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Trace("EXIT");
            }

            return retVal;
        }

        private ReqMessage ProcessGeoITDPruchaseRefund(ReqMessage reqMsg_)
        {
            LOG.Trace("ENTER");

            ReqMessage retVal = new ReqMessage(null);

            try
            {
                string jsonBody = ByteStream.PByteToPrimitive(reqMsg_.Body, 0, typeof(string)).ToString();

                GeoITDPurchaseRequest purchaseRequest = GeoITDPurchaseRequest.DeserializeJson(jsonBody);

                GeoITDClient geoITDClient = new GeoITDClient();
                //(ConfigMgr.Instance.MercadoPagoAPIURL, ConfigMgr.Instance.MercadoLibreAPIURL, ConfigMgr.Instance.MercadoLibreAPIAccessTOKEN);

                string strAux = "";
                long transactionId = 0;
                PurchaseQueryResponse queryResponse;

                LOG.Info("{Message}", $"Before calling Purchase(), REQUEST:\r\n{jsonBody}");

                if (geoITDClient.PurchaseRefund(GeoITDPurchaseRequest.ToPurchaseRefundRequest(purchaseRequest), out queryResponse))
                {
                    strAux = $"response_code={queryResponse.ResponseCode}|" +
                             $"pos_response_code={queryResponse.PosResponseCode}|" +
                             $"pos_response_code_ext={queryResponse.PosResponseCodeExtension}|" +
                             $"transaction_id={transactionId}|" +
                             $"ticket={queryResponse.Ticket}|" +
                             $"authorization_code={queryResponse.AuthorizationCode}|" +
                             $"issuer={queryResponse.Issuer}|" +
                             $"card_number={queryResponse.CardNumber}|" +
                             $"expiration_date={queryResponse.ExpirationDate}|" +
                             $"transaction_datetime={queryResponse.TransactionDate} {queryResponse.TransactionHour}";
                }
                else
                {
                    strAux = $"response_code={queryResponse.ResponseCode}";
                }

                retVal.MessageType = reqMsg_.MessageType;
                retVal.Body = ByteStream.ToPByte(strAux);
                retVal.BodySize = retVal.Body.Length;
                retVal.Checksum = retVal.GenerateChecksum();

                LOG.Info("{Message}", $"After calling Purchase(), RESPONSE:\r\n{strAux}");
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Trace("EXIT");
            }

            return retVal;
        }
        
        private ReqMessage ProcessGeoITDQueryStatus(ReqMessage reqMsg_, bool waitForStatus = true)
        {
            LOG.Trace("ENTER");

            ReqMessage retVal = new ReqMessage(null);

            try
            {
                string jsonBody = ByteStream.PByteToPrimitive(reqMsg_.Body, 0, typeof(string)).ToString();

                GeoITDPurchaseQueryRequest queryRequest = GeoITDPurchaseQueryRequest.DeserializeJson(jsonBody);

                GeoITDClient geoITDClient = new GeoITDClient();

                string strAux = "";
                PurchaseQueryResponse queryResponse;

                LOG.Info("{Message}", $"Before calling ProcessGeoITDQueryStatus(), REQUEST:\r\n{jsonBody}");

                if (geoITDClient.QueryTransactionStatus(GeoITDPurchaseQueryRequest.ToPurchaseQueryRequest(queryRequest), out queryResponse, waitForStatus))
                {
                    strAux = $"response_code={queryResponse.ResponseCode}|" +
                             $"pos_response_code={queryResponse.PosResponseCode}|" +
                             $"pos_response_code_ext={queryResponse.PosResponseCodeExtension}|" +
                             $"ticket={queryResponse.Ticket}|" +
                             $"authorization_code={queryResponse.AuthorizationCode}|" +
                             $"issuer={queryResponse.Issuer}|" +
                             $"card_number={queryResponse.CardNumber}|" +
                             $"expiration_date={queryResponse.ExpirationDate}|" +
                             $"transaction_date={DateTime.ParseExact($"{queryResponse.TransactionDate}", "yyMMdd", CultureInfo.InvariantCulture):dd/MM/yyyy}|" +
                             $"transaction_time={DateTime.ParseExact($"{queryResponse.TransactionHour}", "HHmmss", CultureInfo.InvariantCulture):HH:mm}|" +
                             $"EMV_application_id={queryResponse.EmvApplicationId}|" +
                             $"EMV_application_name={queryResponse.EmvApplicationName}|" +
                             $"transaction_type={queryResponse.TransactionType}|" +
                             $"origin_card_type={queryResponse.OriginCardType}|" +
                             $"batch={queryResponse.Batch}|" +
                             $"acquirer={queryResponse.Acquirer}|" +
                             $"merchant={queryResponse.Merchant}|" +
                             $"input_mode={queryResponse.InputMode}|" +
                             $"card_owner_name={queryResponse.CardOwnerName}";
                }
                else
                {
                    strAux = $"response_code={queryResponse.ResponseCode}";
                }

                retVal.MessageType = reqMsg_.MessageType;
                retVal.Body = ByteStream.ToPByte(strAux);
                retVal.BodySize = retVal.Body.Length;
                retVal.Checksum = retVal.GenerateChecksum();

                LOG.Info("{Message}", $"After calling ProcessGeoITDQueryStatus(), RESPONSE:\r\n{strAux}");
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Trace("EXIT");
            }

            return retVal;
        }

        /*
        private ReqMessage ProcessSaleOrder(ReqMessage reqMsg_)
        {
            ReqMessage retVal = new ReqMessage(null);

            try
            {
                string jsonBody = ByteStream.PByteToPrimitive(reqMsg_.Body, 0, typeof(string)).ToString();

                SaleOrderRequest saleOrder = JsonConvert.DeserializeObject<SaleOrderRequest>(jsonBody);
                SaleId saleID = JsonConvert.DeserializeObject<SaleId>(jsonBody);

                MPQRClient mpClient = new MPQRClient(ConfigMgr.Instance.MercadoPagoAPIURL, ConfigMgr.Instance.MercadoLibreAPIURL, ConfigMgr.Instance.MercadoLibreAPIAccessTOKEN);

                SaleOrderResponse saleResponse;
                string apiResponse;

                LOG.Instance.LogEvent("In ProcessSaleOrder(). Before calling GenerateSaleOrder(). Colletor ID=" + saleID.collector_id.ToString() + ". POS ID=" + saleID.pos_id.ToString() + ". SALE ORDER:\r\n"  + jsonBody, VERBOSITY_LEVEL.INFO);

                mpClient.GenerateSaleOrder(saleID.collector_id, saleID.pos_id, saleOrder, out saleResponse, out apiResponse);

                string strAux = "error_code=" + apiResponse + "|" + 
                                "id=" + saleResponse.id + "|" +
                                "external_reference=" + saleResponse.external_reference + "|" +
                                "total_amount=" + saleResponse.total_amount.ToString() + "|" +
                                "sale_order_response=" + JsonConvert.SerializeObject(saleResponse) + "\r\n";

                retVal.MessageType = reqMsg_.MessageType;
                retVal.Body = ByteStream.ToPByte(strAux);
                retVal.BodySize = retVal.Body.Length;
                retVal.Checksum = retVal.GenerateChecksum();

                LOG.Instance.LogEvent("In ProcessSaleOrder(). After calling GenerateSaleOrder(). RESPONSE:\r\n" + strAux, VERBOSITY_LEVEL.INFO);
            }
            catch (Exception ex)
            {
                LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In TWS.RES.MP.RESQRReqInstance.ProcessSaleOrder() Exception caught: " + ex.Message, VERBOSITY_LEVEL.FATAL);
            }

            return retVal;
        }

        private ReqMessage ProcessCancelOrder(ReqMessage reqMsg_) 
        {
            ReqMessage retVal = new ReqMessage(null);

            try
            {
                string jsonBody = ByteStream.PByteToPrimitive(reqMsg_.Body, 0, typeof(string)).ToString();
                SaleId saleID = JsonConvert.DeserializeObject<SaleId>(jsonBody);

                GeoITDClient mpClient = new GeoITDClient();
                //ConfigMgr.Instance.MercadoPagoAPIURL, ConfigMgr.Instance.MercadoLibreAPIURL, ConfigMgr.Instance.MercadoLibreAPIAccessTOKEN);

                string apiResponse;

                LOG.Instance.LogEvent("In ProcessCancelOrder(). Before calling CancelOrder(). Colletor ID=" + saleID.collector_id.ToString() + ". POS ID=" + saleID.pos_id.ToString(), VERBOSITY_LEVEL.INFO);

                mpClient.CancelOrder(saleID.collector_id, saleID.pos_id, out apiResponse);

                string strAux = "error_code=" + apiResponse;

                retVal.MessageType = reqMsg_.MessageType;
                retVal.Body = ByteStream.ToPByte(strAux);
                retVal.BodySize = retVal.Body.Length;
                retVal.Checksum = retVal.GenerateChecksum();

                LOG.Instance.LogEvent("In ProcessCancelOrder(). After calling CancelOrder(). RESPONSE:\r\n" + strAux, VERBOSITY_LEVEL.INFO);
            }
            catch (Exception ex)
            {
                LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In TWS.RES.MP.RESQRReqInstance.ProcessCancelOrder() Exception caught: " + ex.Message, VERBOSITY_LEVEL.FATAL);
            }

            return retVal;
        }

        private ReqMessage ProcessPaymentSearch(ReqMessage reqMsg_)
        {
            ReqMessage retVal = new ReqMessage(null);

            try
            {
                string jsonBody = ByteStream.PByteToPrimitive(reqMsg_.Body, 0, typeof(string)).ToString();

                PaymentRequest payment = JsonConvert.DeserializeObject<PaymentRequest>(jsonBody);

                MPQRClient mpClient = new MPQRClient(ConfigMgr.Instance.MercadoPagoAPIURL, ConfigMgr.Instance.MercadoPagoAPIURL, ConfigMgr.Instance.MercadoLibreAPIAccessTOKEN);

                PaymentResponse paymentResponse;
                string apiResponse;

                LOG.Instance.LogEvent("In ProcessPaymentSearch(). Before calling PaymentSearch(). External Ref.=" + payment.external_reference, VERBOSITY_LEVEL.INFO);
                mpClient.PaymentSearch(payment.external_reference, out paymentResponse, out apiResponse);

                Result resultToSend = paymentResponse.results.FirstOrDefault(item => item.status == "approved");
                if (resultToSend  == null && paymentResponse.paging.total > 0)
                    resultToSend = paymentResponse.results[paymentResponse.paging.total - 1];

                string strAux = "error_code="   + apiResponse + "|" +
                                "id="           + (resultToSend != null ? resultToSend.id : "0") + "|" +
                                "order_id="     + (resultToSend != null ? resultToSend.order.id : "0") + "|" +
                                "order_type="   + (resultToSend != null ? resultToSend.order.type : "0") + "|" +
                                "status="       + (resultToSend != null ? resultToSend.status : "0") + "|" +
                                "collector_id=" + (resultToSend != null ? resultToSend.collector_id : "0") + "|" +
                                "payment_search_response=" + JsonConvert.SerializeObject(paymentResponse) + "\r\n";

                retVal.MessageType = reqMsg_.MessageType;
                retVal.Body = ByteStream.ToPByte(strAux);
                retVal.BodySize = retVal.Body.Length;
                retVal.Checksum = retVal.GenerateChecksum();

                LOG.Instance.LogEvent("In ProcessPaymentSearch(). After calling PaymentSearch(). RESPONSE:\r\n" + strAux, VERBOSITY_LEVEL.INFO);
            }
            catch (Exception ex)
            {
                LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In TWS.RES.MP.RESQRReqInstance.ProcessPaymentSearch() Exception caught: " + ex.Message, VERBOSITY_LEVEL.FATAL);
            }

            return retVal;
        }

        private ReqMessage GetPayment(ReqMessage reqMsg_)
        {
            ReqMessage retVal = new ReqMessage(null);

            try
            {
                string externalReference = ByteStream.PByteToPrimitive(reqMsg_.Body, 0, typeof(string)).ToString();

                MPQRClient mpClient = new MPQRClient(ConfigMgr.Instance.MercadoPagoAPIURL, ConfigMgr.Instance.MercadoLibreAPIURL, ConfigMgr.Instance.MercadoLibreAPIAccessTOKEN);

                string apiResponse;
                PaymentResponse paymentResponse;

                LOG.Instance.LogEvent("In GetPayment(). Before calling PaymentSearch(). External Ref.=" + externalReference, VERBOSITY_LEVEL.INFO);
                mpClient.PaymentSearch(externalReference, out paymentResponse, out apiResponse);

                string strAux = "Err: " + apiResponse + "|\r\n" + JsonConvert.SerializeObject(paymentResponse);

                retVal.MessageType = reqMsg_.MessageType;
                retVal.Body = ByteStream.ToPByte(strAux);
                retVal.BodySize = retVal.Body.Length;
                retVal.Checksum = retVal.GenerateChecksum();

                LOG.Instance.LogEvent("In GetPayment(). After calling PaymentSearch(). RESPONSE:\r\n" + strAux, VERBOSITY_LEVEL.INFO);
            }
            catch (Exception ex)
            {
                LOG.Instance.LogEvent(Assembly.GetExecutingAssembly().ManifestModule.FullyQualifiedName + ".log", "In TWS.RES.MP.RESQRReqInstance.GetPayment() Exception caught: " + ex.Message, VERBOSITY_LEVEL.FATAL);
            }

            return retVal;
        }*/
    }

    public class SaleId
    {
        public string collector_id { get; set; }
        public string pos_id { get; set; }
    }
}
