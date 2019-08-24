using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;

namespace TestMVC
{
    public class RouteConfig
    {
        public static void RegisterRoutes(RouteCollection routes)
        {
            routes.IgnoreRoute("{resource}.axd/{*pathInfo}");

            routes.MapRoute(
                name: "Default",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Index", id = UrlParameter.Optional }
            );

            routes.MapRoute(
                name: "RegisterNewUser",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Home", action = "Register", id = UrlParameter.Optional }
            );

            routes.MapRoute(
                name: "ForgotPassword",

                url: "{controller}/{action}",
                defaults: new { controller = "Home", action = "Forgot" }
            );

            routes.MapRoute(
                name: "AuthenticationController",
                url: "{controller}/{action}/{uid}",
                defaults: new
                {
                    controller = "AuthenticationController",
                    action = "Login",
                    uid = UrlParameter.Optional,
                    pass = UrlParameter.Optional
                }
            );

            routes.MapRoute(
                name: "LoginUser",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "HomeController", action = "Login", username = UrlParameter.Optional,
                    userLastName = UrlParameter.Optional }
            );

            routes.MapRoute(
                name: "ChatBasicRoom",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Chat", action = "Index", id = UrlParameter.Optional }
            );
            
            routes.MapRoute(
                name: "ChatSpecificRoom",
                url: "{controller}/{action}/{id}",
                defaults: new { controller = "Chat", action = "Chatting", roomId =UrlParameter.Optional }
            );

        }
    }
}
