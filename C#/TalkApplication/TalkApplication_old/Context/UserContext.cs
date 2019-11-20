namespace TalkApplication
{
    using System;
    using System.Data.Entity;
    using System.Data.Entity.ModelConfiguration.Conventions;
    using System.Linq;
    using TalkApplication.Models;

    public partial class UserContext : DbContext
    {
        public UserContext()
       : base("name= ATalkConnection")
        { }

        public virtual DbSet<User> users { get; set; }
        public virtual DbSet<Friend> friends { get; set; }
        public virtual DbSet<Room> rooms { get; set; }
               
        protected override void OnModelCreating(DbModelBuilder modelBuilder)
        {
            modelBuilder.Conventions.Remove<PluralizingTableNameConvention>();
            //modelBuilder.Entity<Friend>().ToTable("Friend");

            modelBuilder.Entity<User>()
           .HasRequired <Room>(s => s.r)
           .WithMany(g => g.usersInTheroom)
           .HasForeignKey<int>(s => s.R_room);

        }
    }
}