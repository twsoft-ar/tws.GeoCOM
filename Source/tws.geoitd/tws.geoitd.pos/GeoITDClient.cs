using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using TWS.GeoCOM.Payment.GeoITDClientSOAP;
using TWS.GeoCOM.Payment.Properties;

namespace tws.geoitd
{
    public class GeoITDClient
    {

        private static readonly NLog.Logger LOG = NLog.LogManager.GetCurrentClassLogger();
        public delegate int GeoITDDelegate(out long transactionID_);

        POSInterfaceServiceClient mPOSClient = new POSInterfaceServiceClient();

        public GeoITDClient()
        {
            mPOSClient.ChannelFactory.Endpoint.ListenUri = new Uri(Settings.Default.GeoITD_URL);
        }

        /*public bool Purchase(PurchaseRequest request_, out PurchaseQueryResponse response_)
        {
            LOG.Debug("ENTER");

            bool retVal = false;
            response_ = null;

            try
            {
                tws.geoitd.GeoITDClientSOAP.POSInterfaceServiceClient svc = new tws.geoitd.GeoITDClientSOAP.POSInterfaceServiceClient();
                svc.ChannelFactory.Endpoint.ListenUri = new Uri("http://geoitddev.geocom.com.uy:8554/v2/itdservice");

                //tws.geoitd.GeoITDClientSOAP.PurchaseRequest pr = new tws.geoitd.GeoITDClientSOAP.PurchaseRequest();

                request_.SystemId = Settings.Default.GeoITD_SystemID;
                request_.PosID = Settings.Default.GeoITD_PosID;
                request_.Branch = Settings.Default.GeoITD_Branch;

                var purchaseResponse = svc.processFinancialPurchase(request_);

                tws.geoitd.GeoITDClientSOAP.PurchaseQueryResponse purchaseStatus = new PurchaseQueryResponse();
                bool keepReading = true;
                while (keepReading)
                {
                    tws.geoitd.GeoITDClientSOAP.PurchaseQueryRequest pqr = new tws.geoitd.GeoITDClientSOAP.PurchaseQueryRequest();
                    pqr.SystemId = request_.SystemId;
                    pqr.PosID = request_.PosID;
                    pqr.Branch = request_.Branch;
                    pqr.ClientAppId = request_.ClientAppId;
                    pqr.UserId = request_.UserId;
                    pqr.TransactionDateTimeyyyyMMddHHmmssSSS = request_.TransactionDateTimeyyyyMMddHHmmssSSS;
                    pqr.TransactionId = purchaseResponse.TransactionId;
                    pqr.STransactionId = purchaseResponse.STransactionId;

                    purchaseStatus = svc.processFinancialPurchaseQuery(pqr);

                    keepReading = (purchaseStatus.ResponseCode == 10 || purchaseStatus.ResponseCode == 12);
                    Thread.Sleep(100);
                }

                if (retVal = (purchaseStatus.ResponseCode == 0))
                    response_ = purchaseStatus;
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Debug("EXIT");
            }

            return retVal;
        }*/

        public bool Purchase(PurchaseRequest request_, out PurchaseResponse purchaseResponse_)
        {
            LOG.Debug("ENTER");

            bool retVal = false;
            purchaseResponse_ = null;

            try
            {
                purchaseResponse_ = mPOSClient.processFinancialPurchase(request_);
                retVal = (purchaseResponse_.ResponseCode == 0);
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Debug("EXIT");
            }

            return retVal;
        }

        public bool Reverse(ReverseRequest request_, out int responseCode_)
        {
            LOG.Debug("ENTER");

            bool retVal = false;
            responseCode_ = -1;

            try
            {
                POSInterfaceServiceClient svc = new POSInterfaceServiceClient();
                svc.ChannelFactory.Endpoint.ListenUri = new Uri("http://geoitddev.geocom.com.uy:8554/v2/itdservice");

                var reverseResponse = svc.processFinancialReverse(request_);
                responseCode_ = reverseResponse.ResponseCode;
                retVal = responseCode_ == 0;
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Debug("EXIT");
            }

            return retVal;
        }

        /*public bool PurchaseAnnulment(PurchaseVoidRequest request_, out PurchaseQueryResponse response_)
        {
            LOG.Debug("ENTER");

            bool retVal = false;
            response_ = null;

            try
            {
                tws.geoitd.GeoITDClientSOAP.POSInterfaceServiceClient svc = new tws.geoitd.GeoITDClientSOAP.POSInterfaceServiceClient();
                svc.ChannelFactory.Endpoint.ListenUri = new Uri("http://geoitddev.geocom.com.uy:8554/v2/itdservice");

                request_.SystemId = Settings.Default.GeoITD_SystemID;
                request_.PosID = Settings.Default.GeoITD_PosID;
                request_.Branch = Settings.Default.GeoITD_Branch;

                var purchaseResponse = svc.processFinancialPurchaseVoidByTicket(request_);

                if (purchaseResponse.ResponseCode != 0)
                    return false;

                    tws.geoitd.GeoITDClientSOAP.PurchaseQueryResponse purchaseStatus = new PurchaseQueryResponse();
                bool keepReading = true;
                while (keepReading)
                {
                    tws.geoitd.GeoITDClientSOAP.PurchaseQueryRequest pqr = new tws.geoitd.GeoITDClientSOAP.PurchaseQueryRequest();
                    pqr.SystemId = request_.SystemId;
                    pqr.PosID = request_.PosID;
                    pqr.Branch = request_.Branch;
                    pqr.ClientAppId = request_.ClientAppId;
                    pqr.UserId = request_.UserId;
                    pqr.TransactionDateTimeyyyyMMddHHmmssSSS = request_.TransactionDateTimeyyyyMMddHHmmssSSS;
                    pqr.TransactionId = purchaseResponse.TransactionId;
                    pqr.STransactionId = purchaseResponse.STransactionId;

                    purchaseStatus = svc.processFinancialPurchaseQuery(pqr);

                    keepReading = (purchaseStatus.ResponseCode == 10 || purchaseStatus.ResponseCode == 12);
                    Thread.Sleep(100);
                }

                if (retVal = (purchaseStatus.ResponseCode == 0))
                    response_ = purchaseStatus;
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Debug("EXIT");
            }

            return retVal;
        }
        */
        public bool PurchaseVoid(PurchaseVoidRequest request_, out PurchaseQueryResponse statusResponse_)
        {
            LOG.Debug("ENTER");

            bool retVal = false;
            statusResponse_ = null;

            try
            {
                var code = GeoITDOperationCall(
                    (out long trId_) =>
                    {
                        var resp = mPOSClient.processFinancialPurchaseVoidByTicket(request_);
                        trId_ = resp.TransactionId;
                        return resp.ResponseCode;
                    }, request_, out statusResponse_, out retVal);
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Debug("EXIT");
            }

            return retVal;
        }

        public bool PurchaseRefund(PurchaseRefundRequest request_, out PurchaseQueryResponse statusResponse_)
        {
            LOG.Debug("ENTER");

            bool retVal = false;
            statusResponse_ = null;

            try
            {
                var code = GeoITDOperationCall(
                    (out long trId_) =>
                    {
                        var resp = mPOSClient.processFinancialPurchaseRefund(request_);
                        trId_ = resp.TransactionId;
                        return resp.ResponseCode;
                    }, request_, out statusResponse_, out retVal);
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Debug("EXIT");
            }

            return retVal;
        }

        public bool QueryTransactionStatus(PurchaseQueryRequest request_, out PurchaseQueryResponse statusResponse_, bool waitForStatus_ = true)
        {
            LOG.Debug("ENTER");

            bool retVal = false;
            statusResponse_ = null;

            try
            {
                PurchaseQueryResponse purchaseStatus = new PurchaseQueryResponse();
                bool keepReading = true;
                while (keepReading)
                {
                    purchaseStatus = mPOSClient.processFinancialPurchaseQuery(request_);

                    keepReading = (purchaseStatus.ResponseCode == 10 || purchaseStatus.ResponseCode == 12) && waitForStatus_;
                    Thread.Sleep(100);
                }

                retVal = purchaseStatus.ResponseCode == 0 &&
                           (purchaseStatus.PosResponseCode == "00" ||
                            purchaseStatus.PosResponseCode == "08" ||
                            purchaseStatus.PosResponseCode == "10" ||
                            purchaseStatus.PosResponseCode == "11" ||
                            purchaseStatus.PosResponseCode == "85" ||
                            purchaseStatus.PosResponseCode == "OF" ||
                            purchaseStatus.PosResponseCode == "Y1" ||
                            purchaseStatus.PosResponseCode == "Y3");

                statusResponse_ = purchaseStatus;
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Debug("EXIT");
            }

            return retVal;
        }

        //private int GeoITDOperationCall(GeoITDDelegate geoITDFunc_, Request request_, out PurchaseQueryResponse statusResponse_, out bool approved_)
        //{
        //    LOG.Debug("ENTER");

        //    int retVal = -1;
        //    statusResponse_ = null;
        //    approved_ = false;

        //    try
        //    {
        //        request_.SystemId = Settings.Default.GeoITD_SystemID;
        //        request_.PosID = Settings.Default.GeoITD_PosID;
        //        request_.Branch = Settings.Default.GeoITD_Branch;

        //        long transactionID;
        //        if(geoITDFunc_(out transactionID) != 0)
        //            return retVal;

        //        PurchaseQueryResponse purchaseStatus = new PurchaseQueryResponse();
        //        bool keepReading = true;
        //        while (keepReading)
        //        {
        //            PurchaseQueryRequest pqr = new PurchaseQueryRequest
        //            {
        //                SystemId = request_.SystemId,
        //                PosID = request_.PosID,
        //                Branch = request_.Branch,
        //                ClientAppId = request_.ClientAppId,
        //                UserId = request_.UserId,
        //                TransactionDateTimeyyyyMMddHHmmssSSS = request_.TransactionDateTimeyyyyMMddHHmmssSSS,
        //                TransactionId = transactionID
        //            };

        //            purchaseStatus = mPOSClient.processFinancialPurchaseQuery(pqr);

        //            keepReading = (purchaseStatus.ResponseCode == 10 || purchaseStatus.ResponseCode == 12);
        //            Thread.Sleep(100);
        //        }

        //        //if ((retVal = purchaseStatus.ResponseCode) == 0)

        //        approved_ = purchaseStatus.ResponseCode == 0 &&
        //                   (purchaseStatus.PosResponseCode == "00" ||
        //                    purchaseStatus.PosResponseCode == "08" ||
        //                    purchaseStatus.PosResponseCode == "10" ||
        //                    purchaseStatus.PosResponseCode == "11" ||
        //                    purchaseStatus.PosResponseCode == "85" ||
        //                    purchaseStatus.PosResponseCode == "OF" ||
        //                    purchaseStatus.PosResponseCode == "Y1" ||
        //                    purchaseStatus.PosResponseCode == "Y3");

        //        statusResponse_ = purchaseStatus;
        //        retVal = purchaseStatus.ResponseCode;
        //    }
        //    catch (Exception ex)
        //    {
        //        LOG.Fatal(ex, "{Message}", "Exception caught.");
        //    }
        //    finally
        //    {
        //        LOG.Debug("EXIT");
        //    }

        //    return retVal;
        //}

        private int GeoITDOperationCall(GeoITDDelegate geoITDFunc_, Request request_, out PurchaseQueryResponse statusResponse_, out bool approved_)
        {
            LOG.Debug("ENTER");

            int retVal = -1;
            statusResponse_ = null;
            approved_ = false;

            try
            {
                long transactionID;
                if (geoITDFunc_(out transactionID) != 0)
                    return retVal;

                //retVal = purchaseStatus.ResponseCode;
            }
            catch (Exception ex)
            {
                LOG.Fatal(ex, "{Message}", "Exception caught.");
            }
            finally
            {
                LOG.Debug("EXIT");
            }

            return retVal;
        }
    }
}
