using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using System.Web;
using Microsoft.AspNet.SignalR;
using Microsoft.AspNet.SignalR.Hubs;
using TalkApplication.Models;

namespace TalkApplication.Hubs
{
    [HubName("atalkhub")]
    public class Atalkhub : Hub
    {
        public void Disconnect(string user)
        {
            if (user != null)
            {
                Debug.WriteLine("I am in function disconnect now");
                UserContext userct = new UserContext();
                var userfound = userct.users.Where(s => s.Nickname == user).FirstOrDefault<User>();
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
            }
            else
            {
                Debug.WriteLine("Username is not found");
            }
        }


        public async Task JoinRoom(string user, string roomName)
        {
            Clients.Caller.ConnectionId = Context.ConnectionId;
            //await Groups.Add(Context.ConnectionId, roomName);
            await Groups.Add(Clients.Caller.ConnectionId, roomName);
            // Clients.Group(roomName).displaymessageToPage(Context.User.Identity.Name, " joined the room.");
            // Clients.Group(roomName).displaymessageToPage(user, " joined the room.");
            string message = user + " joined  the room";
            Clients.Group(roomName).alert(message);

        }


        public void LeaveRoom(string username, string roomName)
        {
            //await Groups.Remove(Context.ConnectionId, roomName);
            //Clients.Group(roomName).displaymessageToPage(Context.User.Identity.Name, " left the room.");
            Clients.Caller.ConnectionId = Context.ConnectionId;
            //Groups.Remove(Context.ConnectionId, roomName);
            string message = username + " just left the room";
            Clients.Group(roomName).alert(message);
            Groups.Remove(Context.ConnectionId, roomName);
        }


        public void Send(string username, string message, string roomName)
        {
            Clients.Group(roomName).displaymessageToPage(username, message);
        }


        public async Task SayBye(string username, string roomName)
        {
            //await Groups.Remove(Context.ConnectionId, roomName);
            //Clients.Group(roomName).displaymessageToPage(Context.User.Identity.Name, " logged off.");
            Disconnect(username);
            Clients.Caller.ConnectionId = Context.ConnectionId;
            //Groups.Remove(Context.ConnectionId, roomName);
            await Groups.Remove(Context.ConnectionId, roomName);
            string message = username + " logged off";
            Clients.Group(roomName).alert(message);
        }
    }
}