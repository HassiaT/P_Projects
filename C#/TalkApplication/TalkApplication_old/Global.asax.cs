using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Optimization;
using System.Web.Routing;
using System.Web.Security;
using TalkApplication.Migrations;

namespace TalkApplication
{
    public class MvcApplication : System.Web.HttpApplication
    {
        protected void Application_Start()
        {
            Database.SetInitializer<UserContext>(null);
            // Database.SetInitializer<UserContext>(new CheckDatabase<UserContext>());
            AreaRegistration.RegisterAllAreas();
            FilterConfig.RegisterGlobalFilters(GlobalFilters.Filters);
            RouteConfig.RegisterRoutes(RouteTable.Routes);
            BundleConfig.RegisterBundles(BundleTable.Bundles);
        }


        protected void Session_End(object sender, EventArgs e)
        {
            string s = Session["user"].ToString();
            Console.WriteLine(" User who just left is :" + s);
            System.IO.File.WriteAllText(@"C:\Users\hassi\source\repos\TalkApplication\auto.txt", "This is generated from Session_End");
            FormsAuthentication.SignOut();
        }


        protected void Application_End(object sender, EventArgs e)
        {
            string s = Session["user"].ToString();
            Console.WriteLine(" User who just left is :" + s);
        }
    }
}
