using System;
using System.Collections.Generic;
using System.Data.Entity.Validation;
using System.Linq;
using System.Threading.Tasks;
using System.Web;
using System.Web.Mvc;
using System.Web.Routing;
using TalkApplication.Models;

namespace TalkApplication.Controllers
{
    public class UserController : Controller
    {
        private IEnumerable<SelectListItem> GetSelectListItems(IEnumerable<string> elements)
        {
            // Create an empty list to hold result of the operation
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
            var allRooms = ctx.rooms.Where(x => string.IsNullOrEmpty(x.Name) == false).ToList();
            foreach (var r in allRooms)
            {
                rooms_name.Add(r.Name);
            }
            return rooms_name;
        }

        // GET : Users
        public ActionResult Create()
        {
            return View();
        }


        //GET : User/Dashboard/
        public ActionResult Dashboard(string name, string message = "")
        {
            DashboardModel mm = new DashboardModel();
            using (var userCont = new UserContext())
            {
                ViewData["legendFriend"] = "My contacts";
                mm.username = name;
                ViewData["currentUser"] = name;
                IEnumerable<User> alltheUsers = userCont.users.Where(x => x.Nickname != name).ToList();
                IEnumerable<Room> alltheRooms = userCont.rooms.Where(x => string.IsNullOrEmpty(x.Name) == false).ToList();
                ViewData["friends"] = alltheUsers;
                var allRooms = GetAllRooms();
                mm.rooms = GetSelectListItems(allRooms);
            }
            if (message != "")
            {
                ViewBag.Error = message;
            }
            return View(mm);
        }  

        [HttpPost]
        public ActionResult Create(User userForm)
        {
            if (ModelState.IsValid)
            {
                UserContext dbFullUser = new UserContext();
                /* if a user with this nickname ALREADY exists in the database */
                if (dbFullUser.users.Any(w => w.Nickname == userForm.Nickname))
                {
                    ViewBag.DuplicateMessage = " There is already with a user with this nickname!";
                    return View("Create", userForm);
                }
                else
                {
                    User us = new User
                    {
                        Nickname = userForm.Nickname,
                        ConfirmPassword = userForm.ConfirmPassword,
                        Password = userForm.Password,
                        Lastname = userForm.Lastname,
                        Firstname = userForm.Firstname,
                        Email = userForm.Email,
                        statusUser = status.disonnected
                    };
                    try
                    {
                        dbFullUser.users.Add(us);
                        dbFullUser.SaveChanges();
                    }
                    catch (DbEntityValidationException e)
                    {
                        foreach (var eve in e.EntityValidationErrors)
                        {
                            foreach (var ve in eve.ValidationErrors)
                            {
                                Console.WriteLine("- Property: \"{0}\", Value: \"{1}\", Error: \"{2}\"",
                                    ve.PropertyName,
                                    eve.Entry.CurrentValues.GetValue<object>(ve.PropertyName),
                                    ve.ErrorMessage);
                            }
                        }
                    }
                    ModelState.Clear();
                    ViewBag.Success = "Successful registration !";
                }
                return View("Create", new User());
            }

            //In case of validation errors
            else
            {
                ViewBag.Error = "Some fields are incorrect for registration!";
            }
            return View("Create", new User());
        }



        [HttpPost]
        public ActionResult LogOut(RoomViewModel mvm)
        {
            UserContext userct = new UserContext();
            var userfound = userct.users.Where(s => s.Nickname == mvm.username).FirstOrDefault<User>();
            //var defaultRoom = userct.rooms.Where(x => string.IsNullOrEmpty(x.Name) == null).FirstOrDefault<Room>();
            var defaultRoom = userct.rooms.Where(x => (string.IsNullOrEmpty(x.Name) == null)).FirstOrDefault<Room>();

            if (userfound != null)
            {
                try
                {
                    int id = (int)((Room)defaultRoom).RoomId;
                    userfound.ConfirmPassword = userfound.Password;
                    userfound.R_room = id;
                    userfound.statusUser = status.disonnected;
                    userct.Entry(userfound).State = System.Data.Entity.EntityState.Modified;
                    userct.SaveChanges();
                }
                catch (Exception e)
                {
                    Console.WriteLine("Exception message : " + e.Message);
                }
            }
            string message = "Successfully logged off";
            return RedirectToAction("Index", "Home", new RouteValueDictionary { { "message", message } });
        }


        [HttpPost]
        public ActionResult Leave(RoomViewModel mvm)
        {
            UserContext userct = new UserContext();
            string message = "";
            var defaultRoom = userct.rooms.Where(x => (string.IsNullOrEmpty(x.Name) == null)).FirstOrDefault<Room>();

            if (defaultRoom != null)
            {
                int id = (int)((Room)defaultRoom).RoomId;
                try
                {
                    // user leaving current room --> put him in no room
                    var userfound = userct.users.Where(s => s.Nickname == mvm.username).FirstOrDefault<User>();
                    if (userfound != null)
                    {
                        userfound.ConfirmPassword = userfound.Password;
                        userfound.R_room = id;
                        userct.Entry(userfound).State = System.Data.Entity.EntityState.Modified;
                        userct.SaveChanges();
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine("Exception message : " + e.Message);
                }
                message = "Successfully left " + mvm.room;
            }
            return RedirectToAction("Dashboard", "User", new RouteValueDictionary { { "name", mvm.username }, { "message", message } });
        }



        // GET : Forgot password form
        public ActionResult Forgot(string message = null)
        {
            if (message != null)
            {
                ViewBag.Error = message;
            }
            return View();
        }


        [HttpPost]
        public ActionResult Forgot(ForgotPasswordViewModel fpv)
        {
            UserContext userct = new UserContext();
            string message = "";
            var defaultUser = userct.users.Where(x => fpv.Nickname == x.Nickname && fpv.Email == x.Email).FirstOrDefault<User>();

            if (ModelState.IsValid)
            {
                if (defaultUser != null)
                {
                    try
                    {
                        defaultUser.Password = fpv.Password;
                        defaultUser.ConfirmPassword = defaultUser.Password;
                        userct.Entry(defaultUser).State = System.Data.Entity.EntityState.Modified;
                        userct.SaveChanges();
                    }

                    catch (Exception e)
                    {
                        Console.WriteLine("Exception message : " + e.Message);
                    }

                }

                else
                {
                    message = "This user is not found.";
                }
            }

            else
            {
                message = "Incorrect fields";
            }

            return RedirectToAction("Forgot", "User", message);


        }
    }
}