using log4net;
using System.Configuration;


namespace DtbAccessProject
{
    public class DtbFactory
    {

        private static readonly ILog logger = LogManager.GetLogger(typeof(DtbFactory));
        public static ILog Logger => logger;

        private DtbConfiguration dtbConfiguration;
        public DtbConfiguration DtbConfiguration { get => dtbConfiguration; set => dtbConfiguration = value; }

        public DtbFactory(DtbConfiguration configuration)
        {
            DtbConfiguration = configuration;
            Logger.Info("Constructor DtbFactory OK ");
        }


        public string getProviderName()
        {
            Logger.Info("Function getProviderName OK");
            return DtbConfiguration.ConnectionProvider;
        }


        public IDtbHandler createDatabase()
        {
            IDtbHandler dtbase = null;
            string strProvider = DtbConfiguration.ConnectionProvider.ToLower();
            DtbTools.DtbProvider providerType = DtbTools.getProviderId(strProvider);

            switch (providerType)
            {
                case DtbTools.DtbProvider.NoProvider:
                    Logger.Error("No provider for the database");
                    break;

                case DtbTools.DtbProvider.SqlProvider:
                    Logger.Info("SQL provider detected - SQL database ");
                    string connection = DtbConfiguration.ConnectionString;
                    return new SQLDataAccess(connection);

                case DtbTools.DtbProvider.OdbcProvider:
                    Logger.Warn("Odbc provider - ODBC database not created");
                    break;

                case DtbTools.DtbProvider.OleProvider:
                    Logger.Warn("OLE DB provider - OLE DB database not created");
                    break;

                case DtbTools.DtbProvider.OracleProvider:
                    Logger.Info("Oracle provider - ORACLE DB not created ");
                    break;

                default:
                    Logger.Error("Default case - No provider for the database - Database cannot be created");
                    break;
            }
            Logger.Info("End of function createDatabase");
            return dtbase;
        }
    }
}