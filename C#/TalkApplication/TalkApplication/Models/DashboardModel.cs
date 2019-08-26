using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace TalkApplication.Models
{
    public class DashboardModel
    {
        public string username { get; set; }

        // This property will hold a state, selected by user
        [Required]
        [Display(Name = "Room")]
        public string room { get; set; }

        // This property will hold all available states for selection
        public IEnumerable<SelectListItem> rooms { get; set; }

    }
}