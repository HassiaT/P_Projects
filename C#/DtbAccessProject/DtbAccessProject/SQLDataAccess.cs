using System;
using System.Data;
using System.Data.SqlClient;
using log4net;

namespace DtbAccessProject
{
    public class SQLDataAccess : IDtbHandler
    {
        private string connection;
        private static readonly ILog logger = LogManager.GetLogger(typeof(SQLDataAccess));
        public string Connection { get => connection; set => connection = value; }
        public static ILog Logger => logger;



        public SQLDataAccess(string connectionString)
        {
            connection = connectionString;
            Logger.Info("SLQAccess constructor - Connection string is :"+connection);
            Logger.Info("SLQAccess constructor - Connection string has been initialized");
        }

        public void closeaConnection(IDbConnection conn)
        {
            var sqlConnection = (SqlConnection)(conn);
            sqlConnection.Close();
            sqlConnection.Dispose();
            Logger.Info("Connection to the database is now closed");
        }

        public IDbCommand createaCommand(string text, CommandType cmdType, IDbConnection conn)
        {
            try
            {
                SqlCommand command = new SqlCommand
                {
                    CommandText = text,
                    Connection = (SqlConnection)conn,
                    CommandType = cmdType
                };
                return command;
            }
            catch (Exception e)
            {
                Logger.Error("Command could not be created!" + e.Message);
            }
            return null;
        }

        public IDbConnection createaConnection()
        {
            try
            {
                return new SqlConnection(connection);
            }
            catch (Exception e)
            {
                Logger.Error("The databse connection could not be established!" + e.Message);
            }
            return null;
        }

        public IDbDataParameter createaParameter(IDbCommand cmd)
        {
            try
            {
                SqlCommand sqlCommand = (SqlCommand)cmd;
                IDbDataParameter param = sqlCommand.CreateParameter();
                return param;
            }
            catch (Exception e)
            {
                Logger.Error("Could not create SQL data parameter " + e.Message);
            }
            return null;
        }

        public IDbDataAdapter createaAdapter(IDbCommand cmd)
        {
            try
            {
                IDbDataAdapter adp = new SqlDataAdapter((SqlCommand)(cmd));
                return adp;
            }
            catch (Exception e)
            {
                Logger.Error("Could not create SQL data adapter!" + e.Message);
            }
            return null;
        }

        public static int method(int a)
        {
            Logger.Debug("In function method that returns the same input ");
            return a;
        }
    }

}