using System;
using System.Globalization;
using System.Text.Encodings.Web;
using System.Text.Json;
using System.Text.Json.Serialization;
using TWS.GeoCOM.Payment.GeoITDClientSOAP;

namespace TWS.GeoCOM.Payment
{
    public class GeoITDPurchaseRequest
    {
        [JsonPropertyName("pos_id")]
        public string PosID { get; set; }

        [JsonPropertyName("system_id")]
        public string SystemID { get; set; }

        [JsonPropertyName("branch")]
        public string Branch { get; set; }

        [JsonPropertyName("client_app_id")]
        public string ClientAppId { get; set; }

        [JsonPropertyName("user_id")]
        public string UserId { get; set; }

        [JsonPropertyName("transaction_date_time")]
        public string TransactionDatetime { get; set; }

        [JsonPropertyName("amount")]
        public string Amount { get; set; }

        [JsonPropertyName("installment")]
        public int Installment { get; set; }

        [JsonPropertyName("plan")]
        public int Plan { get; set; }

        [JsonPropertyName("currency")]
        public string Currency { get; set; }

        [JsonPropertyName("tax_refund")]
        public int TaxRefund { get; set; }

        [JsonPropertyName("taxable_amount")]
        public string TaxableAmount { get; set; }

        [JsonPropertyName("invoice_amount")]
        public string InvoiceAmount { get; set; }

        [JsonPropertyName("tip_amount")]
        public string TipAmount { get; set; }

        [JsonPropertyName("invoice_number")]
        public string InvoiceNumber { get; set; }

        [JsonPropertyName("original_ticket")]
        public string OriginalTicket { get; set; }

        [JsonPropertyName("original_transaction_date")]
        public string OriginalTransactionDate { get; set; }

        
        public static string SerializeJson(GeoITDPurchaseRequest purchaseReq_)
        {
            string retVal = "";
            retVal = JsonSerializer.Serialize<GeoITDPurchaseRequest>(purchaseReq_, SerializerOptions.Options);
            return retVal;
        }
        public static GeoITDPurchaseRequest DeserializeJson(string jsonString_)
        {
            GeoITDPurchaseRequest retVal = null;

            if (jsonString_ != null)
            {
                retVal = JsonSerializer.Deserialize<GeoITDPurchaseRequest>(jsonString_);
                retVal.NormalizeStrings();
            }

            return retVal;
        }

        public static PurchaseRequest ToPurchaseRequest(GeoITDPurchaseRequest src_)
        {
            PurchaseRequest retVal = new PurchaseRequest();

            try
            {
                retVal = new PurchaseRequest()
                {
                    PosID = src_.PosID,
                    SystemId = src_.SystemID,
                    Branch = src_.Branch,
                    ClientAppId = src_.ClientAppId,
                    UserId = src_.UserId,
                    Amount = src_.Amount,
                    Quotas = src_.Installment,
                    Plan = src_.Plan,
                    Currency = src_.Currency,
                    TaxRefund = src_.TaxRefund,
                    TaxableAmount = src_.TaxableAmount,
                    InvoiceAmount = src_.InvoiceAmount,
                    TipAmount = src_.TipAmount,
                    InvoiceNumber = src_.InvoiceNumber,
                    TransactionDateTimeyyyyMMddHHmmssSSS = src_.TransactionDatetime,
                };
            }
            catch
            {
            }

            return retVal;
        }
        public static PurchaseVoidRequest ToPurchaseVoidRequest(GeoITDPurchaseRequest src_)
        {
            PurchaseVoidRequest retVal = new PurchaseVoidRequest();

            try
            {
                retVal = new PurchaseVoidRequest()
                {
                    PosID = src_.PosID,
                    SystemId = src_.SystemID,
                    Branch = src_.Branch,
                    ClientAppId = src_.ClientAppId,
                    UserId = src_.UserId,
                    TicketNumber = src_.OriginalTicket,
                };
            }
            catch
            {
            }

            return retVal;
        }
        public static PurchaseRefundRequest ToPurchaseRefundRequest(GeoITDPurchaseRequest src_)
        {
            PurchaseRefundRequest retVal = new PurchaseRefundRequest();

            try
            {
                retVal = new PurchaseRefundRequest()
                {
                    PosID = src_.PosID,
                    SystemId = src_.SystemID,
                    Branch = src_.Branch,
                    ClientAppId = src_.ClientAppId,
                    UserId = src_.UserId,
                    OriginalTransactionDateyyMMdd = src_.OriginalTransactionDate,
                    TicketNumber = src_.OriginalTicket,
                    Amount = src_.Amount,
                    Quotas = src_.Installment,
                    Plan = src_.Plan,
                    Currency = src_.Currency,
                    TaxRefund = src_.TaxRefund,
                    TaxableAmount = src_.TaxableAmount,
                    InvoiceAmount = src_.InvoiceAmount,
                    InvoiceNumber = src_.InvoiceNumber,
                };
            }
            catch
            {
            }

            return retVal;
        }

        internal void NormalizeStrings()
        {
            PosID = PosID ?? "";
            SystemID = SystemID ?? "";
            Branch = Branch ?? "";
            ClientAppId = ClientAppId ?? "";
            UserId = UserId ?? "";
            Amount = Amount ?? "";
            Currency = Currency ?? "";
            TaxableAmount = TaxableAmount ?? "";
            InvoiceAmount = InvoiceAmount ?? "";
            TipAmount = TipAmount ?? "";
            InvoiceNumber = InvoiceNumber ?? "";
        }
    }

    public class GeoITDPurchaseQueryRequest
    {
        [JsonPropertyName("pos_id")]
        public string PosID { get; set; }

        [JsonPropertyName("system_id")]
        public string SystemID { get; set; }

        [JsonPropertyName("branch")]
        public string Branch { get; set; }

        [JsonPropertyName("client_app_id")]
        public string ClientAppId { get; set; }

        [JsonPropertyName("user_id")]
        public string UserId { get; set; }

        [JsonPropertyName("transaction_date_time")]
        public string TransactionDateTime { get; set; }

        [JsonPropertyName("transaction_id")]
        public long TransactionId { get; set; }


        public static string SerializeJson(GeoITDPurchaseQueryRequest purchaseReq_)
        {
            string retVal = "";
            retVal = JsonSerializer.Serialize<GeoITDPurchaseQueryRequest>(purchaseReq_, SerializerOptions.Options);
            return retVal;
        }
        public static GeoITDPurchaseQueryRequest DeserializeJson(string jsonString_)
        {
            GeoITDPurchaseQueryRequest retVal = null;

            if (jsonString_ != null)
            {
                retVal = JsonSerializer.Deserialize<GeoITDPurchaseQueryRequest>(jsonString_);
                retVal.NormalizeStrings();
            }

            return retVal;
        }

        public static PurchaseQueryRequest ToPurchaseQueryRequest(GeoITDPurchaseQueryRequest src_)
        {
            PurchaseQueryRequest retVal = new PurchaseQueryRequest();

            try
            {
                retVal = new PurchaseQueryRequest()
                {
                    PosID = src_.PosID,
                    SystemId = src_.SystemID,
                    Branch = src_.Branch,
                    ClientAppId = src_.ClientAppId,
                    UserId = src_.UserId,
                    TransactionDateTimeyyyyMMddHHmmssSSS = src_.TransactionDateTime,
                    TransactionId = src_.TransactionId,
                    STransactionId = $"{src_.TransactionId}"
                };
            }
            catch
            {
            }

            return retVal;
        }

        internal void NormalizeStrings()
        {
            PosID = PosID ?? "";
            SystemID = SystemID ?? "";
            Branch = Branch ?? "";
            ClientAppId = ClientAppId ?? "";
            UserId = UserId ?? "";
            TransactionDateTime = TransactionDateTime ?? "";
        }
    }

    #region Helper Classes
    public class DateTimeNullHandlingConverter : JsonConverter<DateTime>
    {
        public override DateTime Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            DateTime retVal = DateTime.MinValue;
            if (reader.TokenType != JsonTokenType.Null)
            {
                string dateTimeStr = reader.GetString();
                try
                {
                    retVal = DateTime.ParseExact(dateTimeStr, "yyyy-MM-dd HH:mm:ss.fff", CultureInfo.InvariantCulture);
                }
                catch
                {
                    if (!DateTime.TryParse(dateTimeStr, out retVal))
                        retVal = DateTime.MinValue;
                }
            }

            return retVal;
        }

        public override void Write(Utf8JsonWriter writer, DateTime value, JsonSerializerOptions options)
        {
            if (DateTime.MinValue == value)
            {
                writer.WriteNullValue();
                return;
            }

            writer.WriteStringValue(value.ToString("yyyy-MM-dd HH:mm:ss.fff"));
        }
    }

    public class SerializerOptions
    {
        public static JsonSerializerOptions Options
        {
            get
            {
                JsonSerializerOptions retVal = new JsonSerializerOptions()
                {
                    WriteIndented = true,
                    IgnoreNullValues = false,
                    Encoder = JavaScriptEncoder.UnsafeRelaxedJsonEscaping
                };
                retVal.Converters.Add(new DateTimeNullHandlingConverter());

                return retVal;
            }
        }
    }
    #endregion Helper Classes
}