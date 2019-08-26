using System.Data;
using System.Data.SqlClient;
using System.Data.OracleClient;
using log4net;
using static DtbAccessProject.DtbTools;

namespace DtbAccessProject
{
    public class DtbParameterManager
    {
        private static readonly ILog logger = LogManager.GetLogger(typeof(DtbParameterManager));
        public static ILog Logger => logger;


        private static IDbDataParameter createSqlParameter(string name, object value, DbType type, ParameterDirection direction)
        {
            return new SqlParameter
            {
                DbType = type,
                ParameterName = name,
                Direction = direction,
                Value = value
            };
        }

        private static IDbDataParameter createSqlParameter(string name, int size, object value, DbType type, ParameterDirection direction)
        {
            return new SqlParameter
            {
                DbType = type,
                Size = size,
                ParameterName = name,
                Direction = direction,
                Value = value
            };
        }

        private static IDbDataParameter createOracleParameter(string name, object value, DbType type, ParameterDirection direction)
        {
            return new OracleParameter
            {
                DbType = type,
                ParameterName = name,
                Direction = direction,
                Value = value
            };
        }

        private static IDbDataParameter createOracleParameter(string name, int size, object value, DbType type, ParameterDirection direction)
        {
            return new OracleParameter
            {

                DbType = type,
                Size = size,
                ParameterName = name,
                Direction = direction,
                Value = value
            };
        }

        public static IDbDataParameter createParameter(string providerName,
            string name, object value, DbType type, ParameterDirection direction = ParameterDirection.Input)
        {
            IDbDataParameter parameter = null;
            DtbProvider findProvider = getProviderId(providerName);

            switch (findProvider)
            {
                case DtbProvider.NoProvider:
                    Logger.Error("No provider for the database");
                    break;

                case DtbProvider.SqlProvider:
                    Logger.Info("SQL provider detected");
                    return createSqlParameter(name, value, type, direction);

                case DtbProvider.OdbcProvider:
                    Logger.Warn("The code for provider OdbcProvider has not been coded yet ");
                    break;

                case DtbProvider.OleProvider:
                    Logger.Warn("The code for provider OleProvider has not been coded yet ");
                    break;

                case DtbProvider.OracleProvider:
                    Logger.Info("Oracle provider is detected");
                    return createOracleParameter(name, value, type, direction);

                default:
                    Logger.Error("No provider found");
                    break;
            }
            return parameter;
        }



        public static IDbDataParameter createParameter(string providerName,
               string name, int size, object value, DbType type, ParameterDirection direction = ParameterDirection.Input)
        {

            IDbDataParameter parameter = null;
            DtbProvider findProvider = getProviderId(providerName);

            switch (findProvider)
            {
                case DtbProvider.NoProvider:
                    Logger.Error("No provider for the database");
                    break;

                case DtbProvider.SqlProvider:
                    Logger.Info("SQL provider detected");
                    return createSqlParameter(name, size, value, type, direction);

                case DtbProvider.OdbcProvider:
                    Logger.Warn("The code for provider OdbcProvider has not been coded yet ");
                    break;

                case DtbProvider.OleProvider:
                    Logger.Warn("The code for provider OleProvider has not been coded yet ");
                    break;

                case DtbProvider.OracleProvider:
                    Logger.Info("Oracle provider is detected");
                    return createOracleParameter(name, value, type, direction);

                default:
                    Logger.Error("No provider found");
                    break;
            }
            return parameter;
        }



    }
}
