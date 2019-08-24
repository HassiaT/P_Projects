using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace TestMVC.Controllers
{
    public class AuthenticationController : Controller
    {


        public ActionResult Register()
        {
            return View();
        }




        public ActionResult Login()
        {
            // if User already has an account --->> found in the database
            //RedirectToRoute(Go to room 0);

            //If NOT print message that password and id are WRONG but stays on the same page

            return View();
        }

    }
}