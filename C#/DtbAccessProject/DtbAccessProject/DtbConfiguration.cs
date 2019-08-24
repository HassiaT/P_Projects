using System;
using System.Configuration;

using log4net;


namespace DtbAccessProject
{
    public class DtbConfiguration
    {
        private static ILog logger = LogManager.GetLogger(typeof(DtbConfiguration));
        private string connectionString;
        private string connectionProvider;

        public static ILog Logger { get => logger; set => logger = value; }
        public string ConnectionString { get => connectionString; set => connectionString = value; }
        public string ConnectionProvider { get => connectionProvider; set => connectionProvider = value; }


        public DtbConfiguration(string connstring, string provider)
        {
            ConnectionString = connstring;
            ConnectionProvider = provider;
            Logger.Info("Finished to initialize attributes for DtbConfiguration OK");
        }
    }
}