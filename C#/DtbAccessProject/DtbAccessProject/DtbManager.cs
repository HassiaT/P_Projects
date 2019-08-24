using System.Data;
using log4net;
using System;

namespace DtbAccessProject
{
    public class DtbManager
    {
        private static ILog logger = LogManager.GetLogger(typeof(DtbManager));
        private DtbFactory databaseFactory;
        private IDtbHandler databaseHandler;
        private string providerName;

        public static ILog Logger { get => logger; set => logger = value; }
        public DtbFactory DatabaseFactory { get => databaseFactory; set => databaseFactory = value; }
        public IDtbHandler DatabaseHandler { get => databaseHandler; set => databaseHandler = value; }
        public string ProviderName { get => providerName; set => providerName = value; }


        public DtbManager(DtbConfiguration conf)
        {
            Logger.Info("Constructor DtbManager - initializing attributes");
            DatabaseFactory = new DtbFactory(conf);
            DatabaseHandler = DatabaseFactory.createDatabase();
            ProviderName = DatabaseFactory.getProviderName();
        }


        public IDbConnection getDatanaseConnection()
        {
            return DatabaseHandler.createaConnection();
        }


        public void closeConnection(IDbConnection idb)
        {
            DatabaseHandler.closeaConnection(idb);
        }

        public IDbDataParameter createParameterManager(string name, object value, DbType type)
        {
            return DtbParameterManager.createParameter(ProviderName, name, value, type, ParameterDirection.Input);
        }

        public IDbDataParameter createParameterManager(string name, int size, object value, DbType type)
        {
            return DtbParameterManager.createParameter(ProviderName, name, size, value, type, ParameterDirection.Input);
        }

        public IDbDataParameter createParameterManager(string name, int size, object value, DbType type, ParameterDirection direction)
        {
            return DtbParameterManager.createParameter(ProviderName, name, size, value, type, direction);
        }

        public DataTable GetDataTable(string cmd, CommandType cmdType, IDataParameter[] parameters = null)
        {
            Logger.Info("Starting function GetDataTable");
            using (var connection = DatabaseHandler.createaConnection())
            {
                connection.Open();
                Logger.Info("Connection to the database is now open in function GetDataTable");
                using (var command = DatabaseHandler.createaCommand(cmd, cmdType, connection))
                {
                    if (parameters != null)
                    {
                        foreach (var param in parameters)
                            command.Parameters.Add(param);
                    }
                    var dataset = new DataSet();
                    var dataAdapter = databaseHandler.createaAdapter(command);
                    dataAdapter.Fill(dataset);
                    return dataset.Tables[0];
                }
            }
        }

        public DataSet GetDataSet(string commandText, CommandType cmdType, IDataParameter[] parameters = null)
        {
            Logger.Info("Starting function GetDataSet");
            using (var connection = DatabaseHandler.createaConnection())
            {
                connection.Open();
                Logger.Info("Connection to the database is now open in function GetDataSet");
                using (var command = DatabaseHandler.createaCommand(commandText, cmdType, connection))
                {
                    if (parameters != null)
                    {
                        foreach (var param in parameters)
                            command.Parameters.Add(param);
                    }
                    var dataset = new DataSet();
                    var dataAdapter = databaseHandler.createaAdapter(command);
                    dataAdapter.Fill(dataset);
                    return dataset;
                }
            }
        }


        public IDataReader GetDataReader(string commandText, CommandType cmdType,
            IDbDataParameter[] parameters, out IDbConnection connection)
        {
            Logger.Info("Starting function GetDataReader");

            IDataReader dataReader = null;
            using (connection = databaseHandler.createaConnection())
            {
                connection.Open();
                Logger.Info("Function GetDataReader - database connection open");
                var command = databaseHandler.createaCommand(commandText, cmdType, connection);
                if (parameters != null)
                {
                    foreach (var parameter in parameters)
                        command.Parameters.Add(parameter);
                }
                dataReader = command.ExecuteReader();
            }
            Logger.Info("Function GetDataReader");
            return dataReader;
        }


        public void DeleteData(string commandText, CommandType cmdType, IDbDataParameter[] parameters = null)
        {
            Logger.Info(" Starting function DeleteData");
            using (var connection = databaseHandler.createaConnection())
            {
                connection.Open();
                using (var command = DatabaseHandler.createaCommand(commandText, cmdType, connection))
                {
                    if (parameters != null)
                    {
                        foreach (var param in parameters)
                            command.Parameters.Add(param); ;
                    }
                    int reTValue = command.ExecuteNonQuery();
                    Logger.Info("Function DeleteData, number of rows impacted is " + reTValue);
                }
            }
        }


        public void InsertData(string commandText, CommandType cmdType, IDbDataParameter[] parameters = null)
        {
            Logger.Info(" Starting function InsertData");
            using (var connection = databaseHandler.createaConnection())
            {
                connection.Open();
                using (var command = DatabaseHandler.createaCommand(commandText, cmdType, connection))
                {
                    if (parameters != null)
                    {
                        foreach (var param in parameters)
                            command.Parameters.Add(param); ;
                    }
                    int reTValue = command.ExecuteNonQuery();
                    Logger.Info("Function InsertData, number of rows impacted is " + reTValue);
                }
            }
        }


        public void InsertDataWithTransactions(string commandText, CommandType cmdType, IDbDataParameter[] parameters = null)
        {
            Logger.Info(" Starting function InsertDataWithTransactions");
            IDbTransaction transaction = null;
            using (var connection = databaseHandler.createaConnection())
            {
                connection.Open();
                transaction = connection.BeginTransaction();
                using (var command = DatabaseHandler.createaCommand(commandText, cmdType, connection))
                {
                    if (parameters != null)
                    {
                        foreach (var param in parameters)
                            command.Parameters.Add(param); ;
                    }
                    try
                    {
                        int reTValue = command.ExecuteNonQuery();
                        transaction.Commit();
                        Logger.Info("Function InsertDataWithTransactions, number of rows impacted is " + reTValue);
                    }
                    catch (Exception)
                    {
                        Logger.Error("Function InsertDataWithTransactions, insertion operation failed. Rolling back...");
                        transaction.Rollback();
                    }
                    finally
                    {
                        connection.Close();
                        Logger.Info("Function InsertDataWithTransactions.Closing database");
                    }
                }
            }
        }


        public void UpdateData(string commandText, CommandType cmdType, IDbDataParameter[] parameters = null)
        {
            Logger.Info(" Starting function UpdateData");
            using (var connection = databaseHandler.createaConnection())
            {
                connection.Open();
                using (var command = DatabaseHandler.createaCommand(commandText, cmdType, connection))
                {
                    if (parameters != null)
                    {
                        foreach (var param in parameters)
                            command.Parameters.Add(param); ;
                    }
                    int reTValue = command.ExecuteNonQuery();
                    Logger.Info("Function UpdateData, number of rows impacted is " + reTValue);
                }
            }
        }


        public void UpdateDataWithTransactions(string commandText, CommandType cmdType, IDbDataParameter[] parameters = null)
        {
            Logger.Info(" Starting function UpdateDataWithTransactions");
            IDbTransaction transaction = null;
            using (var connection = databaseHandler.createaConnection())
            {
                connection.Open();
                transaction = connection.BeginTransaction();
                using (var command = DatabaseHandler.createaCommand(commandText, cmdType, connection))
                {
                    if (parameters != null)
                    {
                        foreach (var param in parameters)
                            command.Parameters.Add(param); ;
                    }
                    try
                    {
                        int reTValue = command.ExecuteNonQuery();
                        transaction.Commit();
                        Logger.Info("Function UpdateDataWithTransactions, number of rows impacted is " + reTValue);
                    }
                    catch (Exception)
                    {
                        Logger.Error("Function UpdateDataWithTransactions, insertion operation failed. Rolling back...");
                        transaction.Rollback();
                    }
                    finally
                    {
                        connection.Close();
                        Logger.Info("Function UpdateDataWithTransactions.Closing database");
                    }
                }
            }
        }

        public object GetScalarValue(string commandText, CommandType cmdType, IDbDataParameter[]
             parameters = null)
        {
            Logger.Info(" Starting function GetScalarValue");
            using (var connection = databaseHandler.createaConnection())
            {
                connection.Open();
                using (var command = DatabaseHandler.createaCommand(commandText, cmdType, connection))
                {

                    if (parameters != null)
                    {
                        foreach (var param in parameters)
                            command.Parameters.Add(param); ;
                    }
                    Logger.Info("Function GetScalarValue. Returning value...");
                    return command.ExecuteScalar();
                }
            }
        }
    }
}