using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Web;


namespace TalkApplication.Models
{
    public enum status
    {
        disonnected = 0,
        online = 1
    };


    public partial class User
    {
        [Key]
        public int id { get; set; }


        [Required]
        [StringLength(50)]
        [Display(Name = "Nickname")]
        public string Nickname { get; set; }

        [Required]
        [StringLength(100, ErrorMessage = "The {0} must be at least {2} characters long.", MinimumLength = 6)]
        [DataType(DataType.Password)]
        [Display(Name = "Password")]
        public string Password { get; set; }


        [NotMappedAttribute]
        [Required]
        [DataType(DataType.Password)]
        [Display(Name = "Confirm password")]
        [Compare("Password", ErrorMessage = "The password and confirmation password do not match.")]
        public string ConfirmPassword { get; set; }


        [Required]
        [StringLength(50)]
        public string Lastname { get; set; }

        [Required]
        [StringLength(50)]
        public string Firstname { get; set; }

        [Required]
        [DataType(DataType.EmailAddress, ErrorMessage = ("Email format is not valid"))]
        [StringLength(50)]
        public string Email { get; set; }

        [EnumDataType(typeof(status))]
        public status statusUser { get; set; }


        public int R_room { get; set; }
        public Room r { get; set; }

    }
}