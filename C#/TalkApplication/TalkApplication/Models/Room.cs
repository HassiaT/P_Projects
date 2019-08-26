namespace TalkApplication
{
    using System;
    using System.Collections.Generic;
    using System.ComponentModel.DataAnnotations;
    using System.ComponentModel.DataAnnotations.Schema;
    using System.Data.Entity.Spatial;
    using TalkApplication.Models;

    public partial class Room
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.None)]
        public int RoomId { get; set; }

        [Required]
        [StringLength(50)]
        public string Name { get; set; }

        // [ForeignKey("R_room")]
        public ICollection<User> usersInTheroom { get; set; }

    }
}
