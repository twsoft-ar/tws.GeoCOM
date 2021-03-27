using System;
using System.Collections.Generic;
using System.Drawing;
using System.Globalization;
using System.IO.Ports;
using System.Windows.Forms;
using TWS.Configurator;
using TWS.Log;

namespace TWS.GeoITD.Configuration
{
    public class ConfigMgr : ConfiguratorBase
    {
        #region Singleton
        private static ConfigMgr mConfiguration = new ConfigMgr();

        static ConfigMgr()
        { }

        private ConfigMgr()
        {
        }

        public static ConfigMgr Instance
        {
            get { return mConfiguration; }
        }
        #endregion Singleton

        public void Initialize(string fileName_)
        {
            base.mFileName = fileName_;
        }

        #region General

        public bool ShowIFCVersion
        {
            get { return GetBoolenValue("SHOW_VERSION"); }
        }

        public Logger.VERBOSITY_LEVEL LogVerbosityLevel
        {
            get
            {
                Logger.VERBOSITY_LEVEL retVal = Logger.VERBOSITY_LEVEL.INFO;

                try
                {
                    retVal = (Logger.VERBOSITY_LEVEL)GetIntegerValue("LOG_VERBOSITY_LEVEL");
                }
                catch (Exception ex)
                {
                    retVal = Logger.VERBOSITY_LEVEL.INFO;
                }

                return retVal;
            }
        }
        #endregion general

        public string MercadoLibreAPIURL
        {
            get { return GetStringValue("MERCADO_LIBRE_API_URL").Trim(); }
        }

        public string MercadoPagoAPIURL
        {
            get { return GetStringValue("MERCADO_PAGO_API_URL").Trim(); }
        }

        public string MercadoLibreAPIAccessTOKEN
        {
            get { return GetStringValue("MERCADO_PAGO_API_ACCESS_TOKEN").Trim(); }
        }

        public string QRPostOrderResource
        {
            get { return GetStringValue("QR_POST_ORDER_RESOURCE").Trim(); }
        }

        public string PayerQRPostOrderResource
        {
            get { return GetStringValue("PAYER_QR_POST_ORDER_RESOURCE").Trim(); }
        }

        public string PaymentSearchResource
        {
            get { return GetStringValue("PAYMENT_SEARCH_RESOURCE").Trim(); }
        }

        public string CustomerName
        {
            get { return GetStringValue("CUSTOMER_NAME").Trim(); }
        }

        public string CustomerFiscalID
        {
            get { return GetStringValue("CUSTOMER_FISCAL_ID").Trim(); }
        }

        public bool UseSimphonyDecimalSeparatorForTenders
        {
            get { return GetBoolenValue("USE_SIMPHONY_DECIMAL_SEPARATOR_FOR_TENDERS"); }
        }

        public string CollectorID
        {
            get { return GetStringValue("COLLECTOR_ID").Trim(); }
        }

        public string StoreID
        {
            get { return GetStringValue("STORE_ID").Trim(); }
        }

        public string Currency
        {
            get { return GetStringValue("MP_CURRENCY").Trim(); }
        }

        public int MP_TenderObjNumber
        {
            get { return GetIntegerValue("MP_TENDER_OBJ_NUM"); }
        }

        public int Timeout
        {
            get { return GetIntegerValue("MP_TIMEOUT"); }
        }

        public string SponsorID
        {
            get { return GetStringValue("SPONSOR_ID").Trim(); }
        }

        public string NotificationURL
        {
            get { return GetStringValue("NOTIFICATION_URL").Trim(); }
        }
    }
}
