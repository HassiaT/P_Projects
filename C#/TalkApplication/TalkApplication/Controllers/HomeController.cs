using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Web;
using System.Web.Mvc;
using TalkApplication;
using TalkApplication.Models;

namespace TestMVC.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index(string message = null, bool err = false)
        {
            if (!err)
            {
                if (message != null)
                {
                    ViewBag.Success = message;
                }
            }
            else
            {
                if (message != null)
                {
                    ViewBag.Error = message;
                }
            }
            return View();
        }

        [HttpPost]
        public ActionResult Index(LoginViewModel m)
        {
            string message = "Successfully logged off!";
            if (message != null)
            {
                ViewBag.Success = message;
            }
            return View("Index", new LoginViewModel());
        }

        public ActionResult Register()
        {
            return View("~/Views/User/Create.cshtml");
        }
    }
}
