using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data.Entity;
using System.Linq;
using System.Transactions;
using System.Web;

namespace TalkApplication
{
    public class CheckDatabase<TContext> : IDatabaseInitializer<TContext>
        where TContext : DbContext
    {
        public void InitializeDatabase(TContext context)
        {
            using (new TransactionScope(TransactionScopeOption.Suppress))
            {
                if (!context.Database.Exists())
                {
                    throw new ConfigurationErrorsException("Database does not exist");
                }
                else
                {
                    if (!context.Database.CompatibleWithModel(true))
                    {
                        throw new InvalidOperationException(
                          "The database is not compatible with the entity model.");
                    }
                }
            }

        }
    }

}