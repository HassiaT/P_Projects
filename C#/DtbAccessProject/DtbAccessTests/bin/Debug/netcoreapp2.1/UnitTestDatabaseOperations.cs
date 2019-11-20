using NUnit.Framework;
using log4net;
using DtbAccessProject;


[assembly: log4net.Config.XmlConfigurator(ConfigFile = "log4net.config", Watch = true)]

namespace Tests
{

    public class ConfigurationCls
    {
        private static ILog logger = LogManager.GetLogger(typeof(ConfigurationCls));



        private string connectionName = null;
        private string connectionstring = null;
        private string connectionProvider = null;

        public ConfigurationCls()
        {
            Logger.Info("Constructor ConfigurationCls triggered");
            initialize();
        }



        public void initialize()
        {
            if (ConnectionName == null && TestContext.Parameters.Exists("connectionName"))
            {
                ConnectionName = TestContext.Parameters["connectionName"];
            }
            else throw new System.Exception("Connection name has not been found");


            if (Connectionstring == null && TestContext.Parameters.Exists("connectionString"))
            {
                Connectionstring = TestContext.Parameters["connectionString"];
            }
            else throw new System.Exception("Connection string is null");



            if (ConnectionProvider == null && TestContext.Parameters.Exists("provider"))
            {
                ConnectionProvider = TestContext.Parameters["provider"];
            }
            else throw new System.Exception("The provider in config file has not been found");

        }



        public static ILog Logger { get => logger; set => logger = value; }
        public string ConnectionName { get => connectionName; set => connectionName = value; }
        public string Connectionstring { get => connectionstring; set => connectionstring = value; }
        public string ConnectionProvider { get => connectionProvider; set => connectionProvider = value; }
    }


    [TestFixture]
    public class Tests
    {
        private static ILog logger = LogManager.GetLogger(typeof(Tests));
        public static ILog Logger { get => logger; set => logger = value; }


        [SetUp]
        public void Start()
        {
            GlobalContext.Properties["LogName"] = "SQLDataAccess";
            Logger.Info(" Unit test class - starting procedure ");
        }


        [Test]
        public void ConnectingtoDatabase()
        {
            Logger.Info(" Unit test class - testing database connection");
            ConfigurationCls cfg = new ConfigurationCls();
            string connName = cfg.ConnectionName;
            string connString = cfg.Connectionstring;
            string connProvider = cfg.ConnectionProvider;

            Logger.Info("Connection name found is " + connName);
            Logger.Info("Connection string found is " + connString);
            Logger.Info("Connection provider found is " + connProvider);

            DtbConfiguration config = new DtbConfiguration(connString, connProvider);
            DtbManager dtbManager = new DtbManager(config);
            Logger.Info("End function ConnectingtoDatabase");
        }
    }
}