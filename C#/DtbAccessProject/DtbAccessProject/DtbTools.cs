using log4net;
using System.ComponentModel;



namespace DtbAccessProject
{
    public static class DtbTools
    {
        private static readonly ILog logger = LogManager.GetLogger(typeof(DtbTools));
        public static ILog Logger => logger;


        public enum DtbProvider
        {
            [Description("No Provider found")]
            NoProvider = -1,

            [Description("system.data.sqlclient")]
            SqlProvider = 1,

            [Description("system.data.oleDb")]
            OleProvider = 2,

            [Description("system.data.odbc")]
            OdbcProvider = 3,

            [Description("system.data.oracleclient")]
            OracleProvider = 4,
        }


        public static DtbProvider getProviderId(string str)
        {
            Logger.Info("Starting function getProviderId ");
            DtbProvider dtb = DtbProvider.NoProvider;
            switch (str.ToLower())
            {
                case "system.data.sqlclient":
                    Logger.Info("SQL provider found");
                    return DtbProvider.SqlProvider;

                case "system.data.oleDb":
                    Logger.Info("OLE DB provider found");
                    return DtbProvider.OleProvider;

                case "system.data.oracleclient":
                    Logger.Info("ORACLE client provider found");
                    return DtbProvider.OracleProvider;

                case "system.data.odbc":
                    Logger.Info("ODBC provider found");
                    return DtbProvider.OdbcProvider;

               default:
                    Logger.Error("No provider found");
                    break;
            }
            return dtb;
        }
    }
}
