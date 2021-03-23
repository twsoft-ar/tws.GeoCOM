using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using tws.geoitd;
using TWS.GeoCOM.Payment.GeoITDClientSOAP;

namespace TestGEOITDClient
{
    class Program
    {
        static void Main(string[] args)
        {
            POSInterfaceServiceClient svc = new POSInterfaceServiceClient();
            svc.ChannelFactory.Endpoint.ListenUri = new Uri("http://geoitddev.geocom.com.uy:8554/v2/itdservice");

            PurchaseRequest pr = new PurchaseRequest();

            pr.SystemId = "F3D5877B-3C08-488C-BE97-907444042490";
            pr.PosID = "43113460";
            pr.Branch = "LOCAL 1";
            pr.ClientAppId = "WS 001";
            pr.UserId = "LUIS";
            pr.TransactionDateTimeyyyyMMddHHmmssSSS = DateTime.Now.ToString("yyyyMMddHHmmssfff");
            pr.InvoiceAmount = "12200";
            pr.Amount = "12200";
            pr.TaxableAmount = "10000";
            pr.TipAmount = "1220";
            pr.Quotas = 1;
            pr.Plan = 1;
            pr.Currency = "858";
            pr.TaxRefund = 0;

            GeoITDClient client = new GeoITDClient();

            PurchaseQueryResponse purchaseStatus;

            bool bVal;
            long transactionId = 0;
/*
            bVal = client.Purchase(pr, out transactionId, out purchaseStatus);

            ReverseRequest revReq = new ReverseRequest();
            revReq.PosID = pr.PosID;
            revReq.SystemId = pr.SystemId;
            revReq.Branch = pr.Branch;
            revReq.ClientAppId = pr.ClientAppId;
            revReq.UserId = pr.UserId;
            revReq.TransactionId = transactionId;
            revReq.STransactionId = transactionId.ToString();

            //int code = -1;
            //bVal = client.Reverse(revReq, out code);

            PurchaseVoidRequest pvr = new PurchaseVoidRequest()
            {
                ClientAppId = pr.ClientAppId,
                UserId = pr.UserId,
                TransactionDateTimeyyyyMMddHHmmssSSS = DateTime.Now.ToString("yyyyMMddHHmmssfff"),
                TicketNumber = purchaseStatus.Ticket,
                Acquirer = purchaseStatus.Acquirer.ToString(),

            };*/

            //bVal = client.PurchaseVoid(pvr, out purchaseStatus);

            PurchaseRefundRequest prr = new PurchaseRefundRequest()
            {
                ClientAppId = pr.ClientAppId,
                UserId = pr.UserId,
                TransactionDateTimeyyyyMMddHHmmssSSS = DateTime.Now.ToString("yyyyMMddHHmmssffff"),
                TicketNumber = "0022",
                OriginalTransactionDateyyMMdd = DateTime.Now.ToString("yyMMdd"),
                Amount = "12200",
                Currency = "858",
                Quotas = 1,
                Plan = 1,
                TaxableAmount = "10000",
                TaxRefund = 0,
                InvoiceAmount = pr.InvoiceAmount,
            };

            bVal = client.PurchaseRefund(prr, out purchaseStatus);

            /*
            var response = svc.processFinancialPurchase(pr);

            bool keepReading = true;
            while (keepReading)
            {
                tws.geoitd.GeoITDClientSOAP.PurchaseQueryRequest pqr = new tws.geoitd.GeoITDClientSOAP.PurchaseQueryRequest();
                pqr.SystemId = pr.SystemId;
                pqr.PosID = pr.PosID;
                pqr.Branch = pr.Branch;
                pqr.ClientAppId = pr.ClientAppId;
                pqr.UserId = pr.UserId;
                pqr.TransactionDateTimeyyyyMMddHHmmssSSS = pr.TransactionDateTimeyyyyMMddHHmmssfff;
                pqr.TransactionId = response.TransactionId;
                pqr.STransactionId = response.STransactionId;

                purchaseState = svc.processFinancialPurchaseQuery(pqr);

                keepReading = (purchaseState.ResponseCode == 10 || purchaseState.ResponseCode == 12);
                Thread.Sleep(100);
            }*/
        }
    }
}
