namespace TalkApplication.Migrations
{
    using System;
    using System.Data.Entity.Migrations;
    
    public partial class AllFineIs : DbMigration
    {
        public override void Up()
        {
           
        }
        
        public override void Down()
        {
            DropForeignKey("dbo.User", "R_room", "dbo.Room");
            DropIndex("dbo.User", new[] { "R_room" });
            DropTable("dbo.User");
            DropTable("dbo.Room");
            DropTable("dbo.Friend");
        }
    }
}
