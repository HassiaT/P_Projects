using System.Data;
using System.ComponentModel;



/* This interface provides basic functions to access, manipulate data using ADO.NET objects */
namespace DtbAccessProject
{

    public interface IDtbHandler
    {
        IDbConnection createaConnection();
        void closeaConnection(IDbConnection conn);
        IDbCommand createaCommand(string text, CommandType cmdType, IDbConnection conn);
        IDbDataAdapter createaAdapter(IDbCommand cmd);
        IDbDataParameter createaParameter(IDbCommand cmd);

    }
}
