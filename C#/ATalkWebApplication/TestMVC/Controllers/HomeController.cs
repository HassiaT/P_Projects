using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace TestMVC.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult Register()
        {
            return RedirectToAction("Register", "AuthenticationController");
        }

        public ActionResult Login()
        {
            // if User already has an account --->> found in the database
            //RedirectToRoute(Go to room 0);
            // return RedirectToAction("Index", "ChatController");
            //If NOT print message that password and id are WRONG but stays on the same page
       
            return RedirectToAction("Login", "AuthenticationController");
        }


        public ActionResult Forgot()
        {
            return View();
        }
    }
}