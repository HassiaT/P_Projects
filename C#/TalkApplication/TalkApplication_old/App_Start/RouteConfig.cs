using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace TalkApplication
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapMvcAttributeRoutes();
            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}",
                defaults: new { controller = "Home", action = "Index" }
           );

            routes.MapRoute(
               name: "ChatConnexion",
               url: "Chat/Connect/{name}",
               defaults: new { controller = "Chat", action = "Connect", name = UrlParameter.Optional }
           );


            routes.MapRoute(
            name: "UserDashboard",
            url: "User/Dashboard",
            defaults: new { controller = "User", action = "Dashboard" }
            );

        }
    }
}
