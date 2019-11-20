using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using TalkApplication.Models;

namespace TalkApplication.Controllers
{
    public class AuthenticationController : Controller
    {
        //GET: /Authentication/Login
        public ActionResult Login()
        {
            return RedirectToAction("Index", "Home");
        }


        // POST: /Authentication/Login
        [HttpPost]
        public ActionResult Login(LoginViewModel modelUser)
        {
            if (ModelState.IsValid)
            {
                UserContext userDb = new UserContext();
                var userfound = userDb.users.SingleOrDefault(s => s.Nickname == modelUser.Username);
                if (userfound != null)
                {
                    if (modelUser.Password == userfound.Password)
                    {
                        if (userfound.statusUser == status.online)
                        {
                            string error = "The user is already connected.";
                            return RedirectToAction("Index", "Home", new RouteValueDictionary { { "message", error }, { "err", true } });
                        }

                        try
                        {
                           
                            userfound.ConfirmPassword = userfound.Password;
                            userfound.statusUser = status.online;
                            userDb.Entry(userfound).Property(x => x.statusUser).IsModified = true;
                            userDb.SaveChanges();
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine("Exception message : " + e.Message);
                        }
                    }
                    else
                    {
                        string secMess = "Incorrect password for this username";
                        return RedirectToAction("Index", "Home", new RouteValueDictionary { { "message", secMess }, { "err", true } });
                        //return View("Login", new LoginViewModel());
                    }
                    string nameUser = modelUser.Username;
                    RouteValueDictionary routeValues = null;
                    routeValues = new RouteValueDictionary {
   { "name",nameUser} };
                    return RedirectToAction("Dashboard", "User", routeValues);
                }
                else
                {
                    string mess = "There is no user with this login";
                    return RedirectToAction("Index", "Home", new RouteValueDictionary { { "message", mess }, { "err", true } });
                }
            }
            else
            {
                string secondmessage = "Username and password are not correctly formatted";

                return RedirectToAction("Index", "Home", new RouteValueDictionary { { "message", secondmessage }, { "err", true } });
            }
        }
    }
}