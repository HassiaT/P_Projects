using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using TalkApplication.Models;

namespace TalkApplication.Controllers
{
    public class ChatController : Controller
    {
        //GET: Go/Chat/
        public ActionResult Connect()
        {
            var allRooms = GetAllRooms();
            var model = new DashboardModel();
            // Create a list of SelectListItems so these can be rendered on the page
            model.rooms = GetSelectListItems(allRooms);
            return View(model);
        }

        private IEnumerable<SelectListItem> GetSelectListItems(IEnumerable<string> elements)
        {
            var selectList = new List<SelectListItem>();
            foreach (var element in elements)
            {
                selectList.Add(new SelectListItem
                {
                    Value = element,
                    Text = element
                });
            }
            return selectList;
        }

        private IEnumerable<string> GetAllRooms()
        {
            List<string> rooms_name = new List<string>();
            UserContext ctx = new UserContext();
            var allRooms = ctx.rooms.ToList();
            foreach (var r in allRooms)
            {
                if (r.Name != "") rooms_name.Add(r.Name);
            }
            return rooms_name;
        }


        [HttpPost]
        public ActionResult Connect(DashboardModel model)
        {
            var rooms = GetAllRooms();
            model.rooms = GetSelectListItems(rooms);
            string user = null;
            string message = null;
            user = model.username;

            var choosenRoom = model.room;

            if (Request.Form["submit2"] != null)
            {
                string notification = "Successfully logged off";
                return RedirectToAction("Index", "Home", new RouteValueDictionary { { "message", notification } });
            }

            if (ModelState.IsValid)
            {
                RouteValueDictionary routeValues = null;
                routeValues = new RouteValueDictionary { { "name", choosenRoom }, { "user", user } };
                UserContext userCt = new UserContext();
                var roomId = userCt.rooms.SingleOrDefault(w => w.Name == choosenRoom);
                var userfound = userCt.users.Where(s => s.Nickname == user).FirstOrDefault<User>();
                if (roomId != null && user != null)
                {
                    try
                    {
                        int idofRoom = roomId.RoomId;
                        Room toAdd = new Room();
                        toAdd.RoomId = idofRoom;
                        toAdd.Name = choosenRoom;
                        userfound.ConfirmPassword = userfound.Password;
                        userfound.R_room = idofRoom;
                        userCt.Entry(userfound).State = System.Data.Entity.EntityState.Modified;
                        userCt.SaveChanges();
                    }

                    catch (Exception e)
                    {
                        Console.WriteLine("Exception message : " + e.Message);
                    }
                }
                return RedirectToAction("Go", "Chat", routeValues);
            }
            else
            {
                message = "This room does not exist! Please create a new one";
            }
            return RedirectToAction("Dashboard", "User", new RouteValueDictionary { { "name", user }, { "message", message } });
        }

        [Route("Chat/Go/{name}", Name = "ChatRoom")]
        public ActionResult Go(string name, string user)
        {
            ViewData["room"] = name;
            ViewData["currentUser"] = user;
            return View();
        }
    }
}