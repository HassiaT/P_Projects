using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace TestMVC.Controllers
{
    public class ChatController : Controller
    {

        // GET: Chat
        public ActionResult Index()
        {
            return RedirectToRoute(new {controller = "Chat", action = "Index", id=0 });
        }


        public ActionResult Chatting(int roomId)
        {
            return View(roomId);
        }
    }
}